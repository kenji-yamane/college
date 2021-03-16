numOfSamples = 10000;

distr = zeros(numOfSamples, 3);

for i=1:numOfSamples
    distr(i, :) = sampleMotionModel([0; 0; 0], [1; 1; 0], 1, diag([0.01, 0.01, 1]));
end

plot(distr(:, 1), distr(:, 2), '.b');
figure
plot(1:numOfSamples, distr(:, 3), '.b');
% None of the results look like a normal distribution
% Which is natural because the random variable passes
% through many unlinear calculations
