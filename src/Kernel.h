#pragma once

#include <stdlib.h>
#include <iostream>

namespace biml 
{

	enum KernelType {
		UNIFORM_SMOOTH,
		SOBEL_X,
		SOBEL_Y
	};

	class Kernel 
	{
		
	public:

		Kernel(KernelType type, unsigned int size);
		~Kernel();

		unsigned int getWindowSize() const;
		float* getData() const; 
		float getValue(int row, int col) const; 


	private:

		void initKernel();

		void printKernel();

		KernelType m_Type;
		unsigned int m_WindowSize;
		float* m_Data;

	};






};