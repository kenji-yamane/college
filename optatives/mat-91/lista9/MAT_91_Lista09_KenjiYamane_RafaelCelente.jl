# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 9
# Aluno: Rafael Celente
# Aluno: Kenji Yamane
# *********************************************************************
# =====================================================================

using Plots
using Printf



# =====================================================================
#                   Método das Diferenças Finitas
# =====================================================================
#  Método baseado no capítulo 11.3 de Numerical Methods, FAIRE, J.
# e BURDEN, R, a partir da pág. 533
#---------------------------------------------------------------------
# Dados de entrada:
# x0             real, tempo inicial
# xf             real, tempo final
# h              real, passo
# ua, ub         real, condições de contorno de Dirichlet
# p, q, r     funções da EDO a ser resolvida: u'' = p(x)u' + q(x)u + r(x)
# ---------------------------------------------------------------------
# Saída:
# U     solução aproximada

function mdf(p, q, r, ui::Float64, uf::Float64, x0::Float64, xf::Float64, h::Float64)
    # Número de passos
    N = round((xf-x0)/h) |> Int
    N = N - 1

    # Incialização de espaços
    x = zeros(N)
    U = zeros(N)
    A = zeros(N, N)
    F = zeros(N)

    # Criação do vetor de intervalos
    for i = 1:N
        x[i] = x0 + i*h
    end

    ## Criação da matriz A
    # Inicialização dos valores de borda
    A[1,1] = 2 + q(x[1])*h^2
    A[1,2] = -1 + h*p(x[1])/2
    A[N,N-1] = -1 - h*p(x[N])/2
    A[N,N] = 2 + q(x[N])*h^2
    # Preenchimentos dos valores centrais
    for i = 2:(N-1)
        A[i, i-1] = -1 - h*p(x[i])/2
        A[i, i] = 2 + q(x[i])*h^2
        A[i, i+1] = -1 + h*p(x[i])/2
    end

    # Criação do vetor F
    F[1] = -r(x[1])*h^2 + (1 + h*p(x[1])/2)*ui
    F[N] = -r(x[N])*h^2 + (1 - h*p(x[N])/2)*uf
    for i = 2:(N-1)
        F[i] = -r(x[i])*h^2
    end

    # Resolução do sistema linear AU = F
    U = A\F

    return x, U
end

# Função para fazer o append dos valores de contorno nos vetores
# v = vetor interno, resultado do método das diferenças finitas
# vi = condição de contorno inicial
# vf =  condição de contorno final
function vec_append(v, vi, vf)
    vret = zeros(0)
    append!(vret, vi)
    append!(vret, v)
    append!(vret, vf)

    return vret
end



# =====================================================================
# *********************************************************************
# 				Exercícios
# *********************************************************************
# =====================================================================

# u'' = p(x)u' + q(x)u + r(x)

# =====================================================================
# Exercício 4a
# u'' = -u
p(t) = 0.
q(t) = -1.
r(t) = 0.
x0 = 0.
xf = pi/4
ui = 1.
uf = 1.
h = pi/20

x, U = mdf(p,q,r, ui, uf, x0, xf, h)
U4a = vec_append(U, ui, uf)

xspan = vec_append(x, x0, xf)

sol(t) = cos(t) + (sqrt(2) - 1)*sin(t)
U_analytic4a = vec_append(sol.(x), ui, uf)

plot(xspan, U4a, legend = :topright, style = :dash, label="Diferenças finitas", title = "Exercicio 4a")
plot!(xspan, U_analytic4a, label="Analítica")

#savefig("ex4a.pdf")
#########################################################################

# =====================================================================
# =====================================================================
# Exercício 4b
# u'' = -4u + cos(x)
p(t) = 0.
q(t) = -4.
r(t) = cos(t)
x0 = 0.
xf = pi/4
ui = 0.
uf = 0.
h = pi/20

x, U = mdf(p,q,r, ui, uf, x0, xf, h)
U4b = vec_append(U, ui, uf)

xspan = vec_append(x, x0, xf)

sol(t) = -cos(2*t)/3 - sqrt(2)*sin(2*t)/6 + cos(t)/3
U_analytic4b = vec_append(sol.(x), ui, uf)

plot(xspan, U4b, legend = :topright, style = :dash, label="Diferenças finitas", title = "Exercicio 4b")
plot!(xspan, U_analytic4b, label="Analítica")

#savefig("ex4b.pdf")
#########################################################################

# =====================================================================
# Exercício 4c
# u'' = 2u' + - u + xexp(x)-x
p(t) = 2.
q(t) = -1.
r(t) = t*exp(t)-t
x0 = 0.
xf = 2.
ui = 0.
uf = -4.
h = 0.2

x, U = mdf(p,q,r, ui, uf, x0, xf, h)
U4c = vec_append(U, ui, uf)

xspan = vec_append(x, x0, xf)

sol(t) = (t^3)*exp(t)/6 - 5*t*exp(t)/3 + 2*exp(t) - t - 2
U_analytic4c = vec_append(sol.(x), ui, uf)

plot(xspan, U4c, legend = :topright, style = :dash, label="Diferenças finitas", title = "Exercicio 4c")
plot!(xspan, U_analytic4c, label="Analítica")

#savefig("ex4c.pdf")
#########################################################################
