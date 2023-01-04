#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Kernel.h"


#define LOG(x) std::cout << x << std::endl



//error codes
#define NO_ERROR			0x0000
#define INVALID_PGM_FILE	0x0001
#define INVALID_FILE_FORMAT 0x0002
#define ERROR_READING_FILE	0x0003

#define GENERAL_ERROR		0xFFFF


namespace biml {

	struct ImageData {
		std::vector<unsigned char> redChannel, greenChannel, blueChannel;
		unsigned int width, height;
		unsigned int max_value;
	};

	enum channel { RED, GREEN, BLUE };

	enum imageType { PGM };

	enum colorspace { GRAYSCALE, RGB };



	//main image class
	class Image {

		//For grayscale images the redchannel will be the grayscale channel; 

	public:

		//constructor / destructor
		Image();
		Image(Image& cpy);

		~Image();


		//load and save methods
		int Load(const char* filepath);
		int Save(const char* filepath);

		void setSize(int rows, int cols);

		void copyImage(Image& img);


		//getters and setters
		unsigned int getPixel(int row, int col);
		void setPixel(int row, int col, const unsigned int value);

		imageType getImageType();
		colorspace getColorspace();

		int getWidth() const;
		int getHeight() const;
		int getMaxValue() const;


		int Convolve(Kernel kernel);



	private:
		ImageData m_Data;
		imageType m_Type;
		colorspace m_Cspace;


	};

}