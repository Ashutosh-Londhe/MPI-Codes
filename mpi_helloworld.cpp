#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int mpi_rank, mpi_size;
    int len;
    char proc_name[MPI_MAX_PROCESSOR_NAME];

    // Initialize the MPI environment
    MPI::Init(argc, argv);

    // Get the number of processes
    mpi_size = MPI::COMM_WORLD.Get_size();

    // Get the rank of the process
    mpi_rank = MPI::COMM_WORLD.Get_rank();
    
    // Get the name of the processor
    MPI::Get_processor_name(proc_name, len);

    printf("Hello world from Rank: %d, out of total: %d. Processor name: %s\n", mpi_rank, mpi_size, proc_name);

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}// End of main

