function [Kp, Kv] = questao2(R, Kt, J, b, wn, xi)
% Use as variaveis R, Kt, J, b, wn e xi para definir a sua resposta.
% Talvez voce nao precise de todas as variaveis para definir sua resposta.
% Definir Kp e Kv, que sao retornados pela funcao.

% Kp = ...
% Kv = ...
    Kp = R*J*wn*wn/(2*xi*wn*R*J - R*b - Kt*Kt);
    Kv = (2*xi*wn*R*J - R*b - Kt*Kt)/Kt;
end
