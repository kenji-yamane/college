import numpy as np
import matplotlib.pyplot as plt

#1 15000 - 40000 - 100000
STEP = 0.001
NUM_ORBITS = 100
DISCARDED_LENGTH = 200000
ORBIT_LENGTH = 10000

horizontal = []
vertical = []

def edo_func(x, y, r):
	return np.array([r*x + y - x**3, -x + r*y + 2*y**3])

def runge_kutta(x, y, control_param):
	v1 = STEP*edo_func(x, y, control_param)
	v1prime = np.array([x, y]) + v1/2
	v2 = STEP*edo_func(v1prime[0], v1prime[1], control_param)
	n = np.array([x, y]) + v2

	return n[0], n[1]

def search_stables(control_param):
	for i in range(NUM_ORBITS):
		valid = True
		x = np.random.uniform(-0.15, 0.15)
		y = np.random.uniform(-0.15, 0.15)

		for j in range(DISCARDED_LENGTH):
			if abs(y) > 0.3:
				valid = False
				break
			x, y = runge_kutta(x, y, control_param)

		for j in range(ORBIT_LENGTH):
			if abs(y) > 1 or not valid:
				break
			x, y = runge_kutta(x, y, control_param)

			horizontal.append(x)
			vertical.append(y)

search_stables(-0.01)

plt.xlabel('x')
plt.ylabel('y')
plt.plot(horizontal, vertical, 'r,')
plt.savefig('before2.png')

