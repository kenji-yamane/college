//
// Created by mmaximo on 3/16/18.
//

#include "Robot2DLocalizer.h"

Robot2DLocalizer::Robot2DLocalizer(double sigmaMotion, double sigmaGPS, double T) : eigenAux(2) {
    double varMotion = sigmaMotion*sigmaMotion;
    double varGPS = sigmaGPS*sigmaGPS;

    Eigen::MatrixXd eye = Eigen::MatrixXd::Identity(2, 2);
    this->kalmanFilter = std::make_shared<KalmanFilter>(eye, eye*T, eye, T*eye*varMotion*T, eye*varGPS);
}

void Robot2DLocalizer::reset(const math::Vector2d &resetPosition, const Eigen::MatrixXd &resetCovariance) {
    this->eigenAux << resetPosition.x, resetPosition.y;
    this->kalmanFilter->reset(this->eigenAux, resetCovariance);

    this->position = resetPosition;
}


const math::Vector2d &Robot2DLocalizer::predict(const math::Vector2d &command) {
    this->eigenAux << command.x, command.y;
    this->kalmanFilter->predict(this->eigenAux);

    this->position.x = this->kalmanFilter->getEstimate()(0);
    this->position.y = this->kalmanFilter->getEstimate()(1);

    return this->position;
}

const math::Vector2d &Robot2DLocalizer::filter(const math::Vector2d &observation) {
    this->eigenAux << observation.x, observation.y;
    this->kalmanFilter->filter(this->eigenAux);

    this->position.x = this->kalmanFilter->getEstimate()(0);
    this->position.y = this->kalmanFilter->getEstimate()(1);

    return this->position;
}

const math::Vector2d &Robot2DLocalizer::getPosition() const {
    return this->position;
}

const Eigen::MatrixXd &Robot2DLocalizer::getCovariance() const {
    this->kalmanFilter->getCovariance();
}
