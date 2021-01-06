#include "..\..\inc\swilib.h"
#include "image.h"
#include "..\alarm.h"

unsigned int status[6];
unsigned int hour[6];
unsigned int min[6];
unsigned int weekdays[6][7];
unsigned int backup[3];
unsigned int ch[3];
unsigned int max;
unsigned int mode=1;
unsigned int X;
unsigned int Y;
unsigned int show_icon;

GBSTMR mytmr;
unsigned int input;

unsigned int num_alarm=0;
unsigned int edit_level=1;
unsigned int ch[3];
unsigned int set=1;
int lng;

int scr_w;
int scr_h;
int font_size;

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
char colors[4][4]={{0xFF,0,0,0x64},{0,0xFF,0,0x64},{0,0,0xFF,0x64},{0xC6,0xAA,0xAF,0x32}};
const char Pointer[5]={0x27,0x27,0xFF,0x27,0x27};
const IMGHDR imgPointer = {5,5,0x1,(char *)Pointer};
GBSTMR mytmr;

WSHDR *ws;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w; 
  char h; 
  char Compr_Bits;  
}PICHDR;

void DrwStr(WSHDR *ws, int x, int y,int w,int h, int font,int flag,char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,w,h);
  SetPropTo_Obj1(&drwobj,&rc,0,ws,font,flag);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
  DrawObject(&drwobj);
}

void DrawBackground()
{
#ifdef NO_PNG
  volatile int hFile;
  PICHDR Pic_Header;
  unsigned int io_error = 0;
  hFile = fopen(fonimg, A_ReadOnly + A_BIN, P_READ, &io_error);
  if(!io_error)
  {
    fread(hFile, &Pic_Header, sizeof(Pic_Header), &io_error);
    unsigned int buf_size = lseek(hFile, 0, S_END, &io_error, &io_error) - sizeof(PICHDR);
    lseek(hFile, sizeof(PICHDR), S_SET, &io_error, &io_error); 
    char *pic_buffer = malloc((buf_size+3)&(~3));
    fread(hFile, pic_buffer, buf_size, &io_error);    
    fclose(hFile, &io_error);
    IMGHDR img;
    img.w = Pic_Header.w;
    img.h = Pic_Header.h;
    img.bpnum = Pic_Header.Compr_Bits;
    img.bitmap = pic_buffer;
    DrwImg(&img, 0, 0);
    mfree(pic_buffer);
  }
#else
  DrawImg(0, 0, (int)fonimg);
#endif
}

void draw_pic(int num,int x, int y)
{
  switch(num)
  {
  case fon:
    {
      DrawBackground();
    } break;
  case st_off:
    {
      IMGHDR img;
      img.w = 52;
      img.h = 52;
      img.bpnum = 0x88;
      img.bitmap = _st_off;
      DrwImg(&img,x,y);
    } break;
  case st_on:
    {
      IMGHDR img;
      img.w = 52;
      img.h = 52;
      img.bpnum = 0x88;
      img.bitmap = _st_on;
      DrwImg(&img,x,y);
    } break;
  case wd_off:
    {
      IMGHDR img;
      img.w = 14;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _wd_off;
      DrwImg(&img,x,y);
    } break;
  case wd_on:
    {
      IMGHDR img;
      img.w = 14;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _wd_on;
      DrwImg(&img,x,y);
    } break;
  case logo:
    {
      IMGHDR img;
      img.w = 26;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _logo;
      DrwImg(&img,x,y);
    } break;
  }
}

#ifdef SIX_ALARMS
#ifndef NEWSGOLD

#define MAX_HEX   (100+10)
#define MAX_BIN   (4 * MAX_HEX)

int hex2bin(char *bin, int hex_len, char *hex)
{
    int i;
    int bi;
    int num;
    int start = 1;

    bi = 0;
    i = 0;
    while (hex[i] == '0') i++;
    for ( ; i < hex_len; i++) {
        if      (hex[i] >= '0' && hex[i] <= '9') num = hex[i]-'0';
        else if (hex[i] >= 'A' && hex[i] <= 'F') num = hex[i]-'A'+10;
        else if (hex[i] >= 'a' && hex[i] <= 'f') num = hex[i]-'a'+10;
        else continue;
        if (start) {
            if ((num >> 3) & 1) start = 0;

            if (!start) bin[bi++] = (num >> 2) & 1;
            else if ((num >> 2) & 1) start = 0;

            if (!start) bin[bi++] = (num >> 1) & 1;
            else if ((num >> 1) & 1) start = 0;

            if (!start) bin[bi++] = num & 1;
            start = 0;
        } else {
            bin[bi++] = (num >> 3) & 1;
            bin[bi++] = (num >> 2) & 1;
            bin[bi++] = (num >> 1) & 1;
            bin[bi++] =  num       & 1;
        }
    }
    return bi;
}

