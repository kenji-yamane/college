function runRobot2DLocalization()

system('../binaries/Robot2DLocalizer_ComponentTest');

groundTruth = load('robot2d_ground_truth.txt');
estimate = load('robot2d_estimate.txt');
observation = load('robot2d_observation.txt');

figure;
hold on;
numStepsXY = 60;
plot(groundTruth(1:numStepsXY, 2), groundTruth(1:numStepsXY, 3), 'LineWidth', 2);
plot(estimate(1:numStepsXY, 2), estimate(1:numStepsXY, 3), 'r', 'LineWidth', 2);
plot(observation(1:numStepsXY, 2), observation(1:numStepsXY, 3), 'g', 'LineWidth', 2);
axis equal
xlabel('X (m)');
ylabel('Y (m)');
grid on;
legend('Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

figure;
hold on;
time = groundTruth(:, 1);
timeObservation = observation(:, 1);
plot(time, groundTruth(:, 2), 'LineWidth', 2);
plot(time, estimate(:, 2), 'r', 'LineWidth', 2);
plot(timeObservation, observation(:, 2), 'g', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('X (m)');
grid on;
legend('Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

figure;
hold on;
time = groundTruth(:, 1);
timeObservation = observation(:, 1);
plot(time, groundTruth(:, 3), 'LineWidth', 2);
plot(time, estimate(:, 3), 'r', 'LineWidth', 2);
plot(timeObservation, observation(:, 3), 'g', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Y (m)');
grid on;
legend('Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

figure;
hold on;
time = estimate(:, 1);
plot(time, estimate(:, 4), 'b', 'LineWidth', 2);
plot(time, estimate(:, 5), 'r', 'LineWidth', 2);
plot(time, estimate(:, 7), 'g', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Variance (m^2)');
grid on;
legend('P_{11}', 'P_{12} = P_{21}', 'P_{22}');
set(gca, 'FontSize', 14);

end