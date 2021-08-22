t = 0:0.01:10;
analytic = @(t) 1 - exp(-0.7*t).*cos(sqrt(0.51)*t) - 0.7/sqrt(0.51)*exp(-0.7*t).*sin(sqrt(0.51)*t);

plot(t, analytic(t), 'g');
xlabel('Tempo (s)');
ylabel('Posição (m)');
title('Sistema massa-mola');
grid on;
print -dpng questao2.png;

numeric = @(t, y) [y(2); 1 - y(1) - 1.4*y(2)];
[~, integrated] = ode45(numeric, t, [0; 0]);
max(analytic(t) - integrated(:, 1).') % comparing numeric and analytic solution
