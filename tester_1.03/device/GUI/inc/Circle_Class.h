#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"


template <typename T>
class Circle_Class : public Screen_Obj<T> {
	public:
		Circle_Class();
	  int32_t Draw (f2D, float, ColorTypeDef);
	  int32_t DrawFilled (f2D, float, ColorTypeDef);
	private:
	  int32_t Pixel (uint32_t, uint32_t, ColorTypeDef);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, ColorTypeDef);
	  int32_t Sqr (int32_t);
};

/*End Of File*/
