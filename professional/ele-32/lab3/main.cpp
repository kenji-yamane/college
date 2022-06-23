#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

#include "random/random.h"
#include "binary/bsc_canal.h"
#include "convolutional/trellis.h"
#include "convolutional/convolutional.h"

int main() {
	Random *r = new Random();
	Binary *bin = new Binary(7);

	std::vector<double> probabilities = {0.5, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005};
	std::vector<double> encoderP[3];
	for (const auto &p : probabilities) {
		double mean[3] = {};
		int iterations = 10;
		if (p < 0.1) {
			iterations = 100;
		}
		for (int i = 0; i < iterations; i++) {
			BscCanal canal(p, r);
		
			std::vector<Convolutional> codes{
				Convolutional(3, std::vector<int>{013, 015, 017}, bin),
			    Convolutional(4, std::vector<int>{025, 033, 037}, bin),
				Convolutional(6, std::vector<int>{0117, 0127, 0155}, bin)
			};
	
			std::vector<int> info;
			for (int i = 0; i < 10000; i++) {
				info.push_back(r->coinFlip());
			}
	
			for (auto &e : codes) {
				for (int i = 0; i < (int)info.size(); i++) {
					int output = e.encode(info[i]);
					std::bitset<3> encoded(output);
					int receivedOutput = 0;
					for (int i = 0; i < 3; i++) {
						int bitOutput = canal.transmit(encoded[i]);
						receivedOutput += (bitOutput << i);
					}
					e.decode(receivedOutput);
				}
			}
	
			for (int i = 0; i < (int)codes.size(); i++) {
				std::vector<int> received = codes[i].getSequence();
				int errors = 0;
				for (int j = 0; j < (int)info.size(); j++) {
					errors += (info[j] ^ received[j]);
				}
				mean[i] += (double)errors/info.size();
			}
		}

		std::cout << "p " << p << ": ";
		for (int i = 0; i < 3; i++) {
			std::cout << mean[i]/iterations << " ";
			encoderP[i].push_back(mean[i]/iterations);
		}
		std::cout << std::endl;
	}

	std::ofstream f("plotter/viterbi-hamming.csv");
	for (int i = 0; i < (int)probabilities.size(); i++) {
		f << probabilities[i];
		for (int j = 0; j < 3; j++) {
			f << "," << encoderP[j][i];
		}
		f << std::endl;
	}

	delete bin;
	delete r;

	return 0;
}
