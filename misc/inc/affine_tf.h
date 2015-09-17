#ifndef AFFINE_TF_H
#define AFFINE_TF_H
#include "geometry.h"
#include <math.h>

class Affine_Body {
	public:
		Affine_Body ();
	  void operator () ();
	  f2D PointRotateZ (f2D, float);
	  f2D PointRotateZ (float, float, float, float, float);
	private:
	  	
	
};

template <typename T>
T Sqr (T, T);


#endif /*AFFINE_TF_H*/

/*End Of File*/

