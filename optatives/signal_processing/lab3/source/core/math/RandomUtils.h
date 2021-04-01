//
// Created by mmaximo on 3/16/18.
//

#ifndef KALMAN_FILTERING_RANDOMUTILS_H
#define KALMAN_FILTERING_RANDOMUTILS_H

#include <random>

namespace math {

/**
 * Provides methods for random number generation.
 */
class RandomUtils {
public:
    /**
     * Generates a random number using gaussian distribution.
     * @param mean gaussian distribution mean.
     * @param sigma gaussian distribution standard deviation.
     * @return gaussian random number.
     */
    static double generateGaussianRandomNumber(double mean, double sigma);

    /**
     * Gerantes a random number using uniform distribution in range [min, max].
     * @param min minimum value of the uniform distribution range.
     * @param max maximum value of the uniform distribution range.
     * @return uniform random number.
     */
    static double generateUniformRandomNumber(double min, double max);

private:
    std::random_device randomDevice;
    std::mt19937 randomGenerator;

    static RandomUtils instance;

    RandomUtils();

    static RandomUtils &getInstance();
};

}

#endif //KALMAN_FILTERING_RANDOMUTILS_H
