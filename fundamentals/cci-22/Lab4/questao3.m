format long
p2 = [-1.004 0.966 -2];

f = @(x) x.^10 - 3*x.^2 - 2;
% g = @(x) -1.004*x.^2 + 0.996*x - 2;
g = @(x) polyval(p2, x);

x = linspace(-1, 0);
y1 = f(x);
y2 = g(x);

coeficients = polyfit(x, y1, 2);
p = @(x) polyval(coeficients, x);
y3 = p(x);

diary resultados.txt
fprintf('Questão 3\n')
fprintf('Diferença encontrada entre f(x) e g(x)')
diffFG = max(abs(y1 - y2))
fprintf('Diferença encontrada entre f(x) e p(x)')
diffFP = max(abs(y1 - y3))
diary off

plot(x, y1, x, y2, x, y3);
legend('f(x)', 'g(x)', 'p(x)');
dividedDifferencesTable(x, y1);
dividedDifferencesTable([-1 -0.5 0], [-4 -2.749 -2]);

function d = dividedDifferencesTable(x, y)
n = length(x);
d = zeros(n, n);
d( : , 1) = y;
for j = 2 : n
    for i = 1 : n - j + 1
        d(i, j) = (d(i + 1, j - 1) - d(i, j - 1))/(x(i + j - 1) - x(i));
    end
end
fprintf('kd poha eh desse aki oh');
n
max(abs(d), [], 'all')
end