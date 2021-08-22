# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 7
# Aluno: Kenji Yamane
# Aluno: Gustavo Asai
# *********************************************************************
# =====================================================================

using Plots
using LinearAlgebra

t = range(0, 2.0*pi, length=1000)

### Questao 1
z = exp.(im*t) .|> (x) -> (x^2-1)/(2x)
plot(z, color=:orange, legend=false, xlim=(-2,2), aspect_ratio=:equal)
plot!(z, fill=(0,:orange,0.2))
savefig("1.pdf")

### Questao 2c
z = exp.(im*t) .|> (x) -> 24(x^4 - x^3)/(55x^3 - 59x^2 + 37x - 9)
plot(z, color=:orange, legend=false, aspect_ratio=:equal)
# Visualizam-se três regiões distintas, a seguir testa-se um ponto de cada uma delas

function adams_bashforth_4(f,a::Float64,b::Float64,k::Float64,u0,u1,u2,u3)
    N = (b-a)/k |> Int

	U = Vector{typeof(u0)}(undef,N+1)
	t = zeros(N+1)

	U[1:4] = [u0, u1, u2, u3]
	t[1:4] = [a, a+k, a+2k, a+3k]

	for i = 1:N-3
		U[i+4] = U[i+3] + k/24 * (55*f(t[i+3],U[i+3]) - 59*f(t[i+2],U[i+2]) + 37*f(t[i+1],U[i+1]) - 9*f(t[i],U[i]))
		t[i+4] = t[i+3] + k
	end

	return t,U
end

# real(z) < 0
z = -0.1
lambda = -2100
f2c(t,u) = lambda*u
k = z/lambda
initials = [1e-3, 1e-3, 1e-3, 1e-3]
t, U = adams_bashforth_4(f2c, 0., 1., k, initials...)
p1 = plot(t,U,legend=false, title="real(z) < 0")
# Erro vai a 0, portanto é região de estabilidade

# real(z) > 0, imaginary(0) > 0
z = 0.2 + 0.75im
lambda = 400 + 1500im
f2c(t, u) = lambda*u
k = z/lambda |> Float64
initials = [1e-3+0im, 1e-3+0im, 1e-3+0im, 1e-3+0im]
t, U = adams_bashforth_4(f2c, 0., 1., k, initials...)
p2 = plot(t,abs.(U),legend=false, title="imaginary(0) > 0")
# Nitidamente, o erro explode neste ponto, portanto esta região não constitui de estabilidade

# real(z) > 0, imaginary(0) < 0
z = 0.2 - 0.75im
lambda = 400 - 1500im
f2c(t, u) = lambda*u
k = z/lambda |> Float64
initials = [1e-3+0im, 1e-3+0im, 1e-3+0im, 1e-3+0im]
t, U = adams_bashforth_4(f2c, 0., 1., k, initials...)
p3 = plot(t,abs.(U),legend=false, title="imaginary(0) < 0")
# Nitidamente, o erro explode neste ponto, portanto esta região não constitui de estabilidade

plot(p1,p2,p3)
savefig("2c_regioes.pdf")

t = range(0, 2.0*pi, length=1000)
z = exp.(im*t) .|> (x) -> 24(x^4 - x^3)/(55x^3 - 59x^2 + 37x - 9)
plot(z, color=:orange, legend=false, aspect_ratio=:equal)
plot!(z[real(z) .< 0], fill=(0,:orange,0.2), linecolor=:transparent)
savefig("2c.pdf")

### Questão 4

### a e b
K1 = 3
K2 = 1
A = [-K1 0 0; K1 -K2 0; 0 K2 0]

lambdas, R = eigen(A)
# lambdas = -3, 1, 0
# Considerando z = -2, temos k = 2/3, 2, infty
# Portanto, o k máximo é de 2/3

function euler(f,a::Float64,b::Float64,k::Float64,u0)
	N = (b-a)/k |> round |> Int
	
	U = Vector{typeof(u0)}(undef,N+1)
	t = zeros(N+1)
	
	U[1] = u0
	t[1] = a
	
	for i = 1:N
		U[i+1] = U[i] + k*f(t[i],U[i])
		t[i+1] = t[i] + k
	end
	
	return t,U
end

f4(t,u) = Diagonal(lambdas)*u

k = 0.6
u_initials = [3, 4, 2]
v_initials = inv(R)*u_initials
t, V = euler(f4, 0., 42., k, v_initials)
U = [R*v for v in V]
A = [u[1] for u in U]
B = [u[2] for u in U]
C = [u[3] for u in U]
plot(t,A,label="A",title="k = 0.6")
plot!(t,B,label="B")
p1 = plot!(t,C,label="C")
# claramente, a solução possui um erro global que, apesar de grande, não explode

k = 0.7
u_initials = [3, 4, 2]
v_initials = inv(R)*u_initials
t, V = euler(f4, 0., 42., k, v_initials)
U = [R*v for v in V]
A = [u[1] for u in U]
B = [u[2] for u in U]
C = [u[3] for u in U]
plot(t,A,label="A",title="k = 0.7")
plot!(t,B,label="B")
p2 = plot!(t,C,label="C")
# claramente, neste caso, a solução possui um erro global que diverge

plot(p1,p2)
savefig("ex4_1.pdf")
# os resultados obtidos reforçam a coerência do valor obtido analiticamente
# para o k através da região de estabilidade absoluta, 0,6 < 2/3 < 0,7

### c

K1 = 300
K2 = 1
A = [-K1 0 0; K1 -K2 0; 0 K2 0]

lambdas, R = eigen(A)
# lambdas = -300, 1, 0
# Considerando z = -2, temos k = 1/150, 2, infty
# Portanto, o k máximo é de 1/150

f4(t,u) = Diagonal(lambdas)*u

k = 0.006
u_initials = [3, 4, 2]
v_initials = inv(R)*u_initials
t, V = euler(f4, 0., 42., k, v_initials)
U = [R*v for v in V]
A = [u[1] for u in U]
B = [u[2] for u in U]
C = [u[3] for u in U]
plot(t,A,label="A",title="k = 0.006")
plot!(t,B,label="B")
p1 = plot!(t,C,label="C")
# claramente, a solução possui um erro global que, apesar de grande, não explode

k = 0.007
u_initials = [3, 4, 2]
v_initials = inv(R)*u_initials
t, V = euler(f4, 0., 42., k, v_initials)
U = [R*v for v in V]
A = [u[1] for u in U]
B = [u[2] for u in U]
C = [u[3] for u in U]
plot(t,A,label="A",title="k = 0.007")
plot!(t,B,label="B")
p2 = plot!(t,C,label="C")
# claramente, neste caso, a solução possui um erro global que diverge

plot(p1,p2)
savefig("ex4_2.pdf")
# os resultados obtidos reforçam a coerência do valor obtido analiticamente
# para o k através da região de estabilidade absoluta, 0,006 < 1/150 < 0,007

### d
# Para o valor de K1 = 300, o passo a partir do qual a solução integrada se torna
# instável é bem menor, forçando os testes a usarem um k menor também. Desta forma,
# a solução fica mais suave, e sem ruído, porém, para o caso de teste com um k
# que provoca instabilidade, verifica-se um crescimento exponencial bem maior
# do erro, decorrente de se utilizar um k bem menor para um mesmo intervalo, o
# que implica em mais passos.
# Além disso, conclui-se a robustez do conceito de região de estabilidade absoluta,
# dado que ele sugeriu valores-limites para o k coerente com os obtidos, seja
# com K1 = 3 ou K1 = 300.