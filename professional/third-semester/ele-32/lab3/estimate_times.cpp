#include <iostream>
#include <bitset>
#include <vector>
#include <chrono>

#include "random/random.h"
#include "binary/bsc_canal.h"
#include "convolutional/trellis.h"
#include "convolutional/convolutional.h"

int main() {
	Random *r = new Random();
	Binary *bin = new Binary(7);

	std::vector<Convolutional> codes{
		Convolutional(3, std::vector<int>{013, 015, 017}, bin),
		Convolutional(4, std::vector<int>{025, 033, 037}, bin),
		Convolutional(6, std::vector<int>{0117, 0127, 0155}, bin)
	};
	std::vector<double> encodeTimes[3];
	std::vector<double> decodeTimes[3];

	std::vector<int> info;
	for (int i = 0; i < 100000; i++) {
		info.push_back(r->coinFlip());
	}

	int output;
	for (int i = 0; i < (int)info.size(); i++) {
		for (int j = 0; j < (int)codes.size(); j++) {
			auto start = std::chrono::steady_clock::now();
			output = codes[j].encode(info[i]);
			auto end = std::chrono::steady_clock::now();
			encodeTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
			start = std::chrono::steady_clock::now();
			codes[j].decode(output);
			end = std::chrono::steady_clock::now();
			decodeTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
		}
	}
	
	std::cout << "encode" << std::endl;
	for (int i = 0; i < (int)codes.size(); i++) {
		double mean = 0;
		for (int j = 0; j < (int)encodeTimes[i].size(); j++) {
			mean += encodeTimes[i][j];
		}
		std::cout << mean/encodeTimes[i].size() << std::endl;
	}
	std::cout << "decode" << std::endl;
	for (int i = 0; i < (int)codes.size(); i++) {
		double mean = 0;
		for (int j = 0; j < (int)decodeTimes[i].size(); j++) {
			mean += decodeTimes[i][j];
		}
		std::cout << mean/decodeTimes[i].size() << std::endl;
	}

	delete bin;
	delete r;

	return 0;
}
