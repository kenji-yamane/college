//
// Created by mmaximo on 3/17/18.
//

#include <iostream>
#include <fstream>
#include "DDRLocalizer.h"
#include "DDRSimulator.h"

int main() {
    std::ofstream groundTruthFile("ddr_ground_truth.txt");
    std::ofstream observationFile("ddr_observation.txt");
    std::ofstream estimateFile("ddr_estimate.txt");

    double sigmaLinearSpeed = 0.05;
    double sigmaAngularSpeed = 0.02;
    double sigmaCameraCartesian = 0.1;
    double sigmaCameraAngle = 0.04;
    double T = 1.0 / 30.0;

    DDRLocalizer localizer(T, sigmaLinearSpeed, sigmaAngularSpeed, sigmaCameraCartesian, sigmaCameraAngle);
    DDRSimulator simulator(T, sigmaLinearSpeed, sigmaAngularSpeed, sigmaCameraCartesian, sigmaCameraAngle);

    math::Pose2D initialPose(5.0 * M_PI / 180.0, 0.0, 0.05);
    Eigen::MatrixXd initialCovariance = 1.0e-3 * Eigen::MatrixXd::Identity(3, 3);
    localizer.reset(initialPose, initialCovariance);

    double linearSpeed = 0.1;
    double angularSpeed = 20.0 * M_PI / 180.0;
    double time = 0.0;
    const double simulationTime = 10.0;
    while (time < simulationTime) {
        time += T;
        simulator.update(linearSpeed, angularSpeed);
        math::Pose2D observation = simulator.observe();
        localizer.predict(linearSpeed, angularSpeed);
        localizer.filter(observation);
        groundTruthFile << time << " " << simulator.getPose().translation.x << " " << simulator.getPose().translation.y << " "
                        << simulator.getPose().rotation << std::endl;
        observationFile << time << " " << observation.translation.x << " " << observation.translation.y << " " << observation.rotation << std::endl;
        estimateFile << time << " " << localizer.getPose().translation.x << " " << localizer.getPose().translation.y << " "
                     << localizer.getPose().rotation << std::endl;
    }

    groundTruthFile.flush();
    observationFile.flush();
    estimateFile.flush();
    groundTruthFile.close();
    observationFile.close();
    estimateFile.close();
}