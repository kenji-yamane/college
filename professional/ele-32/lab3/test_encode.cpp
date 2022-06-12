#include <iostream>
#include <bitset>
#include <vector>

#include "random/random.h"
#include "binary/bsc_canal.h"
#include "convolutional/trellis.h"
#include "convolutional/convolutional.h"

int main() {
	Random *r = new Random();
	Binary *bin = new Binary(7);
	std::bitset<10000> info;
	info.reset();

	Convolutional threeState(3, std::vector<int>{013, 015, 017}, bin);
	Convolutional fourState(4, std::vector<int>{025, 033, 037}, bin);
	Convolutional sixState(6, std::vector<int>{0117, 0127, 0155}, bin);
	std::cout << std::bitset<7>(0127) << std::endl;

	int output = sixState.encode(1);
	std::cout << std::bitset<3>(output)[1];
	for (int i = 0; i < 10; i++) {
		output = sixState.encode(0);
		std::cout << std::bitset<3>(output)[1];
	}
	std::cout << std::endl;

	delete bin;
	delete r;

	return 0;
}
