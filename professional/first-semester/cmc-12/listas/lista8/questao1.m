function y = questao1(w, Au, phiu, Kp, Kd, m, b)
% Determinar a saida em regime permanente senoidal assumindo referencia
% nula e perturbacao senoidal na forma d(t) = Ad * sin(w * t + phid).

% y = @(t) 
Ay = Au/sqrt((b + Kd)^2*w^2 + (Kp - m*w^2)^2);
phiy = phiu + atan((b + Kd)*w/(m*w^2 - Kp));
y = @(t) Ay*sin(w*t + phiy);

end
