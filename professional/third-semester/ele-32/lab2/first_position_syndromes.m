function syndromes = first_position_syndromes(k, g)
    gen = generator();
    gen = generateSpace(gen, k);
    
    input_size = size(gen.space);
    input_size = input_size(1);

    syndromes = [];
    for i = 1:input_size
        u = gen.space(i,:);
        transmitted = flip(conv(flip(g), flip(u)));
        transmitted = mod(transmitted, 2);
        received = transmitted;
        received(1) = received(1) + 1;
        received = mod(received, 2);
        syndrome = get_syndrome(received, g);
        if ~ismember(bi2de(syndrome), syndromes)
            syndromes = [syndromes bi2de(syndrome)];
            sort(syndromes);
        end
    end
end