#ifndef FILL_CLASS_CPP
#define FILL_CLASS_CPP

#ifdef SOFTWARE_GL

#include "Fill_Class.h"

template <typename T>
Fill_Class<T>::Fill_Class (){}

template <typename T>
int32_t Fill_Class<T>::Fill (ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	
	register int32_t x = this->Screen->X0;
	register uint32_t y = this->Screen->Y0;
	register uint32_t D = this->H * x;
	
  for (int32_t __x = D + this->H * this->Screen->W; __x > D; __x -= this->H)  
    for (uint32_t __y = this->Screen->H + y - 1; __y > y; __y--)
        this->Frame[(uint32_t)__y + (uint32_t)__x] = color;
	return 0;
}



template <typename T>
int32_t Fill_Class<T>::Fill (f2D __rect, ColorTypeDef color)
{
	static f2D rect;
	rect = __rect;
	if (this->Screen->Test()) return -1;
	this->Screen->Normalize(&rect);
	
	register int32_t x = rect.x;
	register uint32_t y = rect.y;
	register uint32_t D = this->H * x;
	
  for (int32_t __x = D + this->H * rect.w; __x > D; __x -= this->H)  
    for (uint32_t __y = rect.h + y - 1; __y > y; __y--)
        this->Frame[(uint32_t)__y + (uint32_t)__x] = color;
	return 0;
}

template <typename T>
int32_t Fill_Class<T>::FillX (f2D rect, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	ColorTypeDef *ftarget = this->Screen->Frame->GetBuff();
	ColorTypeDef *target = (ColorTypeDef *)0;
	this->Screen->Normalize(&rect);
	
	register uint32_t H = this->Screen->Frame->GetRect().h;
	register uint32_t x0 = (uint32_t)rect.x * H;
	register uint32_t y0 = (uint32_t)rect.y;
	register uint32_t h = (uint32_t)rect.h * H;
	register uint32_t w = (uint32_t)rect.w;
	uint32_t Key = 0;
	
    for (uint32_t __y = y0 + w; __y > y0; __y--) {  
       for (uint32_t __x = x0 + h; __x > x0; __x -= H) {
				target = ftarget + __y + __x - H;
				if (*(target + H) == color && *target != color)
					 Key ^= 1;
			  if (Key)*(target + H) = color;
			
			}
			Key = 0;
		}
	return 0;	
}

template <typename T>
int32_t Fill_Class<T>::FillY (f2D rect, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	ColorTypeDef *ftarget = this->Screen->Frame->GetBuff();
	ColorTypeDef *target = (ColorTypeDef *)0;
	this->Screen->Normalize(&rect);
	
	register uint32_t H = this->Screen->Frame->GetRect().h;
	register uint32_t x0 = rect.x * H;
	register uint32_t y0 = rect.y;
	register uint32_t h = rect.h * H;
	register uint32_t w = rect.w;
	uint32_t Key = 0;
	
    for (uint32_t __x = x0 + h; __x > x0; __x -= H) {  
      for (uint32_t __y = y0 + w; __y > y0; __y--) {
				target = ftarget + __y + __x - 1;
				if (*(target + 1) == color && *target != color)
					 Key ^= 1;
			  if (Key)*(target + 1) = color;
			}
			Key = 0;
		}
	return 0;	
}

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/


#endif /*FILL_CLASS_CPP*/

