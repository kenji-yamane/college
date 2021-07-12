using Plots

include("../bdf_utils.jl")

mu = 100

function rk_fourth_order(f, a::Float64, b::Float64, k::Float64, u::Array{Float64})
    N = round((b - a)/k) |> Int

    U = [zeros(length(u)) for i in 1:N+1]
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        F0 = f(t[i], U[i])
        F1 = f(t[i] + k/2, U[i] .+ k/2*F0)
        F2 = f(t[i] + k/2, U[i] .+ k/2*F1)
        F3 = f(t[i] + k, U[i] .+ k*F2)

        U[i+1] = U[i] .+ (k/6).*(F0 .+ 2*F1 .+ 2*F2 .+ F3)
        t[i+1] = t[i] + k
    end

    return t, [U[i][1] for i in 1:length(U)], [U[i][2] for i in 1:length(U)]
end

function trapezoidal(f,a::Float64,b::Float64,k::Float64,u::Array{Float64})
    N = round((b - a)/k) |> Int

    U = [zeros(length(u)) for i in 1:N+1]
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k
        ind_coeff = (k*mu - 2/k)*U[i][1] + (k^2*mu/2 - 1)*f(t, U[i])[1] - (k/2 + 1)*U[i][2] - k/2*f(t, U[i])[2]
        rs = roots(Polynomial(reverse([k*mu, -(k*mu*U[i][1] + k^2*mu/2*f(t, U[i])[1]), k^2/2 - k*mu + 2/k, ind_coeff])))
        rs = Complex.(rs)
        real_rs = rs[findall(<(1e-3), [r.im for r in rs])]
        real_rs = [r.re for r  in real_rs]
        U[i + 1][1] = real_rs[findmin([abs(r/k - U[i][1]/k - U[i][2]) for r in real_rs])[2]]
        U[i + 1][2] = 2*(U[i + 1][1] - U[i][1])/k - f(t, U[i])[1]
    end

    return t, [U[i][1] for i in 1:length(U)], [U[i][2] for i in 1:length(U)]
end

function bdf1(f,a::Float64,b::Float64,k::Float64,u::Array{Float64})
    N = round((b - a)/k) |> Int

    U = [zeros(length(u)) for i in 1:N+1]
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k
        ind_coeff = (k*mu - 1)*U[i][1] - k*U[i][2]
        rs = roots(Polynomial(reverse([k*mu, -k*mu*U[i][1], 1 + k^2 - k*mu, ind_coeff])))
        rs = Complex.(rs)
        real_rs = rs[findall(<(1e-3), [r.im for r in rs])]
        real_rs = [r.re for r  in real_rs]
        U[i + 1][1] = real_rs[findmin([abs(r/k - U[i][1]/k - U[i][2]) for r in real_rs])[2]]
        U[i + 1][2] = (U[i + 1][1] - U[i][1])/k
    end

    return t, [U[i][1] for i in 1:length(U)], [U[i][2] for i in 1:length(U)]
end

function bdf_higher_order(f,a::Float64,b::Float64,k::Float64,u::Array{Float64}, order::Int64)
    N = round((b - a)/k) |> Int

    t, Uvalue, Uprime = bdf1(f, a, a + (order - 1)*k, k, u)
    t = [t..., zeros(N + 1 - order)...]
    U = [[v, p] for (v, p) in zip([Uvalue..., zeros(N + 1 - order)...], [Uprime..., zeros(N + 1 - order)...])]

    alphas = bdf_alphas[order]
    betas = bdf_betas[order]
    for i = 1:N-order+1
        t[i+order] = t[i+order-1] + k
        sumInFirst = sum([alphas[j]*U[i + j - 1][1] for j in 1:order])
        sumInSecond = sum([alphas[j]*U[i + j - 1][2] for j in 1:order])
        ind_coeff = alphas[order + 1]/betas[order + 1]/k*sumInFirst + sumInSecond - mu*sumInFirst
        rs = roots(Polynomial(reverse([mu*alphas[order + 1], mu*sumInFirst, alphas[order + 1]^2/betas[order + 1]/k - mu*alphas[order + 1] + 1, ind_coeff])))
        rs = Complex.(rs)
        real_rs = rs[findall(<(1e-3), [r.im for r in rs])]
        real_rs = [r.re for r  in real_rs]
        U[i + order][1] = real_rs[findmin([abs(r - U[i + order - 1][1]) for r in real_rs])[2]]
        U[i + order][2] = (alphas[order + 1]*U[i + order][1] + sumInFirst)/(betas[order + 1]*k)
    end

    return t, [U[i][1] for i in 1:length(U)], [U[i][2] for i in 1:length(U)]
end

Plots.scalefontsizes()
Plots.scalefontsizes(1.6)

f(t, u) = [u[2], mu*(1 - u[1]^2)*u[2] - u[1]]

plot(fontfamily="computer modern", ylims=(-2.5, 2))
t, U, _ = bdf1(f, 0., 400., 0.001, [2., 0.])
plot!(t, U, label="analytic")
t, U, _ = rk_fourth_order(f, 0., 400., 0.01, [2., 0.])
plot!(t, U, label="runge kutta")
t, U, _ = trapezoidal(f, 0., 400., 0.01, [2., 0.])
plot!(t, U, label="trapezoidal")
savefig("../figures/poor_methods.pdf")

plot(fontfamily="computer modern", ylims=(-2.5, 2))
t, U, _ = bdf1(f, 0., 400., 0.001, [2., 0.])
plot!(t, U, label="analytic")
t, U, _ = bdf1(f, 0., 400., 0.01, [2., 0.])
plot!(t, U, label="bdf1")
for i in 2:5
    local t, U, _ = bdf_higher_order(f, 0., 400., 0.01, [2., 0.], i)
    plot!(t, U, label="bdf$(i)")
end
savefig("../figures/bdf_methods.pdf")
