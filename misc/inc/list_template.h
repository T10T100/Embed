#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H
#include <stdint.h>
#include "memory_template.h"

#include "misc/src/list.cpp"

template <typename T_item, typename T_key>
class Node {
	public:
		Node *rlink, *llink;
	  T_item *item_;
	  T_key key;
	private:
};

template <typename T_item, typename T_key>
class LNode {
	public:
	  Node<T_item, T_key> node_; 	
	private:
};

template <typename T_item, typename T_key>
class List_Order : public Allocator <Node<T_item, T_key> >    ,
                   public List_Iterator<Node<T_item, T_key> > {
  protected:
	  List_Order ();
	  ~List_Order ();
	public:
		void operator () ();
	  List_Order &operator + (T_item &);
	  List_Order &operator + (T_item *);
	  List_Order &operator - (T_item &);
	  List_Order &operator - (T_item *);
	  T_item *Pick (uint32_t);
	  T_item *PickPrev (T_item &);
	  T_item *PickPrev (T_item *);
	  T_item *PickNext (T_item *);
	  T_item *PickNext (T_item &);
	  uint32_t Contain ();
	  
	  T_item *GetFirst ();
	  T_item *GetLast ();
	private:
	  
};

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
	lNode *node = this->New();
	if (! lNode) {
		  return (*this);
	} else {}
	node->item_ = *item;
	item.node_ = node;
	(*this) + node;
  return (*this);
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator + (T_item *item)
{
	T_item &lval = item;
  return (*this) + item;
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator - (T_item &item)
{
	Node *node = item.node_;
	if (! lNode) {
		  return (*this);
	} else {}
	(*this) - node;
	this->Delete(node);
  return (*this);	
}

template <typename T_item, typename T_key>
List_Order<T_item, T_key> &List_Order<T_item, T_key>::operator - (T_item *item)
{
	T_item &lval = item;
	return (*this) - item;
}


template <typename T_item, typename T_key>
T_item *List_Order<T_item, T_key>::Pick (uint32_t n)
{
	return this->Get(n)->item;
}

template <typename T_item, typename T_key>
T_item *List_Order<T_item, T_key>::PickNext (T_item &item)
{
	return this->GetNext(item.node_);
}

template <typename T_item, typename T_key>
T_item *List_Order<T_item, T_key>::PickNext (T_item *item)
{
	return this->GetNext(item->node_);
}

template <typename T_item, typename T_key>
T_item *List_Order<T_item, T_key>::PickPrev (T_item &item)
{
	return this->GetPrev(item.node_);
}

template <typename T_item, typename T_key>
T_item *List_Order<T_item, T_key>::PickPrev (T_item *item)
{
	return this->GetPrev(item->node_);
}
#endif /*LIST_TEMPLATE_H*/

/*EndOf File*/

