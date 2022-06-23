import matplotlib.pyplot as plt
from data_grabber import grab_cost_comparation_data

space = 'e6'
data = grab_cost_comparation_data()
p_hamming, e_hamming = data['hamming']['p'], data['hamming'][space]
p_euclidian, e_euclidian = data['euclidian']['p'], data['euclidian'][space]
p_logprob, e_logprob = data['logprob']['p'], data['logprob'][space]


plt.figure()
plt.loglog(p_hamming, p_hamming)
plt.loglog(p_hamming, e_hamming)
plt.loglog(p_euclidian, e_euclidian)
plt.loglog(p_logprob, e_logprob)
plt.legend(['p', 'hamming', 'euclidian', 'logprob'])
plt.gca().invert_xaxis()
plt.savefig('costs_error.png')

