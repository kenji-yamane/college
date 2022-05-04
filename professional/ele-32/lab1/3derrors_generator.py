import numpy as np
from hamming3d import hamming3d_encoder, get_syndrome

h = hamming3d_encoder(np.transpose(np.array([[0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1]])))
errors = []
for i in range(15):
    aux = np.copy(h)
    aux[i] = 1 - aux[i]
    syndrome = get_syndrome(np.transpose([aux]))
    errors.append((8*syndrome[0] + 4*syndrome[1] + 2*syndrome[2] + syndrome[3], i))

decoder_array = []
errors = sorted(errors, key=lambda tup : tup[0])
for err in errors:
    zeros = np.zeros(15, dtype=int)
    zeros[err[1]] = 1
    decoder_array.append(zeros)

print(np.array2string(np.array(decoder_array), separator=', '))

