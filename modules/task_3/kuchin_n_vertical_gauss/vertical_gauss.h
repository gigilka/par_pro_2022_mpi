// Copyright 2022 Kuchin Nikita

#include <mpi.h>

#ifndef MODULES_TASK_3_KUCHIN_N_VERTICAL_GAUSS_VERTICAL_GAUSS_H_
#define MODULES_TASK_3_KUCHIN_N_VERTICAL_GAUSS_VERTICAL_GAUSS_H_

int* getRandomImage(int srcwidth, int srcheight);
int* getSequentialGauss(const int* image, int srcwidth, int srcheight)
int* getParallelGauss(const int* image, int width, int height);

#endif  // MODULES_TASK_3_KUCHIN_N_VERTICAL_GAUSS_VERTICAL_GAUSS_H_