numSamples = 10000;

distr = zeros(numSamples, 2);

for i=1:numSamples
    distr(i, :) = sampleObservationModel([0; 0; 0], [1; 1], diag([0.01, 0.1]));
end

plot(distr(:, 1).*cos(distr(:, 2)), distr(:, 1).*sin(distr(:, 2)), '.b')
% Again something other than a gaussian, for there are unlinear
% calculations
