function y = bscCanal(x,p)

    if errorOccurs(p)        
        y = 1 - x;
    else
        y = x;
    end
    
end

function e = errorOccurs(p)
    r = random('Uniform', 0, 1);
    
    e = r<=p;
end