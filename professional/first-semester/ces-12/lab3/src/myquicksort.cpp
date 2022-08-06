#include <mysortfunctions.h>

// you only need to mantain the headers. You can create aux funcs, objects, or create a generic quicksort that can work with different functions to select the pivot.

int median(int a, int b, int c) {
	return a + b + c - std::max(std::max(a, b), c) - std::min(std::min(a, b), c);
}

int partition(std::vector<int> &v, int ini, int fin, int pivot) {
	int pivot_pos;

	while (ini < fin) {
		while (v[ini] < pivot and ini < fin) ini++;
		while (v[fin] >= pivot and ini < fin) {
			if (v[fin] == pivot) pivot_pos = fin;
			fin--;
		}

		if (ini < fin) std::swap(v[ini], v[fin]);
		if (v[fin] == pivot) pivot_pos = fin;
	}
	if (v[ini] > pivot) {
		std::swap(v[ini], v[pivot_pos]);
		pivot_pos = ini;
	} else if (v[ini] != pivot) {
		std::swap(v[ini + 1], v[pivot_pos]);
		pivot_pos = ini + 1;
	}

	return pivot_pos;
}

void efficient_quicksort(std::vector<int> &v, int min, int max, SortStats &stats) {
	stats.recursive_calls++;
	stats.custom1++;

	while (min < max) {
		int pivot = median(v[min], v[(min + max) >> 1], v[max]);
		int pivot_pos = partition(v, min, max, pivot);
		if (pivot_pos - min < max - pivot_pos) {
			efficient_quicksort(v, min, pivot_pos - 1, stats);
			min = pivot_pos + 1;
		} else {
			efficient_quicksort(v, pivot_pos + 1, max, stats);
			max = pivot_pos - 1;
		}
	}

	stats.depth_recursion_stack = std::max(stats.custom1, stats.depth_recursion_stack);
	stats.custom1--;
}

void two_recursion_quicksort(std::vector<int> &v, int min, int max, SortStats &stats, bool fixed) {
	stats.recursive_calls++;
	stats.custom1++;

	if (min < max) {
		int pivot, pivot_pos;
		if (fixed) pivot = v[min];
		else pivot = median(v[min], v[(min + max) >> 1], v[max]);
		pivot_pos = partition(v, min, max, pivot);

		two_recursion_quicksort(v, min, pivot_pos - 1, stats, fixed);
		two_recursion_quicksort(v, pivot_pos + 1, max, stats, fixed);
	}

	stats.depth_recursion_stack = std::max(stats.custom1, stats.depth_recursion_stack);
	stats.custom1--;
}

/// the most comon quicksort, with 2 recursive calls
void myquicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
	two_recursion_quicksort(v, 0, (int)v.size() - 1, stats, false);
}// function myquicksort_2recursion_medianOf3

/// quicksort with one recursive call
void myquicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
	efficient_quicksort(v, 0, (int)v.size() - 1, stats);
} // function myquicksort_1recursion_medianOf3

/// quicksort with fixed pivot 
/// be sure to compare with equivalent implementation 
/// e.g., if you do 1 recursive call, compare with the 1recursion version
void myquicksort_fixedPivot(std::vector<int> &v, SortStats &stats) {
	two_recursion_quicksort(v, 0, (int)v.size() - 1, stats, true);
} // myquicksort_fixedPivot

