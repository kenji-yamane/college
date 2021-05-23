first_a = load("data/solar_wind1a.dat");
second = load("data/solar_wind2.dat");

figure;
[pxx, freq] = pwelch(first_a);
loglog(freq, pxx);
print('-dpng', 'figures/psd1a.png');

figure;
[pxx, freq] = pwelch(second);
loglog(freq, pxx);
print('-dpng', 'figures/psd2.png');
