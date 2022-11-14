#include <stdio.h>
#include <mpi.h>

int main(int argc, char  *argv[])
{
    int rank;
    int size;
    int n = 0;
    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0) {
        MPI_Send(&n, 1, MPI_INT, 1, 777, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_INT, size - 1, 777, MPI_COMM_WORLD, &stat);
        printf("rank = %d\tn = %d\n", rank, n);
    } else {
        MPI_Recv(&n, 1, MPI_INT, rank - 1, 777, MPI_COMM_WORLD, &stat);
        n++;
        printf("rank = %d\tn = %d\n", rank, n);
        MPI_Send(&n, 1, MPI_INT, (rank + 1) % size, 777, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
