#ifndef FRAME_CLASS_CPP
#define FRAME_CLASS_CPP

#include "Frame_Class.h"


template <typename T>
Frame2D<T>::Frame2D (){}

template <typename T>
void Frame2D<T>::operator () (b2D rect)
{
	this->Data.Frame = (ColorTypeDef *)(this + 1);	
	this->Data.glo_x = rect.x;
	this->Data.glo_y = rect.y;
	this->Data.W     = rect.w;
	this->Data.H     = rect.h;
	this->PointToFill = StdColBlack;
}

template <typename T>
void Frame2D<T>::operator () (b2D rect, ColorTypeDef *buff)
{
	this->Data.Frame = buff;	
	this->Data.glo_x = rect.x;
	this->Data.glo_y = rect.y;
	this->Data.W     = rect.w;
	this->Data.H     = rect.h;
	this->PointToFill = StdColBlack;
}


template <typename T>
b2D Frame2D<T>::GetRect ()
{
	b2D rect = {this->Data.glo_x, this->Data.glo_y, this->Data.W, this->Data.H};
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
ColorTypeDef *Frame2D<T>::GetBuff (b2D rect)
{
	return (this->Data.Frame + rect.y + rect.x * this->Data.H);
}

template <typename T>
void Frame2D<T>::FillDMA (ColorTypeDef color)
{
	this->PointToFill = color;
	this->DmaTransfer(this->Data.Frame, &this->PointToFill, this->Data.W * this->Data.H);
}




template <typename T>
Frame2DManager<T>::Frame2DManager () {}
	
template <typename T>
void Frame2DManager<T>::operator () ()
{

}

template <typename T>
Frame2D<T> *Frame2DManager<T>::Create (b2D rect)
{
	Frame2D<T> *frame = this->New((rect.h * rect.w) * sizeof(ColorTypeDef));
	*this + frame;
	(*frame)(rect);
	return frame;
}

template <typename T>
Frame2D<T> *Frame2DManager<T>::Access (uint32_t id)
{
	Frame2D<T> *frame = this->Get(id);
	return frame;
}
#endif /*FRAME_CLASS_CPP*/

