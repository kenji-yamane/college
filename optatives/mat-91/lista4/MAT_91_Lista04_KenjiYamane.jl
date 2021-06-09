# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 4
# Aluno: Kenji Yamane
# *********************************************************************
# =====================================================================

using Plots
using Printf

# =====================================================================
# *********************************************************************
# 				Métodos
# *********************************************************************
# =====================================================================


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

# =====================================================================
#                         Métodos de Adams-Bashforth
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, tempo inicial
# b     real, tempo final
# N     inteiro, número de passos
# u     vetor de reais, condicoes iniciais
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
# =====================================================================

function adamsBashforth(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i = 1:length(u)
		U[i] = u[i]
		t[i] = a + k*(i - 1)
	end

	for i = 1:(N - length(u) + 1)
		if length(u) == 2 # 2 stages
			U[i+2] = U[i+1] + k/2*(3*f(t[i+1], U[i+1]) - f(t[i], U[i]))
			t[i+2] = t[i+1] + k
		elseif length(u) == 3 # 3 stages
			U[i+3] = U[i+2] + k/12*(23*f(t[i+2], U[i+2]) - 16*f(t[i+1], U[i+1]) + 5*f(t[i], U[i]))
			t[i+3] = t[i+2] + k
		elseif length(u) == 4 # 4 stages
			U[i+4] = U[i+3] + k/24*(55*f(t[i+3], U[i+3]) - 59*f(t[i+2], U[i+2]))
			U[i+4] = U[i+4] + k/24*(37*f(t[i+1], U[i+1]) - 9*f(t[i], U[i]))
			t[i+4] = t[i+3] + k
		end
	end

	return t,U
end

# =====================================================================
#                 Métodos de Adams-Moulton para questao 3a
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, tempo inicial
# b     real, tempo final
# N     inteiro, número de passos
# u     vetor de reais, condicoes iniciais
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
# =====================================================================

function adamsMoulton3a(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i = 1:length(u)
		U[i] = u[i]
		t[i] = a + k*(i - 1)
	end

	for i = 1:(N - length(u) + 1)
		if length(u) == 2 # 2 stages
			t[i+2] = t[i+1] + k
			U[i+2] = U[i+1] + 5k/12*t[i+2]*exp(3t[i+2]) + k/12*(8*f(t[i+1], U[i+1]) - f(t[i], U[i]))
			U[i+2] = U[i+2]/(1 + 5k/6)
		elseif length(u) == 3 # 3 stages
			t[i+3] = t[i+2] + k
			U[i+3] = U[i+2] + 9k/24*t[i+3]*exp(3t[i+3]) + k/24*(19*f(t[i+2],U[i+2]))
			U[i+3] = U[i+3] + k/24*(-5*f(t[i+1], U[i+1]) + f(t[i],U[i]))
			U[i+3] = U[i+3]/(1 + 9k/12)
		end
	end

	return t,U
end

# =====================================================================
#                 Métodos de Adams-Moulton para questao 3b
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, tempo inicial
# b     real, tempo final
# N     inteiro, número de passos
# u     vetor de reais, condicoes iniciais
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
# =====================================================================

function adamsMoulton3b(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i = 1:length(u)
		U[i] = u[i]
		t[i] = a + k*(i - 1)
	end

	for i = 1:(N - length(u) + 1)
		if length(u) == 2 # 2 stages
			t[i+2] = t[i+1] + k
			U[i+2] = U[i+1] + 5k/12 + k/12*(8*f(t[i+1], U[i+1]) - f(t[i], U[i]))
			U[i+2] = U[i+2]/(1 - 5k/(12t[i+2]))
		elseif length(u) == 3 # 3 stages
			t[i+3] = t[i+2] + k
			U[i+3] = U[i+2] + 9k/24 + k/24*(19*f(t[i+2],U[i+2]))
			U[i+3] = U[i+3] + k/24*(-5*f(t[i+1], U[i+1]) + f(t[i],U[i]))
			U[i+3] = U[i+3]/(1 - 9k/(24*t[i+3]))
		end
	end

	return t,U
end

# =====================================================================
# =====================================================================
#                 Método de Runge-Kutta de quarta ordem
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, ponto inicial
# b     real, ponto final
# k     real, tamanho do passo
# N     inteiro, número de passos
# u     real, condição inicial
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
function RK_quarta_ordem(f,a::Float64,b::Float64,N::Int64,u::Float64, k::Float64)

U = zeros(N+1)
t = zeros(N+1)

U[1] = u
t[1] = a

for i = 1:3
	F0 = f(t[i], U[i])
	F1 = f(t[i] + 0.5*k, U[i] + 0.5*k*F0)
	F2 = f(t[i] + 0.5*k, U[i] + 0.5*k*F1)
	F3 = f(t[i] + k, U[i] + k*F2)
	U[i+1] = U[i] + (k/6)*(F0 + 2*F1 + 2*F2 + F3)
	t[i+1] = a + k*(i + 1)
end
return t,U
end

# =====================================================================
#                   Método Preditor - Corretor
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
function pred_corr(f,a::Float64,b::Float64,N::Int64,u::Float64)
	U = zeros(N+1)
	t = zeros(N+1)

	k = (b-a)/N

	#for i in 1:3
	t, U = RK_quarta_ordem(f, a, b, N, u, k)

	#initial_U = vetor que contém os valores iniciais para os 3 primeiros valores da funçao

	for i in 4:N
		t[i+1] = t[i] + k
		w = U[i] + k/24 * (55*f(t[i], U[i]) - 59*f(t[i-1], U[i-1]) + 37*f(t[i-2], U[i-2]) - 9*f(t[i-3], U[i-3]))
		U[i+1] = U[i] + k/24 * ( 9*f(t[i+1], w) + 19*f(t[i], U[i]) - 5*f(t[i-1], U[i-1]) + f(t[i-2], U[i-2]))
	end

	return t, U
end
# =====================================================================

# =====================================================================
# =====================================================================
#                 Método de Euler para sistemas
# =====================================================================
# ---------------------------------------------------------------------
function euler_sistemas(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(length(u), N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i in 1:length(u)
		U[i,1] = u[i]
	end
	t[1] = a

		for i = 1:N
			U[:,i+1] = U[:,i] + k*f(t[i],U[:,i])
			t[i+1] = t[i] + k
		end
	return t,U
end

# =====================================================================
# =====================================================================
#       Método de Runge-Kutta de quarta ordem para sistemas
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, ponto inicial
# b     real, ponto final
# k     real, tamanho do passo
# N     inteiro, número de passos
# u     real, condição inicial
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
function RK_4_sistemas(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})

	U = zeros(length(u), N+1)
	t = zeros(N+1)

	k = 1.0
	for i in 1:length(u)
		U[i,1] = u[i]
	end
	t[1] = a

	for i = 1:N
		F0 = f(t[i], U[:,i])
		F1 = f(t[i] .+ 0.5*k, U[:,i] + 0.5*k*F0)
		F2 = f(t[i] .+ 0.5*k, U[:,i] + 0.5*k*F1)
		F3 = f(t[i] .+ k, U[:,i] + k*F2)
		U[:,i+1] = U[:,i] + (k/6)*(F0 + 2*F1 + 2*F2 + F3)
		t[i+1] = a + k*i
	end
	return t,U
end

# =====================================================================
# =====================================================================
#       Método de Runge-Kutta de segunda ordem para sistemas
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, ponto inicial
# b     real, ponto final
# k     real, tamanho do passo
# N     inteiro, número de passos
# u     real, condição inicial
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
function RK_2_sistemas(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})

	U = zeros(length(u), N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i in 1:length(u)
		U[i,1] = u[i]
	end
	t[1] = a

	for i = 1:N
		U[:,i+1] = U[:,i] + 0.5*k*(f(t[i],U[:,i])+ f(t[i]+k,U[:,i]+k*f(t[i],U[:,i])))
		t[i+1] = t[i] + k
	end
	return t,U
end


f(t, U) = [U[2],U[1]+exp(t)]
a = 0.0
b = 0.2
N = 2
u = [1.0; 0.0]

t, U = RK_2_sistemas(f,a,b,N,u)

# =====================================================================
#             Métodos de Adams-Bashforth para sistemas
# =====================================================================
# ---------------------------------------------------------------------
# Dados de entrada:
# a     real, tempo inicial
# b     real, tempo final
# N     inteiro, número de passos
# u     vetor de reais, condicoes iniciais
# f     função lado direito do PVI
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)
# =====================================================================

function adamsBashforth_sistemas(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(length(u), N+1)
	t = zeros(N+1)

	k = (b-a)/N
	for i in 1:length(u)
		U[i,1] = u[i]
		t[i] = a + k*(i - 1)
	end
	t[1] = a

	for i = 1:(N - length(u) + 1)
		if length(u) == 2 # 2 stages
			U[:,i+2] = U[:,i+1] + k/2*(3*f(t[i+1], U[:,i+1]) - f(t[i], U[:,i]))
			t[i+2] = t[i+1] + k
		elseif length(u) == 3 # 3 stages
			U[:,i+3] = U[:,i+2] + k/12*(23*f(t[i+2], U[:,i+2]) - 16*f(t[i+1], U[:,i+1]) + 5*f(t[i], U[:,i]))
			t[i+3] = t[i+2] + k
		elseif length(u) == 4 # 4 stages
			U[:,i+4] = U[:,i+3] + k/24*(55*f(t[i+3], U[:,i+3]) - 59*f(t[i+2], U[:,i+2]))
			U[:,i+4] = U[:,i+4] + k/24*(37*f(t[i+1], U[:,i+1]) - 9*f(t[i], U[:,i]))
			t[i+4] = t[i+3] + k
		end
	end

	return t,U
end


# =====================================================================
#            Método Preditor - Corretor para sistemas
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
function pred_corr_sistemas(f,a::Float64,b::Float64,N::Int64,u::Vector{Float64})
	U = zeros(length(u), N+1)
	t = zeros(N+1)

	t, U = RK_4_sistemas(f, a, b, 3, u, k)



	for i in 4:N
		t[i+1] = t[i] + k
		w = U[:,i] + k/24 * [55*f(t[i], U[:,i]) - 59*f(t[i-1], U[:,i-1]) + 37*f(t[i-2], U[:,i-2]) - 9*f(t[i-3], U[:,i-3])]
		U[:,i+1] = U[:,i] + k/24 * [ 9*f(t[i+1], w) + 19*f(t[i], U[:,i]) - 5*f(t[i-1], U[:,i-1]) + f(t[i-2], U[:,i-2])]
	end

	return t, U
end
# *********************************************************************
# 				Exercícios
# *********************************************************************
# =====================================================================
# =====================================================================
# Exercício 1

f1a(t, u) = t*exp(3t) - 2u
analytic1a(t) = exp(3t)*(5t - 1)/25 + exp(-2t)/25

p1a = plot(xlabel="t", ylabel="U", legend=:topleft, title="1. (a) Aproximacao")
p1a_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="1. (a) Erros")
for i=2:4
	initialConditions = Vector{Float64}()
	for j=1:i
		push!(initialConditions, analytic1a(0 + 0.2*(j - 1)))
	end

	t, U = adamsBashforth(f1a, 0., 1., 5, initialConditions)
	plot!(p1a, t, U, label="adams bashforth $i", linestyle=:dot)
	plot!(p1a_errors, t, abs.(U - analytic1a.(0:0.2:1)), label="adams bashforth $i", linestyle=:dot)
end
plot!(p1a, 0:0.2:1, analytic1a.(0:0.2:1), label="analitica")
plot(p1a, p1a_errors)
#savefig("ex1a.pdf")

# =====================================================================
f1b(t, u) = exp(t - u)
analytic1b(t) = log(exp(t) + exp(1) - 1)

p1b = plot(xlabel="t", ylabel="U", legend=:topleft, title="1. (b) Aproximacao")
p1b_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="1. (b) Erros")
for i=2:4
	initialConditions = Vector{Float64}()
	for j=1:i
		push!(initialConditions, analytic1b(0 + 0.2*(j - 1)))
	end

	t, U = adamsBashforth(f1b, 0., 1., 5, initialConditions)
	plot!(p1b, t, U, label="adams bashforth $i", linestyle=:dot)
	plot!(p1b_errors, t, abs.(U - analytic1b.(0:0.2:1)), label="adams bashforth $i", linestyle=:dot)
end
plot!(p1b, 0:0.2:1, analytic1b.(0:0.2:1), label="analitica")
plot(p1b, p1b_errors)
#savefig("ex1b.pdf")
# =====================================================================
f1c(t, u) = t^(-2)*(sin(2t) - 2t*u)
analytic1c(t) = -cos(2t)/(2t^2) - (2 + cos(2)/2)/(t^2)

p1c = plot(xlabel="t", ylabel="U", legend=:topleft, title="1. (c) Aproximacao")
p1c_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="1. (c) Erros")
for i=2:4
	initialConditions = Vector{Float64}()
	for j=1:i
		push!(initialConditions, analytic1c(1 + 0.2*(j - 1)))
	end

	t, U = adamsBashforth(f1c, 1., 2., 5, initialConditions)
	plot!(p1c, t, U, label="adams bashforth $i", linestyle=:dot)
	plot!(p1c_errors, t, abs.(U - analytic1c.(1:0.2:2)), label="adams bashforth $i", linestyle=:dot)
end
plot!(p1c, 1:0.2:2, analytic1c.(1:0.2:2), label="analitica")
plot(p1c, p1c_errors)
#savefig("ex1c.pdf")

# Percebe-se que no geral, as estimativas do metodo de adams-bashforth de 4 estagios
# eh melhor que a de 3 estagios, a qual por sua vez eh melhor que a de 2 estagios.
# Isso era de se esperar, com mais informacoes de como eh a funcao de fato, o polinomio
# de interpolacao fica mais coerente e parecido com a funcao em si. Uma unica irregularidade
# foi encontrada no quesito b, ela pode ser explicada dado que em alguns casos bem
# especificos, a de 2 estagios pode ter vantagem, uma funcao que eh linear durante
# dois passos somente, por exemplo.

# =====================================================================
# Exercício 3

f3a(t, u) = t*exp(3t) - 2u
analytic3a(t) = exp(3t)*(5t - 1)/25 + exp(-2t)/25

p3a = plot(xlabel="t", ylabel="Erros", legend=:topleft, title="3. (a)")
p3a = plot(xlabel="t", ylabel="U", legend=:topleft, title="3. (a) Aproximacao")
p3a_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="3. (a) Erros")
for i=2:3
	initialConditions = Vector{Float64}()
	for j=1:i
		push!(initialConditions, analytic3a(0 + 0.2*(j - 1)))
	end

	t, U = adamsMoulton3a(f3a, 0., 1., 5, initialConditions)
	plot!(p3a, t, U, label="adams moulton $i", linestyle=:dot)
	plot!(p3a_errors, t, abs.(U - analytic3a.(0:0.2:1)), label="adams moulton $i", linestyle=:dot)
