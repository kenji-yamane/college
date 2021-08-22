import csv
import matplotlib.pyplot as plt

def get_data(filename):
	horizontal = []
	vertical = []

	with open(filename) as csv_file:
		rows = csv.reader(csv_file, delimiter=',')
		for row in rows:
			horizontal.append(float(row[0]))
			vertical.append(float(row[1]))
	
	return horizontal, vertical

horizontal, vertical = get_data('stable_manifold.txt')
plt.plot(horizontal, vertical, 'r--')
horizontal, vertical = get_data('background_saddle.txt')
plt.plot(horizontal, vertical, 'm,')
horizontal, vertical = get_data('saddle.txt')
plt.plot(horizontal, vertical, 'c.')
horizontal, vertical = get_data('periodic_saddle.txt')
plt.plot(horizontal, vertical, 'k+', markersize=10)
plt.savefig('szabo.png')

