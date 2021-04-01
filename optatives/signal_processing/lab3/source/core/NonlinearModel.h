//
// Created by mmaximo on 3/24/18.
//

#ifndef EKF_NONLINEARMODEL_H
#define EKF_NONLINEARMODEL_H

#include <Eigen/Dense>

class NonlinearModel {
public:
    virtual Eigen::VectorXd propagate(const Eigen::VectorXd &state, const Eigen::VectorXd &command) = 0;

    virtual Eigen::VectorXd observe(const Eigen::VectorXd &state) = 0;

    virtual Eigen::MatrixXd getA(const Eigen::VectorXd &state, const Eigen::VectorXd& command) = 0;

    virtual Eigen::MatrixXd getB(const Eigen::VectorXd &state, const Eigen::VectorXd& command) = 0;

    virtual Eigen::MatrixXd getC(const Eigen::VectorXd &state) = 0;

    virtual Eigen::MatrixXd getQ(const Eigen::VectorXd &state, const Eigen::VectorXd& command) = 0;

    virtual Eigen::MatrixXd getR(const Eigen::VectorXd &state) = 0;

};


#endif //EKF_NONLINEARMODEL_H
