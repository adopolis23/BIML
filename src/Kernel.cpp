#include "Kernel.h"

#include <stdlib.h>
#include <iostream>

namespace biml {


	Kernel::Kernel(KernelType type, unsigned int size)
	{
		this->m_Type = type;
		this->m_WindowSize = size;

		this->m_Data = (float*)malloc((size_t)(size * 2 * sizeof(float)));

		initKernel();
		
	}


	void Kernel::initKernel()
	{
		if (this->m_Type == KernelType::UNIFORM_SMOOTH) {
			//setup kernel for uniform smooth



			for (int i = 0; i < this->m_WindowSize* this->m_WindowSize; i++) {
				this->m_Data[i] = ((float)1.0f/this->m_WindowSize * this->m_WindowSize);
			}



		}
		else if (this->m_Type == KernelType::SOBEL) {
			//setup kernel for sobel


		}
	}


	Kernel::~Kernel()
	{
		free(this->m_Data);
	}

}