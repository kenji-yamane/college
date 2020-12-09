import csv
import numpy as np
import matplotlib.pyplot as plt

horizontal = []
vertical = []

with open('diagram.txt') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	for row in spamreader:
		#if (float(row[1]) > 0.4 and float(row[1]) < 0.6):
		horizontal.append(float(row[0]))
		vertical.append(float(row[1]))

fig, ax = plt.subplots()
plt.xlabel(r'$\nu$')
plt.ylabel('$b_z$')
#plt.xlim([0.014, 0.024])
#plt.ylim([-1.82, 1.32])
ax.plot(horizontal, vertical, ',k')
plt.show()

