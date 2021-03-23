//
// Created by mmaximo on 3/17/18.
//

#include "BallTracker.h"

BallTracker::BallTracker(double sigmaAcceleration, double sigmaCamera, double T, int cameraDelay) :
        A(4, 4),
        Q(4, 4),
        acc(2) {
    double varCam = sigmaCamera*sigmaCamera;
    double varAcc = sigmaAcceleration*sigmaAcceleration;
    this->sigmaAcc = sigmaAcceleration;

    Eigen::MatrixXd eye = Eigen::MatrixXd::Identity(2, 2);
    Eigen::MatrixXd B(4, 2), C(2, 4), M(2, 2), R(2, 2);

    this->A << 1, 0, T, 0,
                0, 1, 0, T,
                0, 0, 1, 0,
                0, 0, 0, 1;

    B << 0, 0,
        0, 0,
        T, 0,
        0, T;

    C << 1, 0, 0, 0,
        0, 1, 0, 0;

    M = eye*varAcc;
    this->Q = B*M*B.transpose();
    R = eye*varCam;

    this->kalmanFilter = std::make_shared<KalmanFilter>(this->A, B, C, this->Q, R);
    this->cameraDelay = cameraDelay;
}


void BallTracker::resetFilter(const Eigen::VectorXd &resetMean, const Eigen::MatrixXd &resetCovariance) {
    this->kalmanFilter->reset(resetMean, resetCovariance);
}

void BallTracker::predict() {
    this->acc << math::RandomUtils::generateGaussianRandomNumber(0, this->sigmaAcc),
                math::RandomUtils::generateGaussianRandomNumber(0, this->sigmaAcc);

    this->kalmanFilter->predict(this->acc);
}

void BallTracker::filter(const math::Vector2d &observation) {
    Eigen::VectorXd aux(2);

    aux << observation.x, observation.y;
    this->kalmanFilter->filter(aux);
}

void BallTracker::predictAndFilter(const math::Vector2d &observation) {
    this->predict();
    this->filter(observation);
}

const math::Vector2d &BallTracker::getPosition() const {
    this->position.x = this->kalmanFilter->getEstimate()[0];
    this->position.y = this->kalmanFilter->getEstimate()[1];

    return this->position;
}

const math::Vector2d &BallTracker::getVelocity() const {
    this->velocity.x = this->kalmanFilter->getEstimate()[2];
    this->velocity.y = this->kalmanFilter->getEstimate()[3];

    return this->velocity;
}

const Eigen::MatrixXd &BallTracker::getCovariance() const {
    return this->kalmanFilter->getCovariance();
}

void BallTracker::compensateDelayAndAssign(Eigen::VectorXd &x, Eigen::MatrixXd &P) {
    // You do not need to use this method if you do not want to
}