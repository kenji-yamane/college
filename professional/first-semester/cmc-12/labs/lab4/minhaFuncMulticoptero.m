planta = obterPlantaMulticoptero();

requisitos.x.tr = 1.0;
requisitos.x.Mp = 0.1;
requisitos.z.tr = 1.0;
requisitos.z.Mp = 0.1;
requisitos.theta.tr = 0.1;
requisitos.theta.Mp = 0.05;

controlador = projetarControladorMulticoptero(requisitos, planta);
simulacao = simularExperimentoMulticoptero(controlador, planta, 'g');
%fazerAnimacaoMulticoptero(simulacao, planta);
tracarGraficosSimulacao(simulacao);
