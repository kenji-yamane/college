# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 2
# Aluno: Gustavo Asai
# Aluno: Kenji Yamane
# *********************************************************************
# =====================================================================

using Plots
using Printf

# =====================================================================
#                         Método de Euler
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, tempo inicial
# b     real, tempo final
# N     inteiro, número de passos
# u     real, condição inicial
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)

function euler(f,a::Float64,b::Float64,N::Int64,u::Float64)
#Digite seu código aqui

U = zeros(N+1)
t = zeros(N+1)

k = (b-a)/N
U[1] = u
t[1] = a

for i = 1:N
	U[i+1] = U[i] + k*f(t[i],U[i])
	t[i+1] = t[i] + k
end

return t,U
end

function taylor(f,fprime,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b-a)/k |> Int

	U = zeros(N+1)
	t = zeros(N+1)
	
	U[1] = u
	t[1] = a
	
	for i = 1:N
		U[i+1] = U[i] + k*(f(t[i],U[i]) + k/2*fprime(t[i],U[i]))
		t[i+1] = t[i] + k
	end

	return t, U
end

function heun(f,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b-a)/k |> Int
	
	U = zeros(N+1)
	t = zeros(N+1)
	
	U[1] = u
	t[1] = a
	
	for i = 1:N
		U[i+1] = U[i] + k/2*(f(t[i], U[i]) + f(t[i] + k, U[i] + k*f(t[i], U[i])))
		t[i+1] = t[i] + k
	end
	
	return t,U
end

# =====================================================================
# Exercício 2
#Digite aqui os dados do seu PVI
f2a(t,u) = u^2 - t^4 + 2t
p2a = plot(xlabel="t", ylabel="U",legend=:topleft, title="2. (a)")
for N in [10, 20, 40, 80]
	t, U = euler(f2a, 0., 1., N, 0.)
	plot!(t,U,label="N = $N")
end

f2b(t,u) = -u + t + 2
p2b = plot(xlabel="t", ylabel="U",legend=:topleft, title="2. (b)")
for N in [10, 20, 40, 80]
	t, U = euler(f2b, 0., 1., N, 2.)
	plot!(t,U,label="N = $N")
end

plot(p2a,p2b)
savefig("ex2.pdf")
# Verifica-se uma convergência conforme N aumenta

# =====================================================================
# Exercício 4
#Digite aqui os dados do seu PVI

f4a(t,u) = t*exp(3t) - 2u
f4aprime(t,u) = exp(3t) + 3t*exp(3t) - 2*f4a(t,u)

p4a = plot(xlabel="t", ylabel="U",legend=:topleft, title="4. (a)")
for k in [0.5, 0.001]
	t, U = taylor(f4a, f4aprime, 0., 1., k, 0.)
	plot!(t,U,label="k = $k")
end

f4b(t, u) = exp(t - u)
f4bprime(t, u) = exp(t - u) - exp(2(t - u))
p4b = plot(xlabel="t", ylabel="U",legend=:topleft, title="4. (b)")
for k in [0.5, 0.001]
	t, U = taylor(f4b, f4bprime, 0., 1., k, 1.)
	plot!(t,U,label="k = $k")
end

f4c(t, u) = (sin(2t) - 2t*u)/t^2
f4cprime(t, u) = (2cos(2t) - 2u)/t^2 - (2sin(2t) - 4t*u)/t^3 - 2*f4c(t, u)/t
p4c = plot(xlabel="t", ylabel="U", title="4. (c)")
for k in [0.25, 0.001]
	t, U = taylor(f4c, f4cprime, 1., 2., k, 2.)
	plot!(t,U,label="k = $k")
end

plot(p4a,p4b,p4c)
savefig("ex4.pdf")
# Assumindo que a solução "verdadeira" seja com k muito pequeno, a aproximação da equação 4a teve o pior
# desempenho, pois a derivada da solução varia muito mais rapidamente que o k utilizado consegue captar.
# Nas outras, em que a derivada varia mais suavemente, o resultado foi mais satisfatório.

# =====================================================================
# Exercício 6
#Digite aqui os dados do seu PVI

f6(t,u) = -u

p6 = []
for k in [1/4, 1/8, 1/16]
	p = plot(xlabel="t", ylabel="U", title="k = $k")

	t_analitico = collect(0:0.01:1)
	U_analitico = exp.(-t_analitico)
	plot!(t_analitico, U_analitico, label="Analítico")

	t_heun, U_heun = heun(f6, 0., 1., k, 1.)
	plot!(t_heun, U_heun, label="Heun")

	t_euler, U_euler = euler(f6, 0., 1., Int(1/k), 1.)
	plot!(t_euler, U_euler, label="Euler")

	push!(p6, p)
end

plot(p6...)
savefig("ex6.pdf")
# Percebe-se que a curva da solução por Heun se aproxima mais da solução analítica que a curva da solução por Euler