#ifndef NEWTON_H_
#define NEWTON_H_

#include "Fractal.hpp"
#include <utility>
#include <cmath>

template<typename T>
class Newton : public Fractal<T> {
public:
	Newton() = default;
	~Newton() = default;

	int getPoint(T x, T y, unsigned int max) {
		T xn = x;
		T yn = y;
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
private:
	constexpr static double eps = 0.025;

	std::pair<T, T> n(T xn, T yn) {
		T x2 = xn * xn;
		T y2 = yn * yn;
		T xy2 = (x2 + y2)*(x2 + y2);
		T x = (2.0 / 3.0) * xn + ((x2 - y2) / (3 * xy2));
		T y = (2.0 / 3.0) * (yn - ((xn*yn) / xy2));
		return std::pair<T, T>(x, y);
	}

	int end(T xn, T yn) {
		if (belongsTo(xn, yn, Point<T>{ 1.0, 0.0 }))
			return 1;
		if (belongsTo(xn, yn, Point<T>{ -0.5, 0.86666 }))
			return 2;
		if (belongsTo(xn, yn, Point<T>{ -0.5, -0.86666 }))
			return 3;
		return 0;
	}

	bool belongsTo(T x, T y, Point<T> p) {
		T x2 = (x - p.x)*(x - p.x);
		T y2 = (y - p.y)*(y - p.y);
		if ((x2 + y2) < eps)
			return true;
		return false;
	}
};

#endif // NEWTON_H_
