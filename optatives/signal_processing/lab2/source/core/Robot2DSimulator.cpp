//
// Created by mmaximo on 3/16/18.
//

#include "Robot2DSimulator.h"
#include "math/RandomUtils.h"

Robot2DSimulator::Robot2DSimulator(double sigmaMotion, double sigmaGPS, double T) : sigmaMotion(sigmaMotion),
                                                                                    sigmaGPS(sigmaGPS), T(T), position(0.0, 0.0) {
}

void Robot2DSimulator::update(const math::Vector2d &velocity) {
    position.x += (velocity.x + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaMotion)) * T;
    position.y += (velocity.y + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaMotion)) * T;
}

math::Vector2d Robot2DSimulator::observe() const {
    return math::Vector2d(position.x + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaGPS),
                          position.y + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaGPS));
}

const math::Vector2d &Robot2DSimulator::getPosition() const {
    return position;
}
