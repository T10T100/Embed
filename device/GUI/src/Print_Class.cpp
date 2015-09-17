#ifndef PRINT_CLASS_CPP
#define PRINT_CLASS_CPP
#include "Print_Class.h"

template <typename T>
Print_Class<T>::Print_Class() {}
	
template <typename T>
void Print_Class<T>::Init ()
{
	this->EofX = this->Screen->GetRect().w;
	this->EofY = this->Screen->GetRect().h;
  this->Font = (tFont *)0;	
	this->Format = 0;
}	

template <typename T>
void Print_Class<T>::UseFont (const tFont *font)
{
  this->Font = font;
	this->FontW = font->W;
	this->FontH = font->H;
}	

template <typename T>
int32_t Print_Class<T>::GetCharCode (char symbol)
{
  if (this->Font == (tFont *)0) return -1;
  uint32_t code = 0;
  uint32_t quantity = this->Font->Quantity;
  while ((code != symbol) && (quantity--))
        code = this->Font->CharArray[quantity].Code;
  return quantity;  
}	

template <typename T>
b2D Print_Class<T>::Char(b2D rect, char code, ColorTypeDef color)
{
  if (this->Font == (tFont *)0) return rect;
	
  code = this->GetCharCode(code);
  const tImage *Img = this->Font->CharArray[code].Image;
  this->Screen->Bitmap.Draw(rect, Img, StdColWhite);
	this->Caret.x = Img->W + rect.x;
	this->Caret.w -=Img->W;
  return this->Caret;
}

template <typename T>
b2D Print_Class<T>::Char(char code, ColorTypeDef color)
{
	b2D rect;
	return rect;
}

template <typename T> template <typename char_t>
b2D Print_Class<T>::String(b2D rect, char_t *str, gbasic_t len, ColorTypeDef color)
{
	if (this->Screen->Test()) return rect;
	
	this->Caret = rect;
	char_t C = '0';
    uint32_t __i = 0;
    while (len--) {
			C = *(str + __i++);
      if (this->Caret.x > (rect.w + rect.x) || (C == '\n')) {
          this->Caret.x = rect.x;
				  this->Caret.w = rect.w;
          this->Caret.y += this->FontH;
				  this->Caret.h -= this->FontH;
			} else {}
      if (this->Caret.y > rect.h + rect.y) {
          return this->Caret;
      } else {}	
      if ((C != '\n')) {				
        this->Char(this->Caret, C);		
			} else {}				
    }
	return this->Caret;
}

template <typename T> template <typename char_t>
b2D Print_Class<T>::String(char_t *str, gbasic_t len, ColorTypeDef color)
{
	return this->String(this->Caret, str, len, color);
}

template <typename T> template <typename char_t>
b2D Print_Class<T>::fString(char_t *str, gbasic_t len, ColorTypeDef color)
{
	b2D rect = this->Screen->GetRect();
	rect.x = 0;
	rect.y = 0;
	return this->String(rect, str, len, color);
}

template <typename T>
b2D Print_Class<T>::String(b2D rect, __TEXT text, ColorTypeDef color)
{
	return this->String(rect, text.Buff.Ram, text.Size, color);
}

template <typename T> 
b2D Print_Class<T>::String(__TEXT text, ColorTypeDef color)
{
	b2D rect = this->Screen->GetRect();
	rect.x = 0;
	rect.y = 0;
	return this->String(rect, text.Buff.Ram, text.Size, color);
}


#endif /*PRINT_CLASS_CPP*/

/*End Of File*/

