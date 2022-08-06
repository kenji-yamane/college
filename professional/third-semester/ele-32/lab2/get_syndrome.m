function s = get_syndrome(r,g)
    r = flip(r,2);
    g = flip(g,2);
    
    [q,s] = deconv(r,g);
    
    s = flip(s,2);
    s = mod(s,2);
    s = s(1:length(g) - 1);
end