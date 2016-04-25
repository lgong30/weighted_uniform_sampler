#include <stdio.h>
#include "random_variable.h"


int main()
{
	int i, min = 0, max = 100,n = 10;
	printf("test random integer generator ...\n");
	printf("	U([%d,%d],1,%d):\n",min,max,n);
	int *rand_ints = UniformIntRandomVariable(min,max,n);
	for (i = 0;i < n;++ i)
		printf("	%4d ",rand_ints[i]);
	printf("\n");
	printf("test random real generator ...\n");
	double dmin = 0, dmax = 1;
	double *rand_reals = UniformDoubleRandomVariable(dmin,dmax,n);
	for (i = 0;i < n;++ i)
		printf("	%8.4f ",rand_reals[i]);
	printf("\n");	

	free(rand_ints);
	free(rand_reals);

}