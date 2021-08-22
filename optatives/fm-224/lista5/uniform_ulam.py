import matplotlib.pyplot as plt
import numpy as np

from utils import extract_from_file

uniform_proof = extract_from_file("uniform_proof.txt")
plt.figure()
plt.hist(uniform_proof, bins=100)
plt.savefig('uniform_ulam/uniform_proof.png')

raw_uniform = extract_from_file("raw_uniform.txt")
uniform_power_spectrum = np.abs(np.fft.rfft(raw_uniform - np.mean(raw_uniform)))**2
plt.figure()
plt.plot(uniform_power_spectrum)
plt.savefig('uniform_ulam/uniform_psd.png')
print('uniform time series:')
print('    mean: ', np.mean(raw_uniform))
print('    variance: ', np.var(raw_uniform))

ulam = extract_from_file("ulam.txt")
ulam_power_spectrum = np.abs(np.fft.rfft(ulam - np.mean(ulam)))**2
plt.figure()
plt.plot(ulam_power_spectrum)
plt.savefig('uniform_ulam/ulam_psd.png')
print('ulam time series:')
print('    mean: ', np.mean(ulam))
print('    variance: ', np.var(ulam))

