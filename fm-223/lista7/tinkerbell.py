import numpy as np
import matplotlib.pyplot as plt

ORBIT_LENGTH = 1000000
DISCARDED_POINTS = 100

def tinkerbell_map(x, y, c4):
	return x**2 - y**2 - 0.3*x - 0.6*y, 2*x*y + 2*x + c4*y

horizontal = []
vertical = []

x_travel = 0.1
y_travel = 0.1

for i in range(ORBIT_LENGTH):
	x_travel, y_travel = tinkerbell_map(x_travel, y_travel, 0.7)
	if i > DISCARDED_POINTS:
		horizontal.append(x_travel)
		vertical.append(y_travel)
        
plt.plot(horizontal, vertical, ',')
plt.savefig('./tinkerbell/bigger.jpg')

