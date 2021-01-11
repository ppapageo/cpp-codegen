#include "conv/CgenUnrollConv.h"

CgenUnrollConv::CgenUnrollConv(int out_ch, int in_ch, int in_row, int in_col, int k_row, int k_col, int pad, int stride, float* input, float* kernel): BaseConv(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel){
	
	sc.append_file("../templates/conv_unroll.txt");
	sc.replace("$in_ch",std::to_string(in_ch));
	sc.replace("$out_ch",std::to_string(out_ch));
	sc.replace("$out_row",std::to_string(out_row));
	sc.replace("$out_col",std::to_string(out_col));
	sc.replace("$k_row",std::to_string(k_row));
	sc.replace("$k_col",std::to_string(k_col));
	sc.replace("$stride",std::to_string(stride));
	sc.replace("$in_row",std::to_string(in_row));
	sc.replace("$in_col",std::to_string(in_col));
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
	sc.replace("$unroll",unrolled.str());
	sc.save();
	sc.compile();

	se.openlib("/tmp/cpp-codegen/libtmpunroll.so");
	se.loadlib("func");

}

CgenUnrollConv::~CgenUnrollConv(){
	se.closelib();
}

void CgenUnrollConv::forward(){
	se.func(input,kernel,&output);
}
