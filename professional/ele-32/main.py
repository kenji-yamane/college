import random
import numpy as np
from bsc_canal import *
from hamming import *

p = 0.7

def test_bsc_canal():
	iterations = 10000
	i = 0
	for j in range(iterations):
		transmitted = 1
	
		received = bsc_canal(transmitted, p)
		if received == transmitted:
			i += 1
	
	print(i/iterations)

h = hamming_encoder(np.transpose(np.array([[0, 1, 1, 0]])))
#h = hamming_encoder(np.array([[0, 1, 1, 0]]))

print(h)


