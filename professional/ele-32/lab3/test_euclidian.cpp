#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

#include "random/random.h"
#include "binary/awgn_canal.h"
#include "binary/binary.h"

int main() {
	Random *r = new Random();
	Binary *bin = new Binary(7);

	std::vector<double> probabilities = {0.5, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005};
	std::vector<double> snr = {0., 0.3542, 0.8212, 1.35277, 2.1089, 2.706, 3.3174, 4.142, 4.775};
	std::vector<double> perror;
	int ke = -1;
	for (const auto &p : probabilities) {
		ke++;
		double mean = 0;
		int iterations = 10;
		if (p < 0.1) {
			iterations = 100;
		}
		for (int i = 0; i < iterations; i++) {
			AwgnCanal canal(snr[ke]);
		
			std::vector<int> info;
			for (int i = 0; i < 10000; i++) {
				info.push_back(r->coinFlip());
			}
	
			std::vector<int> received;
			for (int i = 0; i < (int)info.size(); i++) {
				double transmitted = canal.transmit(bin->binaryToBPSK(info[i]));
				if (transmitted > 0) {
					received.push_back(1);
				} else {
					received.push_back(0);
				}
			}
	
			int errors = 0;
			for (int j = 0; j < (int)info.size(); j++) {
				errors += (info[j] ^ received[j]);
			}
			mean += (double)errors/info.size();
		}

		std::cout << "p " << p << ": ";
		std::cout << mean/iterations << " ";
		perror.push_back(mean/iterations);
		std::cout << std::endl;
	}

	std::ofstream f("plotter/viterbi-euclidian.csv");
	for (int i = 0; i < (int)probabilities.size(); i++) {
		f << probabilities[i];
		f << "," << perror[i];
		f << std::endl;
	}

	delete bin;
	delete r;

	return 0;
}
