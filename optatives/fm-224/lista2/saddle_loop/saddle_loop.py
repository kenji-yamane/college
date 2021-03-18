import numpy as np
from math import sqrt
import matplotlib.pyplot as plt

MU = None
STEP = 0.001
edo_fund = None

def eigen_values():
	return (MU - sqrt(MU**2 + 4))/2, (MU + sqrt(MU**2 + 4))/2

def edo_func_normal(x):
	return np.array([x[1], MU*x[1] + x[0] - x[0]**2 + x[0]*x[1]])

def edo_func_reversal(x):
	return np.array([-x[1], -MU*x[1] - x[0] + x[0]**2 - x[0]*x[1]])

def runge_kutta_step(x):
	k1 = STEP*edo_func(x)
	k2 = STEP*edo_func(x + k1/2)
	k3 = STEP*edo_func(x + k2/2)
	k4 = STEP*edo_func(x + k3)

	return np.array(x + k1/6 + k2/3 + k3/3 + k4/6)

def plot_orbit(initial_point, orbit_length):
	point = initial_point
	for i in range(orbit_length):
		point = runge_kutta_step(point)
		horizontal.append(point[0])
		vertical.append(point[1])

fig = plt.figure()
ax = fig.add_subplot()
ax.spines['left'].set_position(('data', 0))
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position(('data', 0))
ax.spines['top'].set_color('none')

#MU = -0.8645
#eigen1, eigen2 = eigen_values()
#unstable_eigen = max(eigen1, eigen2)
#stable_eigen = min(eigen1, eigen2)

#horizontal, vertical = [], []

#edo_func = edo_func_normal
#plot_orbit(np.array([1, unstable_eigen])/1000, 20000)
#plot_orbit(np.array([-1, -unstable_eigen])/1000, 11000)

#edo_func = edo_func_reversal
#plot_orbit(np.array([-1, -stable_eigen])/1000, 4100)
#plot_orbit(np.array([300, stable_eigen])/1000, 30000) # dislodged

#plt.plot(horizontal, vertical, ',')
#plt.savefig('sl_MU.pdf')
#ax.clear()

#MU = -0.8
#eigen1, eigen2 = eigen_values()
#unstable_eigen = max(eigen1, eigen2)
#stable_eigen = min(eigen1, eigen2)

#horizontal, vertical = [], []

#edo_func = edo_func_normal
#plot_orbit(np.array([1, unstable_eigen])/1000, 17000)
#plot_orbit(np.array([-1, -unstable_eigen])/1000, 11000)

#edo_func = edo_func_reversal
#plot_orbit(np.array([-1, -stable_eigen])/1000, 4300)
#plot_orbit(np.array([1, stable_eigen])/1000, 20000)

#plt.plot(horizontal, vertical, ',')
#plt.savefig('sl_more_MU.pdf')
#ax.clear()

MU = -0.9
eigen1, eigen2 = eigen_values()
unstable_eigen = max(eigen1, eigen2)
stable_eigen = min(eigen1, eigen2)

horizontal, vertical = [], []

edo_func = edo_func_normal
plot_orbit(np.array([1.3, 0]), 30000)

plot_orbit(np.array([1, unstable_eigen])/1000, 20000)
plot_orbit(np.array([-1, -unstable_eigen])/1000, 11000)

edo_func = edo_func_reversal
plot_orbit(np.array([-1, -stable_eigen])/1000, 4100)
plot_orbit(np.array([1, stable_eigen])/1000, 10800)

plt.plot(horizontal, vertical, ',')
plt.savefig('sl_less_MU.pdf')
fig.clear()

#MU = -0.87
#eigen1, eigen2 = eigen_values()
#unstable_eigen = max(eigen1, eigen2)
#stable_eigen = min(eigen1, eigen2)

#horizontal, vertical = [], []

#edo_func = edo_func_normal
#plot_orbit(np.array([1.4, 0]), 36000)

#plot_orbit(np.array([1, unstable_eigen])/1000, 20000)
#plot_orbit(np.array([-1, -unstable_eigen])/1000, 11000)

#edo_func = edo_func_reversal
#plot_orbit(np.array([-1, -stable_eigen])/1000, 4100)
#plot_orbit(np.array([1, stable_eigen])/1000, 12000)

#ax.plot(horizontal, vertical, ',')
#plt.savefig('sl_almost_MU.pdf')
#fig.clear()

