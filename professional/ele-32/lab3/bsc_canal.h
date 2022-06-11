#ifndef BSC_CANAL_H
#define BSC_CANAL_H

#include "random.h"

class BscCanal {
public:
	BscCanal(double, Random);
	int transmit(int);

private:
	double p;
	Random *r;

	bool errorHappened();
};

#endif

