#include "Image.h"


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

	Image::Image(const char* filepath)
		: Image()
	{
		Load(filepath);
	}

	Image::Image(Image& cpy)
	{
		this->copyImage(cpy);
	}





	void Image::copyImage(Image& cpy) {
		//TODO: probably a better way to do this

		//clear the channels
		this->m_Data.redChannel.clear();
		this->m_Data.greenChannel.clear();
		this->m_Data.blueChannel.clear();


		this->setSize(cpy.getHeight(), cpy.getWidth());



		for (int i = 0; i < this->m_Data.height; i++) {
			for (int j = 0; j < this->m_Data.width; j++) {

				this->setPixel(i, j, cpy.getPixel(i, j));

			}
		}

		this->m_Cspace = cpy.getColorspace();
		this->m_Type = cpy.getImageType();
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
		else if (strstr(filepath, ".ppm") != NULL) {
			LOG("Loading PPM File " << filepath);
			this->m_Type = imageType::PPM;
			this->m_Cspace = colorspace::RGB;
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
		else if (this->m_Type == imageType::PPM && strcmp(str.c_str(), "P6") != 0) {
			
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
		else if (this->m_Type == imageType::PPM) {
			
			//multiply area by 3 for each channel r g and b
			totalBytes = this->m_Data.width * this->m_Data.height * 3;
			
			//init buffer with size of total bytes and check initialization
			char* buffer = (char*)malloc(totalBytes);
			if (buffer == nullptr) {
				LOG("Failed to initialize image data buffer");
				return GENERAL_ERROR;
			}

			//read the file data into the buffer
			fileData.read(buffer, totalBytes);

			unsigned char r, g, b;

			//for each character in the buffer add to the red channel vector
			for (int i = 0; i < totalBytes/3; i++) {
				r = (unsigned char)buffer[i*3];
				g = (unsigned char)buffer[(i*3)+1];
				b = (unsigned char)buffer[(i*3)+2];


				this->m_Data.redChannel[i] = r;
				this->m_Data.greenChannel[i] = g;
				this->m_Data.blueChannel[i] = b;

				//LOG((unsigned char)c);
			}

			free(buffer);

		}

		fileData.close();

		return NO_ERROR;
	}





	int Image::Save(const char* filepath)
	{
		std::fstream outfile;
		unsigned int totalBytes;
		unsigned char c, r, g, b;

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
		else if (this->m_Type == imageType::PGM) {
			
			outfile << "P6\n";
			outfile << this->m_Data.width << " " << this->m_Data.height << "\n";
			outfile << "255\n";

			totalBytes = this->m_Data.width * this->m_Data.height * 3;

			for (int i = 0; i < totalBytes/3; i++) {

				r = (this->m_Data.redChannel[i] > this->m_Data.max_value ? this->m_Data.max_value : this->m_Data.redChannel[i]);
				g = (this->m_Data.greenChannel[i] > this->m_Data.max_value ? this->m_Data.max_value : this->m_Data.greenChannel[i]);
				b = (this->m_Data.blueChannel[i] > this->m_Data.max_value ? this->m_Data.max_value : this->m_Data.blueChannel[i]);

				outfile << (unsigned char)r;
				outfile << (unsigned char)g;
				outfile << (unsigned char)b;

			}

		}

		outfile.close();

		return NO_ERROR;
	}





	void Image::setSize(int rows, int cols)
	{
		//this is the size of one channel
		int length = rows * cols;
		this->m_Data.height = rows;
		this->m_Data.width = cols;

		this->m_Data.redChannel.clear();
		this->m_Data.greenChannel.clear();
		this->m_Data.blueChannel.clear();

		this->m_Data.redChannel.resize(length);
		this->m_Data.greenChannel.resize(length);
		this->m_Data.blueChannel.resize(length);
	}

	







	int Image::Convolve(Kernel kernel)
	{

		Image* tgt = new Image(*this);

		//if window size is 5 then windowSize/2 = 2
		int newVal = 0;

		//for each pixel in image [without getting too close to edge]
		for (int i = kernel.getWindowSize() / 2; i < this->getHeight() - (kernel.getWindowSize() / 2) - 1; i++) {
			for (int j = kernel.getWindowSize() / 2; j < this->getWidth() - (kernel.getWindowSize() / 2) - 1; j++) {

				newVal = 0;

				for (int in = 0; in < kernel.getWindowSize(); in++) {
					for (int jn = 0; jn < kernel.getWindowSize(); jn++) {



						float kernelval = kernel.getValue(in, jn);
						int imageval = this->getPixel((i - (kernel.getWindowSize() / 2) + in), (j - (kernel.getWindowSize() / 2) + jn));


						newVal = newVal + (kernelval * imageval);

						


					}
				}

				tgt->setPixel(i, j, newVal);
				//std::cout << newVal << std::endl;

			}

		}


		this->copyImage(*tgt);
		delete tgt;

		return NO_ERROR;

	}







	unsigned int Image::getPixel(int row, int col)
	{
		int index = row * this->m_Data.width + col;
		return this->m_Data.redChannel[index];
	}

	void Image::setPixel(int row, int col, const unsigned int value)
	{

		int index = row * this->m_Data.width + col;

		int newVal = value;

		if (value > 255)
			newVal = 255;
		else if (value < 0)
			newVal = 0;

		

		this->m_Data.redChannel[index] = newVal;
		this->m_Data.greenChannel[index] = newVal;
		this->m_Data.blueChannel[index] = newVal;

		//this->m_Data.redChannel[index] = (value > 255 ? 255 : value);

	}



	void Image::checkChannel(int channel) {
		switch (channel) {

		case 0:
			for (int i = 0; i < 10; i++) {
				LOG(m_Data.redChannel[i]);
			}
			break;
		case 1:
			for (int i = 0; i < 10; i++) {
				LOG(m_Data.greenChannel[i]);
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++) {
				LOG(m_Data.blueChannel[i]);
			}
		default:
			LOG("Default");
		};
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