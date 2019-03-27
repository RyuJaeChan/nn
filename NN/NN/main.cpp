#include "mnist.h"

int main()
{
	MNIST m;
	m.ReadFile("dataset/train-labels.idx1-ubyte");

	return 0;
}