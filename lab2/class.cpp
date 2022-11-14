#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int n = 20;
    MPI_Status stat;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *a = new int[n];

    if(rank == 0) {
       for (int i{0}; i < n; i++) {
        a[i] = i;
       }
        for (int i{0}; i < size; i++)
        MPI_Send(&a[0], n, MPI_INT, 1, 777, MPI_COMM_WORLD);
    } else {
        for (int i{0}; i < n; i++) {
            a[i] = 0;
        }
    }
        MPI_Recv(&a[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);

    printf("rank = %d\n:", rank);
    for (int i = 0; i < n; i++) {
        printf("%d  ", a[i]);
    }
    delete []a;

    MPI_Finalize();

    return 0;
}