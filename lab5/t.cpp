#include <mpi.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    int rank;
    int size;
    int k = 5;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        int n = 3 * (size-1);
        int** a = new int* [n];
        a[0] = new int[n * k];
        for(int i = 1; i < n; i++)
            a[i] = a[i - 1] + k;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < k; j++)
                a[i][j] = 0;

        for(int i = 1; i < size; i++)
            MPI_Recv(a[(i - 1) * 3], 3 * k, MPI_INT, i, 111, MPI_COMM_WORLD, &stat);
            
        printf("rank = %d, a: \n", rank);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < k; j++)
                printf(" %d ", a[i][j]);
            printf("\n ");
        }
    } else {
        int n = 3;

        int** a = new int* [n];
        a[0] = new int[n * k];
        for(int i = 1; i < n; i++)
            a[i] = a[i - 1] + k;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < k; j++)
                a[i][j] = rank;

        MPI_Send(*a, 3 * k, MPI_INT, 0, 111, MPI_COMM_WORLD);

    }
    MPI_Finalize();
    return 0;
}
