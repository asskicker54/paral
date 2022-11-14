#include <mpi.h>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

void My_Bcast(void*, int, MPI_Datatype, int, MPI_Comm);

int main(int argc, char* argv[]){
    int rank;
    int arr_size = 100;
    int a[arr_size];
    double avg_time;
    for (int s = 0; s < arr_size; s++) {
        a[s] = s;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double my_start_time = MPI_Wtime();
    for (int i = 1; i < arr_size; i++) {
    MPI_Barrier(MPI_COMM_WORLD);
        My_Bcast(a, i, MPI_INT, 0, MPI_COMM_WORLD);
        //cout << "rank " << rank << "\t" << a[i] << "\n";
    MPI_Barrier(MPI_COMM_WORLD);
    }
    double my_end_time = MPI_Wtime();
    double final_time = my_end_time - my_start_time;
    cout << final_time << endl;

    MPI_Finalize();
    return 0;
}

void My_Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int rank;
    MPI_Comm_rank(comm, &rank);
    int size;
    MPI_Comm_size(comm, &size);

    if (rank != root) {
        MPI_Recv(buffer, count, datatype, MPI_ANY_SOURCE, 7777, comm, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < ceil(log2(size)); i++) {
        if (rank < pow(2, i)) {
            MPI_Send(buffer, count, datatype, int(ceil(rank + pow(2, i))) % size, 7777, comm);
        }
    }
}


