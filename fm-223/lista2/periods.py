import numpy as np
import matplotlib.pyplot as plt

from utils import heron_map

plot_iteration = 1

def plot_period(func, point_symbol, density):
	convergence = False
	global plot_iteration

	while not convergence:
		convergence = True
		x = np.random.uniform(0, 1)
		y = np.random.uniform(0, 1)
		horizontal = []
		vertical = []
		
		for i in range(100):
			x, y = func(x, y)
			if x**2 + y**2 > 100:
				convergence = False
				break

		if convergence:
			for i in range(density):
				horizontal += [x]
				vertical += [y]
				x, y = func(x, y)
	
	fig, ax = plt.subplots()
	ax.plot(horizontal, vertical, point_symbol)
	plt.savefig('period' + str(plot_iteration) + '.jpg')
	plot_iteration += 1

plot_period(lambda x, y: heron_map(0.9, 0.4, x, y), '+', 50)
plot_period(lambda x, y: heron_map(0.988, 0.4, x, y), '+', 50)
plot_period(lambda x, y: heron_map(1.0, 0.4, x, y), ',', 2000)
plot_period(lambda x, y: heron_map(1.0293, 0.4, x, y), '+', 100)
plot_period(lambda x, y: heron_map(1.045, 0.4, x, y), ',', 20000)
plot_period(lambda x, y: heron_map(1.2, 0.4, x, y), ',', 20000)

