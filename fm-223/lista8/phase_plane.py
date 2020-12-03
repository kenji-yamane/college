import numpy as np
from math import cos, sin, pi
import matplotlib.pyplot as plt

TRAJECTORY_LENGTH = 10000
TIME_STEP = 0.001
ARROW_RESOLUTION = 0.0004
ARROW_STEP = 1000

def rotation_mtx(theta):
	row_1 = [cos(theta), -sin(theta)]
	row_2 = [sin(theta), cos(theta)]

	return np.array([row_1, row_2])

def ode_law(x):
	return np.array([x[1], x[1] - x[1]*x[0]**2 - x[0]])

def runge_kutta_step(x):
	x1 = TIME_STEP*ode_law(x)
	x2 = TIME_STEP*ode_law(x + x1/2)

	return x + x2

horizontal = []
vertical = []

def draw_arrow(point, direction):
	original_point = np.array(point)
	direction /= np.linalg.norm(direction)

	end_1 = np.matmul(rotation_mtx(3*pi/4), direction)
	end_2 = np.matmul(rotation_mtx(-3*pi/4), direction)

	for i in range(100):
		point += end_1*ARROW_RESOLUTION
		horizontal.append(point[0])
		vertical.append(point[1])
	
	point = original_point
	for i in range(100):
		point += end_2*ARROW_RESOLUTION
		horizontal.append(point[0])
		vertical.append(point[1])

initial_points = []
for i in range(10):
	initial_points.append(np.array([0, i/10 + 0.1]))
	initial_points.append(np.array([0, -i/10 - 0.1]))

for orbit_point in initial_points:
	direction = ode_law(orbit_point)
	arrows = 0

	for j in range(TRAJECTORY_LENGTH):
		if arrows == ARROW_STEP:
			direction = ode_law(orbit_point)
			draw_arrow(np.array(orbit_point), direction)
			arrows = 0
		orbit_point = runge_kutta_step(orbit_point)

		horizontal.append(orbit_point[0])
		vertical.append(orbit_point[1])

		arrows += 1

fig, ax = plt.subplots()
ax.spines['left'].set_position('center')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('center')
ax.spines['top'].set_color('none')

ax.plot(horizontal, vertical, 'k,')
plt.savefig('van_der_pol_in.jpg')

