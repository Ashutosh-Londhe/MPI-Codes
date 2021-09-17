#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char *argv[] )
{
    int errs = 0;
    int mpi_rank, mpi_size;
    int num_bucket = 256;
    int *sendbuf, *recvval, i, j;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank );
    MPI_Comm_size( MPI_COMM_WORLD, &mpi_size );

    if(mpi_size < 2)
    {
        printf("Exclusive scan should have more than 1 PE\n"); 
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    sendbuf = (int *)malloc( num_bucket * sizeof(int) );
    recvval = (int *)malloc( num_bucket * sizeof(int) );
       
    /* Initialize data */
    for (j = 0; j < num_bucket; j++) 
        sendbuf[j] = mpi_rank;

    MPI_Barrier(MPI_COMM_WORLD);

    struct timespec start, end;
    double startSeconds, endSeconds;

    clock_gettime(CLOCK_MONOTONIC, &start);
    /* Perfrom Exscan */
    MPI_Exscan( sendbuf, recvval, num_bucket, MPI_INT, MPI_SUM, MPI_COMM_WORLD );
    clock_gettime(CLOCK_MONOTONIC, &end);

    free( sendbuf );
    free( recvval );

    startSeconds = start.tv_sec + ((double) start.tv_nsec ) * 1.0e-9;
    endSeconds   = end.tv_sec   + ((double) end.tv_nsec ) * 1.0e-9;

    double time_us = (endSeconds - startSeconds)* 1000.0;
    
    printf("Rank: %d, execution time: %lf ms. \n", mpi_rank, time_us);

    MPI_Finalize();
    return 0;
}// End of main

