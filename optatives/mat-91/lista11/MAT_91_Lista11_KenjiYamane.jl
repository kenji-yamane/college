# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 11
# Aluno: Kenji Yamane
# *********************************************************************
# =====================================================================

using Plots
using LinearAlgebra

function lagrangian(x, t, U)
	N = length(U)

	ans = 0
	for k in 1:N
		aux = 1
		for i = 1:N
			if i != k
				aux *= (x - t[i])/(t[k] - t[i])
			end
		end
		ans += U[k]*aux
	end

	return ans
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

function diferencafinita_naolinear(f,fu,fu_linha,h::Float64,a::Float64,b::Float64,ua::Float64,ub::Float64)
	N = Int(round((b-a)/h)) - 1
	w = zeros(N+2)
	x = zeros(N+2)
	A = zeros(N)
	B = zeros(N)
	C = zeros(N)
	D = zeros(N)
	l = zeros(N)
	u = zeros(N)
	z = zeros(N)
	v = zeros(N)

	w[1] = ua
	w[N+2] = ub
    for i = 2:N+1
        w[i] = ua+i*((ub-ua)/(b-a))*h
    end
	for i = 1:N+2
        x[i] = a+(i-1)*h
    end

	for k = 1:10
		t = (w[3] - ua)/(2*h)
		A[1] = 2 + h^2 * fu(x[2],w[2],t)
		B[1] = -1 + (h/2) * fu_linha(x[2],w[2],t)
		D[1] = -(2*w[2] - w[3] - ua + h^2 * f(x[2],w[2],t))

		for i = 2:N-1
			t = (w[i+2]-w[i])/(2*h)
			A[i] = 2 + h^2 * fu(x[i+1],w[i+1],t)
			B[i] = -1 + (h/2) * fu_linha(x[i+1],w[i+1],t)
			C[i] = -1 - (h/2) * fu_linha(x[i+1],w[i+1],t)
			D[i] = -(2*w[i+1] - w[i+2] - w[i] + h^2 * f(x[i+1],w[i+1],t))
		end

		t = (ub - w[N])/(2*h)
		A[N] = 2 + h^2 * fu(x[N+1],w[N+1],t)
		C[N] = -1 - (h/2) * fu_linha(x[N+1],w[N+1],t)
		D[N] = -(2*w[N+1] - w[N] - ub + h^2 * f(x[N+1],w[N+1],t))

		l[1] = A[1]
		u[1] = B[1]/A[1]
		z[1] = D[1]/l[1]

		for i = 2:N-1
			l[i] = A[i] - C[i] * u[i-1]
			u[i] = B[i]/l[i]
			z[i] = (D[i] - C[i] * z[i-1])/l[i]
		end

		l[N] = A[N] - C[N] * u[N-1]
		z[N] = (D[N] - C[N] * z[N-1])/l[N]

		v[N] = z[N]
		w[N+1] = w[N+1] + v[N]

		for i = N-1:-1:1
			v[i] = z[i] - u[i] * v[i+1]
			w[i+1] = w[i+1] + v[i]
		end
	end
	return x,w
end

# Questao 2
p(x) = 0
q(x) = -1
r(x) = x^2 + x
analytic(x) = cos(x)/cos(1) - sin(x)/sin(1) + x^2 + x - 2
t, U = pseudo_espectral(p, q, r, 10, 0., 0.)

comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title="2. comparacao")
scatter!(t, U, label="aproximacao")
plot!(-1:0.01:1, analytic.(-1:0.01:1), label="analitico")

errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title="2. erros")
plot!(t, abs.(analytic.(t) .- U), label="")

spectral_plot = plot(xlabel="x", ylabel="previsao", legend=:topleft, title="2. lagrange")
prediction(x) = lagrangian(x, t, U)
plot!(-1:0.01:1, prediction.(-1:0.01:1), label="")

lagrange_errors_plot = plot(xlabel="x", ylabel="erro", legend=:topleft, title="2. erro na previsao")
plot!(-1:0.01:1, abs.(analytic.(-1:0.01:1) .- prediction.(-1:0.01:1)), label="")

result = plot(comparison_plot, errors_plot, spectral_plot, lagrange_errors_plot)
savefig("ex2.pdf")
# como se pode ver, somente com 10 pontos, o metodo pseudo espectral eh capaz
# de ter erros da ordem de 1e-11, o que eh de fato impressionante. Sem falar
# em como sua previsao nos outros pontos, usando o polinomio de lagrange,
# obteve ordens de grandeza no erro similares.

# Questao 3

# letra a
p(x) = -3
q(x) = 2
r(x) = 2x + 3
t_spec, U_spec = generalized_pe(p, q, r, 10, 0., 1., 2., 1.)

