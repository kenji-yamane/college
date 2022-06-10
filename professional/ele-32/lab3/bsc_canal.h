#ifndef BSC_CANAL_H
#define BSC_CANAL_H

#include "random.h"

class BscCanal {
public:
	BscCanal(double p, Random *r);
	int transmit(int x);

private:
	double p;
	Random *r;

	bool errorHappened();
};

#endif

