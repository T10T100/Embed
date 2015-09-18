#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H
#include <stdint.h>
#include "memory_template.h"

#include "list.h"

template <typename T_item, typename T_key>
class Node {
	public:
		Node *rlink, *llink;
	  T_item *item_;
	  T_key key;
	private:
};

template <typename T_item, typename T_key>
class Iterator {
	public:
		Node<T_item, T_key> *node_;
    Iterator<T_item, T_key> &operator = (uint32_t);	
	  T_item *Pick ();
	private:		
};

template <typename T_item, typename T_key>
Iterator<T_item, T_key> &Iterator<T_item, T_key>::operator = (uint32_t)
{

}

template <typename T_item, typename T_key>
T_item *Iterator<T_item, T_key>::Pick()
{
    return node_->item_;
}

template <typename T_item, typename T_key>
class List_Order : private Allocator <void> {
  protected:
	  
	public:
		void operator () ();
	  List_Order &operator + (T_item &);
	  List_Order &operator + (T_item *);
	  List_Order &operator - (Iterator<T_item, T_key> &);
	  List_Order &operator - (Iterator<T_item, T_key> *);
	  Iterator<T_item, T_key>Pick (uint32_t);
	  Iterator<T_item, T_key>PickPrev (Iterator<T_item, T_key> &);
	  Iterator<T_item, T_key>PickPrev (Iterator<T_item, T_key> *);
	  Iterator<T_item, T_key>PickNext (Iterator<T_item, T_key> *);
	  Iterator<T_item, T_key>PickNext (Iterator<T_item, T_key> &);
	  uint32_t Size ();
	  
	  Iterator<T_item, T_key> Begin ();
	  Iterator<T_item, T_key> End ();
	  List_Order ();
	  ~List_Order ();
	private:
		List_Iterator< Node<T_item, T_key> > llist_; 
	  
};

template <typename T_item, typename T_key>
Iterator<T_item, T_key> List_Order<T_item, T_key>::Begin ()
{
	Iterator<T_item, T_key> I;
	I.node_ = llist_.GetFirst();
	return I;
}

template <typename T_item, typename T_key>
Iterator<T_item, T_key> List_Order<T_item, T_key>::End ()
{
	Iterator<T_item, T_key> I;
	I->node_ = llist_.GetLast();
	return I;
}

template <typename T_item, typename T_key>
uint32_t List_Order<T_item, T_key>::Size ()
{
	return llist_.Contain();
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key>::List_Order (){}

template <typename T_item, typename T_key>
List_Order<T_item, T_key>::~List_Order (){}

template <typename T_item, typename T_key>
void List_Order<T_item, T_key>::operator ()()
{
	
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator + (T_item &item)
{
	Node<T_item, T_key> *node = this->New< Node<T_item, T_key> >();
	if (! node) {
		  return (*this);
	} else {}
	node->item_ = &item;
	llist_ + node;
  return (*this);
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator + (T_item *item)
{
	T_item &lval = *item;
  return (*this) + lval;
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator - (Iterator<T_item, T_key> &item)
{

  return (*this);	
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator - (Iterator<T_item, T_key> *item)
{
	T_item &lval = item;
	return (*this) - lval;
}


template <typename T_item, typename T_key>
Iterator<T_item, T_key>List_Order<T_item, T_key>::Pick (uint32_t n)
{
	Iterator<T_item, T_key> I;
	I->node_ = llist_.Get(n);
	return I;
}

template <typename T_item, typename T_key>
Iterator<T_item, T_key>List_Order<T_item, T_key>::PickNext (Iterator<T_item, T_key> &item)
{
	item.node_ = llist_.GetNext(item.node_);
	return item;
}

template <typename T_item, typename T_key>
Iterator<T_item, T_key>List_Order<T_item, T_key>::PickNext (Iterator<T_item, T_key> *item)
{
	item->node_ = llist_.GetNext(item->node_);
	return item;
}

template <typename T_item, typename T_key>
Iterator<T_item, T_key>List_Order<T_item, T_key>::PickPrev (Iterator<T_item, T_key> &item)
{
	item.node_ = llist_.GetPrev(item.node_);
	return item;
}

template <typename T_item, typename T_key>
Iterator<T_item, T_key>List_Order<T_item, T_key>::PickPrev (Iterator<T_item, T_key> *item)
{
	item->node_ = llist_.GetPrev(item->node_);
	return item;
}

#endif /*LIST_TEMPLATE_H*/

/*End Of File*/

