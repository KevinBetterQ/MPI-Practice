#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char **argv){ 
	const int limit = 10; 
	int rank, count = 0; 
	MPI_Status status; 
	MPI_Init(&argc, &argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	while (count < limit){ 
		if (rank == 0){ 
			count++; 
			MPI_Send(&count, 1, MPI_INT, 1, 10, MPI_COMM_WORLD); 
			printf("0 sent %d to 1\n", count);
			MPI_Recv(&count, 1, MPI_INT, 1, 20, MPI_COMM_WORLD, &status); 
			printf("0 received %d from 1\n", count);
		} else { 
			MPI_Recv(&count, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status); 
			printf("1 received %d from 0\n", count); 
			count++;
			MPI_Send(&count, 1, MPI_INT, 0, 20, MPI_COMM_WORLD); 
			printf("1 sent %d to 0\n", count); 
		} 
	} 
	MPI_Finalize(); 
}
