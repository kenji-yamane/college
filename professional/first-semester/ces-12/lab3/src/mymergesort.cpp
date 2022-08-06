
#include <mysortfunctions.h>

void mymergesort_recursive(std::vector<int> &v, SortStats &stats) {
	stats.recursive_calls++;
	stats.custom1++;

	if (v.size() > 1) {
		std::vector<int> left, right;
	
		left.resize(v.size() >> 1);
		right.resize(v.size() - (v.size() >> 1));
		for (int i = 0; i < (int)v.size(); i++) {
			if (i < (int)(v.size() >> 1)) left[i] = v[i];
			else right[i - (int)(v.size() >> 1)] = v[i];
		}
	
		mymergesort_recursive(left, stats);
		mymergesort_recursive(right, stats);
	
		int iv = 0, ileft = 0, iright = 0;
		while (ileft < (int)left.size() and iright < (int)right.size()) {
			if (left[ileft] < right[iright]) v[iv++] = left[ileft++];
			else v[iv++] = right[iright++];
		}
		while (ileft < (int)left.size()) v[iv++] = left[ileft++];
		while (iright < (int)right.size()) v[iv++] = right[iright++];
	}

	stats.depth_recursion_stack = std::max(stats.custom1, stats.depth_recursion_stack);
    stats.custom1--;
}

void mymergesort_iterative(std::vector<int> &v, SortStats &stats) {
	stats.recursive_calls = stats.depth_recursion_stack = 1;

	for (size_t block_size = 1; block_size < v.size(); block_size <<= 1) {
		for (size_t i = 0; i + block_size < v.size(); i += (block_size << 1)) {
			int left = (int)i, right = (int)(i + block_size), iordered = 0;
			std::vector<int> ordered_block;
			ordered_block.resize(std::min(2*block_size, v.size() - i));

			while (left < (int)(i + block_size) and right < (int)(i + ordered_block.size())) {
				if (v[left] < v[right]) ordered_block[iordered++] = v[left++];
				else ordered_block[iordered++] = v[right++];
			}
			while (left < (int)(i + block_size)) ordered_block[iordered++] = v[left++];
			while (right < (int)(i + ordered_block.size())) ordered_block[iordered++] = v[right++];

			for (size_t j = i; j < i + ordered_block.size(); j++) v[j] = ordered_block[j - i];
		}
	}
}

