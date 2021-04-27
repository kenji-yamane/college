media(X, [X]).
media(X, [H | T]) :- media(X1, T), length(T, L), X is (X1*L + H)/(L + 1).
