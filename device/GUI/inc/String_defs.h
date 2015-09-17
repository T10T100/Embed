#ifndef STRING_DEFS_H
#define STRING_DEFS_H
#include <stdint.h>

struct bar_t {
  const char* __string;
  uint16_t __len;    
};

typedef struct {
	union __Buff {
		const char *Const;
		char       *Ram;    
	} Buff;
	uint32_t Size;
} __TEXT;

#endif /*STRING_DEFS_H*/

/*End Of File*/
