#ifndef __LOCKER
#define __LOCKER
#include <stdint.h>

class Locker {
	public: 
		Locker ();
	  void Unlock (uint32_t = 0);
	  void Lock (uint32_t = 0);
	  bool Test ();
  private:
    bool lock;		
};



#endif

