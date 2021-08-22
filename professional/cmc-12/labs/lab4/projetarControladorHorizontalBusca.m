function controlador = projetarControladorHorizontalBusca(requisitosX,...
    requisitosTheta, planta)
% controlador = projetarControladorHorizontalBusca(requisitosX,
% requisitosTheta, planta) projeta o controlador horizontal com um 
% refinamento atraves de busca em grade para um melhor atendimento aos 
% requisitos. As entradas da funcao sao as structs requisitosX, 
% requisitosTheta e planta, que contem os requisitos da malha horizontal,
% os requisitos da malha de arfagem e os parametros da planta, 
% respectivamente. requisitosX e requisitosTheta sao da forma:
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
[tr, Mp] = deal(requisitosX.tr, requisitosX.Mp);
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
        controladorHorBusca = projetarControladorHorizontalAnalitico(requisitosBusca, planta);
        controladorArfBusca = projetarControladorArfagem(requisitosTheta, planta);
        dinamicaBusca = obterMalhaHorizontal(controladorHorBusca, controladorArfBusca, planta);
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
controlador = projetarControladorHorizontalAnalitico(bestRequisitos, planta);
end