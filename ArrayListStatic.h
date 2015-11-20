#ifndef ARRAY_LIST
#define ARRAY_LIST
#include <stdint.h>

#include "memory_template.h"


template <typename Object>
	class DefaultArrayListNode {
		public:
		DefaultArrayListNode (Object &userObject)
		{
			  this->userObject = userObject;
		}
		
		bool equals (DefaultArrayListNode<Object> &node)
		{
			return this.isEquals(this->userObject, node.userObject);
		}
		
		
		private:
		Object &userObject;
		Object &prevLink;
	  Object &nextLink;
		
		virtual bool isEquals (Object thisObject, Object object)
		{
			return false;
		}
	};

	
	template <typename Object>
		class ArrayListStatic {
			public: 
			ArrayListStatic ()
			{
				
			}
			
			Object &add (Object &item)
			{
					this->elementCount++;
					Object &i;
					if (!this->first) {
						this->first = item;
						this->last = item;
						item.nextLink = nullptr;
						item.prevLink = nullptr;
						return item;
					}
					i = *first;
					if (i.prevLink) {
						i.prevLink.nextLink = item;
						item.nextLink = i;
						item.prevLink = i.prevLink;
						i.prevLink = item;	
						return item;	
					}
					item.nextLink = i;
					item.prevLink = nullptr;
					i.prevLink = item;
					this->first = item;
					return item;				
			}
			
			Object &add (Object *item)
			{
				
				return item;
			}
			
			Object &addFirst (Object &item)
			{
				
				
				return item;
			}
			
			Object &addFirst (Object *item)
			{
				
				return item;
			}
			
			Object &addLast (Object &item)
			{
				
				
				return item;
			}
			
			Object &addLast (Object *item)
			{
				
				return item;
			}
			
			ArrayListStatic<Object> &addAll (ArrayListStatic<Object> &arrayList)
			{
				
				return *this;
			}
			
			template <typename Collection>
			ArrayListStatic<Object> &addAll (Collection collection)
			{
				
				return *this;
			}
			
			Object &remove (Object &object)
			{
				
				return object;
			}
			
			Object &remove (Object *object)
			{
				
				return *object;
			}
			
			Object &removeFirst (Object &object)
			{
				
				return object;
			}
			
			Object &removeFirst (Object *object)
			{
				
				return *object;
			}
			
			Object &removeLast (Object &object)
			{
				
				return object;
			}
			
			Object &removeLast (Object *object)
			{
				
				return *object;
			}
			
			void removeAll (ArrayListStatic<Object> &arrayList)
			{
				
			}
			
			
			
			
			
			bool isEmpty ()
			{
				if (this->elementCount > 0) {
					return true;
				} else {
					return false;
				}
			}
			
			uint32_t size ()
			{
				return this->elementCount;
			}
			private:
			uint32_t elementCount;
			Object &firstNode;
			Object &lastNode;
		};
#endif

/*End of file*/

