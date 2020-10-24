import numpy as np
import matplotlib.pyplot as plt
import cmath

HORIZONTAL_PRECISION = 3000
VERTICAL_PRECISION = 3000
UNSTABLE_CHECK_ITERATIONS = 50
IS_UNSTABLE = 100

x_domain = np.linspace(-1.5, 1, HORIZONTAL_PRECISION)
y_domain = np.linspace(-1.5, 1, VERTICAL_PRECISION)

horizontal = []
vertical = []

for x in x_domain:
	for y in y_domain:
		z = complex(0, 0)
		c = complex(x, y)
		
		for i in range(0, UNSTABLE_CHECK_ITERATIONS):
			z = z*z + c

		if abs(z) < IS_UNSTABLE:
			horizontal.append(x)
			vertical.append(y)

plt.plot(horizontal, vertical, 'k,')
plt.savefig('mandelbrot.jpg')

