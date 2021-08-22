import numpy as np
from math import log

ORBIT_LENGTH = 10000
MAP_DIMENSION = 2

def henon_map(vet):
	return np.array([1.4 - vet[0]**2 + 0.3*vet[1], vet[0]])

def henon_jacobian(vet):
	return np.array([[-2*vet[0], 0.3], [1, 0]])

eye = np.eye(MAP_DIMENSION)
w = []
for i in range(MAP_DIMENSION):
	w.append(eye[i])
v = np.array([0, 0])
lyapunov_exponents = np.zeros(MAP_DIMENSION)

for i in range(ORBIT_LENGTH):
	z = []
	for j in range(MAP_DIMENSION):
		z.append(np.matmul(henon_jacobian(v), w[j]))

	y = []
	for j in range(MAP_DIMENSION):
		y.append(z[j])
		for k in range(j):
			y[j] -= y[k]*np.dot(z[j], y[k])/np.dot(y[k], y[k])
	
	for j in range(MAP_DIMENSION):
		lyapunov_exponents[j] += log(np.linalg.norm(y[j]))

	for j in range(MAP_DIMENSION):
		w[j] = y[j]/np.linalg.norm(y[j])

	v = henon_map(v)

for i in range(MAP_DIMENSION):
	lyapunov_exponents[i] /= ORBIT_LENGTH

for i in range(MAP_DIMENSION):
	print(lyapunov_exponents[i])

print('dimension:', 1 + lyapunov_exponents[0]/abs(lyapunov_exponents[1]))

