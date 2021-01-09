#include "conv/ConvUtils.h"

void pad_input(int in_ch, int* in_row, int* in_col, int pad, float** input){
	if(pad==1){
		int in_addr, in_addr_pad;
		int row_pad=(*in_row)+2*pad;
		int col_pad=(*in_col)+2*pad;
		float* temp;
		//new zero matrix
		temp = new float[in_ch*row_pad*col_pad]();
		//fill in
		for(int ki=0; ki<in_ch; ki++){
			for(int i=0; i<(*in_row); i++){
				for(int j=0; j<(*in_col); j++){
					in_addr=((*in_row) * ki+i) * (*in_col)+j;
					in_addr_pad=(row_pad*ki+i+pad)*col_pad+j+pad;
					temp[in_addr_pad]=(*input)[in_addr];
				}
			}
		}
		float* todel = *input;
		*input=temp;
		delete [] todel;
		*in_row=row_pad;
		*in_col=col_pad;

	}
}

float* populate_zero(int size){
	float* arr = new float[size]();
	return arr;
}

float* populate_rand(int size, float high, float low){
	float* arr = new float[size];
	for (int i=0; i < size; i ++){
		arr[i]= low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
	}
	return arr;
}

void im2col(const float *data_im, const int in_ch, const int in_row, const int in_col, const int k_row, const int k_col, const int out_row, const int out_col, const int stride, float *data_col) {
	int data_im_addr;
	int data_col_addr=0;
	int i,j,ii,jj,ki,m,n;
	for(ki = 0; ki < in_ch; ki++){
		for(m = 0; m < k_row; m++){
			for(n = 0; n < k_col; n++){
				for(i = 0; i < out_row; i++){
					for(j=0; j < out_col; j++){
						jj = stride*j + n;
						ii = stride*i + m;
						data_im_addr =(ki*in_row+ii)*in_col+jj;
						data_col[data_col_addr++] = data_im[data_im_addr];
					}
				}
			}
		}
	}

}
void im2col_and_matmul(int in_ch, int in_row, int in_col, int out_ch, int out_row, int out_col, int k_row, int k_col, int pad, int stride, const float *input, const float *weight, float *data_col, float *output) {
	int in_ch_per_group = in_ch;
	int out_ch_per_group = out_ch;
	float alpha = 1;
	float beta = 0;

	im2col(input, in_ch, in_row, in_col, k_row, k_col, out_row, out_col, stride, data_col);
	int m = out_ch_per_group;
	int k = in_ch_per_group * k_row * k_col;
	int n = out_row * out_col;
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			m, n, k, alpha, weight,
			k, data_col, n, beta, output, n);

}
