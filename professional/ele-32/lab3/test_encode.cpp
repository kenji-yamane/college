#include <iostream>
#include <bitset>
#include <vector>

#include "random.h"
#include "bsc_canal.h"
#include "trellis.h"
#include "encoder.h"

int main() {
	Random *r = new Random();
	std::bitset<10000> info;
	info.reset();

	Encoder threeState(3, std::vector<int>{013, 015, 017});
	Encoder fourState(4, std::vector<int>{025, 033, 037});
	Encoder sixState(6, std::vector<int>{0117, 0127, 0155});
	std::cout << std::bitset<7>(0127) << std::endl;

	int output = sixState.encode(1);
	std::cout << std::bitset<3>(output)[1];
	for (int i = 0; i < 10; i++) {
		output = sixState.encode(0);
		std::cout << std::bitset<3>(output)[1];
	}
	std::cout << std::endl;

	delete r;

	return 0;
}
