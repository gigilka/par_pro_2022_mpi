// Copyright 2022 Kuchin Nikita

#include "../../../modules/task_2/kuchin_n_ring_topology/ring_topology.h"

#include <./mpi.h>

#include <iostream>
#include <random>
#include <vector>

int randomMesg() {
    std::random_device dev;
    std::mt19937 gen(dev());
    int tmp = 1;
    tmp = gen() % 2147483646;
    return tmp;
}

void shift(int const& message, const int start) {
    int rank, csize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int result = 0;
    MPI_Request req;

    if (rank == start) {
        MPI_Isend(&message, 1, MPI_INT, (rank + 1) % csize, 0, MPI_COMM_WORLD,
                  &req);
    }
    if (rank != (start)) {
        int prevrank = (rank - 1) % csize;
        int nextrank = (rank + 1) % csize;
        MPI_Irecv(&result, 1, MPI_INT, prevrank, 0, MPI_COMM_WORLD, &req);
        result = result - 1;
        MPI_Isend(&result, 1, MPI_INT, nextrank, 0, MPI_COMM_WORLD, &req);
    }

    if (rank == start) {
        MPI_Irecv(&result, 1, MPI_INT, (start - 1) % csize, 0, MPI_COMM_WORLD,
                  &req);
    }
}
