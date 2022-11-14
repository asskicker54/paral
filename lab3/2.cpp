#include <iostream>
#include <mpi.h>

using namespace std;

int CreateSequence(int n){
	return abs((n - 1)) * (2 + n) / 2;
};


int main(int argc, char* argv[]) {
    int rank;
    int size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("rank=%d a:", rank);
        int* a = new int[CreateSequence(size)];
        int r = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&a[r], i + 1, MPI_INT, i, 777, MPI_COMM_WORLD, &stat);
            r = CreateSequence(i + 1);
        }
        for (int i = 0; i < CreateSequence(size); i++) {
            printf("%d", a[i]);
        }
        printf("\n");
        delete []a;
    } else {
        printf("rank=%d a:", rank);
        int* a = new int[rank + 1];
        for (int i = 0; i < rank + 1; i++) {
            a[i] = rank;
        }
            MPI_Send(&a[0], rank + 1, MPI_INT, 0, 777, MPI_COMM_WORLD);
        for (int i = 0; i < rank + 1; i++) {
            printf("%d", a[i]);
        }
        printf("\n");
        delete []a;
    }

    
    MPI_Finalize();

    return 0;
}