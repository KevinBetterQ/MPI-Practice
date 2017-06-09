#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char** argv){ 
	int rank, size, token, source, dest; 
	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	source = rank == 0 ? size -1 : rank - 1; 
	dest = (rank + 1) % size; 
	token = 100; 
	if (rank == 0){ 
		MPI_Ssend(&token, 1, MPI_INT, dest, 1, MPI_COMM_WORLD); 
		printf("Process %d sends token to %d.\n", rank, dest);
		MPI_Recv(&token, 1, MPI_INT, source, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
		printf("Process %d receives token from %d.\n", rank, source); 
	} else { 
		MPI_Recv(&token, 1, MPI_INT, source, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
		printf("Process %d receives token from %d.\n", rank, source); 
		MPI_Ssend(&token, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
		printf("Process %d sends token to %d.\n", rank, dest); 
	} 
	MPI_Finalize(); 
	return 0; 
} 
