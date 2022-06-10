#include <iostream>
#include <bitset>
#include <vector>
#include <string>

#include "random.h"
#include "bsc_canal.h"
#include "trellis.h"
#include "encoder.h"

void printPythonArray(std::string descriptor, std::vector<double> arr) {
	std::cout << descriptor << " = [" << arr[0];
	for (int i = 1; i < arr.size(); i++) {
		std::cout << ", " << arr[i];
	}
	std::cout << "]";
	std::cout << std::endl;
}

int main() {
	Random *r = new Random();

	std::vector<double> probabilities;
	for (double p = 0.5; p > 0.151; p -= 0.01) {
		probabilities.push_back(p);
	}
	for (double p = 0.15; p > 0.049; p -= 0.005) {
		probabilities.push_back(p);
	}
	probabilities.push_back(0.02);
	probabilities.push_back(0.01);
	probabilities.push_back(0.005);
	std::vector<double> encoderP[3];
	for (const auto &p : probabilities) {
		BscCanal canal(p, r);

		std::vector<Encoder> encoders{
			Encoder(3, std::vector<int>{013, 015, 017}),
		    Encoder(4, std::vector<int>{025, 033, 037}),
			Encoder(6, std::vector<int>{0117, 0127, 0155})
		};

		std::vector<int> info;
		for (int i = 0; i < 10000; i++) {
			info.push_back(r->coinFlip());
		}

		for (auto &e : encoders) {
			for (int i = 0; i < info.size(); i++) {
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

		std::cout << "p " << p << ": ";
		for (int i = 0; i < encoders.size(); i++) {
			std::vector<int> received = encoders[i].getSequence();
			int errors = 0;
			for (int j = 0; j < info.size(); j++) {
				errors += (info[j] ^ received[j]);
			}
			std::cout << (double)errors/info.size() << " ";
			encoderP[i].push_back((double)errors/info.size());
		}
		std::cout << std::endl;
	}

	printPythonArray("p", probabilities);
	printPythonArray("e3", encoderP[0]);
	printPythonArray("e4", encoderP[1]);
	printPythonArray("e6", encoderP[2]);

	delete r;

	return 0;
}
