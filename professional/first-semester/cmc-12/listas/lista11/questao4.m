function deltaPM = questao4()
% Calcule a perda de margem de fase provocada pelos atrasos na malha.
% Retorne um valor positivo.
ksi = 0.7;
wn = 2*pi;
wcp = wn*sqrt(-2*ksi^2 + sqrt(4*ksi^4 + 1));
tau = 0.1;
deltaPM = tau*wcp;
end