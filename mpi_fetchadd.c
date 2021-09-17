#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int mpi_rank, mpi_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    if(mpi_size != 2)
    {
        if(mpi_rank == 0)
            printf("Error!! Please run with 2 MPI processes \n");
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    int window_buffer = 0;
    if(mpi_rank == 1)
        window_buffer = 10;
    MPI_Win window;
    MPI_Win_create(&window_buffer, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &window);    
    
    if(mpi_rank == 1)
    {
        printf("[MPI process 1] Value in my window_buffer before MPI_fetch_op: %d.\n", window_buffer);
    }
    MPI_Win_fence(0, window);
 
    int my_value, ret_val;
    if(mpi_rank == 0)
    {
        my_value = 15; ret_val = -1;
        MPI_Fetch_and_op(&my_value, &ret_val, MPI_INT, 1, 0, MPI_SUM, window);    
        printf("[MPI process 0] I put data %d in MPI process 1 window via MPI_fetch_op(sum).\n", my_value);
    }
    
    MPI_Win_fence(0, window);
                   
    if(mpi_rank == 1)
    {
        printf("[MPI process 1] Value in my window_buffer after MPI_Put: %d.\n", window_buffer);
    } 
    else
    {
        printf("[MPI process 0] i got %d as a return value.\n", ret_val);
    }

    MPI_Win_free(&window);
    MPI_Finalize();

    return 0;
}// End of main
