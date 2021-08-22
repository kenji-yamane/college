import numpy as np
import matplotlib.pyplot as plt

NUM_ORBITS = 5000
ORBIT_LENGHT = 100
DISCARDED = 100

# original
# x_interval = (0, 1)
# y_interval = (0, 1)

# zoom 1
# x_interval = (0, 0.6)
# y_interval = (0, 0.6)

# zoom 2
# x_interval = (0, 0.6)
# y_interval = (0.4, 1)

# zoom 3
x_interval = (0.4, 1)
y_interval = (0, 0.6)

def inside_box(x, y):
	if x > x_interval[0] and x < x_interval[1]:
		if y > y_interval[0] and y < y_interval[1]:
			return True
	
	return False

def iterated_function(x, y):
	p = np.random.uniform(0, 1)
	if p > 2/3:
		return x/2, y/2
	elif p > 1/3:
		return (1 + x)/2, y/2
	else:
		return x/2, (1 + y)/2

horizontal = []
vertical = []

for i in range(NUM_ORBITS):
	point_x = np.random.uniform(0, 1)
	point_y = np.random.uniform(0, 1)

	for j in range(DISCARDED):
		point_x, point_y = iterated_function(point_x, point_y)
	
	for j in range(ORBIT_LENGHT):
		point_x, point_y = iterated_function(point_x, point_y)
		if inside_box(point_x, point_y):
			horizontal.append(point_x)
			vertical.append(point_y)

fig, ax = plt.subplots()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

plt.plot(horizontal, vertical, ',')
plt.savefig('iterated_2d_zoom3.jpg')

