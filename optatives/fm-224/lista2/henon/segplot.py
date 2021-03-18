import matplotlib.pyplot as plt
import numpy as np
import csv

stable_horizontal = []
stable_vertical = []

with open('stable.txt') as csvfile:
	csv_reader = csv.reader(csvfile, delimiter=',')
	
	for row in csv_reader:
		stable_horizontal.append(float(row[0]))
		stable_vertical.append(float(row[1]))

unstable_horizontal = []
unstable_vertical = []

with open('unstable.txt') as csvfile:
	csv_reader = csv.reader(csvfile, delimiter=',')
	
	for row in csv_reader:
		unstable_horizontal.append(float(row[0]))
		unstable_vertical.append(float(row[1]))

plt.plot(stable_horizontal, stable_vertical, ',b')
plt.plot(unstable_horizontal, unstable_vertical, ',r')
plt.savefig('b_more.png')

