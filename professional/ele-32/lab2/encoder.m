function v = encoder(u,g)
    u = flip(u,2);
    g = flip(g,2);

    v = flip(conv(u,g),2);
    v = mod(v,2);
end