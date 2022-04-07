import random
import numpy as np
from bsc_canal import bsc_canal
from hamming import hamming_encoder, hamming_decode
from hamming3d import hamming3d_encoder, hamming3d_decoder

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

transmitted = [0, 1, 1, 0]
for i in range(4):
	received = hamming_encoder(np.transpose([transmitted]))
	received[i] = 1 - received[i]
	corrected = hamming_decode(np.transpose([received]))
	if (not np.array_equal(corrected[0:4], np.array(transmitted))):
		print('error found')

transmitted = [0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1]
for i in range(11):
	received = hamming3d_encoder(np.transpose([transmitted]))
	received[i] = 1 - received[i]
	corrected = hamming3d_decoder(np.transpose([received]))
	if (not np.array_equal(corrected[0:11], np.array(transmitted))):
		print('error found')

