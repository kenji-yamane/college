function bits = generateBits(n)
    bits = zeros(1, 1e6 - mod(1e6,n));
    
    for i = 1:length(bits)
       bits(i) = randi([0,1]) ;
    end

end