int bin2hex(char *hex, int bin_len, char *bin)
{
    int  i, j;
    int  num;
    int  ti, hi;
    char tmp[MAX_BIN];

    ti = 0;
    num = (bin_len+1) % 4;
    if (num > 0) {
        num = 4 - num;
        while (num-- > 0) tmp[ti++] = 0;
    }
    tmp[ti++] = 1;
    while (bin_len-- > 0) tmp[ti++] = *bin++;

    hi = 0;
    for (i = 0; i < ti; i += 4) {
        num = 0;
        for (j = 0; j < 4; j++) num = (num << 1) | tmp[i+j];
        if (num < 10) num += '0';
        else          num += 'A' - 10;
        hex[hi++] = num;
    }
    return hi;
}

int digit2int (char d)
{
  switch (d)
    {
    case 'F':
    case 'E':
    case 'D':
    case 'C':
    case 'B':
    case 'A':
      return d - 'A' + 10;
    case 'f':
    case 'e':
    case 'd':
    case 'c':
    case 'b':
    case 'a':
      return d - 'a' + 10;
    case '9':
    case '8':
    case '7':
    case '6':
    case '5':
    case '4':
    case '3':
    case '2':
    case '1':
    case '0':
      return d - '0';
    }
  return -1;
}

int hex2int (char *s)
{
  int res;
  int tmp;
  if (strlen (s) < 1)
    return -1;
  if (strlen (s) > 2)
    return -1;
  res = digit2int (s[0]);
  if (res < 0)
    return -1;
  tmp = res;
  if (strlen (s) > 1)
    {
      res = digit2int (s[1]);
      if (res < 0)
	return -1;
      tmp = tmp * 16 + res;
    }
  return tmp;
}

void geteeblock()
{
  char *Block5166=malloc(8);
  EEFullReadBlock(5166, Block5166, 0, 5,0,0);
  
  char *hex=malloc(8);
  char *bin=malloc(8);
  sprintf(hex, "%x", Block5166[3]);
  hex2bin(bin, 3, hex);
  
  if (Block5166[4]==0xF1)
    status[5]=1;
  else status[5]=0;
  hour[5]=Block5166[0];
  min[5]=Block5166[1];
  for (int i=0;i<7;i++)
    weekdays[5][i]=bin[6-i];
  
  mfree(Block5166);
  mfree(bin);
  mfree(hex);
}

void saveeeblock()
{
  char *Block5166=malloc(8);
  Block5166[0]=hour[5];
  Block5166[1]=min[5];
  Block5166[2]=0;
  
  char *hex=malloc(3);
  char *bin=malloc(8);
  for (int i=0;i<7;i++)
    bin[i]=weekdays[5][6-i];
  bin[7]=1;
  bin2hex(hex, 7, bin);
  hex[2]=0;
  Block5166[3]=hex2int(hex);
  
  if (status[5]==1)
    Block5166[4]=0xF1;
  else Block5166[4]=0xF0;
  Block5166[5]=0xFF;
  
  EEFullWriteBlock(5166, Block5166, 0, 5,0,0);
  mfree(Block5166);
  mfree(bin);
  mfree(hex);
}
#endif
#endif

void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(64);
    fread(handle,data,60,&err);
      
