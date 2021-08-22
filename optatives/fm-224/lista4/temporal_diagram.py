import csv
import matplotlib.pyplot as plt

time_A1 = []
orbit_A1 = []

time_A3 = []
orbit_A3 = []

time_A6 = []
orbit_A6 = []

with open('diagram.txt') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		if float(row[2]) == 0:
			time_A1.append(float(row[0]))
			orbit_A1.append(float(row[1]))

		if float(row[2]) == 1:
			time_A3.append(float(row[0]))
			orbit_A3.append(float(row[1]))

		if float(row[2]) == 2:
			time_A6.append(float(row[0]))
			orbit_A6.append(float(row[1]))

plt.figure()
plt.plot(time_A1, orbit_A1, ',k')
plt.plot(time_A3, orbit_A3, '^y')
plt.plot(time_A6, orbit_A6, 'sg')
plt.xlabel('t')
plt.ylabel('$b_z$')
plt.savefig('temporal_diagram.png')

