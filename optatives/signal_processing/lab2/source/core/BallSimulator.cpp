//
// Created by mmaximo on 3/17/18.
//

#include "BallSimulator.h"
#include "math/RandomUtils.h"

BallSimulator::BallSimulator(double sigmaAcceleration, double sigmaCamera, double T, int cameraDelay)
        : sigmaAcceleration(sigmaAcceleration), sigmaCamera(sigmaCamera), T(T), cameraDelay(cameraDelay) {
    for (int i = 0; i <= cameraDelay; ++i)
        observations.push(math::Vector2d(position.x + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCamera),
                                         position.y + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCamera)));
}

void BallSimulator::update() {
    position.x += velocity.x * T;
    position.y += velocity.y * T;
    observations.push(math::Vector2d(position.x + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCamera),
                                     position.y + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCamera)));
    observations.pop();
}

math::Vector2d BallSimulator::observe() const {
    return observations.front();
}

const math::Vector2d &BallSimulator::getPosition() const {
    return position;
}

const math::Vector2d &BallSimulator::getVelocity() const {
    return velocity;
}

void BallSimulator::setVelocity(const math::Vector2d &velocity) {
    this->velocity = velocity;
}
