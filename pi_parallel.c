#include <omp.h>
#include <stdio.h>


static long num_steps = 1000000;
double step;
int main()
{
	int i;
	double x,pi;
	double sum[4] = {0,0,0,0};
	double time = omp_get_wtime();
	omp_set_num_threads(4);

	step = 1.0/(double)num_steps;
#pragma omp parallel 
	{
		int tid = omp_get_thread_num();
		printf("Houston calling thread no. %d\n",tid);
		int nsteps = num_steps/4;
		i = nsteps*tid;
		for(i;i<num_steps;i++) {
			x = (i+0.5)*step;
			sum[tid] = sum[tid] + 4.0/(1.0+x*x);
		}
	}
	pi = step * (sum[0]+sum[1]+sum[2]+sum[3]);
	printf("%lf\n",pi);
return 0;
}
