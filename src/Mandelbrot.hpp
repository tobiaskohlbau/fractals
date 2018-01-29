#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include "Fractal.hpp"
#include <utility>
#include <cmath>

template<typename T>
class Mandelbrot : public Fractal<T> {
public:
	Mandelbrot() = default;
	~Mandelbrot() = default;

	int getPoint(T x, T y, unsigned int max) override {
		T xn = x;
		T yn = y;
		for (unsigned int i = 0; i < max; ++i) {
			auto p = this->n(xn, yn, x, y);
			xn = p.first;
			yn = p.second;
			int tmp = this->end(xn, yn);
			if (tmp)
				return tmp;
		}
		return -1;
	}
private:
	constexpr static double eps = 4;

	std::pair<T, T> n(T xn, T yn, T cx, T cy) {
		T x = xn * xn - yn * yn + cx;
		T y = 2 * xn * yn + cy;
		return std::pair<T, T>(x, y);
	}

	int end(T xn, T yn) {
		if ((xn*xn + yn*yn) > eps)
			return 1;
		return 0;
	}
};

#endif // MANDELBROT_H_