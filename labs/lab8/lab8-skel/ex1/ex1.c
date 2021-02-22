#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int recv_num, send_num;
    srand(time(0));
    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number.
        send_num = rand();
        // Send the number to the next process.
        MPI_Send(&send_num, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        printf("First procces send the number : %d\n",send_num);
        MPI_Recv(&recv_num, 1, MPI_INT, numtasks-1, 0, MPI_COMM_WORLD, NULL);
        printf("First procces received the number : %d\n",recv_num);

    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the number from the previous process.
        MPI_Recv(&recv_num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, NULL);
        // Increments the number.
        send_num = recv_num + 2;
        // Sends the number to the first process.
        MPI_Send(&send_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } else {
        // Middle process.
        // Receives the number from the previous process.
        MPI_Recv(&recv_num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, NULL);
        // Increments the number.
        send_num = recv_num + 2;
        // Sends the number to the next process.
        MPI_Send(&send_num, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();

}

