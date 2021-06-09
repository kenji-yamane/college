using Plots

function q4(f ,a::Float64, b::Float64, k::Float64, U1::Float64)
    N = (b-a)/k |> Int

    U = zeros(N+1)
    t = zeros(N+1)

    U[1] = U1
    U[2] = 4*U1
    t[1] = a
    t[2] = a + k
    for i = 2:N
        U[i+1] = 4U[i] - 3U[i-1] + f(t[i-1],U[i-1])
        t[i+1] = t[i] + k
    end

    return t, U
end

f(t, u) = 1 - u
sol(t) = 1 - exp(-t)
a = 0.
b = 1.
u0 = 0.
u1 = 1 - exp(-.1)
k = 0.1
t1, U1 = q4(f, a, b, k, u1)

p1 = plot(xlabel="t", ylabel="u", t1, sol.(t1), label = "u(t) = 1 - exp(-t)", title="4b")
p1 = plot!(t1, U1, seriestype = :scatter, label = "q4b");

u1 = 1 - exp(-0.01)
k = 0.01
t2, U2 = q4(f, a, b, k, u1)

p2 = plot(xlabel="t", ylabel="u", t2, sol.(t2), label = "u(t) = 1 - exp(-t)", title="4c")
p2 = plot!(t2, U2, seriestype = :scatter, label = "q4c");

savefig(p1, "4b.png")
savefig(p2, "4c.png")
