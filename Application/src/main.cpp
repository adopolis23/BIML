#include <stdio.h>

#include "BIML.h"

int main() {

	biml::Image img("Images/coins.pgm");

	img.Convolve(biml::Kernel(biml::KernelType::SOBEL_X, 5));

	img.Save("Images/coins_sobel.pgm");

	return 0;
}