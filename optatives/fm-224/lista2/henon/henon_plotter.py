import numpy as np
import matplotlib.pyplot as plt
import csv

def is_in_range(x, y):
	return -2.5 <= x <= 5 and -2.5 <= y <= 5

def henon(x, y, b):
	return -0.75 - x**2 + b*y, x

def make_orbit(x, y, orbit_size, func):
	for i in range(orbit_size):
		x, y = func(x, y)

		if not is_in_range(x, y):
			break

		horizontal.append(x)
		vertical.append(y)

horizontal = []
vertical = []

x_initial = np.linspace(-1.5, -0.5, 30)

for xi in x_initial:
	make_orbit(xi, xi, 1000, lambda x, y: henon(x, y, -1))

stable_horizontal = []
stable_vertical = []

with open('stable.txt') as csvfile:
	csv_reader = csv.reader(csvfile, delimiter=',')
	
	for row in csv_reader:
		stable_horizontal.append(float(row[0]))
		stable_vertical.append(float(row[1]))

unstable_horizontal = []
unstable_vertical = []

with open('unstable.txt') as csvfile:
	csv_reader = csv.reader(csvfile, delimiter=',')
	
	for row in csv_reader:
		unstable_horizontal.append(float(row[0]))
		unstable_vertical.append(float(row[1]))

plt.plot(stable_horizontal, stable_vertical, ',b')
plt.plot(unstable_horizontal, unstable_vertical, ',r')
plt.plot(horizontal, vertical, ',g')
plt.savefig('b_one.png')

