numSteps = 800;

truePos = zeros(numSteps, 3);
deadReckon = zeros(numSteps, 3);
truePos(1, :) = [0; 0; 0];
deadReckon(1, :) = [0; 0; 0];
for i=2:numSteps
    truePos(i, :) = sampleMotionModel(truePos(i - 1, :), [1; 0; 0.1], 1/30, diag([0.4, 0.4, 0.1]));
    deadReckon(i, :) = sampleMotionModel(deadReckon(i - 1, :), [1; 0; 0.1], 1/30, zeros(3));
end

plot(truePos(:, 1), truePos(:, 2), '.b');
hold on
plot(deadReckon(:, 1), deadReckon(:, 2), '.r');
