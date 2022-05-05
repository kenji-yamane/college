n = 20;
k = 11;
c = cyclpoly(n,k,'all');
u_size = n - length(c) + 1;
% g = generator();
% g = generateSpace(g,u_size);

g = dec2bin(0:2^u_size-1) - '0';

[m, index_m] = get_min(c, g(2:end,:));
g = c(index_m,:);

pVectorBase = [0.5, 0.2, 0.1];
pVector = [0.5, 0.2, 0.1];

for i = 1:5
    fator = 10^i;
    pVector = [pVector pVectorBase/fator];
end

pVector = sort(pVector);

statistics = zeros(1, length(pVector));

for loop_i = 1:length(pVector)
%     loop_i = 1
    p = pVector(loop_i);
    
%     display("p selected")
    bits = generateBits(u_size);
    
%     display("bits generated");
    bitsGroups = zeros((length(bits)/u_size), u_size);
    
    for i=1:(length(bits)/u_size)
        bitsGroups(i,:) = bits(u_size*(i-1)+1:u_size*(i-1)+u_size);
    end
    
%     display("bits grouped");   
    decodeMatrix = zeros((length(bits)/u_size), u_size);
    
%     display("decoding");
    
    fp_syndromes = first_position_syndromes(u_size, g);
    
    for i=1:(length(bits)/u_size)
        decodeMatrix(i,:) = etd(bitsGroups(i,:),p,g, fp_syndromes);
    end

    
    decodeVector = reshape(transpose(decodeMatrix),1,[]);
    incorrect = sum(mod(bits+decodeVector,2));
    
    statistics(loop_i) = incorrect/(1e6-mod(1e6,u_size));
    
end

display("finished all");
