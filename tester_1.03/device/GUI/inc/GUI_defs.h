
#ifndef GUI_DEFS_H
#define GUI_DEFS_H


#include <stdint.h>
#include <geometry.h>
#include "memory_alloc.h"

#define labs(x) ((int32_t)(x) < 0 ? -(int32_t)(x) : (int32_t)(x))

#ifdef ColorDepthBpp1
typedef uint8_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = 1,
};
#endif
#ifdef ColorDepthBpp4
typedef uint8_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = 15,
};
#endif
#ifdef ColorDepthBpp8
typedef uint8_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = 255,
};
#endif
#ifdef ColorDepthBpp16
typedef uint16_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = 65535,
};
#endif
#ifdef ColorDepthBpp24
typedef uint32_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = (255) | (255 << 8) | (255 << 16),
};
#endif
#ifdef ColorDepthBpp32
typedef uint32_t ColorTypeDef;
enum StdPalette {
	StdColBlack = 0,
	StdColWhite = (255) | (255 << 8) | (255 << 16) | (255 << 24),
};
#endif

struct  tImage{
    const ColorTypeDef *Image;
    uint16_t W, H;
    
};

struct tChar {
    const uint8_t Code;
    const tImage *Image;       
};

struct tFont {
    const uint8_t Quantity;
    const tChar *CharArray;   
    const uint8_t W, H;    
};




#endif /*GUI_DEFS_H*/
