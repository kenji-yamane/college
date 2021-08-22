import matplotlib.pyplot as plt
import numpy as np

from utils import extract_from_file

gaussian_proof = extract_from_file("gaussian_proof.txt")
plt.figure()
plt.hist(gaussian_proof, bins=100)
plt.savefig('gaussian/proof.png')

raw_gaussian = extract_from_file("raw_gaussian.txt")
raw_power_spectrum = np.abs(np.fft.rfft(raw_gaussian))**2
plt.figure()
plt.plot(raw_power_spectrum)
plt.savefig('gaussian/raw.png')

filtered_gaussian = extract_from_file("filtered_gaussian.txt")
filtered_power_spectrum = np.abs(np.fft.rfft(filtered_gaussian))**2
plt.figure()
plt.plot(filtered_power_spectrum)
plt.savefig('gaussian/filtered.png')

plt.figure()
plt.plot(raw_gaussian)
plt.savefig('gaussian/raw_orbit.png')
plt.figure()
plt.plot(filtered_gaussian)
plt.savefig('gaussian/filtered_orbit.png')

