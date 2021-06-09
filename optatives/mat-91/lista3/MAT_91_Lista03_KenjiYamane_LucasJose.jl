# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 3
# Aluno: Kenji Yamane
# Aluno: Lucas Jose
# *********************************************************************
# =====================================================================

using Plots
using Printf

function euler(f,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b - a)/k |> Int
	
	U = zeros(N+1)
	t = zeros(N+1)
	estimate = zeros(N/4 |> Int)
	
	U[1] = u
	t[1] = a
	
	steps = 0
	for i = 1:N
		U[i+1] = U[i] + k*f(t[i],U[i])
		t[i+1] = t[i] + k

		steps = steps + 1
		if steps%4 == 0
			estimate[steps/4 |> Int] = U[i + 1]
		end
	end
	
	return t,U, estimate
end

function enhanced_euler(f,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b - a)/k |> Int
	
	U = zeros(N+1)
	t = zeros(N+1)
	estimate = zeros(N/2 |> Int)
	
	U[1] = u
	t[1] = a
	
	steps = 0
	for i = 1:N
		U[i+1] = U[i] + k*f(t[i] + k/2,U[i] + k/2*f(t[i], U[i]))
		t[i+1] = t[i] + k

		steps = steps + 1
		if steps%2 == 0
			estimate[steps/2 |> Int] = U[i + 1]
		end
	end
	
	return t,U, estimate
end

function fourth_order_rk(f,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b - a)/k |> Int
	
	U = zeros(N+1)
	t = zeros(N+1)
	estimate = zeros(N |> Int)
	
	U[1] = u
	t[1] = a
	
	for i = 1:N
		F0 = f(t[i], U[i])
		F1 = f(t[i] + k/2, U[i] + k/2*F0)
		F2 = f(t[i] + k/2, U[i] + k/2*F1)
		F3 = f(t[i] + k, U[i] + k*F2)

		U[i+1] = U[i] + k/6*(F0 + 2*F1 + 2*F2 + F3)
		t[i+1] = t[i] + k

		estimate[i] = U[i + 1]
	end
	
	return t,U, estimate
end

function best_solver(f,a::Float64,b::Float64,k::Float64,u::Float64)
	N = (b - a)/k |> Int
	
	U = zeros(N+1)
	t = zeros(N+1)
	estimate = zeros(N/100 |> Int)
	
	U[1] = u
	t[1] = a
	
	steps = 0
	for i = 1:N
		F0 = f(t[i], U[i])
		F1 = f(t[i] + k/2, U[i] + k/2*F0)
		F2 = f(t[i] + k/2, U[i] + k/2*F1)
		F3 = f(t[i] + k, U[i] + k*F2)

		U[i+1] = U[i] + k/6*(F0 + 2*F1 + 2*F2 + F3)
		t[i+1] = t[i] + k

		steps = steps + 1
		if steps%100 == 0
			estimate[steps/100 |> Int] = U[i + 1]
		end
	end
	
	return t,U, estimate
end

function runge_kutta_fhlberg(f,a::Float64,b::Float64,u0::Float64,tol::Float64,kmax::Float64,kmin::Float64)
	N = floor((b - a)/kmin) |> Int
	
	U = zeros(N+2)
	t = zeros(N+2)

	
	t[1]=a
	U[1]=u0
	k=kmax
	flag=1
	i=1
	
	while flag==1
		F0=k*f(t[i],U[i])
		F1=k*f(t[i]+k/4,U[i]+F0/4)
		F2=k*f(t[i]+(3*k/8),U[i]+(3*F0/32)+(9*F1/32))
		F3=k*f(t[i]+(12*k/13),U[i]+(1932*F0/2197)-(7200*F1/2197)+(7296*F2/2197))
		F4=k*f(t[i]+k,U[i]+(439*F0/216)-8*F1+(3680*F2/513)-(845*F3/4104))
		F5=k*f(t[i]+k/2,U[i]-(8*F0/27)+2*F1-(3544*F2/2565)+(1859*F3/4104)-(11*F4/40))
		R=abs((F0/360)-(128*F2/4275)-(2197*F3/75240)+(F4/50)+(2*F5/55))/k
		if R<=tol
			t[i+1]=t[i]+k
			U[i+1]=U[i]+(25*F0/216)+(1408*F2/2565)+(2197*F3/4104)-(F4/5)
			#=
			t[i+1]=t[i]
			U[i+1]=U[i]
			=#
			i=i+1
		end
		sigma=0.84*((tol/R)^(1/4))
		if sigma<=0.1
			k=0.1*k
		elseif sigma>=4
			k=4*k
		else
			k=sigma*k
		end

		if k>kmax
			k=kmax
		end

		if t[i]>=b
			flag=0
		end

		if t[i]+k>=b
			k=b-t[i]
		end

		if k<kmin
			flag=-1
		end

	end

	Uf = zeros(i)
	tf = zeros(i)

	for j in 1:i  
		Uf[j]=U[j]
		tf[j]=t[j]
	end

	return tf,Uf
end

f3a(t, u) = u - t^2 + 1

p3a_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="3. (a) aproximacoes")
t, U, est_euler = euler(f3a, 0., 2., 0.025, 0.5)
plot!(t, U, label="euler", linestyle=:dash)

t, U, est_en_euler = enhanced_euler(f3a, 0., 2., 0.05, 0.5)
plot!(t, U, label="euler melhorado", linestyle=:dashdot)

t, U, est_rk4 = fourth_order_rk(f3a, 0., 2., 0.1, 0.5)
plot!(t, U, label="rk 4a ordem", linestyle=:dashdotdot)

p3a_errors = plot(xlabel="t", ylabel="erro global", legend=:topleft, title="3. (a) erros")

