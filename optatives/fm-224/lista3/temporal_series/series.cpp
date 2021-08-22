#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define ALPHA 1.276
#define BETA 0.3
#define EPSILON 1e-3
#define NUMCYCLES 4000
#define CYCLESIZE 3

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

	void pasteTime(std::ofstream &out, int cycle) {
		out << cycle << ", " << this->x << std::endl;
	}

	void debug() {
		std::cout << this->x << ", " << this->y << std::endl;
	}

	Dot iterate() {
		return {ALPHA - this->x*this->x + BETA*this->y, this->x};
	}

private:
	double x;
	double y;
};

int main(int argc, char **argv) {
	std::ofstream timeSeries("registry.txt");

	Dot d(0.5, 0.5);

	for (int i = 0; i < NUMCYCLES; i++) {
		for (int j = 0; j < CYCLESIZE; j++) {
			d = d.iterate();

			if (i > 3000) {
				d.pasteTime(timeSeries, i);
			}
		}
	}

	timeSeries.close();

	return 0;
}

