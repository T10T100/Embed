#include <stdint.h>
#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"


template <typename T> 
	class Bitmap_Class : public Screen_Obj<T> {
	public:
		Bitmap_Class ();
	  template <typename img_t>
	    int32_t Draw (f2D, img_t *, ColorTypeDef = StdColWhite);
		template <typename img_t>
	    int32_t Tile (f2D, img_t *, ColorTypeDef = StdColWhite);
	    void SetScale (f2D);
		  void SetScale (float, float);
	private:
	  template <typename img_t>
	    int32_t DrawScaled (f2D, img_t *, ColorTypeDef = StdColWhite);
		template <typename img_t>
	    int32_t DrawNoScale (f2D, img_t *, ColorTypeDef = StdColWhite);
	  uint8_t scale_x, scale_y;
};

