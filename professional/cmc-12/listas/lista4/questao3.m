function G = questao3(J, b, R, L, Kt)
% Defina a funcao de transferencia G do motor eletrico usando tf ou zpk.
% Caso queira, pode usar o truque de definir s: s = tf('s');

% G = ...
    G = tf(Kt, [J*L, b*L + R*J, R*b + Kt*Kt, 0]);
end
