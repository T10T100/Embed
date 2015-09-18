#ifndef FRAME_CLASS_H
#define FRAME_CLASS_H

#include "GUI_defs.h"
#include "geometry.h"
#include "memory_template.h"
#include "List.h"

template <typename T>
struct frame_data_t {
	ColorTypeDef *Frame;
	T W, H;
	T glo_x, glo_y;
};



template <typename T>
	class Frame2D : public List_Node<Frame2D<T>, uint8_t>{
	public:
		Frame2D ();
	  void operator () (b2D);
	  void operator () (b2D, ColorTypeDef *);
	  b2D GetRect ();
	  float GetH ();
	  float GetW ();
	  ColorTypeDef *GetBuff ();
	  ColorTypeDef *GetBuff (b2D);
	  void FillDMA (ColorTypeDef = StdColBlack);
	private:
    frame_data_t<T> Data;
	  virtual void DmaTransfer (ColorTypeDef *, ColorTypeDef *, uint32_t);
	  ColorTypeDef PointToFill;
};

template <typename T>
	class Frame2DManager : public List_Iterator<Frame2D<T> > ,
		                     public Allocator<Frame2D<T> >     {
	public:
		Frame2DManager ();
	  void operator () ();
	  Frame2D<T> *Create (b2D);
	  Frame2D<T> *Access (uint32_t);
	private:
};
												 
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
#endif /*FRAME_CLASS_H*/



/*End Of File*/
