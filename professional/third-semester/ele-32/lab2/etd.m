function decoded = etd(u,p, g, fp_syndromes)
    transmitted = encoder(u, g);
    received = zeros(1,length(transmitted));
    
    for i=1:length(transmitted)
       received(i) = bscCanal(transmitted(i),p); 
    end
    decoded = decoder(received, g, fp_syndromes);
end