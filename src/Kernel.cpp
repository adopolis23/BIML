#include "Kernel.h"

#include <stdlib.h>

namespace biml {


	Kernel::Kernel(KernelType type, unsigned int size)
	{
		this->m_Type = type;
		this->m_WindowSize = size;

		this->m_Data = (float*)malloc(size * 2 * sizeof(float));
	}

	Kernel::~Kernel()
	{
		free(this->m_Data);
	}

}