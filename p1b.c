# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

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

int main(int argc, char *argv[]){
    MPI_Init ( &argc, &argv );
    int rank,size,master=0;
    MPI_Comm_rank ( MPI_COMM_WORLD, &rank);
    MPI_Comm_size ( MPI_COMM_WORLD, &size);
    int n=1000000000/size;
    double wtime=MPI_Wtime();
    double *pi=(double *)malloc(sizeof(double)),*combined_pi=(double *)malloc(sizeof(double));
    *pi=(double)func(n)*4/(double)n;
    MPI_Reduce((void *)pi,(void *)combined_pi,1,MPI_DOUBLE,MPI_SUM,master,MPI_COMM_WORLD);
    *combined_pi=(*combined_pi)/size;
    wtime=MPI_Wtime()-wtime;
    if(rank==master){
        printf("Final Estimate by process %d = %f in time %f for %d iterations overall\n",rank,*combined_pi,wtime,n*size);
    }
    else{
        printf("Estimate by process %d = %f in time %f for %d iterations\n",rank,*pi,wtime,n);
    }
    MPI_Finalize();
}