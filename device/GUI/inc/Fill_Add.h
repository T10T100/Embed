
#include <stdint.h>
#include "misc/src/graphic.cpp"

template <typename T> 
class ScrFill {
  public:
    ScrFill ();
	  void operator () (T &);
    T *Screen;
    int32_t Fill (ColorTypeDef = StdColBlack);	
	  int32_t Fill (f2D, ColorTypeDef = StdColBlack);
	  int32_t FillX (f2D, ColorTypeDef = StdColBlack);
	  int32_t FillY (f2D, ColorTypeDef = StdColBlack);
	
	protected:
	friend class Screen;
};


