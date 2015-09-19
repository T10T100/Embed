#include "Screen.h"


Screen::Screen (){}
	

void Screen::operator () (b2D rect, Frame2D<gbasic_t> &frame)
{
	
	this->Dispose(rect);
	this->Frame = &frame;
	this->Fill(*this);
	this->Bitmap(*this);
	      this->Bitmap.SetScale(0, 0);
	this->Circle(*this);
	this->Line(*this);
	      this->Line.Init();
	this->Rectangle(*this);
	      this->Rectangle.Init();
	this->Print(*this);
	      this->Print.Init();
    
  this->frame_ = this->Frame->GetBuff();
  this->h_     = this->Frame->GetH();
}

int32_t Screen::Pixel (gbasic_t x, gbasic_t y, ColorTypeDef color)
{
  *(frame_ + (y + Y0) + (x + X0) * h_) = color;
  return 0;    
}

ColorTypeDef Screen::Pixel (gbasic_t x, gbasic_t y)
{
  return *(frame_ + (y + Y0) + (x + X0) * h_);    
}

ColorTypeDef Screen::PixelsAround (gbasic_t x, gbasic_t y)
{
	int32_t tx = (x + X0) * h_;
	int32_t ty = y + Y0;
	int32_t s = tx + ty;
	uint32_t h = h_;
	if (! s) {
		s = 1;
		h = 0;
	} else {}
    if (*(frame_ + y + tx)) {
        return 1;
    } else     if (*(frame_ + s + h)) {
        return 1;
    } else     if (*(frame_ + s - h)) {
        return 1;
    } else     if (*(frame_ + s + 1)) {
        return 1;
    } else     if (*(frame_ + s - 1)) {
        return 1;
    } else     if (*(frame_ + s + 1 + h)) {
        return 1;
    } else     if (*(frame_ + s - 1 - h)) {
        return 1;
    } else     if (*(frame_ + s - 1 + h)) {
        return 1;
    } else     if (*(frame_ + s + 1 - h)) {
        return 1;
    } else {} 
		return 0;
}

int32_t Screen::Refresh ()
{
	return this->Fill.Fill(this->back_color);
}

Frame2D<gbasic_t> *Screen::GetFrame ()
{
	return this->Frame;
}

tTexture *Screen::MakeTexture (gbasic_t w, gbasic_t h)
{
	
  tTexture *texture = this->New<tTexture>((w + 1) * (h + 1) * sizeof(ColorTypeDef));
	texture->Image = (ColorTypeDef *)(texture + 1);
	texture->W = w;
	texture->H = h;
	return texture;
}

tTexture *Screen::MakeTexture (b2D rect)
{
  return this->MakeTexture(rect.w, rect.h);
}

int32_t Screen::KillTexture (tTexture *texture)
{
  return this->Delete(texture);
}




ScreenManager::ScreenManager (){}
	
void ScreenManager::operator () ()
{
	this->Unlock();
}

Screen *ScreenManager::Create (b2D rect, Frame2D<gbasic_t> *frame)
{
	Screen *screen = this->New();
	list_ + screen;
	screen->operator()(rect, *frame);
	return screen;
}

int32_t ScreenManager::Kill (Screen *screen)
{
	if (screen == (Screen *)0) return -1;
	
	//list_ - iterator_;
	//this->Delete(screen);
	return 0;
}

int32_t ScreenManager::Refresh (uint32_t flags)
{
	if (this->Test()) return -1;
	//while (i--)
		//list_.Get(i)->Refresh();
	return 0;
}
