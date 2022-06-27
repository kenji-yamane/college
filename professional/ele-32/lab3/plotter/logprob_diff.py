import matplotlib.pyplot as plt
from data_grabber import grab_cost_comparation_data
import numpy as np

space = 'e6'
data = grab_cost_comparation_data()
p_hamming, e_hamming = data['hamming']['p'], data['hamming'][space]
p_logprob, e_logprob = data['logprob']['p'], data['logprob'][space]

e_hamming = np.array(e_hamming)
e_logprob = np.array(e_logprob)
print(e_logprob - e_hamming)

plt.figure()
plt.plot(p_hamming, e_hamming - e_logprob)
plt.gca().invert_xaxis()
plt.savefig('logprob_diff.png')

