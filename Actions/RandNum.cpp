#include "RandNum.h"

int RandNum::RandomShape() {
	srand(time(nullptr));
	xs = rand() % 5;
	return xs;
}
int RandNum::RandomColor() {
	srand(time(nullptr));
	xc = rand() % 6;
	return xc;
}
RandNum::RandNum() {
	xs = -1;
	xc = -1;
}

