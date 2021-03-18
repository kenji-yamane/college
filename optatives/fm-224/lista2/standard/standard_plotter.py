from math import sin, pi
import numpy as np
import matplotlib.pyplot as plt

def standard_func(x, y, a):
	return x + y, y + a*sin(x + y)

def plot_orbit(xi, yi, a, orbit_len):
	x, y = xi, yi

	for i in range(orbit_len):
		x, y = standard_func(x, y, a)
		if x < -pi:
			x += 2*pi
		if x > pi:
			x -= 2*pi
		if y < -pi:
			y += 2*pi
		if y > pi:
			y -= 2*pi

		horizontal.append(x)
		vertical.append(y)

horizontal = []
vertical = []

plot_orbit(0.5, 0.5, 7, 10000)

plt.plot(horizontal, vertical, ',')
plt.savefig('standard7.png')

