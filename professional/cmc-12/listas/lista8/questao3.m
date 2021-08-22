function [magnitude, fase] = questao3(sys, w)
% Calcula valores de magnitude e fase de uma aproximacao para tracado
% manual do diagrama de Bode da funcao de transferencia sys nas frequencias
% das por w. Os valores de magnitude e fase sao dados em dB e graus,
% respectivamente. Note que
% magnitude(i) = |sys(j * w(i)|,
% fase(i) = fase(sys(j * w(i)).
[tf_zeros, dc_gain] = zero(sys);
tf_poles = pole(sys);
tf_zeros = abs(sort(tf_zeros));
tf_poles = abs(sort(tf_poles));

for i=0:length(tf_zeros)-1
    dc_gain = dc_gain*tf_zeros(i+1);

    magnitude_break(i+1).freq = tf_zeros(i+1);
    magnitude_break(i+1).change = 20;
    
    fase_break(2*i+1).freq = tf_zeros(i+1)/10;
    fase_break(2*i+1).change = 45;
    fase_break(2*i+2).freq = 10*tf_zeros(i+1);
    fase_break(2*i+2).change = -45;
end
for i=0:length(tf_poles)-1
    dc_gain = dc_gain/tf_poles(i+1);

    magnitude_break(length(tf_zeros)+i+1).freq = tf_poles(i+1);
    magnitude_break(length(tf_zeros)+i+1).change = -20;
    
    fase_break(2*length(tf_zeros)+2*i+1).freq = tf_poles(i+1)/10;
    fase_break(2*length(tf_zeros)+2*i+1).change = -45;
    fase_break(2*length(tf_zeros)+2*i+2).freq = 10*tf_poles(i+1);
    fase_break(2*length(tf_zeros)+2*i+2).change = 45;
end
dc_gain = 20*log10(dc_gain);

[~, idx] = sort([magnitude_break.freq]);
magnitude_break = magnitude_break(idx);
[~, idx] = sort([fase_break.freq]);
fase_break = fase_break(idx);

magnitude_break(1).value = dc_gain;
mag_derivative = 0;
for i=1:length(magnitude_break)-1
    mag_derivative = mag_derivative + magnitude_break(i).change;
    diff = log10(magnitude_break(i+1).freq) - log10(magnitude_break(i).freq);
    magnitude_break(i+1).value = magnitude_break(i).value + mag_derivative*diff;
end
mag_derivative = mag_derivative + magnitude_break(length(magnitude_break)).change;
mag_interp = @(w_log) interp1(log10([magnitude_break.freq]), [magnitude_break.value], w_log);

fase_break(1).value = 0;
fase_derivative = 0;
for i=1:length(fase_break)-1
    fase_derivative = fase_derivative + fase_break(i).change;
    diff = log10(fase_break(i+1).freq) - log10(fase_break(i).freq);
    fase_break(i+1).value = fase_break(i).value + fase_derivative*diff;
end
fase_derivative = fase_derivative + fase_break(length(fase_break)).change;
fase_interp = @(w_log) interp1(log10([fase_break.freq]), [fase_break.value], w_log);

for i=1:length(w)
    if w(i) < magnitude_break(1).freq
        magnitude(i) = magnitude_break(1).value;
    elseif w(i) > magnitude_break(length(magnitude_break)).freq
        diff = log10(w(i)) - log10(magnitude_break(length(magnitude_break)).freq);
        magnitude(i) = magnitude_break(length(magnitude_break)).value + diff*mag_derivative;
    else
        magnitude(i) = mag_interp(log10(w(i)));
    end

    if w(i) < fase_break(1).freq
        fase(i) = fase_break(1).value;
    elseif w(i) > fase_break(length(fase_break)).freq
        diff = log10(w(i)) - log10(fase_break(length(fase_break)).freq);
        fase(i) = fase_break(length(fase_break)).value + diff*fase_derivative;
    else
        fase(i) = fase_interp(log10(w(i)));
    end
end

end
