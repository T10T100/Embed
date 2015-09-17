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
	*this + screen;
	screen->operator()(rect, *frame);
	return screen;
}

int32_t ScreenManager::Kill (Screen *screen)
{
	if (screen == (Screen *)0) return -1;
	*this - screen;
	this->Delete(screen);
	return 0;
}

int32_t ScreenManager::Refresh (uint32_t flags)
{
	if (this->Test()) return -1;
	register uint32_t i = this->Contain();
	while (i--)
		this->Get(i)->Refresh();
	return 0;
}
