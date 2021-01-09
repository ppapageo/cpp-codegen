#include "conv/Im2colConv.h"

void Im2colConv::forward(){
	float* temp = populate_zero(in_ch*k_row*k_col*out_row*out_col);
	int pad = 0;
	im2col_and_matmul(in_ch,in_row,in_col,out_ch,out_row,out_col,k_row,k_col,pad,stride,input,kernel,temp,output);
	delete [] temp;
}
