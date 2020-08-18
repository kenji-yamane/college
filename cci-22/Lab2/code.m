format long;

f=@(x) 4*sin(x) - exp(x);
phi=@(x) x - 2*sin(x) + 0.5*exp(x);
df=@(x) 4*cos(x) - exp(x);

bissection(f, a, b, epsilon1, maxIterations);
falsePosition(f, a, b, epsilon1, epsilon2, maxIterations);
fixedPoint(f, phi, (a + b)/2, epsilon1, epsilon2, maxIterations);
newtonRaphson(f, df, (a + b)/2, epsilon1, epsilon2, maxIterations);
secant(f, a, b, epsilon1, epsilon2, maxIterations);

function [r, k] = bissection(f, a, b, epsilon, maxIterations)
	k = 0;
	while k < maxIterations
		k = k + 1;
		if abs(a - b) < epsilon
			r = (a + b)/2;
			break;
		end
		r = (a + b)/2;
		if f(r)*f(a) < 0
			b = r;
		else
			a = r;
		end
	end
	fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
end

function [r, k] = falsePosition(f, a, b, epsilon1, epsilon2, maxIterations)
	k = 0;
	while k < maxIterations
		k = k + 1;
		if abs(a - b) < epsilon1
			r = (a*f(b) - b*f(a))/(f(b) - f(a));
			break;
		end
		r = (a*f(b) - b*f(a))/(f(b) - f(a));
		if abs(f(r)) < epsilon2
			break;
		end
		if f(a)*f(r) < 0
			b = r;
		else
			a = r;
		end
	end
	fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
end

function [r, k] = fixedPoint(f, phi, x0, epsilon1, epsilon2, maxIterations)
	k = 0; r = x0;
	while k < maxIterations
		if abs(f(r)) < epsilon1
			break;
		end
		k = k + 1;
		temp = r;
		r = phi(r);
		if abs(r - temp) < epsilon2
			break;
		end
	end
	fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
end

function [r, k] = newtonRaphson(f, df, x0, epsilon1, epsilon2, maxIterations)
	k = 0; r = x0;
	while k < maxIterations
		if abs(f(r)) < epsilon1
			break;
		end
		k = k + 1;
		temp = r;
		r = r - f(r)/df(r);
		if abs(r - temp) < epsilon2
			break;
		end
	end
	fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
end

function[r, k] = secant(f, x0, x1, epsilon1, epsilon2, maxIterations)
	k = 0; r = x1; temp1 = x0;
	if abs(f(x0)) < epsilon1
		fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
		return;
	end
	while k < maxIterations
		if abs(f(r)) < epsilon1 || abs(r - temp1) < epsilon2
			break;
		end
		k = k + 1;
		temp2 = r;
		r = r - f(r)*(r - temp1)/(f(r) - f(temp1));
		temp1 = temp2;
	end
	fprintf('A raiz aproximada é %.10f, obtido em %d iterações.\n', r, k);
end
