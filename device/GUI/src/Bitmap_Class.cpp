#ifndef BITMAP_CLASS_CPP
#define BITMAP_CLASS_CPP

#ifdef SOFTWARE_GL

#include "bitmap_class.h"

template <typename T>
Bitmap_Class<T>::Bitmap_Class ()
{
}
		
template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::DrawNoScale (b2D rect, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	this->Screen->Trunc(&rect);
	uint32_t gh = this->H;
  uint32_t x = rect.x * gh, xi = 0;
	uint32_t w = GUI_min(rect.w, image->W);
	uint32_t h = GUI_min(rect.h, image->H);
	int32_t y0 = rect.y;
	uint32_t iw = image->W;
	
	ColorTypeDef *dest = this->Frame;
  const ColorTypeDef *src = image->Image;
	
  uint32_t S = h * iw;
  ColorTypeDef target = color;
	if (color != StdColBlack) {
		for (; xi < w; x += gh, xi++) {  
			for (uint32_t y = y0 + x, yi = xi, t = S + xi; yi < t; y++, yi += iw) {
				target = src[yi];
				if (target != color) {
					dest[y] = target;   
				} else {}
			}
		}
  } else {
		for (; xi < w; x += gh, xi++) {  
			for (uint32_t y = y0 + x, yi = xi, t = S + xi; yi < t; y++, yi += iw) {
					dest[y] = src[yi];   
			}
		}
	}
	
	return 0;
}

