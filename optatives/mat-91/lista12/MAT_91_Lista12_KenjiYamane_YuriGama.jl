# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 11
# Aluno 1: Kenji Yamane
# Aluno 2: Yuri Gama
# *********************************************************************
# =====================================================================

using Plots
using LinearAlgebra
using QuadGK

function colocacao_1(p,q,r,a, b, N, α, β, ϕ)
    h = (b-a)/(N-1)
    A = zeros(N,N)
    x = [a+i*h for i=1:N-2]
    x = [a, x..., b]

    for i=2:N-1
        for j=1:N
            A[i,j] = ϕ[3][j](x[i]) - p(x[i])*ϕ[2][j](x[i]) - q(x[i])*ϕ[1][j](x[i])
        end
    end

    for j=1:N
        A[1,j] = ϕ[1][j](a)
        A[N,j] = ϕ[1][j](b)
    end

    R = r.(x)
    R[1] = α
    R[end] = β
    c = A\R

    return x, c
end

function pseudo_espectral(p, q, r, N::Int64, alpha::Float64, beta::Float64)
	P, Q, D = zeros(Float64, N+1, N+1), zeros(Float64, N+1, N+1), zeros(Float64, N+1, N+1)
	chebyshev = [cos(i*pi/N) for i in 0:N]
	c = ones(N + 1)
	c[1] = c[N + 1] = 2

	for i = 1:N+1, j = 1:N+1
		if i == 1 && j == 1
			D[i, j] = (2N^2+ 1)/6
		elseif i == N + 1 && j == N + 1
			D[i, j] = -(2N^2 + 1)/6
		elseif i == j
			D[i, j] = -chebyshev[j]/(2(1 - chebyshev[j]^2))
			P[i, j] = p(chebyshev[i])
			Q[i, j] = q(chebyshev[i])
		else
			D[i, j] = c[i]/c[j]*(-1)^(i + j)/(chebyshev[i] - chebyshev[j])
		end
	end
	
	D_tilde = D[2:N, :]
	D_hat = D[:, 2:N]
	D_bar = D[2:N, 2:N]
	P_bar = P[2:N, 2:N]
	Q_bar = Q[2:N, 2:N]
	R = [r(chebyshev[i]) for i in 2:N]

	A = D_tilde*D_hat - P_bar*D_bar - Q_bar
	F = R - D_tilde*(beta*D[:,1] + alpha*D[:,N+1]) + P_bar*(beta*D_tilde[:,1] + alpha*D_tilde[:,N+1])

	U = \(A, F)

	return chebyshev, vcat(vcat(beta, U), alpha)
end

function generalized_pe(p, q, r, N::Int64, a::Float64, b::Float64, alpha::Float64, beta::Float64)
	pqry = [fy(y) = (b - a)*y/2 + (b + a)/2 |> f for f in [p, q, r]]

	py(y) = (b - a)*pqry[1](y)/2
	qy(y) = (b - a)^2*pqry[2](y)/4
	ry(y) = (b - a)^2*pqry[3](y)/4
	ty, U = pseudo_espectral(py, qy, ry, N, alpha, beta)

	t = [(b - a)*el/2 + (b + a)/2 for el in ty]
	return t, U
end

function chebyshev_galerkin(p, q, r, N::Int64, alpha::Float64, beta::Float64)
	aux(x) = sqrt(1 - x^2)
	cheb_polys = [f(x) = cos(i*acos(x)) for i in 0:N]
	cheb_polysd = [f(x) = i*sin(i*acos(x))/aux(x) for i in 0:N]
	cheb_polysdd = [f(x) = -(i^2)*cos(i*acos(x))/(aux(x)^2) + i*x*sin(i*acos(x))/(aux(x)^3) for i in 0:N]

	phi = [f(x) = cheb_polys[j + 1](x) - ((j+1)%2)*cheb_polys[1](x) - (j%2)*cheb_polys[2](x) for j in 1:N]
	phid = [f(x) = cheb_polysd[j + 1](x) - ((j+1)%2)*cheb_polysd[1](x) - (j%2)*cheb_polysd[2](x) for j in 1:N]
	phidd = [f(x) = cheb_polysdd[j + 1](x) - ((j+1)%2)*cheb_polysdd[1](x) - (j%2)*cheb_polysdd[2](x) for j in 1:N]

	A = zeros(N, N)
	for i = 1:N, j = 1:N
		if i == 1
			A[i, j] = cheb_polys[j](1)
		elseif i == N
			A[i, j] = cheb_polys[j](0)
		else
			func(x) = (cheb_polysdd[j](x) - p(x)*cheb_polysd[j](x) - q(x)*cheb_polys[j](x))*phi[i](x)/aux(x)
			A[i, j] = quadgk(func, 0, 0.9999999, rtol=1e-3)[1]
		end
	end

	R = zeros(N)
	for i = 1:N
		func(x) = r(x)*phi[i](x)/aux(x)
		R[i] = quadgk(func, 0, 0.9999999, rtol=1e-3)[1]
	end
	R[1] = R[N] = 0

	c = \(A, R)
	approxx(x) = sum([cheb_polys[i](x)*c[i] for i in 1:N])
	return approxx
end

p(x) = 0
q(x) = -400
r(x) = -400*cos(pi*x)^2 - 2*pi^2*cos(2*pi*x)

galerkin = chebyshev_galerkin(p, q, r, 20, 0., 0.)

t, U = generalized_pe(p, q, r, 100, 0., 1., 0., 0.)

# Comparar-se-a a implementacao contra o metodo implementado na semana anterior,
# o metodo pseudo-espectral (cuja corretude ja foi confirmada), para se ter nocao de
# como o algoritmo esta desempenhando quanto ao erro
comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title="5 Galerkin comparacao")
plot!(t, galerkin.(t), label="galerkin")
plot!(t, U, label="analitico")

errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title="5 Galerkin erros")
plot!(t, abs.(U .- galerkin.(t)))

result = plot(comparison_plot, errors_plot)
savefig("ex5_galerkin.pdf")
# Verifica-se pela figura que o metodo de Galerkin obtem desempenho similar ao do metodo pseudo-espectral
# suficientemente para poder dizer que ele de fato funciona neste caso.

N = 100;
aux(x) = sqrt(1 - x^2)
cheb_polys = [f(x) = cos(i*acos(x)) for i in 0:N]
cheb_polysd = [f(x) = i*sin(i*acos(x))/aux(x) for i in 0:N]
cheb_polysdd = [f(x) = -(i^2)*cos(i*acos(x))/(aux(x)^2) + i*x*sin(i*acos(x))/(aux(x)^3) for i in 0:N]
a = 0.
b = 1.
α = 0.
β = 0.
ϕ = [cheb_polys, cheb_polysd, cheb_polysdd]
x, c = colocacao_1(p,q,r,a,b, N, α, β, ϕ)

s(x) = [c[i]*cheb_polys[i](x) for i=1:N]
u(x) = sum(s(x));
plot(x, u.(x), label = "Colocação", title = "Questão 5", dpi = 300)
plot!(t, galerkin.(t), label="galerkin")
plot!(t, U, label="analitico")

savefig("q5-metodos.pdf")
