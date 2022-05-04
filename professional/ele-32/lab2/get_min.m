function [min, index] = get_min(code_generator, u)
    index = -1;
    code_size = size(code_generator);
    code_size = code_size(1);
    
    u_size = size(u);
    u_size = u_size(1);
    
    min = zeros(1,code_size);

    for i = 1:code_size
        min(i) = inf;
        for u_i = 1:u_size
            g = flip(code_generator(i,:),2);
            x = conv(g,u(u_i,:));
            
            if norm(x,1) < min(i)
               min(i) = norm(x,1);
            end
        end
    end
    
   max_min = max(min);
   
   for i = 1:code_size
       if max_min == min(i)
           index = i;
       end
   end
end