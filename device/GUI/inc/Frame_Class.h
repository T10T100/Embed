#include "GUI_defs.h"
#include "geometry.h"
#include "memory_template.h"
#include "misc/src/List.cpp"

template <typename T>
struct frame_data_t {
	ColorTypeDef *Frame;
	T W, H;
	T glo_x, glo_y;
};



template <typename T>
	class Frame2D : public List_Node<Frame2D<T>, uint8_t>{
	public:
		Frame2D ();
	  void operator () (b2D);
	  void operator () (b2D, ColorTypeDef *);
	  b2D GetRect ();
	  float GetH ();
	  float GetW ();
	  ColorTypeDef *GetBuff ();
	  ColorTypeDef *GetBuff (b2D);
	  void FillDMA (ColorTypeDef = StdColBlack);
	private:
    frame_data_t<T> Data;
	  virtual void DmaTransfer (ColorTypeDef *, ColorTypeDef *, uint32_t);
	  ColorTypeDef PointToFill;
};

template <typename T>
	class Frame2DManager : public List_Iterator<Frame2D<T> > ,
		                     public Allocator<Frame2D<T> >     {
	public:
		Frame2DManager ();
	  void operator () ();
	  Frame2D<T> *Create (b2D);
	  Frame2D<T> *Access (uint32_t);
	private:
};


/*End Of File*/
