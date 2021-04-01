function [p1, p2] = questao1(tr, Mp)
% Determinar os polos de um sistema de 2a ordem a partir do tempo de 
% subida de 0 a 100% tr e sobressinal Mp. Convencao:
% p1 = -sigma + wd * j,
% p2 = -sigma - wd * j,
% em que sigma > 0 e wd > 0.
    epsilon = log(Mp)/sqrt(pi^2 + log(Mp)^2);
    omega_d = (pi - acos(epsilon))/(tr*sqrt(1 - epsilon^2));
    sigma = epsilon*omega_d/sqrt(1 - epsilon^2);
    
    p1 = -sigma + omega_d*1j;
    p2 = -sigma - omega_d*1j;
end
