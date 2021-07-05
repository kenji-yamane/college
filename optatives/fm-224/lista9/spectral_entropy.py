import matplotlib.pyplot as plt
from scipy.fftpack import rfft, fftfreq
from math import pi
import numpy as np
import csv

time = np.arange(0, 100, 0.01)
space = np.arange(0, 1024, 1)
z = []
with open("complete_kuramoto.txt") as csvfile:
	rows = csv.reader(csvfile, delimiter=",")
	i = 0
	z_row = []
	for row in rows:
		if i >= 1024:
			i = 0
			z.append(list(z_row))
			z_row.clear()

		z_row.append(float(row[0]))
		i += 1

averaged_psd = np.zeros(len(z[0]))
freqs = fftfreq(len(z[0]), d = 2*pi/536)
for z_row in z:
	z_row = np.array(z_row)
	z_row = z_row - np.mean(z_row)
	psd = rfft(z_row)
	for k in range(len(averaged_psd)):
		averaged_psd[k] += psd[k]/10000

fig, ax = plt.subplots(1, 1)
ax.plot(freqs, averaged_psd**2)
ax.set_xlabel(r'$k$')
ax.set_ylabel(r'$|\hat{u}|^2$')
plt.show()

tot = np.sum(averaged_psd**2)
probs = averaged_psd**2/tot
for prob in probs:
	if abs(prob) < 0.00001:
		prob = 1
print(-np.dot(probs, np.log(probs)))

