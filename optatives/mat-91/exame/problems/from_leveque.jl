using Plots

include("../bdf_utils.jl")

lambda = -1e6

function rk_fourth_order(f,a::Float64,b::Float64,k::Float64,u::Float64)
    N = (b - a)/k |> Int

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
    N = (b - a)/k |> Int

    U = zeros(N+1)
    t = zeros(N+1)

    U[1] = u
    t[1] = a

    for i = 1:N
        t[i+1] = t[i] + k
        U[i+1] = (U[i] + k*f(t[i], U[i])/2 - k*lambda*cos(t[i + 1])/2 - k*sin(t[i + 1])/2)/(1 - lambda*k/2)
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
        U[i + 1] = (U[i] - k*lambda*cos(t[i + 1]) - k*sin(t[i + 1]))/(1 - lambda*k)
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
        U[i + order] += betas[order + 1]*k*(lambda*cos(t[i + order]) + sin(t[i + order]))
        U[i + order] += sum([alphas[j]*U[i + j - 1] for j in 1:order])
        U[i + order] /= betas[order + 1]*k*lambda - alphas[order + 1]
    end

    return t,U
end

Plots.scalefontsizes()
Plots.scalefontsizes(1.6)

f(t, u) = lambda*(u - cos(t)) - sin(t)
analytic(t) = 0.5exp(-t*1e6) + cos(t)

plot(fontfamily="computer modern", ylims=(-1.5, 3))
t, U = rk_fourth_order(f, 0., 3., 0.01, 1.5)
plot!(t, U, label="runge kutta", linestyle=:dashdot)
plot!(t, analytic.(t), label="analitica")
t, U = trapezoidal(f, 0., 3., 0.01, 1.5)
plot!(t, U, label="trapezoidal", linestyle=:dot)
# t, U = bdf_higher_order(f, 0., 3., 0.0001, 1.5, 7)
# plot!(t, U, label="bdf7", linestyle=:dashdotdot)
savefig("../figures/poor_methods.pdf")

plot(fontfamily="computer modern", ylims=(-1, 1.5))
plot!(t, analytic.(t), label="analitica")
t, U = bdf1(f, 0., 3., 0.01, 1.5)
plot!(t, U, label="bdf1", linestyle=:dashdot)
for i in 2:6
    local t, U = bdf_higher_order(f, 0., 3., 0.01, 1.5, i)
    plot!(t, U, label="bdf$(i)", linestyle=:dashdot)
end
savefig("../figures/bdf_methods.pdf")

plot(fontfamily="computer modern", xlims=(0, 1e-11))
t, U = bdf1(f, 0., 1e-11, 1e-15, 1.5)
plot!(t, abs.(U .- analytic.(t)), label="bdf1", linestyle=:dashdot)
for i in 2:7
    local t, U = bdf_higher_order(f, 0., 1e-11, 1e-15, 1.5, i)
    plot!(t, abs.(U .- analytic.(t)), label="bdf$(i)")
end
savefig("../figures/bdf_methods_errors.pdf")
