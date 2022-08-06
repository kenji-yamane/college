classdef generator
    properties
        space
    end
    methods
        function g = generateSpace(g, n)
            g.space = [];
            g = recursiveGenerate(g, n, [], 1);
        end

        function g =  recursiveGenerate(g, n, u, i)
            if i > n
                g.space = [g.space ; u];
                return
            end

            g = recursiveGenerate(g, n, [u 0], i + 1);
            g = recursiveGenerate(g, n, [u 1], i + 1);
        end
    end
end