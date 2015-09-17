#ifndef ARRAY_H
#define ARRAY_H
#include <stdint.h>
#include "memory_template.h"
#include "misc/src/list.cpp"

template <typename I>
class Array : public Allocator <I> {
    public:
        Array ();
        void operator () ();
        void AddNext ();
        void Add (uint32_t);
        I *Get (uint32_t);
        uint32_t Contain ();
    private:
        uint32_t Elements;
		    I *larray;
};


template <typename I>
class lArray : public Allocator <I> {
    public:
        lArray ();
        void operator () (uint32_t);
		    void operator () (List_Iterator<I> &);
		    void operator () (lArray<I> &);
		    I *operator [] (uint32_t);
		    lArray<I> operator = (uint32_t);
		    lArray<I> operator + (I *);
        void AddNext (I *);
        void Add (I *, uint32_t);
        I *Get (uint32_t);
		    I *GetArray (uint32_t &);
		    ~lArray ();
		    
        uint32_t Contain ();
    private:
        uint32_t Elements;
		    uint32_t P;
		    I **larray;
};


template <typename I>
lArray<I>::lArray () {} 
	
template <typename I>
lArray<I>::~lArray () 
{
  this->Delete(this->larray);
	this->Delete(this);
}


template <typename I>
void lArray<I>::operator () (uint32_t q)
{
	this->larray = this->NewlArray(q);
	
	if (this->larray == (I **)0) {
		return;
	} else {}
	this->Elements = q;
  this->P = 0;
}

template <typename I>
void lArray<I>::operator () (List_Iterator<I> &list)
{
	uint32_t t = list.Contain();
  this->larray = this->NewlArray(t);
	
	if (this->larray == (I **)0) {
		return;
	} else {}
	uint32_t n = 0;
	I *link = list.GetFirst();
	this->Elements = t;
  while (t--) {
      this->larray[n++] = link;
		  link = list.GetNext(link);
	}	
  this->P = 0;	
}

template <typename I>
void lArray<I>::operator () (lArray<I> &array)
{
	uint32_t t = array.Contain() + 1;
	this->Elements = t;
  this->larray = this->NewlArray(t);
	
	if (this->larray == (I **)0) {
		return;
	} else {}
	this->Elements = t;
  while (t--) {
      this->larray[t] = array[t];
	}		
	this->P = 0;
}

template <typename I>
I *lArray<I>::operator [] (uint32_t i)
{
	return this->larray[i];
}

template <typename I>
lArray<I> lArray<I>::operator = (uint32_t p)
{
	if (p < this->Elements) {
	    this->P = p;
	} else {}
	return *this;
}

template <typename I>
lArray<I> lArray<I>::operator + (I *item)
{
	this->larray[this->P] = item;
	if (this->P < this->Elements) {
		  this->P++;
	} else {}
	return *this;
}

template <typename I>
void lArray<I>::AddNext (I *item)
{
	this->larray[this->Elements] = item;
}


template <typename I>
void lArray<I>::Add (I *item, uint32_t i)
{
	if (i < this->Elements) {
	    this->larray[i] = item;
	} else {}
}

template <typename I>
I *lArray<I>::Get (uint32_t i)
{
	return this->larray[i];
}

template <typename I>
I *lArray<I>::GetArray (uint32_t &t)
{
	t = this->Elements;
	return this->larray;
}

template <typename I>
uint32_t lArray<I>::Contain ()
{
	return this->Elements;
}
#endif /*ARRAY_H*/

/*End Of File*/

