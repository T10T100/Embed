#ifndef __ALLOCATOR
#define __ALLOCATOR

#include <stdint.h>
#include <errno.h>
#include "List.h"
#include "locker.h"
#include "Terminal_Interface.h"
#include "String_Defs.h"

#ifndef Heap_Print_Alloc
#define Heap_Print_Alloc 200
#endif

typedef uint32_t memory_size_t;
typedef uint32_t alloc_addr_t; 

class MemoryChunk : public List_Node <MemoryChunk, alloc_addr_t> {
  public:
	  MemoryChunk () {}
	private:
	  memory_size_t size;
	
	friend class MemoryAllocator;
};

#define __m sizeof(MemoryChunk)

class MemoryAllocator : public Locker ,
	                      public __TTY {
	public:
	  MemoryAllocator () {}
	  void operator () (void *, memory_size_t);
	  void *New (memory_size_t);
	  int32_t Delete (void *);
			
	  int32_t Check ();	
	  __TEXT PrintTable ();
	private:
	  MemoryChunk *Separate (MemoryChunk *P, memory_size_t Size);
	  int32_t Sanitize (List_Iterator <MemoryChunk> &List);
	  List_Iterator <MemoryChunk> PoolFree, PoolInUse;
      uint32_t Success, Errors, Sanitized;
};


#endif /*__ALLOCATOR*/

