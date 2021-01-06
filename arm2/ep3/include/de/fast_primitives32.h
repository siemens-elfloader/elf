

#ifndef __FAST_PRIMITIVES32_H__
#define __FAST_PRIMITIVES32_H__

#include  <de/pixtypes.h>
#include  <de/pixmap.h>



/* blending two color with alpha chanel */
color32_t plAlphaBlend32(color32_t color, color32_t background, uint8_t alpha);


/* put color */
__inl
void plPutPixel32(image_t *img, int x, int y, color32_t c)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 32) return;
    color32_t *map = (color32_t *)img->bitmap;
    map[ plCalcSeek(x, y, img) ] = c;
}


__inl
void plPutPixel32i(image_t *img, int i, color32_t c)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*4) return;
    color32_t *map = (color32_t *)img->bitmap;
    map[i] = c;
}


/* put color with blend */
__inl
void plPutPixelBlend32(image_t *img, int x, int y, color32_t c)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 32) return;
    color32_t *map = (color32_t *)img->bitmap;

    uint32_t s = plCalcSeek(x, y, img);
    map[s] = plAlphaBlend32(c, map[s], plAlpha(c));
}


__inl
void plPutPixelBlend32i(image_t *img, int i, color32_t c)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*4) return;
    color32_t *map = (color32_t *)img->bitmap;
    map[i] = plAlphaBlend32(c, map[i], plAlpha(c));
}


__inl
color32_t plGetPixel32(image_t *img, int x, int y)
{
    if(x < 0 || y < 0 || x >= img->w || y >= img->h || img->bpnum != 32) return 0;
    color32_t *map = (color32_t *)img->bitmap;
    return map[plCalcSeek(x, y, img)];
}


__inl
color32_t plGetPixel32i(image_t *img, int i)
{
    if(i < 0 || i > plCalcSeek(img->w, img->h, img)*4) return 0;
    color32_t *map = (color32_t *)img->bitmap;
    return map[i];
}


/* терь тоже самое но без проверок */
__inl
void plPutPixel32f(image_t *img, int x, int y, color32_t c)
{
    color32_t *map = (color32_t *)img->bitmap;
    map[ plCalcSeek(x, y, img) ] = c;
}

__inl
void plPutPixel32if(image_t *img, int i, color32_t c)
{
    color32_t *map = (color32_t *)img->bitmap;
    map[i] = c;
}

__inl
void plPutPixelBlend32f(image_t *img, int x, int y, color32_t c)
{
    color32_t *map = (color32_t *)img->bitmap;
    uint32_t s = plCalcSeek(x, y, img);
    uint8_t alpha = plAlpha(c);
    if(alpha != 0xFF)
        map[s] = plAlphaBlend32(c, map[s], plAlpha(c));
    else
        map[s] = c;
}

__inl
void plPutPixelBlend32if(image_t *img, int i, color32_t c)
{
    color32_t *map = (color32_t *)img->bitmap;
    map[i] = plAlphaBlend32(c, map[i], plAlpha(c));
}

__inl
color32_t plGetPixel32f(image_t *img, int x, int y)
{
    color32_t *map = (color32_t *)img->bitmap;
    return map[plCalcSeek(x, y, img)];
}

__inl
color32_t plGetPixel32if(image_t *img, int i)
{
    color32_t *map = (color32_t *)img->bitmap;
    return map[i];
}


#endif









