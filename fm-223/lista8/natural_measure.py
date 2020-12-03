import numpy as np
from math import sqrt
import matplotlib.pyplot as plt

NUM_BINS = 100
ORBIT_LEN = 300000000
CUTS = 1

def natural_measure(func, start, end):
	bin_length = (end - start)/NUM_BINS
	bins = np.zeros(NUM_BINS)
	orbit_point = (start + end)/2
	orbit_point = (start + orbit_point)/2
	orbit_point = (start + orbit_point)/2

	for i in range(ORBIT_LEN):
		orbit_point = func(orbit_point)
		
		to_start = orbit_point - start
		to_bins = int(to_start/bin_length)
		bins[to_bins] = bins[to_bins] + 1
	
	bins /= ORBIT_LEN # natural measure
	bins /= bin_length # invariant measure

	return bins

def critical_map(x):
	c = 1 - sqrt(2)/2
	if x < c:
		return 2 + sqrt(2)*(x - 1)
	else:
		return sqrt(2)*(1 - x)

def logistic_map(x):
	return 4*x*(1 - x)

x = np.linspace(0, 1, NUM_BINS)
y = natural_measure(critical_map, 0, 1)
x = x[CUTS:-CUTS]
y = y[CUTS:-CUTS]
plt.ylim(0, 2.5)
plt.plot(x, y, '.')
plt.savefig('critical_measure.jpg')

