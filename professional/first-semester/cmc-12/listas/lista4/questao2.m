function x = questao2()
% Defina a a solucao do PVI x(t) como uma funcao anonima do MATLAB.
% A funcao anonima deve ter como unica variavel de entrada o tempo t.
% Caso queira saber mais, acesse:
% https://www.mathworks.com/help/matlab/matlab_prog/anonymous-functions.html

% x = @(t) ...
    x = @(t) exp(-3*t)*sin(3*t) + 1;
end