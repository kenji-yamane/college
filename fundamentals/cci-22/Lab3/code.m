format long;

A = [3 -0.1 -0.2 ; 0.1 7 -0.3 ; 0.3 -0.2 10];
b = [7.85 ; -19.3 ; 71.4];
gaussElimination(A, b);
gaussJordan(A, b);
luDecomposition(A, b);
gaussJacobi(A, b, 0.0000001);
gaussSiedel(A, b, 0.0000001);

function x = gaussElimination(A, b)
	n = size(b);
	for i = 1 : n
		for j = i + 1 : n
			if A(i, i) == 0
				aux = A(j, :);
				A(j, :) = A(i, :);
				A(i, :) = aux;
			end
		end
		for j = i + 1 : n
			if A(i, i) == 0
				fprintf('O sistema não tem solução!.\n');
				x = [];
				return;
			end
			m = A(j, i)/A(i, i);
			for k = i : n
				A(j, k) = A(j, k) - m*A(i, k);
			end
			b(j) = b(j) - m*b(i);
		end
	end
	x(n) = 0;
	for i = n : -1 : 1
		for j = n : -1 : i
			b(i) = b(i) - A(i, j)*x(j);
		end
		x(i) = b(i)/A(i, i);
	end
	fprintf('A solução encontrada pelo método da eliminação gaussiana foi:\n');
	x
end

function x = gaussJordan(A, b)
	n = size(b);
	for i = 1 : n
		for j = i + 1 : n
			if A(i, i) == 0
				aux = A(j, :);
				A(j, :) = A(i, :);
				A(i, :) = aux;
			end
		end
		for j = i + 1 : n
			if A(i, i) == 0
				fprintf('O sistema não tem solução!.\n');
				x = [];
				return;
			end
			m = A(j, i)/A(i, i);
			for k = i : n
				A(j, k) = A(j, k) - m*A(i, k);
			end
			b(j) = b(j) - m*b(i);
		end
	end
	for i = n : -1 : 2
		for j = i - 1 : -1 : 1
			m = A(j, i)/A(i, i);
			for k = i : n
				A(j, k) = A(j, k) - m*A(i, k);
			end
			b(j) = b(j) - m*b(i);
		end
	end
	x(n) = 0;
	for i = 1 : n
		x(i) = b(i)/A(i, i);
	end
	fprintf('A solução encontrada pelo método de Gauss-Jordan foi:\n');
	x
end

function x = luDecomposition(A, b)
	n = size(b);
	L = eye(n);
	for i = 1 : n
		if A(i, i) == 0
			fprintf('O sistema não pode ser resolvido pela forma');
			fprintf('clássica de decomposição LU\n');
			x = [];
			return;
		end
		L(i + 1 : n, i) = A(i + 1 : n, i)/A(i, i);
		for l = i + 1 : n
			A(l, :) = A(l, :) - L(l, i)*A(i, :);
		end
	end
	U = A;
	y(n) = 0;
	for i = 1 : n
		for j = 1 : i
			b(i) = b(i) - L(i, j)*y(j);
		end
		y(i) = b(i);
	end
	x(n) = 0;
	for i = n : -1 : 1
		for j = n : -1 : i
			y(i) = y(i) - U(i, j)*x(j);
		end
		x(i) = y(i)/U(i, i);
	end
	fprintf('A solução encontrada pela decomposição em LU foi:');
	x
end

function x = gaussJacobi(A, b, epsilon)
	n = size(b);
	g(n) = 0;
	C = eye(n);
	for i = 1 : n
		for j = 1 : n
			if i == j
				C(i, j) = 0;
				g(i) = b(i)/A(i, j);
			else
				if A(i, i) == 0
					fprintf('O sistema não pode ser resolvido pela forma ');
					fprintf('clássica de Gauss Jacobi\n');
					x = [];
					return;
				end
				C(i, j) = -A(i, j)/A(i, i);
			end
		end
	end
	x = g;
	iterations = 0;
	convergence = inf;
	while convergence > epsilon
		iterations = iterations + 1;
		previousX = x;
		x = x*C + g;
		d = -inf;
		X = -inf;
		for i = 1 : n
			d = max(d, abs(x(i) - previousX(i)));
			X = max(X, abs(x(i)));
		end
		convergence = d/X;
	end
	fprintf('Por Gauss-Jacobi, precisando de %d iterações:', iterations);
	x
end

function x = gaussSiedel(A, b, epsilon)
	n = size(b);
	g(n) = 0;
	C = eye(n);
	for i = 1 : n
		for j = 1 : n
			if i == j
				C(i, j) = 0;
				g(i) = b(i)/A(i, j);
			else
				if A(i, i) == 0
					fprintf('O sistema não pode ser resolvido pela forma ');
					fprintf('clássica de Gauss-Siedel\n');
					x = [];
					return;
				end
				C(i, j) = -A(i, j)/A(i, i);
			end
		end
	end
	x(n) = 0;
	for i = 1 : n
		x(i) = 0;
	end
	y(n) = 0;
	iterations = 0;
	convergence = inf;
	while convergence > epsilon
		iterations = iterations + 1;
		previousX = x;
		for i = 1 : n
			y(i) = 0;
		end
		for i = 1 : n
			for j = 1 : n
				y(i) = y(i) + C(i, j)*x(j);
			end
			y(i) = y(i) + g(i);
			x(i) = y(i);
		end
		d = -inf;
		X = -inf;
		for i = 1 : n
			d = max(d, abs(x(i) - previousX(i)));
			X = max(X, abs(x(i)));
		end
		convergence = d/X;
	end
	fprintf('Por Gauss-Siedel, precisando de %d iterações:', iterations);
	x
end
