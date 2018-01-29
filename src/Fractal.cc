#include "Fractal.h"

template<typename T>
int Fractal<T>::getPoint(T x, T y, unsigned int max) {
	float xn = x;
	float yn = y;
	for (unsigned int i = 0; i < max; ++i) {
		auto p = this->n(xn, yn);
		xn = p.first;
		yn = p.second;
		int tmp = this->end(xn, yn);
		if (tmp)
			return tmp;
	}
	return -1;
}