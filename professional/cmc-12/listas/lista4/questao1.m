function f = questao1()
% Defina a inversa f(t) solicitada atraves de uma funcao anonima do MATLAB.
% A funcao anonima deve ter como unica variavel de entrada o tempo t.
% Caso queira saber mais, acesse:
% https://www.mathworks.com/help/matlab/matlab_prog/anonymous-functions.html

% f = @(t) ...
    f = @(t) -exp(-2*t) + exp(-t) + 2*t*exp(-t);
end