function z = sampleObservationModel(x, l, R)
    z = zeros(2, 1);
    
    z(1) = sqrt((x(1) - l(1))^2 + (x(2) - l(2))^2);
    z(2) = atan2(l(2) - x(2), l(1) - x(1)) - x(3);
    
    z = mvnrnd(z, R);
end
