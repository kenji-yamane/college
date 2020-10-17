import numpy as np

EPSILON = 1e-8

def inverse_jacobian_step(x, a):
	"""
		Determines dx in the Newton-Raphson method
		:param x: two dimensional input
		:type x: numpy array
	"""

	jacobian = np.array([[-2*x[0] - 1, -0.3], [1, -1]])
	applied = np.array([a - x[0]**2 - 0.3*x[1] - x[0], x[0] - x[1]])
	return np.array(np.linalg.solve(jacobian, applied))

dx = np.array([1, 1])
guess = np.array([-3, -3])

while dx[0]**2 + dx[1]**2 > EPSILON:
	dx = inverse_jacobian_step(guess, 1.4)
	guess = guess - dx

print(guess)

