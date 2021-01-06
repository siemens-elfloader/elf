

#ifndef __FAST_PRIMITIVES16_H__
#define __FAST_PRIMITIVES16_H__

#include  <de/pixtypes.h>
#include  <de/pixmap.h>


/* blending two color with alpha chanel */
color16_t plAlphaBlend16(color16_t _color, color16_t _background, uint8_t alpha);


/* put color */
__inl
void plPutPixel16(image_t *img, int x, int y, color16_t c)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 16) return;
    color16_t *map = (color16_t *)img->bitmap;
    map[ plCalcSeek(x, y, img) ] = c;
}


__inl
void plPutPixel16i(image_t *img, int i, color16_t c)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*2) return;
    color16_t *map = (color16_t *)img->bitmap;
    map[i] = c;
}


/* put color with blend */
__inl
void plPutPixelBlend16(image_t *img, int x, int y, color16_t c, uint8_t alpha)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 16) return;
    color16_t *map = (color16_t *)img->bitmap;

    uint16_t s = plCalcSeek(x, y, img);
    map[s] = plAlphaBlend16(c, map[s], alpha);
}


__inl
void plPutPixelBlend16i(image_t *img, int i, color16_t c, uint8_t alpha)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*2) return;
    color16_t *map = (color16_t *)img->bitmap;
    map[i] = plAlphaBlend16(c, map[i], alpha);
}


__inl
color16_t plGetPixel16(image_t *img, int x, int y)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 16) return 0;
    color16_t *map = (color16_t *)img->bitmap;
    return map[plCalcSeek(x, y, img)];
}


__inl
color16_t plGetPixel16i(image_t *img, int i)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*2) return 0;
    color16_t *map = (color16_t *)img->bitmap;
    return map[i];
}


/* терь тоже самое но без проверок */
__inl
void plPutPixel16f(image_t *img, int x, int y, color16_t c)
{
    color16_t *map = (color16_t *)img->bitmap;
    map[ plCalcSeek(x, y, img) ] = c;
}

__inl
void plPutPixel16if(image_t *img, int i, color16_t c)
{
    color16_t *map = (color16_t *)img->bitmap;
    map[i] = c;
}

__inl
void plPutPixelBlend16f(image_t *img, int x, int y, color16_t c, uint8_t alpha)
{
    color16_t *map = (color16_t *)img->bitmap;
    uint16_t s = plCalcSeek(x, y, img);
    map[s] = plAlphaBlend16(c, map[s], alpha);
}

__inl
void plPutPixelBlend16if(image_t *img, int i, color16_t c, uint8_t alpha)
{
    color16_t *map = (color16_t *)img->bitmap;
    map[i] = plAlphaBlend16(c, map[i], alpha);
}

__inl
color16_t plGetPixel16f(image_t *img, int x, int y)
{
    color16_t *map = (color16_t *)img->bitmap;
    return map[plCalcSeek(x, y, img)];
}

__inl
color16_t plGetPixel16if(image_t *img, int i)
{
    color16_t *map = (color16_t *)img->bitmap;
    return map[i];
}





#endif









