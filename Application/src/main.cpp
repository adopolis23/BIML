#include <stdio.h>

#include "BIML.h"

int main() {

	biml::Image img("Images/tree_1.ppm");


	img.Save("Images/tree_saved.pgm");

	return 0;
}