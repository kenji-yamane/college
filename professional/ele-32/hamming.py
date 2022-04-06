import numpy as np

G = np.array([
    [1, 0, 0, 0, 1, 1, 1],
    [0, 1, 0, 0, 1, 0, 1],
    [0, 0, 1, 0, 1, 1, 0],
    [0, 0, 0, 1, 0, 1, 1]
])
def hamming_encoder(u):
    temp = u*G

    ans = temp[0]
    for i in range(1, len(temp)):
        ans = np.logical_xor(ans, temp[i])
    return 1*ans

