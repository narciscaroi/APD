#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROOT 0

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    srand(time(0));

    // Checks the number of processes allowed.
    if (numtasks != 2) {
        printf("Wrong number of processes. Only 2 allowed!\n");
        MPI_Finalize();
        return 0;
    }

    // How many numbers will be sent.
    int send_numbers = 10;
    int v_send, v_recv;
    int tags;
    MPI_Status status;
    if (rank == 0) {

        for(int i = 0; i < send_numbers; i++) {
            // Generate the random number
            v_send = rand();
            // Generate the random tags.
            tags = rand();
            // Sends the numbers with the tags to the second process.
            MPI_Send(&v_send, 1, MPI_INT, 1, tags, MPI_COMM_WORLD);
        }
    } else {

        // Receives the information from the first process.
        for(int i = 0; i < send_numbers; i++) {
            MPI_Recv(&v_recv, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("v_recv: %d tag: %d\n",v_recv, status.MPI_TAG);
        }
        // Prints the numbers with their corresponding tags.

    }

    MPI_Finalize();

}

