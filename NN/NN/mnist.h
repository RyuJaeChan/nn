
#include <stdio.h>		//FILE, fopen(), fclose()
#include <string>

class MNIST
{
private:
	size_t sizeOfTrainingImage;	//Todo : 32 bit integer
	size_t sizeOfTrainingLabel;
	size_t sizeOfTestImage;
	size_t sizeOfTestLabel;



	void ReadFile(std::string fileName)
	{
		FILE* fp = fopen(fileName.c_str(), "r");



	}

public:
	void ReadTrainingSet()
	{

	}



};