mdc(X, X, X).
mdc(X, Y, D) :- X < Y, Y1 is Y - X, mdc(X, Y1, D).
mdc(X, Y, D) :- Y < X, mdc(Y, X, D).

prime(_, 1).
prime(U, I) :- I1 is I - 1, mdc(U, I, 1), prime(U, I1).

is_prime(N) :- N1 is N - 1, prime(N, N1).

