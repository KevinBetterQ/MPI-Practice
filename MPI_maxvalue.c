#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
int main(int argc, char **argv){
  int arr[1000],size,rank, local_max, max;
  int i, each, *begin, *maximums;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  if (rank == 0){
     for (i = 0; i < 1000; i++)
        arr[i] = i + 1;
     each = 1000 / size;
     for (i = 1; i < size; i++){
        begin = arr + each * i;
        MPI_Send(begin, each, MPI_INT, i, 99, comm);
     }
     maximums = (int*)malloc(sizeof(int) * size);
  }
  else{
     MPI_Recv(arr, 1000 / size, MPI_INT, 0, 99, comm, &status);
  }
  local_max = arr[0];
  for (i = 0; i < 1000/size; i++)
     if (local_max < arr[i])
         local_max = arr[i];
  printf("max of process %d is %d.\n", rank, local_max);
  if (rank != 0){
     MPI_Send(&local_max, 1, MPI_INT, 0, 100, comm);
  }
  else{
     maximums[0] = local_max;
     for (i = 1; i < size; i++)
        MPI_Recv(&maximums[i], 1, MPI_INT, i, 100, comm, &status);
     max = maximums[0];
     for (i = 0; i < size; i++)
         if (max < maximums[i])
            max = maximums[i];
     printf("Max is %d.\n", max);
  }
  MPI_Finalize();
  return 0;
}
