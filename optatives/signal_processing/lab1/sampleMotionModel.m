function xNew = sampleMotionModel(x, v, T, Q)
    xNew = zeros(3, 1);
    
    v = mvnrnd(v, Q);
    
    final = x(3) + v(3)*T/2;
    delta = v(3)*T/2;
    
    xNew(1) = x(1) + 2*v(1)/v(3)*cos(final)*sin(delta) - 2*v(2)/v(3)*sin(final)*sin(delta);
    xNew(2) = x(2) + 2*v(1)/v(3)*sin(final)*sin(delta) + 2*v(2)/v(3)*cos(final)*sin(delta);
    xNew(3) = x(3) + v(3)*T;
end
