def heron_map(a, b, x, y):
	"""
		Represents law that defines heron's map
		:param a: control variable
		:type a: float
		:param b: control variable
		:type b: float
		:param x: first input
		:type x: float
		:param y: second input
		:type y: float
	"""
	return (a - x**2 + b*y, x)

