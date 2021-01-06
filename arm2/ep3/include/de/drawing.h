
#ifndef __DRAWING_H__
#define __DRAWING_H__

#include <inttypes.h>
#include <stdlib.h>
#include <swilib.h>
#include "pixtypes.h"
#include "freetype.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Flip_Vertical 0x00000001
#define Flip_Horisontal 0x00000002
#define Rotate_90 0x00000004


enum
{
    FT_TEXT_W_LEFT   = (1 << 0),
    FT_TEXT_W_CENTER = (1 << 1),
    FT_TEXT_W_RIGHT  = (1 << 2),

    FT_TEXT_H_UP     = (1 << 3),
    FT_TEXT_H_CENTER = (1 << 4),
    FT_TEXT_H_DOWN   = (1 << 5)
};


static inline image_t *imghdr2image(IMGHDR *img)
{
    if(!img)
        return 0;
    image_t *i = (image_t*)malloc(sizeof(image_t));
    i->w = img->w;
    i->h = img->h;
    i->bpnum = img->bpnum==10?32:16;
    i->bitmap = img->bitmap;
    return i;
}


static inline image_t *imghdr2image_p(IMGHDR *img)
{
    image_t *r = (image_t*)malloc(sizeof(image_t));
    r->w = img->w;
    r->h = img->h;
    r->bpnum = img->bpnum == 10? 32:16;
    r->bitmap = img->bitmap;
    return r;
}


static inline void imghdr2image_c(IMGHDR *imgh, image_t *img)
{
    img->w = imgh->w;
    img->h = imgh->h;
    img->bpnum = imgh->bpnum == 10? 32:16;
    img->bitmap = imgh->bitmap;
}



/* ������ ����� ����������� */
image_t *create_image(uint16_t w, uint16_t h, uint8_t depth);

image_t *image_create_from_png(const char *p, int bpnum);

/* ������������ ����������� */
void free_image(image_t *);

/* create image */
IMGHDR *create_imghdr(uint16_t w, uint16_t h, uint8_t depth);

/* free image */
void free_imghdr(IMGHDR *);

/* push image to screen */
void ll_drawimage(int x, int y, int w, int h, image_t *img);

/* push image to screen */
void drawimage(int x, int y, image_t *img);


void ll_drawimghdr(int x, int y, int w, int h, IMGHDR *img);
void drawimghdr(int x, int y, IMGHDR *img);

/* fork image */
image_t * image_fork(image_t *src);

/* copy image without alpha blend */
void image_copy(image_t * dst, image_t *src);

/* ���������� rgba ����� */
void drawpixel(image_t *buffer, uint16_t x, uint16_t y, const uint8_t color[4]);

/* ���������� ��� ����� + �����*/
void drawpixel24(image_t *buffer, uint16_t x, uint16_t y, const uint8_t color[3], uint8_t alpha);

/* ���������� 16������ ����� */
void drawpixel16(image_t *buffer, uint16_t x, uint16_t y, color16_t color);

/* ���������� 32������ ����� */
void drawpixel32(image_t *buffer, uint16_t x, uint16_t y, color32_t color);

/* ����������� ������� � �������� ��� ����� ������ */
void setpixel32(image_t *buffer, uint16_t x, uint16_t y, color32_t color);

/* ���������� ������� �� ������� � ������� */
void drawpixel32i(image_t *buffer, uint32_t index, color32_t col);

/* ����� ������� �� �����������, ���� ����������� 16 ��� �� ��������� uint16_t */
uint32_t pixel(image_t *buffer, uint16_t x, uint16_t y);

/* ����� 16� ������ ���� �� �������� �� �������� �������� */
uint16_t pixel16(image_t *buffer, uint16_t x, uint16_t y);

/* ����� 32� ������ ���� �� �������� �� �������� �������� */
uint32_t pixel32(image_t *buffer, uint16_t x, uint16_t y);

/* ����� 32� ������ ���� �� ������ �� �������� �� �������� �������� */
uint32_t pixel32i(image_t *buffer, uint32_t index);

/* ��������� ������ 32������ ������ */
void fillscreen(image_t *buffer, color32_t col);

/* ���������� rgba ����� */
void drawline32(image_t *buffer, int16_t x1, int16_t y1,
              int16_t x2, int16_t y2, color32_t color);

/* Draw a horizontal/vertical line (optimised) */
void drawhline32(image_t *buffer, int16_t x1, int16_t x2, int16_t y, color32_t col);
void drawvline32(image_t *buffer, int16_t x, int16_t y1, int16_t y2, color32_t col);

/* ���������� rgba ������������� */
void drawrectangle32(image_t *buffer, int16_t x1, int16_t y1,
                   int16_t x2, int16_t y2, color32_t color);

/* ���������� ����������� rgba ������������� */
void drawfillrect32(image_t *buffer, int16_t x1, int16_t y1,
                  int16_t x2, int16_t y2, color32_t color_rect,
                  color32_t color_inside);



/* ���������� rgba ���������� */
void drawcircle32(image_t *buffer, int16_t x, int16_t y, int16_t r, color32_t color);

/* ���������� ������� ���������� */
void drawfillcircle32(image_t *buffer, int16_t x, int16_t y, int16_t r, color32_t color);

/* ���������� rgba ����� */
void drawellipse32(image_t *buffer, int16_t x, int16_t y, int16_t a, int16_t b, color32_t color);

/* ���������� ����������� */
void drawtriangle32(image_t *buffer, int16_t x1, int16_t y1,
                                  int16_t x2, int16_t y2,
                                  int16_t x3, int16_t y3,
                                  color32_t color);

/* ���������� ����������� ����������� */
void drawfilltriangle32(image_t *buffer, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, color32_t clr);

