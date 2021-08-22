function runRobot2DMonteCarlo()

Nc = 1000;

sumSquaredError = 0;
for i=1:Nc
    if mod(i, 10) == 0
        fprintf('Progress: %d/%d\n', i, Nc);
    end
    system('../binaries/Robot2DLocalizer_ComponentTest');
    groundTruth = load('robot2d_ground_truth.txt');
    estimate = load('robot2d_estimate.txt');
    sumSquaredError = sumSquaredError + (groundTruth(:,2) - estimate(:,2)).^2 +...
        (groundTruth(:,3) - estimate(:,3)).^2;
end

time = groundTruth(:, 1);
rmse = sqrt(sumSquaredError / Nc);
plot(time, rmse, 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Position RMSE (m)');
set(gca, 'FontSize', 14);
grid on;

end