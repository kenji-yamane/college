function runDDRLocalization()

system('../binaries/DDR_ComponentTest');

groundTruth = load('ddr_ground_truth.txt');
estimate = load('ddr_estimate.txt');
observation = load('ddr_observation.txt');

figure;
hold on;
numStepsXY = 300;
plot(groundTruth(1:numStepsXY, 2), groundTruth(1:numStepsXY, 3), 'LineWidth', 2);
plot(estimate(1:numStepsXY, 2), estimate(1:numStepsXY, 3), 'r', 'LineWidth', 2);
plot(observation(1:numStepsXY, 2), observation(1:numStepsXY, 3), '.g', 'MarkerSize', 10);
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
h3 = plot(timeObservation, observation(:, 2), 'g', 'LineWidth', 2);
h1 = plot(time, groundTruth(:, 2), 'LineWidth', 2);
h2 = plot(time, estimate(:, 2), 'r', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('X (m)');
grid on;
legend([h1 h2 h3], 'Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

figure;
hold on;
time = groundTruth(:, 1);
timeObservation = observation(:, 1);
h3 = plot(timeObservation, observation(:, 3), 'g', 'LineWidth', 2);
h1 = plot(time, groundTruth(:, 3), 'LineWidth', 2);
h2 = plot(time, estimate(:, 3), 'r', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Y (m)');
grid on;
legend([h1 h2 h3], 'Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

figure;
hold on;
time = groundTruth(:, 1);
timeObservation = observation(:, 1);
h3 = plot(timeObservation, observation(:, 4) * 180 / pi, 'g', 'LineWidth', 2);
h1 = plot(time, groundTruth(:, 4) * 180 / pi, 'LineWidth', 2);
h2 = plot(time, estimate(:, 4) * 180 / pi, 'r', 'LineWidth', 2);
xlabel('Time (s)');
ylabel('\psi (º)');
grid on;
legend([h1 h2 h3], 'Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);

end