/* ���������� ������� �������� � ������ */
void ll_drawimg(image_t *buffer, int16_t x, int16_t y, int16_t w, int16_t h, char blend, image_t *img);
void drawimg(image_t *buffer, int16_t x, int16_t y, char blend, image_t *img);
void drawimg_area_to_area(image_t *buffer, int16_t x, int16_t y, int16_t width, int16_t height,
                           int16_t x2, int16_t y2, char blend, image_t *img);

/* ������� ����� �������� ����� ���������. � �������� conv ��������� ������� ����������� ������� ����� ��������� � ucs2  */
/* � ������� ��������� ��������� �� ��������� ������, ��� ������ ���������� ucs2 ������ � �������� ��������� */
/* ������+(������� ������ ������ ����� ���������). ������� ����� ���������� � ���������� */
uint16_t drawstring(ft_font *ftf, image_t *buffer, const wchar_t *str, int16_t x, int16_t y,
                        int mw, int mh, int type, uint8_t leter_step, int32_t max_leter_cnt, color32_t color,
                        void (*set_pixel)(void *layer, int x, int y, color32_t c), wchar_t (*conv)(const void **));

uint32_t drawstringf(ft_font *ftf, image_t *buffer, const void *str, int16_t x, int16_t y,
                 int mw, int mh, int type, uint8_t leter_step, int32_t _max_leter_cnt, color32_t color,
                 void (*set_pixel)(void *layer, int x, int y, color32_t c), wchar_t (*conv)(const void **));

/* �� �������� ���������� ������� ^*/
uint32_t ft_string_metrics(ft_font *ftf, const void *str, uint32_t *height, uint32_t *y_seek, int32_t max_leter_cnt, wchar_t (*conv)(const void **));


/* ������ ������ ucs c ������� freetype2 */
uint16_t drawsymbol32_ucs(ft_font *ftf, image_t *buffer, uint16_t leter, int16_t x, int16_t y,
                          int16_t mw, int16_t mh, char align, color32_t color, void (*set_pixel)(void *layer, int x, int y, color32_t c) );

uint16_t drawstring32_ucs(ft_font *ftf, image_t *buffer, const wchar_t *str, int16_t x, int16_t y,
                        int w, int h, int type, uint8_t leter_step, int32_t max_leter_cnt, color32_t color);

uint32_t drawstring32f_ucs(ft_font *ftf, image_t *buffer, const wchar_t *str, int16_t x, int16_t y,
                 int mw, int mh, int type, uint8_t leter_step, int32_t _max_leter_cnt, color32_t color);


uint32_t ft_string_metrics_ucs(ft_font *ftf, const wchar_t *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);

/* UTF-8 */
uint16_t drawstring32_utf8(ft_font *ftf, image_t *buffer, const char *str, int16_t x, int16_t y,
                         int16_t w, int16_t h, int type, uint8_t leter_step, int32_t max_leter_cnt, color32_t color);

uint16_t drawstring32f_utf8(ft_font *ftf, image_t *buffer, const char *str, int16_t x, int16_t y,
                         int16_t w, int16_t h, int type, uint8_t leter_step, int32_t max_leter_cnt, uint32_t color);

uint32_t ft_string_metrics_utf8(ft_font *ftf, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);

/* ������ ����� */
void image_wave(image_t *dest, image_t *img, int l);

/* �������� �� ����� */
void image_blur(image_t *dest, image_t *img, int r);

/* ������ �����������, ���������� ����� ������ � ������ ��������� */
image_t *image_rescale_quality(image_t *image, int newwidth, int newheight);
image_t *image_rescale_fast(image_t *original, int newWidth, int newHeight);

/* ������������ ����������� �� ������������ ���� */
void image_rotate(image_t *dest, image_t *src, int centerx, int centery, int angle);

/* ����������� ��������, ��������� ��� �������� �� �����, �� ������������ */
void image_smooth(image_t *dst, image_t *src, uint16_t smooth_w, uint16_t smooth_h);

/* ���������� ��������� */
void image_reflection(image_t *dst, image_t *src, int ref_w_h);

/* ������ �������� �� ����� cf �� ����� ct. type: 0 - � �����-����, 1 - ��������, 2 - � ���� �� �����, 3 - �������� */
void ll_image_gradient(image_t *dst, uint16_t x, uint16_t y, uint16_t w, uint16_t h, int type, uint8_t cf[4], uint8_t ct[4]);
void image_gradient(image_t *dst, int type, uint8_t cf[4], uint8_t ct[4]);

/* ��������� ����� ����� � �����������, �������: dst ������ ���� 32� ������ */
void image_alpha(image_t *dst, image_t *src, uint8_t alpha);


/* UCS */
uint16_t drawstring32s_ucs(ft_font *ftf, const wchar_t *str, int16_t x, int16_t y,
                        int mw, int mh, int align, uint8_t leter_step, int32_t max_leter_cnt, uint32_t color);
uint16_t drawstring32fs_ucs(ft_font *ftf, const wchar_t *str, int16_t x, int16_t y,
                        int mw, int mh, int align, uint8_t leter_step, int32_t max_leter_cnt, uint32_t color);

/* UTF-8 */
uint16_t drawstring32s_utf8(ft_font *ftf, const char *str, int16_t x, int16_t y,
                         int16_t w, int16_t h, int type, uint8_t leter_step, int32_t max_leter_cnt, uint32_t color);

uint16_t drawstring32fs_utf8(ft_font *ftf, const char *str, int16_t x, int16_t y,
                         int16_t w, int16_t h, int type, uint8_t leter_step, int32_t max_leter_cnt, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif





