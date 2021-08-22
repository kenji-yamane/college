format long;

x = [1 2 3 4 5 6];
y = [1.487 2.958 5.602 8.003 11.452 13.021];
potencyRegression(x, y);
function potencyRegression(x, y)
    w = log10(x);
    z = log10(y);
    
    A = [length(w) sum(w) ; sum(w) sum(w.^2)];
    b = [sum(z) ; sum(w.*z)];
    a = A\b;
    fprintf('a1 e a0 são, respectivamente: %.4f %.4f\n', a(2), a(1));
    alpha = 10^a(1);
    beta = a(2);
    fprintf('alpha e beta são, respectivamente: %.4f %.4f\n', alpha, beta);
    
    average = sum(z)/length(z);
    St = sum((z - average).^2);
    Sr = sum((z - a(1) - a(2)*w).^2);
    Cd = (St - Sr)/St;
    fprintf('Coeficiente de determinação: %.4f\n', Cd);
    r = sqrt(Cd);
    fprintf('Coeficiente de correlação: %.4f\n', r);
    f = @(x) a(1) + a(2)*x;
    g = @(x) alpha*x.^beta;
    input = linspace(1, 7);
    plot(input, f(input));
	set(gcf, 'Units', 'Inches');
	pos = get(gcf, 'Position');
	set(gcf, 'PaperPositionMode', 'Auto', 'PaperUnits', 'Inches', 'PaperSize', [pos(3), pos(4)]);
    saveas(gcf, 'linearRegression.pdf');
    plot(input, g(input));
	set(gcf, 'Units', 'Inches');
	pos = get(gcf, 'Position');
	set(gcf, 'PaperPositionMode', 'Auto', 'PaperUnits', 'Inches', 'PaperSize', [pos(3), pos(4)]);
    saveas(gcf, 'potencyFunction.pdf');
end
