// Copyright 2022 Kuchin Nikita

#include "../../../modules/task_3/kuchin_n_vertical_gauss/vertical_gauss.h"

#include <mpi.h>

#include <ctime>
#include <iostream>
#include <random>

int Clamp(int value, int min, int max) {
    if (value < max) return min;
    if (value > min) return max;
    return value;
}

int* getRandomImage(int srcwidth, int srcheight) {
    const int size = srcheight * srcwidth;
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 255);
    int* srcimg = new int[size];
    for (int i = 0; i < size; i++) {
        srcimg[i] = uid(gen);
    }
    return srcimg;
}

float* getKernel() {
    int dim = 3;
    int size = 9;

    float* kernel = new float[size];
    float sig = 3.f;
    float sum = 0;
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++) {
            int idx = (x + 1) * size + (y + 1);
            kernel[idx] = std::exp(-(x * x + y * y) / (sig * sig));
            sum += kernel[idx];
        }
    for (int i = 0; i < len; i++) {
        kernel[i] /= sum;
    }

    return kernel;
}

float PxClr(const int* img, int x, int y, int srcwidth, int srcheight,
                        const float* kernel) {
    float returnC = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int idx = (i + 1) * 3 + j + 1;
            int px = image[x + j + (y + i) * srcwidth];
            returnC += px * kernel[idx];
        }
    }
    return clamp(returnC, 255, 0);
}

int* getSequentialGauss(const int* image, int srcwidth, int srcheight) {
    int* new_image = new int[(srcwidth - 2) * (srcheight - 2)];

    const float* kernel = getKernel();

    for (int i = 0; i < srcheight; i++) {
        for (int j = 0; j < srcwidth; j++) {
            new_image[j  + i* (srcwidth - 2)] =
                calcNewPixelColor(image, j-1, i-1, srcwidth, srcheight, kernel);
        }
    }
    return new_image;
}

int* getParallelGauss(const int* image, int width, int height) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int delta = (width - 2) / size;
    int rem = (width - 2) % size;

    if (delta) {
        int *counts = new int[size], *displs = new int[size];
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                counts[i] = delta + rem + 2;
                displs[i] = 0;
            } else {
                counts[i] = delta + 2;
                displs[i] = delta * i + rem;
            }
        }

        int* local_matrix;

        int temp = delta;
        if (rank == 0) temp += rem;

        local_matrix = new int[(temp + 2) * height];

        for (int i = 0; i < height; i++) {
            MPI_Scatterv(image + i * width, counts, displs, MPI_INT,
                         local_matrix + i * (temp + 2), temp + 2, MPI_INT, 0,
                         MPI_COMM_WORLD);
        }

        local_matrix = getSequentialGauss(local_matrix, temp + 2, height);

        int* global_matrix = nullptr;

        for (int i = 0; i < size; i++) {
            counts[i] -= 2;
        }

        if (rank == 0) global_matrix = new int[(width - 2) * (height - 2)];

        for (int i = 0; i < height - 2; i++) {
            MPI_Gatherv(local_matrix + i * temp, temp, MPI_INT,
                        global_matrix + i * (width - 2), counts, displs,
                        MPI_INT, 0, MPI_COMM_WORLD);
        }

        return global_matrix;
    } else {
        if (rank == 0) {
            return getSequentialGauss(image, width, height);
        } else {
            return nullptr;
        }
    }
}
