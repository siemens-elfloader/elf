#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "jpeg-7/jpeglib.h"
#define NO_LOG


char DEBUG = 1;
TDate date; TTime time;
#ifndef NO_LOG
void Tlog (char *string)
{
  if(DEBUG)
  {
    int logfile=fopenA("0:\\zbin\\ScreenGrabber.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
   char *data=(char*)malloc(4096);
   GetDateTime(&date,&time); 
   sprintf(data,">%d:%02d:%02d/%02d-%02d-%04d< >kernel<   %s\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
   lseek(logfile, 0x0, S_END, 0, 0);
   fwrite(logfile,data,strlen(data),0);
   mfree(data);
   fclose(logfile,0);
  }
}
#else 
void Tlog (char *string){}
#endif
char lgn[128]; //for Tlog()



const int minus11=-11;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
CSM_RAM *tcsm;
extern void kill_data(void *p, void (*func_p)(void *));



extern const int CFG_OUTPUT_FORMAT;
extern const char CFG_OUTPUT_PATH[];
extern const int CFG_JPEG_CLEVEL;
extern const int CFG_BMP_BPP;
extern const int CFG_HOTKEY;
extern const int CFG_ENABLE_MSG;

void write_jpeg(char *file, unsigned char *image24, unsigned int w, unsigned int h)
{
  Tlog("write jpeg...");
        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr jerr;
        int row_stride;
        JSAMPROW row_pointer;
        int i;
        
        int outfile = fopenA(file,A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
        
        cinfo.err = jpeg_std_error(&jerr);
        Tlog("err ok");
        jpeg_create_compress(&cinfo);
        Tlog("create compress ok");
        jpeg_stdio_dest(&cinfo, outfile);
        Tlog("stdio dest ok");
        cinfo.image_width = w;
        cinfo.image_height = h;
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;
        jpeg_set_defaults(&cinfo);
        Tlog("defafults ok");
        jpeg_set_quality(&cinfo,CFG_JPEG_CLEVEL,TRUE);
        Tlog("quality ok");
        jpeg_start_compress(&cinfo, TRUE);
        Tlog("compress ok");
        row_stride = 3*w;
        for (i=0; i<h; i++)
        {
                row_pointer = &image24[i*row_stride];
                jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }
        Tlog("scanlines writed");
        jpeg_finish_compress(&cinfo);
        Tlog("compress finished");
        jpeg_destroy_compress(&cinfo);
        Tlog("compress destroyed");
        fclose(outfile,0);
        Tlog("all ok");
}



#include "pnglib/png.h"
static void unpremultiply_data(png_structp png, png_row_infop row_info, png_bytep data)
{
    int i;
    for (i = 0; i < row_info->rowbytes; i += 4) 
    {
        unsigned char *b = &data[i];
        unsigned int pixel;
        unsigned char alpha;

        memcpy (&pixel, b, sizeof (unsigned int));
        alpha = (pixel & 0xff000000) >> 24;
        if (alpha == 0)
        {
            b[0] = b[1] = b[2] = b[3] = 0;
        }
        else
        {
            b[0] = (((pixel & 0x0000ff) >>  0) * 255 + alpha / 2) / alpha;
            b[1] = (((pixel & 0x00ff00) >>  8) * 255 + alpha / 2) / alpha;
            b[2] = (((pixel & 0xff0000) >> 16) * 255 + alpha / 2) / alpha;
            b[3] = alpha;
        }
    }
}
void write_png_argb32 (char *filename,char *buffer32,int width,int height,int stride)
{
    int file = fopenA(filename,A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
    int i;
    png_struct *png;
    png_info *info;
    png_byte **rows;
    png_color_16 white;

    rows = malloc (height * sizeof(png_byte*));

    for (i = 0; i < height; i++) 
    {
        rows[i] = buffer32 + i * stride;
    }

    png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info = png_create_info_struct (png);

    png_init_io (png, file);
    png_set_IHDR (png, info,
                  width, height, 8,
                  PNG_COLOR_TYPE_RGB_ALPHA,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    white.red = 0xff;
    white.blue = 0xff;
    white.green = 0xff;
    png_set_bKGD (png, info, &white);

    png_set_write_user_transform_fn (png, unpremultiply_data);
    png_set_bgr (png);

    png_write_info (png, info);
    png_write_image (png, rows);
    png_write_end (png, info);

    png_destroy_write_struct (&png, &info);

    fclose(file,0);
    mfree (rows);
}












#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      FSTATS fs;unsigned int err;
      if(GetFileStats(CFG_OUTPUT_PATH,&fs,&err)<0) ShowMSG(0,(int)"wrong output path!");
      else ShowMSG(1,(int)"<data saved>");
    }
  }
  return (1);
}




static void maincsm_oncreate(CSM_RAM *data)
{
  
}




void rgb16torgb32(const char *src, char *dst, unsigned int src_size)
{
        const short *end;
        char *d = (char *)dst;
        const short *s = (short*)src;
        end = s + src_size/2;
        while(s < end)
        {
                register short bgr;
                bgr = *s++;
                *d++ = (bgr&0x1F)<<3;
                *d++ = (bgr&0x7E0)>>3;
                *d++ = (bgr&0xF800)>>8;
                *d++ = 255;
        }
}
void rgb16tobgr24(const char*src,char *dst,unsigned int src_size)
{
        const short *end;
        char *d = (char*)dst;
        const short *s = (const short*)src;
        end = s + src_size/2;
        while(s < end)
        {
                register short bgr;
                bgr = *s++;
                *d++ = (bgr&0xF800)>>8;
                *d++ = (bgr&0x7E0)>>3;
                *d++ = (bgr&0x1F)<<3;
        }
}






extern int WriteBMP(char *fname,char *data,int w,int h,char bpp);


#define T_PNG 1
#define T_JPG 0

void StartShoot()
{
  Tlog("shoot...");
  char *tmp = malloc(256);
  char *screen = (char*)RamScreenBuffer();
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  char *buf;
  
  
  if(CFG_OUTPUT_FORMAT==T_PNG)
  {
    Tlog("png");
    buf = malloc(ScreenW()*ScreenH()*4);
    sprintf(tmp,"%s%d%d%d_%d%d%d.png",CFG_OUTPUT_PATH,date.day,date.month,date.year,time.hour,time.min,time.sec);
    rgb16torgb32(screen,buf,ScreenW()*ScreenH()*2);
    write_png_argb32(tmp,buf,ScreenW(),ScreenH(),ScreenW()*4);
  }
  else if(CFG_OUTPUT_FORMAT==T_JPG)
  {
    Tlog("jpg");
    buf = malloc(ScreenW()*ScreenH()*3);
    sprintf(tmp,"%s%d%d%d_%d%d%d.jpg",CFG_OUTPUT_PATH,date.day,date.month,date.year,time.hour,time.min,time.sec);
    rgb16tobgr24(screen,buf,ScreenW()*ScreenH()*2);
    write_jpeg(tmp,buf,ScreenW(),ScreenH());
  }
 /* else if(CFG_OUTPUT_FORMAT==T_BMP)
  {
    Tlog("bmp");
    buf = malloc(ScreenW()*ScreenH()*2);
    sprintf(tmp,"%s%d%d%d_%d%d%d.bmp",CFG_OUTPUT_PATH,date.day,date.month,date.year,time.hour,time.min,time.sec);
    memcpy(buf,screen,ScreenW()*ScreenH()*2);
    Tlog("memcpy ok");
    WriteBMP(tmp,buf,ScreenW(),ScreenH(),16);
  }*/
  else goto exit;
  
  if(CFG_ENABLE_MSG) ShowMSG(1,(int)"Screen saved");
  
  
  mfree(buf);
exit:
  mfree(tmp);
}



int press_allow = 1;
int mode_enter;
int my_keyhook(int submsg, int msg)
{
  if(submsg==CFG_HOTKEY)
  {
   switch(msg)
   {
    case KEY_DOWN: if(mode_enter==2)
    {
     GBS_SendMessage(MMI_CEPID,KEY_UP,CFG_HOTKEY);
     return(0);
    }
    mode_enter=0;return(2);
    case KEY_UP: if(mode_enter==0)
    {
      press_allow = 1;
     mode_enter=2;
     GBS_SendMessage(MMI_CEPID,KEY_DOWN,CFG_HOTKEY);
     return(2);
    }
    if(mode_enter==2)
    {
     mode_enter=0;
     return(0);
    }
    mode_enter=0;return(2);      
  case LONG_PRESS: mode_enter=1;
  if(press_allow) StartShoot();
  press_allow = 0;
  GBS_SendMessage(MMI_CEPID,KEY_UP,CFG_HOTKEY);
    break;
  }
  return(2);
  }
  
  return 0;
}





static void Killer(void)
{
  RemoveKeybMsgHook((void *)my_keyhook);
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ScreenGrabber (c)half65");
}












extern int saveGIF(const char *filename,int wid,int hit,const unsigned char *pal,const unsigned char *data);



int main()
{
  Tlog("started...");
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  AddKeybMsgHook((void *)my_keyhook);
  /*
  IMGHDR *test_img = CreateIMGHDRFromPngFile("0:\\zbin\\test_in.png",0);
  Tlog("img_created");
  wrbuf = test_img->bitmap;
  //char *buf = malloc(test_img->w*test_img->h*3);
  //rgb16tobgr24(test_img->bitmap,buf,test_img->w*test_img->h*2);
  //write_jpeg("0:\\zbin\\test_out.jpg",buf,test_img->w,test_img->h);
  //Tlog("jpeg writed");
  
  //Tlog("cmap ok");
  //saveGIF("0:\\zbin\\test_out.gif",test_img->w,test_img->h,cmap,test_img->bitmap);
  //Tlog("gif writed");
  
  //mfree(buf);
  mfree(test_img->bitmap);
  mfree(test_img);
  
  Tlog("completed");
  */
  return 0;
}
