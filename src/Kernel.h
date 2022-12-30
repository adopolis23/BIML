#pragma once


namespace biml 
{

	enum KernelType {
		UNIFORM_SMOOTH, SOBEL
	};

	class Kernel 
	{
		
	public:

		Kernel(KernelType type, unsigned int size);
		~Kernel();


	private:

		KernelType m_Type;
		unsigned int m_WindowSize;
		float* m_Data;

	};






};