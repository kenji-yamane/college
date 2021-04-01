function [A, B, C, D] = questao3(m1, m2, k, b)
% Use as variaveis m1, m2, k e b para definir a sua resposta.
% Definir as matrizes A, B, C e D que serao retornadas pela funcao.
    A = [[0 1 0 0]; [-k/m1 -b/m1 k/m1 0]; [0 0 0 1]; [k/m2 0 -k/m2 -b/m2]];
    B = [0; 0; 0; 1/m2];
    C = [[1 0 0 0]; [0 0 1 0]];
    D = [0; 0; 0; 0];
end
