#include <gtest/gtest.h>
#include "conv/ConvUtils.h"
#include "conv/VanillaConv.h"
#include "conv/CgenConv.h"
#include "conv/CgenUnrollConv.h"
#include "conv/Im2colConv.h"
#include "string_exec.h"
#define THRESHOLD 5e-4
int perc_diff(float a, float b){
	return 100*(a-b)/a;
}
//In 2 equal sized matrices, checks if all float elements
//differ only up to a tolerance level
bool matr_all_equal(float* a, float* b, int size){
	for(int i =0; i<size; i++){
		if(perc_diff(a[i],b[i])>THRESHOLD)
			return false;
	}
	return true;
}


TEST(Conv, CgenConv) {
	int in_ch=32;
	int in_row=96;
	int in_col=96;
	int out_ch=128;
	int k_row=3;
	int k_col=3;
	int stride=1;
	int pad=1;
	if (pad==1){
		pad=(k_row-1)/2;
	}
	float* input = populate_rand(in_ch*in_row*in_col, 15.42, 0.42);
	float* kernel = populate_rand(out_ch*in_ch*k_row*k_col, 15.42, 0.42);
	pad_input(in_ch, &in_row, &in_col, pad, &input);	
	VanillaConv vc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	CgenConv cc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	EXPECT_EQ(true,matr_all_equal(vc.output,cc.output,vc.out_ch*vc.out_col*vc.out_row));
	delete [] input;
	delete [] kernel;
}

TEST(Conv, CgenUnrollConv) {
	int in_ch=32;
	int in_row=96;
	int in_col=96;
	int out_ch=128;
	int k_row=3;
	int k_col=3;
	int stride=1;
	int pad=1;
	if (pad==1){
		pad=(k_row-1)/2;
	}
	float* input = populate_rand(in_ch*in_row*in_col, 15.42, 0.42);
	float* kernel = populate_rand(out_ch*in_ch*k_row*k_col, 15.42, 0.42);
	pad_input(in_ch, &in_row, &in_col, pad, &input);	
	VanillaConv vc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	CgenUnrollConv uc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	EXPECT_EQ(true,matr_all_equal(vc.output,uc.output,vc.out_ch*vc.out_col*vc.out_row));
	delete [] input;
	delete [] kernel;
}

TEST(Conv, Im2colConv) {
	int in_ch=32;
	int in_row=96;
	int in_col=96;
	int out_ch=128;
	int k_row=3;
	int k_col=3;
	int stride=1;
	int pad=1;
	if (pad==1){
		pad=(k_row-1)/2;
	}
	float* input = populate_rand(in_ch*in_row*in_col, 15.42, 0.42);
	float* kernel = populate_rand(out_ch*in_ch*k_row*k_col, 15.42, 0.42);
	pad_input(in_ch, &in_row, &in_col, pad, &input);	
	VanillaConv vc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	Im2colConv ic(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	EXPECT_EQ(true,matr_all_equal(vc.output,ic.output,vc.out_ch*vc.out_col*vc.out_row));
	delete [] input;
	delete [] kernel;
}

