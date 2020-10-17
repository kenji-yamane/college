import matplotlib.pyplot as plt
import numpy as np

def logistic_function(a, x):
	return a*x*(1 - x)

def logistic_derivative(a, x):
	return a*(1 - 2*x)

a_space = np.linspace(2, 4, 60000)
lyapunov_a_space = []
lyapunov_exponent_space = []

for a in a_space:
	orbit = np.random.uniform(0, 1)
	for i in range(100):
		orbit = logistic_function(a, orbit)
	
	lyapunov_exponent = 0
	for i in range(100):
		orbit = logistic_function(a, orbit)
		if logistic_derivative(a, orbit) != 0:
			lyapunov_exponent += np.log(np.abs(logistic_derivative(a, orbit)))
	lyapunov_exponent /= 100
	if lyapunov_exponent > -1:
		lyapunov_exponent_space.append(lyapunov_exponent)
		lyapunov_a_space.append(a)

lyapunov_exponent_space = np.array(lyapunov_exponent_space)
plt.plot(lyapunov_a_space, lyapunov_exponent_space, ',')
plt.plot(a_space, np.zeros(len(a_space)))
plt.savefig('lyapunov.jpg')

