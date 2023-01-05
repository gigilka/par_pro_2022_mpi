// copyright 2022 Kuchin Nikita

#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>
#include <vector>

#include "./ring_topology.h"

TEST(MPI_2, MPI_2_ring_1_Test) {
    int rank, csize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int msg = randomMesg();
    int tmp = msg;
    int start = csize / 2;

    shift(tmp, start);
    ASSERT_EQ(tmp, msg);
}

TEST(MPI_2, MPI_2_ring_2_Test) {
    int rank, csize = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int msg = randomMesg();
    int tmp = msg;
    int start = csize / 4;

    shift(tmp, start);
    ASSERT_EQ(tmp, msg);
}

TEST(MPI_2, MPI_2_ring_3_Test) {
    int rank, csize = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int msg = randomMesg();
    int tmp = msg;
    int start = 0;

    shift(tmp, start);
    ASSERT_EQ(tmp, msg);
}

TEST(MPI_2, MPI_2_ring_4_Test) {
    int rank, csize = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int msg = randomMesg();
    int tmp = msg;
    int start = csize / 3;

    shift(tmp, start);
    ASSERT_EQ(tmp, msg);
}

TEST(MPI_2, MPI_2_ring_5_Test) {
    int rank, csize = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    int msg = randomMesg();
    int tmp = msg;
    int start = csize;

    shift(tmp, start);
    ASSERT_EQ(tmp, msg);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
