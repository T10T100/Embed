#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"

template <typename T>
class Line_Class : public Screen_Obj<T> {
	public:
	  Line_Class ();
	  int32_t DrawDda (float, float, float, float, ColorTypeDef);
	  int32_t DrawVertical (f2D rect, ColorTypeDef);
	  int32_t DrawHorizontal (f2D rect, ColorTypeDef);
	  int32_t DrawDdaBold (float, float, float, float, ColorTypeDef);
	  int32_t DrawVerticalBold (f2D rect, ColorTypeDef);
	  int32_t DrawHorizontalBold (f2D rect, ColorTypeDef);
	  int32_t DrawVector (float, float, float, float, ColorTypeDef);
	  int32_t DrawVectorBold (float, float, float, float, ColorTypeDef);
	private:
	  uint8_t Z;
	  int32_t Pixel (uint32_t, uint32_t, ColorTypeDef);
	  int32_t fVertical (uint32_t, uint32_t, uint32_t, ColorTypeDef);
	  int32_t fHorizontal (uint32_t, uint32_t, uint32_t, ColorTypeDef);
};

/*End Of File*/

