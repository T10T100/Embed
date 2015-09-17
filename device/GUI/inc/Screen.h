#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "memory_template.h"
#include "device/GUI/src/Frame_Class.cpp"
#include "misc/src/list.cpp"
#include "geometry.h"
#include "locker.h"

#include "affine_tf.h"

#include "device/GUI/src/Screen_Obj.cpp"
#include "device/GUI/src/Fill_Class.cpp"
#include "device/GUI/src/Bitmap_Class.cpp"
#include "device/GUI/src/Circle_Class.cpp"
#include "device/GUI/src/Line_Class.cpp"
#include "device/GUI/src/Rectangle_Class.cpp"
#include "device/GUI/src/Print_Class.cpp"

class Screen : public Locker ,
	           public Coordinates,		  
		       public List_Node <Screen, uint8_t>,
               public Allocator <Screen>				 {
	public:
	  Screen ();
	  void operator () (b2D, Frame2D<gbasic_t> &); 
	  int32_t Refresh ();
	  tTexture *MakeTexture (b2D);
	  tTexture *MakeTexture (gbasic_t, gbasic_t);
	  int32_t   KillTexture (tTexture *);
	  
	  Affine_Body Affine;
	
    Fill_Class       <Screen> Fill;
	  Bitmap_Class     <Screen> Bitmap;
	  Circle_Class     <Screen> Circle;
	  Line_Class       <Screen> Line;
	  Rectangle_Class  <Screen> Rectangle;
	  Print_Class      <Screen> Print;
	  Frame2D<gbasic_t> *GetFrame ();
	private:
	  Frame2D<gbasic_t> *Frame;
	  ColorTypeDef back_color;
	
	  friend class Bitmap_Class     <Screen>;
	  friend class Fill_Class       <Screen>;
	  friend class Circle_Class     <Screen>;
	  friend class Line_Class       <Screen>;
	  friend class Rectangle_Class  <Screen>;
	  friend class Print_Class      <Screen>;
	  friend class Screen_Obj       <Screen>;
};
							 
class ScreenManager : public Locker ,
	                    public List_Iterator<Screen>,
										  public Allocator <Screen>		 {
  public:
		ScreenManager ();
	  void operator () ();
	  Screen *Create (b2D, Frame2D<gbasic_t> *);
	  int32_t Kill (Screen *);
	  int32_t Refresh (uint32_t);
	private:
};



#endif /*SCREEN_H*/




