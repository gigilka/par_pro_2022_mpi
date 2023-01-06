// Copyright 2022 Kuchin Nikita
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../modules/task_2/kuchin_n_ring_topology/ring_topology.h"

void shift(void* message, int start, int end) {
    int csize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == start) {
        int next_rank = (rank + 1) % csize;
        MPI_Send(message, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
        return;
    }
    if (rank != end && (end - start) != 1 && (rank > start || rank < end)) {
        int prev_rank = rank - 1;
        if (rank == 0) {
            prev_rank == csize - 1;
        }
        MPI_Recv(message, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        int next_rank = (rank + 1) % csize;
        MPI_Send(message, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    if (rank == end) {
        int last_rank = end - 1;
        if (end == 0) {
            last_rank = csize - 1;
        }
        MPI_Recv(message, 1, MPI_INT, last_rank, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    }
}
