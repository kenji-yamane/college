function [phi, sAst, K] = questao2()
% Determinar:
% - O angulo de saida phi (em graus) do ramo do lugar geometrico das raizes
% (LGR) que comeca no polo -1 + j.
% - O ponto de chegada sAst do mesmo ramo no eixo real.
% - O ganho K assocado a este ponto de chegada.
    phi = 90 - 180*atan(1/9)/pi;
    sAst = -10 - sqrt(82);
    K = 10*((sAst + 1)^2 + 1)/abs(sAst + 10);
end
