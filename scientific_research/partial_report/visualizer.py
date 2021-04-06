import csv
import matplotlib.pyplot as plt

plt.figure()
plt.grid()

horizontal = []
vertical = []
count = 1
with open('./itandroids-vss/logging/withResponse.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		if len(row) > 0 and count > 50 and count < 115:
			vertical.append(float(row[0]))
			horizontal.append(count - 50)

plt.plot(horizontal, vertical, linewidth=2)

horizontal = []
vertical = []
count = 1
with open('./itandroids-vss/logging/withoutResponse.log') as csvfile:
	rows = csv.reader(csvfile, delimiter=',')
	for row in rows:
		count += 1
		if len(row) > 0 and count > 225 and count < 290:
			vertical.append(float(row[0]))
			horizontal.append(count - 225)

plt.plot(horizontal, vertical, linewidth=2)
plt.xlabel('Ciclo')
plt.ylabel('Pixels vermelhos')
plt.legend(['Com Retinex', 'Sem Retinex'])
plt.savefig('comparation.png', format='png', dpi=400)

