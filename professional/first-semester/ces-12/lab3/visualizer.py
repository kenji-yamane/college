import csv
import matplotlib.pyplot as plt

class SortData:
	def __init__(self, algoname):
		self.algoname = algoname
		self.time = []
		self.n = []
		self.calls = []
		self.depth = []

def extract_data(filename, algoname):
	data = SortData(algoname)
	with open(filename) as csvfile:
		rows = csv.reader(csvfile, delimiter=',')

		for row in rows:
			data.time.append(float(row[0]))
			data.n.append(float(row[2]))
			data.calls.append(float(row[3]))
			data.depth.append(float(row[4]))
	
	return data

# quick merge radix comparison
plt.figure()

quicksort = extract_data("build/QS_1R_MS_RAND_200_20000.csv", "quick sort")
mergesort = extract_data("build/MRG_I_MS_RAND_200_20000.csv", "merge sort")
radixsort = extract_data("build/RADIX_MS_RAND_200_20000.csv", "radix sort")
stlsort = extract_data("build/STL_SORT_MS_RAND_200_20000.csv", "stl sort")

plt.plot(quicksort.n, quicksort.time)
plt.plot(mergesort.n, mergesort.time)
plt.plot(radixsort.n, radixsort.time)
plt.plot(stlsort.n, stlsort.time)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quicksort.algoname, mergesort.algoname, radixsort.algoname, stlsort.algoname])
plt.savefig('overall.png')

# iterative merge and recursive merge comparison
plt.figure()

iterative_merge = extract_data("build/MRG_I_MS_RAND_200_20000.csv", "iterative merge")
recursive_merge = extract_data("build/MRG_R_MS_RAND_200_20000.csv", "recursive merge")

plt.plot(recursive_merge.n, recursive_merge.time)
plt.plot(iterative_merge.n, iterative_merge.time)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([recursive_merge.algoname, iterative_merge.algoname])
plt.savefig('mergesorts.png')

# quick 1 recursion and quick 2 recursion comparison
quickfixed = extract_data("build/QS_FP_MS_RAND_200_20000.csv", "quickfixed")
quick1r = extract_data("build/QS_1R_MS_RAND_200_20000.csv", "quick1r")
quick2r = extract_data("build/QS_2R_MS_RAND_200_20000.csv", "quick2r")

plt.figure()
plt.plot(quick1r.n, quick1r.time)
plt.plot(quick2r.n, quick2r.time)
plt.plot(quickfixed.n, quickfixed.time)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quick1r.algoname, quick2r.algoname, quickfixed.algoname])
plt.savefig('quicksorts_time.png')

plt.figure()
plt.plot(quick1r.n, quick1r.calls)
plt.plot(quick2r.n, quick2r.calls)
plt.plot(quickfixed.n, quickfixed.calls)
plt.xlabel('N')
plt.ylabel('Chamadas recursivas')
plt.legend([quick1r.algoname, quick2r.algoname, quickfixed.algoname])
plt.savefig('quicksorts_calls.png')

plt.figure()
plt.plot(quick1r.n, quick1r.depth)
plt.plot(quick2r.n, quick2r.depth)
plt.plot(quickfixed.n, quickfixed.depth)
plt.xlabel('N')
plt.ylabel('Profundidade recursiva')
plt.legend([quick1r.algoname, quick2r.algoname, quickfixed.algoname])
plt.savefig('quicksorts_depth.png')

# median pivot and fixed pivot for almost ordered vectors comparison
quickfixed = extract_data("build/QS_FP_MS_AO_200_20000.csv", "fixed pivot")
quickmedian = extract_data("build/QS_2R_MS_AO_200_20000.csv", "median pivot")

plt.figure()
plt.plot(quickmedian.n, quickmedian.time)
plt.plot(quickfixed.n, quickfixed.time)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quickmedian.algoname, quickfixed.algoname])
plt.savefig('medianfixed_time.png')

plt.figure()
plt.plot(quickmedian.n, quickmedian.calls)
plt.plot(quickfixed.n, quickfixed.calls)
plt.xlabel('N')
plt.ylabel('Chamadas recursivas')
plt.legend([quickmedian.algoname, quickfixed.algoname])
plt.savefig('medianfixed_calls.png')

plt.figure()
plt.plot(quickmedian.n, quickmedian.depth)
plt.plot(quickfixed.n, quickfixed.depth)
plt.xlabel('N')
plt.ylabel('Profundidade recursiva')
plt.legend([quickmedian.algoname, quickfixed.algoname])
plt.savefig('medianfixed_depth.png')

plt.figure()
plt.plot(quickmedian.n, quickmedian.depth)
plt.xlabel('N')
plt.ylabel('Profundidade recursiva')
plt.legend([quickmedian.algoname])
plt.savefig('only_median.png')

# best quick and std sort for almost ordered vectors comparison
quickbest = extract_data("build/QS_1R_MS_AO_200_20000.csv", "best quick")
quickstl = extract_data("build/STL_SORT_MS_AO_200_20000.csv", "stl quick")

plt.figure()
plt.plot(quickstl.n, quickstl.time)
plt.plot(quickbest.n, quickbest.time)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quickstl.algoname, quickbest.algoname])
plt.savefig('beststl_time.png')

plt.figure()
plt.plot(quickstl.n, quickstl.calls)
plt.plot(quickbest.n, quickbest.calls)
plt.xlabel('N')
plt.ylabel('Chamadas recursivas')
plt.legend([quickstl.algoname, quickbest.algoname])
plt.savefig('beststl_calls.png')

plt.figure()
plt.plot(quickstl.n, quickstl.calls)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quickstl.algoname])
plt.savefig('stl_calls.png')

plt.figure()
plt.plot(quickstl.n, quickstl.depth)
plt.plot(quickbest.n, quickbest.depth)
plt.xlabel('N')
plt.ylabel('Profundidade recursiva')
plt.legend([quickstl.algoname, quickbest.algoname])
plt.savefig('beststl_depth.png')

plt.figure()
plt.plot(quickstl.n, quickstl.depth)
plt.xlabel('N')
plt.ylabel('tempo (ms)')
plt.legend([quickstl.algoname])
plt.savefig('stl_depth.png')

