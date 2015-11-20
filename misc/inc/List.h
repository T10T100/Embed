#ifndef __LIST
#define __LIST
#include <stdint.h>
#include <vector>

template <class T, typename K>
	class List_Node {
		public:
			T *rlink, *llink;
		  K key;
		  //virtual bool TestWith (K &);
	};

template <class Object>
  class ArrayList {
	  public:
	  	ArrayList ();
	    bool add (Object &);
		  bool add (Object *);
		  int32_t add (Object &, uint32_t index);
		template <typename Array>
		  void addAll (Array &);
		template <typename Array>
		  void addAll (Array *);
    template <typename A>
		  A &add(A &);
		template <typename A>
		  A &add (A *);
	    Object &remove (Object &);
	    Object &remove (Object *);
		  Object &remove (uint32_t index);

		template <typename A>
		  A &addAll (A &);
		template <typename A>
		  A &addAll (A *);
		
	    Object &get (uint32_t index);
	    Object &getLast ();
      Object &getFirst ();
		  Object &removeLast ();
      Object &removeFirst ();
      Object &getNext (Object *);
		  Object &getNext (Object &);
	    uint32_t size ();
		  bool isEmpty ();
	  private:
		  Object *First, *Last;
	    uint32_t Elements;
  };

template <class Object>
ArrayList<Object>::ArrayList()
{
}
template <class Object>
bool ArrayList<Object>::add(Object &item)
{
	this->Elements++;
		Object *i,*j;
		if (!this->First) {
			this->First = &item;
			this->Last = &item;
			item.rlink = (T *)0;
			item.llink = (T *)0;
			return true;
		}
		i = this->First;
		j = (Object *)0;
		while (i != (Object *)0) {
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
		item.rlink = (Object *)0;
		this->Last = &item;
		item.llink = j;
		return true;	
}
template <class Object>
Object &ArrayList<Object>::remove (Object &item)
{
	if (this->Elements == 0)return (Object *)0;
	this->Elements--;
	Object *l = item.llink,*r = item.rlink;
		if (!l&&!r) {
			this->First = (Object *)0;
			this->Last = (Object *)0;
			return (Object *)0;
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
		return item;	
}

template <class Object>
bool ArrayList<Object>::add(Object *item)
{
	return *this + *item;
}


template <class Object>
	template <typename Array>
Array &ArrayList<Object>::add(Array *array)
{
	Array &a = *array;
	return (*this) + a;
}

template <class Object>
	template <typename Array>
void ArrayList<Object>::addAll (Array &array)
{
	while (t--) {
		(*this) + array[t];
	}
	return *this;
}

template <class Object>
	template <typename Array>
void ArrayList<Object>::addAll (Array *array)
{
	for (Object o : array.getUserObject) {
		
	}
	Array &a = *array;
	return this->Array(a, t);
}

		  

template <class Object>
Object &ArrayList<Object>::remove (Object *item)
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

template <class Object>
Object &ArrayList<Object>::get (uint32_t index)
{
	if (this->Elements < index) return (T *)0;
	
	T *item = this->First;
	while (index--)
		  item = item->rlink;
	return item;
}
template <class Object>
Object &ArrayList<Object>::getLast ()
{
	return this->Last;
}

template <class Object>
Object &ArrayList<Object>::getFirst ()
{
	return this->First;
}

template <class Object>
Object &ArrayList<Object>::getNext (Object &item)
{
    if (item != (Object *)0)
        if (item->rlink != (Object *)0) return item->rlink;
    return (Object *)0;
}

template <class Object>
Object &ArrayList<Object>::remove (uint32_t index)
{
	if (this->Elements < index) return (T *)0;
	
	T *item = this->First;
	while (index--)
		  item = item->rlink;
	*(this) - item;
	return item;
}


template <class Object>
uint32_t ArrayList<Object>::size ()
{
	return this->Elements;
}

#endif /*__LIST*/
