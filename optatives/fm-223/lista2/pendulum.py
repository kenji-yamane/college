import numpy as np
import matplotlib.pyplot as plt
from math import sin, cos, pi

def differential_equation(angle, velocity, time):
	"""
		Given the inputs, returns its respective differentials
		:param angle: angle the line makes with the vertical
		:type angle: float
		:param velocity: velocity of the mass, in radians per sec
		:type velocity: float
		:param time: time that passed
		:type time: float
	"""

	return velocity, -0.05*velocity - sin(angle) + 2.5*cos(time)

def runge_kutta(angle, velocity, time, step):
	"""
		Makes a step in runge kutta's algorithm to solving ODE
		:param angle: angle the line makes with the vertical
		:type angle: float
		:param velocity: velocity of the mass, in radians per sec
		:type velocity: float
		:param time: time that passed
		:type time: float
	"""

	k1_angle, k1_velocity = differential_equation(angle, velocity, time)
	k2_angle, k2_velocity = differential_equation(angle + step*k1_angle/2, velocity + step*k1_velocity/2, time + step/2)
	k3_angle, k3_velocity = differential_equation(angle + step*k2_angle/2, velocity + step*k2_velocity/2, time + step/2)
	k4_angle, k4_velocity = differential_equation(angle + step*k3_angle, velocity + step*k3_velocity, time + step)

	new_angle = angle + step*k1_angle/6 + step*k2_angle/3 + step*k3_angle/3 + step*k4_angle/6
	new_velocity = velocity + step*k1_velocity/6 + step*k2_velocity/3 + step*k3_velocity/3 + step*k4_velocity/6
	
	return new_angle, new_velocity

angle = np.random.uniform(-pi, pi)
velocity = np.random.uniform(-3, 4)
time = 0
horizontal = []
vertical = []

for i in range(500000):
	horizontal += [angle%(2*pi) - pi]
	vertical += [velocity]
	for j in range(60):
		angle, velocity = runge_kutta(angle, velocity, time, pi/30)
		time += pi/30

plt.plot(horizontal, vertical, ',')
plt.savefig('pendulum_orbit.jpg')

