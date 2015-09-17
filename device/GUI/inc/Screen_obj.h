#include <stdint.h>
#include "device/GUI/src/Frame_Class.cpp"

template <typename T>
class Screen_Obj {
	public:
		Screen_Obj ();
	  void operator () (T &);
	protected:
		T *Screen;
	  ColorTypeDef *Frame;
	  uint32_t H;
};

/*End Of File*/
