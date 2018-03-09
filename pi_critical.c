#include <omp.h>
#include <stdio.h>


static long num_steps = 1000000;
double step;
int main()
{
	double x,pi;
	static double sum;
	omp_set_num_threads(4);

	step = 1.0/(double)num_steps;
	double time = omp_get_wtime();
#pragma omp parallel 
	{
		int i;
		int tid = omp_get_thread_num();
		printf("Houston calling thread no. %d\n",tid);
		int nsteps = num_steps/4;
		i = nsteps*tid;
		int j = i + num_steps/4;
		for(i;i<j;i++) {
			x = (i+0.5)*step;
#pragma omp critical
			sum = sum + 4.0/(1.0+x*x);
		}
	}
	pi = step * sum;
	double time_end = omp_get_wtime();
	printf("The time taken is: %lf\n",time_end - time);
	printf("%lf\n",pi);
return 0;
}
