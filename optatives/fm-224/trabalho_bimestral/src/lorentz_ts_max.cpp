#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <cmath>

#define TS_SIZE 80000
#define STEPS_TO_ONE 64
#define PERIOD 50
#define TAU 9
#define EPSILON 1e-8
#define INF 100000

void tsToEigen(std::vector<double> &ts, Eigen::VectorXd &v, int posic) {
	v << ts[posic + 2*TAU], ts[posic + TAU], ts[posic];
}

int main() {
	std::vector<double> time_series;
	std::ifstream time_series_file("../lorentz_time_series.txt");
	time_series.resize(TS_SIZE);
	for (int i = 0; i < TS_SIZE; i++) {
		time_series_file >> time_series[i];
	}
	time_series_file.close();

	Eigen::VectorXd referencePoint(3), travelingPoint(3);
	int iReference = 0, iTraveling;
	tsToEigen(time_series, referencePoint, iReference);

	double minSoFar = INF;
	for (int i = 40*TAU; i + 2*TAU + STEPS_TO_ONE < TS_SIZE; i++) {
		Eigen::VectorXd aux(3);
		tsToEigen(time_series, aux, i);
		
		double dist = (aux - referencePoint).norm();
		if (dist < minSoFar and dist > EPSILON) {
			minSoFar = dist;
			travelingPoint = aux;
			iTraveling = i;
		}
	}

	std::ofstream meanConv("../logs/ts_mean_convergence.txt");
	double maxLyapunov = 0;
	for (int i = 0; iReference + STEPS_TO_ONE + 2*TAU < TS_SIZE; i++) {
		double before = (referencePoint - travelingPoint).norm();

		iReference += STEPS_TO_ONE;
		iTraveling += STEPS_TO_ONE;
		tsToEigen(time_series, referencePoint, iReference);
		tsToEigen(time_series, travelingPoint, iTraveling);

		double after = (referencePoint - travelingPoint).norm();

		maxLyapunov = (maxLyapunov*i + std::log2(after/before))/(i + 1);
		meanConv << maxLyapunov << std::endl;
		
		minSoFar = INF;
		for (int j = 0; j + 2*TAU + STEPS_TO_ONE < TS_SIZE; j++) {
			Eigen::VectorXd aux(3);
			tsToEigen(time_series, aux, j);

			if ((aux - travelingPoint).norm() > EPSILON) {
				Eigen::VectorXd refToTrav = travelingPoint - referencePoint;
				Eigen::VectorXd refToAux = aux - referencePoint;

				double dist = refToAux.norm();
				double angle = std::acos(refToTrav.dot(refToAux)/refToTrav.norm()/dist);

				if (dist + angle < minSoFar) {
					minSoFar = dist + angle;
					travelingPoint = aux;
					iTraveling = j;
				}
			}
		}
	}
	meanConv.close();

	std::cout << "max lyapunov exponent estimate: ";
	std::cout << maxLyapunov << std::endl;

	return 0;
}

