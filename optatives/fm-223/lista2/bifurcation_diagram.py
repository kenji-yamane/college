import matplotlib.pyplot as plt
import numpy as np

from utils import heron_map

def bifurcation_diagram(start, end, func):
	"""
		Constructs the bifurcation diagram for map_function1
		:param start: point in x axis to start plotting
		:type start: float
		:param end: point in x axis to end plotting
		:type end: float
		:param figname: name of the figure to be saved
		:type end: float
	"""
	a_space = np.linspace(start, end, 500)
	horizontal = []
	vertical = []
	
	for a in a_space:
		point_x = np.random.uniform(-1, 1)
		point_y = np.random.uniform(-1, 1)
		for i in range(100):
			if point_x < -2.5 or point_x > 2.5:
				break
			point_x, point_y = func(a, point_x, point_y)
		
		for i in range(800):
			if point_x < -2.5 or point_x > 2.5:
				break
			horizontal.append(a)
			vertical.append(point_x)
			point_x, point_y = func(a, point_x, point_y)
	
	fig, ax = plt.subplots()
	ax.plot(horizontal, vertical, ',')
	plt.savefig('bifurcation_diagram.jpg')

bifurcation_diagram(0, 1.25, lambda a, x, y: heron_map(a, 0.4, x, y))

