#include "Newton.hpp"
#include "Mandelbrot.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <memory>
#include <utility>

template<typename T>
std::pair<T, T> steps(int height, int width, T left, T right, T bottom, T top) {
	T xres = (std::abs(left) + std::abs(right)) / width;
	T yres = (std::abs(top) + std::abs(bottom)) / height;
	return std::pair<T, T>(xres, yres);
}

cv::Mat calc(Fractal<double> *fract, int height, int width, double left, double right, double top, double bottom) {
	cv::Mat img(height, width, CV_8UC1);
	auto res = steps(height, width, left, right, top, bottom);
	double x = left;
	double y = top;
	for (int r = 0; r < img.rows; ++r, y += res.second) {
		x = left;
		auto pixel = img.ptr<uchar>(r);
		for (int c = 0; c < img.cols; ++c, x += res.first) {
			int val = fract->getPoint(x, y, 15);
			if (val == -1)
				*pixel = 0;
			else
				*pixel = 255;
			pixel++;
		}
	}
	return img;
}

int main(int argc, char **argv) {
	std::unique_ptr<Fractal<double>> nwt = std::make_unique<Newton<double>>();
	std::unique_ptr<Fractal<double>> mbt = std::make_unique <Mandelbrot<double>>();
	//Newton<double> nwt;
	//Mandelbrot<double> mbt;

	auto inwt = calc(nwt.get(), 1080, 1920, -2.0, 2.0, -1.5, 1.5);
	auto imbt = calc(mbt.get(), 1080, 1920, -2.0, 2.0, -1.5, 1.5);
	
	cv::imwrite("newton.png", inwt, { CV_IMWRITE_PNG_COMPRESSION, 9});
	cv::imwrite("mandelbrot.png", imbt, { CV_IMWRITE_PNG_COMPRESSION, 9 });
}