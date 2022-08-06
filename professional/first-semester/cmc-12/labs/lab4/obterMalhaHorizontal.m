function dinamica = obterMalhaHorizontal(controladorX, controladorTheta, planta)
% dinamica = obterMalhaHorizontal(controladorX, controladorTheta, planta)
% obtem a dinamica da malha horizontal. As structs controladorX e 
% controladorTheta possuem a seguinte estrutura:
% controlador.Kp: ganho proporcional.
% controlador.Ki: ganho integrativo.
% controlador.Kd: ganho derivativo.
% A struct planta tem os seguintes parametros:
% planta.m: massa.
% planta.J: inercia.
% planta.l: distancia entre os rotores.
% planta.g: aceleracao da gravidade.
% A saida dinamica eh a dinamica da malha horizontal na forma de funcao de
% transferencia.

% dinamica = ...;
[Kpx, Kix, Kdx] = deal(controladorX.Kp, controladorX.Ki, controladorX.Kd);
[Kpo, Kvo] = deal(controladorTheta.Kp, controladorTheta.Kv);
[J, g] = deal(planta.J, planta.g);

num = g*Kvo*Kpo*Kix;
den = [J, Kvo, Kvo*Kpo, g*Kvo*Kpo*Kdx, g*Kvo*Kpo*Kpx, g*Kvo*Kpo*Kix];
dinamica = tf(num, den);
end