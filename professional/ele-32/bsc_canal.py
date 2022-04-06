import random

def error_occurs(p):
    r = random.uniform(0, 1)
    return (r <= p)

def bsc_canal(x, p):
    if error_occurs(p):
        return 1 - x
    return x

