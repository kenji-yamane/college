import numpy as np
import matplotlib.pyplot as plt

NUM_ORBITS = 5000
ORBIT_LENGHT = 100
DISCARDED = 100

# original
interval = (0, 1)
# zoom 1
# interval = (0, 1/3)
# zoom 2
# interval = (2/9, 1/3)
# zoom 3
# interval = (2/9, 7/27)

def cantor_map(x):
	if np.random.uniform(0, 1) > 0.5:
		return x + (1 - x)*2/3
	else:
		return x + (0 - x)*2/3

points = []

for i in range(NUM_ORBITS):
	point = np.random.uniform(0, 1)
	for j in range(DISCARDED):
		point = cantor_map(point)
	
	for j in range(ORBIT_LENGHT):
		point = cantor_map(point)
		if point > interval[0] and point < interval[1]:
			points.append(point)

fig, ax = plt.subplots()
fig.set_figheight(2)
fig.set_figwidth(4)
ax.spines['left'].set_color('none')
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

plt.yticks([])
plt.plot(np.array(points), np.zeros(len(points)), ',')
plt.savefig('iterated_1d_zoom3.jpg')

