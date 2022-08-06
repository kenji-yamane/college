import matplotlib.pyplot as plt
from data_grabber import grab_space_comparation_data

data = grab_space_comparation_data('logprob')
p, e3, e4, e6 = data['p'], data['e3'], data['e4'], data['e6']

alt_data = grab_space_comparation_data('alt-logprob')
alt_p = alt_data['p'].copy()
alt_e3 = alt_data['e3']
alt_e4 = alt_data['e4']
alt_e6 = alt_data['e6']
p += reversed(alt_data['p'])
e3 += reversed(alt_data['e3'])
e4 += reversed(alt_data['e4'])
e6 += reversed(alt_data['e6'])

plt.figure()
plt.grid()
plt.plot(p, p)
plt.plot(p, e3)
plt.plot(p, e4)
plt.plot(p, e6)
plt.xlabel('$p$')
plt.ylabel('$p_e$')
plt.legend(['p', 'm = 3', 'm = 4', 'm = 6'])
plt.gca().invert_xaxis()
plt.savefig('perror.png')

