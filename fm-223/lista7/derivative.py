from math import atan
import matplotlib.pyplot as plt

horizontal = []
vertical = []

for i in range(17):
	dx = 10**(-i)
	horizontal.append(dx)
	vertical.append(abs(1/2 - (atan(1 + dx) - atan(1))/dx))

fig, ax = plt.subplots()

ax.plot(horizontal, vertical, '.')
plt.xlabel('dx')
plt.ylabel('E')
ax.set_xscale('log')
plt.savefig('derivative.jpg')

