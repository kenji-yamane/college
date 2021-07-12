# Projeto de análise numérica

Este código serve como auxílio para escrita do artigo teórico
relativo ao desempenho dos métodos da classe BDF em problemas
Stiff.

Todos os programas devem ser executados a partir da pasta
onde estão. Todos deixam as suas figuras geradas dentro da pasta
`figures`.

## Estrutura de pastas

- bdf_generator.jl
- bdf_utils.jl
- convergence/
	- absolute_stability.jl
	- consistency.jl
	- zero_stability.jl
- problems/
	- flame_model.jl
	- from_leveque.jl
	- van_der_pol.jl
- figures/

## Explicação dos programas

### `bdf_generator.jl`

Geram os coeficientes do método BDF da ordem que se queira.
Pode-se ajustar a ordem com a variável `order`.

### `convergence`

Contém programas que computam gráficos e valores relativos à consistência, estabilidade
e convergência dos métodos BDF.

### `problems`

Aplica em diferentes problemas os métodos BDF, trapezional e de Runge-Kutta.

O utilizado no artigo seria o do `flame_model.jl`.

