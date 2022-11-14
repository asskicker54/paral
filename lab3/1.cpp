#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int rank;
    int size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int* a;
    if (rank == 0) {
        a = new int[size * 3];
        for (int i = 0; i < size * 3; i++) {
            a[i] = i;
        }

        for (int i = 1; i < size * 3; i++) {
            if (i % size != 0) {
                MPI_Send(&a[i], 1, MPI_INT, (i % size), 777, MPI_COMM_WORLD);
            }
        }
    } else {
        a = new int[3];
        for (int i = 0; i < 3; i++) {
            MPI_Recv(&a[i], 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
        }

        cout << "\nrank: " << rank << "     num: ";
        for (int i = 0; i < 3; i++) {
            cout << " " << a[i] << ", ";
        }

    }

    delete []a;
    MPI_Finalize();

    return 0;
}