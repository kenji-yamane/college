#include <iostream>
#include <bitset>
#include <vector>
#include <chrono>

#include "random.h"
#include "bsc_canal.h"
#include "trellis.h"
#include "encoder.h"

int main() {
	Random *r = new Random();

	std::vector<Encoder> encoders{
		Encoder(3, std::vector<int>{013, 015, 017}),
		Encoder(4, std::vector<int>{025, 033, 037}),
		Encoder(6, std::vector<int>{0117, 0127, 0155})
	};
	std::vector<double> encodeTimes[3];
	std::vector<double> decodeTimes[3];

	std::vector<int> info;
	for (int i = 0; i < 100000; i++) {
		info.push_back(r->coinFlip());
	}

	int output;
	for (int i = 0; i < info.size(); i++) {
		for (int j = 0; j < encoders.size(); j++) {
			auto start = std::chrono::steady_clock::now();
			output = encoders[j].encode(info[i]);
			auto end = std::chrono::steady_clock::now();
			encodeTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
			start = std::chrono::steady_clock::now();
			encoders[j].decode(output);
			end = std::chrono::steady_clock::now();
			decodeTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
		}
	}
	
	std::cout << "encode" << std::endl;
	for (int i = 0; i < encoders.size(); i++) {
		double mean = 0;
		for (int j = 0; j < encodeTimes[i].size(); j++) {
			mean += encodeTimes[i][j];
		}
		std::cout << mean/encodeTimes[i].size() << std::endl;
	}
	std::cout << "decode" << std::endl;
	for (int i = 0; i < encoders.size(); i++) {
		double mean = 0;
		for (int j = 0; j < decodeTimes[i].size(); j++) {
			mean += decodeTimes[i][j];
		}
		std::cout << mean/decodeTimes[i].size() << std::endl;
	}

	delete r;

	return 0;
}
