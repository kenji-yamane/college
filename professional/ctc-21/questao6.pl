maximo(X, [X]).
maximo(X, [H1 | [H2 | T]]) :- H1 >= H2, maximo(X, [H1 | T]).
maximo(X, [H1 | [H2 | T]]) :- H1 < H2, maximo(X, [H2 | T]).
