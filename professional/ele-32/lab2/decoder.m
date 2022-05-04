function decoder(r,g)
    syndromeCycles = 0;
    wordCycles = 0;
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