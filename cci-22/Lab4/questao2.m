x = [-1 ; 0 ; 2 ; 5 ; 6 ; 9 ; 10];
y = [1 ; 1 ; 0 ; -1 ; -2 ; -5 ; -18];

d = dividedDifferencesTable(x, y);
function d = dividedDifferencesTable(x, y)
n = length(x);
d = zeros(n, n);
d( : , 1) = y;
for j = 2 : n
    for i = 1 : n - j + 1
        d(i, j) = (d(i + 1, j - 1) - d(i, j - 1))/(x(i + j - 1) - x(i));
    end
end
diary resultados.txt
fprintf('Questão 2\n');
fprintf('A tabela de diferenças divididas é:');
d
diary off
end