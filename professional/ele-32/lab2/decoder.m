function u = decoder(r,g, fp_syndromes)
    syndromeCycles = 0;
    wordCycles = 0;
    
    syndrome = get_syndrome(r, g);
    while syndrome ~= zeros(length(syndrome))
        if ismember(bi2de(syndrome), fp_syndromes)
            r(1) = r(1) + 1;
            r = mod(r, 2);
            syndrome = get_syndrome(r, g);
            syndromeCycles = 0;
            continue;
        end
        if syndromeCycles == length(syndrome)
            break;
        end
        syndrome = cycleSyndrome(syndrome, g);
        syndromeCycles = syndromeCycles + 1;
        r = cycleWord(r);
        wordCycles = mod(wordCycles + 1, length(r));
    end
    
    while wordCycles ~= 0
        r = cycleWord(r);
        wordCycles = mod(wordCycles + 1, length(r));
    end
    u = get_information(r, g);
end

function word = cycleWord(w)
    word = flip(conv(flip(w), flip([0 1])));
    if word(length(word)) == 1
        word(1) = word(1) + 1;
    end
    word(end) = [];
    word = mod(word, 2);
end

function syndrome = cycleSyndrome(s, g)
    syndrome = flip(conv(flip(s), flip([0 1])));
    if syndrome(length(syndrome)) == 1
        syndrome = syndrome + [g(1:length(g)-1) 0];
    end
    syndrome(end) = [];
    syndrome = mod(syndrome, 2);
end