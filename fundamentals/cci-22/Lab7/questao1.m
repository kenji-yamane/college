format long;

f = @(x) 2 + 5*x - 3*x.^2 + 6*x.^3 - 7*x.^4 - 3*x.^5 + x.^6;
integrated = @(x) 2*x + 2.5*x.^2 - x.^3 + 1.5*x.^4 - 1.4*x.^5 - 0.5*x.^6 + 1/7*x.^7;
exactIntegral = integrated(1) - integrated(0);
I = trapezoidRule(f, 0, 1, 1);
err = exactIntegral - I;
fprintf('1a -> Aproximação: %.12f Et: %.12f\n', I, err);
I = trapezoidRule(f, 0, 1, 4);
err = exactIntegral - I;
fprintf('1b -> Aproximação: %.12f Et: %.12f\n', I, err);
I = trapezoidRule(f, 0, 1, 10);
err = exactIntegral - I;
fprintf('1c -> Aproximação: %.12f Et: %.12f\n', I, err);

I = oneThirdRule(f, 0, 1, 2);
err = exactIntegral - I;
fprintf('2a -> Aproximação: %.12f Et: %.12f\n', I, err);
I = oneThirdRule(f, 0, 1, 4);
err = exactIntegral - I;
fprintf('2b -> Aproximação: %.12f Et: %.12f\n', I, err);
I = oneThirdRule(f, 0, 1, 10);
err = exactIntegral - I;
fprintf('2c -> Aproximação: %.12f Et: %.12f\n', I, err);

I = threeEightsRule(f, 0, 1, 3);
err = exactIntegral - I;
fprintf('3a -> Aproximação: %.12f Et: %.12f\n', I, err);
I = oneThirdRule(f, 0, 0.4, 2) + threeEightsRule(f, 0.4, 1, 3);
err = exactIntegral - I;
fprintf('3b -> Aproximação: %.12f Et: %.12f\n', I, err);

function I = trapezoidRule(f, a, b, n)
    h = (b - a)/n;
    
    I = 0;
    for i = 1 : n
        I = I + unitaryTrapezoid(f, a + h*(i - 1), a + h*i);
    end
end

function I = unitaryTrapezoid(f, a, b)
    I = (b - a)*(f(a) + f(b))/2;
end

function I = oneThirdRule(f, a, b, n)
    I = 0; i = 0; h = (b - a)/n;
    while i + 1 < n
        I = I + unitaryOneThird(f, a + h*i, a + h*(i + 1), a + h*(i + 2));
        i = i + 2;
    end
end

function I = unitaryOneThird(f, x0, x1, x2)
    I = (x1 - x0)*(f(x0) + 4*f(x1) + f(x2))/3;
end

function I = threeEightsRule(f, a, b, n)
    I = 0; i = 0; h = (b - a)/n;
    
    while i + 2 < n
        x0 = a + h*i; x1 = a + h*(i + 1);
        x2 = a + h*(i + 2); x3 = a + h*(i + 3);
        I = I + unitaryThreeEights(f, x0, x1, x2, x3);
        i = i + 3;
    end
end

function I = unitaryThreeEights(f, x0, x1, x2, x3)
    I = 3*(x1 - x0)*(f(x0) + 3*f(x1) + 3*f(x2) + f(x3))/8;
end