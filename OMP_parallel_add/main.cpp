// REFERENCE : http://selkie.macalester.edu/csinparallel/modules/ConceptDataDecomposition/build/html/Decomposition/OpenMP_VecAdd.html

#include <stdlib.h>   //malloc and free
#include <stdio.h>    //printf
#include <omp.h>      //OpenMP
#include <ctime>
// Very small values for this simple illustrative example
#define ARRAY_SIZE 1000     //Size of arrays whose elements will be added together.
#define NUM_THREADS 4    //Number of threads to use for vector addition.

/*
 * navigate to directory and type make clean
 * Then type make
 * Then type ./output to see the result
 */
int main (int argc, char *argv[]) 
{
	// elements of arrays a and b will be added
	// and placed in array c
	int * a;
	int * b; 
	int * c; //stores parallel addition
	int * d; //stores serial addition
        
    int n = ARRAY_SIZE;                 // number of array elements
	int n_per_thread;                   // elements per thread
	int total_threads = NUM_THREADS;    // number of threads to use  
	int i;       // loop index
        
    // allocate spce for the arrays
    a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);
	d = (int *) malloc(sizeof(int)*n);

    for(i=0; i<n; i++) {
        a[i] = rand()%100; // random numbers between 0 and 99
    }
    for(i=0; i<n; i++) {
        b[i] = rand()%100;
    }   
    printf("Adding in serial ");
    clock_t begin = clock();
    for (i=0; i<n; i++)
    {
    	d[i] = a[i]+b[i];
    }
    clock_t end = clock();
    double elapsed_sec = double(end-begin)/ CLOCKS_PER_SEC;
    printf("Time elapsed %f\n",elapsed_sec);
	// Setting the number of threads .
	omp_set_num_threads(total_threads);
	
	// determine how many elements each process will work on
	n_per_thread = n/total_threads;
	
	printf("Adding in parallel ");
	clock_t beginp = clock();
	#pragma omp parallel for shared(a, b, c) private(i) schedule(static, n_per_thread)
    for(i=0; i<n; i++) 
    {
		c[i] = a[i]+b[i];
		// This following line can show which thread handles which subset of the data
		// printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
    }
    clock_t endp = clock();
    double elapsed_secp = double(endp-beginp)/ CLOCKS_PER_SEC;
    printf("Time elapsed %f\n",elapsed_secp);

    // NOTE : Parallel code is more that 100 times slower than serial ! 
    // This maybe because of additional parallelization overhead as compared to just adding serially
    // we will start to observe difference when we do : #define ARRAY_SIZE 1000000 | at line 8


	/*
	// Following code can check for correctness
	printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");
        for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
        }
	*/

        // clean up memory
    free(a);  free(b); free(c);
	
	return 0;
}