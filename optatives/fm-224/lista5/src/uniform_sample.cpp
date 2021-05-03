#include <iostream>
#include <fstream>

#include "lib/RandomUtils.h"

int main() {
    RandomUtils randomUtils = RandomUtils();

    std::ofstream out("../logs/uniform_proof.txt");
	for (int i = 0; i < 100000; i++) {
		out << randomUtils.uniformRand(0, 1) << std::endl;
	}

	out.close();
	
	std::ofstream rawOut("../logs/raw_uniform.txt");
	double moving_average = 0;

    for (int i = 0; i < 4096; i++) {
		double sample = randomUtils.uniformRand(0, 1);
        rawOut << sample << std::endl;
    }

    rawOut.close();

    return 0;
}
