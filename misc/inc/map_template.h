#ifndef MAP_TEMPLATE_H
#define MAP_TEMPLATE_H
#include <stdint.h>
#include "list_template.h"
namespace storage {
	
template <const int Q, typename T_item, typename T_key>
class MapIterator {
	public:
		Iterator<T_item, T_key> iterator_[Q];
	  T_item &Pick (uint32_t);
	  void SetKey (uint32_t, T_key);
	private:
};	

template <const int Q, typename T_item, typename T_key>
T_item &MapIterator<Q, T_item, T_key>::Pick (uint32_t n)
{
	if (n >= Q) {
		n = Q - 1;
	} else {}
	return this->iterator_[n].node_->item_;
}

template <const int Q, typename T_item, typename T_key>
void MapIterator<Q, T_item, T_key>::SetKey (uint32_t n, T_key key)
{
	if (n >= Q) {
		n = Q - 1;
	} else {}
	this->iterator_[n].node_->key = key;
}
	
template <const int Q, typename T_item, typename T_key>
class Map {
	public:
		Map ();
	  void operator () ();
	  Map &operator + (T_item &);
	  Map &operator + (T_item *);
	  Map &operator - (MapIterator<Q, T_item, T_key> &);
	  Map &operator - (MapIterator<Q, T_item, T_key> *);
	  MapIterator<Q, T_item, T_key>Pick (uint32_t);
	  MapIterator<Q, T_item, T_key>PickPrev (MapIterator<Q, T_item, T_key> &, uint32_t);
	  MapIterator<Q, T_item, T_key>PickPrev (MapIterator<Q, T_item, T_key> *, uint32_t);
	  MapIterator<Q, T_item, T_key>PickNext (MapIterator<Q, T_item, T_key> *, uint32_t);
	  MapIterator<Q, T_item, T_key>PickNext (MapIterator<Q, T_item, T_key> &, uint32_t);
	  MapIterator<Q, T_item, T_key> Begin ();
	  MapIterator<Q, T_item, T_key> End ();
	  uint32_t Size ();
	private:
		List_Order<T_item, T_key> list_[Q + 1];
	  MapIterator<Q, T_item, T_key> iterator_;
};


template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::Begin ()
{
	for (int32_t q = Q; q >= 0; q--) {
		iterator_.iterator_[q] = list_[q].Begin();
	}
	return iterator_;
}

template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::End ()
{
	for (int32_t q = Q; q >= 0; q--) {
		iterator_[q]->iterator = list_[q].End();
	}
	return iterator_;
}

template <const int Q, typename T_item, typename T_key>
uint32_t Map<Q, T_item, T_key>::Size ()
{
	return list_[0].Size();
}


template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key>::Map (){}
/*
template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key>::~List_Order (){}
*/

template <const int Q, typename T_item, typename T_key>
void Map<Q, T_item, T_key>::operator ()()
{
	
}

template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key> &Map<Q, T_item, T_key>::operator + (T_item &item)
{
	for (int32_t q = Q; q >= 0; q--) {
		  list_[q] + item;
	}
  return (*this);
}

template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key> &Map<Q, T_item, T_key>::operator + (T_item *item)
{
	T_item &lval = *item;
  return (*this) + lval;
}

template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key> &Map<Q, T_item, T_key>::operator - (MapIterator<Q, T_item, T_key> &item)
{

  return (*this);	
}

template <const int Q, typename T_item, typename T_key>
Map<Q, T_item, T_key> &Map<Q, T_item, T_key>::operator - (MapIterator<Q, T_item, T_key> *item)
{
	T_item &lval = item;
	return (*this) - lval;
}


template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::Pick (uint32_t n)
{
  for (int32_t q = Q; q >= 0; q--) {
		  iterator_[q]->node_ = list_[q].Pick(n);
	}
	return iterator_;
}

template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::PickNext (MapIterator<Q, T_item, T_key> &item, uint32_t q)
{
	if (q >= Q) {
		q = Q - 1;
	} else {}
	item.iterator[q] = list_[q].PickNext(item.iterator[q]);
	return item;
}

template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::PickNext (MapIterator<Q, T_item, T_key> *item, uint32_t q)
{
	if (q >= Q) {
		q = Q - 1;
	} else {}
	item->iterator[q] = list_[q].PickNext(item->iterator[q]);
	return item;
}

template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::PickPrev (MapIterator<Q, T_item, T_key> &item, uint32_t q)
{
	if (q >= Q) {
		q = Q - 1;
	} else {}
	item.iterator[q] = list_[q].PickPrev(item.iterator[q]);
	return item;
}

template <const int Q, typename T_item, typename T_key>
MapIterator<Q, T_item, T_key> Map<Q, T_item, T_key>::PickPrev (MapIterator<Q, T_item, T_key> *item, uint32_t q)
{
	if (q >= Q) {
		q = Q - 1;
	} else {}
	item->iterator[q] = list_[q].PickPrev(item->iterator[q]);
	return item;
}

};
#endif /*MAP_TEMPLATE_H*/

/*End Of File*/