end
plot!(p3a, 0:0.2:1, analytic1a.(0:0.2:1), label="analitica")
plot(p3a, p3a_errors)
#savefig("ex3a.pdf")
# =====================================================================
f3b(t, u) = 1 + u/t
analytic3b(t) = t*log(t) + 2t

p3b = plot(xlabel="t", ylabel="Erros", legend=:topleft, title="3. (b)")
p3b = plot(xlabel="t", ylabel="U", legend=:topleft, title="3. (b) Aproximacao")
p3b_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="3. (b) Erros")
for i=2:3
	initialConditions = Vector{Float64}()
	for j=1:i
		push!(initialConditions, analytic3b(1 + 0.2*(j - 1)))
	end

	t, U = adamsMoulton3b(f3b, 1., 2., 5, initialConditions)
	plot!(p3b, t, U, label="adams moulton $i", linestyle=:dot)
	plot!(p3b_errors, t, abs.(U - analytic3b.(1:0.2:2)), label="adams moulton $i", linestyle=:dot)
end
plot!(p3b, 1:0.2:2, analytic3b.(1:0.2:2), label="analitica")
plot(p3b, p3b_errors)
savefig("ex3b.pdf")


# Novamente, se verifica que quanto mais estagios, melhor eh a aproximacao,
# o que eh previsto pela mesma razao explicada no caso do adams bashfort.
# Vale notar que na 3a, o metodo implicito obteve um resultado bem melhor
# quando comparado com o metodo explicito aplicado em 3b.
# Novamente, eh natural, dado que o metodo implicito considera um ponto
# a mais na interpolacao


