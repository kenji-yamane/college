import matplotlib.pyplot as plt
import numpy as np
import subprocess
import csv

time = np.arange(0, 100, 0.01)
space = np.arange(0, 50, 1)
z = []
with open("kuramoto_out.txt") as csvfile:
	rows = csv.reader(csvfile, delimiter=",")
	i = 0
	z_row = []
	for row in rows:
		if i >= 50:
			i = 0
			z.append(list(z_row))
			z_row.clear()

		z_row.append(float(row[0]))
		i += 1

fig, ax = plt.subplots(1, 1)
cp = ax.contourf(time, space, np.array(z).transpose())
fig.colorbar(cp)
ax.set_xlabel(r'$t$')
ax.set_ylabel(r'$\frac{x}{\Delta x}$')
plt.show()
#plt.savefig("./figures/1d.png")

