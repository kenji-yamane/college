import csv


def grab_data():
	f = open('../build/data.csv')
	csvreader = csv.reader(f)

	data = {}
	labels = ['p', 'e3', 'e4', 'e6']
	for l in labels:
		data[l] = []
	for row in csvreader:
		for i in range(4):
			data[labels[i]].append(float(row[i]))
	return data

