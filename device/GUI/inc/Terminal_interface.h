#ifndef TERMINAL_INTERFACE_H
#define TERMINAL_INTERFACE_H

#include <stdint.h>
#include <string.h>
#include "dtostr.h"
#include "String_Defs.h"

#ifndef T_CHAR
#define T_CHAR 
typedef char tchar_t; 
#endif

typedef struct {
	uint8_t Tab;
} tab_t;

class __TTY {
	public:
	  __TTY ();
	  void operator () (void *, uint32_t);
	  __TTY &Print (int32_t, char *str, uint32_t);
	  __TTY &Print (char *str, uint32_t);
	  __TTY &Print (int32_t, char *str);
	  __TTY &Print (char *str);
	  __TTY &Char (int32_t, char);
	  __TTY &Char (char);
	  __TTY &operator << (char *);
	  __TTY &operator << (int32_t);
	  __TTY &operator << (float);
	  __TTY &operator << (double);
	  __TTY &operator << (char);
	  __TTY &operator << (tab_t);
	  __TTY &operator + (char *);
	  __TTY &operator + (int32_t);
	  __TTY &operator + (float);
	  __TTY &operator + (double);
	  __TTY &operator + (char);
	  __TTY &operator + (tab_t);
	
	  __TEXT Print ();
	private:
		void Clear ();
		char *Buff;
	  uint32_t Size;
	  uint32_t Cursor;
};

#endif /*TERMINAL_INTERFACE_H*/

/*End Of File*/

