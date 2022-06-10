import matplotlib.pyplot as plt
import csv

f = open('data.csv')
csvreader = csv.reader(f)

p = []
e3 = []
e4 = []
e6 = []
for row in csvreader:
	p.append(float(row[0]))
	e3.append(float(row[1]))
	e4.append(float(row[2]))
	e6.append(float(row[3]))


plt.figure()
plt.loglog(p, p)
plt.loglog(p, e3)
plt.loglog(p, e4)
plt.loglog(p, e6)
plt.legend(['p', 'e3', 'e4', 'e6'])
plt.gca().invert_xaxis()
plt.savefig('perror.png')

