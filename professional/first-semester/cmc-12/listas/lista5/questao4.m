function [F, C] = questao4()
% Determinar as funcoes de transferencia F(s) e C(s) para que o sistema se
% comporte como um sistema de 2a ordem padrao com wn = 2 * pi * 2 rad/s e
% xi = 0.6.

    m = 1000;
    b = 50;
    wn = 2 * pi * 2;
    xi = 0.6;
    s = tf('s');
    
    Kp = m*wn^2;
    Kd = 2*xi*wn*m - b;
    
    F = Kp/(Kp + Kd*s);
    C = Kp + Kd*s;
end
