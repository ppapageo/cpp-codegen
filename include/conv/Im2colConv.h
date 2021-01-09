#ifndef IM2COLCONV_H
#define IM2COLCONV_H
#include "conv/BaseConv.h"

class Im2colConv: public BaseConv
{
	public:
	using BaseConv::BaseConv;
	void forward();
};
#endif
