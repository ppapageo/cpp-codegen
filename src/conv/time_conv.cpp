//Usage ./time_conv <c_in> <rows> <cols> <c_out> <kRows> <kCols> <stride> <pad>
//#include "conv.h"
#include "conv/ConvUtils.h"
#include "conv/VanillaConv.h"
#include "conv/CgenConv.h"
#include "conv/CgenUnrollConv.h"
#include "conv/Im2colConv.h"
int main( int argc, char** argv )
{
	if (argc<=8){
		std::cout<<"Too few arguments"<<"\n";
		std::cout<<"Usage ./time_conv <c_in> <rows> <cols> <c_out> <kRows> <kCols> <stride> <pad>"<<"\n";
		exit(1);
	}
	int in_ch=atoi(argv[1]);
	int in_row=atoi(argv[2]);
	int in_col=atoi(argv[3]);
	int out_ch=atoi(argv[4]);
	int k_row=atoi(argv[5]);
	int k_col=atoi(argv[6]);
	int stride=atoi(argv[7]);
	int pad=0;
	if (atoi(argv[8])==1){
		pad=(k_row-1)/2;
	}
	srand (static_cast <unsigned> (time(0)));

	float* input = populate_rand(in_ch*in_row*in_col, 15.42, 0.42);
	float* kernel = populate_rand(out_ch*in_ch*k_row*k_col, 15.42, 0.42);
	pad_input(in_ch, &in_row, &in_col, pad, &input);	
	VanillaConv vc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	CgenConv cc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	CgenUnrollConv uc(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	Im2colConv ic(out_ch, in_ch, in_row, in_col, k_row, k_col, pad, stride, input, kernel);
	
	auto cr_start = std::chrono::high_resolution_clock::now();
	vc.forward();
	auto cr_end = std::chrono::high_resolution_clock::now();
	std::cout<<"VanillaConv Time(s):\t"<< std::chrono::duration<double>(cr_end-cr_start).count()<<"\n";
	
	cr_start = std::chrono::high_resolution_clock::now();
	cc.forward();
	cr_end = std::chrono::high_resolution_clock::now();
	std::cout<<"CgenConv Time(s):\t"<< std::chrono::duration<double>(cr_end-cr_start).count()<<"\n";
	
	cr_start = std::chrono::high_resolution_clock::now();
	uc.forward();
	cr_end = std::chrono::high_resolution_clock::now();
	std::cout<<"CgenUnrollConv Time(s):\t"<< std::chrono::duration<double>(cr_end-cr_start).count()<<"\n";
	
	cr_start = std::chrono::high_resolution_clock::now();
	ic.forward();
	cr_end = std::chrono::high_resolution_clock::now();
	std::cout<<"Im2colConv Time(s):\t"<< std::chrono::duration<double>(cr_end-cr_start).count()<<"\n";

#ifdef DEBUG
	int size = vc.out_ch*vc.out_col*vc.out_row;
	if(size>9) size = 9;
	for (int i = 0; i < size; i++){
		std::cout<<vc.output[i]<<" : "<<cc.output[i]<<" : "<<uc.output[i]<<" : "<<ic.output[i]<<"\n";
	}
#endif
	delete [] input;
	delete [] kernel;

}
