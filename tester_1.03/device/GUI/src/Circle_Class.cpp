#ifndef CIRCLE_CLASS_CPP
#define CIRCLE_CLASS_CPP

#ifdef SOFTWARE_GL

#include "Circle_Class.h"

template <typename T>
Circle_Class<T>::Circle_Class (){}

template <typename T>
int32_t Circle_Class<T>::Sqr (int32_t val)
{
  return val * val;
}

template <typename T>
int32_t Circle_Class<T>::Pixel (uint32_t x, uint32_t y, ColorTypeDef color)
{
  *(this->Frame + y + x * this->H) = color;
	return 0;
}
template <typename T>
int32_t Circle_Class<T>::Point (int32_t x0, int32_t y0, int32_t x, int32_t y, ColorTypeDef color)
{
	int32_t h0 = (x + x0) * this->H + y0;
	int32_t h1 = (-x + x0) * this->H + y0;
  *(this->Frame + y + h0) = color;
	*(this->Frame - y + h1) = color;
	*(this->Frame - y + h0) = color;
	*(this->Frame + y + h1) = color;
	return 0;
}
template <typename T>
int32_t Circle_Class<T>::Draw (f2D rect, float R, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	this->Screen->Normalize(&rect);
	int32_t y = (int32_t)R;
	int32_t sR = this->Sqr((int32_t)R);
	int32_t x = 0;
	int32_t Dg = 0;
	int32_t Dd = 0;
	int32_t Dv = 0;
	int32_t sqrx = 0;
	int32_t sqry = 0;
	rect.x += R / 2;
	rect.y += R / 2;
	this->Pixel((int32_t)rect.x,  y  + (int32_t)rect.y, color);
	this->Pixel((int32_t)rect.x,  -y  + (int32_t)rect.y, color);
	for(;y >= 0 || x < (int32_t)R;){
		sqrx = this->Sqr(x + 1) - sR;
		sqry = this->Sqr(y - 1);
		Dg = (sqrx + this->Sqr(y));
		Dd = (sqrx + sqry);
		Dv = (this->Sqr(x) + sqry - sR);
		if(Dd < 0){
			if(labs(Dd) < labs(Dg)){
				  x++;
				  y--;
			}
			else {
			    x++;
			}
		}
		else if(Dd > 0){
			if(labs(Dd) < labs(Dv)){
				  y--;
				  x++;
			}
			else {
			    y--;
			}
		}
		else {
			  y--;
			  x++;
		}
		this->Point((int32_t)rect.x, (int32_t)rect.y, x, y, color);
	}
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::DrawFilled (f2D rect, float R, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	this->Screen->Normalize(&rect);
	
	return 0;
}

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*CIRCLE_CLASS_CPP*/


/*End Of File*/
