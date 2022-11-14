#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank;
    int size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int **a = new int *[size];
    a[0] = new int[size * size];
    for (int i = 1; i < size; i++) {
        a[i] = a[i - 1] + size;
    }
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                a[i][j] = i;
            }
        }
    }

    int *c = new int[size];
    int *d = new int[size];
    for (int i = 0; i < size; i++) {
        c[i] = size - i;
        d[i] = i * size;
    }

    int *b = new int[size - rank];

    MPI_Scatterv(*a, c, d, MPI_INT, b, size - rank, MPI_INT, 0, MPI_COMM_WORLD);
    cout << rank << endl;
    cout << "a = [";
    for (int i = 0; i < size - rank; i++) {
        cout << " " << b[i];
    }
    cout << endl;
    MPI_Finalize();
    delete a;
    delete b;
    delete c;
    delete d;
    return 0;
}