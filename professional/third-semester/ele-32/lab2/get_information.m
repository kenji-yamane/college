function u = get_information(r,g)
    r = flip(r,2);
    g = flip(g,2);
    
    [u,s] = deconv(r,g);
    
    u = flip(u,2);
    u = mod(u,2);
    u = u(1:length(r) - length(g) + 1);
end