import csv

def extract_from_file(filename):
	data = []
	with open("./src/logs/" + filename) as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			data.append(float(row[0]))
	return data

def extract_three_from_file(filename):
	first, second, third = [], [], []
	with open("./src/logs/" + filename) as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			first.append(float(row[0]))
			second.append(float(row[1]))
			third.append(float(row[2]))
	return first, second, third

