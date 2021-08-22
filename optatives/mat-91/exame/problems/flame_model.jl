using Plots

include("../bdf_utils.jl")

delta = 1e-4

function rk_fourth_order(f,a::Float64,b::Float64,k::Float64,u::Float64)
    N = round((b - a)/k) |> Int

    U = zeros(N+1)
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k

        F0 = f(t[i], U[i])
        F1 = f(t[i] + k/2, U[i] + k/2*F0)
        F2 = f(t[i] + k/2, U[i] + k/2*F1)
        F3 = f(t[i] + k, U[i] + k*F2)
        U[i+1] = U[i] + k/6*(F0 + 2*F1 + 2*F2 + F3)
    end

    return t,U
end

function trapezoidal(f,a::Float64,b::Float64,k::Float64,u::Float64)
    N = (b - a)/k |> round |> Int

    U = zeros(N+1)
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k
        ind_coeff = -U[i] - k*f(t[i], U[i])/2
        rs = roots(Polynomial(reverse([k/2, -k/2, 1, ind_coeff])))
        rs = Complex.(rs)
        U[i + 1] = rs[findmin([abs(r.im) for r in rs])[2]].re
    end

    return t,U
end

function bdf1(f,a::Float64,b::Float64,k::Float64,u::Float64)
    N = round((b - a)/k) |> Int

    U = zeros(N+1)
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k
        ind_coeff = -U[i]
        rs = roots(Polynomial(reverse([k, -k, 1, ind_coeff])))
        rs = Complex.(rs)
        U[i + 1] = rs[findmin([abs(r.im) for r in rs])[2]].re
    end

    return t,U
end

function bdf_higher_order(f,a::Float64,b::Float64,k::Float64,u::Float64, order::Int64)
    N = round((b - a)/k) |> Int

    t, U = bdf1(f, a, a + (order - 1)*k, k, u)
    t = [t..., zeros(N + 1 - order)...]
    U = [U..., zeros(N + 1 - order)...]

    alphas = bdf_alphas[order]
    betas = bdf_betas[order]
    for i = 1:N-order+1
        t[i+order] = t[i+order-1] + k
        ind_coeff = sum([alphas[j]*U[i + j - 1] for j in 1:order])
        rs = roots(Polynomial(reverse([betas[order + 1]*k, -betas[order + 1]*k, alphas[order + 1], ind_coeff])))
        rs = Complex.(rs)
        U[i + order] = rs[findmin([abs(r.im) for r in rs])[2]].re
    end

    return t,U
end

f(t, u) = u^2 - u^3

step = 15.

plot(fontfamily="computer modern", ylims=(-0.5, 1.5), legend=:topleft, legendfontsize=14)
t, U = rk_fourth_order(f, 0., 2/delta, step, delta)
plot!(t, U, label="Runge-Kutta")
t, U = bdf_higher_order(f, 0., 2/delta, step, delta, 7)
plot!(t, U, label="BDF7")
savefig("../figures/poor_methods.pdf")

plot(fontfamily="computer modern", legend=:topright, legendfontsize=14)
t, U = trapezoidal(f, 0., 2/delta, step, delta)
plot!(t, U, label="Trapezoide")
for i in 3:6
    local t, U = bdf_higher_order(f, 0., 2/delta, step, delta, i)
    plot!(t, U, label="BDF$(i)")
end
xlims!((0.995e4,1.03e4))
ylims!((0.90,1.11))
savefig("../figures/alpha_stables.pdf")

plot(fontfamily="computer modern", ylims=(-0.1, 1.1), legend=:topleft, legendfontsize=14)
t, U = bdf1(f, 0., 2/delta, step, delta)
plot!(t, U, label="BDF1", linewidth=2)
t, U = bdf_higher_order(f, 0., 2/delta, step, delta, 2)
plot!(t, U, label="BDF2", linewidth=2)
savefig("../figures/l_stables.pdf")
