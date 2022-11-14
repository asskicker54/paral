#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int n = 2;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int** a = new int* [2 * size];
    a[0] = new int[2 * n * size];
    for (int i{1}; i < 2 * size; i++) {
        a[i] = a[i - 1] + n;
    }

    if (rank == 0) {
        for (int i = 0; i < 2 * size; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i;
            }
        }
    }

    int** b = new int* [2];
    b[0] = new int[2 * n];

    for (int i{1}; i < 2; i++) {
        b[i] = b[i - 1] + n;
    }

    int* c = new int[size];
    int* d = new int[size];

    for (int i{0}; i < size; i++) {
        c[i] = i + 1;
        d[i] = (i * (i + 1)) / 2;
    }

    MPI_Scatter(*a, 2 * n, MPI_INT, *b, 2 * n, MPI_INT, 0, MPI_COMM_WORLD);

    sleep(rank);

    cout << "rank: " << rank << endl;
    cout << "a = [";
    for (int i{0}; i < 2; i++) {
        for (int j{0}; j < n; j++) {
            cout << " " << b[i][j];
        }
        cout << endl;
    }

    cout << " ]" << endl;
    MPI_Finalize();

    delete []a;
    delete []b;
    delete []c; 
    delete []d;

    return 0;
}