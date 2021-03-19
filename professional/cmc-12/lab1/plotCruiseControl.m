cruise_control = load('data.mat');

force = cruise_control.data.f;
time = cruise_control.data.t;
velocity = cruise_control.data.v;

[m, b] = identificarCruiseControl(force, time, velocity);

model_func = @(t) force/b*(1 - exp(-b*t/m));

plot(time, velocity, 'b');
hold on
p = plot(time, model_func(time), '--r');
p.LineWidth = 2;
xlabel('Tempo(s)')
ylabel('Velocidade(m/s)')
legend('experimental', 'modelo')
title('experimental x modelo')

print -dpng teste_modelo.png
