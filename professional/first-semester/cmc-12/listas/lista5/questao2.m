function ts = questao2(sys)
% Determinar numericamente o tempo de acomodacao de 2% ts do sistema
% dinamico sys
    [y, t] = step(sys);
    [y, t] = step(sys, 0:0.001:10*t(size(y)));
    
    y_stable = y(end);
    
    for i = 1:size(y)
        if abs((y(i) - y_stable)/y_stable) > 0.02
            ts = t(i);
            extrm = abs(y(i) - y_stable);
        end
    end
end
