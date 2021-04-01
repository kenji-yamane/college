//
// Created by mmaximo on 3/24/18.
//

#ifndef EKF_DDRSIMULATOR_H
#define EKF_DDRSIMULATOR_H

#include <memory>
#include <Eigen/Dense>
#include "NonlinearModel.h"
#include "math/Pose2D.h"

class DDRSimulator {
public:
    DDRSimulator(double T, double sigmaLinearSpeed, double sigmaAngularSpeed, double sigmaCameraCartesian, double sigmaCameraAngle);

    const math::Pose2D &update(double linearSpeed, double angularSpeed);

    math::Pose2D observe();

    const math::Pose2D& getPose() const;

private:
    math::Pose2D pose;
    double T;
    double sigmaLinearSpeed;
    double sigmaAngularSpeed;
    double sigmaCameraCartesian;
    double sigmaCameraAngle;
};


#endif //EKF_DDRSIMULATOR_H
