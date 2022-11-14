#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank;
    int size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n1 = 1;
    int n2 = 0;

    printf("start\nrank = %d\tn = %d", rank, n2);
    MPI_Sendrecv(&n1, 1, MPI_INT, (rank + 2) % size, 777, &n2, 1, MPI_INT, (rank - 2 + size) % size, 777, 
        MPI_COMM_WORLD, &stat);
    printf("stop\nrank = %d\tn = %d", rank, n2);
    
    MPI_Finalize();
    return 0;
}