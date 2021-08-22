function [A, B] = questao3(ymax, m, b, g, Kf, y0)
% Determine as matrizes A e B do modelo linearizado do levitador magnetico
% em torno do ponto de equilibrio (y0, v0, u0), com v0 = 0 e
% u0 = sqrt(m * g / Kf) * (ymax - y0).

% A = ...
% B = ...
    A = [0 1; g/(ymax - y0) -b/m];
    B = [0; 2*sqrt(g*Kf/m)/(ymax - y0)];

end
