format long;

x = 0.1; n = 100000; D = 10000;

for c = 1:n
	D = D - x;
end

diary resultados.txt
D
diary end
