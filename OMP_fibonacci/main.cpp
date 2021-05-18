// Reference : Example A.15.4c in the OpenMP 3.1
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 16

int fib(int n)
{
	int x,y;
	if(n<2)
		return n;
	else
	{	
		omp_set_num_threads(NUM_THREADS); // Use 16 threads for all consecutive parallel regions
		// Tell the compiler that the variable x is shared across all the threads
		#pragma omp task shared(x)
			x = fib(n-1);
		// Tell the compiler that the variable x is shared across all the threads
		#pragma omp task shared(y)
			y = fib(n-2);
		// Use the fork join paradigm: here waiting for the child tasks to get finished
		#pragma omp taskwait
			return x+y;
	}
	
}

int main()
{
	int n,fibonacci;
	double starttime;
	printf("Please insert n, to calculate fib(n): \n");
	scanf("%d",&n);
	starttime = omp_get_wtime();
	fibonacci = fib(n);

	printf("fib(%d)=%d \n",n,fibonacci);
	printf("calculation took %lf sec\n",omp_get_wtime()-starttime);
	return 0;
}