status[0]=data[2];
hour[0]=data[3];
min[0]=data[4];
weekdays[0][0]=data[5];
weekdays[0][1]=data[6];
weekdays[0][2]=data[7];
weekdays[0][3]=data[8];
weekdays[0][4]=data[9];
weekdays[0][5]=data[10];
weekdays[0][6]=data[11];
status[1]=data[12];
hour[1]=data[13];
min[1]=data[14];
weekdays[1][0]=data[15];
weekdays[1][1]=data[16];
weekdays[1][2]=data[17];
weekdays[1][3]=data[18];
weekdays[1][4]=data[19];
weekdays[1][5]=data[20];
weekdays[1][6]=data[21];
status[2]=data[22];
hour[2]=data[23];
min[2]=data[24];
weekdays[2][0]=data[25];
weekdays[2][1]=data[26];
weekdays[2][2]=data[27];
weekdays[2][3]=data[28];
weekdays[2][4]=data[29];
weekdays[2][5]=data[30];
weekdays[2][6]=data[31];
status[3]=data[32];
hour[3]=data[33];
min[3]=data[34];
weekdays[3][0]=data[35];
weekdays[3][1]=data[36];
weekdays[3][2]=data[37];
weekdays[3][3]=data[38];
weekdays[3][4]=data[39];
weekdays[3][5]=data[40];
weekdays[3][6]=data[41];
status[4]=data[42];
hour[4]=data[43];
min[4]=data[44];
weekdays[4][0]=data[45];
weekdays[4][1]=data[46];
weekdays[4][2]=data[47];
weekdays[4][3]=data[48];
weekdays[4][4]=data[49];
weekdays[4][5]=data[50];
weekdays[4][6]=data[51];

show_icon=data[53];
X=data[54];
Y=data[55];

    mfree(data);
  }
  fclose(handle,&err);
#ifdef SIX_ALARMS
  geteeblock();
#endif
}

void save_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile,A_WriteOnly+A_Create,P_WRITE,&err);
  if(handle!=-1)
  {
    char *data=malloc(64);
    
data[2]=status[0];
data[3]=hour[0];
data[4]=min[0];
data[5]=weekdays[0][0];
data[6]=weekdays[0][1];
data[7]=weekdays[0][2];
data[8]=weekdays[0][3];
data[9]=weekdays[0][4];
data[10]=weekdays[0][5];
data[11]=weekdays[0][6];
data[12]=status[1];
data[13]=hour[1];
data[14]=min[1];
data[15]=weekdays[1][0];
data[16]=weekdays[1][1];
data[17]=weekdays[1][2];
data[18]=weekdays[1][3];
data[19]=weekdays[1][4];
data[20]=weekdays[1][5];
data[21]=weekdays[1][6];
data[22]=status[2];
data[23]=hour[2];
data[24]=min[2];
data[25]=weekdays[2][0];
data[26]=weekdays[2][1];
data[27]=weekdays[2][2];
data[28]=weekdays[2][3];
data[29]=weekdays[2][4];
data[30]=weekdays[2][5];
data[31]=weekdays[2][6];
data[32]=status[3];
data[33]=hour[3];
data[34]=min[3];
data[35]=weekdays[3][0];
data[36]=weekdays[3][1];
data[37]=weekdays[3][2];
data[38]=weekdays[3][3];
data[39]=weekdays[3][4];
data[40]=weekdays[3][5];
data[41]=weekdays[3][6];
data[42]=status[4];
data[43]=hour[4];
data[44]=min[4];
data[45]=weekdays[4][0];
data[46]=weekdays[4][1];
data[47]=weekdays[4][2];
data[48]=weekdays[4][3];
data[49]=weekdays[4][4];
data[50]=weekdays[4][5];
data[51]=weekdays[4][6];

data[53]=show_icon;
data[54]=X;
data[55]=Y;

    fwrite(handle,data,56,&err);
    mfree(data);
  }
  fclose(handle,&err);
#ifdef SIX_ALARMS
  saveeeblock();
#endif
}

void edit()
{
  if (input)
  {
    switch(set)
    {
    case 1: if(ch[1])
        hour[num_alarm]=backup[1];
    case 2: if(ch[2])
      min[num_alarm]=backup[2];
    }
    }
}

void status_on_off()
{
  if (status[num_alarm]==1) status[num_alarm]=0; else status[num_alarm]=1;
}

void weekday_on_off()
{
  if (weekdays[num_alarm][set]==1) weekdays[num_alarm][set]=0; else weekdays[num_alarm][set]=1;
}


