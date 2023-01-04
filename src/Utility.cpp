#include "Utility.h"



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
		std::cout << "Computing Uniform Smooth; Window Size: " << ws << std::endl;
		
		Kernel k(KernelType::UNIFORM_SMOOTH, ws); 

		auto start_time = std::chrono::high_resolution_clock::now();

		img.Convolve(k);

		auto stop_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);

		std::cout << "Exec Time for Uniform Smooth: " << duration.count()/1000 << " nanoseconds." << "\n";


	}


	void biml::Sobel(Image& img, int ws, int dir)
	{
		std::cout << "Computing Sobel; Window Size: " << ws << " Direction: " << (dir == 0 ? "x" : "y") << std::endl;

		Kernel k((dir == 0 ? KernelType::SOBEL_X : KernelType::SOBEL_Y), ws);

		auto start_time = std::chrono::high_resolution_clock::now();

		img.Convolve(k);

		auto stop_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);

		std::cout << "Exec Time for Sobel: " << duration.count() / 1000 << " nanoseconds." << "\n";

	}
	
};
