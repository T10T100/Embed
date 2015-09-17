#include "physic.h"

using namespace Physic;

Bounce::Bounce () {}
	
void Bounce::operator () (float w0, float g, float air, float dt, float m)
{
	this->Air = air;
	this->W0 = w0;
	this->W = w0;
	this->dt = dt;
	this->g = g;
	this->E = w0;
	this->K = 0;
	this->S = w0 / (g * m);
	this->m = m;
	this->V = 0;
	this->sign = 1.0F;
}

float Bounce::Step ()
{
	E = W - K;
	S = E / (m * g);
	V = V + g * dt * sign;
	K = K + m * V * g * dt * sign;
			
	if (E <= 0 && sign > 0) {
		S = 0;
		K = W;
		sign = -1.0F;
	} else {}
	if (K <= 0 && sign < 0) {
		sign = 1.0F;
		K = 0;
		V = 0;
	}
			
	W -= 5;
	if (W < 0) {
	  W = W0;
	} else {}	
	return S;
}

float Bounce::Step(float g)
{
	this->g = g;
	return this->Step();
}





Ball2D::Ball2D () {}
    
void Ball2D::operator () (float m, float p, float a)
{ 
    this->dt = 1.0F;
    this->A = a;
    this->m  = m;
    this->p  = p;
    this->Sx = 0;
    this->Sy = 0;
    V = p / m;
	/*
    this->W = 1000;
	  this->K = 0.0F;
	  this->E = W - K;
	  this->g = 1.0F;
	  this->Vg = 0.0F;
	  this->h = E / (m * g);
	*/
    this->Dir(A);
}

f2P Ball2D::Step (b2D r)
{
    Sx = (Sx + Vx * dt);
    Sy = (Sy + Vy * dt);
	  
    uint32_t t = this->Test(r, A);
    if (t) {
			  switch (t) {
					case 1: if (V > 5.0F) {
							        V -= 0.1F;
                  } else {}
						break;
					case 2: if (V < 30.0F) {
							        V += 0.3F;
                  } else {}
						break;	
          default: break;													
				}
				this->Dir(A);
    } else {}
    
    f2P point = {Sx, Sy};
    return point;
}

void Ball2D::Step ()
{   
    Sx = Sx + Vx * dt;
    Sy = Sy + Vy * dt;
}

bool Ball2D::Test (Ball2D &ball)
{
    f2D r = {ball.Sx, ball.Sy, ball.m, ball.m};
		f2D r0 = {Sx, Sy, this->m, this->m};
		if (Sx >= ball.Sx) {
			if ((Vx > 0)) {
				if ((ball.Vx < 0)) {
				  return false;
				} else if (Vx > ball.Vx){
					return false;
				}
			} else {}
		} else {
			if ((Vx < 0)) {
				if ((ball.Vx > 0)) {
				  return false;
				} else if (Vx < ball.Vx){
					return false;
				}
			} else {}
		}
				
		if (Sy >= ball.Sy) {
			if ((Vy > 0)) {
				if ((ball.Vy < 0)) {
				  return false;
				} else if (Vy > ball.Vy){
					return false;
				}
			} else {}
		} else {
			if ((Vy < 0)) {
				if ((ball.Vy > 0)) {
				  return false;
				} else if (Vy < ball.Vy){
					return false;
				}
			} else {}
		}
    return (gTest::TestBoxBounds(r0, r)); 
}

bool Ball2D::SwapP (Ball2D &ball)
{
	
    float ta, tV, tm, sa, ca; 
	  
	  tV =  ball.V;
	  ta =  ball.A;
	  tm = ball.m; 
	  sa = ball.sina;
	  ca = ball.cosa;
	  float km = 1 / (ball.m + m);
	  float k = (V + tV) * km;
	  
	  ball.V  = k * m;
	  V  =  k * tm;
	  ball.p = ball.m * ball.V;
	  p = m * V;
	  ball.A = A;
	  A = ta;
	  ball.Dir(sina, cosa);
	  this->Dir(sa, ca);
    return false;
}

