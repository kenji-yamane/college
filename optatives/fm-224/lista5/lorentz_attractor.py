import numpy as np
import matplotlib.pyplot as plt

from utils import extract_three_from_file

x, y, z = extract_three_from_file("lorentz_attractor.txt")

plt.figure()
plt.plot(x, y, ',')
plt.savefig('lorentz/attractor_xy.eps')

plt.figure()
plt.plot(x, z, ',')
plt.savefig('lorentz/attractor_xz.eps')

plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x, y, z, ',')
plt.savefig('lorentz/attractor.eps')

x1, y1, z1 = extract_three_from_file("lorentz_cycle.txt")

plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x, y, z, ',')
ax.plot3D(x1, y1, z1)
plt.savefig('lorentz/leafs_cycle.eps')

plt.figure()
ax = plt.axes(projection='3d')
left = 40
right = left + len(x1)//2
ax.plot3D(x, y, z, ',')
ax.plot3D(x1[left:right], y1[left:right], z1[left:right])
plt.savefig('lorentz/leaf_cycle.eps')

