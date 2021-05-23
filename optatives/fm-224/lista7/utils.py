import csv
import numpy as np

def extract_from_file(filename):
	data = []
	with open("./data/" + filename) as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			data.append(float(row[0]))
	return data

def stats_moment(data, order):
	return np.sum((data - np.mean(data))**order)/len(data)

