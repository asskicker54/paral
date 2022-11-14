#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int **a = new int *[2 * size];
    a[0] = new int[2 * size * size];
    for (int i = 1; i < 2 * size; i++) {
        a[i] = a[i - 1] + size;
    }

    if (rank == 0) {
        for (int i = 0; i < 2 * size; i++) {
            if ((i % 2) == 0) {
                for (int j = 0; j < size; j++) {
                    a[i][j] = i / 2;
                }
                for (int j = 0; j < size; j++) {
                    a[i + 1][j] = i / 2;
                }
            }
        }
    }

    int **b = new int *[2];
    b[0] = new int[2 * (rank + 1)];
    for (int i = 1; i < 2; i++) {
        b[i] = b[i - 1] + (rank + 1);
    }

    int *c = new int[size];
    int *d = new int[size];
    for (int i = 0; i < size; i++) {
        c[i] = 2 * (i + 1);
        d[i] = 2 * i * size;
    }

    MPI_Scatterv(*a, c, d, MPI_INT, *b, 2 * (rank + 1), MPI_INT, 0, MPI_COMM_WORLD);
    cout << rank << endl;
    cout << "a = [";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < rank + 1; j++) {
            cout << " " << b[i][j];
        }
        cout << endl;
    }
    cout << " ]" << endl;
    MPI_Finalize();
    delete a;
    delete b;
    delete c;
    delete d;
    return 0;
}