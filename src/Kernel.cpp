#include "Kernel.h"



namespace biml {


	Kernel::Kernel(KernelType type, unsigned int size)
	{
		this->m_Type = type;
		this->m_WindowSize = size;

		this->m_Data = (float*)malloc((size_t)(size * size * sizeof(float)));

		initKernel();

		printKernel();
		
	}


	void Kernel::initKernel()
	{
		if (this->m_Type == KernelType::UNIFORM_SMOOTH) {
			//setup kernel for uniform smooth



			for (int i = 0; i < this->m_WindowSize * this->m_WindowSize; i++) {
				this->m_Data[i] = ((float)1.0f/(this->m_WindowSize * this->m_WindowSize));
			}



		}
		else if (this->m_Type == KernelType::SOBEL_X) {
			//setup kernel for sobel

			for (int i = 0; i < this->m_WindowSize * this->m_WindowSize; i++) {
				this->m_Data[i] = (int)(i % this->m_WindowSize) - (int)(this->m_WindowSize/2);
			}

		}

		else if (this->m_Type == KernelType::SOBEL_Y) {
			//setup kernel for sobel

			for (int i = 0; i < this->m_WindowSize * this->m_WindowSize; i++) {
				this->m_Data[i] = (int)(i / this->m_WindowSize) - (int)(this->m_WindowSize / 2);
			}

		}

	}


	Kernel::~Kernel()
	{
		//free(this->m_Data);
	}
	



	float Kernel::getValue(int row, int col) const 
	{
		int index = row * this->getWindowSize() + col;
		return this->m_Data[index];
	}




	unsigned int Kernel::getWindowSize() const {
		return this->m_WindowSize;
	}

	float* Kernel::getData() const
	{
		return this->m_Data;
	}




	void Kernel::printKernel() {
		for (int i = 0; i < this->m_WindowSize; i++) {
			for (int j = 0; j < this->m_WindowSize; j++) {
				std::cout << this->getValue(i, j) << " ";
			}
			std::cout << "\n";
		}
	}






}