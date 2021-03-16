function monteCarloPi(numPoints)
    amostral_x = rand(1, numPoints);
    amostral_y = rand(1, numPoints);
    
    amostral_norm = amostral_x.^2 + amostral_y.^2;
    inside = amostral_norm <= 1;
    outside = amostral_norm > 1;
    
    plot(amostral_x(inside), amostral_y(inside), '.b');
    hold on
    plot(amostral_x(outside), amostral_y(outside), '.r');
    
    fprintf('estimation of pi: %d\n', 4*length(find(inside == 1))/numPoints)
end
