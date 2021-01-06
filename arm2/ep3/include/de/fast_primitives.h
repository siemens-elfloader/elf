
#ifndef __FAST_PRIMITIVES_H__
#define __FAST_PRIMITIVES_H__

#include <de/fast_primitives32.h>
#include <de/fast_primitives16.h>
#include <de/pixtypes.h>



__inl
void plPutPixel(image_t *img, int x, int y, color32_t c)
{
    if( x < 0 || y < 0 || x >= img->w || y >= img->h ) return;
    switch(img->bpnum)
    {
    case 32:
        plPutPixel32f(img, x, y, c);
        break;

    case 16:
        plPutPixel16f(img, x, y, rgb32ToRgb16(c));
        break;
    }
}


__inl
void plPutPixelf(image_t *img, int x, int y, color32_t c)
{
    switch(img->bpnum)
    {
    case 32:
        plPutPixel32f(img, x, y, c);
        break;

    case 16:
        plPutPixel16f(img, x, y, rgb32ToRgb16(c));
        break;
    }
}


__inl
void plPutPixelBlend(image_t *img, int x, int y, color32_t c)
{
    if( x < 0 || y < 0 || x >= img->w || y >= img->h ) return;
    switch(img->bpnum)
    {
    case 32:
        plPutPixelBlend32f(img, x, y, c);
        break;

    case 16:
        plPutPixelBlend16f(img, x, y, rgb32ToRgb16(c), plAlpha(c));
        break;
    }
}


__inl
void plPutPixeli(image_t *img, int i, color32_t c)
{
    if(i < 0) return;

    switch(img->bpnum)
    {
    case 32:
        if(i > plCalcSeek(img->w, img->h, img)*4) return;
        plPutPixel32if(img, i, c);
        break;

    case 16:
        if(i > plCalcSeek(img->w, img->h, img)*2) return;
        plPutPixel16if(img, i, rgb32ToRgb16(c));
        break;
    }
}


__inl
void plPutPixelif(image_t *img, int i, color32_t c)
{
    switch(img->bpnum)
    {
    case 32:
        plPutPixel32if(img, i, c);
        break;

    case 16:
        plPutPixel16if(img, i, rgb32ToRgb16(c));
        break;
    }
}


__inl
void plPutPixelBlendi(image_t *img, int i, color32_t c)
{
    if(i < 0) return;
    switch(img->bpnum)
    {
    case 32:
        if(i > plCalcSeek(img->w, img->h, img)*4) return;
        plPutPixelBlend32if(img, i, c);
        break;

    case 16:
        if(i > plCalcSeek(img->w, img->h, img)*2) return;
        plPutPixelBlend16if(img, i, rgb32ToRgb16(c), plAlpha(c));
        break;
    }
}

__inl
void plPutPixelBlendif(image_t *img, int i, color32_t c)
{
    switch(img->bpnum)
    {
    case 32:
        plPutPixelBlend32if(img, i, c);
        break;

    case 16:
        plPutPixelBlend16if(img, i, rgb32ToRgb16(c), plAlpha(c));
        break;
    }
}


__inl
void plPutPixela(image_t *img, int x, int y, color32_t c)
{
    if(img->blend && plAlpha(c))
    {
        plPutPixelBlend(img, x, y, c);
    } else
    {
        plPutPixel(img, x, y, c);
    }
}



#endif
