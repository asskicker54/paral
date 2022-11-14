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

    int* a = new int[2 * size];

    if (rank == 0) {
        for (int i = 0; i < 2 * size; i++) {
            a[i] = i;
        }
    }

    int* b = new int[2];

    MPI_Scatter(a, 2, MPI_INT, b, 2, MPI_INT, 0, MPI_COMM_WORLD);

    sleep(rank);

    cout << "rank: " << rank << endl;
    cout << "a = [";
    for (int i{0}; i < 2; i++) {
        cout << " " << b[i];
    }

    cout << " ]" << endl;
    MPI_Finalize();

    delete a;
    delete b;

    return 0;
}