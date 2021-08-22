import csv
from math import sqrt
import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as optimize
import scipy.linalg as linalg

def henon_map(x):
	return np.array([1.276 - x[0]**2 + 0.3*x[1], x[0]])

def henon_map7(x):
	mapped = np.array(x)
	for i in range(7):
		mapped = henon_map(mapped)
	
	return mapped

largest = [0, 0]
with open('background_saddle.txt') as saddlefile:
	rows = csv.reader(saddlefile, delimiter=',')
	for row in rows:
		if float(row[1]) > largest[1]:
			largest[0], largest[1] = float(row[0]), float(row[1])

largest[0] += 0.01
largest[1] -= 0.01
fixed = optimize.fixed_point(henon_map7, largest, xtol=1e-7)#[-1.1, 1.6], xtol=1e-5)
#fixed = np.array(largest)

while fixed[0] > -1:
	fixed = henon_map(fixed)
interest_point = np.array(fixed)

f = open('periodic_saddle.txt', 'w')
for i in range(35):
	f.write(str(fixed[0]) + ', ' + str(fixed[1]) + '\n')
	fixed = henon_map(fixed)

eig_val, eig_vec = linalg.eig(np.array([[-2*interest_point[0], 0.3], [1, 0]]))
stable_man = np.array(eig_vec[:, 1])
stable_man /= 100

f2 = open('stable_manifold.txt', 'w')
p = np.array(interest_point)
while p[1] < 2:
	p += stable_man
print(p)
up = np.array(p)

p = np.array(interest_point)
while p[1] > -1.5:
	p -= stable_man
print(p)

p = np.array(up)
while p[1] > -1.5:
	p -= stable_man
	f2.write(str(p[0]) + ', ' + str(p[1]) + '\n')

