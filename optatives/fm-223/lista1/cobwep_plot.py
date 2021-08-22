import numpy as np
import matplotlib.pyplot as plt

from utils import map_function1, map_function2

def set_axis(ax):
	"""
		Sets x and y axes of a matplotlib plot to origin
		:param ax: plot whose axes will be set
		:type ax: matplotlib axix
	"""
	ax.spines['left'].set_position('zero')
	ax.spines['bottom'].set_position('zero')
	ax.spines['right'].set_color('none')
	ax.spines['top'].set_color('none')

def cobweb(starting_point, num_iterations, func):
	"""
		Creates necessary data to make a cobweb plot in matplotlib
		:param starting_point: point in x axis to start the cobweb plot
		:type starting_point: float
		:param num_iterations: number of iterations, i.e. segments in cobweb plot
		:type num_iterations: float
		:param func: function whose cobweb plot data will be constructed
		:type func: function
	"""
	
	horizontal = [starting_point]
	vertical = [0]
	start_point = [starting_point, 0]
	
	for i in range(0, num_iterations):
		if i%2 == 0:
			end_point = [start_point[0], func(start_point[0])]
		else:
			end_point = [start_point[1], start_point[1]]
		
		horizontal += [end_point[0]]
		vertical += [end_point[1]]
		start_point = end_point
	
	return horizontal, vertical

fig, ax = plt.subplots()
set_axis(ax)
plt.xticks([0.1, 0.5])
plt.yticks([0.5])

x = np.linspace(-0.1, 0.7)
ax.plot(x, x)
ax.plot(x, map_function1(2, x))

h, v = cobweb(0.1, 7, lambda x : map_function1(2, x))
ax.plot(h, v, '--')

plt.savefig('cobweb1.jpg')

fig, ax = plt.subplots()
set_axis(ax)
plt.xticks([-1, 1, 1.6, 1.8])
plt.yticks([-1, 1])

x = np.linspace(-2, 2)
ax.plot(x, x)
ax.plot(x, map_function2(x))

h, v = cobweb(1.6, 7, map_function2)
ax.plot(h, v, '--')
h, v = cobweb(1.8, 10, map_function2)
ax.plot(h, v, '--')

plt.savefig('cobweb2.jpg')

fig, ax = plt.subplots()
set_axis(ax)
plt.xticks([0, 1])
plt.yticks([1])

x = np.linspace(0, 1)
ax.plot(x, x)
ax.plot(x, map_function1(3.86, x))

h, v = cobweb(0.1, 200, lambda x : map_function1(3.86, x))
ax.plot(h, v, '--')

plt.savefig('cobweb3.jpg')

