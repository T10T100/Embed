#ifndef CIRCLE_CLASS_CPP
#define CIRCLE_CLASS_CPP

#ifdef SOFTWARE_GL

#include "Frame_Class.h"
#include "screen_obj.h"


template <typename T>
class Circle_Class : public Screen_Obj<T> {
	public:
		Circle_Class();
	  int32_t Draw (b2D, float, ColorTypeDef);
	  int32_t Draw (gbasic_t, gbasic_t, float, ColorTypeDef);
	  int32_t DrawFilled (b2D, float, ColorTypeDef);
	  int32_t DrawFilled (gbasic_t, gbasic_t, float, ColorTypeDef);
	  int32_t Round (b2D, float, ColorTypeDef, uint32_t = 2);
	  int32_t Round (gbasic_t, gbasic_t, float, ColorTypeDef, uint32_t = 2);
	  int32_t Arc (b2D, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Arc (gbasic_t, gbasic_t, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Segment (b2D, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Segment (gbasic_t, gbasic_t, float, float, ColorTypeDef, float = PI_const / 16);
	private:
	  int32_t Pixel (uint32_t, uint32_t, ColorTypeDef);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t fBotToTop (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t Sqr (int32_t);
};


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
int32_t Circle_Class<T>::fBotToTop (int32_t x0, int32_t y0, int32_t x, int32_t y, ColorTypeDef color)
{
	uint32_t h = this->H;
	int32_t D = x0 * h + y0;
	int32_t D0 = x * h + D;
	int32_t D1 = -x * h + D;
	y0 = - y;
	y  = + y;
	for (; y > y0; y--) {
      *(this->Frame + y + D0) = color;
		  *(this->Frame + y + D1) = color;
	}
	return 0;		
}

template <typename T>
int32_t Circle_Class<T>::Draw (b2D rect, float R, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	this->Screen->Trunc(&rect);
	int32_t y = (int32_t)R;
	int32_t sR = this->Sqr((int32_t)R);
	int32_t x = 0;
	int32_t Dg = 0;
	int32_t Dd = 0;
	int32_t Dv = 0;
	int32_t sqrx = 0;
	int32_t sqry = 0;
	rect.x += R;
	rect.y += R;
	this->Pixel(rect.x,  y  + rect.y, color);
	this->Pixel(rect.x,  -y  + rect.y, color);
	for(;y >= 0;){
		sqrx = this->Sqr(x + 1) - sR;
		sqry = this->Sqr(y - 1);
		Dg = (sqrx + this->Sqr(y));
		Dd = (sqrx + sqry);
		Dv = (this->Sqr(x) + sqry - sR);
		if(Dd < 0){
			if(Dd > -labs(Dg)){ 	
				  x++;
				  y--;
			}
			else {
			    x++;
			}
		}
		else if(Dd > 0){
			if(Dd < labs(Dv)){
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
		this->Point(rect.x, rect.y, x, y, color);
	}
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::Draw (gbasic_t x0, gbasic_t y0, float R, ColorTypeDef color)
{
	b2D rect = {x0, y0, 0, 0};
	return this->Draw (rect, R, color);
}

template <typename T>
int32_t Circle_Class<T>::DrawFilled (b2D rect, float R, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	this->Screen->Trunc(&rect);
	int32_t y = (int32_t)R;
	int32_t sR = this->Sqr((int32_t)R);
	int32_t x = 0;
	int32_t Dg = 0;
	int32_t Dd = 0;
	int32_t Dv = 0;
	int32_t sqrx = 0;
	int32_t sqry = 0;
	rect.x += R;
	rect.y += R;
	uint32_t tx = 0;
	this->fBotToTop(rect.x, rect.y, x, y, color);
	for(;y >= 0 ;){
		sqrx = this->Sqr(x + 1) - sR;
		sqry = this->Sqr(y - 1);
		Dg = (sqrx + this->Sqr(y));
		Dd = (sqrx + sqry);
		Dv = (this->Sqr(x) + sqry - sR);
		if(Dd < 0){
			if(Dd > -labs(Dg)){
				  x++;
				  y--;
			}
			else {
			    x++;
			}
		}
		else if(Dd > 0) {
			if(Dd < labs(Dv)){
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
		if (tx != x) {
		    this->fBotToTop(rect.x, rect.y, x, y, color);
		} else {}
		tx = x;
	}
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::Round (b2D rect, float R, ColorTypeDef color, uint32_t z)
{
	b2D cut_rect = rect;
	this->Draw(rect, R, color);
	rect.x = rect.x + z;
	rect.y = rect.y + z;
	this->Draw(rect, R - z, color);
	this->Screen->Fill.FillX(cut_rect, color);
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::Round (gbasic_t x0, gbasic_t y0, float R, ColorTypeDef color, uint32_t z)
{
	b2D rect = {x0, y0, 0, 0}, cut_rect = {x0, y0, (gbasic_t)(2 * R), (gbasic_t)(2 * R)};
	this->Draw(rect, R, color);
	rect.x = rect.x + z;
	rect.y = rect.y + z;
	this->Draw(rect, R - z, color);
	this->Screen->Fill.FillX(cut_rect, color);
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::Arc (b2D rect, float R, float A, ColorTypeDef color, float Ai)
{
	return this->Arc(rect.x, rect.y, R, A, color, Ai);
}

template <typename T>
int32_t Circle_Class<T>::Arc (gbasic_t x0, gbasic_t y0, float R, float A, ColorTypeDef color, float Ai)
{
	float x = 0, y = R;
	float px = x0 + x, py = y0 + y;
	int32_t t = (int32_t)abs(floor(A / Ai));
	while (t--) {
		x = (float)x + y * Ai;
	  y = (float)y - x * Ai; 
		this->Screen->Line.DrawDda((gbasic_t)px, (gbasic_t)py, (gbasic_t)x + x0, (gbasic_t)y + y0, color);
		px = x + x0;
		py = y + y0;
	}
	
	return 0;
}

template <typename T>
int32_t Circle_Class<T>::Segment (b2D rect, float R, float A, ColorTypeDef color, float Ai)
{
	return this->Segment(rect.x, rect.y, R, A, color, Ai);
}

template <typename T>
int32_t Circle_Class<T>::Segment (gbasic_t x0, gbasic_t y0, float R, float A, ColorTypeDef color, float Ai)
{
	float x = 0, y = R;
	float px = x0, py = y0;
	int32_t t = (int32_t)abs(floor(A / Ai));
	b2D rect = {x0 - R, y0 - R, 2 * R, 2 * R};
	while (t--) {
		x = (float)x + y * Ai;
	  y = (float)y - x * Ai; 
		this->Screen->Line.DrawDda((gbasic_t)px, (gbasic_t)py, (gbasic_t)x + x0, (gbasic_t)y + y0, color);
		px = x + x0;
		py = y + y0;
	}
	x = 0, y = R - 10.0F;
	px = x0 + x, py = y0 + y;
	t = (int32_t)abs(floor(A / Ai));
	while (t--) {
		x = (float)x + y * Ai;
	  y = (float)y - x * Ai; 
		this->Screen->Line.DrawDda((gbasic_t)px, (gbasic_t)py, (gbasic_t)x + x0, (gbasic_t)y + y0, color);
		px = x + x0;
		py = y + y0;
	}
	this->Screen->Line.DrawDda((gbasic_t)x0, (gbasic_t)y0, (gbasic_t)x + x0, (gbasic_t)y + y0, color);
	this->Screen->Fill.FillX(rect, color);
	return 0;
}
 
template <typename T>
int32_t Circle_Class<T>::DrawFilled (gbasic_t x, gbasic_t y, float R, ColorTypeDef color)
{
	b2D rect = {x, y, 0, 0};
	return this->DrawFilled(rect, R, color);
}
#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*CIRCLE_CLASS_CPP*/


/*End Of File*/
