#include "affine_tf.h"

template <typename T>
T Sqr (T a, T b)
{ 
	return a * b;
}

Affine_Body::Affine_Body () {}
	
void Affine_Body::operator () ()
{

}

f2D Affine_Body::PointRotateZ (float x0, float y0, float x, float y, float A)
{
	f2D rect = {0, 0, 0, 0};
	rect.x = x0 + x + y * A;
	rect.y = y0 + y - x * A; 
	return rect;
}


f2D Affine_Body::PointRotateZ (f2D rect, float A)
{
	return this->PointRotateZ(rect.x, rect.y, rect.w, rect.h, A);
}