uint32_t Ball2D::Test (b2D r, float &a)
{
   uint32_t tst = 0;
     if (Sx < m) {
        Sx = m;
        a = -A;
        tst = 1;
    } else if (Sx > r.w) {
        Sx = r.w;
        a = -A;
        tst = 2;
    } else if (Sy < m) {
        Sy = m;
        a = - (PI_const + A);
        tst = 3;
    } else if (Sy > r.h) {
        Sy = r.h;
        a = - (PI_const + A);
        tst = 4;
    } else {}

    return tst;
}



bool Ball2D::Test (float x0, float y0, float x, float y)
{
    bool tst = false;
    float xa = Vx + Sx;
    float ya = Vy + Sy;
    float a = 0.0F;
    
    tst = gTest::TestLineIntersect(x0, y0, x, y, Sx, Sy, xa, ya);
    if (!tst) {
        tst = gTest::TestLineIntersect(x0, y0, x, y, xa, ya, Sx, Sy);
    } else {}
    if (tst) {
      if (y0 == y) {
          a = 0;
      } else if (x0 == x) {
          a = -PI_const;
      } else {
          a = atan(double((y - y0) / (x - x0)));
      }
      this->Dir(-A + a);  
    } else {}
    
    return tst;
}

void Ball2D::Dir (float a)
{
    A = a;
	  sina = sin(A);
	  cosa = cos(A);
    Vx = V * sina;
    Vy = V * cosa;
}

void Ball2D::Dir (float a, float b)
{
	  sina = a;
	  cosa = b;
    Vx = V * sina;
    Vy = V * cosa;
}



Ball2DGroup::Ball2DGroup () {}
    
void Ball2DGroup::operator () (b2D r, float m, float p)
{
    this->Rect = r;
    this->p = p;
    this->m = m;    
}

void Ball2DGroup::Step ()
{
    uint32_t t = this->Balls.Contain();
	  lArray<Ball2D> *array = this->New<lArray<Ball2D> >();
	  (*array)(t);
	  uint32_t moved = 0;
    uint32_t c = t;
	  Ball2D *ball, *ball2;
	  ball = this->Balls.GetFirst();
	  while (ball) {
			 ball->Step(this->Rect); 
			 ball = this->Balls.GetNext(ball);
		}
    for (int32_t i = c; i >= 0; i--) {
        ball = this->Balls.Get(i);
			  this->Balls - ball;
			  ball2 = this->Balls.GetFirst();
        while (ball2) {
            if (ball2->Test(*ball)) {
							  ball2->SwapP(*ball);	
                array->Add(ball2, moved++);
							  i--;
                this->Balls - ball2;							
            } else {}
					  ball2->key = ball2->Sx * ball2->Sy;
						ball2 = this->Balls.GetNext(ball2);
        }
				this->Balls + ball;
    }
		this->Balls.Array(array, moved);
		(*array).~lArray();
}

void Ball2DGroup::Add (uint32_t q)
{
    float a = PI2_const - 0.7F;
	  float x = 30, y = 30, p = 3.0F;
    Ball2D *ball;
    while (q--) {
        ball = this->New();
        if (! ball) {
            return;
        } else {}
        (*ball)(m, p, a);
				m += 0.1F;
				ball->Sx = 30;
				ball->Sy = 30;	
				p += 1.5F;
        this->Balls + ball;
        a += 0.01F;
    }
}

void Ball2DGroup::Add (float M, float P, float A)
{
    Ball2D *ball;
    ball = this->New();
    if (! ball) {
        return;
    } else {}
    (*ball)(M, P, A);
		ball->Sx = 30;
		ball->Sy = 30;
	  this->Balls + ball;
}

void Ball2DGroup::Remove (uint32_t q)
{
    
}

void Ball2DGroup::Draw ()
{
    f2P p = {0, 0};
    Ball2D *ball = this->Balls.GetFirst();
    while (ball) {
        p.x = ball->Sx - ball->m;
        p.y = ball->Sy - ball->m;
        this->Draw (p, ball->m, 0xcccc + (uint16_t)ball->p);    
        ball = this->Balls.GetNext(ball);
    }    
}












