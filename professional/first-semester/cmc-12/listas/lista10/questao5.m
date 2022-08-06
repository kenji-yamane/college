function [GR, GN, GD] = questao5(L, R, Kp, Ki, a)
% Determine a resposta em funcao de L, R, Kp, Ki e a. Escreva as funcoes de
% transferencia com o s de Laplace definido logo abaixo.

s = tf('s');
C = Kp + Ki/s;
F = Ki/(Kp*s + Ki);
Fm = a/(s + a);
G = 1/(L*s + R);
GR = C*G*F/(1 + C*G*Fm);
GN = -C*G*Fm/(1 + C*G*Fm);
GD = G/(1 + C*G*Fm);

end