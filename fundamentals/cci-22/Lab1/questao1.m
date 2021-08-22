format long;

e = single(1);
while 1 + e/2 > 1
	e = e/2;
end

diary resultados.txt
e
diary off
