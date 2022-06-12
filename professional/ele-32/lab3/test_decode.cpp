#include <iostream>
#include <bitset>
#include <vector>

#include "random/random.h"
#include "binary/bsc_canal.h"
#include "convolutional/trellis.h"
#include "convolutional/convolutional.h"

int main() {
	Binary *bin = new Binary(7);
	Random *r = new Random();

	Convolutional sixState(6, std::vector<int>{0117, 0127, 0155}, bin);
	std::vector<int> info;
	for (int i = 0; i < 10000; i++) {
		info.push_back(r->coinFlip());
	}

	for (int i = 0; i < (int)info.size(); i++) {
		int output = sixState.encode(info[i]);
		sixState.decode(output);
	}
	std::vector<int> recoveredInfo = sixState.getSequence();
	for (int i = 0; i < (int)recoveredInfo.size(); i++) {
		if (recoveredInfo[i] != info[i]) {
			std::cout << "error found!" << std::endl;
		}
	}

	delete bin;
	delete r;

	return 0;
}
