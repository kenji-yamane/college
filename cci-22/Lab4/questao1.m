x = [-7 -4 -2 1 2];
y = [-1 ; -3 ; 1 ; 0 ; 0.5];

p = vandermonde(x, y);
function p = vandermonde(x, y)
n = length(y);
vMatrix = zeros(n, n + 1);

for j = 1 : n
    vMatrix( : , j) = x.^(j - 1);
end
vMatrix( : , n + 1) = y;
for i = 1 : n
    for j = i + 1 : n
        vMatrix(j, : ) = vMatrix(j, : ) - vMatrix(i, : ).*(vMatrix(j, i)/vMatrix(i, i));
    end
end
for i = n : -1 : 1
    for j = i - 1 : -1 : 1
        vMatrix(j, : ) = vMatrix(j, : ) - vMatrix(i, :).*(vMatrix(j, i)/vMatrix(i, i));
    end
end
p = zeros(1, n);
for i = 1 : n
    p(i) = vMatrix(i, n + 1)/vMatrix(i, i);
end
diary resultados.txt
fprintf('Questão 1\n');
fprintf('O polinômio encontrado possui os seguintes coeficientes, ordenados por potência crescente de x');
p
diary off
end