# =====================================================================
# *********************************************************************
#              MAT-91 2021 - Lista 13
# Aluno: Gustavo Asai
# Aluno: Kenji Yamane
# *********************************************************************
# =====================================================================

using Plots

function colocacao_bspline(p, q, r, x, α, β)
	N = length(x)
    h = x[2] - x[1]

	A = [
		begin
			if j == i # a
				3/2h^2 + 3/4h*p(x[i]) - 1/4*q(x[i])
			elseif j == i+1 # b
				-3/h^2 - q(x[i])
			elseif j == i+2 # d
				3/2h^2 - 3/4h*p(x[i]) - 1/4*q(x[i])
			else
				0
			end
		end for i in 1:N, j in 1:N+2
	]
    first_row = [1/4, 1, 1/4, zeros(N-1)...]
    last_row = [zeros(N-1)..., 1/4, 1, 1/4]
	A = [first_row'; A; last_row']

	R = [r(x[i]) for i in 1:N]
	R = [α, R..., β]

	c = A\R

    # criacao das splines cubicas B_{-1} a B_{N+1}
    B = [
		b -> begin
			if i > 2 && i < N + 2 && b >= x[i - 2] && b <= x[i - 1]
				1/4h^3*(b - x[i - 2])^3
			elseif i > 1 && i < N + 1 && b >= x[i - 1] && b <= x[i]
                aux = (b - x[i - 1])/h
            	1/4 + 3/4*aux + 3/4*aux^2 - 3/4*aux^3
            elseif i > 0 && i < N && b >= x[i] && b <= x[i + 1]
                aux = (x[i + 1] - b)/h
            	1/4 + 3/4*aux + 3/4*aux^2 - 3/4*aux^3
			elseif i < N - 1 && b >= x[i + 1] && b <= x[i + 2]
				1/4h^3*(x[i + 2] - b)^3
            else
				0
			end
		end
		for i in 0:N+1
	]

	return x -> [c[i]*B[i](x) for i in 1:N+2] |> sum
end

p(x) = -1
q(x) = 2
r(x) = -2
analytic(x) = 1 - sinh(2)/sinh(3)*exp(x) - sinh(1)/sinh(3)*exp(-2x)

x = range(-1,1,length=5)
sol = colocacao_bspline(p, q, r, x, 0, 0)

xplot = range(-1,1,length=100)
plot(xplot,sol.(xplot),label="Colocação")
plot!(xplot,analytic.(xplot),label="Analítica")
savefig("1.pdf")
# verifica-se uma similaridade satisfatoria entre a analitica e a aproximacao feita pelo
# metodo da colocacao utilizando as b-splines. Ademais, testou-se tambem com valores de N maiores
# que 4, chegando ate 15, e verificou-se tambem consistencia.