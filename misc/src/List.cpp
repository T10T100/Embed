
#ifndef __LIST
#define __LIST

#include "List.h"


template <class T>
List_Iterator<T>::List_Iterator()
{
}
template <class T>
bool List_Iterator<T>::operator + (T &item)
{
	this->Elements++;
		T *i,*j;
		if (!this->First) {
			this->First = &item;
			this->Last = &item;
			item.rlink = (T *)0;
			item.llink = (T *)0;
			return true;
		}
		i = this->First;
		j = (T *)0;
		while (i != (T *)0) {
			if (i->key > item.key) {
				j = i;
				i = i->rlink;
				continue;
			}
			if (i->llink) {
				i->llink->rlink = &item;
				item.rlink = i;
				item.llink = i->llink;
				i->llink = &item;
				return true;
			}
			item.rlink = i;
			item.llink = (T *)0;
			i->llink = &item;
			this->First = &item;
			return true;
		}
		j->rlink = &item;
		item.rlink = (T *)0;
		this->Last = &item;
		item.llink = j;
		return true;	
}
template <class T>
T *List_Iterator<T>::operator - (T &item)
{
	if (this->Elements == 0)return (T *)0;
	this->Elements--;
	T *l = item.llink,*r = item.rlink;
		if (!l&&!r) {
			this->First = (T *)0;
			this->Last = (T *)0;
			return (T *)0;
		}
		if (!l) {
			this->First = r;
			r->llink = (T *)0;
		}
		else    l->rlink = r;
		
		if (!r) {
   			l->rlink = (T *)0;
			  this->Last = l;
		}
		else    r->llink = l;
		return &item;	
}

template <class T>
bool List_Iterator<T>::operator + (T *item)
{
	return *this + *item;
}

template <class T>
	template <typename A>
List_Iterator<T> &List_Iterator<T>::operator + (A &array)
{
	uint32_t t = array.Contain();
	while (t--) {
		(*this) + array[t];
	}
	return *this;
}

template <class T>
	template <typename A>
List_Iterator<T> &List_Iterator<T>::operator + (A *array)
{
	A &a = *array;
	return (*this) + a;
}

template <class T>
	template <typename A>
List_Iterator<T> &List_Iterator<T>::Array (A &array, uint32_t t)
{
	while (t--) {
		(*this) + array[t];
	}
	return *this;
}

template <class T>
	template <typename A>
List_Iterator<T> &List_Iterator<T>::Array (A *array, uint32_t t)
{
	A &a = *array;
	return this->Array(a, t);
}

		  

template <class T>
T *List_Iterator<T>::operator - (T *item)
{
	return *this - *item;
}
/*
template <class T>
bool List_Iterator<T>::operator << (T &item)
{
	return 0;
}
template <class T>
bool List_Iterator<T>::operator >> (T &item)
{
	return 0;
}
*/

template <class T>
T *List_Iterator<T>::Get (uint32_t index)
{
	if (this->Elements < index) return (T *)0;
	
	T *item = this->First;
	while (index--)
		  item = item->rlink;
	return item;
}
template <class T>
T *List_Iterator<T>::GetLast ()
{
	return this->Last;
}

template <class T>
T *List_Iterator<T>::GetFirst ()
{
	return this->First;
}

template <class T>
T *List_Iterator<T>::GetNext (T *item)
{
    if (item != (T *)0)
        if (item->rlink != (T *)0) return item->rlink;
    return (T *)0;
}

template <class T>
T *List_Iterator<T>::Remove (uint32_t index)
{
	if (this->Elements < index) return (T *)0;
	
	T *item = this->First;
	while (index--)
		  item = item->rlink;
	*(this) - item;
	return item;
}

template <class T>
int32_t List_Iterator<T>::Remove (T *item)
{
	if (!this->Contain()) return -1;
	*(this) - item;
	
	return 0;
}

template <class T>
int32_t List_Iterator<T>::Remove (T &item)
{
	if (!this->Contain()) return -1;

	*(this) - &item;
	return 0;
}

template <class T>
int32_t List_Iterator<T>::Put (T &item, uint32_t index)
{
	return -1;
}
template <class T>
uint32_t List_Iterator<T>::Contain ()
{
	return this->Elements;
}

#endif /*__LIST*/
