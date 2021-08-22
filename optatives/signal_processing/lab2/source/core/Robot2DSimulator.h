//
// Created by mmaximo on 3/16/18.
//

#ifndef KALMAN_FILTERING_ROBOT2DSIMULATOR_H
#define KALMAN_FILTERING_ROBOT2DSIMULATOR_H

#include "math/Vector2.h"

class Robot2DSimulator {
public:
    Robot2DSimulator(double sigmaMotion, double sigmaGPS, double T);

    void update(const math::Vector2d& velocity);

    math::Vector2d observe() const;

    const math::Vector2d& getPosition() const;

private:
    double sigmaMotion;
    double sigmaGPS;
    double T;
    math::Vector2d position;
};


#endif //KALMAN_FILTERING_ROBOT2DSIMULATOR_H
