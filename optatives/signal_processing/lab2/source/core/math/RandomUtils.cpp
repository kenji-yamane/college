//
// Created by mmaximo on 3/16/18.
//

#include "RandomUtils.h"

namespace math {

RandomUtils RandomUtils::instance;

double RandomUtils::generateGaussianRandomNumber(double mean, double sigma) {
    std::normal_distribution<double> gaussianDistribution(mean, sigma);
    return gaussianDistribution(getInstance().randomGenerator);
}

double RandomUtils::generateUniformRandomNumber(double min, double max) {
    std::uniform_real_distribution<double> uniformDistribution(min, max);
    return uniformDistribution(getInstance().randomGenerator);
}

RandomUtils::RandomUtils() {
    randomGenerator.seed(randomDevice());
}

RandomUtils &RandomUtils::getInstance() {
    return instance;
}

}