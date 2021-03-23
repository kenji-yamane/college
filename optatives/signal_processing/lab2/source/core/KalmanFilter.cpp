//
// Created by mmaximo on 3/16/18.
//

#include "KalmanFilter.h"

//namespace signal_processing {

KalmanFilter::KalmanFilter(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                                              const Eigen::MatrixXd &C, const Eigen::MatrixXd &Q,
                                              const Eigen::MatrixXd &R) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->Q = Q;
    this->R = R;

    this->reset();
}

void KalmanFilter::reset() {
    this->x.setZero();
    this->P.setIdentity()*1e6;
}


void KalmanFilter::reset(const Eigen::VectorXd &x0, const Eigen::MatrixXd &P0) {
    this->x = x0;
    this->P = P0;
}

const Eigen::VectorXd &KalmanFilter::predict(const Eigen::VectorXd &u) {
    x = A*x + B*u;
    P = A*P*(A.transpose()) + Q;
}

const Eigen::VectorXd &KalmanFilter::filter(const Eigen::VectorXd &z) {
    K = P*(C.transpose())*((R + C*P*(C.transpose())).inverse());
    x = x + K*(z - C*x);
    P = P - K*C*P;
}

const Eigen::VectorXd &KalmanFilter::getEstimate() {
    return this->x;
}

const Eigen::MatrixXd &KalmanFilter::getCovariance() {
    return this->P;
}

//}