

#include "mnist.h"


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

public:
	//for test
	Network(){}


	Network(size_t _inputSize, size_t _outputSize, size_t _layerSize, size_t _neuronSize)
		: inputSize(_inputSize), outputSize(_outputSize), layerSize(_layerSize), neuronSize(_neuronSize)
	{
		layers = std::vector<std::vector<Neuron>>(layerSize, std::vector<Neuron>(neuronSize, Neuron(neuronSize)));
		
		for (auto it : layers.front())
		{
			it.ResizeW(inputSize);
		}

		layers.back().resize(outputSize);
	}

	void Forward()
	{
		MNIST::LoadData(
			"dataset/train-images.idx3-ubyte",
			"dataset/train-labels.idx1-ubyte",
			[=](std::vector<double> imageArr, std::vector<double> labelArr)
			{
				std::cout << imageArr.size() << std::endl;

			}
		);
	}



};