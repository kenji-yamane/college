//
// Created by mmaximo on 3/16/18.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "Robot2DLocalizer.h"
#include "Robot2DSimulator.h"

int main() {
    std::ofstream groundTruthFile("robot2d_ground_truth.txt");
    std::ofstream observationFile("robot2d_observation.txt");
    std::ofstream estimateFile("robot2d_estimate.txt");

    double sigmaMotion = 0.2;
    double sigmaGPS = 0.2;
    double T = 0.1;
    Robot2DSimulator simulator(sigmaMotion, sigmaGPS, T);
    Robot2DLocalizer localizer(sigmaMotion, sigmaGPS, T);

    // We initialize the filter with an offset to show that it still converges to the correct mean in this case
    math::Vector2d initialPosition(0.1, 0.1);
    Eigen::MatrixXd initialCovariance = Eigen::MatrixXd::Identity(2, 2);
    localizer.reset(initialPosition, initialCovariance);

    double A = 1.0;
    double B = 1.0;
    double w1 = 3.0;
    double w2 = 2.0;
    double delta = M_PI / 2.0;
    math::Vector2d velocity;
    int numSteps = 600;
    for (int i = 0; i < numSteps; ++i) {
        double time = i * T;
        velocity.x = A * w1 * cos(w1 * time + delta);
        velocity.y = B * w2 * cos(w2 * time);

        simulator.update(velocity);
        localizer.predict(velocity);
        if (time < (2.0 / 6.0) * numSteps * T || time > (4.0 / 6.0) * numSteps * T) {
            // GPS fail
            math::Vector2d observation = simulator.observe();
            observationFile << time << " " << observation.x << " " << observation.y << std::endl;
            localizer.filter(observation);
        }
        math::Vector2d position = simulator.getPosition();
        groundTruthFile << time << " " << position.x << " " << position.y << std::endl;
        math::Vector2d estimate = localizer.getPosition();
        Eigen::MatrixXd covariance = localizer.getCovariance();
        estimateFile << time << " " << estimate.x << " " << estimate.y << " " << covariance(0, 0) << " "
                     << covariance(0, 1) << " " << covariance(1, 0) << " " << covariance(1, 1) <<
                     std::endl;
    }
    groundTruthFile.flush();
    observationFile.flush();
    estimateFile.flush();
    groundTruthFile.close();
    observationFile.close();
    estimateFile.close();
    return 0;
}