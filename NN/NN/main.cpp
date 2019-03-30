#include "nn.h"

int main()
{
	Network nw(28*28, 8, 5, 10);
	nw.Training();


	return 0;
}