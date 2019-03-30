
#include <iostream>

#include <fstream>		//std::ifstream, std::ios
#include <string>
#include <functional>	//std::function
#include <vector>		//std::vector
#include <cassert>		//assert()

class MNIST
{
private:
	static size_t sizeOfTrainingImage;	//Todo : 32 bit integer
	static int sizeOfTrainingLabel;
	static size_t sizeOfTestImage;
	static size_t sizeOfTestLabel;

	static size_t numOfImage;
	static size_t numOfLabel;

	typedef std::function<void(std::vector<double>)> CallbackType;
	typedef std::function<void(std::vector<double>, std::vector<double>)> CallbackType2;

	static int ConvertInt(int val)
	{
		int ret = 0;
		int temp = 0xff000000;
		for (int i = 0; i < 3; i++)
		{
			ret |= val & temp;
			val <<= 8;
			ret >>= 8;
			ret &= 0x00ffffff;
		}

		return ret;
	}

	static std::vector<double> GetVectorFromBytes(void* byte, size_t size)
	{
		std::vector<double> arr;
		while (size > 0)
		{
			arr.push_back(*(int*)byte >> --size & 0x01);
		}
		return arr;
	}

	static void ReadFile(std::string fileName, CallbackType callback)
	{
		std::ifstream is(fileName, std::ios::binary);

		is.read((char*)&sizeOfTestImage, sizeof(int));
		is.read((char*)&sizeOfTrainingLabel, sizeof(int));

		int cnt = 0;
		while (!is.eof())
		{
			unsigned char temp;
			is.read((char*)&temp, sizeof(unsigned char));
			callback(GetVectorFromBytes(&temp, sizeof(unsigned char)* 8));
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

	static void ReadLabelFile(std::string fileName, CallbackType callback)
	{
		std::ifstream is(fileName, std::ios::binary);

		is.read((char*)&numOfLabel, sizeof(int));	//first 4bytes means magic number(MSB first)
		is.read((char*)&numOfLabel, sizeof(int));

		int cnt = 0;
		while (!is.eof())
		{
			unsigned char temp;
			is.read((char*)&temp, sizeof(unsigned char));
			callback(GetVectorFromBytes(&temp, sizeof(unsigned char)* 8));
		}
	}

	static void ReadImage(std::string fileName, CallbackType callback)
	{
		
		std::ifstream is(fileName, std::ios::binary);

		is.read((char*)&numOfImage, sizeof(int));	//first 4bytes means magic number(MSB first)
		is.read((char*)&numOfImage, sizeof(int));
		int width, height;
		is.read((char*)&width, sizeof(int));
		is.read((char*)&height, sizeof(int));

		size_t imageSize = ConvertInt(width) * ConvertInt(height);

		int cnt = 0;
		while (!is.eof())
		{
			unsigned char temp;
			is.read((char*)&temp, imageSize);
			callback(GetVectorFromBytes(&temp, imageSize));
		}
	}


	static void ReadFiles(std::string imageData, std::string labelData, CallbackType2 callback)
	{
		std::ifstream imageIs(imageData, std::ios::binary);
		std::ifstream labelIs(labelData, std::ios::binary);

		imageIs.read((char*)&numOfImage, sizeof(int));	//first 4bytes means magic number(MSB first)
		imageIs.read((char*)&numOfImage, sizeof(int));
		numOfImage = ConvertInt(numOfImage);
		int width, height;
		imageIs.read((char*)&width, sizeof(int));
		imageIs.read((char*)&height, sizeof(int));
		size_t imageSize = ConvertInt(width) * ConvertInt(height);

		labelIs.read((char*)&numOfLabel, sizeof(int));	//first 4bytes means magic number(MSB first)
		labelIs.read((char*)&numOfLabel, sizeof(int));
		numOfLabel = ConvertInt(numOfLabel);

		assert(numOfImage == numOfLabel);

		while (!imageIs.eof())
		{
			std::vector<double> imageArr;
			for (size_t i = 0; i < imageSize; i++)
			{
				unsigned char pixel;
  				imageIs.read((char*)&pixel, sizeof(unsigned char));
				imageArr.push_back(pixel != 0);
			}

			unsigned char temp;
			labelIs.read((char*)&temp, sizeof(unsigned char));
			callback(imageArr, GetVectorFromBytes(&temp, sizeof(unsigned char)* 8));
		}


	}


public:
	static void LoadData(std::string imageData, std::string labelData, CallbackType2 callback)
	{
		ReadFiles(imageData, labelData, callback);
	}

};
size_t MNIST::sizeOfTrainingImage;	//Todo : 32 bit integer
int MNIST::sizeOfTrainingLabel;
size_t MNIST::sizeOfTestImage;
size_t MNIST::sizeOfTestLabel;

size_t MNIST::numOfImage;
size_t MNIST::numOfLabel;