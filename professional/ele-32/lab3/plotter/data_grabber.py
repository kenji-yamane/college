import csv


def grab_test_data():
	f = open('viterbi-euclidian.csv')
	csvreader = csv.reader(f)

	data = {}
	labels = ['p', 'e']
	for l in labels:
		data[l] = []
	for row in csvreader:
		for i in range(2):
			data[labels[i]].append(float(row[i]))
	return data

def grab_space_comparation_data(viterbi='hamming'):
	file_dict = {
		'hamming': 'viterbi-hamming.csv',
		'euclidian': 'viterbi-euclidian.csv',
		'logprob': 'viterbi-logprob.csv'
	}
	f = open(file_dict[viterbi])
	csvreader = csv.reader(f)

	data = {}
	labels = ['p', 'e3', 'e4', 'e6']
	for l in labels:
		data[l] = []
	for row in csvreader:
		for i in range(4):
			data[labels[i]].append(float(row[i]))
	return data

def grab_cost_comparation_data():
	hamming = grab_space_comparation_data('hamming')
	euclidian = grab_space_comparation_data('euclidian')
	logprob = grab_space_comparation_data('logprob')

	data = {
		'euclidian': euclidian,
		'hamming': hamming,
		'logprob': logprob
	}
	return data

