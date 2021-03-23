//
// Created by mmaximo on 3/17/18.
//

#ifndef KALMAN_FILTERING_BALLTRACKER_H
#define KALMAN_FILTERING_BALLTRACKER_H

#include <memory>
#include "math/Vector2.h"
#include "KalmanFilter.h"
#include "math/RandomUtils.h"

/**
 * Tracker for a soccer ball.
 */
class BallTracker {
public:
    /**
     * Constructs a tracker for a soccer ball.
     * @param sigmaAcceleration standard deviation of the stochastic acceleration.
     * @param sigmaCamera standard deviation of the camera measurements.
     * @param T sample time.
     * @param cameraDelay camera delay in timesteps.
     */
    BallTracker(double sigmaAcceleration, double sigmaCamera, double T, int cameraDelay = 0);

    /**
     * Resets the underlying Kalman filter using given mean and covariance.
     * @param resetMean mean to reset the filter to.
     * @param resetCovariance covariance to reset the filter to.
     */
    void resetFilter(const Eigen::VectorXd &resetMean, const Eigen::MatrixXd &resetCovariance);

    /**
     * Executes a prediction step.
     */
    void predict();

    /**
     * Executes a filtering step.
     * @param observation camera observation.
     */
    void filter(const math::Vector2d &observation);

    /**
     * Executes prediction and filtering steps.
     * @param observation camera observation.
     */
    void predictAndFilter(const math::Vector2d &observation);

    /**
     * Obtains the current position estimate.
     * @return current position estimate.
     */
    const math::Vector2d &getPosition() const;

    /**
     * Obtains the current velocity estimate.
     * @return current velocity estimate.
     */
    const math::Vector2d &getVelocity() const;

    /**
     * Obtaints the current state uncertainty.
     * @return current state uncertainty.
     */
    const Eigen::MatrixXd &getCovariance() const;

private:
    std::shared_ptr<KalmanFilter> kalmanFilter;
    int cameraDelay;
    double sigmaAcc;
    Eigen::VectorXd acc;
    Eigen::MatrixXd A;
    Eigen::MatrixXd Q;
    math::Vector2d position;
    math::Vector2d velocity;
    Eigen::MatrixXd covariance;

    void compensateDelayAndAssign(Eigen::VectorXd &x, Eigen::MatrixXd &P);
};


#endif //KALMAN_FILTERING_BALLTRACKER_H
