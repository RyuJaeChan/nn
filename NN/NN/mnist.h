
#include <iostream>

#include <fstream>		//std::ifstream, std::ios
#include <string>
#include <functional>	//std::function
#include <vector>		//std::vector

class MNIST
{
private:
	size_t sizeOfTrainingImage;	//Todo : 32 bit integer
	int sizeOfTrainingLabel;
	size_t sizeOfTestImage;
	size_t sizeOfTestLabel;


public:
	void ReadFile(std::string fileName)
	{
		//FILE* fp = fopen(fileName.c_str(), "r");
		std::ifstream is(fileName, std::ios::binary);

		is.read((char*)&sizeOfTestImage, sizeof(int));
		is.read((char*)&sizeOfTrainingLabel, sizeof(int));
		unsigned char temp;
		std::cout << "sizeOfTrainingLabel : " << (int)sizeOfTrainingLabel << std::endl;
		int cnt = 0;
		while (!is.eof())
		{
			is.read((char*)&temp, sizeof(unsigned char));
			std::cout << "cnt[" << cnt++ << "] temp : " << (int)temp <<std::endl;
		}



		//Label
		//offset 0000		: magic number (MSB first)
		//offset 0004		: number of items
		//offset 0008		: label(0~9)
		//offset 0009		: label(0~9)
		//	...

		//Image Filse
		//offset 0000		: magic number (MSB first)
		//offset 0004		: number of images
		//offset 0008		: number of rows
		//offset 0012		: number of rows
		//offset 0016		: pixel
		//offset 0017		: pixel
		//	...



	}

public:
	void ReadTrainingSet(std::function<void(double)> callback)
	{
		callback(1.0);


	}



};
