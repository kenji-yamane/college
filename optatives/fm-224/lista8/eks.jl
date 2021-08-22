using Plots
using Printf

rk_step = 0.0015
n = 16
init_discard_len = 30000
orbit_len = 100000
epsilon = 1e-3

function take(U, i)
	if i == 0 || i < -n || i > n
		return 0
	end
	if i < 0
		return -U[-i]
	end
	return U[i]
end

function fourth_order_rk(f, U)
	F0 = f(U)
	F1 = f(U .+ rk_step/2*F0)
	F2 = f(U .+ rk_step/2*F1)
	F3 = f(U .+ rk_step*F2)

	U = U .+ (rk_step/6).*(F0 .+ 2*F1 .+ 2*F2 .+ F3)
	return U
end

eks(U, v) = [(k^2-v*k^4)*take(U, k) - sum([take(U, m)*take(U, k-m) for m=-n:n])*k/2 for k in 1:n]

horizontal = zeros(0)
vertical = zeros(0)
for v in 0.02985:0.000001:0.03048
	for j = 1:3
		orbit_point = rand(Float64, n)
		for i = 1:init_discard_len
			orbit_point = fourth_order_rk(U -> eks(U, v), orbit_point)
			if sqrt(sum([orbit_point[i]^2 for i in 1:n])) > 1e4
				break
			end
		end
		next_len = orbit_len
		if v > 0.03
			next_len = orbit_len/20
		end
		for i = 1:next_len
			if sqrt(sum([orbit_point[i]^2 for i in 1:n])) > 1e4
				break
			end
			orbit_point = fourth_order_rk(U -> eks(U, v), orbit_point)
			if abs(orbit_point[1]) < epsilon && eks(orbit_point, v)[1] > 0
				append!(horizontal, v)
				append!(vertical, orbit_point[2])
			end
		end
	end
end

scatter(horizontal, vertical, markersize=1)
savefig("bifurcation_diagram.png")

