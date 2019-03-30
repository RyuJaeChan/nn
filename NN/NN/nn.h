

#include "mnist.h"

#include <random>

class Neuron
{
private:
	//double s;
	double f;
	double delta;
	std::vector<double> w;	//w's size is equal to the number of previous inputs
	double output;

public:
	Neuron(int sizeOfW = 0)
	{
		w.resize(sizeOfW);
	}

	void ResizeW(size_t size)
	{
		w.resize(size);
	}

	void InitW()
	{
		std::random_device rd;
		std::mt19937_64 rand(rd());
		std::uniform_real_distribution<double> range(0, 1);
		for (auto& e : w)
		{
			e = range(rand);
		}
	}


};


/*
*
*/
class Network
{
private:
	size_t inputSize;		// size of first layer
	size_t outputSize;		// size of last layer
	size_t layerSize;		// size of hidden layer
	size_t neuronSize;		// size of each hidden layer

	std::vector<std::vector<Neuron>> layers;
	friend Neuron;

	void InitW()
	{
		for (auto& layer : layers)
		{
			for (auto& neuron : layer)
			{
				neuron.InitW();
			}
		}
	}

	void Forward(std::vector<double> imageArr, std::vector<double> labelArr)
	{
		for (auto& layer : layers)
		{
			for (auto& neuron : layer)
			{
				neuron.InitW();
			}
		}

		for (int i = 0; i < layers.size(); i++)
		{



		}





	}
public:
	//for test
	Network(){}


	Network(size_t _inputSize, size_t _outputSize, size_t _layerSize, size_t _neuronSize)
		: inputSize(_inputSize), outputSize(_outputSize), layerSize(_layerSize), neuronSize(_neuronSize)
	{
		layers = std::vector<std::vector<Neuron>>(layerSize, std::vector<Neuron>(neuronSize, Neuron(neuronSize)));
		
		for (auto& it : layers.front())
		{
			it.ResizeW(inputSize);
		}

		layers.back().resize(outputSize);
	}

	void Training()
	{
		InitW();

		MNIST::LoadData(
			"dataset/train-images.idx3-ubyte",
			"dataset/train-labels.idx1-ubyte",
			[=](std::vector<double> imageArr, std::vector<double> labelArr)
		{
			Forward(imageArr, labelArr);








			//==print image
			std::cout << imageArr.size() << std::endl;
			for (int i = 0; i < labelArr.size(); i++)
			{
				std::cout << labelArr[i] << " ";
			}
			std::cout << std::endl;

			for (int i = 0; i < 28; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					std::cout << imageArr[i * 28 + j];
				}
				std::cout << std::endl;
			}
			//==


			}
		);
	}
};