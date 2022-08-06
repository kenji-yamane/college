function minhaFuncCompararComESemFiltro()
% minhaFuncCompararComESemFiltro() compara um projeto de malha vertical com filtro
% com um projeto de malha vertical sem.

requisitos.tr = 1.0;
requisitos.Mp = 0.1;

planta = obterPlantaMulticoptero();

controlador = projetarControladorVerticalAnalitico(requisitos, planta);

malhaComFiltro = obterMalhaVertical(controlador, planta);
malhaSemFiltro = minhaFuncObterMalhaVerticalSemFiltro(controlador, planta);

t = 0:1e-3:5;

zComFiltro = step(malhaComFiltro, t);
zSemFiltro = step(malhaSemFiltro, t);

figure;
hold on;
plot(t, zComFiltro, 'LineWidth', 2);
plot(t, zSemFiltro, 'LineWidth', 2);
grid on;
xlabel('Tempo (s)', 'FontSize', 14);
ylabel('Z (m)', 'FontSize', 14);
set(gca, 'FontSize', 14);
legend('ComFiltro', 'SemFiltro', 'FontSize', 14, 'Location', 'Southeast');

end