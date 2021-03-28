#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define ALPHA 1.276
#define BETA 0.3
#define EPSILON 1e-3

class Dot {
public:
	Dot() : x(0), y(0) {}
	Dot(double x, double y) : x(x), y(y) {}
	~Dot() = default;

	Dot operator-(const Dot &other) {
		return {this->x - other.x, this->y - other.y};
	}

	Dot operator+(const Dot &other) {
		return {this->x + other.x, this->y + other.y};
	}

	Dot operator*(const double &factor) {
		return {this->x*factor, this->y*factor};
	}

	Dot operator/(const double &factor) {
		return {this->x/factor, this->y/factor};
	}

	double abs() {
		return std::sqrt(this->x*this->x + this->y*this->y);
	}

	double angle(Dot &other) {
		return acos((this->x*other.x + this->y*other.y)/(this->abs()*other.abs()));
	}

	void pasteOut(std::ofstream &out) {
		out << this->x << ", " << this->y << std::endl;
	}

	void debug() {
		std::cout << this->x << ", " << this->y << std::endl;
	}

	Dot iterateOne() {
		return {ALPHA - this->x*this->x + BETA*this->y, this->x};
	}

	Dot iterate() {
		Dot d(this->x, this->y);
		for (int i = 0; i < 7; i++) {
			d = d.iterateOne();
		}

		return d;
	}

private:
	double x;
	double y;
};

class Box {
public:
	Box(Dot lt, Dot rt, Dot rb, Dot lb) : lt(lt), rt(rt), rb(rb), lb(lb) {}

	void generateGrid(double width, double height) {
		Dot down = (lb - lt)/height, right = (rt - lt)/width;

		for (Dot di = lt + down + right; this->isInside(di); di = di + down) {
			for (Dot dj = di + down + right; this->isInside(dj); dj = dj + right) {
				grid.push_back(dj);
			}
		}
	}

	void iterate(int numIter) {
		for (auto &d : grid) {
			Dot start = d, mid;
			for (int i = 0; i < numIter; i++) {
				d = d.iterate();
				if (not this->isInside(d)) break;
				if (i == numIter/2) mid = d;
			}

			if (this->isInside(d)) {
				stable.push_back(start);
				saddle.push_back(mid);
				unstable.push_back(d);
			}
		}
	}

	bool isInside(Dot d) {
		Dot toLt = (this->lt - d), toRt = (this->rt - d);
		Dot toLb = (this->lb - d), toRb = (this->rb - d);

		if (toLt.abs() < EPSILON or toRt.abs() < EPSILON
			or toRb.abs() < EPSILON or toLb.abs() < EPSILON) {
			return true;
		} else {
			double angle = 0;

			angle += toLt.angle(toRt) + toRt.angle(toRb);
			angle += toRb.angle(toLb) + toLb.angle(toLt);

			return fabs(angle - 2*M_PI) < EPSILON;
		}
	}

	void pasteOut(std::ofstream &fStable, std::ofstream &fUnstable, std::ofstream &fSaddle) {
		std::cout << "out size: " << this->stable.size() << std::endl;
		for (auto &d : this->stable) {
			d.pasteOut(fStable);
		}
		for (auto &d : this->unstable) {
			d.pasteOut(fUnstable);
		}
		for (auto &d : this->saddle) {
			for (int i = 0; i < 7; i++) {
				d.pasteOut(fSaddle);
				d = d.iterateOne();
			}
		}
	}

private:
	Dot lt;
	Dot rt;
	Dot rb;
	Dot lb;

	std::vector<Dot> grid;
	std::vector<Dot> stable;
	std::vector<Dot> unstable;
	std::vector<Dot> saddle;
};

int main(int argc, char **argv) {
	Box b({-1.5, 2}, {-1.28131688, 2}, {-0.87424729, -1.5}, {-1.5, -1.5});
	//Box b({-1.28131688, 2}, {2, 2}, {2, -1.5}, {-0.87424729, -1.5});

	b.generateGrid(2000, 2000);
	b.iterate(10);

	std::ofstream st("stable.txt");
	std::ofstream unst("unstable.txt");
	std::ofstream sadd("saddle.txt");

	b.pasteOut(st, unst, sadd);

	st.close();
	unst.close();
	sadd.close();

	return 0;
}

