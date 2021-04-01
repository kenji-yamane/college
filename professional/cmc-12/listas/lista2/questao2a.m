function tau = questao2a(R, Kt, J, b)
% Retorne a constante de tempo do motor eletrico. Considere o sistema
% dinamico que tem V como entrada e omega como saida. Considere que a
% indutancia L eh desprezivel. De sua resposta em funcao dos parametros
% do motor.

% tau = ...
    tau = R*J/(b*R + Kt^2);

end