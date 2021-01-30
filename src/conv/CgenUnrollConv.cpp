#include "conv/CgenUnrollConv.h"

CgenUnrollConv::CgenUnrollConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel): BaseConv(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel){
	
	se.append_file("../templates/conv_unroll.txt");
	se.replace("$in_ch",std::to_string(in_ch));
	se.replace("$out_ch",std::to_string(out_ch));
	se.replace("$out_row",std::to_string(out_row));
	se.replace("$out_col",std::to_string(out_col));
	se.replace("$k_row",std::to_string(k_row));
	se.replace("$k_col",std::to_string(k_col));
	se.replace("$stride",std::to_string(stride));
	se.replace("$in_row",std::to_string(in_row));
	se.replace("$in_col",std::to_string(in_col));
	std::stringstream unrolled;
	for(int m=0; m<k_row; m++){
		for(int n=0; n<k_col; n++){
			int kofst=m*k_col+n;
			int jj = n;
			int ii= m;
			int inofst=ii*in_col+jj;
			unrolled<<"					float ps"<<kofst<<"=kernel[k_addr+"<<kofst<<"]*input[in_addr+"<<inofst<<"];\n";
		}
	}
	unrolled<<"					(*output)[out_addr]+=";
	for(int s=0; s<k_row*k_col-1; s++) unrolled<<"ps"<<s<<"+";
	unrolled<<"ps"<<k_row*k_col-1<<";\n";
	se.replace("$unroll",unrolled.str());
	se.save();
	se.compile();

	se.openlib("/tmp/cpp-codegen/libtmpunroll.so");
	se.loadlib("func");

}

CgenUnrollConv::~CgenUnrollConv(){
	se.closelib();
}

void CgenUnrollConv::forward(){
	se.func(input,kernel,&output);
}
