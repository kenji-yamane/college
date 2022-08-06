function [A, B, C, D] = questao3(v, Kp, Kpsi)
% Use as variaveis v, Kp e Kpsi para definir a sua resposta.
% Talvez voce nao precise de todas as variaveis para definir sua resposta.
% Definir as matrizes A, B, C e D da representação em espaço de estados,
% que sao retornadas pela funcao.

% A = ...
% B = ...
% C = ...
% D = ...
    A = [[0, v]; [-Kpsi*Kp, -Kpsi]];
    B = [0; Kpsi*Kp];
    C = [1, 0];
    D = 0;
end
