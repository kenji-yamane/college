import numpy as np

G = np.array([
    [1, 0, 0, 0, 1, 1, 1],
    [0, 1, 0, 0, 1, 0, 1],
    [0, 0, 1, 0, 1, 1, 0],
    [0, 0, 0, 1, 0, 1, 1]
])

H_transpose = np.array([
    [1, 1, 1],
    [1, 0, 1],
    [1, 1, 0],
    [0, 1, 1],
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
    ])

error_vector = np.array([
                            [0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 1],
                            [0, 0, 0, 0, 0, 1, 0],
                            [0, 0, 0, 1, 0, 0, 0],
                            [0, 0, 0, 0, 1, 0, 0],
                            [0, 1, 0, 0, 0, 0, 0],
                            [0, 0, 1, 0, 0, 0, 0],
                            [1, 0, 0, 0, 0, 0, 0],
                        ])

def hamming_encoder(u):
    temp = u*G

    ans = temp[0]
    for i in range(1, len(temp)):
        ans = np.logical_xor(ans, temp[i])
    return 1*ans

def get_sindrome(u):
    temp = u*H_transpose

    ans = temp[0]
    for i in range(1, len(temp)):
        ans = np.logical_xor(ans, temp[i])
    return 1*ans

def hamming_decode(u):
    sindrome = get_sindrome(u)
    position_array = sindrome[2] + sindrome[1]*2 + sindrome[0]*4  
    error = error_vector[position_array]

    ans = np.logical_xor(np.transpose(u)[0], error)

    return 1*ans

    


