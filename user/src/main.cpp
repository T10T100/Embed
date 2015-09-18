#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "init.h"
#include "device.h"
#include "texture_Img.h"
#include <Texture_Small_0.h>
#include "Wall0.h"
#include "Font.h"
#include "extern.h"
#include "memory_template.h"
#include "physic.h"
using namespace Physic;

uint16_t c = 0;

ColorTypeDef *addr;


uint16_t color = 0;
Frame2D<gbasic_t> *frame;

Bounce bounce_0, bounce_1;
Bounce bounce_2, bounce_3;
Bounce bounce_4, bounce_5;
Ball2D ball_0;
Screen *screen;
Ball2DGroup BallGr;
StarDust dust;
DustPart parts[1025];
int main ()
{
	HAL_Init();
  HAL_Delay(500);
  SystemClock_Config();
  ClockEnable();
  HsramInit();
  DmaInit();
  //SpiInit();
  GpioInit();
	
	Heap((void *)0x60000000, 0xEFFFF);
	
	b2D rect = {0, 0, WDX, 512}, LcdDrvRect = {0, 0, WDX, 320};
	FrameManager();
	frame = FrameManager.Create(rect);
	rect.x = 0;
	rect.y = 0;
	rect.h = 460;
	rect.w = 460;
	
	ScreenMang();
	screen = ScreenMang.Create(rect, frame);
	//rect.y = 250;
	Screen *screen0 = ScreenMang.Create(rect, frame);
	
	screen->Print.UseFont(&Font);
	TFT.Init(0);
	TFT.Backlight(); 
	rect.h = 100;
	rect.w = 100;
	rect.x = 100;
	rect.y = 50;
	float A = 0;//(float *)Heap.New(4);
	b2D rect0 = {0, 0, 50, 50};
	uint16_t counter = 0, c = 0;
	b2D r= {0, 0, 400, 300};
	rect.h = 100;
    rect.w = 100;
    rect.x = 100;
	rect.y = 50;
	b2D rot = {0, 0, 50, 50};
    tTexture *tex1;
    tex1 = screen->MakeTexture(rot);
    tTexture *tex2;
    tex2 = screen->MakeTexture(rot);
    f2P point = {0.0F, 0.0F};
    BallGr(rect0, 15.0F, 10.0F);
    BallGr.Add(20);
    float a = 1.0F;
	dust.SetUp(parts, *Font.CharArray[36].Image, 500);
	dust.SetUp(parts, Image0, 800);	
	while (1) {	
		counter++;
		if (0) {
			
		}
          screen->Fill.Fill(0x0000);
		      
          
		      
          screen->Bitmap.Fill(tex1);
          screen->Bitmap.NewBitmapOpen(*tex1);
              BallGr.Draw();
              //screen->Rectangle.Draw(rect0, 0xaa00);
          screen->Bitmap.NewBitmapClose();
		      BallGr.Step();
          //screen->Bitmap.Rotate(tex2, tex1, a);
          screen->Bitmap.SetScale(3, 2);
          screen->Bitmap.Tile(r, tex1);
		      //screen->Bitmap.Draw(0, 0, &Wall0);
		      //screen->Bitmap.SetScale(0, 0);
		      screen->Bitmap.SetScale(0, 0);
		      //screen->Print.String(Heap.PrintTable());
          //BallGr.Step();
          //BallGr.Draw();
          
          
      //LcdDrvRect.y = counter++ % 190;
		  
		  TFT.Fill(*frame, LcdDrvRect);
	}
  return 0;
}

void Ball2DGroup::Draw (f2P p, float R, uint32_t color)
{
    screen->Circle.Draw(p.x, p.y, R / 2, color);
	  //screen->Rectangle.Draw(r, color);
}

int32_t StarDust::Draw (float x, float y, uint32_t color)
{
    return screen->Pixel(x, y, color);
}

uint32_t StarDust::ReadPixel (float x, float y)
{
    return screen->Pixel(x, y);
}

uint32_t StarDust::ReadAround (float x, float y)
{
    return screen->PixelsAround(x, y);
}

