function runMonteCarlo()

Nc = 500;

sumSquaredErrorPosition = 0;
sumSquaredErrorAngle = 0;
for i=1:Nc
    if mod(i, 10) == 0
        fprintf('Progress: %d/%d\n', i, Nc);
    end
    
    system('../binaries/DDR_ComponentTest');

    groundTruth = load('ddr_ground_truth.txt');
    estimate = load('ddr_estimate.txt');
%     observation = load('ddr_observation.txt');
    
    sumSquaredErrorPosition = sumSquaredErrorPosition + (groundTruth(:,2) - estimate(:,2)).^2 +...
        (groundTruth(:,3) - estimate(:,3)).^2;
    sumSquaredErrorAngle = sumSquaredErrorAngle + wrapToPi(groundTruth(:,4) - estimate(:,4)).^2;
end

time = groundTruth(:, 1);
rmsePosition = sqrt(sumSquaredErrorPosition / Nc);
rmseAngle = sqrt(sumSquaredErrorAngle / Nc);

figure;
plot(time, rmsePosition, 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Position RMSE (m)');
set(gca, 'FontSize', 14);
grid on;

figure;
plot(time, rmseAngle, 'LineWidth', 2);
xlabel('Time (s)');
ylabel('Angle RMSE (rad)');
set(gca, 'FontSize', 14);
grid on;

monteCarlo.time = time;
monteCarlo.rmsePosition = rmsePosition;
monteCarlo.rmseAngle = rmseAngle;
save('monte_carlo.mat', 'monteCarlo');

end