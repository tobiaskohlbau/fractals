#ifndef FRACTAL_H_
#define FRACTAL_H_

#include <utility>

template<typename T>
struct Point {
	T x;
	T y;
};

template<typename T>
class Fractal {
public:
	virtual int getPoint(T x, T y, unsigned int max) = 0;
};

#endif // FRACTAL_H_
