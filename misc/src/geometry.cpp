#include "geometry.h"

b2D Coordinates::GetRect ()
{
	b2D rect = {this->X0, this->Y0, this->W, this->H};
	return rect;
}

b2D Coordinates::GetxRect ()
{
	b2D rect = {this->X0 + this->W, this->Y0, this->W, this->H};
	return rect;
}

b2D Coordinates::GetyRect ()
{
	b2D rect = {this->X0, this->Y0 + this->H, this->W, this->H};
	return rect;
}

b2D Coordinates::GetxyRect ()
{
	b2D rect = {this->X0 + this->W, this->Y0 + this->H, this->W, this->H};
	return rect;
}

int32_t Coordinates::GetW ()
{
	return this->W;
}

int32_t Coordinates::GetH ()
{
	return this->W;
}

void Coordinates::Place (b2D rect)
{
    this->X0 = rect.x;
    this->Y0 = rect.y;
}

void Coordinates::Place (gbasic_t x, gbasic_t y)
{
	this->X0 = x;
	this->Y0 = y;
}

void Coordinates::Dispose (b2D rect)
{
	this->X0 = rect.x;
	this->Y0 = rect.y;
	this->W  = rect.w;
	this->H  = rect.h;
}

void Coordinates::Dispose (gbasic_t x, gbasic_t y, gbasic_t w, gbasic_t h)
{
	this->X0 = x;
	this->Y0 = y;
	this->W  = w;
	this->H  = h;
}

b2D Coordinates::AllignLeft (b2D rect)
{
	this->W = rect.x;
	return this->GetRect();
}
b2D Coordinates::AllignRight (b2D rect)
{
	this->X0 = rect.x + rect.w;
	this->W -= X0;
	return this->GetRect();
}
b2D Coordinates::AllignTop (b2D rect)
{
	this->Y0 = rect.y + rect.h;
	this->H -= Y0;
	return this->GetRect();
}

b2D Coordinates::AllignBottom (b2D rect)
{
	this->H = rect.y;
	return this->GetRect();
}

int32_t Coordinates::Trunc (b2D *rect, b2D cut)
{
	
	if (rect->x > cut.w) {
		  rect->x = cut.w;
	}
	if (rect->x + rect->w > cut.w) {
		  rect->w = cut.w - rect->x;
	}
  if (rect->y > cut.h) {
		  rect->y = cut.h;
	}
	if (rect->y + rect->h > cut.h) {
		  rect->h = cut.h - rect->y;
	}
	return 0;
}

int32_t Coordinates::Trunc (b2D *rect)
{
	
	if (rect->x > this->W) {
		  rect->x = this->W;
	}
	if (rect->x + rect->w > this->W) {
		  rect->w = this->W - rect->x;
	}
  if (rect->y > this->H) {
		  rect->y = this->H;
	}
	if (rect->y + rect->h > this->H) {
		  rect->h = this->H - rect->y;
	}
	
	rect->x += this->X0;
	rect->y += this->Y0;
	return 0;
}

b2D Coordinates::TruncLine  (gbasic_t x0, gbasic_t y0,gbasic_t x, gbasic_t y)
{	
	if (x0 < 0) {
		  x0 = 0;
	} else {
		  if (x0 > this->W) {
		     x0 = this->W;
	    }  else {}
	}
	if (y0 < 0) {
		  y0 = 0;
	} else {
      if (y0 > this->H) {
		      y0 = this->H;
	    } else {}	
	}
    if (x < 0) {
	    x = 0;
	} else {
		  if (x > this->W) {
		      x = this->W;
	    } else {}
	}
    if (y < 0) {
		  y = 0;
	} else {
	    if (y > this->H) {
		      y = this->H;
	    } else {}
	}
	
	x0 += this->X0;
	y0 += this->Y0;
	x  += this->X0;
	y  += this->Y0;
	b2D rect = {x0, y0, x, y};
	return  rect;
}

using namespace gTest;


bool gTest::TestLineIntersect (float xa, float ya, float xb, float yb,\
                        float xc, float yc, float xd, float yd )
{
  float v1, v2, v3, v4;
  
  v1 = xb * yc - yb * xc;
  v2 = xb * yd - yb * xd;
  v1 *= v2;
  if (v1 > 0) {
      return false;
  } else {}
      
  v3 = xd * ya - yd * xa;
  v4 = xd * yb - yd * xb;
  v3 *= v4;
  if (v3 > 0) {
      return false;
  } else {}

  return true;
}

bool gTest::TestBoxBounds (f2D r0, f2D r1)
{
	 int32_t w0 = r0.x + r0.w, h0 = r0.y + r0.h;
	 int32_t w = r1.x + r1.w, h = r1.y + r1.h;
	 if (w < r0.x) {
		   return false;
	 } else {}
	 if (h < r0.y) {
		   return false;
	 } else {}
		 
	 if (w0 < r1.x) {
		   return false;
	 } else {}
	 if (h0 < r1.y) {
		   return false;
	 } else {}
   return true;
}

bool gTest::TestPointInBox (f2D r, float x, float y)
{
   x -= r.x;
   if (x < 0) {
       return false;
   } else if (x > r.w) {
       return false;
   } else {}
       
   y -= r.y;
   if (y < 0) {
       return false;
   } else if (y > r.h) {
       return false;
   } else {}
       
   return true;
}

