function controlador = projetarControladorPI(planta, requisitos)
% controlador = projetarControladorPI(planta, requisitos) projeta
% um controlador PI com pre-filtro para um servomotor de velocidade. O 
% projeto assume como aproximacao que a dinamica da corrente pode ser
% negligenciada. As entradas da funcao as structs planta, que contem os
% parametros da planta, e requisitos, que contem os requisitos. A planta
% eh dada por:
% planta.R: resistencia.
% planta.Jeq: inercia equivalente vista pelo motor.
% planta.Beq: coeficiente de atrito viscoso equivalente visto pelo motor.
% planta.Kt: constante de torque.
% Os requisitos sao:
% requisitos.tr: tempo de subida de 0 a 100%.
% requisitos.Mp: sobressinal.
% A saida da funcao eh a struct controlador com:
% controlador.Kp: ganho proporcional.
% controlador.Ki: ganho integrativo.

% controlador.Kp = ...
% controlador.Ki = ...
    [R, Jeq, Beq, Kt] = deal(planta.R, planta.Jeq, planta.Beq, planta.Kt);
    [tr, Mp] = deal(requisitos.tr, requisitos.Mp);
    
    ksi = abs(log(Mp))/sqrt(pi^2 + log(Mp)^2);
    wn = (pi - acos(ksi))/(tr*sqrt(1 - ksi^2));
    
    controlador.Kp = (2*R*Jeq*ksi*wn - Kt^2 - R*Beq)/Kt;
    controlador.Ki = R*Jeq*wn^2/Kt;
end