void OnRedraw()
{
  switch(mode)
  {
  case 1:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      draw_pic(logo,2,2);
      
      char *ColorIndex[3]={GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(3)};
      
      wsprintf(ws, percent_t, alarm_name);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      wsprintf(ws, percent_t, change);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      wsprintf(ws, percent_t, save);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      char *stat=malloc(16);
      int tmp=scr_h/7.3;
#ifndef SL65
      int tmp3=0;
#endif
      for (int i=0;i<num_alarms;i++)
      {
        if (status[i]) strcpy(stat,on);
          else strcpy(stat,off);
#ifdef SL65
        wsprintf(ws, "%d: %d:%02d %t",i+1,hour[i],min[i],stat);
        DrwStr(ws,10,5+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+(num_alarm==i)]);
#else
        wsprintf(ws, "%t %d: %d:%02d %t",alarm_name,i+1,hour[i],min[i],stat);
        int tmp2=1+tmp*(i+1)+tmp3+tmp3;
        if (num_alarm==i)
        {
          DrwStr(ws,5,tmp2,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[2]);
          tmp3=3;
          for (int ii=0;ii<7;ii++)
          {
            draw_pic((int)wd_off+weekdays[i][ii],scr_w-11*(7-ii)-3, tmp2+GetFontYSIZE(FONT_SMALL)+1);
          }
        }
          else DrwStr(ws,5,tmp2,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
#endif
      }
      mfree(stat);
    } break;

  case 2:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      draw_pic(logo,2,2);
      
      char *ColorIndex[3]={GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(3)};
      
      wsprintf(ws, "%t %d",alarm_name,num_alarm+1);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
#ifdef SL65
      if(status[num_alarm]==1) draw_pic(st_on,5,HeaderH());
        else draw_pic(st_off,5,HeaderH());
#else
      if(status[num_alarm]==1) draw_pic(st_on,scr_w/2-26,HeaderH());
        else draw_pic(st_off,scr_w/2-26,HeaderH());
#endif
      if ((edit_level==1)||(edit_level==3))
        {
          wsprintf(ws, percent_t, change);
          DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
        }
      
      wsprintf(ws, percent_t,ok);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      int a=scr_w/2-GetSymbolWidth('n',FONT_SMALL)*2;
      if (status[num_alarm]) wsprintf(ws, percent_t,on);
          else 
          {
            wsprintf(ws, percent_t,off);
            a-=3;
          }
#ifdef SL65
      DrwStr(ws,67,HeaderH()+18,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+(edit_level==1)]);
#else
      DrwStr(ws,a,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+(edit_level==1)]);
#endif
      
#ifdef SL65
      a=67;
        int b=HeaderH()+21+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+((edit_level==2)&&(set==1))]);
        
      a+=(GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)+GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL));
      wsprintf(ws, ":");
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      a+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+((edit_level==2)&&(set==2))]);
#else
      a=scr_w/2-GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)-GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL);      
        int b=HeaderH()+60+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+((edit_level==2)&&(set==1))]);
        
      a=scr_w/2;
      wsprintf(ws, ":");
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1]);
      
      a+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+((edit_level==2)&&(set==2))]);
#endif
      a=scr_w/7.3;
#ifdef SL65
      b=scr_h-SoftkeyH()-font_size-18;
#else
      b=scr_h-SoftkeyH()-font_size-24;
