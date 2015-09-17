#ifndef BITMAP_CLASS_CPP
#define BITMAP_CLASS_CPP

#ifdef SOFTWARE_GL

#include "bitmap_class.h"

template <typename T>
Bitmap_Class<T>::Bitmap_Class ()
{
this->scale_x = 0;
this->scale_y = 0;
}
		
template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::DrawNoScale (f2D rect, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	this->Screen->Normalize(&rect);
  uint32_t __x = rect.x * this->H, xi = 0;
  uint32_t S = image->H * image->W;
  ColorTypeDef target = color;
  for (; xi < image->W; __x += this->H, xi++) {  
    for (uint32_t __y = rect.y, yi = 0; yi < S; __y++, yi += image->W) {
      target = *(image->Image + xi + yi);
			if (target != color)
			  this->Frame[__y + __x] = target;   
		}
	}
	
	return 0;
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::DrawScaled (f2D rect, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	if (!this->scale_x || !this->scale_y) {
		  this->DrawNoScale(rect, image);
	}
	rect.w = image->W * this->scale_x;
	rect.h = image->H * this->scale_y;
	this->Screen->Normalize(&rect);
	
  uint32_t __x = rect.x * this->H;
	uint32_t Hstep = this->H * this->scale_x;	
  uint32_t S = image->H * image->W;
	
  for (uint16_t xi = 0; xi < image->W; __x += Hstep, xi++) { 
	    for (uint32_t __sx = __x; __sx < __x + Hstep; __sx += this->H) {
          for (uint16_t __y = rect.y, yi = 0; yi < S; __y += this->scale_y, yi += image->W) {
			        for (uint16_t __sy = __y; __sy < this->scale_y + __y; __sy++) {
			                this->Frame[__sy + __sx] = *(image->Image + xi + yi);
							}
					}
			}
	}		
	return 0;
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Draw (f2D rect, img_t *image, ColorTypeDef color)
{
	return this->DrawScaled (rect, image, color);
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Tile (f2D rect, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	
	return 0;
}

template <typename T>
void Bitmap_Class<T>::SetScale (f2D rect)
{
  this->scale_x = (uint8_t)rect.x;
	this->scale_y = (uint8_t)rect.y;
}	

template <typename T>
void Bitmap_Class<T>::SetScale (float x, float y)
{
  this->scale_x = (uint8_t)x;
	this->scale_y = (uint8_t)y;
}	

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*BITMAP_CLASS_CPP*/

