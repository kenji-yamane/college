import matplotlib.pyplot as plt
import numpy as np

from utils import map_function1

def bifurcation_diagram(start, end, figname):
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
		point = np.random.uniform(0, 1)
		for i in range(100):
			point = map_function1(a, point)
		
		for i in range(700):
			horizontal.append(a)
			vertical.append(point)
			point = map_function1(a, point)
	
	fig, ax = plt.subplots()
	ax.plot(horizontal, vertical, ',')
	plt.savefig(figname)

bifurcation_diagram(1, 4, 'bifurcation1.jpg')
bifurcation_diagram(3.4, 4, 'bifurcation2.jpg')
bifurcation_diagram(3.82, 3.86, 'bifurcation3.jpg')