# =====================================================================
# Exercício 5

f5a(t, u) = (u/t)^2 + u/t
analytic5a(t) = 1/(1 - log(10,t))

p5a = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (a) Aproximacao")
p5a_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="5. (a) Erros")
t, U = pred_corr(f5a, 1.0, 1.2, 5, 1.0)
plot!(p5a, t, U, label="preditor-corretor", linestyle=:dot)
plot!(p5a_errors, t, abs.(U - analytic5a.(1:0.04:1.2)), label="preditor-corretor", linestyle=:dot)
plot!(p5a, 1:0.04:1.2, analytic5a.(1:0.04:1.2), label="analitica")
plot(p5a, p5a_errors)
savefig("ex5a.pdf")

# =====================================================================

f5b(t, u) = sin(t) + exp(-t)
analytic5b(t) = 2 - exp(-t) - cos(t)

p5b = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (b) Aproximacao")
p5b_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="5. (b) Erros")
t, U = pred_corr(f5b, 0., 1., 5, 0.)
plot!(p5b, t, U, label="preditor-corretor", linestyle=:dot)
plot!(p5b_errors, t, abs.(U - analytic5b.(0:0.2:1)), label="preditor-corretor", linestyle=:dot)
plot!(p5b, 0:0.2:1, analytic5b.(0:0.2:1), label="analitica")
plot(p5b, p5b_errors)
savefig("ex5b.pdf")


# =====================================================================

f5c(t, u) = (u^2+ u)/t
analytic5c(t) = 2*t /(1 - 2*t)

p5c = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (c) Aproximacao")
p5c_errors = plot(xlabel="t", ylabel="Erro", legend=:topleft, title="5. (c) Erros")
t, U = pred_corr(f5c, 1., 3., 5, -2.)
plot!(p5c, t, U, label="preditor-corretor", linestyle=:dot)
plot!(p5c_errors, t, abs.(U - analytic5c.(1:0.4:3)), label="preditor-corretor", linestyle=:dot)
plot!(p5c, 1:0.4:3, analytic5c.(1:0.4:3), label="analitica")
plot(p5c, p5c_errors)
savefig("ex5c.pdf")



