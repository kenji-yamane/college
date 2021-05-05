import csv

def extract_from_file(filename):
	data = []
	with open("./src/logs/" + filename) as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			data.append(float(row[0]))
	return data

