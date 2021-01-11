#ifndef CGENCONV_H
#define CGENCONV_H
#include "conv/BaseConv.h"
#include "string_exec.h"

class CgenConv: public BaseConv
{
	public:
	StringCompile sc={"../cmpflags.txt","/tmp/cpp-codegen","tmpconv"};
	StringExec se;
	CgenConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel);
	~CgenConv();
	void forward();
};
#endif
