#include <stdint.h>
#include "String_Defs.h"
#include "device/GUI/src/Frame_Class.cpp"
#include "device/GUI/src/Screen_obj.cpp"
#include "misc/src/List.cpp"

enum FormatEnum{
	StrFormatTabOnly      = 0,
	StrFormatSpaceOnly    = 1,
	StrFormatTimeOnly     = 2,
};

template <typename T>
class Print_Class : public Screen_Obj<T> ,
	                  public List_Node<tFont, uint8_t>{
  public:
	  Print_Class ();
	  void Init ();
	  void UseFont (const tFont *Font);
	  b2D Char (b2D, char, ColorTypeDef = StdColBlack);
	  b2D Char (char, ColorTypeDef);
	template <typename char_t>
	  b2D String (b2D, char_t *, gbasic_t, ColorTypeDef = StdColBlack);
	template <typename char_t>
	  b2D fString (char_t *, gbasic_t, ColorTypeDef = StdColBlack);
	template <typename char_t>
	  b2D String (char_t *, gbasic_t, ColorTypeDef = StdColBlack);
	
	
	  b2D String (b2D, __TEXT , ColorTypeDef = StdColBlack);
	  b2D String (__TEXT , ColorTypeDef = StdColBlack);
  private:
		int32_t GetCharCode (char);
		b2D Caret;
	  gbasic_t EofX, EofY;
	  gbasic_t FontW, FontH;
	  const tFont *Font;
	  uint8_t Format;
};

