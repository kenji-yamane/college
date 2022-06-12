import matplotlib.pyplot as plt
import numpy as np
from math import isclose
from data_grabber import grab_data

data = grab_data()
p, e3, e4, e6 = data['p'], data['e3'], data['e4'], data['e6']

lastBeforeIntersection = 0
for i in range(len(p) - 5):
	if np.argmax([e3[i], e4[i], e6[i]]) > 0:
		lastBeforeIntersection = i

p = p[0:lastBeforeIntersection + 2]
e3 = e3[0:lastBeforeIntersection + 2]
e4 = e4[0:lastBeforeIntersection + 2]
e6 = e6[0:lastBeforeIntersection + 2]

plt.figure()
plt.loglog(p, p)
plt.loglog(p, e3)
plt.loglog(p, e4)
plt.loglog(p, e6)
plt.legend(['p', 'e3', 'e4', 'e6'])
plt.gca().invert_xaxis()
plt.savefig('intersection.png')

