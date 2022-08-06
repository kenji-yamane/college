function planta = obterPlanta()
% Ix, Iy, Iz são os momentos de inércia em relação a cada eixo
% g é a aceleração da gravidade adotava
% m é a massa do drone
% b é o coeficiente de empuxo (Thrust coefficient)
% d é o coeficiente de atrito com o ar (Drag coefficient)
% l é a distância dos rotores ao centro do drone

planta.Ix = 8.5532e-3; % kg.m^2
planta.Iy = 8.5532e-3; % kg.m^2
planta.Iz = 1.476e-2;  % kg.m^2
planta.g = 9.81;       % m/s^2
planta.m = 9.64e-1;    % kg
planta.b = 7.66e-5;    % N.s^2
planta.d = 5.63e-6;    % N.m.s^2
planta.l = 2.2e-1;     % m

end