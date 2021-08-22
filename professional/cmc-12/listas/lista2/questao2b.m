function omegaInf = questao2b()
% Retorne a velocidade do motor em regime, considerando os parametros
% do motor Maxon RE-max 17 214897. Use SI.

% omegaInf = ...
    R = 8.3;
    Kt = 10.7e-3;
    J = 0.868e-7;
    b = 8.87e-8;
    V = 14.8;
    
    omegaInf = Kt*V/(R*b + Kt^2);

end