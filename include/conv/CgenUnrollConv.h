#ifndef CGENUNROLLCONV_H
#define CGENUNROLLCONV_H
#include "conv/BaseConv.h"
#include "string_exec.h"

class CgenUnrollConv: public BaseConv
{
	public:
	StringCompile sc={"../cmpflags.txt","tmpfiles","tmpunroll"};
	StringExec se;
	CgenUnrollConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel);
	~CgenUnrollConv();
	void forward();
};
#endif
