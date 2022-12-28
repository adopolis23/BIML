#include "Utility.h"


namespace biml {

	void biml::Binarize(Image& img, int threshold)
	{
		for (int i = 0; i < img.getHeight(); i++) {
			for (int j = 0; j < img.getWidth(); j++) {
				
				int value = img.getPixel(i, j);

				if (value >= threshold) {
					img.setPixel(i, j, img.getMaxValue());
				}
				else {
					img.setPixel(i, j, 0);
				}

			}
		}
	}

};
