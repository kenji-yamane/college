format long;

A = [1 5 6 ; 2 -5 8 ; 0 2 7];
exact = max(leverrier(A));
fprintf('a) Valor exato: %.4f\n', exact);
[aux, iter] = potency(A, 0.1);
err = abs(aux - exact);
fprintf('b) val: %.4f err: %.4f iter: %.4f\n', aux, err, iter);
[aux, iter] = potency(A, 0.01);
err = abs(aux - exact);
fprintf('c) val: %.4f err: %.4f iter: %.4f\n', aux, err, iter);
[aux, iter] = potency(A, 0.001);
err = abs(aux - exact);
fprintf('d) val: %.4f err: %.4f iter: %.4f\n', aux, err, iter);
[aux, iter] = potency(A, 0.0001);
err = abs(aux - exact);
fprintf('e) val: %.4f err: %.4f iter: %.4f\n', aux, err, iter);


function eigenValues = leverrier(A)
    p = zeros(1, length(A) + 1);
    s = zeros(1, length(A));
    M = eye(length(A));
    
    p(1) = 1;
    for i = 2 : length(A) + 1
        M = A*M;
        s(i - 1) = trace(M);
        for j = 1 : i - 1
            p(i) = p(i) - p(j)*s(i - j);
        end
        p(i) = p(i)/(i - 1);
    end
    eigenValues = roots(p);
end

function [eigenDominant, iterations] = potency(A, epsilon)
    v = ones(length(A), 1);
    iterations = 1;
    while max(abs(v - A*v/(sign(max(abs(A*v)))*max(abs(A*v))))) > epsilon
        v = A*v/(sign(max(abs(A*v)))*max(abs(A*v)));
        iterations = iterations + 1;
    end
    eigenDominant = sign(max(abs(A*v)))*max(abs(A*v));
end