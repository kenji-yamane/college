function [Kp, Kpsi] = questao5()
% Calcule os valores de Kp e Kpsi para que o sistema atenda aos requisitos
% no dominio da frequencia.
ksi = 1.4128;
wn = 14.8758;
Kpsi = 2*ksi*wn;
Kp = wn/(2*ksi);
end
