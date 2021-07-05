#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#include <Eigen/Dense>

class RungeKutta {
public:
	RungeKutta(double step, std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f);
	~RungeKutta() = default;
	double getTime();
	void secondOrder(Eigen::VectorXd &orbitPoint);
	void fourthOrder(Eigen::VectorXd &orbitPoint);

private:
	double step, time;
	std::function<Eigen::VectorXd(const Eigen::VectorXd&)> orbitFunction;
};

#endif // RUNGEKUTTA_H

