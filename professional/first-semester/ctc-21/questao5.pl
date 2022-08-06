mover(estado(X, Y, vazio, Z, W), opA, estado(X, vazio, Y, Z, W)).
mover(estado(X, Y, vazio, Z, W), opB, estado(X, Y, Z, vazio, W)).
mover(estado(X, Y, vazio, Z, W), opC, estado(vazio, Y, X, Z, W)).
mover(estado(X, Y, vazio, Z, W), opD, estado(X, Y, W, Z, vazio)).

mover(estado(X, vazio, Y, Z, W), opA, estado(vazio, X, Y, Z, W)).
mover(estado(X, vazio, Y, Z, W), opB, estado(X, Y, vazio, Z, W)).
mover(estado(X, vazio, Y, Z, W), opD, estado(X, Z, Y, vazio, W)).

mover(estado(vazio, X, Y, Z, W), opB, estado(X, vazio, Y, Z, W)).
mover(estado(vazio, X, Y, Z, W), opD, estado(Y, X, vazio, Z, W)).

mover(estado(X, Y, Z, vazio, W), opA, estado(X, Y, vazio, Z, W)).
mover(estado(X, Y, Z, vazio, W), opB, estado(X, Y, Z, W, vazio)).
mover(estado(X, Y, Z, vazio, W), opC, estado(X, vazio, Z, Y, W)).

mover(estado(X, Y, Z, W, vazio), opA, estado(X, Y, Z, vazio, W)).
mover(estado(X, Y, Z, W, vazio), opC, estado(X, Y, vazio, W, Z)).

preto_entre_branco(estado(branco, preto, vazio, preto, branco)).
preto_entre_branco(estado(branco, vazio, preto, preto, branco)).
preto_entre_branco(estado(branco, preto, preto, vazio, branco)).
preto_entre_branco(estado(branco, preto, preto, branco, vazio)).
preto_entre_branco(estado(vazio, branco, preto, preto, branco)).

movimentos(Estado, []) :- preto_entre_branco(Estado).
movimentos(Estado1, [H | T]) :- mover(Estado1, H, Estado2), movimentos(Estado2, T).

