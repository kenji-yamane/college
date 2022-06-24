#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

#include "random/random.h"
#include "binary/awgn_canal.h"
#include "convolutional/trellis.h"
#include "convolutional/convolutional.h"

int main() {
	Random *r = new Random();
	Binary *bin = new Binary(7);

	std::ifstream in_f("plotter/p_rsn.csv");
	std::string dummyStr;
	char dummyChar;
	double p, rsn;
	in_f >> dummyStr;
	std::vector<double> probabilities, snr;
	while (in_f >> p) {
		in_f >> dummyChar >> rsn;
		probabilities.push_back(p);
		snr.push_back(rsn);
	}

	std::vector<double> encoderP[3];
	int ke = -1;
	for (const auto &p : probabilities) {
		ke++;
		double mean[3] = {};
		int iterations = 10;
		if (p < 0.1) {
			iterations = 100;
		}
		for (int i = 0; i < iterations; i++) {
			AwgnCanal canal(snr[ke]);
		
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
					std::vector<double> toTransmit = bin->binary3ToBPSK(output);
					for (int i = 0; i < (int)toTransmit.size(); i++) {
						toTransmit[i] = canal.transmit(toTransmit[i]);
					}
					e.decode(toTransmit);
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

	std::ofstream f("plotter/viterbi-euclidian.csv");
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
