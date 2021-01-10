#ifndef CONVUTILS_H
#define CONVUTILS_H
#include <stdio.h>
#include <iostream>
#include <cblas.h>
#include <cstdlib>
#include <math.h>
#include <chrono>
void pad_input(int in_ch, int* in_row, int* in_col, int pad, float** input);

float* populate_rand(int size, float high, float low);

float* populate_zero(int size);

void im2col(const float *data_im, const int channels, const int height, const int width, const int kernel_h, const int kernel_w, const int output_h, const int output_w, const int stride, float *data_col);

void im2col_and_matmul(int in_ch, int in_row, int in_col, int out_ch, int out_row, int out_col, int k_row, int k_col, int pad, int stride, const float *input, const float *weight, float *data_col, float *output);
#endif
