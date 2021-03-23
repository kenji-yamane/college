//
// Created by mmaximo on 3/17/18.
//

#include <iostream>
#include <fstream>
#include "BallTracker.h"
#include "BallSimulator.h"

int main() {
    std::ofstream groundTruthFile("ball_ground_truth.txt");
    std::ofstream observationFile("ball_observation.txt");
    std::ofstream estimateFile("ball_estimate.txt");

    double sigmaAcceleration = 2.0;
    double sigmaCamera = 0.04;
    double T = 1.0 / 30.0;
    int cameraDelay = 2;

    BallTracker tracker(sigmaAcceleration, sigmaCamera, T, cameraDelay);
    BallSimulator simulator(sigmaAcceleration, sigmaCamera, T, cameraDelay);

    Eigen::VectorXd initialState = Eigen::VectorXd::Zero(4);
    Eigen::MatrixXd initialCovariance = 1.0e-2 * Eigen::MatrixXd::Identity(4, 4);
    tracker.resetFilter(initialState, initialCovariance);

    math::Vector2d velocity;
    double time;
    math::Vector2d lastObservation(0.0, 0.0);
    int numStepsPerSide = 100;
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0:
                velocity.x = 1.0;
                velocity.y = 0.0;
                break;
            case 1:
                velocity.x = 0.0;
                velocity.y = 1.0;
                break;
            case 2:
                velocity.x = -1.0;
                velocity.y = 0.0;
                break;
            case 3:
                velocity.x = 0.0;
                velocity.y = -1.0;
                break;
        }
        simulator.setVelocity(velocity);
        for (int j = 0; j < numStepsPerSide; ++j) {
            time = (i * numStepsPerSide + j) * T;
            simulator.update();
            math::Vector2d observation = simulator.observe();
            tracker.predictAndFilter(observation);
            math::Vector2d numericVelocity = (1.0 / T) * (observation - lastObservation); // numeric derivative
            groundTruthFile << time << " " << simulator.getPosition().x << " " << simulator.getPosition().y << " "
                            << simulator.getVelocity().x << " " << simulator.getVelocity().y << std::endl;
            observationFile << time << " " << observation.x << " " << observation.y << " " << numericVelocity.x << " "
                            << numericVelocity.y << std::endl;
            estimateFile << time << " " << tracker.getPosition().x << " " << tracker.getPosition().y << " "
                         << tracker.getVelocity().x << " " << tracker.getVelocity().y << std::endl;
            lastObservation = observation;
        }
    }

    groundTruthFile.flush();
    observationFile.flush();
    estimateFile.flush();
    groundTruthFile.close();
    observationFile.close();
    estimateFile.close();
}