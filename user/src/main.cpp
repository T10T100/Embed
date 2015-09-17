#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "init.h"
#include "device.h"
#include <res/Rose_Img.c>
#include <res/texture_Img.c>
#include <res/Texture_Small_0.c>
#include <res/Wall0.c>
#include <res/Font.c>
#include "extern.cpp"
#include "memory_template.h"
#include "physic.h"
using namespace Physic;

uint16_t c = 0;

ColorTypeDef *addr;


uint16_t color = 0;
Frame2D<gbasic_t> *frame;
ColorTypeDef Tex0[100 * 100 * sizeof(ColorTypeDef)];
ColorTypeDef Tex1[100 * 100 * sizeof(ColorTypeDef)];
tTexture tex0 = {Tex0, 100, 100};
tTexture tex1 = {Tex1, 100, 100};
tTexture tex_case[2] = {tex0, tex1};
tTexture *Texture_Temp0 = (tTexture *)0, *Texture_Bg0 = (tTexture *)0;


Bounce bounce_0, bounce_1;
Bounce bounce_2, bounce_3;
Bounce bounce_4, bounce_5;
Ball2D ball_0;
Screen *screen;
Ball2DGroup BallGr;
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
	b2D rect0 = {0, 0, 450, 450};
	uint8_t counter = 0, c = 0;
	Texture_Temp0->W = 100;
	Texture_Temp0->H = 100;
	b2D r= {0, 0, 100, 100};
	rect.h = 100;
    rect.w = 100;
    rect.x = 100;
	rect.y = 50;
	b2D rot = {0, 120, 200, 200};

    
    f2P point = {0.0F, 0.0F};
    BallGr(rect0, 15.0F, 10.0F);
    BallGr.Add(2);
		for (uint32_t i = 120; i > 0; i--) {
			  BallGr.Add(float(rand() % 30) + 10, (float)counter / 8 + 40, float(counter++) / 100);
		}
	while (1) {	
          screen->Fill.Fill(0x1111);
		      //screen->Bitmap.Draw(0, 0, &Wall0);
		      //screen->Bitmap.SetScale(0, 0);
		      screen->Print.String(Heap.PrintTable());
          BallGr.Step();
          BallGr.Draw();
          screen->Rectangle.Draw(rect0, 0xaa00);
		if (counter++ % 200 == 0) {
			BallGr.Add(40, 0, 1.3F);
		}
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

