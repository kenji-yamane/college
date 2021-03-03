def map_function1(a, x):
	"""
		Represents function which makes the 1D map
		:param a: control variable
		:type a: float
		:param x: input
		:type x: numpy array
	"""

	return a*x*(1 - x)

def map_function2(x):
	"""
		Represents function which makes the 1D map
		:param x: input
		:type x: numpy array
	"""

	return (3*x - x**3)/2
