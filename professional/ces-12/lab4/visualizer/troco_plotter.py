import matplotlib.pyplot as plt

from utils import get_troco_data

BASE_FIG_PATH = '../report/figures/troco/'

# comparison between the three algorithms
greedy = get_troco_data('GR_BR200')
dynamic_programming = get_troco_data('PD_BR200')
divide_and_conquer = get_troco_data('DC40')

for algo in [greedy, dynamic_programming, divide_and_conquer]:
	plt.figure()
	plt.title('Tempo de execução ' + algo['name'])
	plt.xlabel('Troco')
	plt.ylabel('Tempo')
	plt.plot(algo['change'], algo['exec_time'])
	plt.savefig(BASE_FIG_PATH + algo['name'] + 'exec.pdf')
	
	plt.figure()
	plt.title('Número de moedas ' + algo['name'])
	plt.xlabel('Troco')
	plt.ylabel('Número')
	plt.plot(algo['change'], algo['num_coins'], 'r')
	plt.savefig(BASE_FIG_PATH + algo['name'] + 'found.pdf')

# comparing PD and GR
algo1 = get_troco_data('GR_GRLoses')
algo2 = get_troco_data('PD_GRLoses')

plt.figure()
plt.title('Comparando PD e GR')
plt.xlabel('Troco')
plt.ylabel('Tempo')
plt.plot(algo1['change'], algo1['exec_time'], label='GR')
plt.plot(algo2['change'], algo2['exec_time'], label='PD')
plt.legend()
plt.savefig(BASE_FIG_PATH + 'GR_loses' + 'exec.pdf')

plt.figure()
plt.title('Comparando PD e GR')
plt.xlabel('Troco')
plt.ylabel('Número de moedas')
plt.plot(algo1['change'], algo1['num_coins'], label='GR')
plt.plot(algo2['change'], algo2['num_coins'], '.--', label='PD')
plt.legend()
plt.savefig(BASE_FIG_PATH + 'GR_loses' + 'found.pdf')

