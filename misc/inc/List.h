
#include <stdint.h>

template <class T, typename K>
	class List_Node {
		public:
			T *rlink, *llink;
		  K key;
		  //virtual bool TestWith (K &);
	};

template <class T>
  class List_Iterator {
	  public:
	  	List_Iterator ();
	    bool operator +  (T &);
	    T *operator -  (T &);
		  bool operator +  (T *);
	    T *operator -  (T *);
		template <typename A>
		  List_Iterator &operator + (A &);
		template <typename A>
		  List_Iterator &operator + (A *);
		template <typename A>
		  List_Iterator &Array (A &, uint32_t);
		template <typename A>
		  List_Iterator &Array (A *, uint32_t);
		  /*
	    bool operator << (T &);
	    bool operator >> (T &);
		  */
	    T *Get (uint32_t index);
	    T *GetLast ();
      T *GetFirst ();
      T *GetNext (T *);
	    int32_t Put (T &, uint32_t index);
	    T *Remove (uint32_t index);
		  int32_t Remove (T *);
		  int32_t Remove (T &);
	    uint32_t Contain ();
	  private:
		  T *First, *Last;
	    uint32_t Elements;
  };

