#include <iostream>
#include <mpi.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    int rank;
    int size;
    MPI_Status status;
    int n = 9;
    int s = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        int** a = new int* [n];
        a[0] = new int [n*n];
        for(int i = 1; i < size; i++)
            a[i]=a[i-1]+n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = 10 * (i + 1) + j + 1;
            }
        }

        for (int i = 1; i < size; i++) {
            MPI_Send(&a[i - 1], n, MPI_INT, i, 777, MPI_COMM_WORLD);
        }
    } else {
        int* a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = 0;
        }

        MPI_Recv(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD, &status);

        printf("rank = %d, a: \n", rank);

        for(int i = 0; i < n; i++) {
            cout << a[i];
        }
        cout << '\n';
    }

    MPI_Finalize();
    return 0;

}