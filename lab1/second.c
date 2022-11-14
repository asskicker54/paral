#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    double startTime = MPI_Wtime();
    for(int i = 1; i <= 10; i++){
        double tick = MPI_Wtick();
        printf("Tick%d = %0.9f \n", i, tick);
    }
    double endTime = MPI_Wtime();

    printf("Time = %f \n", endTime - startTime);
    return 0;
}
