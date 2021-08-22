import csv

TROCO_BASE_PATH = '../build/troco_'
SSP_BASE_PATH = '../build/SSP_Tests_Timed_'


def get_troco_data(filename):
	bizarro_data = {}
	change, exec_time, num_coins, rec_calls = [], [], [], []

	with open(TROCO_BASE_PATH + filename + '.csv') as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			if float(row[0]) >= 0:
				change.append(float(row[0]))
				exec_time.append(float(row[1]))
				num_coins.append(float(row[2]))
				rec_calls.append(float(row[3]))
			else:
				bizarro_data['total_time'] = float(row[1])
	
	bizarro_data['name'] = filename[0:2]
	bizarro_data['change'] = change
	bizarro_data['exec_time'] = exec_time
	bizarro_data['num_coins'] = num_coins
	bizarro_data['rec_calls'] = rec_calls
	
	return bizarro_data

def get_ssp_data(filename):
	bizarro_data = {}
	input_size, exec_time, num_true, num_trials = [], [], [], []

	with open(SSP_BASE_PATH + filename + '.dat') as csvfile:
		rows = csv.reader(csvfile, delimiter=',')
		for row in rows:
			input_size.append(float(row[0]))
			exec_time.append(float(row[1]))
			num_true.append(float(row[2]))
			num_trials.append(float(row[3]))
	
	bizarro_data['name'] = filename
	bizarro_data['input_size'] = input_size
	bizarro_data['exec_time'] = exec_time
	bizarro_data['num_true'] = num_true
	bizarro_data['num_trials'] = num_trials
	
	return bizarro_data

