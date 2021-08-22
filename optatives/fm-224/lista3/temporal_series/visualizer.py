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

horizontal, vertical = get_data('registry.txt')
plt.plot(horizontal, vertical, '.')
plt.xlabel('ciclo')
plt.ylabel('x')
plt.savefig('after_crisis.png')

