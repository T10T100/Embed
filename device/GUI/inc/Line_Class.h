#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"
#include "device/GUI/src/Rectangle_Class.cpp"

template <typename T>
class Line_Class : public Screen_Obj<T> {
	public:
	  Line_Class ();
	  void Init ();
	  int32_t DrawDda (float, float, float, float, ColorTypeDef);
	  int32_t DrawVertical (b2D rect, ColorTypeDef);
	  int32_t DrawHorizontal (b2D rect, ColorTypeDef);
	  int32_t DrawDdaBold (float, float, float, float, ColorTypeDef);
	  int32_t DrawVerticalBold (b2D rect, ColorTypeDef);
	  int32_t DrawHorizontalBold (b2D rect, ColorTypeDef);
	  int32_t DrawVector (float, float, float, float, ColorTypeDef);
	  int32_t DrawVectorBold (float, float, float, float, ColorTypeDef);
	private:
	  uint8_t Z;
	  int32_t Pixel (int32_t, int32_t, ColorTypeDef);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t fBotToTop (uint32_t, uint32_t, uint32_t, ColorTypeDef, uint8_t = 1);
	  int32_t fLeftToRight (uint32_t, uint32_t, uint32_t, ColorTypeDef, uint8_t = 1);
	  int8_t log2LaySize;
	
	  friend class Rectangle_Class<T>;
};

/*End Of File*/

