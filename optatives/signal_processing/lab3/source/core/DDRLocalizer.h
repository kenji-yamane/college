//
// Created by mmaximo on 3/24/18.
//

#ifndef EKF_DDRLOCALIZER_H
#define EKF_DDRLOCALIZER_H

#include <Eigen/Dense>
#include <math/Pose2D.h>
#include <memory>
#include "NonlinearModel.h"

class DDRLocalizer {
public:
    DDRLocalizer(double T, double sigmaLinearSpeed, double sigmaAngularSpeed, double sigmaCameraCartesian, double sigmaCameraAngle);

    void reset(const math::Pose2D& pose, const Eigen::MatrixXd &covariance);

    const math::Pose2D &predict(double linearSpeed, double angularSpeed);

    const math::Pose2D &filter(const math::Pose2D& observation);

    const Eigen::VectorXd& getState();

    const math::Pose2D &getPose();

    const Eigen::MatrixXd& getCovariance();

private:
    std::shared_ptr<NonlinearModel> model;
    Eigen::VectorXd state;
    Eigen::MatrixXd covariance;
    math::Pose2D pose;
};


#endif //EKF_DDRLOCALIZER_H
