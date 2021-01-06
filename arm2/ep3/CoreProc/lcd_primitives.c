
#include <spl/lcd_primitives.h>



void lcd_draw_image(LCDLAYER *layer, int x, int y, image_t *_img)
{
    if(!_img) return;
    if(!_img->bitmap) return;

    IMGHDR img = {_img->w, _img->h, _img->bpnum==16? 8:10, _img->bitmap};

    RECT rc;
    DRWOBJ drwobj;
    StoreXYWHtoRECT(&rc, x, y, img.w, img.h);
    SetPropTo_Obj5(&drwobj, &rc, 0, &img);
    PushDRWOBJOnLAYER(&drwobj, layer);
}



void lcd_draw_imghdr(LCDLAYER *layer, int x, int y, IMGHDR *img)
{
    if(!img) return;
    if(!img->bitmap) return;

    RECT rc;
    DRWOBJ drwobj;
    StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
    SetPropTo_Obj5(&drwobj, &rc, 0, img);
    PushDRWOBJOnLAYER(&drwobj, layer);
}




void lcd_draw_text(LCDLAYER *layer, WSHDR *text, int x1, int y1, int x2, int y2,
                  int font, int text_attribute,
                  const char *Pen, const char *Brush)
{
    RECT rc;
    DRWOBJ drwobj;
    StoreXYWHtoRECT(&rc, x1, y1, x2, y2);
    SetPropTo_Obj1(&drwobj, (void *)&rc, 0,
                   text, font, text_attribute);
    SetColor(&drwobj, (char *)Pen, (char *)Brush);
    PushDRWOBJOnLAYER(&drwobj, layer);
}


void lcd_draw_fillrect(LCDLAYER *layer, int x1, int y1, int x2, int y2, const char *brush)
{
    RECT rc;
    DRWOBJ drwobj;
    StoreXYWHtoRECT(&rc, x1, y1, x2, y2);
    SetProp2Square_v1(&drwobj, &rc, 0, 0, 0);
    SetColor(&drwobj, NULL, (char *)brush);
    PushDRWOBJOnLAYER(&drwobj, layer);
}


void lcd_draw_invertrect(LCDLAYER *layer, int x1,int y1,int x2,int y2)
{
    RECT rc;
    DRWOBJ drwobj;
    StoreXYWHtoRECT(&rc, x1, y1, x2, y2);
    SetProp2Square_v2(&drwobj, &rc, 0x20);
    PushDRWOBJOnLAYER(&drwobj, layer);
}


void lcd_draw_eimg(LCDLAYER *layer, int x, int y, EIMGHDR *eimg)
{
   RECT rc;
   DRWOBJ drwobj;
   StoreXYWHtoRECT(&rc,x,y,eimg->w,eimg->h);
   SetPropTo_obj0x17(&drwobj,&rc, 0, eimg, 0, 0);
   PushDRWOBJOnLAYER(&drwobj, layer);
}

void lcd_draw_line(LCDLAYER *layer, int x, int y, int x2, int y2, const char *pen)
{
   RECT rc;
   DRWOBJ drwobj;

   StoreXYWHtoRECT(&rc,x,y,x2,y2);
   SetProp2Square_v1(&drwobj, &rc,0x09, 0, 0);
   SetPropTo_obj0x0F(&drwobj, &rc, 0x09, x, y, x2, y2);
   SetColor(&drwobj, (char *)pen, NULL);
   PushDRWOBJOnLAYER(&drwobj, layer);
}

void lcd_draw_filltriangle(LCDLAYER *layer, int x1, int y1,
                                            int x2, int y2,
                                            int x3, int y3,
                                            int flag,
                                            const char *Pen, const char *Brush)
{
   DRWOBJ drwobj;
   SetPropTo_obj0x15(&drwobj, x1, y1, x2, y2, x3, y3, flag, (char *)Pen, (char *)Brush);
   PushDRWOBJOnLAYER(&drwobj, layer);
}

void lcd_draw_arc(LCDLAYER *layer, int x1, int y1, int x2, int y2, int begin_angle, int end_angle, const char *pen, const char *brush)
{
   RECT rc;
   DRWOBJ drwobj;

   StoreXYWHtoRECT(&rc,x1,y1,x2,y2);
   SetPropTo_obj0x13(&drwobj, &rc, 0x01, 0x10,0x20, 0x21, 0x21, begin_angle, end_angle);
   SetColor(&drwobj, (char *)pen, (char *)brush);
   PushDRWOBJOnLAYER(&drwobj, layer);
}

