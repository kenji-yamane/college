function runBallTracking()

system('../binaries/BallTracker_ComponentTest');

groundTruth = load('ball_ground_truth.txt');
estimate = load('ball_estimate.txt');
observation = load('ball_observation.txt');

figure;
hold on;
plot(groundTruth(:, 2), groundTruth(:, 3), 'LineWidth', 2);
plot(estimate(:, 2), estimate(:, 3), 'r', 'LineWidth', 2);
plot(observation(:, 2), observation(:, 3), 'g', 'LineWidth', 2);
xlabel('X (m)');
ylabel('Y (m)');
legend('Ground Truth', 'Estimate', 'Observation');
set(gca, 'FontSize', 14);
axis equal
grid on;

figure;
hold on;
time = groundTruth(:, 1);
h3 = plot(time, observation(:, 4), 'g', 'LineWidth', 2);
h2 = plot(time, estimate(:, 4), 'r', 'LineWidth', 2);
h1 = plot(time, groundTruth(:, 4), 'LineWidth', 2);
xlabel('Time (s)');
ylabel('X Speed (m/s)');
legend([h1 h2 h3], 'Ground Truth', 'Estimate', 'Numeric Derivative');
set(gca, 'FontSize', 14);
grid on;
xlim([0 time(end)]);


figure;
hold on;
time = groundTruth(:, 1);
h3 = plot(time, observation(:, 5), 'g', 'LineWidth', 2);
h2 = plot(time, estimate(:, 5), 'r', 'LineWidth', 2);
h1 = plot(time, groundTruth(:, 5), 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Y Speed (m/s)');
legend([h1 h2 h3], 'Ground Truth', 'Estimate', 'Numeric Derivative');
set(gca, 'FontSize', 14);
grid on;
xlim([0 time(end)]);

end