template <typename T> template <typename img_d, typename img_t>
int32_t Bitmap_Class<T>::Copy (b2D rect, img_d *img_dest, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	
  uint32_t x = rect.x * img_dest->H, xi = 0;
	uint32_t w = image->W;
	uint32_t h = image->H;
	
  register int32_t wd = img_dest->W;
		
	register const ColorTypeDef *src = image->Image;
	register ColorTypeDef *dest = img_dest->Image;
	
  uint32_t S = h * w;
  ColorTypeDef target = color;
	
	if (color != StdColBlack) {
		for (; xi < w; x++, xi++) {  
			for (uint32_t y = rect.y, yi = 0; yi < S; y += wd, yi += w) {
				target = src[xi + yi];
				if (target != color) {
					dest[y + x] = target;   
				} else {}
			}
		}
  } else {	
		for (; xi < w; x++, xi++) {  
			for (uint32_t y = rect.y, yi = 0; yi < S; y += wd, yi += w) {
					dest[y + x] = src[xi + yi];   
			}
		}
	}
	return 0;
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::DrawScaled (b2D rect, img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	if (!this->scale_x || !this->scale_y) {
		  return this->DrawNoScale(rect, image, color);
	}
	rect.w = image->W * this->scale_x;
	rect.h = image->H * this->scale_y;
	this->Screen->Trunc(&rect);
	
	register uint32_t h  = this->H;
	register uint32_t ys = this->scale_y;
	register uint32_t xs = this->scale_x;
	register uint32_t xt = rect.w / xs;
	register uint32_t yt = rect.h / ys;	
	
  register uint32_t S = yt * image->W;
	register ColorTypeDef *target = this->Frame;
	register const ColorTypeDef *source = image->Image;
	ColorTypeDef targ = color;
	register uint32_t ws = image->W;
	if (color == StdColBlack) {
		for (uint32_t xi = 0, x = rect.x * h; xi < xt; xi++) { 
				for (uint32_t d = x + xs * h; x < d; x += h) {
						for (uint32_t y = rect.y + 1, yi = 0; yi < S; yi += ws) {
								for (uint32_t d = y + ys; y < d; y++) {
									 target[y + x] = source[xi + yi]; 
								}
						}
				}
		}	
  }	else {
		for (uint32_t xi = 0, x = rect.x * h; xi < xt; xi++) { 
				for (uint32_t d = x + xs * h; x < d; x += h) {
						for (uint32_t y = rect.y + 1, yi = 0; yi < S; yi += ws) {
								for (uint32_t d = y + ys; y < d; y++) {
									  targ = source[xi + yi];
									  if (targ != color) {
										    target[y + x] = targ;
										} else {}	
								}
						}
				}
		}			
	}
	return 0;
}


template <typename T> template <typename dest_t, typename src_t>
dest_t *Bitmap_Class<T>::ShiftRight (dest_t *dest, src_t *src, uint32_t w, float A, ColorTypeDef color)
{
	int32_t S = w * w;
	int32_t C = (int32_t)((float)(w / 2) * A) * w;
	
	int32_t xi = 0;
	float j;
	int32_t yi = 0;
	int32_t t = 0;
	int32_t W = w + C;
  for (yi = 0, j = 0; yi < w; yi++, j += A) {  
		for (xi = yi, t = S + yi; xi < t; xi += w) {
				dest[xi - (int32_t)(j) * w + C] = src[xi];   
		}
	}
	return dest;
}

template <typename T> template <typename dest_t, typename src_t>
dest_t *Bitmap_Class<T>::ShiftLeft (dest_t *dest, src_t *image, uint32_t w, float A, ColorTypeDef color)
{
	return this->ShiftRight(dest, image, w, -A, color);
}

template <typename T> template <typename dest_t, typename src_t>
dest_t *Bitmap_Class<T>::ShiftDown (dest_t *dest, src_t *src, uint32_t w, float A, ColorTypeDef color)
{
	int32_t S = w * w;
	int32_t C = -(int32_t)((float)(w / 2) * A);
	
	int32_t xi = S;
  for (float j = 0; xi > 0; xi -= w, j -= A) {  
		for (int32_t c = ((int32_t)(j) - C), t = w + xi, yi = xi; yi < t; yi++) {
				dest[yi + c] = src[yi];   
		}
	}
	return dest;
}

template <typename T> template <typename dest_t, typename src_t>
dest_t *Bitmap_Class<T>::ShiftUp (dest_t *dest, src_t *image, uint32_t w, float A, ColorTypeDef color)
{
	return this->ShiftDown(dest, image, w, -A, color);
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::FlipVertical (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t hd = img_dest->H;
  uint32_t S = h * img_src->W;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t x = 0, xi = w;
		for (; xi > 0; x += hd, xi--) {  
			for (uint32_t y = 0, yi = 0; yi < S; y++, yi += w) {
					target[y + x] = src[xi + yi];   
			}
		}
	return img_src;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::FlipHorizontal (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
	uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t hd = img_dest->H;
    uint32_t S = h * img_src->W;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t x = 0, xi = w;
		for (; xi > 0; x += hd, xi--) {  
			for (uint32_t y = 0, yi = 0; yi < S; y++, yi += w) {
					target[y + x] = src[xi + yi];   
			}
		}
	return img_src;
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ShrinkX (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t wd = img_dest->W;
  uint32_t S = h * w;
	ColorTypeDef *target = img_dest->Image;
	const ColorTypeDef *src = img_src->Image;
	float Ax = 0, An = 0;;
	
	uint32_t x = 0, xi = 0;
	/*
			for (; xi < w; x++, xi++) {  
			for (uint32_t y = rect.y, yi = 0; yi < S; y += wd, yi += w) {
					dest[y + x] = src[xi + yi];   
			}
		}
	*/
		for (x = 0, xi = 0; xi < S; xi += w) {  
			Ax += A;
			if ((Ax - An) > 1.0F) {
				An += 1.0F;
				for (uint32_t y = x, yi = xi, t = h + xi; yi < t; y += wd, yi++) {
						target[y] = src[yi];   
				}
				x++;
		  } else {}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ShrinkY (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t wd = img_dest->W;
  uint32_t S = h * img_src->W;
	ColorTypeDef *target = img_dest->Image;
	const ColorTypeDef *src = img_src->Image;
	float Ay = 0, An = 0;
	
	uint32_t x = 0, xi = 0;
		for (uint32_t y = 0, yi = 0; yi < S; yi += w) {  
			Ay += A;
			if ((Ay - An) > 1.0F) {
				An += 1;
				for (x = y, xi = yi; xi < w + yi; x++, xi++) {
						target[x] = src[xi];   
				}
				y += wd;
		  } else {}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ExpandX (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t wd = img_dest->W;
  uint32_t S = h * w;
	ColorTypeDef *target = img_dest->Image;
	const ColorTypeDef *src = img_src->Image;
	if (A != 0) {
	  A = (1.0F - 1 / A);
	}
	float Ax = 0, An = 0;
	
	uint32_t x = 0, xi = 0;
		for (; xi < w; x++) {  
			Ax += A;
			if ((Ax - An) > 1.0F) {
				An += 1.0F;
		  } else {
			    xi++;
			}
			for (uint32_t y = x, yi = xi, t = S + xi; yi < t; y += wd, yi += w) {
						target[y] = src[yi];   
			}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ExpandY (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
	uint32_t h = img_src->H;
	uint32_t wd = img_dest->W;
  uint32_t S = h * w;
	ColorTypeDef *target = img_dest->Image;
	const ColorTypeDef *src = img_src->Image;
	if (A != 0) {
	  A = (1.0F - 1 / A);
	}
	float Ax = 0, An = 0;
	
	uint32_t x = 0, xi = 0;
		 for (uint32_t y = 0, yi = 0; yi < S; y += wd){  
			Ax += A;
			if ((Ax - An) > 1.0F) {
				An += 1.0F;
		  } else {
			    yi += w;
			}
			for (x = y, xi = yi; xi < w + yi; x++, xi++) {
				  target[x] = src[xi];   
			}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ResizeY (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (A > 1.0F) {
		return this->ExpandY(img_dest, img_src, A, color);
	} else {
		return this->ShrinkY(img_dest, img_src, A, color);
	}
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::ResizeX (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	if (A > 1.0F) {
		return this->ExpandX(img_dest, img_src, A, color);
	} else {
		return this->ShrinkX(img_dest, img_src, A, color);
	}
}

template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::Resize (img_d *dest, img_t *src, float A, float B, ColorTypeDef color)
{
	gbasic_t w = (uint32_t)abs(floor((float)src->W * A));
	gbasic_t h = (uint32_t)abs(floor((float)src->H * B));
	b2D rect = {0, 0, w, h};
	return this->Resize(rect, dest, src, color);
}


template <typename T> template <typename img_t, typename img_d>
	img_d *Bitmap_Class<T>::Resize (b2D rect, img_d *img_dest, img_t *img_src, ColorTypeDef color)
{
	tTexture *texture = this->Screen->MakeTexture(90, 90);
	if (! texture) {
		return img_src;
	} else {}
	texture->H = img_src->H;
	texture->W = rect.w;
	img_dest->W = rect.w;
	img_dest->H = rect.h;
	float A = (float)rect.w / (float)img_src->W;
	float B = (float)rect.h / (float)img_src->H;
	
	this->Fill(texture);	
	this->ResizeX(texture, img_src, A);	
	this->Fill(img_dest);
	this->ResizeY(img_dest, texture, B);	
	
	this->Screen->KillTexture(texture);
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::Rotate90 (img_d *img_dest, img_t *img_src, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	uint32_t w = img_src->W;
  uint32_t S = w * w;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t xi = 0;
		for (; xi < S; xi += w) {  
			for (uint32_t y = xi, yi = w + xi; yi > xi; y++, yi--) {
					target[y] = src[yi];   
			}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::Rotate180 (img_d *img_dest, img_t *img_src, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
	uint32_t w = img_src->W;
  uint32_t S = w * w;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t x = 0, xi = w;
		for (; xi > 0; x += w, xi--) {  
			for (uint32_t y = x, yi = S + xi; yi > xi; y++, yi -= w) {
					target[y] = src[yi];   
			}
		}
	return img_src;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::Rotate270 (img_d *img_dest, img_t *img_src, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;

	uint32_t w = img_src->W;
  uint32_t S = w * w;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t x = 0, xi = S;
		for (; xi > 0; x += w, xi -= w) {  
			for (uint32_t y = x, yi = xi, t = w + xi; yi < t; y++, yi++) {
					target[y] = src[yi];   
			}
		}
	return img_dest;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::Rotate0 (img_d *img_dest, img_t *img_src, ColorTypeDef color)
{
	if (this->Screen->Test()) return img_dest;
	
  uint32_t w = img_src->W;
  uint32_t S = w * w;
	ColorTypeDef *target = img_dest->Image;
	ColorTypeDef *src = img_src->Image;
	
	uint32_t x = 0, xi = 0;
		for (; xi < w; x += w, xi++) {  
			for (uint32_t y = x, yi = xi, t = S + xi; yi < t; y++, yi += w) {
					target[y] = src[yi];   
			}
		}
	return img_src;
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Tile (b2D rect, img_t *image, ColorTypeDef color)
{
	
	if (this->Screen->Test()) return -1;
	
	this->Screen->Trunc(&rect);
	uint32_t x0 = rect.x;
	uint32_t y0 = rect.y;
	uint32_t w  = rect.w + x0;
	uint32_t h  = rect.h + y0;
	uint32_t img_w = image->W;
	uint32_t img_h = image->H;
	uint32_t cut_x = 0;
	uint32_t cut_y = 0;
	uint32_t h0 = this->H;
	uint32_t t_y;
	
	ColorTypeDef *target = this->Frame;
	ColorTypeDef *src = image->Image;
	if (color == StdColBlack) {
		for (; x0 < w; x0 += img_w) {
				t_y = y0;
			for (; y0 < h; y0 += img_h) {
					uint32_t __x = x0 * h0;
					uint32_t xi = 0;	
					uint32_t i = w - x0;
					if (i < img_w) {
							cut_x = i;
					} else {
							cut_x = img_w;
					}
					i = h - y0;
					if (i < img_h) {
						 cut_y = i;
					} else {
					cut_y = img_h;
					}
					uint32_t S = cut_y * img_w;
					for (; xi < cut_x; __x += h0, xi++) {  
							for (uint32_t __y = y0, yi = 0; yi < S; __y++, yi += img_w) {
									target[__y + __x] = src[xi + yi];   
							}
					}
			}
			y0 = t_y;
		}
  } else {
		for (ColorTypeDef tcol = 0; x0 < w; x0 += img_w) {
				t_y = y0;
			for (; y0 < h; y0 += img_h) {
					uint32_t __x = x0 * h0;
					uint32_t xi = 0;	
					uint32_t i = w - x0;
					if (i < img_w) {
							cut_x = i;
					} else {
							cut_x = img_w;
					}
					i = h - y0;
					if (i < img_h) {
						 cut_y = i;
					} else {
					cut_y = img_h;
					}
					uint32_t S = cut_y * img_w;
					for (; xi < cut_x; __x += h0, xi++) {  
							for (uint32_t __y = y0, yi = 0; yi < S; __y++, yi += img_w) {
								  tcol = src[xi + yi];
								  if (tcol != color) {
									    target[__y + __x] = tcol;
									} else {}									
							}
					}
			}
			y0 = t_y;
		}		
	}
	return 0;
}

template <typename T>
void Bitmap_Class<T>::SetScale (b2D rect)
{
  this->scale_x = (uint8_t)rect.x;
	this->scale_y = (uint8_t)rect.y;
	this->BlendLevel = 0;
}	

template <typename T>
void Bitmap_Class<T>::SetScale (float x, float y)
{
  this->scale_x = (uint8_t)x;
	this->scale_y = (uint8_t)y;
	this->BlendLevel = 0;
}	

template <typename T>
void Bitmap_Class<T>::setBlendLevel (uint8_t level)
{
	 this->BlendLevel = level;
}

template <typename T>
int32_t Bitmap_Class<T>::NewBitmapOpen (tTexture &texture)
{
	if (this->Screen->Test()) return -1;
	uint8_t memo[sizeof(Frame2D<gbasic_t>)];
	Frame2D<gbasic_t>  *TempFrameDataPack = (Frame2D<gbasic_t> *)memo;
	
	this->TempFrameDataPackP = this->Screen->GetFrame();
	this->TempFrameDataRect  = this->Screen->GetRect();
    b2D rect = {0, 0, texture.W, texture.H};
	(*TempFrameDataPack)(rect, texture.Image);
	(*this->Screen)(rect, *TempFrameDataPack, 0);
	
	return 0;
}

template <typename T>
int32_t Bitmap_Class<T>::NewBitmapClose ()
{
	if (this->Screen->Test()) return -1;
	(*this->Screen)(this->TempFrameDataRect, *this->TempFrameDataPackP, 0);
	
	return 0;
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Fill (img_t *image, ColorTypeDef color)
{
	if (this->Screen->Test()) return -1;
	
	ColorTypeDef *target = image->Image;
	for (uint32_t D = image->W * image->H; D > 0; D--)
	    target[D] = color;
	return 0;
}

template <typename T> template <typename img_t, typename img_d>
img_d *Bitmap_Class<T>::Rotate (img_d *img_dest, img_t *img_src, float A, ColorTypeDef color)
{
	float D = ((float)GUI_max(img_src->H, img_src->W) * 2.0F );
	uint32_t w = (int32_t)D;
	img_dest->W = w;
	img_dest->H = w;
    
  tTexture *texture = this->Screen->MakeTexture((int32_t)D, (int32_t)D);
	
	this->Fill(img_dest, StdColWhite);
	this->Copy(img_dest, img_src, color);
	
	float t;
	t = A / (PI_const / 2);
	t = (abs(floor(t)));
	bool sign = false;
	if (A > 0) {
		A -= t * (PI_const / 2);
	} else {
		sign = true;
		A += t * (PI_const / 2);
	}
	this->Fill(&img_dest[1]);
	int32_t j = (int32_t)t % 4;
		if (j == 1) {
			if (sign) {
				this->Rotate270(texture, img_dest);
			} else {
			  this->Rotate90(texture, img_dest);
			}
		} else if (j == 2) {
			this->Rotate180(texture, img_dest);
		} else if (j == 3){
			if (sign) {
				this->Rotate90(texture, img_dest);
			} else {
			  this->Rotate270(texture, img_dest);
			}
		} else {
			this->Rotate0(texture, img_dest);
		}
	A = ((PI_const / 4) - A);
  
  ColorTypeDef *Output = img_dest->Image, *Input = texture->Image;		
		
  this->Fill(img_dest, StdColWhite);
	this->ShiftRight(Output, Input, w, A / 2);
	this->Fill(texture, StdColWhite);
  this->ShiftDown(Input, Output, w, A);
	this->Fill(img_dest, StdColWhite);
  this->ShiftRight(Output, Input, w, A / 2);    
  this->Screen->KillTexture(texture);
	return img_dest;
}


template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Draw (b2D rect, img_t *image, ColorTypeDef color)
{
	return this->DrawScaled (rect, image, color);
}

template <typename T> template <typename img_t>
int32_t Bitmap_Class<T>::Draw (gbasic_t x0, gbasic_t y0, img_t *image, ColorTypeDef color)
{
	b2D rect = {x0, y0, 0, 0};
	return this->DrawScaled (rect, image, color);
}

template <typename T> template <typename img_d, typename img_t>
int32_t Bitmap_Class<T>::Copy (gbasic_t x0, gbasic_t y0,img_d *img_dest, img_t *image, ColorTypeDef color)
{
	b2D rect = {x0, y0, 0, 0};
	return this->Copy (rect, img_dest, image, color);
}

template <typename T> template <typename img_d, typename img_t>
int32_t Bitmap_Class<T>::Copy (img_d *img_dest, img_t *image, ColorTypeDef color)
{
	int32_t x = (img_dest->W - image->W) / 2;
	int32_t y = (img_dest->H - image->H) / 2;
	b2D rect = {x, y, 0, 0};
	return this->Copy (rect, img_dest, image, color);
}
#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif /*BITMAP_CLASS_CPP*/

