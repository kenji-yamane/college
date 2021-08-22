import matplotlib.pyplot as plt
from scipy.fftpack import rfft, fftfreq
from math import pi
import numpy as np
import csv
import subprocess

time = np.arange(0, 100, 0.1)
space = np.arange(0, 1024, 1)

spectral_entropy = 0
while abs(spectral_entropy - 4.4) > 0.05:
	proc = subprocess.call("./a.out")
	z = []
	times = []
	time = None
	with open("complete_kuramoto.txt") as csvfile:
		rows = csv.reader(csvfile, delimiter=",")
		i = 0
		z_row = []
		for row in rows:
			if i >= 1024:
				i = 0
				z.append(list(z_row))
				times.append(float(time))
				z_row.clear()
	
			time = float(row[1])
			z_row.append(float(row[0]))
			i += 1
	
	averaged_psd = np.zeros(len(z[0]))
	freqs = fftfreq(len(z[0]), d = 2*pi/536)
	i = 0
	for z_row in z:
		z_row = np.array(z_row)
		z_row = z_row - np.mean(z_row)
		psd = rfft(z_row)
		for k in range(len(averaged_psd)):
			averaged_psd[k] += psd[k]/times[i]
		i += 1
	
	tot = np.sum(averaged_psd**2)
	probs = averaged_psd**2/tot
	for prob in probs:
		if abs(prob) < 0.00001:
			prob = 1
	spectral_entropy = -np.dot(probs, np.log(probs))
	print(spectral_entropy)

