#ifndef RECTANGLE_CLASS_CPP
#define RECTANGLE_CLASS_CPP
#include "Rectangle_Class.h"

template <typename T>
Rectangle_Class<T>::Rectangle_Class () {}
		
template <typename T>
void Rectangle_Class<T>::Init ()
{
	this->Z = 5;
}

template <typename T>
int32_t Rectangle_Class<T>::Draw (b2D rect, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	static b2D r;
	r = rect;
	this->Screen->Trunc(&r);
	uint32_t w0 = r.x + r.w;
	uint32_t h0 = r.y + r.h;
	this->Screen->Line.fBotToTop(r.x, r.y, h0, color);
	this->Screen->Line.fBotToTop(w0, r.y, h0, color);
	this->Screen->Line.fLeftToRight(r.x, r.y, w0, color);
	this->Screen->Line.fLeftToRight(r.x, h0, w0, color);
	
	return 0;
}

template <typename T>
int32_t Rectangle_Class<T>::DrawHatched (b2D rect, ColorTypeDef color, uint8_t hatch)
{
	if (this->Screen->Test()) return -1;
	
	return 0;
}


#endif /*RECTANGLE_CLASS_CPP*/

/*End Of File*/
