//
// Created by mmaximo on 3/16/18.
//

#ifndef KALMAN_FILTERING_ROBOT2DLOCALIZER_H
#define KALMAN_FILTERING_ROBOT2DLOCALIZER_H

#include <Eigen/Core>
#include <memory>
#include "math/Vector2.h"
#include "KalmanFilter.h"

//namespace signal_processing {

/**
 * Localizer for a 2D robot with GPS.
 */
class Robot2DLocalizer {
public:
    /**
     * Constructs a 2D robot localizer.
     * @param sigmaMotion standard deviation of the velocity command.
     * @param sigmaGPS standard deviation of the GPS measurements.
     * @param T sample time.
     */
    Robot2DLocalizer(double sigmaMotion, double sigmaGPS, double T);

    /**
     * Resets the localizer to a given position and covariance.
     * @param resetPosition position to reset the localizer to.
     * @param resetCovariance covariance to reset the localizer to.
     */
    void reset(const math::Vector2d &resetPosition, const Eigen::MatrixXd &resetCovariance);

    /**
     * Executes a prediction step.
     * @param command velocity command.
     * @return new predicted state.
     */
    const math::Vector2d &predict(const math::Vector2d &command);

    /**
     * Executes a observation step.
     * @param observation GPS observation.
     * @return new filtered state.
     */
    const math::Vector2d &filter(const math::Vector2d &observation);

    /**
     * Obtains the current position estimate.
     * @return current position estimate.
     */
    const math::Vector2d &getPosition() const;

    /**
     * Obtains the current position uncertainty.
     * @return current position uncertainty.
     */
    const Eigen::MatrixXd &getCovariance() const;

private:
    std::shared_ptr<KalmanFilter> kalmanFilter;
    Eigen::VectorXd eigenAux;
    math::Vector2d position;
};

//}

#endif //KALMAN_FILTERING_ROBOT2DLOCALIZER_H
