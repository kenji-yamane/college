import matplotlib.pyplot as plt
import numpy as np

from utils import stats_moment
from utils import extract_from_file

first_b = extract_from_file("solar_wind1b.dat")
second = extract_from_file("solar_wind2.dat")

plt.figure()
plt.hist(first_b, bins=1000)
plt.savefig('figures/pdf1b.png')

plt.figure()
plt.hist(second, bins=1000)
plt.savefig('figures/pdf2.png')

first_b_stddev = np.sqrt(stats_moment(first_b, 2))
second_stddev = np.sqrt(stats_moment(second, 2))

first_b_skewness = stats_moment(first_b, 3)/(first_b_stddev**3)
second_skewness = stats_moment(second, 3)/(second_stddev**3)

first_b_curtosis = stats_moment(first_b, 4)/(first_b_stddev**4)
second_curtosis = stats_moment(second, 4)/(second_stddev**4)

print('curtose da 1b:', first_b_curtosis)
print('skewness da 1b:', first_b_skewness)
print('-------------------------')
print('curtose da 2:', second_curtosis)
print('skewness da 2:', second_skewness)

