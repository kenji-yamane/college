import matplotlib.pyplot as plt
import numpy as np

from utils import extract_from_file

for tau in [3, 6, 12, 25]:
	lorentz_ts = extract_from_file('lorentz_time_series.txt')
	xline = lorentz_ts[tau:len(lorentz_ts)]
	yline = lorentz_ts[0:len(lorentz_ts) - tau]
	plt.figure()
	plt.plot(xline, yline, ',')
	plt.savefig('lorentz/lorentz_reconstructed_' + str(tau) + '.eps')

