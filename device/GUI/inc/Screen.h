#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "memory_template.h"
#include "Frame_Class.h"
#include "list.h"
#include "list_template.h"
#include "geometry.h"
#include "locker.h"

#include "affine_tf.h"

#include "screen_obj.h"
#include "fill_class.h"
#include "bitmap_class.h"
#include "circle_class.h"
#include "line_class.h"
#include "rectangle_class.h"
#include "print_class.h"

class Screen : public Locker ,
	             public Coordinates,
               public Allocator <Screen>				  {
	public:
	  Screen ();
	  void operator () (b2D, Frame2D<gbasic_t> &); 
	  int32_t Refresh ();
	  tTexture *MakeTexture (b2D);
	  tTexture *MakeTexture (gbasic_t, gbasic_t);
	  int32_t   KillTexture (tTexture *);
    
    int32_t Pixel (gbasic_t, gbasic_t, ColorTypeDef);
    ColorTypeDef Pixel (gbasic_t, gbasic_t);
	  ColorTypeDef PixelsAround (gbasic_t, gbasic_t);
	  
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
    ColorTypeDef *frame_;
    ColorTypeDef h_;
	
	  friend class Bitmap_Class     <Screen>;
	  friend class Fill_Class       <Screen>;
	  friend class Circle_Class     <Screen>;
	  friend class Line_Class       <Screen>;
	  friend class Rectangle_Class  <Screen>;
	  friend class Print_Class      <Screen>;
	  friend class Screen_Obj       <Screen>;
};
							 
class ScreenManager : public Locker ,
										  public Allocator <Screen>		 {
  public:
		ScreenManager ();
	  void operator () ();
	  Screen *Create (b2D, Frame2D<gbasic_t> *);
	  int32_t Kill (Screen *);
	  int32_t Refresh (uint32_t);
	private:
		Iterator<Screen, uint8_t>  iterator_;
	  List_Order<Screen, uint8_t> list_;
};



#endif /*SCREEN_H*/