StarDust::StarDust () {}
StarDust::~StarDust () {}

void StarDust::operator () ()
{
    this->index_ = 0;
}

void StarDust::Step (b2D r)
{
    DustPart *npart;
    DustPart *part;
    DustPart tpart;
    int32_t q = eq_, t = eq_;
    int32_t moved = 0;
    while (q--) {
        part = &edust_[q];
        
        part->x = part->x + part->vx;
        part->y = part->y + part->vy;
        if (part->x < 1) {
           part->vx = -part->vx; 
           part->x = 1;
        } else if (part->x > r.w) {
           part->vx = -part->vx; 
           part->x = r.h - 1;
        } else if (part->y < 1) {
           part->vy = -part->vy;
           part->y = 1;            
        } else if (part->y > r.h) {
           part->vy = -part->vy; 
           part->y = r.h - 1;
        } else {}
        
        t = 0;
        npart = &edust_[0];
        while (t < q) {
            
            
            if (this->Test(*part, *npart)/* || this->TestAround(*npart)*/) {
                moved++;
                tpart = edust_[q];
                edust_[q] = edust_[t];
                edust_[t] = tpart;
                q--;
            } else {
                
            }
            npart = &edust_[++t];
        }        
    } 
}

int32_t StarDust::TestAround (DustPart &p)
{
    float x = p.x;
    float y = p.y;
    if (this->ReadPixel(x, y)) {
        return 1;
    } else     if (this->ReadPixel(x + 1, y)) {
        return 1;
    } else     if (this->ReadPixel(x - 1, y)) {
        return 1;
    } else     if (this->ReadPixel(x, y + 1)) {
        return 1;
    } else     if (this->ReadPixel(x, y - 1)) {
        return 1;
    } else     if (this->ReadPixel(x + 1, y + 1)) {
        return 1;
    } else     if (this->ReadPixel(x - 1, y - 1)) {
        return 1;
    } else     if (this->ReadPixel(x + 1, y - 1)) {
        return 1;
    } else     if (this->ReadPixel(x - 1, y + 1)) {
        return 1;
    } else {}
    return 0;        
}

int32_t StarDust::Test (DustPart &p, DustPart &n)
{
    float a, vx, vy;
    if (((uint32_t)p.x == (uint32_t)n.x) && ((uint32_t)p.y == (uint32_t)n.y)) {
        a = p.a;
        vx = p.vx;
        vy = p.vy;
        p.a = n.a;
        p.vx = n.vx;
        p.vy = n.vy;
        n.a = a;
        n.vx = vx;
        n.vy = vy;
        return 1;
    }
    return 0;
}

void StarDust::Add (float a)
{
    DustPart *part = this->New();
    if (! part) {
        return; 
    } else {}
    part->x = 1;
    part->y = 1;    
    part->v = 1.0F;
    part->a = a;
    part->vx = 1.0F * sin(part->a);
    part->vy = 1.0F * cos(part->a);
    this->parts_[index_] + part;
}

void StarDust::Add (uint32_t)
{
    
}

void StarDust::SetUp (DustPart *dust, uint32_t q)
{
    float a = 0.1F;
    this->eq_ = q;
    this->edust_ = dust;
    while (q--) {
       dust[q].x = 1;
       dust[q].y = 1;    
       dust[q].v = 1.0F;
       dust[q].a = a;
       dust[q].vx = 1.0F * sin(a);
       dust[q].vy = 1.0F * cos(a); 
       a += 0.00628;
    }
}

void StarDust::Remove (uint32_t)
{
    
}

void StarDust::Draw ()
{
    
    DustPart part = edust_[0];
    uint32_t t = eq_;
    while (t--) {
        this->Draw (part.x, part.y, part.x * part.y);
        part = edust_[t];
    }
   
}
    

    

/*End Of File*/
	