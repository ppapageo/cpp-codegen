#ifndef BASECONV_H
#define BASECONV_H
#include "conv/ConvUtils.h"
#include <omp.h>
class BaseConv
{
	public:
	int in_ch;
	int in_row;
	int in_col;
	int out_ch;
	int out_row;
	int out_col;
	int k_row;
	int k_col;
	int pad;
	int stride;

	void print();
	BaseConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel);
	virtual ~BaseConv();
	float *output;
	float *input;
	float *kernel;
};
#endif
