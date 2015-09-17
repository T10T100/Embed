#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"


template <typename T>
class Circle_Class : public Screen_Obj<T> {
	public:
		Circle_Class();
	  int32_t Draw (b2D, float, ColorTypeDef);
	  int32_t Draw (gbasic_t, gbasic_t, float, ColorTypeDef);
	  int32_t DrawFilled (b2D, float, ColorTypeDef);
	  int32_t DrawFilled (gbasic_t, gbasic_t, float, ColorTypeDef);
	  int32_t Round (b2D, float, ColorTypeDef, uint32_t = 2);
	  int32_t Round (gbasic_t, gbasic_t, float, ColorTypeDef, uint32_t = 2);
	  int32_t Arc (b2D, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Arc (gbasic_t, gbasic_t, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Segment (b2D, float, float, ColorTypeDef, float = PI_const / 16);
	  int32_t Segment (gbasic_t, gbasic_t, float, float, ColorTypeDef, float = PI_const / 16);
	private:
	  int32_t Pixel (uint32_t, uint32_t, ColorTypeDef);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t fBotToTop (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t Sqr (int32_t);
};

/*End Of File*/
