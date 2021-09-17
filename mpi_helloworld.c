#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int mpi_rank, mpi_size;
    int len;
    char name[MPI_MAX_PROCESSOR_NAME];

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    
    // Get the name of the processor
    MPI_Get_processor_name(name, &len);

    printf("Hello world from Rank: %d, out of total: %d. Processor name: %s\n", mpi_rank, mpi_size, name);

    MPI_Finalize();
}// End of main

