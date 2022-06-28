import matplotlib.pyplot as plt
import numpy as np
from math import isclose
from data_grabber import grab_space_comparation_data

data = grab_space_comparation_data()
p, e3, e4, e6 = data['p'], data['e3'], data['e4'], data['e6']

lastBeforeIntersection = 0
for i in range(len(p) - 5):
	if np.argmax([e3[i], e4[i], e6[i]]) == 0:
		lastBeforeIntersection = i

p = p[lastBeforeIntersection - 2:len(p)]
e3 = e3[lastBeforeIntersection - 2:len(e3)]
e4 = e4[lastBeforeIntersection - 2:len(e4)]
e6 = e6[lastBeforeIntersection - 2:len(e6)]

plt.figure()
plt.grid()
plt.loglog(p, p)
plt.loglog(p, e3)
plt.loglog(p, e4)
plt.loglog(p, e6)
plt.xlabel('$p$')
plt.ylabel('$p_e$')
plt.legend(['p', 'm = 3', 'm = 4', 'm = 6'])
plt.gca().invert_xaxis()
plt.savefig('intersection.png', dpi=400)

