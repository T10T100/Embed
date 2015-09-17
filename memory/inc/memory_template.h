#ifndef MEMORY_TEMPLATE_CPP
#define MEMORY_TEMPLATE_CPP

#include <stdint.h>

template <typename native>
class Allocator {
  public:
    /*
    Allocator ();
    ~Allocator ();
    */
  template <typename Obj>
    Obj *New ();

  template <typename Obj>
    Obj *New (uint32_t); 
	
	template <typename Obj>
    Obj *NewArray (uint32_t);
	
	template <typename Obj>
    Obj **NewlArray (uint32_t);

  template <typename Obj>
    int32_t Delete (Obj *); 
	
    native *New ();
    native *New (uint32_t); 
	  native *NewArray (uint32_t);
	  native **NewlArray (uint32_t);
  
  private:     
};

void *Alloc (uint32_t);
int32_t Free (void *); 

/*
Allocator::Allocator () {}
Allocator::~Allocator() {}
*/

template <typename native>
template <typename Obj>
  Obj *Allocator<native>::New ()
{
  return (Obj *)Alloc (sizeof(Obj));
}

template <typename native>
template <typename Obj>
  Obj *Allocator<native>::New (uint32_t size)
{
  return (Obj *)Alloc (sizeof(Obj) + size);
}

template <typename native>
template <typename Obj>
  Obj *Allocator<native>::NewArray (uint32_t size)
{
  return (Obj *)Alloc (sizeof(Obj) * size);
}

template <typename native>
template <typename Obj>
  Obj **Allocator<native>::NewlArray (uint32_t size)
{
  return (Obj **)Alloc (sizeof(Obj *) * size);
}

template <typename native>
template <typename Obj>
  int32_t Allocator<native>::Delete (Obj *o)
{
  return Free(static_cast<void *>(o)); 
}

template <typename native>
  native *Allocator<native>::New ()
{
  return (native *)Alloc (sizeof(native));
}

template <typename native>
  native *Allocator<native>::New (uint32_t size)
{
  return (native *)Alloc (sizeof(native) + size);
}

template <typename native>
  native *Allocator<native>::NewArray (uint32_t size)
{
  return (native *)Alloc (sizeof(native) * size);
}


template <typename native>
  native **Allocator<native>::NewlArray (uint32_t size)
{
  return (native **)Alloc (sizeof(native *) * size);
}


#endif /*MEMORY_TEMPLATE_CPP*/

//extern Allocator RAM;

/*End Of File*/

