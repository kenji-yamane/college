import csv
import matplotlib.pyplot as plt

for data in ['stable', 'unstable', 'saddle']:
	with open(data + '.txt') as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=',')
		
		horizontal, vertical = [], []
	
		for row in csv_reader:
			horizontal.append(float(row[0]))
			vertical.append(float(row[1]))
		
		plt.cla()
		plt.plot(horizontal, vertical, ',')
		plt.savefig(data + '.png')

delim = ['r,', 'g,', 'b,']
i = 0
for data in ['stable', 'unstable', 'saddle']:
	with open(data + '.txt') as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=',')
		
		horizontal, vertical = [], []
	
		for row in csv_reader:
			horizontal.append(float(row[0]))
			vertical.append(float(row[1]))
		
		plt.plot(horizontal, vertical, delim[i])
	i += 1
plt.savefig('all.png')

with open('saddle.txt') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	
	horizontal, vertical = [], []

	for row in csv_reader:
		if 0.1 < float(row[0]) < 0.7 and 0.7 < float(row[1]) < 1.3:
			horizontal.append(float(row[0]))
			vertical.append(float(row[1]))
	
	plt.cla()
	plt.plot(horizontal, vertical, ',')
	plt.savefig('zoom.png')

