#include <stdio.h>

#include "BIML.h"

int main() {

	biml::Image img("Images/coins.ppm");


	img.Save("Images/coins_saved.ppm");

	return 0;
}