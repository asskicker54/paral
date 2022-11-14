#include <stdio.h>
#include <mpi.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    int rank, size;
    int *a = (int*)malloc((size) * sizeof(int));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = rank + 1;
    for(int i = 0; i < k; i++) {
        a[i] = i;
        sum += a[i];
    }

    printf("rank = %d\tsum = %d\n", rank, sum);
    MPI_Finalize();
    return 0;
}
