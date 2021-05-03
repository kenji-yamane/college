#include <iostream>
#include <fstream>
#include <queue>

#include "lib/RandomUtils.h"

int main() {
    RandomUtils randomUtils = RandomUtils();

    std::ofstream out("../logs/gaussian_proof.txt");
	for (int i = 0; i < 100000; i++) {
		out << randomUtils.gaussianRand(0, 1) << std::endl;
	}

	out.close();
	
	std::ofstream rawOut("../logs/raw_gaussian.txt");
	std::ofstream filteredOut("../logs/filtered_gaussian.txt");
	double moving_average = 0;
	std::queue<double> mask;

    for (int i = 0; i < 1024; i++) {
		double sample = randomUtils.gaussianRand(0, 1);
        rawOut << sample << std::endl;

		moving_average += sample;
		mask.push(sample);
		if (mask.size() == 15) {
			filteredOut << moving_average/15 << std::endl;
			moving_average -= mask.front();
			mask.pop();
		}
    }

    rawOut.close();
	filteredOut.close();

    return 0;
}
