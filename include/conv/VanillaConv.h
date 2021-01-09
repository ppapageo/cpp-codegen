#ifndef VANILLACONV_H
#define VANILLACONV_H
#include "conv/BaseConv.h"

class VanillaConv: public BaseConv
{
	public:
	void forward();
	using BaseConv::BaseConv;
};
#endif
