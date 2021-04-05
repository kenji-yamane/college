import csv
import numpy as np
from scipy.stats import linregress
import matplotlib.pyplot as plt

number_of_points = []
search_time_stl = []
search_time_rb = []
insertion_time_stl = []
insertion_time_rb = []

with open('../build/oak_search.csv') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')

	for row in rows:
		if float(row[2]) < 0.01 and float(row[3]) < 0.01:
			number_of_points.append(float(row[1]))
			search_time_stl.append(float(row[2]))
			search_time_rb.append(float(row[3]))
			insertion_time_stl.append(float(row[4]))
			insertion_time_rb.append(float(row[5]))

plt.figure()
plt.plot(number_of_points, search_time_stl, '.', number_of_points, search_time_rb, '.')

slope, intercept, r, p, _ = linregress(np.log(number_of_points), np.array(search_time_stl))
x = np.linspace(0.1, max(number_of_points))
plt.plot(x, slope*np.log(x) + intercept)
print(slope, intercept)

slope, intercept, r, p, _ = linregress(np.log(number_of_points), np.array(search_time_rb))
x = np.linspace(0.1, max(number_of_points))
plt.plot(x, slope*np.log(x) + intercept)

plt.title('tempo de procura')
plt.legend(['stl', 'implementada'])
plt.xlabel('N')
plt.ylabel('tempo')
plt.savefig('search_time.png')

plt.figure()
plt.plot(number_of_points, insertion_time_stl, '.', number_of_points, insertion_time_rb, '.')

slope, intercept, r, p, _ = linregress(np.log(number_of_points), np.array(insertion_time_stl))
x = np.linspace(0.1, max(number_of_points))
plt.plot(x, slope*np.log(x) + intercept)

slope, intercept, r, p, _ = linregress(np.log(number_of_points), np.array(insertion_time_rb))
x = np.linspace(0.1, max(number_of_points))
plt.plot(x, slope*np.log(x) + intercept)

plt.title('tempo de insercao')
plt.legend(['stl', 'implementada'])
plt.xlabel('N')
plt.ylabel('tempo')
plt.savefig('insertion_time.png')

