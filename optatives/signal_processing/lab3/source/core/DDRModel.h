//
// Created by mmaximo on 3/24/18.
//

#ifndef EKF_DDRMODEL_H
#define EKF_DDRMODEL_H

#include "NonlinearModel.h"

class DDRModel : public NonlinearModel {
public:
    DDRModel(double T, const Eigen::MatrixXd& M, const Eigen::MatrixXd& R);

    Eigen::VectorXd propagate(const Eigen::VectorXd &state, const Eigen::VectorXd &command);

    Eigen::VectorXd observe(const Eigen::VectorXd &state);

    Eigen::MatrixXd getA(const Eigen::VectorXd &state, const Eigen::VectorXd& command);

    Eigen::MatrixXd getB(const Eigen::VectorXd &state, const Eigen::VectorXd& command);

    Eigen::MatrixXd getC(const Eigen::VectorXd &state);

    Eigen::MatrixXd getQ(const Eigen::VectorXd &state, const Eigen::VectorXd& command);

    Eigen::MatrixXd getR(const Eigen::VectorXd &state);

private:
    double T;
    static constexpr double EPSILON = 1.0e-3;
    Eigen::MatrixXd M;
    Eigen::MatrixXd R;
};


#endif //EKF_DDRMODEL_H
