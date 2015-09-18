#ifndef SCREEN_OBJ_CPP
#define SCREEN_OBJ_CPP

#include <stdint.h>
#include "frame_class.h"

template <typename T>
class Screen_Obj {
	public:
		Screen_Obj ();
	  void operator () (T &);
	protected:
		T *Screen;
	  ColorTypeDef *Frame;
	  uint32_t H;
};


template <typename T>
Screen_Obj<T>::Screen_Obj () {}
		
template <typename T>
void Screen_Obj<T>::operator () (T &screen)
{
	this->Screen = &screen;
	uint32_t h = (uint32_t)this->Screen->Frame->GetH();
	this->H = h;
	this->Frame = this->Screen->Frame->GetBuff();
}


#endif /*SCREEN_OBJ_CPP*/

/*End Of File*/