#endif
      for (int i=0;i<7;i++)
      {
        wsprintf(ws, percent_t,wd[i]);
        DrwStr(ws,4+a*i,b,scr_w,scr_h,FONT_SMALL,1,ColorIndex[0],ColorIndex[1+((edit_level==3)&&(set==i))]);
      }
      b+=(font_size+3);
      for (int i=0;i<7;i++)
      {
        draw_pic(wd_off+weekdays[num_alarm][i],5+a*i,b);
      }
    } break;
  case 3:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,
                   GetPaletteAdrByColorIndex(0),
                   GetPaletteAdrByColorIndex(0));
      for (int y_0=0; y_0< scr_h;y_0+=10)
        {
          DrawLine(0,y_0,scr_w,y_0,1,colors[3]);
        }
      for (int x_0=0; x_0<scr_w;x_0+=10)
        {
          DrawLine(x_0,0,x_0,scr_h,1,colors[3]);
        }
      DrwImg((IMGHDR *)&imgPointer,X-2,Y-2);
      
      wsprintf(ws, "%03d,%03d", X, Y);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
      
      if (show_icon) wsprintf(ws, percent_t, on);
        else wsprintf(ws, percent_t, off);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
    }
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  ws = AllocWS(128);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(ws);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  //DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int onkey(unsigned char keycode, int pressed)
{
  switch(mode)
  {
    case 1:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case LEFT_SOFT:
            case ENTER_BUTTON:  mode=2; OnRedraw(); break;
            case RIGHT_SOFT:
              {
                save_settings();
                GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,"alarm");
                return(1);
              }
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (num_alarm>0) num_alarm--;
                  else num_alarm=(num_alarms-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (num_alarm<(num_alarms-1)) num_alarm++;
                  else num_alarm=0;
                  break;
              }
            case GREEN_BUTTON: open_bcfg(); break;
            case '1': num_alarm=0; break;
            case '2': num_alarm=1; break;
            case '3': num_alarm=2; break;
            case '4': num_alarm=3; break;
            case '5': num_alarm=4; break;
#ifdef SIX_ALARMS
            case '6': num_alarm=5; break;
#endif
            case '#': mode=3; break;
            //case '*': saveeeblock(); break;
            //case '*': ShowMSG(1,(int)"Alarm cfg editor\n(c)Geka"); break;
            }
          }
      } break;
  case 2:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=1; break;
        case RIGHT_SOFT:  mode=1; OnRedraw(); break;
        case LEFT_SOFT:
          {
            if (edit_level==1) status_on_off();
            if (edit_level==3)
            {
              weekday_on_off();
              if (set<6) set++;
               else set=0;
            }
            break;
          }
          case UP_BUTTON:
            {
              if (edit_level>1) edit_level--;
                else edit_level=3;
              if (edit_level==3)
                set=0;
              else set=1;
              input=1;
              edit();
              break;
            }
        case DOWN_BUTTON:
          {
            if (edit_level<3) edit_level++;
              else edit_level=1;
              if (edit_level==3)
                set=0;
              else set=1;
            input=1;
            edit();
            break;
          }
        case LEFT_BUTTON:
          {
            if(edit_level==1) status_on_off();
            if(edit_level==2)
            {
              if (set>0) set--;
                else set=2;
              lng=0;
            }
            if(edit_level==3)
            {
              if (set>0) set--;
                else set=6;
            }
            break;
          }
        case RIGHT_BUTTON:
          {
            if(edit_level==1) status_on_off();
            if(edit_level==2)
            {
              if (set<2) set++;
                else set=1;
              lng=0;
            }
            if(edit_level==3)
            {
              if (set<6) set++;
                else set=0;
            }
            break;
          }
        case ENTER_BUTTON:
          {
            if(edit_level==3)
            {
              weekday_on_off();
              if (set<6) set++;
                else set=0;
            }
            break;
          }
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
            if(edit_level==2)
            {
              ++lng;
              if (set==1) max=3;
                else max=6;
              if (backup[set]<max) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                  lng=1;
                }
                ch[set]=1;
                input=1;
                edit();
                if (lng==2) {if(set==1) {set=2; lng=0;} else {edit_level=1; lng=1;}}
            }
            if(edit_level==3)
            {
              int key=keycode-'0';
              if (key<8&&key>0) set=key;
            }
            break;
          }
        }
      }
    } break;
  case 3:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
        switch(keycode)
          {
          case LEFT_BUTTON: case '4': if (X>0) X-=5; else X=scr_w; break;
          case RIGHT_BUTTON: case '6': if (X<132) X+=5; else X=0; break;
          case UP_BUTTON: case '2': if (Y>0) Y-=5; else Y=scr_h; break;
          case DOWN_BUTTON: case '8': if (Y<176) Y+=5; else Y=0; break;
          }
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=1; break;
        case LEFT_SOFT: if (show_icon==1) show_icon=0; else show_icon=1; break;
        case LEFT_BUTTON: case '4': if (X!=0) X--; else X=scr_w; break;
        case RIGHT_BUTTON: case '6': if (X!=132) X++; else X=0; break;
        case UP_BUTTON: case '2': if (Y!=0) Y--; else Y=scr_h; break;
        case DOWN_BUTTON: case '8': if (Y!=176) Y++; else Y=0; break;
        default: mode=1; break;
        }
      }
    } break;
  }
  DirectRedrawGUI();
  return(0);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  return onkey(msg->gbsmsg->submess, msg->gbsmsg->msg);
}

  extern void kill_data(void *p, void (*func_p)(void *));
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}
#endif

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const struct
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

void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Alarm cfg editor");
  FreeWS(ws);
}

int main(void)
{
  if (check_install()>0)
    return 0;
  font_size=GetFontYSIZE(FONT_SMALL);
  load_settings();
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
