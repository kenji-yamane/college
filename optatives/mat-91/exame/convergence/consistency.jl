include("../bdf_utils.jl")

for (alpha,beta) in zip(bdf_alphas,bdf_betas)
    println(sum(alpha), " ", sum([(j - 1)*alpha[j] - beta[j] for j in 1:length(alpha)]))
end
