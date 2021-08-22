function controlador = projetarControladorPFeedforward(planta, requisitos)
% controlador = projetarControladorFeedforward(planta, requisitos) projeta
% um controlador P + feedforward para um servomotor de velocidade. O 
% projeto assume como aproximacao que a dinamica da corrente pode ser
% negligenciada. As entradas da funcao as structs planta, que contem os
% parametros da planta, e requisitos, que contem os requisitos. A planta
% eh dada por:
% planta.R: resistencia.
% planta.Jeq: inercia equivalente vista pelo motor.
% planta.Beq: coeficiente de atrito viscoso equivalente visto pelo motor.
% planta.Kt: constante de torque.
% Os requisitos sao:
% requisitos.tau: constante de tempo desejada.
% Alem disso, assume-se erro nulo em regime para entrada degrau como
% requisito.
% A saida da funcao eh a struct controlador com:
% controlador.Kp: ganho proporcional.
% controlador.Kf: ganho de feedforward.

% controlador.Kp = ...
% controlador.Kf = ...
    [R, Jeq, Beq, Kt] = deal(planta.R, planta.Jeq, planta.Beq, planta.Kt);
    tau = requisitos.tau;
    controlador.Kp = (R*Jeq - tau*R*Beq - tau*Kt^2)/(tau*Kt);
    controlador.Kf = (R*Beq + Kt^2)/Kt;
end