t, U, est_best = best_solver(f3a, 0., 2., 0.001, 0.5)
t = LinRange(0.1, 2., 20)
plot!(t, est_best .- est_euler, label="euler", linestyle=:dash)
plot!(t, est_best .- est_en_euler, label="euler melhorado", linestyle=:dashdot)
plot!(t, est_best .- est_rk4, label="rk 4a ordem", linestyle=:dashdotdot)

plot(p3a_approx, p3a_errors)
savefig("ex3a.pdf")
@printf("3a\n")
@printf("confirma-se pela figura que neste caso, runge-kutta\n")
@printf("de quarta ordem possui um desempenho melhor que\n")
@printf("o euler melhorado, o qual por sua vez possui um\n")
@printf("desempenho melhor que o de euler, como esperado\n\n")

f3b(t, u) = u^2 - t^4 + 2t

p3b_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="3. (b) aproximacoes")
t, U, est_euler = euler(f3b, 0., 1., 0.025, 0.)
plot!(t, U, label="euler", linestyle=:dash)

t, U, est_en_euler = enhanced_euler(f3b, 0., 1., 0.05, 0.)
plot!(t, U, label="euler melhorado", linestyle=:dashdot)

t, U, est_rk4 = fourth_order_rk(f3b, 0., 1., 0.1, 0.)
plot!(t, U, label="rk 4a ordem", linestyle=:dashdotdot)

p3b_errors = plot(xlabel="t", ylabel="erro global", legend=:topleft, title="3. (b) erros")

t, U, est_best = best_solver(f3b, 0., 1., 0.001, 0.)
t = LinRange(0.1, 1., 10)
plot!(t, est_best .- est_euler, label="euler", linestyle=:dash)
plot!(t, est_best .- est_en_euler, label="euler melhorado", linestyle=:dashdot)
plot!(t, est_best .- est_rk4, label="rk 4a ordem", linestyle=:dashdotdot)

plot(p3b_approx, p3b_errors)
savefig("ex3b.pdf")
@printf("3b\n")
@printf("confirma-se pela figura que neste caso, runge-kutta\n")
@printf("de quarta ordem possui um desempenho melhor que\n")
@printf("o euler melhorado, o qual por sua vez possui um\n")
@printf("desempenho melhor que o de euler, como esperado\n\n")

f3c(t, u) = -u + t + 2

p3c_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="3. (c) aproximacoes")
t, U, est_euler = euler(f3c, 0., 1., 0.025, 2.)
plot!(t, U, label="euler", linestyle=:dash)

t, U, est_en_euler = enhanced_euler(f3c, 0., 1., 0.05, 2.)
plot!(t, U, label="euler melhorado", linestyle=:dashdot)

t, U, est_rk4 = fourth_order_rk(f3c, 0., 1., 0.1, 2.)
plot!(t, U, label="rk 4a ordem", linestyle=:dashdotdot)

p3c_errors = plot(xlabel="t", ylabel="erro global", legend=:topleft, title="3. (c) erros")

t, U, est_best = best_solver(f3c, 0., 1., 0.001, 2.)
t = LinRange(0.1, 1., 10)
plot!(t, est_best .- est_euler, label="euler", linestyle=:dash)
plot!(t, est_best .- est_en_euler, label="euler melhorado", linestyle=:dashdot)
plot!(t, est_best .- est_rk4, label="rk 4a ordem", linestyle=:dashdotdot)

plot(p3c_approx, p3c_errors)
savefig("ex3c.pdf")
@printf("3c\n")
@printf("confirma-se pela figura que neste caso, runge-kutta\n")
@printf("de quarta ordem possui um desempenho melhor que\n")
@printf("o euler melhorado, o qual por sua vez possui um\n")
@printf("desempenho melhor que o de euler, como esperado\n\n")

f5a(t, u) = (u/t)^2 +(u/t)
h(t) = -t/(log(t)-1) #Resultado analítico

p3a_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (a)")
t, U= runge_kutta_fhlberg(f5a, 1.,1.2,1.,0.0001,0.05,0.02)
plot!(t, U, label="Runge-Kutta-Fehlberg", markershape = :ltriangle, linestyle = :dashdot)
plot!(h,1,1.2,label = "Resultado Analitico")
savefig("ex5a.pdf")

@printf("5a\n")
@printf("Conseguimos perceber que o passo máximo foi escolhido em toda a instância\n\n")

g(t)=2-cos(t)-exp(-t)
f5b(t, u) = sin(t)+exp(-t)

p3a_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (b)")
t, U = runge_kutta_fhlberg(f5b, 0.,1.,0.,0.0001,0.25,0.02)
plot!(t, U, label="Runge-Kutta-Fehlberg", markershape = :ltriangle, linestyle = :dashdot)
plot!(g,0,1,label = "Resultado Analitico")
savefig("ex5b.pdf")
@printf("5b\n")
@printf("Conseguimos perceber que o passo máximo foi escolhido em toda a instância\n\n")

j(t)=(2*t)/(1-2*t)
f5c(t, u) = (u^2+u)/t

p3a_approx = plot(xlabel="t", ylabel="U", legend=:topleft, title="5. (c)")
t, U = runge_kutta_fhlberg(f5c, 1.,3.,-2.,0.0001,0.5,0.02)
plot!(t, U, label="Runge-Kutta-Fehlberg", markershape = :ltriangle, linestyle = :dashdot)
plot!(j,1,3,label = "Resultado Analitico")
savefig("ex5c.pdf")
@printf("5c\n")
@printf("Conseguimos perceber que o passo máximo foi escolhido mais ao fim da malha\n")
@printf("já que no início a derivada é maior e a escolha de um passo maior implicaria\n")
@printf("em maior erro!!\n\n")

