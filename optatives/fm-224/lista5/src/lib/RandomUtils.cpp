#include "RandomUtils.h"

std::random_device RandomUtils::randomDevice;

RandomUtils::RandomUtils() {
    randomGenerator.seed(randomDevice());
}

double RandomUtils::gaussianRand(double mean, double sigma) {
    std::normal_distribution<double> gaussianDistribution(mean, sigma);
    return gaussianDistribution(this->randomGenerator);
}

double RandomUtils::uniformRand(double min, double max) {
    std::uniform_real_distribution<double> uniformDistribution(min, max);
    return uniformDistribution(this->randomGenerator);
}

