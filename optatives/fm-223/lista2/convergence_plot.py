import numpy as np
import matplotlib.pyplot as plt

from utils import heron_map

def convergence_plot(func):
	x_space = np.linspace(-2.5, 2.5, 700)
	y_space = np.linspace(-2.5, 2.5, 700)
	horizontal = []
	vertical = []

	for x in x_space:
		for y in y_space:
			input1 = x
			input2 = y

			for i in range(20):
				input1, input2 = func(input1, input2)

				if input1**2 + input2**2 > 6:
					horizontal.append(x)
					vertical.append(y)
					break
	
	fig, ax = plt.subplots()
	plt.xticks([-2.5, 2.5])
	plt.yticks([-2.5, 2.5])

	ax.plot(horizontal, vertical, ',')
	plt.show()

# convergence_plot(lambda x, y: heron_map(1.28, -0.3, x, y))
convergence_plot(lambda x, y: heron_map(1.4, -0.3, x, y))

