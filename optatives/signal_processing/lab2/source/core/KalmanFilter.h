//
// Created by mmaximo on 3/16/18.
//

#ifndef KALMAN_FILTERING_KALMANFILTER_H
#define KALMAN_FILTERING_KALMANFILTER_H

#include <Eigen/Dense>

//namespace signal_processing {

/**
 * Kalman filter using time-invariant A, B, C, Q and R matrices.
 */
class KalmanFilter {
public:
    /**
     * Constructs a Kalman filter considering the following mathematical model:
     * xt = A * xt-1 + B * ut
     * zt = C * xt
     * wt is a gaussian random variable with zero mean and covariance matrix Q.
     * rt is a gaussian random variable with zero mean and covariance matrix R.
     * @param A state prediction matrix.
     * @param B command prediction matrix.
     * @param C observation matrix.
     * @param Q prediction noise covariance matrix.
     * @param R observation noise covariance matrix.
     */
    KalmanFilter(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, const Eigen::MatrixXd &C, const Eigen::MatrixXd &Q,
                 const Eigen::MatrixXd &R);

    /**
     * Resets the Kalman filter to an uncertain state: zero mean and high covariance.
     */
    void reset();

    /**
     * Resets the Kalman filter using given mean and covariance.
     * @param x0 mean to reset the filter to.
     * @param P0 covariance to reset the filter to.
     */
    void reset(const Eigen::VectorXd &x0, const Eigen::MatrixXd &P0);

    /**
     * Executes a prediction step.
     * @param u control command.
     * @return new predicted state.
     */
    const Eigen::VectorXd &predict(const Eigen::VectorXd &u);

    /**
     * Executes a filtering step.
     * @param z observation.
     * @return new filtered state.
     */
    const Eigen::VectorXd &filter(const Eigen::VectorXd &z);

    /**
     * Obtains the current state estimate.
     * @return current state estimate.
     */
    const Eigen::VectorXd &getEstimate();

    /**
     * Obtains the current state uncertainty.
     * @return current state uncertainty.
     */
    const Eigen::MatrixXd &getCovariance();

private:
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd C;
    Eigen::MatrixXd Q;
    Eigen::MatrixXd R;
    Eigen::MatrixXd K;

    Eigen::VectorXd x;
    Eigen::MatrixXd P;
};

//}

#endif //KALMAN_FILTERING_KALMANFILTER_H
