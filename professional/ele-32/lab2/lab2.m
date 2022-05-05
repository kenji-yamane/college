% n = 14
c14 = cyclpoly(14,8,'all');
g = generator();
g = generateSpace(g,7);

[m, index_m] = get_min(c14, g.space(2:end,:));
c14 = c14(index_m,:);

encoder(g.space(5,:), c14)

% hamming code on cyclical form
g_test = [1 1 0 1];

for i=1:7
    to_transmit = [1 1 1 1];
    transmitted = encoder(to_transmit, g_test);
    received = transmitted;
    received(i) = mod((received(i) + 1), 2);
    fp_syndromes = first_position_syndromes(4, g_test);
    decoded = decoder(received, g_test, fp_syndromes);
    if decoded ~= to_transmit
        disp(":(");
    end
end
