plot(t1, v1, 'r')
hold on
plot(t2, v2, 'b')
plot(t3, v3, 'g')
xlabel('Tempo(s)')
ylabel('Velocidade(m/s)')
legend('d = 100 N', 'd = 200 N', 'd = 300 N')
title('Com perturbacao')
print -dpng 3c.png
