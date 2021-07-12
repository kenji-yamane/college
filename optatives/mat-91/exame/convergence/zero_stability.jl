using Plots

include("../bdf_utils.jl")

Plots.scalefontsizes()
Plots.scalefontsizes(1.6)
circle =  exp.(im.*(0:0.001:2*pi))
for (i, p) in enumerate(rhos)
	r = Complex.(roots(p))
	plot(circle, legend=false, fontfamily="computer modern")
	scatter!(r, aspect_ratio=:equal, framestyle=:origin, markersize=8)
	savefig("../figures/roots$i.pdf")
end
