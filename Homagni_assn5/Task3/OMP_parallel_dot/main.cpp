// reference : https://computing.llnl.gov/tutorials/openMP/samples/C/omp_dotprod_openmp.c
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
/* Define length of dot product vectors */
#define VECLEN 100
#define NUMTHREADS 16 //defined the number of threads to be 16

int main ()
{
	int i,len=VECLEN;
	//Adding the option for number of threads 
	int threads=NUMTHREADS;
	//Adding a variable to keep track of thread ids 
	int tid;
	double *a, *b;
	double sum, psum;

	printf("Starting omp_dotprod_serial\n");
	clock_t begin = clock();
	/* Assign storage for dot product vectors */
	a = (double*) malloc (len*sizeof(double));
	b = (double*) malloc (len*sizeof(double));
	/* Initialize dot product vectors */
	for (i=0; i<len; i++) 
	{
		a[i]=10.0;
		b[i]=a[i];
	}
	/* Perform the dot product */
	sum = 0.0;
	for (i=0; i<len; i++)
	{
		sum += (a[i] * b[i]);
	}
	printf ("Done. Serial version: sum = %f \n", sum);
	clock_t end = clock();
    double elapsed_sec = double(end-begin)/ CLOCKS_PER_SEC;
    printf("Time elapsed %f\n",elapsed_sec);

    free (a);
	free (b);

    printf("Starting omp_dotprod_parallel\n");
    a = (double*) malloc (len*sizeof(double));
	b = (double*) malloc (len*sizeof(double));
	/* Initialize dot product vectors again for a fair time comparison*/
	for (i=0; i<100; i++) 
	{
		a[i]=10.0;
		b[i]=a[i];
	}

	// Adding code to perform parallelized dot product
	//Initialize sum to be 0.0 again
	clock_t beginp = clock();
	double parsum = 0.0; // Not initializing with 0.0 may return a garbage value sometimes 
	int j;
	//need to adjust length according to the number of threads being used
	len = 10;
	//array index variable has to declared private
	#pragma omp parallel private(j) num_threads(threads) 
	{
		#pragma omp for reduction(+:parsum)
		  for (j=0; j<len*threads; j++) 
		    {
		      parsum += (a[j] * b[j]);
		    }
	}

	printf ("Done. OpenMP version: sum  =  %f \n", parsum);

	clock_t endp = clock();
    double elapsed_secp = double(endp-beginp)/ CLOCKS_PER_SEC;
    printf("Time elapsed %f\n",elapsed_secp);
	return 0;
}
