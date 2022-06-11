#include <iostream>
#include <bitset>
#include <vector>

#include "random.h"
#include "bsc_canal.h"
#include "trellis.h"
#include "convolutional.h"

int main() {
	Binary *bin = new Binary(7);
	Random *r = new Random();

	Convolutional sixState(6, std::vector<int>{0117, 0127, 0155}, bin);
	std::vector<int> info;
	for (int i = 0; i < 10000; i++) {
		info.push_back(r->coinFlip());
	}

	for (int i = 0; i < info.size(); i++) {
		int output = sixState.encode(info[i]);
		sixState.decode(output);
	}
	std::vector<int> recoveredInfo = sixState.getSequence();
	for (int i = 0; i < recoveredInfo.size(); i++) {
		if (recoveredInfo[i] != info[i]) {
			std::cout << "error found!" << std::endl;
		}
	}

	delete bin;
	delete r;

	return 0;
}
