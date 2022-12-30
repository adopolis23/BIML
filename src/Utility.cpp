#include "Utility.h"
#include "Kernel.h"
#include <iostream>


namespace biml {

	void biml::Binarize(Image& img, int threshold)
	{
		//for each pixel in the image
		for (int i = 0; i < img.getHeight(); i++) {
			for (int j = 0; j < img.getWidth(); j++) {
				
				int value = img.getPixel(i, j);

				//if value is greater than threshold -> set pixel white; else -> set black 
				if (value >= threshold) {
					img.setPixel(i, j, img.getMaxValue());
				}
				else {
					img.setPixel(i, j, 0);
				}

			}
		}
	}




	void biml::UniformSmooth(Image& img, int ws) 
	{
		
		Kernel k(KernelType::UNIFORM_SMOOTH, 3); 

		std::cin.get();

	}

};
