#include "conv/CgenConv.h"

CgenConv::CgenConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel): BaseConv(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel){
	se.append_file("../templates/conv.txt");
	se.replace("$in_ch",std::to_string(in_ch));
	se.replace("$out_ch",std::to_string(out_ch));
	se.replace("$out_row",std::to_string(out_row));
	se.replace("$out_col",std::to_string(out_col));
	se.replace("$k_row",std::to_string(k_row));
	se.replace("$k_col",std::to_string(k_col));
	se.replace("$stride",std::to_string(stride));
	se.replace("$in_row",std::to_string(in_row));
	se.replace("$in_col",std::to_string(in_col));
	se.save();
	se.compile();

	se.openlib("/tmp/cpp-codegen/libtmpconv.so");
	se.loadlib("func");

}

CgenConv::~CgenConv(){
	se.closelib();
}

void CgenConv::forward(){
	se.func(input,kernel,&output);
}
