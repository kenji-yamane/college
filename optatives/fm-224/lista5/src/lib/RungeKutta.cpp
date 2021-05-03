#include "RungeKutta.h"

RungeKutta::RungeKutta(double step, std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f) {
	this->time = 0;
	this->step = step;
	this->orbitFunction = f;
}

double RungeKutta::getTime() {
	return this->time;
}

void RungeKutta::secondOrder(Eigen::VectorXd &orbitPoint) {
	Eigen::VectorXd v1, v2;

	v1 = this->step*this->orbitFunction(orbitPoint);
	v2 = this->step*this->orbitFunction(orbitPoint + v1/2);

	orbitPoint += v2;
	this->time += this->step;
}

void RungeKutta::fourthOrder(Eigen::VectorXd &orbitPoint) {
	Eigen::VectorXd v1, v2, v3, v4;

	v1 = this->step*this->orbitFunction(orbitPoint);
	v2 = this->step*this->orbitFunction(orbitPoint + v1/2);
	v3 = this->step*this->orbitFunction(orbitPoint + v2/2);
	v4 = this->step*this->orbitFunction(orbitPoint + v3);

	orbitPoint += (v1 + 2*v2 + 2*v3 + v4)/6;
	this->time += step;
}

