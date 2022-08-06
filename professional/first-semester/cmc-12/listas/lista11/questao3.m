function [K, z, p] = questao3()
% Projetar controlador com funcao de transferencia
% C(s) = K * (s - z) / (s * (s - p)).
R = 1;
L = 0.1;
wb = 15;
err = 0.01;
PMmin = 50;

K = 2*max(-L*wb^2 + wb*sqrt(2*L^2*wb^2 + R^2), err*R) + 3;
wcp = sqrt(-R^2 + sqrt(R^4 + 4*L^2*K^2))/sqrt(2*L^2);
PM = 90 - 180*atan(L*wcp/R)/pi;
deltaPM = 10;
phiMax = PMmin - PM + deltaPM;
alpha = (1 - sin(phiMax*pi/180))/(1 + sin(phiMax*pi/180));
T = 1/wcp/sqrt(alpha);
z = -1/T;
p = -1/T/alpha;
end