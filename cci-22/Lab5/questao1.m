format long

f = @(x) 4./(5 + 2*x.^2);

for i = 2 : 10
    approximate(f, i, -3, 3);
end

function approximate(f, n, a, b)
nodes = chebyshevNodes(a, b, n);
coefficients = vandermonde(nodes, f(nodes));
p = @(x) polyval(coefficients, x);

x = linspace(a, b);
fprintf('Maior módulo da diferença para o grau %d\n', n);
diff = max(abs(p(x) - f(x)))
plot(x, f(x), x, p(x));
legend('f(x)', 'p(x)');
set(gcf, 'Units', 'Inches');
pos = get(gcf, 'Position');
set(gcf, 'PaperPositionMode', 'Auto', 'PaperUnits', 'Inches', 'PaperSize', [pos(3), pos(4)]);
saveas(gcf, (['grau', num2str(n), '.pdf']));
end

function nodes = chebyshevNodes(a, b, n)
nodes = zeros(1, n + 1);
for k = 1 : n + 1
    nodes(k) = (a + b)/2 - (b - a)*cos((k - 1)*pi/n)/2;
end
end

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
    p(n - i + 1) = vMatrix(i, n + 1)/vMatrix(i, i);
end
end
