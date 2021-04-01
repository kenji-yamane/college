//
// Created by mmaximo on 3/24/18.
//

#include "DDRSimulator.h"
#include "math/RandomUtils.h"
#include "math/MathUtils.h"

DDRSimulator::DDRSimulator(double T, double sigmaLinearSpeed, double sigmaAngularSpeed, double sigmaCameraCartesian,
                           double sigmaCameraAngle) : T(T), sigmaLinearSpeed(sigmaLinearSpeed),
                                                      sigmaAngularSpeed(sigmaAngularSpeed),
                                                      sigmaCameraCartesian(sigmaCameraCartesian),
                                                      sigmaCameraAngle(sigmaCameraAngle), pose(math::Pose2D(0.0, 0.0, 0.0)) {
}

const math::Pose2D &DDRSimulator::update(double linearSpeed, double angularSpeed) {
    double vn = linearSpeed + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaLinearSpeed);
    double wn = angularSpeed + math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaAngularSpeed);
    if (fabs(wn) < 1.0e-3) {
        pose.translation.x = pose.translation.x + vn * T * cos(pose.rotation + wn * T / 2.0);
        pose.translation.y = pose.translation.y + vn * T * sin(pose.rotation + wn * T / 2.0);
    } else {
        pose.translation.x = pose.translation.x + 2.0 * (vn / wn) * cos(pose.rotation + wn * T / 2.0) * sin(wn * T / 2.0);
        pose.translation.y = pose.translation.y + 2.0 * (vn / wn) * sin(pose.rotation + wn * T / 2.0) * sin(wn * T / 2.0);
    }
    pose.rotation = math::MathUtils::normalizeAngle(pose.rotation + wn * T);
    return pose;
}

math::Pose2D DDRSimulator::observe() {
    math::Pose2D observation = pose;
    observation.translation.x += math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCameraCartesian);
    observation.translation.y += math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCameraCartesian);
    observation.rotation += math::RandomUtils::generateGaussianRandomNumber(0.0, sigmaCameraAngle);
    observation.rotation = math::MathUtils::normalizeAngle(observation.rotation);
    return observation;
}

const math::Pose2D &DDRSimulator::getPose() const {
    return pose;
}