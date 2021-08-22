format long;

x = [1 2 3 4 5 6];
y = [1.487 2.958 5.602 8.003 11.452 13.021];
polynomialRegression(x, y);

function polynomialRegression(x, y)
    A = [length(x) sum(x) sum(x.^2) ;
         sum(x) sum(x.^2) sum(x.^3) ;
         sum(x.^2) sum(x.^3) sum(x.^4)];
    b = [sum(y) ; sum(x.*y) ; sum((x.^2).*y)];
    a = A\b;
    fprintf('a2, a1 e a0 são, respectivamente: %.4f %.4f %.4f\n', a(3), a(2), a(1));
    
    average = sum(y)/length(y);
    St = sum((y - average).^2);
    Sr = sum((y - a(1) - a(2)*x - a(3)*x.^2).^2);
    Cd = (St - Sr)/St;
    fprintf('Coeficiente de determinação: %.4f\n', Cd);
    r = sqrt(Cd);
    fprintf('Coeficiente de correlação: %.4f\n', r);
    f = @(x) a(1) + a(2)*x + a(3)*x.^2;
    input = linspace(0, 7);
    plot(x, y, 'ok', input, f(input));
    legend('Dados', 'Regressão');
	set(gcf, 'Units', 'Inches');
	pos = get(gcf, 'Position');
	set(gcf, 'PaperPositionMode', 'Auto', 'PaperUnits', 'Inches', 'PaperSize', [pos(3), pos(4)]);
    saveas(gcf, 'polynomialRegression.pdf');
end
