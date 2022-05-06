import csv
import matplotlib.pyplot as plt

plt.figure()
plt.grid()

horizontal = []
vertical = []
count = 1
with open('hue.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		vertical.append(abs(float(row[0])))
		horizontal.append(count)
plt.plot(horizontal, vertical, linewidth=2)

horizontal = []
vertical = []
count = 1
with open('value.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		vertical.append(abs(float(row[0])))
		horizontal.append(count)
plt.plot(horizontal, vertical, linewidth=2)

horizontal = []
vertical = []
count = 1
with open('saturation.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		vertical.append(abs(float(row[0])))
		horizontal.append(count)
plt.plot(horizontal, vertical, linewidth=2)

plt.xlabel('Ciclo')
plt.ylabel('Variação')
plt.legend(['Hue', 'Value', 'Saturation'])
plt.savefig('comparation.png', format='png', dpi=400)

