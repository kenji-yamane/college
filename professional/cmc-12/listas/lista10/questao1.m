function [GM, PM, wcg, wcp] = questao1(mag, fase, w)
% [GM, PM, wcg, wcp] = questao1(mag, fase, w) determina as margens de ganho
% e de fase a partir da resposta em frequencia de um sistema. mag (dB) e
% fase (graus) representam as magnitudes e fase da resposta em frequencia
% considerando as frequencias dadas por w (rad/s). GM e PM sao as margens
% de ganho e de fase, respectivamente, que sao medidas em wcg e wcp,
% respectivamente.

magInterp = @(t) interp1(w, mag, t);
phaseInterp = @(t) interp1(w, fase, t);

wcp = bisectionMethod(magInterp, min(w), max(w), @(x) x);
wcg = bisectionMethod(phaseInterp, min(w), max(w), @(x) x + 180);
PM = 180 + phaseInterp(wcp);
GM = -magInterp(wcg);
max(mag)

end

function middle = bisectionMethod(f, ini, fin, comparator)
    middle = (ini + fin)/2;
    while abs(comparator(f(middle))) > 1e-4
        if sign(comparator(f(middle))) == sign(comparator(f(ini)))
            ini = middle;
        else
            fin = middle;
        end
        middle = (ini + fin)/2;
    end
end