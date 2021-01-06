

#include <swilib.h>
#include <de/drawing.h>
#include <spl/lcd_primitives.h>


LCDLAYER lcd_layer;


__attribute_constructor
void initDraw()
{
    memcpy(&lcd_layer, *RamMMILCDLayer(), sizeof(lcd_layer));
}



void lcdDrawScrollString(image_t *screen, WSHDR *ws, int x, int y, int x1,
                         int y1, int font, int attribute, char *pen, char *brush)

{
    lcd_layer.w = screen->w;
    lcd_layer.h = screen->h;
    lcd_layer.buf = screen->bitmap;

    lcd_draw_text(&lcd_layer, ws, x, y, x1, y1, font, attribute, pen, brush);
}


void lcdDisplayImageAsLayer(image_t *img)
{
    lcd_layer.buf = img->bitmap;
    displayLayer(&lcd_layer);
}
