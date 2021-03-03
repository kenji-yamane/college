import numpy as np

lesser = 1e-20
bigger = 1

NUM_ITERATIONS = 100

for i in range(NUM_ITERATIONS):
	middle = (lesser + bigger)/2

	if 1 + middle == 1:
		lesser = middle
	else:
		bigger = middle

print(bigger)
print(np.finfo(float).eps)

