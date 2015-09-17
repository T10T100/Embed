#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"

#ifndef GUI_FILL_TRIG_JITTER
#define GUI_FILL_TRIG_JITTER 3
#endif

template <typename T> 
class Fill_Class : public Screen_Obj<T> {
  public:
    Fill_Class ();
    int32_t Fill (ColorTypeDef = StdColBlack);	
	  int32_t Fill (b2D, ColorTypeDef = StdColBlack);
	  int32_t Fill (gbasic_t, gbasic_t, gbasic_t, gbasic_t, ColorTypeDef = StdColBlack);
	  int32_t FillX (b2D, ColorTypeDef = StdColBlack, uint8_t = GUI_FILL_TRIG_JITTER);
	  int32_t FillY (b2D, ColorTypeDef = StdColBlack);
	protected:
	  friend class Screen; 
};


