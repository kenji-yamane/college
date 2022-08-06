function controlador = projetarControladorVerticalBusca(requisitos, planta)
% controlador = projetarControladorVerticalBusca(requisitos, planta) 
% projeta o controlador vertical com um refinamento atraves de busca em 
% grade para um melhor atendimento aos requisitos. As entradas da funcao 
% sao as structs requisitos e planta, que contem os requisitos e os 
% parametros da planta, respectivamente. Os requisitos sao:
% requisitos.tr: tempo de subidade de 0 a 100%.
% requisitos.Mp: sobressinal.
% A planta eh dada por:
% planta.m: massa.
% planta.J: inercia.
% planta.l: distancia entre os rotores.
% planta.g: aceleracao da gravidade.
% A saida da funcao eh a struct controlador com:
% controlador.Kp: ganho proporcional.
% controlador.Ki: ganho integrativo.
% controlador.Kd: ganho derivativo.

% Numero de valores de cada parametro usados na grade
N = 20;

% Gerando os valores na grade
[tr, Mp] = deal(requisitos.tr, requisitos.Mp);
trs = linspace(0.8 * tr, 1.2 * tr, N);
Mps = linspace(0.8 * Mp, 1.2 * Mp, N);

% Iterar sobre a grade de trs e Mps para determinar o par tr e Mp que
% melhor atende aos requisitos

% controlador.Kp = ...;
% controlador.Ki = ...;
% controlador.Kd = ...;
bestSoFar = inf;
for i=1:N
    for j=1:N
        requisitosBusca.tr = trs(i);
        requisitosBusca.Mp = Mps(j);
        controladorBusca = projetarControladorVerticalAnalitico(requisitosBusca, planta);
        dinamicaBusca = obterMalhaVertical(controladorBusca, planta);
        infoBusca = stepinfo(dinamicaBusca, 'RiseTimeLimits', [0, 1]);
        
        trBusca = infoBusca.RiseTime;
        MpBusca = infoBusca.Overshoot/100;
        costFunction = abs(tr - trBusca)/tr + abs(Mp - MpBusca)/Mp;
        if costFunction < bestSoFar
            bestSoFar = costFunction;
            bestRequisitos = requisitosBusca;
        end
    end
end
controlador = projetarControladorVerticalAnalitico(bestRequisitos, planta);
end