order = 9
diffs = [
    begin
        [((-1)^m)*binomial(i, m) for m in 0:order]
    end for i in 1:order
]

right = factorial(order)
weights = [right/i for i in 1:order]

left = zeros(Int64, order + 1)
for (i, diff) in enumerate(diffs)
    left .+= weights[i].*diff
end

common_div = right
for el in left
    global common_div = gcd(common_div, el)
end
println("alphas: ", reverse(left.÷common_div))
println("betas: ", [zeros(Int64, order)..., right÷common_div])
