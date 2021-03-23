//
// Created by mmaximo on 3/17/18.
//

#ifndef KALMAN_FILTERING_BALLSIMULATOR_H
#define KALMAN_FILTERING_BALLSIMULATOR_H

#include "math/Vector2.h"
#include <queue>

class BallSimulator {
public:
    BallSimulator(double sigmaAcceleration, double sigmaCamera, double T, int cameraDelay = 0);

    void update();

    math::Vector2d observe() const;

    const math::Vector2d& getPosition() const;

    const math::Vector2d& getVelocity() const;

    void setVelocity(const math::Vector2d& velocity);

private:
    double sigmaAcceleration;
    double sigmaCamera;
    double T;
    int cameraDelay;
    std::queue<math::Vector2d> observations;
    math::Vector2d position;
    math::Vector2d velocity;
};


#endif //KALMAN_FILTERING_BALLSIMULATOR_H
