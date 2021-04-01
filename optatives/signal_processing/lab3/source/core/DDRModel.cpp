//
// Created by mmaximo on 3/24/18.
//

#include "DDRModel.h"

DDRModel::DDRModel(double T, const Eigen::MatrixXd &M, const Eigen::MatrixXd &R) : T(T), M(M), R(R) {
}


Eigen::VectorXd DDRModel::propagate(const Eigen::VectorXd &state, const Eigen::VectorXd &command) {
    double x = state(0), y = state(1), psi = state(2), v = command(0), w = command(1);
    Eigen::VectorXd nextState(3);

    nextState << x + 2*v/w*cos(psi + w*T/2)*sin(w*T/2),
                 y + 2*v/w*sin(psi + w*T/2)*sin(w*T/2),
                 psi + w*T;

    return nextState;
}

Eigen::VectorXd DDRModel::observe(const Eigen::VectorXd &state) {
    double x = state(0), y = state(1), psi = state(2);
    Eigen::VectorXd observedState(3);

    observedState << x, y, psi;

    return observedState;
}

Eigen::MatrixXd DDRModel::getA(const Eigen::VectorXd &state, const Eigen::VectorXd &command) {
    double psi = state(2), v = command(0), w = command(1);
    Eigen::MatrixXd A(3, 3);

    if (fabs(w) < EPSILON) {
        A << 1, 0, -T*sin(psi + T*w/2)*v,
             0, 1, T*cos(psi + T*w/2)*v,
             0, 0, 1;
    } else {
        A << 1, 0, -2*v/w*sin(psi + T*w/2)*sin(T*w/2),
             0, 1, 2*v/w*cos(psi + T*w/2)*sin(T*w/2),
             0, 0, 1;
    }

    return A;
}

Eigen::MatrixXd DDRModel::getB(const Eigen::VectorXd &state, const Eigen::VectorXd &command) {
    double psi = state(2), v = command(0), w = command(1);
    Eigen::MatrixXd B(3, 2);

    if (fabs(w) < EPSILON) {
        B << T*cos(psi + T*w/2), -T*T*sin(psi + T*w/2)*v/2,
             T*sin(psi + T*w/2), T*T*cos(psi + T*w/2)*v/2,
             0, T;
    } else {
        B << 2*cos(psi + T*w/2)*sin(T*w/2)/w, T*cos(psi + T*w/2)*cos(T*w/2)*v/w - cos(psi + T*w/2)*sin(T*w/2)*2*v/w/w - T*sin(psi + T*w/2)*sin(T*w/2)*v/w,
             2*sin(psi + T*w/2)*sin(T*w/2)/w, T*cos(psi + T*w/2)*sin(T*w/2)*v/w - sin(psi + T*w/2)*sin(T*w/2)*2*v/w/w + T*sin(psi + T*w/2)*cos(T*w/2)*v/w,
             0, T;
    }

    return B;
}

Eigen::MatrixXd DDRModel::getC(const Eigen::VectorXd &state) {
    return Eigen::MatrixXd::Identity(3, 3);
}

Eigen::MatrixXd DDRModel::getQ(const Eigen::VectorXd &state, const Eigen::VectorXd &command) {
    Eigen::MatrixXd W = this->getB(state, command);

    return W*this->M*W.transpose();
}

Eigen::MatrixXd DDRModel::getR(const Eigen::VectorXd &state) {
    return this->R;
}
