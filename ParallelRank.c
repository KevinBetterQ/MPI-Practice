#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
#include <stdlib.h>

int main (int argc ,char** argv)
{


	int rank,size,i,j;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//int *sbuf = (int *) malloc(sizeof(int)  * size);
	srand(rank*1000);
	int send = rand();
	int *sbuf = (int *) malloc(sizeof(int) * size);
        int *rbuf = (int *) malloc(sizeof(int) * size);
	int *sort = (int *) malloc(sizeof(int) * size);
        printf("Process %d  rand is %d\n",rank,send);
        MPI_Gather(&send, 1, MPI_INT, rbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank==0)
      {

	for(i=0;i<size;i++){
	  sort[i] = rbuf[i];
	  printf("%d ",rbuf[i]);
	}
        putchar('\n');

	int t;
	for(i=0;i<size;i++){
	    for(j=i+1;j<size;j++){
		if(sort[i]<sort[j]){
		  t = sort[i];
		  sort[i] = sort[j];
		  sort[j] = t;
		}
	    }
	}

	for(i=0;i<size;i++){
	  for(j=0;j<size;j++){
		if(sort[i]==rbuf[j]){
		  sbuf[i] = j;
		}
	  }
	}
	
      }

	

	MPI_Scatter(sbuf, size, MPI_INT, rbuf, size, MPI_INT, 0,  MPI_COMM_WORLD);
	if(rank==0){
	  for(i=0;i<size;i++){
            printf("%d ",rbuf[i]);
          }
	  putchar('\n');

	}
 
	MPI_Finalize();
	return 0;
}