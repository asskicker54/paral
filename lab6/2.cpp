#include "mpi.h"
#include <iostream>
#include "time.h"
#include <cmath>
#include <limits>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    int rank;
    int size;
    double s = 0;
    double t1, t2;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int p = 3; p < 10; p++){

        int n = pow(10, p);

        double best_time = numeric_limits<double>::infinity();

        for(int j = 1; j <= 100; j++){
            s = 0;

                t1 = MPI_Wtime();
                
                for(int i = 0; i <= n; i += 1){
                    s += (1. / (1. + i));
                }

                t2 = MPI_Wtime();

                if((t2 - t1) < best_time){
                    best_time = t2 - t1;
                }

                if(j == 100){
                    printf("\nSum = %f \nn: 10 |Pow: %d \nBest time = %g \n\n", s, p, best_time);
                }
        }
    }
  
    MPI_Finalize();
    return 0;
}
