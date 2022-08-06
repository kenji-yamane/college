function [Kp, Kv] = questao2()
% Projetar Kp e Kv para que o carro autonomo tenha banda passante de 1 Hz e
% margem de fase de 60 graus. Usar formulas exatas, i.e. sem aproximacoes.
ksi = 1/2*1/((1/tan(pi/3)^2 - 1/2)^2 - 1/4)^0.25;
wn = 2*pi/sqrt(1 - 2*ksi^2 + sqrt(4*ksi^4 - 4*ksi^2 + 2));
m = 1000;
b = 50;
Kv = 2*ksi*wn*m - b;
Kp = wn*wn*m/Kv;
end