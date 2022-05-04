% n = 14
c14 = cyclpoly(14,8,'all');
g = generator();
g = generateSpace(g,7);

[m, index_m] = get_min(c14, g.space(2:end,:));
c14 = c14(index_m,:);

encoder(g.space(5,:), c14)

