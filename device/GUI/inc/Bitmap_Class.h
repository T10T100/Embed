#include <stdint.h>
#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"
#include "device/GUI/src/Print_Class.cpp"


template <typename T> 
	class Bitmap_Class : public Screen_Obj<T> {
	public:
		Bitmap_Class ();
	  template <typename img_t>
	    int32_t Draw (b2D, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t>
			int32_t Draw (gbasic_t, gbasic_t, img_t *, ColorTypeDef = StdColBlack);
		
		
		template <typename img_d, typename img_t>
	    int32_t Copy (b2D, img_d *, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_d, typename img_t>
	    int32_t Copy (gbasic_t, gbasic_t, img_d *, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_d, typename img_t>
	    int32_t Copy (img_d *, img_t *, ColorTypeDef = StdColBlack);
		
		template <typename img_t, typename img_d>
	    img_d *Rotate (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d *Rotate90 (img_d *, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d *Rotate180 (img_d *, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d *Rotate270 (img_d *, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d *Rotate0 (img_d *, img_t *, ColorTypeDef = StdColBlack);
		
		template <typename img_t, typename img_d>
	    img_d  *FlipVertical (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *FlipHorizontal (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		
		template <typename img_t, typename img_d>
	    img_d  *ShrinkX (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *ShrinkY (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *ExpandX (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *ExpandY (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *ResizeX (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *ResizeY (img_d *, img_t *, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *Resize (img_d *, img_t *, float, float, ColorTypeDef = StdColBlack);
		template <typename img_t, typename img_d>
	    img_d  *Resize (b2D, img_d *, img_t *, ColorTypeDef = StdColBlack);
		
		template <typename img_t>
	    int32_t Tile (b2D, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t>
		  int32_t TileLarge (b2D, img_t *, ColorTypeDef = StdColBlack);
		
		
		template <typename img_t>
		  int32_t Fill (img_t *, ColorTypeDef = StdColBlack);
		
		  int32_t NewBitmapOpen (tTexture &);
		  int32_t NewBitmapClose ();
	    void SetScale (b2D);
		  void SetScale (float, float);
		  void setBlendLevel (uint8_t = 0);
	private:
	  	
	
	  template <typename img_t>
	    int32_t DrawScaled (b2D, img_t *, ColorTypeDef = StdColBlack);
		template <typename img_t>
	    int32_t DrawNoScale (b2D, img_t *, ColorTypeDef = StdColBlack);
		
		template <typename dest, typename src>
	    dest  *ShiftRight ( dest *, src *, uint32_t, float, ColorTypeDef = StdColBlack);
		template <typename  dest, typename src>
	    dest  *ShiftLeft ( dest *, src *, uint32_t, float, ColorTypeDef = StdColBlack);
		template <typename  dest, typename src>
	    dest  *ShiftUp ( dest *, src *, uint32_t, float, ColorTypeDef = StdColBlack);
		template <typename  dest, typename src>
	    dest  *ShiftDown ( dest *, src *, uint32_t, float, ColorTypeDef = StdColBlack);
	  
	  uint8_t scale_x, scale_y;
		b2D TempFrameDataRect;
		Frame2D<gbasic_t> *TempFrameDataPackP;
		uint8_t BlendLevel;
		
		
	friend class Print_Class<T>;
};

