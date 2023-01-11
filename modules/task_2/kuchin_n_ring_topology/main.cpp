// Copyright 2022 Kuchin NIkita
#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./ring_topology.h"

TEST(MPI_2, MPI_2_test_1_Test) {
    int testn = 1;
    int rank, csize;
    int msg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);

    if (csize != 1) {
        if (rank == 0) {
            msg = 123;
        }

        shift(&msg, 0, 1);
        //  std::cout << "test" << testn << " " << rank << " " << msg <<
        //  std::endl;
        if (rank == 1) {
            ASSERT_EQ(msg, 123);
        }
    }
}

TEST(MPI_2, MPI_2_test_2_Test) {
    int testn = 2;
    int rank, csize;
    int msg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);

    if (csize != 1) {
        if (rank == 0) {
            msg = 123;
        }

        shift(&msg, 0, csize - 1);
        //  std::cout << "test" << testn << " " << rank << " " << msg <<
        //  std::endl;
        if (rank == csize - 1) {
            ASSERT_EQ(msg, 123);
        }
    }
}

TEST(MPI_2, MPI_2_test_3_Test) {
    int testn = 3;
    int rank, csize;
    int msg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);

    if (csize != 1) {
        if (rank == csize / 2) {
            msg = 123;
        }

        shift(&msg, csize / 2, 0);
        //  std::cout << "test" << testn << " " << rank << " " << msg <<
        //  std::endl;
        if (rank == 0) {
            ASSERT_EQ(msg, 123);
        }
    }
}

TEST(MPI_2, MPI_2_test_4_Test) {
    int testn = 4;
    int rank, csize;
    int msg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);

    if (csize != 1) {
        if (rank == csize - 1) {
            msg = 123;
        }

        shift(&msg, csize - 1, 0);
        //  std::cout << "test" << testn << " " << rank << " " << msg <<
        //  std::endl;
        if (rank == 0) {
            ASSERT_EQ(msg, 123);
        }
    }
}

TEST(MPI_2, MPI_2_test_5_Test) {
    int testn = 5;
    int rank, csize;
    int msg;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);

    if (csize != 1) {
        if (rank == 1) {
            msg = 123;
        }

        shift(&msg, 1, 0);
        //  std::cout << "test" << testn << " " << rank << " " << msg <<
        //  std::endl;
        if (rank == 0) {
            ASSERT_EQ(msg, 123);
        }
    }
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
