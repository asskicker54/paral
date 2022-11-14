#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    double sum = 0;
    int n = pow(10, 9);
    MPI_Init(&argc, &argv);
    double startTime = MPI_Wtime();
    for (double i = 1; i < n; i++) {
        sum += 1/(i+1);
    }
    double endTime = MPI_Wtime();
    MPI_Finalize();
    printf("Sum = %f \nTime = %f\n", sum, endTime - startTime);
    return 0;
}
