#ifndef PHYSIC_H
#define PHYSIC_H
#include <stdint.h>
#include <math.h>
#include "geometry.h"
#include "misc/src/list.cpp"
#include "memory_template.h"
#include "array.h"

namespace Physic {
	
	class Bounce {
		public:
			Bounce ();
			void operator ()(float, float, float, float, float);
			float Step ();
			float Step (float);
		private:
			float V, S, E, K, W, W0, g, dt, Air, m, sign; 
	};
    

    class Ball2D : public List_Node <Ball2D, float> {
        public:
           Ball2D ();
           void operator () (float, float, float);
           f2P Step (b2D);  
				   void Step ();
           bool Test (float, float, float, float);        
        private:
           void Dir (float);
				   void Dir (float, float);
           uint32_t Test (b2D, float &);
           
           bool Test (Ball2D &);
				   bool SwapP (Ball2D &);
           float dt, V, Vx, Vy, Sx, Sy, p, m, A;
				   float sina, cosa;
        
        friend class Ball2DGroup;
            
    };
    
    class Ball2DGroup : public Allocator <Ball2D> {
        public:
          Ball2DGroup ();
          void operator () (b2D, float, float);
          void Step ();
          void Add (uint32_t);
				  void Add (float, float, float);
          void Remove (uint32_t);
          void Draw ();
        
        private:
          float p, m;
          b2D Rect;  
          List_Iterator<Ball2D> Balls;  
          virtual void Draw (f2P, float, uint32_t);
    };
    
	

};



#endif /*PHYSIC_H*/

/*End Of File*/

