#include <iostream>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    int rank;
    int size;
    int n = 0;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        //0 процесс
        int** a = new int*[size];
        a[0] = new int[size*size];

        for(int i = 1; i < size; i++) {
            a[i] = a[i - 1] + size;
        }

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
                a[i][j] = 0;
            }
        }

        for(int i = 1; i < size; i++) {
            //проверяем входные сообщения без их реального приема
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            MPI_Get_count(&stat, MPI_INT, &n);
            //Принимаем массив от sourse, с n количеством элементов
            MPI_Recv(a[stat.MPI_SOURCE], n, MPI_INT, stat.MPI_SOURCE, 777, MPI_COMM_WORLD, &stat);
            printf("rank = %d, n = %d source = %d \n", rank, n, stat.MPI_SOURCE);
        }

        cout << "a: \n";
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                cout << a[i][j] << "\t";
            }
            cout << endl;
        }
    } else {
        //не 0 процесс
        srand(rank);
        n = rand() % size + 1;

        cout << "rank: " << rank << " n=" << n << endl;
        int* a = new int[n];

        for(int i = 0; i < n; i++){
            a[i] = rank;
        }
        //Отправляем массив на 0 процесс
        MPI_Send(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}