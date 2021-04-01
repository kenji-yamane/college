//
// Created by mmaximo on 3/24/18.
//

#include "DDRLocalizer.h"

#include "DDRModel.h"
#include "math/MathUtils.h"

DDRLocalizer::DDRLocalizer(double T, double sigmaLinearSpeed, double sigmaAngularSpeed, double sigmaCameraCartesian,
                           double sigmaCameraAngle) {
    Eigen::MatrixXd M(2, 2);
    M << sigmaLinearSpeed*sigmaLinearSpeed, 0,
         0, sigmaAngularSpeed*sigmaAngularSpeed;

    Eigen::MatrixXd R(3, 3);
    R << sigmaCameraCartesian*sigmaCameraCartesian, 0, 0,
         0, sigmaCameraCartesian*sigmaCameraCartesian, 0,
         0, 0, sigmaCameraAngle*sigmaCameraAngle;

    this->model = std::make_shared<DDRModel>(T, M, R);
    this->state = Eigen::VectorXd(3);
}

void DDRLocalizer::reset(const math::Pose2D &pose, const Eigen::MatrixXd &covariance) {
    this->pose = pose;
    this->covariance = covariance;

    this->state << pose.translation.x, pose.translation.y, pose.rotation;
}

const math::Pose2D &DDRLocalizer::predict(double linearSpeed, double angularSpeed) {
    Eigen::VectorXd command(2);

    command << linearSpeed, angularSpeed;
    this->state = this->model->propagate(this->state, command);

    Eigen::MatrixXd A = this->model->getA(this->state, command), Q = this->model->getQ(this->state, command);
    this->covariance = A*this->covariance*A.transpose() + Q;

    this->pose.translation.x = this->state(0);
    this->pose.translation.y = this->state(1);
    this->pose.rotation = math::MathUtils::normalizeAngle(this->state(2));

    return pose;
}

const math::Pose2D &DDRLocalizer::filter(const math::Pose2D& observation) {
    Eigen::VectorXd observedState(3);
    observedState << observation.translation.x, observation.translation.y, observation.rotation;

    Eigen::MatrixXd C = this->model->getC(observedState), R = this->model->getR(observedState);
    Eigen::MatrixXd K = this->covariance*C.transpose()*(R + C*this->covariance*C.transpose()).inverse();

    if (fabs(this->state(2) - observedState(2)) < 5*M_PI/180) {
        this->state = this->state + K * (observedState - this->model->observe(this->state));
        this->covariance = this->covariance - K * C * this->covariance;

        this->pose.translation.x = this->state(0);
        this->pose.translation.y = this->state(1);
        this->pose.rotation = math::MathUtils::normalizeAngle(this->state(2));
    }

    return pose;
}

const Eigen::VectorXd &DDRLocalizer::getState() {
    return state;
}

const math::Pose2D &DDRLocalizer::getPose() {
    return pose;
}

const Eigen::MatrixXd &DDRLocalizer::getCovariance() {
    return covariance;
}

