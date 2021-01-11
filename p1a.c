#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define SEED 3579124

int func(int n){
	int count=0;
	for (int i=0; i<n; i++) {
		double x = (double)rand()/RAND_MAX;
		double y = (double)rand()/RAND_MAX;
		double z = x*x+y*y;
		if (z-1.0<0.000001)
				count++;
	}
	return count;
}

int main(int argc, char *argv[]) {
	long n = atoi(argv[1]), count = 0;
	double pi,ti=omp_get_wtime();
	int fact=10000000;
	n/=fact;
	srand(SEED);
	printf("%d",n);
	omp_set_num_threads(atoi(argv[2]));
	#pragma omp parallel for reduction(+:count) schedule(static)
	for (int i=0; i<n; i++) {
		count+=func(fact);
	}
	pi=(double)count/(n*fact)*4;
	printf("Time: %f\n",omp_get_wtime()-ti);
	printf("# of trials= %d , estimate of pi is %g \n",n,pi);

	printf("n=%d\n",n);
	return 0;
}
