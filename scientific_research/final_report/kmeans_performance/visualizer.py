import csv
import matplotlib.pyplot as plt

plt.figure()
plt.grid()

horizontal = []
vertical = []
count = 1
with open('kmeans.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		if count > 27:
			vertical.append(float(row[0]))
			horizontal.append(count - 27)
plt.plot(horizontal, vertical, linewidth=2)

horizontal = []
vertical = []
count = 1
with open('retinex.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		if count > 15:
			vertical.append(float(row[0]))
			horizontal.append(count - 15)
plt.plot(horizontal, vertical, linewidth=2)

horizontal = []
vertical = []
count = 1
with open('normal.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		if count > 44:
			vertical.append(float(row[0]))
			horizontal.append(count - 44)
plt.plot(horizontal, vertical, linewidth=2)

plt.xlabel('Ciclo')
plt.ylabel('Pixels amarelos')
plt.legend(['KMeans', 'Retinex', 'Natural'])
plt.savefig('comparison_fat.png', format='png', dpi=400)

