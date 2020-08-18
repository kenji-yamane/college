format long;

yprime = @(t, y) t - y;
truey = 1.41096;

y = eulerMethod(0, 2, yprime, 0.4, 0.4);
err = abs(y - truey);
fprintf('a -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = eulerMethod(0, 2, yprime, 0.1, 0.4);
err = abs(y - truey);
fprintf('b -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = eulerMethod(0, 2, yprime, 0.01, 0.4);
err = abs(y - truey);
fprintf('c -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK2(0, 2, yprime, 0.4, 0.4);
err = abs(y - truey);
fprintf('d -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK2(0, 2, yprime, 0.1, 0.4);
err = abs(y - truey);
fprintf('e -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK2(0, 2, yprime, 0.01, 0.4);
err = abs(y - truey);
fprintf('f -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK4(0, 2, yprime, 0.4, 0.4);
err = abs(y - truey);
fprintf('g -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK4(0, 2, yprime, 0.1, 0.4);
err = abs(y - truey);
fprintf('h -> Aproximação: %.5f Ea: %.5f\n', y, err);
y = RK4(0, 2, yprime, 0.01, 0.4);
err = abs(y - truey);
fprintf('i -> Aproximação: %.5f Ea: %.5f\n', y, err);

function y = eulerMethod(t, y, f, h, objective)
    while t < objective
        y = y + f(t, y)*h;
        t = t + h;
    end
end

function y = RK2(t, y, f, h, objective)
    while t < objective
        k1 = f(t, y);
        k2 = f(t + h, y + k1*h);
        fi = (0.5*k1 + 0.5*k2);
        y = y + fi*h;
        t = t + h;
    end
end

function y = RK4(t, y, f, h, objective)
    while t < objective
        k1 = f(t, y);
        k2 = f(t + 0.5*h, y + 0.5*k1*h);
        k3 = f(t + 0.5*h, y + 0.5*k2*h);
        k4 = f(t + h, y + k3*h);
        y = y + (k1 + 2*k2 + 2*k3 + k4)*h/6;
        t = t + h;
    end
end