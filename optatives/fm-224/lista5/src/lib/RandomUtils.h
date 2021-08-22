#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <random>

class RandomUtils {
public:
    RandomUtils();
    double gaussianRand(double mean, double sigma);
    double uniformRand(double min, double max);

private:
    static std::random_device randomDevice;
    std::mt19937 randomGenerator;
};

#endif //RANDOMUTILS_H

