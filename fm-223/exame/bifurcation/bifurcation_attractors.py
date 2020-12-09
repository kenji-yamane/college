import csv
import numpy as np
import matplotlib.pyplot as plt

horizontal = []
vertical = []

for i in range(4):
	with open('diagrams/diagram_A' + str(i + 1) + '.txt') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		hor = []
		ver = []
		for row in spamreader:
			if float(row[0]) > 0.0165 and float(row[0]) < 0.0175:
				hor.append(float(row[0]))
				ver.append(float(row[1]))
		horizontal.append(hor)
		vertical.append(ver)

fig, ax = plt.subplots()
plt.xlabel(r'$\nu$')
plt.ylabel('$b_z$')
ax.plot(horizontal[0], vertical[0], ',m')
ax.plot(horizontal[1], vertical[1], ',b')
ax.plot(horizontal[2], vertical[2], ',g')
ax.plot(horizontal[3], vertical[3], ',r')
ax.plot([], [], '-m', label='A1')
ax.plot([], [], '-b', label='A2')
ax.plot([], [], '-g', label='A3')
ax.plot([], [], '-r', label='A4')
ax.legend()
plt.savefig('attractors_zoom.jpg')

