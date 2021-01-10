#include "conv/VanillaConv.h"
void VanillaConv::forward(){
	int i, j,ki,ko,ii,jj,m, n;
	int out_addr, in_addr, kern_addr;
	for (ki=0; ki<this->in_ch; ki++){ //Input Channel
#pragma omp parallel for private(ko,i,j,m,n,ii,jj,out_addr,in_addr,kern_addr)
		for (ko=0; ko<this->out_ch; ko++){ //Output Channel
			for(i=0; i < this->out_row; i++){ // Input row
				for(j=0; j < this->out_col; j++){ // Input columns
					for(m=0; m < this->k_row; m++){ // Kernel rows
						for(n=0; n < this->k_col; n++){ // Kernel columns
							jj = stride*j + n;
							ii = stride*i + m;
							out_addr= (ko*(this->out_row)+i)*(this->out_col)+j;
							in_addr=(ki*this->in_row+ii)*this->in_col+jj;
							kern_addr=((ko*this->in_ch+ki)*this->k_row+m)*this->k_col+n;

							output[out_addr]+=input[in_addr] * kernel[kern_addr];
						}
					}
				}
			}
		}
	}
}
