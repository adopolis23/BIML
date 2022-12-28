#include "Image.h"
#include <iostream>
#include <fstream>
#include <string>

namespace biml {


	Image::Image()
	{
		//clear the channels
		this->m_Data.redChannel.clear();
		this->m_Data.greenChannel.clear();
		this->m_Data.blueChannel.clear();

		//for now default values are PGM images and Grayscale
		this->m_Type = imageType::PGM;
		this->m_Cspace = colorspace::GRAYSCALE;
	}




	Image::~Image()
	{
	}





	int Image::Load(const char* filepath)
	{
		std::ifstream fileData;
		std::string str;
		unsigned int totalBytes;



		if (strstr(filepath, ".pgm") != NULL) {
			LOG("Loading PGM File " << filepath);
			this->m_Type = imageType::PGM;
			this->m_Cspace = colorspace::GRAYSCALE;

		}
		else {
			LOG("Invalid File Format Detected");
			return INVALID_FILE_FORMAT;
		}




		fileData.open(filepath, std::ios_base::in | std::ios_base::binary);

		if (!fileData) {
			std::cout << "Error Reading File" << std::endl;
			return ERROR_READING_FILE;
		}

		//get first line if file type is .pgm and there is no P5 in first line then invalid pgm file
		std::getline(fileData, str);


		if (this->m_Type == imageType::PGM && strcmp(str.c_str(), "P5") != 0) {
			LOG("Invalid PGM File");
			return INVALID_PGM_FILE;
		}


		fileData >> this->m_Data.width;
		fileData >> this->m_Data.height;
		setSize(this->m_Data.height, this->m_Data.width);

		std::getline(fileData, str);
		std::getline(fileData, str);

		this->m_Data.max_value = stoi(str);



		//read in actual image data
		if (this->m_Type == imageType::PGM) {

			//for a pgm image each pixel is one byte so total bytes is just cols * rows
			totalBytes = this->m_Data.width * this->m_Data.height;

			char* buffer = (char*)malloc(totalBytes);
			if (buffer == nullptr) {
				LOG("Failed to initialize image data buffer");
				return GENERAL_ERROR;
			}

			//read the total bytes into the buffer that has been created
			fileData.read(buffer, totalBytes);



			unsigned char c;

			//for each character in the buffer add to the red channel vector
			for (int i = 0; i < totalBytes; i++) {
				c = (unsigned char)buffer[i];
				this->m_Data.redChannel[i] = c;

				//LOG((unsigned char)c);
			}



			//deallocate the heap memory for buffer
			free(buffer);


		}

		fileData.close();

		return NO_ERROR;
	}





	int Image::Save(const char* filepath)
	{
		std::fstream outfile;
		unsigned int totalBytes;
		unsigned char c;

		outfile.open(filepath, std::ios_base::out | std::ios_base::binary);

		if (strstr(filepath, ".pgm") != NULL) {
			LOG("Saving PGM File " << filepath);
		}
		else {
			LOG("Invalid File Format Detected");
			return INVALID_FILE_FORMAT;
		}


		if (this->m_Type == imageType::PGM) {

			outfile << "P5\n";
			outfile << this->m_Data.width << " " << this->m_Data.height << "\n";
			outfile << "255\n";

			totalBytes = this->m_Data.width * this->m_Data.height;

			for (int i = 0; i < totalBytes; i++) {

				c = (this->m_Data.redChannel[i] > this->m_Data.max_value ? this->m_Data.max_value : this->m_Data.redChannel[i]);

				outfile << (unsigned char)c;

			}
		}

		outfile.close();

		return NO_ERROR;
	}



	void Image::setSize(int rows, int cols)
	{
		//this is the size of one channel
		int channelSize = rows * cols;

		this->m_Data.redChannel.resize(channelSize);
		this->m_Data.greenChannel.resize(channelSize);
		this->m_Data.blueChannel.resize(channelSize);
	}

	unsigned int Image::getPixel(int row, int col)
	{
		int index = row * this->m_Data.width + col;
		return this->m_Data.redChannel[index];
	}

	void Image::setPixel(int row, int col, const unsigned int value)
	{

		int index = row * this->m_Data.width + col;
		this->m_Data.redChannel[index] = value;

	}

	imageType Image::getImageType()
	{
		return this->m_Type;
	}

	colorspace Image::getColorspace()
	{
		return this->m_Cspace;
	}

	int Image::getWidth() const
	{
		return this->m_Data.width;
	}

	int Image::getHeight() const
	{
		return this->m_Data.height;
	}

	int Image::getMaxValue() const
	{
		return this->m_Data.max_value;
	}


}