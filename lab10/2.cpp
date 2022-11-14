#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int n;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* a = new int[size * (size + 1)];

    if (rank == 0) {
        for (int i = 0; i < size * (size + 1); i++) {
            a[i] = i;
        }
    }

    int* b = new int[2 * rank + 2];

    int* c = new int[size];
    int* d = new int[size];

    for (int i{0}; i < size; i++) {
        c[i] = 2 * i + 2;
    }

    d[0] = 0;
    for (int i{0}; i < size; i++) {
        d[i] = d[i - 1] + 2 * i;
    }

    MPI_Scatterv(a, c, d, MPI_INT, b, 2 * rank + 2, MPI_INT, 0, MPI_COMM_WORLD);

    sleep(rank);

    cout << "rank: " << rank << endl;
    cout << "a = [";
    for (int i{0}; i < 2 * rank + 2; i++) {
        cout << " " << b[i];
    }

    cout << " ]" << endl;
    MPI_Finalize();

    delete a;
    delete b;
    delete c; 
    delete d;

    return 0;
}