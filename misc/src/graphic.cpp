#ifndef __GRAPHIC
#define __GRAPHIC
#include "graphic.h"


template <typename T>
Frame2D<T>::Frame2D (){}

template <typename T>
void Frame2D<T>::operator () (f2D rect, MemoryAllocator &heap)
{
	if (this->Heap == (MemoryAllocator *)0)
		  this->Heap = &heap;
	this->Data.Frame = (ColorTypeDef *)heap.New((rect.h * rect.w) * sizeof(ColorTypeDef) + 1);	
	this->Data.glo_x = rect.x;
	this->Data.glo_y = rect.y;
	this->Data.W     = rect.w;
	this->Data.H     = rect.h;
	this->PointToFill = StdColBlack;
}

template <typename T>
void Frame2D<T>::Kill ()
{
	this->Heap->Delete(this->Data.Frame);
}

template <typename T>
f2D Frame2D<T>::GetRect ()
{
	f2D rect = {this->Data.glo_x, this->Data.glo_y, this->Data.W, this->Data.H};
	return rect;
}

template <typename T>
float Frame2D<T>::GetH ()
{
	return this->Data.H;
}

template <typename T>
float Frame2D<T>::GetW ()
{
	return this->Data.W;
}

template <typename T>
ColorTypeDef *Frame2D<T>::GetBuff ()
{
	return this->Data.Frame;
}

template <typename T>
void Frame2D<T>::FillDMA (ColorTypeDef color)
{
	this->PointToFill = color;
	this->DmaTransfer(this->Data.Frame, &this->PointToFill, this->Data.W * this->Data.H);
}








#endif

