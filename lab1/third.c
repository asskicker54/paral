#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    char name[MPI_MAX_PROCESSOR_NAME];
    int nameLen;
    MPI_Get_processor_name(name, &nameLen);
    MPI_Finalize();
    printf("Hello World from processor %s \nResultlen = %d \n", name, nameLen);
    return 0;
}
