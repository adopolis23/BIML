#pragma once
#include "Image.h"
#include "Kernel.h"
#include <iostream>
#include <chrono>

namespace biml {


	void Binarize(Image& img, int threshold);
	void UniformSmooth(Image& img, int ws);
	void Sobel(Image& img, int ws, int dir);

};