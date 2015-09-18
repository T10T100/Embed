#ifndef LINE_CLASS_CPP
#define LINE_CLASS_CPP

#ifdef SOFTWARE_GL

#include "frame_class.h"
#include "screen_obj.h"
#include "rectangle_class.h"

template <typename T>
class Line_Class : public Screen_Obj<T> {
	public:
	  Line_Class ();
	  void Init ();
	  int32_t DrawDda (float, float, float, float, ColorTypeDef);
	  int32_t DrawVertical (b2D rect, ColorTypeDef);
	  int32_t DrawHorizontal (b2D rect, ColorTypeDef);
	  int32_t DrawDdaBold (float, float, float, float, ColorTypeDef);
	  int32_t DrawVerticalBold (b2D rect, ColorTypeDef);
	  int32_t DrawHorizontalBold (b2D rect, ColorTypeDef);
	  int32_t DrawVector (float, float, float, float, ColorTypeDef);
	  int32_t DrawVectorBold (float, float, float, float, ColorTypeDef);
	private:
	  uint8_t Z;
	  int32_t Pixel (int32_t, int32_t, ColorTypeDef);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t fBotToTop (uint32_t, uint32_t, uint32_t, ColorTypeDef, uint8_t = 1);
	  int32_t fLeftToRight (uint32_t, uint32_t, uint32_t, ColorTypeDef, uint8_t = 1);
	  int8_t log2LaySize;
	
	  friend class Rectangle_Class<T>;
};

template <typename T>
Line_Class<T>::Line_Class()
{

}

template <typename T>
void Line_Class<T>::Init ()
{
	this->Z = 5;
	uint32_t h = this->H;
	while ((h >> (this->log2LaySize++))){} 
}
		
template <typename T>
int32_t Line_Class<T>::Pixel (int32_t x, int32_t y, ColorTypeDef color)
{
  *(this->Frame + y + x * this->H) = color;
	return 0;
}

template <typename T>
int32_t Line_Class<T>::DrawDda (float xt0, float yt0, float xt, float yt, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	b2D rect = this->Screen->TruncLine(xt0, yt0, xt, yt);
	int32_t Xo = rect.x;
  int32_t Yo = rect.y;
  int32_t X  =  rect.w;
  int32_t Y  =  rect.h;
	int32_t dx = labs(X - Xo);
  int32_t dy = labs(Y - Yo);
  int32_t sx = X >= Xo ? 1 : -1;
  int32_t sy = Y >= Yo ? 1 : -1;
		if(dy <= dx)                    
		{
			int32_t d =  (dy<<1)-dx;                     
			int32_t d1 = dy<<1;
			int32_t d2 = (dy-dx)<<1;
			this->Pixel(Xo, Yo, color);            
			for(int32_t x = Xo+sx, y = Yo, i = 1; i<=dx; i++, x+=sx) 
			{
				if(d>0)            
				{
					d +=d2;
					y +=sy;
				}
				else d +=d1;
				this->Pixel(x, y,color);            
			}
		}
		else
		{
			int32_t d = (dx<<1)-dy;
			int32_t d1 = dx<<1;
			int32_t d2 = (dx-dy)<<1;
			this->Pixel(Xo, Yo,  color);
			for(int32_t x = Xo,y = Yo+sy,i = 1;i<=dy;i++,y+=sy)
			{
				if(d>0)
				{
					d+=d2;
					x+=sx;
				}
				else d+=d1;
				this->Pixel(x, y, color);
			}
		}  
  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawDdaBold (float xt0, float yt0, float xt, float yt, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	if (this->Z == 0) this->Z = 2;
	b2D rect = this->Screen->TruncLine(xt0, yt0, xt, yt);
	int32_t Xo = rect.x;
  int32_t Yo = rect.y;
  int32_t X  =  rect.w;
  int32_t Y  =  rect.h;
	int32_t dx = labs(X - Xo);
  int32_t dy = labs(Y - Yo);
  int32_t sx = X >= Xo ? this->Z : -this->Z;
  int32_t sy = Y >= Yo ? this->Z : -this->Z;
		if(dy <= dx)                    
		{
			int32_t d =  (dy<<1)-dx;                     
			int32_t d1 = dy<<1;
			int32_t d2 = (dy-dx)<<1;           
			for(int32_t x = Xo+sx, y = Yo, i = 1; i<=dx/this->Z; i++, x+=sx) 
			{
				if(d>0)            
				{
					d +=d2;
					y +=sy;
				}
				else {
					  d +=d1;
				}
				this->fBotToTop(x, y, y + this->Z, color, this->Z);           
			}
		}
		else
		{
			int32_t d = (dx<<1)-dy;
			int32_t d1 = dx<<1;
			int32_t d2 = (dx-dy)<<1;
			for(int32_t x = Xo,y = Yo+sy,i = 1;i<=dy/this->Z;i++,y+=sy)
			{
				if(d>0)
				{
					d+=d2;
					x+=sx;
				}
				else {
					  d+=d1;
				}
				this->fLeftToRight(x, y, x + this->Z, color, this->Z);
			}
		}  
  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawVector (float x0, float y0, float R, float A, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	float x, y;
  x = x0 + R * sin(A);
  y = y0 + R * cos(A);
	return this->DrawDda(x0, y0, x, y, color);
}

template <typename T>
int32_t Line_Class<T>::DrawVectorBold (float x0, float y0, float R, float A, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	float x, y;
  x = x0 + R * sin(A);
  y = y0 + R * cos(A);	
	return this->DrawDdaBold(x0, y0, x, y, color);	
}

template <typename T>
int32_t Line_Class<T>::DrawVertical (b2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawHorizontal (b2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawHorizontalBold (b2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::fBotToTop (uint32_t x0, uint32_t y0, uint32_t y, ColorTypeDef color, uint8_t z)
{
	uint32_t h = this->H;
	uint32_t D = x0 * h;
	
	y0 += D;
	y += D;
	for (; y > y0; y--) {
	    for (int32_t tz = z * h; tz > 0; tz -= h) {
          *(this->Frame + y + tz) = color;
			}
	}
	return 0;		
}

template <typename T>
int32_t Line_Class<T>::fLeftToRight (uint32_t x0, uint32_t y0, uint32_t x, ColorTypeDef color,  uint8_t z)
{
	uint32_t h0 = this->H;
	x0 = x0 * h0 + y0;
	x = x * h0 + y0;
	
  for (; x > x0; x -= h0) {
	    for (uint32_t tz = z; tz > 0; tz--) {
          *(this->Frame + x + tz) = color;
			}
	}
	return 0;		
}

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*LINE_CLASS_CPP*/


/*End Of File*/

