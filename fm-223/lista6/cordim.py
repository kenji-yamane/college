import csv
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt

horizontal = []
vertical = []

with open('corr.txt') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	for row in spamreader:
		horizontal.append(float(row[0]))
		vertical.append(float(row[1]))

x = np.array(horizontal)
y = np.array(vertical)
dim, C, r_value, p_value, err = stats.linregress(x, y)
print('dimensao:', dim, err)
print('C:', C)
print('r2:', r_value**2)
print('p:', p_value)
plt.plot(horizontal, vertical, 'r.')
plt.plot(np.linspace(-8, -2), dim*np.linspace(-8, -2) + C)
plt.savefig('cordim.jpg')

