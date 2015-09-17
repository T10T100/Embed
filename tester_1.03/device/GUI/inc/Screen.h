#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "memory_alloc.h"
#include "Screen_Driver.h"
#include "device/GUI/src/Frame_Class.cpp"
#include "misc/src/list.cpp"
#include "geometry.h"
#include "locker.h"

#include "device/GUI/src/Screen_Obj.cpp"
#include "device/GUI/src/Fill_Class.cpp"
#include "device/GUI/src/Bitmap_Class.cpp"
#include "device/GUI/src/Circle_Class.cpp"
#include "device/GUI/src/Line_Class.cpp"

class Screen : public Locker ,
	             public Coordinates,		  
							 public List_Node <Screen, uint8_t> {
	public:
		Screen ();
	  void operator () (f2D, Frame2D<resolution_t> &); 
	  int32_t Refresh ();
    Fill_Class       <Screen> Fill;
	  Bitmap_Class     <Screen> Bitmap;
	  Circle_Class     <Screen> Circle;
	  Line_Class       <Screen> Line;
	private:
		Frame2D<resolution_t> *Frame;
	  ColorTypeDef back_color;
	  int32_t Normalize (f2D *);
	  int32_t Normalize (float, float, float, float);
	
	  friend class Bitmap_Class     <Screen>;
	  friend class Fill_Class       <Screen>;
	  friend class Circle_Class     <Screen>;
	  friend class Line_Class       <Screen>;
	  friend class Screen_Obj       <Screen>;
};
							 
class ScreenManager : public Locker ,
	                    public List_Iterator<Screen>{
  public:
		ScreenManager ();
	  void operator () (MemoryAllocator &);
	  Screen *Create ();
	  int32_t Kill (Screen *);
	  int32_t Refresh (uint32_t);
	private:
		MemoryAllocator *Heap;
	  
	
};



#endif /*SCREEN_H*/




