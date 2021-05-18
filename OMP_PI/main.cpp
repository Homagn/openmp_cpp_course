/*=======================================================================*/
/* Approximates pi with the n-point quadrature rule 4 / (1+x**2)         */
/* applied to the integral of x from 0 to 1.                             */
/*=======================================================================*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

const double M_pi = 3.14159265358979323846; /* reference value */
#define NUM_THREADS 1

double calc_pi (unsigned n) {
  double h   = 1.0 / n;
  double sum = 0.0;
  double x;
  int i;
  
  for (i=0; i<n; i++) {
    x = (i + 0.5) * h;
    sum += 4.0 / ( 1.0 + x*x );
  }

  return h * sum;
}

double parallel_pi(unsigned n) 
{
    double h = 1.0 / n;
    double integral = 0.0;
    double x;
    int i;
    omp_set_num_threads(NUM_THREADS); // Use 2 threads for all consecutive parallel regions
    #pragma omp parallel private(i, x)
      {
        #pragma omp for reduction(+:integral) schedule(dynamic)
        for (i = 0; i < n; i++) {
            x = (i + 0.5) * h;
            integral += 4.0 / (1.0 + x * x);
        }
      }

    return h * integral;
}


int main(int argc, char* argv[]) {
  int n;

  if ( argc != 2 ) {
    fprintf(stderr, "usage: pi <num_iterations>\n");
    return 1;
  }

  n = atoi(argv[1]);
  //Using the provided serial process
  double starttime;
  starttime = omp_get_wtime();

  if ( n > 0 ) {
    double pi = calc_pi(n);
    double err = pi - M_pi;
    printf("Calculated pi is %19.15f\n", pi);
    printf("Referenced pi is %19.15f\n", M_pi);
    printf("  Error in pi is %19.15f (%f%%)\n", err, err*100/M_pi);
  }
  printf("serial calculation took %lf sec\n",omp_get_wtime()-starttime);

  // Our parallel process
  starttime = omp_get_wtime();
  if (n > 0) {
      double pi = parallel_pi(n);
      double err = pi - M_pi;
      printf("Calculated pi is %19.15f\n", pi);
      printf("Referenced pi is %19.15f\n", M_pi);
      printf("  Error in pi is %19.15f (%f%%)\n", err, err * 100 / M_pi);
  }
  printf("parallel calculation took %lf sec\n",omp_get_wtime()-starttime);

  return 0;
}


