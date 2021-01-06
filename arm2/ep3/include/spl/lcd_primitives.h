

#ifndef __LCD_PRIMITIVES_H__
#define __LCD_PRIMITIVES_H__

#include <swilib.h>
#include <de/drawing.h>
#include <de/pixmap.h>

#ifdef __cplusplus
extern "C" {
#endif


static inline
void lcd_draw_pixel32(LCDLAYER *layer, int x, int y, uint32_t pixel)
{
    if(x < 0 || y < 0 || x >= layer->w || y >= layer->h) return;
    switch(layer->depth)
    {
        case 4:
            ((uint16_t*)layer->buf)[ y * layer->w + x ] = rgb32ToRgb16(pixel);
            break;

        case 5:
            ((uint32_t*)layer->buf)[ y * layer->w + x ] = pixel;
            break;
    }
}


inline void displayLayer(LCDLAYER *layer)
{
    GBS_SendMessage(LCD_DISPQUEUE_CEPID, LCD_DISPLAY_LAYER, 0, (void *)layer);
}



void lcd_draw_imghdr(LCDLAYER *layer, int x, int y, IMGHDR *img);
void lcd_draw_image(LCDLAYER *layer, int x, int y, image_t *_img);
void lcd_draw_eimg(LCDLAYER *layer, int x, int y, EIMGHDR *eimg);
void lcd_draw_text(LCDLAYER *layer, WSHDR *text, int x1, int y1, int x2, int y2,
              int font, int text_attribute,
              const char *Pen, const char *Brush);
void lcd_draw_fillrect(LCDLAYER *layer, int x1, int y1, int x2, int y2, const char *brush);
void lcd_draw_invertrect(LCDLAYER *layer, int x1,int y1,int x2,int y2);
void lcd_draw_line(LCDLAYER *layer, int x, int y, int x2, int y2, const char *pen);
void lcd_draw_filltriangle(LCDLAYER *layer, int x1, int y1,
                                            int x2, int y2,
                                            int x3, int y3,
                                            int flag,
                                            const char *Pen, const char *Brush);
void lcd_draw_arc(LCDLAYER *layer, int x1, int y1, int x2, int y2,
                                   int begin_angle, int end_angle,
                                   const char *pen, const char *brush);

#ifdef __cplusplus
}
#endif

#endif