f(x, u, u_linha) = p(x)*u_linha + q(x)*u + r(x)
fu(x, u, u_linha) = q(x)
fu_linha(x, u, u_linha) = p(x)
t_diff, U_diff = diferencafinita_naolinear(f, fu, fu_linha, 0.1, 0., 1., 2., 1.)

# obtido pelo wolfram alpha
analytic(x) = (x - 5exp(-(3 + sqrt(17))*(x - 1)/2) - 5exp(x/2*(sqrt(17) - 3)) + 5exp((sqrt(17)x - 3x+ sqrt(17) + 3)/2) + 5exp(sqrt(17) - x/2*(3 + sqrt(17))) - exp(sqrt(17))*(x + 3) + 3)/(exp(sqrt(17)) - 1)

comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title="3.a comparacao")
scatter!(t_spec, U_spec, label="pseudo espectral")
scatter!(t_diff, U_diff, label="diferencas finitas")
plot!(0:0.001:1, analytic.(0:0.001:1), label="analitico")

errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title="3.a erros")
plot!(t_spec, abs.(analytic.(t_spec) .- U_spec), label="pseudo espectral")
plot!(t_diff, abs.(analytic.(t_diff) .- U_diff), label="diferencas finitas")

result = plot(comparison_plot, errors_plot)
savefig("ex3a.pdf")
# Como se pode ver, o desempenho do algoritmo pseudo espectral eh extremamente melhor que
# o de diferencas finitas

# agora que se provou que o algoritmo pseudo espectral generalizado funciona,
# utilizar-se-a uma versao sua com um numero N de pontos na malha elevado
# como funcao analitica, na b e na c
# letra b
p(x) = -4/x
q(x) = 2/x^2
r(x) = -2/x^2log(x)
t_spec, U_spec = generalized_pe(p, q, r, 20, 1., 2., -0.5, log(2))

f(x, u, u_linha) = p(x)*u_linha + q(x)*u + r(x)
fu(x, u, u_linha) = q(x)
fu_linha(x, u, u_linha) = p(x)
t_diff, U_diff = diferencafinita_naolinear(f, fu, fu_linha, 0.05, 1., 2., -0.5, log(2))

t, U = generalized_pe(p, q, r, 100, 1., 2., -0.5, log(2))
analytic(x) = lagrangian(x, t, U)

comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title="3.b comparacao")
scatter!(t_spec, U_spec, label="pseudo espectral")
scatter!(t_diff, U_diff, label="diferencas finitas")
plot!(1:0.001:2, analytic.(1:0.001:2), label="analitico")

errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title="3.b erros")
plot!(t_spec, abs.(analytic.(t_spec) .- U_spec), label="pseudo espectral")
plot!(t_diff, abs.(analytic.(t_diff) .- U_diff), label="diferencas finitas")

result = plot(comparison_plot, errors_plot)
savefig("ex3b.pdf")
# novamente se confirma como o metodo pseudo espectral possui qualidade superior, mesmo
# com os mesmos pontos que o do metodo de diferencas finitas

# letra c
p(x) = -(x + 1)
q(x) = 2
r(x) = (1 - x^2)*exp(-x)
t_spec, U_spec = generalized_pe(p, q, r, 10, 0., 1., -1., 0.)

f(x, u, u_linha) = p(x)*u_linha + q(x)*u + r(x)
fu(x, u, u_linha) = q(x)
fu_linha(x, u, u_linha) = p(x)
t_diff, U_diff = diferencafinita_naolinear(f, fu, fu_linha, 0.1, 0., 1., -1., 0.)

t, U = generalized_pe(p, q, r, 100, 0., 1., -1., 0.)
analytic(x) = lagrangian(x, t, U)

comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title="3.c comparacao")
scatter!(t_spec, U_spec, label="pseudo espectral")
scatter!(t_diff, U_diff, label="diferencas finitas")
plot!(0:0.001:1, analytic.(0:0.001:1), label="analitico")

errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title="3.c erros")
plot!(t_spec, abs.(analytic.(t_spec) .- U_spec), label="pseudo espectral")
plot!(t_diff, abs.(analytic.(t_diff) .- U_diff), label="diferencas finitas")

result = plot(comparison_plot, errors_plot)
savefig("ex3c.pdf")
# verifica-se que, o desempenho do metodo de diferencas finitas melhora progressivamente,
# porem, ainda esta bem pior quando comparado com o metodo espectral, novamente

# a partir do exposto, pode-se concluir como o metodo pseudo espectral eh de longe
# bem melhor que o metodo de diferencas finitas, como esperado

