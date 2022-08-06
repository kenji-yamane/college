function [alpha, T] = questao2()
% Projete a compensacao lag para reduzir o erro em regime pela metade.
% Considere a compensacao lag na seguinte forma:
% Clag = alpha * (T * s + 1) / (alpha * T * s + 1).
alpha = 19/9;
wcp = 6.8962;
T = 10/wcp;
end