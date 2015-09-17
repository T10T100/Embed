#ifndef LINE_CLASS_CPP
#define LINE_CLASS_CPP

#ifdef SOFTWARE_GL

#include "Line_Class.h"

template <typename T>
Line_Class<T>::Line_Class()
{
this->Z = 5;
}
		
template <typename T>
int32_t Line_Class<T>::Pixel (uint32_t x, uint32_t y, ColorTypeDef color)
{
  *(this->Frame + y + x * this->H) = color;
	return 0;
}

template <typename T>
int32_t Line_Class<T>::DrawDda (float x0, float y0, float x, float y, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	this->Screen->Normalize(x0, y0, x, y);
	int32_t Xo = (int32_t)x0;
  int32_t Yo = (int32_t)y0;
  int32_t X  =  (int32_t)x;
  int32_t Y  =  (int32_t)y;
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
int32_t Line_Class<T>::DrawDdaBold (float x0, float y0, float x, float y, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	
	this->Screen->Normalize(x0, y0, x, y);
	int32_t Xo =  (int32_t)x0;
  int32_t Yo =  (int32_t)y0;
  int32_t X  =  (int32_t)x;
  int32_t Y  =  (int32_t)y;
	int32_t dx = labs(X - Xo);
  int32_t dy = labs(Y - Yo);
  int32_t sx = X >= Xo ? 1 : -1;
  int32_t sy = Y >= Yo ? 1 : -1;
		if(dy <= dx)                    
		{
			int32_t d =  (dy<<1)-dx;                     
			int32_t d1 = dy<<1;
			int32_t d2 = (dy-dx)<<1;
			this->fVertical(Xo, Yo, Yo + 5, color);            
			for(int32_t _x = Xo+sx, _y = Yo, i = 1; i<=dx; i++, _x+=sx) 
			{
				if(d>0)            
				{
					d +=d2;
					y +=sy;
				}
				else d +=d1;
				this->fVertical(x, _y, _y + 5, color);            
			}
		}
		else
		{
			int32_t d = (dx<<1)-dy;
			int32_t d1 = dx<<1;
			int32_t d2 = (dx-dy)<<1;
			this->fHorizontal(Xo, Yo, Xo + 5, color);
			for(int32_t _x = Xo, _y = Yo+sy, i = 1; i<=dy;i++, _y+=sy)
			{
				if(d>0)
				{
					d+=d2;
					_x+=sx;
				}
				else d+=d1;
				this->fHorizontal(_x, _y, _x + 5, color);
			}
		}  
  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawVector (float x0, float y0, float R, float A, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	float x, y;
  x = x0 + R * cos(A);
  y = y0 + R * sin(A);
	return this->DrawDda(x0, y0, x, y, color);
}

template <typename T>
int32_t Line_Class<T>::DrawVectorBold (float x0, float y0, float R, float A, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;
	float x, y;
  x = x0 + R * cos(A);
  y = y0 + R * sin(A);	
	return this->DrawDdaBold(x0, y0, x, y, color);	
}

template <typename T>
int32_t Line_Class<T>::DrawVertical (f2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawHorizontal (f2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::DrawHorizontalBold (f2D rect, ColorTypeDef color)
{
  if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename T>
int32_t Line_Class<T>::fVertical (uint32_t x0, uint32_t y0, uint32_t y, ColorTypeDef color)
{
  uint32_t D = this->H * x0;
	uint32_t Highest = 0, Lowest = 0;
	y0 += D;
	y += D;
	if (y >= y0) {
		Highest = y;
		Lowest = y0;
	}
	else {
		Highest = y0;
		Lowest = y;
	}
    for (; Highest > Lowest; Highest--)
        *(this->Frame + Highest) = color;
	return 0;		
}

template <typename T>
int32_t Line_Class<T>::fHorizontal (uint32_t x0, uint32_t y0, uint32_t x, ColorTypeDef color)
{
	x0 = x0 * this->H + y0;
	x = x * this->H + y0;
	uint32_t Highest = 0, Lowest = 0;
	if (x >= x0) {
		Highest = x;
		Lowest = x0;
	}
	else {
		Highest = x0;
		Lowest = x;
	}
  for (; Highest > Lowest; Highest -= this->H)
      *(this->Frame + Highest) = color;
	return 0;		
}

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*LINE_CLASS_CPP*/

/*End Of File*/

