format long;

f = @(x) 1./(1 + 7*x.^2);
nodes = [0 0.4 0.65 1.31 1.48 1.62 2.45];
s = @(x) cubicSpline(nodes, f(nodes), x);
input = [0.22 0.47 1.09 1.36 1.92];
outputF = f(input)
outputS = [s(0.22) s(0.47) s(1.09) s(1.36) s(1.92)]
error = (abs(outputF - outputS)./outputS).*100

function value = cubicSpline(x, y, input)
n = length(x);
h = zeros(1, n - 1);
for i = 1 : n - 1
    h(i) = x(i + 1) - x(i);
end
A = zeros(n, n); A(1, 1) = 1; A(n, n) = 1;
for i = 2 : n - 1
    A(i, i) = 2*(h(i - 1) + h(i)); A(i, i - 1) = h(i - 1); A(i, i + 1) = h(i);
end
b = zeros(n, 1);
for i = 2 : n - 1
    b(i) = 6*((y(i + 1) - y(i))/h(i) - (y(i) - y(i - 1))/h(i - 1));
end
g = A\b;
a = zeros(n - 1, 1); b = zeros(n - 1, 1); c = zeros(n - 1, 1); d = zeros(n - 1, 1);
for i = 1 : n - 1
    a(i) = (g(i + 1) - g(i))/(6*h(i));
    b(i) = g(i + 1)/2;
    c(i) = (y(i + 1) - y(i))/h(i) + (2*h(i)*g(i + 1) + g(i)*h(i))/6;
    d(i)= y(i + 1);
end
i = 1;
while input > x(i + 1)
    i = i + 1;
end
value = a(i)*(input - x(i + 1)).^3 + b(i)*(input - x(i + 1)).^2 + c(i)*(input - x(i + 1)) + d(i);
end