using Plots

include("../bdf_utils.jl")

Plots.scalefontsizes()
Plots.scalefontsizes(1.6)
t = range(0, 2*pi, length=1000)

plot(color=:orange, aspect_ratio=:equal, fontfamily="computer modern", framestyle=:origin)
for i in 1:2
    z = exp.(im.*t) .|> (x) -> rhos[i](x)/sigmas[i](x)
    plot!(z, label="BDF$i")
end
savefig("../figures/a_stables.pdf")

plot(color=:orange, aspect_ratio=:equal, fontfamily="computer modern", framestyle=:origin)
for i in 3:6
    z = exp.(im.*t) .|> (x) -> rhos[i](x)/sigmas[i](x)
    plot!(z, label="BDF$i")
end
savefig("../figures/a_unstables.pdf")

plot(color=:orange, legend=false, aspect_ratio=:equal, fontfamily="computer modern", framestyle=:origin)
for i in 7:7
    z = exp.(im.*t) .|> (x) -> rhos[i](x)/sigmas[i](x)
    plot!(z)
end
savefig("../figures/seventh.pdf")

plot(color=:orange, aspect_ratio=:equal, fontfamily="computer modern", framestyle=:origin)
for i in 7:7
    z = exp.(im.*t) .|> (x) -> rhos[i](x)/sigmas[i](x)
    plot!(z, label="BDF$i", xlims=(-2, 2), ylims=(-2, 2))
end
savefig("../figures/seventh_zoom.pdf")
