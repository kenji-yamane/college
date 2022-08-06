s = tf('s');
G = 1/((s + 1)*(s^2 + 4));

r = 1/32;

figure;
hold on;

w1 = 2+r:1e-2:1000;
w2 = [-1000:1e-2:-2-r, -2-r-1e-2:1e-4:-2-r];
angles = -pi/2:1e-3:pi/2;
w6 = -2+r:1e-4:2-r;

C1mx = zeros(size(w1));
C1my = zeros(size(w1));
for i = 1:length(w1)
    sm = evalfr(G, w1(i)*1j);
    C1mx(i) = real(sm);
    C1my(i) = imag(sm);
end

C2mx = zeros(size(w2));
C2my = zeros(size(w2));
for i = 1:length(w2)
    sm = evalfr(G, w2(i)*1j);
    C2mx(i) = real(sm);
    C2my(i) = imag(sm);
end

C3mx = zeros(size(angles));
C3my = zeros(size(angles));
for i = 1:length(angles)
    sm = evalfr(G, 1000*exp(angles(i)*1j));
    C3mx(i) = real(sm);
    C3my(i) = imag(sm);
end

C4mx = zeros(size(angles));
C4my = zeros(size(angles));
for i = 1:length(angles)
    sm = evalfr(G, 2*1j + r*exp(angles(i)*1j));
    C4mx(i) = real(sm);
    C4my(i) = imag(sm);
end

C5mx = zeros(size(angles));
C5my = zeros(size(angles));
for i = 1:length(angles)
    sm = evalfr(G, -2*1j + r*exp(angles(i)*1j));
    C5mx(i) = real(sm);
    C5my(i) = imag(sm);
end

C6mx = zeros(size(w6));
C6my = zeros(size(w6));
for i = 1:length(w6)
    sm = evalfr(G, w6(i)*1j);
    C6mx(i) = real(sm);
    C6my(i) = imag(sm);
end

plot(C1mx, C1my, 'b', 'LineWidth', 2);
plot(C2mx, C2my, 'r', 'LineWidth', 2);
plot(C3mx, C3my, 'g', 'LineWidth', 2);
plot(C4mx, C4my, 'm', 'LineWidth', 2);
plot(C5mx, C5my, 'k', 'LineWidth', 2);
plot(C6mx, C6my, 'c', 'LineWidth', 2);

axis equal
grid on
xlabel('Re\{G(j \omega)\}')
xlabel('Im\{G(j \omega)\}')
