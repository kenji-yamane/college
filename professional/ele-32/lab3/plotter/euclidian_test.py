import matplotlib.pyplot as plt
from data_grabber import grab_test_data

data = grab_test_data()
p, e = data['p'], data['e']

plt.figure()
plt.loglog(p, p)
plt.loglog(p, e)
plt.legend(['p', 'e'])
plt.gca().invert_xaxis()
plt.savefig('test_results.png')

