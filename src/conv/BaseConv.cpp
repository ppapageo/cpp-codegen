#include "conv/BaseConv.h"

BaseConv::BaseConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel){
	this->out_ch = out_ch;
	this->in_ch = in_ch;
	this->in_row = in_row;
	this->in_col = in_col;
	this->k_row = k_row;
	this->k_col = k_col;
	this->pad = pad;
	this->stride = stride;

	this->out_row = (in_row - k_row )/stride+1;
	this->out_col = (in_col - k_col )/stride+1;
	srand (static_cast <unsigned> (time(0)));
	this->output = populate_zero(this->out_ch*this->out_row*this->out_col);
	this->input = input;
	this->kernel = kernel;
}

BaseConv::~BaseConv(){
	delete[] output;
}
