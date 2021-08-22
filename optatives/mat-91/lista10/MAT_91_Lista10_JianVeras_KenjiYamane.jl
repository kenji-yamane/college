# ===============================================================================
# *******************************************************************************
#                               MAT-91 2021 - Lista 9
# Alunos: Kenji Yamane e Jian Veras
# *******************************************************************************
# ===============================================================================

using Plots
using Printf
using LaTeXStrings
using TypedTables

# ===============================================================================
# *******************************************************************************
#                                     Métodos
# *******************************************************************************
# ===============================================================================

# ===============================================================================
#                            Metodo de Runge Kutta quarta ordem
# ===============================================================================
# -------------------------------------------------------------------------------
# Dados de entrada:
# f     	função vetorial que descreve uma EDO de ordem qualquer
# a    	 	real, tempo inicial
# b     	real, tempo final
# k     	real, tamanho do passo
# u     	real, condicoes iniciais
# -------------------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)

function fourth_order_rk(f, a::Float64, b::Float64, k::Float64, u::Array{Float64})
	N = (b - a)/k |> Int
	
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
	
	return t,U
end

# ===============================================================================
#                            Método de Shooting Linear
# ===============================================================================
# -------------------------------------------------------------------------------
# Dados de entrada:
# fu    	funcao vetorial que representa a edo completa
# fv        funcao vetorial que representa a edo homogenea
# a    	 	real, tempo inicial
# b     	real, tempo final
# k     	real, tamanho do passo
# alpha    	real, condição de contorno u(a)
# beta    	real, condição de contorno u(b)
# -------------------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)

function linear_shooting(fu, fv, a::Float64, b::Float64, k::Float64, alpha::Float64, beta::Float64)
	initials_first = [alpha, 0.]
	t_first, U_first = fourth_order_rk(fu, a, b, k, initials_first)

	initials_second = [0., 1.]
	t_second, U_second = fourth_order_rk(fv, a, b, k, initials_second)

	U = U_first + ((beta - last(U_first)[1])/last(U_second)[1]).*U_second

	return t_first, [U[i][1] for i in 1:length(U)]
end

# ===============================================================================
#                            Método de Diferenças Finitas
# ===============================================================================
# -------------------------------------------------------------------------------
# Dados de entrada:
# f     	função que descreve u'' --> u'' = f(x,u,u_linha)
# fu    	derivada da função f em u
# fu_linha  derivada da função f em u'
# a    	 	real, tempo inicial
# b     	real, tempo final
# h     	real, tamanho do passo
# ua    	real, condição de contorno u(a)
# ub    	real, condição de contorno u(b)
# -------------------------------------------------------------------------------
# Saída:
# U     solução aproximada de u' = f(t,u)

function diferencafinita_naolinear(f,fu,fu_linha,a::Float64,b::Float64,h::Float64,ua::Float64,ub::Float64)
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

# ===============================================================================
# *******************************************************************************
#                                    Exercícios
# *******************************************************************************
# ===============================================================================

# ===============================================================================

# Exercicio 2
function plot_comparison_and_errors(analytic, x::Array{Float64}, U::Array{Float64}, str::String)
	analytic_U = analytic.(x)
	comparison_plot = plot(xlabel="x", ylabel="U", legend=:topleft, title=str*" comparacao")
	plot!(x, U, linestyle=:dash, label="aproximacao")
	plot!(x, analytic_U, linestyle=:dashdot, label="analitico")

	errors_plot = plot(xlabel="x", ylabel="erro global", legend=:topleft, title=str*" erros")
	plot!(x, abs.(analytic_U .- U), label="")

	result = plot(comparison_plot, errors_plot)
	display(result)
end

# 2a
f(t, U) = [U[2], -U[1]]
analytic(t) = cos(t) + (sqrt(2) - 1)*sin(t)
t, U = linear_shooting(f, f, 0., pi/4, pi/20, 1., 1.)
plot_comparison_and_errors(analytic, t, U, "2.a")
display("desempenho de elevada qualidade com relacao a precisao, do metodo de shooting")
display("com erros da ordem de 1e-7")

# 2b
fu(t, U) = [U[2], -4U[1] + cos(t)]
fv(t, U) = [U[2], -4U[1]]
analytic(t) = -cos(2t)/3 - sqrt(2)*sin(2*t)/6 + cos(t)/3
t, U = linear_shooting(fu, fv, 0., pi/4, pi/20, 0., 0.)
plot_comparison_and_errors(analytic, t, U, "2.b")
display("aqui se observam erros da ordem de 1e-5, um pouco maior que a da questao 2a,")
display("porem ainda assim um desempenho muito bom. O aumento do erro global em relacao")
display("a a) pode ser justificado pelo fato da funcao da a) ser homogenea originalmente")

# 2c
fu(t, U) = [U[2], 2*U[2] - U[1] + t*exp(t) - t]
fv(t, U) = [U[2], 2*U[2] - U[1]]
analytic(t) = exp(t)*t^3/6 - 5t*exp(t)/3 + 2*exp(t) - t - 2
t, U = linear_shooting(fu, fv, 0., 2., 0.2, 0., -4.)
plot_comparison_and_errors(analytic, t, U, "2.c")
display("outra vez, um erro um pouco maior, de 1e-4, provavelmente em virtude da maior nao")
display("linearidade da funcao, porem ainda assim um desempenho muito bom")

display("o metodo de shooting linear provou ser extremamente eficaz em termos de precisao,")
display("sendo que ele tambem nao eh pesado. Ademais, nem houve a necessidade")
display("de se trocar as condicoes iniciais das funcoes u, e v, bastando as recomendadas")

# Exercício 4

# item (a)
f(x,u,u_linha) = -u + 2(u_linha)^2/u
fu(x,u,u_linha) = -1-2*(u_linha)^2/u^2
fu_linha(x,u,u_linha) = 4*u_linha/u
a = -1.0
b = 1.0
ua = (exp(1)+exp(-1))^(-1)
ub = ua
h = 0.2
sol(x) = (exp(x) + exp(-x))^(-1)

x,U = diferencafinita_naolinear(f,fu,fu_linha,a,b,h,ua,ub)

plot(sol, a, b,label="Método Analítico", linewidth=2, legend=:bottom)
graf = plot!(x, U,label="Passo h = $h", seriestype =:scatter,
	linewidth=2, title="Questão 4, item a")
display(graf)

sol_values = zeros(size(x,1))
for i = 1:size(x,1)
	sol_values[i] = sol(x[i])
end

dif = []
push!(dif,maximum(abs,sol_values - U))

# item (b)

for i = 1:5
	hnew = 0.2/2^i
	xn,Un = diferencafinita_naolinear(f,fu,fu_linha,a,b,hnew,ua,ub)

	sol_valuesnew = zeros(size(xn,1))
	for i = 1:size(xn,1)
		sol_valuesnew[i] = sol(xn[i])
	end
	push!(dif,maximum(abs,sol_valuesnew - Un))
end

razao = [0.0]

for i = 1:5
	push!(razao,dif[i+1]/dif[1])
end
H = [0.2,0.2/2,0.2/4,0.2/8,0.2/16,0.2/32]
result = Table(h = H,
			   Diferenca_Maxima = dif,
				Razao_Sucessores = razao)

display(result)
display("Fica evidente que a ordem de convergência é dada por h^2,\n")
display("uma vez que os erros sucessores variam proprocionalmente ao quadrado\n")
display("da razão entre os respectivos passos.\n")
