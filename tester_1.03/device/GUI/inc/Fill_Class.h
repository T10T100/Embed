#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"


template <typename T> 
class Fill_Class : public Screen_Obj<T> {
  public:
    Fill_Class ();
    int32_t Fill (ColorTypeDef = StdColBlack);	
	  int32_t Fill (f2D, ColorTypeDef = StdColBlack);
	  int32_t FillX (f2D, ColorTypeDef = StdColBlack);
	  int32_t FillY (f2D, ColorTypeDef = StdColBlack);
	protected:
	  friend class Screen;
};


