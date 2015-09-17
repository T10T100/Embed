#ifndef SCREEN_OBJ_CPP
#define SCREEN_OBJ_CPP
#include "Screen_obj.h"

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
