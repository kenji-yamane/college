import matplotlib.pyplot as plt
from data_grabber import grab_space_comparation_data

data = grab_space_comparation_data('euclidian')
p, e3, e4, e6 = data['p'], data['e3'], data['e4'], data['e6']

plt.figure()
plt.loglog(p, p)
plt.loglog(p, e3)
plt.loglog(p, e4)
plt.loglog(p, e6)
plt.legend(['p', 'e3', 'e4', 'e6'])
plt.gca().invert_xaxis()
plt.savefig('perror.png')

