// Copyright 2022 Kuchin Nikita
#include "../../../modules/task_2/kuchin_n_ring_topology/ring_topology.h"

#include <mpi.h>

#include <random>

int randomMesg() {
    std::random_device dev;
    std::mt19937 gen(dev());
    int tmp = 1;
    tmp = gen() % 2147483646;
    return tmp;
}

void shift(int& message, const int start) {
    int rank, csize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int result = 0;
    MPI_Status st;

    if (rank == start) {
        MPI_Send(&message, 1, MPI_INT, (start + 1) % csize, 0, MPI_COMM_WORLD);
        MPI_Recv(&message, 1, MPI_INT, (start - 1) % csize, 0, MPI_COMM_WORLD,
                 &st);
    } else {
        MPI_Recv(&message, 1, MPI_INT, (rank - 1) % csize, 0, MPI_COMM_WORLD,
                 &st);
        MPI_Send(&message, 1, MPI_INT, (rank + 1) % csize, 0, MPI_COMM_WORLD);
    }
}
