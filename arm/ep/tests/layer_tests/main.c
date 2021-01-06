
#include <swilib.h>
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/csm.h>
#include <spl/gui.h>
#include <spl/timer.h>
#include <spl/lcd_primitives.h>
#include <spl/memctl.h>
#include <de/drawing.h>
#include <spl/processbridge.h>


int csm_id, gui_id;
RECT canvas;
LCDLAYER *mmi_layer;
extern LCDLAYER lcd_layer;
char screen[132*176*4];
char red[] = {0xff, 0x00, 0x00, 0xff};
char white[] = {0xff, 0xff, 0xff, 0xff};
int fps = 0, fps_cnt = 0, last_time, timeri = -1;
    static int tmrcnt = 0;

image_t img;

void lcdDisplayImageAsLayer(image_t *img);
void lcdDrawScrollString(image_t *screen, WSHDR *ws, int x, int y, int x1,
                         int y1, int font, int attribute, char *pen, char *brush);



void memset64(void *dst, int c, size_t size);
void bcopy64(void *dst, void *src, size_t size);

__attribute__((noinline))
void _fillscreen(image_t *img, color32_t color)
{
    switch(img->bpnum)
    {
        case 16:
        {
            color16_t col16 = rgb32ToRgb16(color);
            int size = (img->w * img->h * 2);
            color32_t x2col16 = col16 << 16 | col16;

            if( (size % 4) == 0 ) {
                size /= 4;
                while(--size)
                    ((color32_t*)img->bitmap)[size] = x2col16;
            }
            else if( (size % 2) == 0 ) {
                size /= 2;
                while(--size)
                    ((color16_t*)img->bitmap)[size] = col16;
            }
        }
        break;

        case 32:
        {
                int size = img->w * img->h;
                while(--size)
                    ((color32_t*)img->bitmap)[size] = color;
        }
        break;
    }
}


void onRedrawGUI(int id)
{
    color16_t col16 = rgb32ToRgb16(0xFFFF0000);
    color32_t x2col16 = col16 << 16 | col16;
    //memcpy(screen, mmi_layer->buf, 132*176*2);

    memset64(screen, x2col16, 132*176*2);
    //memset(screen, x2col16, 132*176*2);

    //_fillscreen(&img, 0xFFFF0000);
    //lcd_draw_fillrect(&lcd_layer, 0, 0, 132, 176, red);


    WSHDR *ws = AllocWS(128);
    wsprintf(ws, "fps: %d\n %d", fps, tmrcnt);
    //lcdDrawScrollString(&img, ws, 40, 40, 132, 176, FONT_SMALL, 0, white, 0);
    lcd_draw_text(&lcd_layer, ws, 40, 40, 132, 176, FONT_SMALL, 0, white, 0);
    FreeWS(ws);

    //lcdDisplayImageAsLayer(&img);
    displayLayer(&lcd_layer);

    fps_cnt++;

    TTime time;
    GetDateTime(0, &time);
    if(last_time != time.sec)
    {
        fps = fps_cnt;
        fps_cnt = 0;
        last_time = time.sec;
    }
}


void timer(int id)
{
    if(tmrcnt % 8)
        onRedrawGUI(0);
    if(tmrcnt >= 1200) {
        timerStop(timeri);
        return;
    }

    tmrcnt++;
}


void onCreateGUI(int id)
{
    mmi_layer = *RamMMILCDLayer();

    img.w = 132;
    img.h = 176;
    img.bitmap = (unsigned char*)screen;
    img.blend = 0;
    img.bpnum = 16;

    lcd_layer.buf = screen;

    timeri = timerStart(1, timer);
    printf("timer: %d\n", timeri);
}


void onCloseGUI(int id)
{
    timerStop(timeri);
}


void onFocusGUI(int id)
{
}


void onUnfocusGUI(int id)
{
}


void onKeyGUI(int id, GUI_MSG *msg)
{
    if ((msg->gbsmsg->msg == KEY_DOWN || msg->gbsmsg->msg == LONG_PRESS))
    {
        switch(msg->gbsmsg->submess)
        {
            case RIGHT_SOFT:
                closeGUI(id);
                return;
        }
    }

    onRedrawGUI(id);
    //REDRAW();
}



void onCreateCSM(int id, CSM_RAM *ram)
{
    canvas.x = 0;
    canvas.y = 0;
    canvas.x2 = ScreenW();
    canvas.y2 = ScreenH();

    gui_id = createGUI(&canvas, onRedrawGUI,
                       onCreateGUI,
                       onCloseGUI,
                       onFocusGUI,
                       onUnfocusGUI,
                       onKeyGUI,
                       NULL);

    printf("csm_id: %d | gui_id: %d\n", csm_id, gui_id);

    bindGUIToCSM(csm_id, getGUIid(gui_id));
}


void onCloseCSM(int id, CSM_RAM *ram)
{
    quit();
}




int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    csm_id = createCSM("test", CoreCSM_GUI, onCreateCSM, onCloseCSM, 0);

    processEvents();
    return 0;
}





