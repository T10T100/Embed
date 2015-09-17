#include "memory_alloc.h"

void MemoryAllocator::operator () (void *__heap, memory_size_t __size) 
{
	MemoryChunk *chunk = (MemoryChunk *)__heap;
	for (memory_size_t i = 0; i < __size; i++) {
	    *((uint8_t *)__heap + i) = 0;
	}
	chunk->size = __size;
	chunk->key  = (alloc_addr_t)chunk;
	this->PoolFree + chunk;
	char *a = (char *)this->New(Heap_Print_Alloc);
	__TTY::operator () (a, Heap_Print_Alloc);
	this->Unlock();
}

MemoryChunk *MemoryAllocator::Separate (MemoryChunk *memo, memory_size_t size)
{
	  MemoryChunk *chunk = (MemoryChunk *)0;
		chunk = (MemoryChunk *)((alloc_addr_t)memo + size + sizeof(MemoryChunk));
		chunk->size = memo->size - size - sizeof(MemoryChunk);
		memo->size = size;
		return chunk;
}

int32_t MemoryAllocator::Sanitize (List_Iterator <MemoryChunk> &List)
{
	  if (List.Contain() < 2) {
			return -1;
		} else {}
		MemoryChunk *New = List.GetLast()->llink, *Old = List.GetLast();
		while (New != (MemoryChunk *)0) {
			if ((alloc_addr_t)Old + Old->size + sizeof(MemoryChunk) == (alloc_addr_t)New) {
				Old->size += sizeof(MemoryChunk) + New->size;
				List - New;
        this->Sanitized++;
			}
			Old = New;
			New = New->llink;
		}	
		New = List.GetFirst()->rlink;
		Old = List.GetFirst();
		while (New != (MemoryChunk *)0) {
			if ((alloc_addr_t)Old + Old->size + sizeof(MemoryChunk) == (alloc_addr_t)New) {
				Old->size += sizeof(MemoryChunk) + New->size;
				List - New;
        this->Sanitized++;
			}
			Old = New;
			New = New->rlink;
		}	
    return 0;		
}

void *MemoryAllocator::New (memory_size_t size)
{
	 if (!size) return 0;
	 if (this->Test()) return 0;
	 this->Lock();
	
	 MemoryChunk *chunk = this->PoolFree.GetFirst();
			while (chunk != (MemoryChunk *)0) {
				if (chunk->size >= size) {
					this->PoolFree.Remove(chunk);
					if (chunk->size >= size + sizeof(MemoryChunk) + __m) 
						this->PoolFree + Separate(chunk, size);
					this->PoolInUse + chunk;
					chunk->key = (alloc_addr_t)chunk;
					this->Unlock();
                    this->Success++;
					return (void *)(chunk + 1);
				}
				chunk = chunk->rlink;
			}
	 errno = ENOMEM;
     this->Errors++;
	 this->Unlock();
	 return (void *)0;
}

int32_t MemoryAllocator::Delete (void *P)
{
	 if (P == (MemoryChunk *)0) {
         this->Errors++;
         return errno = EINVAL;
     } else {}
	 if (this->Test()) {
         this->Errors++;
         return 0;
     } else {}
	 this->Lock();
	 errno = 0;
	 MemoryChunk *chunk = (MemoryChunk *)(P) - 1;
	 
	 /*
	 if (!(chunk->llink) && !(chunk->llink)) errno = EINVAL;
	 else if (!(chunk->llink)) {
		 if (chunk->rlink->llink != chunk) errno = EINVAL;
	 } else if (!(chunk->rlink)){
		 if (chunk->llink->rlink != chunk) errno = EINVAL;
	 } else {
		 if (chunk->llink->rlink != chunk->rlink->llink) errno = EINVAL;
	 }
	 */
	 if (errno == EINVAL) {
		 this->Unlock();
		 return errno;
	 } else {}
	 this->PoolInUse - chunk;
	 this->PoolFree + chunk;
	 Sanitize(this->PoolFree);
	 this->Unlock();
	 return errno;	
}

int32_t MemoryAllocator::Check ()
{
	return 0;
}

__TEXT MemoryAllocator::PrintTable ()
{
	int32_t t = this->PoolInUse.Contain();
	int32_t i = this->PoolFree.Contain(), total;
	this->Print(0, (char *)"Memory Chip :", 13);
	this->Print((char *)"CY1619", 6);
	(*this) + '\n';
	this->Print((char *)"Memory Speed :", 14);
	this->Print((char *)"20MHz", 5);
	(*this) + '\n';
	this->Print((char *)"Allocations:", 12);
	(*this) + ' ' + (i + t) + '(' + i + '/' + t + ')' + '\n';
	i = this->PoolFree.Contain();
	t = 0;
	while (i--) {
		t += this->PoolFree.Get(i)->size;
	}
	total = t;
	this->Print((char *)"Free (Bytes):", 13);
	(*this) + ' ' + t + '\n';
	
	i = this->PoolInUse.Contain();
	t = 0;
	while (i--) {
		t += this->PoolInUse.Get(i)->size;
	}
	this->Print((char *)"Used (Bytes):", 13);
	(*this) + ' ' + t + '\n';
	total += t;
    this->Print((char *)"Total (Bytes):", 14);
	(*this) + ' ' + total + '\n';
    
    this->Print((char *)"Succeed:", 8);
	(*this) + ' ' + (int32_t)this->Success + '\n';
    this->Print((char *)"Sanitized:", 10);
	(*this) + ' ' + (int32_t)this->Sanitized + '\n';
    this->Print((char *)"Errors:", 7);
	(*this) + ' ' + (int32_t)this->Errors + '\n';
	return this->Print();
}


