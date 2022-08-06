import matplotlib.pyplot as plt

from utils import get_ssp_data

BASE_FIG_PATH = '../report/figures/ssp/'

algos = ['DD', 'PD', 'A2']
tests = ['AVIS', 'RAND', 'EVOD', 'P3', 'P4', 'P5']

print('input_size')
for algo in algos:
	for test in tests:
		bizarro_data = get_ssp_data(algo + '_' + test)
		print(bizarro_data['name'] + ':')
		print(bizarro_data['input_size'])

print()
print('num_true')
for test in tests:
	for algo in algos:
		bizarro_data = get_ssp_data(algo + '_' + test)
		print(bizarro_data['name'] + ':')
		print(bizarro_data['num_true'])

print()
print('num_trials')
for test in tests:
	for algo in algos:
		bizarro_data = get_ssp_data(algo + '_' + test)
		print(bizarro_data['name'] + ':')
		print(bizarro_data['num_trials'])

print()
print('exec_time')
for test in tests:
	for algo in algos:
		bizarro_data = get_ssp_data(algo + '_' + test)
		print(bizarro_data['name'] + ':')
		print(bizarro_data['exec_time'])
	print()

for test in tests:
	plt.figure()
	plt.title('Gerador ' + test)
	plt.xlabel('Tamanho do input')
	plt.ylabel('Tempo de execução')
	for algo in algos:
		bizarro_data = get_ssp_data(algo + '_' + test)
		plt.plot(bizarro_data['input_size'], bizarro_data['exec_time'], label=algo)
	plt.legend()
	plt.savefig(BASE_FIG_PATH + 'comp' + test + '.pdf')

for test in ['P4', 'P5']:
	plt.figure()
	plt.title('Gerador ' + test)
	plt.xlabel('Tamanho do input')
	plt.ylabel('Tempo de execução')
	for algo in ['DD', 'A2']:
		bizarro_data = get_ssp_data(algo + '_' + test)
		plt.plot(bizarro_data['input_size'], bizarro_data['exec_time'], label=algo)
	plt.legend()
	plt.savefig(BASE_FIG_PATH + 'compDDA2' + test + '.pdf')

for algo in algos:
	plt.figure()
	plt.title('Algoritmo ' + algo)
	plt.xlabel('Tamanho do input')
	plt.ylabel('Respostas positivas')
	for test in ['P3', 'P4', 'P5']:
		bizarro_data = get_ssp_data(algo + '_' + test)
		plt.plot(bizarro_data['input_size'], bizarro_data['num_true'], label=test)
	plt.legend()
	plt.savefig(BASE_FIG_PATH + 'compTrue' + algo + '.pdf')


