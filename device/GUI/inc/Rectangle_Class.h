#include <stdint.h>
#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"

template <typename T> 
class Rectangle_Class   : public Screen_Obj<T> {
	public:
		Rectangle_Class ();
	  void Init ();
	  int32_t Draw (b2D, ColorTypeDef);
	  int32_t DrawHatched (b2D, ColorTypeDef, uint8_t);
	private:
		uint8_t Z;
	
};

