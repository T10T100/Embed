

#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <stdint.h>
#include <math.h>

#define PI_const (3.14159265359F)
#define PI2_const (3.14159265359F / 2.0F)
#define PI4_const (3.14159265359F / 4.0F)
#define PI32_const (3.14159265359F * 1.5F)

typedef int16_t gbasic_t;


typedef struct {
	gbasic_t x, y, w, h;
} b2D;

typedef struct {
	float x, y, w, h;
} f2D;

struct b2P {
	gbasic_t x, y;
};

typedef struct {
	float x, y;
}f2P ;

class Coordinates {
	public:
    void Place (b2D);
	  void Place (gbasic_t, gbasic_t);
	  void Dispose (b2D);
	  void Dispose (gbasic_t, gbasic_t, gbasic_t, gbasic_t);
	  b2D GetRect();
	  b2D GetxRect ();
      b2D GetyRect ();
      b2D GetxyRect ();
	  int32_t GetH();
	  int32_t GetW();
	  b2D AllignLeft (b2D);
	  b2D AllignRight (b2D);
	  b2D AllignTop (b2D);
	  b2D AllignBottom (b2D);
	  int32_t Trunc (b2D *, b2D);
	  int32_t Trunc (b2D *);
	  b2D TruncLine (gbasic_t, gbasic_t, gbasic_t, gbasic_t);
	  gbasic_t X0, Y0, W, H;	
    protected:
};

namespace gTest {
  
  bool TestLineIntersect (float, float, float, float ,\
                          float, float, float, float  );   

  bool TestBoxBounds (f2D, f2D);  
  
  bool TestPointInBox (f2D, float, float);
    
    
    
};




/*GEOMETRY_H*/

#endif



