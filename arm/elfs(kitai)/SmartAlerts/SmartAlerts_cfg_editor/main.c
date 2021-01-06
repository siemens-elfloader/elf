#include "..\..\inc\swilib.h"
#include "image.h"
#include "..\SmartAlerts.h"

TTime time;

unsigned int files[8];
unsigned int smss[8];
unsigned int calls[8];
unsigned int amenus[11];

unsigned int status[5];
unsigned int hour[5];
unsigned int min[5];
unsigned int weekdays[5][7];
unsigned int day[7][24];
unsigned int miss[6];

unsigned int bmenus[4];
unsigned int backup[12];
unsigned int other[8];
unsigned int weeks[8];
unsigned int name2[9];
unsigned int max;
unsigned int mode=0;
unsigned int X;
unsigned int Y;
unsigned int show_icon;

GBSTMR mytmr;

unsigned int file;
unsigned int sms;
unsigned int call;

unsigned int amenu=0;
unsigned int mmenu=0;
unsigned int bmenu=0;
unsigned int onum=0;
unsigned int num_alarm=0;
unsigned int menu=0;
unsigned int dat=0;
unsigned int seven=0;
unsigned int edit_level=1;
unsigned int set=1;
int lng;

int scr_w;
int scr_h;
int font_size;
int tmp;

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
char colors[4][4]={{0xFF,0,0,0x64},{0,0xFF,0,0x64},{0,0,0xFF,0x64},{0xC6,0xAA,0xAF,0x32}};
const char Pointer[5]={0x27,0x27,0xFF,0x27,0x27};
const IMGHDR imgPointer = {5,5,0x1,(char *)Pointer};
GBSTMR mytmr;

WSHDR *ws=NULL;

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

void draw_pic(int num,int x, int y)
{
  switch(num)
  {
  case fon:
    {
      DrawImg(0, 0, (int)fonpng);
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
  }
}


void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(512);
    fread(handle,data,512,&err);
      
show_icon=data[1];
X=data[2];
Y=data[3]*256+data[4];
//5
for(int i=0;i<5;i++)
{
  status[i]=data[i+5];
  hour[i]=data[i+10];
  min[i]=data[i+15];
  files[i]=data[i+20];
  calls[i]=data[i+25];
  smss[i]=data[i+30];
}

//20
for(int i=0;i<35;i++)
{
weekdays[i/7][i%7]=data[i+20];
}
//55
for(int i=0;i<168;i++)
{
day[i/24][i%24]=data[i+55];
}
//223
for(int i=0;i<8;i++)
{
 name2[i]=data[i+223];
 weeks[i]=data[i+231];
 amenus[i]=data[i+239];
 files[i]=data[i+247];
 calls[i]=data[i+255];
 smss[i]=data[i+263];
 other[i]=data[i+271];
}

amenus[8]=data[279];
amenus[9]=data[280];
amenus[10]=data[281];

bmenus[0]=data[282];
bmenus[1]=data[283];
bmenus[2]=data[284];
bmenus[3]=data[285];

miss[0]=data[286];
miss[1]=data[287];
miss[2]=data[288];
miss[3]=data[289];
miss[4]=data[290];
miss[5]=data[291];


    mfree(data);
  }
  fclose(handle,&err);
}

void save_settings(void)
{
  unsigned int err; 
  int handle=fopen(cfgfile,A_WriteOnly+A_Create,P_WRITE,&err);
  if(handle!=-1)
  {
    char *data=malloc(512);

data[1]=show_icon;
data[2]=X;
data[3]=Y/256;
data[4]=Y%256;
//5
for(int i=0;i<5;i++)
{
  data[i+5]=status[i];
  data[i+10]=hour[i];
  data[i+15]=min[i];
}
//20
for(int i=0;i<35;i++)
{
data[i+20]=weekdays[i/7][i%7];
}
//55
for(int i=0;i<168;i++)
{
data[i+55]=day[i/24][i%24];
}
//223
for(int i=0;i<8;i++)
{
 data[i+223]=name2[i];
 data[i+231]=weeks[i];
 data[i+239]=amenus[i];
 data[i+247]=files[i];
 data[i+255]=calls[i];
 data[i+263]=smss[i];
 data[i+271]=other[i];
}

data[279]=amenus[8];
data[280]=amenus[9];
data[281]=amenus[10];


data[282]=bmenus[0];
data[283]=bmenus[1];
data[284]=bmenus[2];
data[285]=bmenus[3];

data[286]=miss[0];
data[287]=miss[1];
data[288]=miss[2];
data[289]=miss[3];
data[290]=miss[4];
data[291]=miss[5];

    fwrite(handle,data,512,&err);
    mfree(data);
  }
  fclose(handle,&err);
}

void edit()
{
    switch(set)
    {
    case 1: 
      hour[num_alarm]=backup[1];break;
    case 2: 
      min[num_alarm]=backup[2];break;
    case 3: 
      day[seven][dat]=backup[3];break;
    case 4:
      weeks[7]=backup[4]; break;
    case 5:
      bmenus[bmenu]=backup[5]; break;
    case 6:
      miss[mmenu]=backup[6];break;
    case 7:
      files[file]=backup[7];break;
    case 8:
      calls[call]=backup[8]; break;
    case 9:
      smss[sms]=backup[9];break;
    case 10:
      amenus[amenu]=backup[10];break;
    case 11:
      other[onum]=backup[11];break;
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

const char percent_t[]="%t";

void CreateList(char const *header,char control,char const *list[],int num,int change,int boxend,int datanum,unsigned int data[],int fix,char const *LeftButton,char const *RightButton)
{
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      
      if(LeftButton!=0)
      {
      wsprintf(ws,percent_t,LeftButton);
      DrwStr(ws,18,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws,percent_t,RightButton);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      wsprintf(ws,percent_t,header);
      DrwStr(ws,5,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      GetDateTime(0,&time);
      wsprintf(ws,"%02d:%02d",time.hour,time.min);
      DrwStr(ws,scr_w-font_size*3,4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
     
      tmp=scr_h/11.6;
      int i;
      for(i=0;i<num;i++)
      {
      wsprintf(ws,percent_t,list[i]);
      if (control==i&&i<change) DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      
      for (int i=0;i<boxend;i++)
      {
        if (data[i]) draw_pic(wd_on,scr_w-font_size*2,4+tmp*(i+1));
          else draw_pic(wd_off,scr_w-font_size*2,4+tmp*(i+1));
      }
      
      
      for (int i=boxend;i<datanum+boxend;i++)
      {
        wsprintf(ws, "%02d",data[i+fix]);
        if(control==i+fix)
        DrwStr(ws,scr_w-font_size*2,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,scr_w-font_size*2,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
}

const char percent_d[]="%02d";
const char minus[]="-";
const char colon[]=":";

void DrawData(unsigned int num,unsigned int data[])
{
      tmp=scr_h/11.6;
      int c=font_size*1.5;

      for(int i=0;i<4;i++)  
      {  
      wsprintf(ws,percent_d,data[i+4]);
      
      if (num==i+4)
        DrwStr(ws,scr_w-font_size*3.5+i%2*c,6+tmp*(5+i/2),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,scr_w-font_size*3.5+i%2*c,6+tmp*(5+i/2),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      wsprintf(ws,minus);
      DrwStr(ws,scr_w-font_size*2.5,6+tmp*5,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws,colon);
      DrwStr(ws,scr_w-font_size*2.5,6+tmp*6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

}

void OnRedraw()
{
  switch(mode)
  {
  case 0:
    {
      CreateList(main_menu[mode],
                 menu,main_menu+1,9,9,
                 8,0,name2,0,
                 change,save);
    } break;

    
  case 1:
    {
      CreateList(main_menu[mode],
                 0,0,0,0,
                 5,0,status,0,
                 change,back);

      tmp=scr_h/11.6;
 
      for (int i=0;i<num_alarms;i++)
      {
        wsprintf(ws, "%t %d: %d:%02d",alarm_name,i+1,hour[i],min[i]);
        if (num_alarm==i) DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }

     
    } break;

 case 2:
    {
      CreateList(main_menu[mode],
                 amenu,alerts_menu,9,3,
                 3,6,amenus,1,
                 change,back);
      
      wsprintf(ws,"%02d-",amenus[3]);
      if(amenu==3)
      DrwStr(ws,scr_w-font_size*3.5,6+tmp*4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
      else
      DrwStr(ws,scr_w-font_size*3.5,6+tmp*4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
     }break; 

   case 3:
    {
      CreateList(main_menu[mode],
                 seven,wd2,8,7,
                 7,1,weeks,0,
                 change,back);
    } break; 
  
  case 4:
    {
      CreateList(main_menu[mode],
                 mmenu,mn,6,2,
                 2,4,miss,0,
                 change,back);
    }break; 
  
  case 5:
    {
      CreateList(main_menu[mode],
                 bmenu,bn,4,1,
                 1,3,bmenus,0,
                 change,back);
    }break; 
    
    case 6:
    {
      
      CreateList(main_menu[mode],
                 file,rn,6,2,
                 2,2,files,0,
                 change,back);
      
      DrawData(file,files);
    }break; 
    
    case 7:
    {
      CreateList(main_menu[mode],
                 call,rn,6,2,
                 2,2,calls,0,
                 change,back);

      DrawData(call,calls);
    }break; 
    
    case 8:
    {
      CreateList(main_menu[mode],
                 sms,rn,6,2,
                 2,2,smss,0,
                 change,back);
      
      DrawData(sms,smss);
    }break; 
    
    
  case 9:
    {
      CreateList(main_menu[mode],
                 onum,othern,8,4,
                 4,4,other,0,
                 change,back);    
    } break; 
    
    
  case 12:
    {
      CreateList(Alarm_name[num_alarm],
                 0,0,0,0,
                 0,0,0,0,
                 0,0);
      
      if(status[num_alarm]==1) draw_pic(st_on,scr_w/2-25,HeaderH());
        else draw_pic(st_off,scr_w/2-25,HeaderH());

      if ((edit_level==1)||(edit_level==3))
        {
          wsprintf(ws,"%t",change);
          DrwStr(ws,18,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
      
      wsprintf(ws,"%t",ok);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      int x=scr_w/2-font_size*0.5;
      if (status[num_alarm])         wsprintf(ws,"%t", on);
          else 
          {
        wsprintf(ws,"%t",off);
            x-=3;
          }

      if (edit_level==1) DrwStr(ws,x,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      x=scr_w/2-GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)-GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL);      
        int b=HeaderH()+60+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      if ((edit_level==2)&&(set==1))
        DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
      x=scr_w/2;
      wsprintf(ws, ":");
      DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      x+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      if ((edit_level==2)&&(set==2))
        DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      x=scr_w/7.3;
      b=scr_h-SoftkeyH()-font_size-24;
      for (int i=0;i<7;i++)
      {
                wsprintf(ws,"%t", wd[i]);
        if ((edit_level==3)&&(set==i)) DrwStr(ws,4+x*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,4+x*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      b+=(font_size+3);
      for (int i=0;i<7;i++)
      {
        if (weekdays[num_alarm][i]) draw_pic(wd_on,5+x*i,b);
          else draw_pic(wd_off,5+x*i,b);
      }
    } break;
    
    
  case 13:
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
      
      if (show_icon)         wsprintf(ws,"%t", on);
        else         wsprintf(ws,"%t", off);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
    } break;  
    
    
  case 15:
    {
      CreateList(wd2[seven],
                 0,0,0,0,
                 0,0,0,0,
                 prev,next);
      
      tmp=scr_h/11.6;

      int x=scr_w/4;     
      int b=HeaderH()+font_size+4;
      int c=(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6;
      
      for(int i=0;i<dats;i++)  
      {
      wsprintf(ws, "%02d-%01d",i,day[seven][i]);
      int j=i/4;
      if ((dat==i))
        DrwStr(ws,4+(i-4*j)*x,b+j*c,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-4*j)*x,b+j*c,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
    } break;  
    
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

void control(unsigned int *name,unsigned int control)
{
  if (name[control]==1) name[control]=0; else name[control]=1;
}


int onkey(unsigned char keycode, int pressed)
{
  switch(mode)
  {
    case 0:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON: mode=menu+1; OnRedraw(); break;
            case LEFT_SOFT: 
              control(name2,menu);
              break;
            case RIGHT_SOFT:
              {
                save_settings();
                GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,"smartalerts");
                return(1);
              }
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (menu>0) menu--;
                  else menu=(menus-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (menu<(menus-1)) menu++;
                  else menu=0;
                  break;
              }
            case GREEN_BUTTON: runFile(bcfgfile1); break;
            case '0':runFile(ring);  break;
           /* 
            case '9':
                GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,"close");
                ShowMSG(1,(int)"主程序关闭中!");
                //runFile(sa);
                return(1);
               // break;
            
            case '1': break;
            case '2': break;
            case '3': break;
            case '4': break;
            case '5': break;
    
              */
            }
          }
      } break;
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
            case ENTER_BUTTON:
                 mode=12; OnRedraw(); break;
            case LEFT_SOFT: 
                 control(status,num_alarm);
                 break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
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
            case GREEN_BUTTON: runFile(bcfgfile); break;
            case '1': num_alarm=0; break;
            case '2': num_alarm=1; break;
            case '3': num_alarm=2; break;
            case '4': num_alarm=3; break;
            case '5': num_alarm=4; break;
            //case '6': num_alarm=5; break;
            case '#': mode=13; OnRedraw(); break;
            case '0':runFile(ring);  break;
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
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
              if(amenu<3)
              {
                control(amenus,amenu);
              }
              break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (amenu>0) amenu--;
                else amenu=10-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (amenu<(10-1)) amenu++;
                else amenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(amenu>2)
          {
               set=10;  
               if ((backup[set]<3&&(amenu==3||amenu==4))||
                   (backup[set]<6&&(amenu==5||amenu==7))||
                   (backup[set]<10&&(amenu==6||amenu==8))||
                   (backup[set]<1&&amenu==9))
               backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
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
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
                if(seven!=7)
                   mode=15; OnRedraw(); break;
            case LEFT_SOFT:
                if(seven!=7)
                {
                  control(weeks,seven);
                } break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            //case GREEN_BUTTON: open_bcfg(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (seven>0) seven--;
                  else seven=(sevens-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (seven<(sevens-1)) seven++;
                  else seven=0;
                  break;
              }
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
             {
               if(seven==7)
               {  
               set=4;
               if (backup[set]<6) 
               {
                  backup[set]=backup[set]*10+keycode-'0';
               }
               else
               {
                  backup[set]=keycode-'0';
               }
               edit();
               }
                break;
              }
            }
          }
      } break;   
      
     case 4:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
                if(mmenu<2)
                {
                control(miss,mmenu);
		}
                break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (mmenu>0) mmenu--;
                else mmenu=6-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (mmenu<(6-1)) mmenu++;
                else mmenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(mmenu>1)
          {
               set=6;  
               if ((backup[set]<3&&(mmenu==2||mmenu==3))||
                   (backup[set]<10&&mmenu==4)||
                   (backup[set]<2&&mmenu==5))
                {
                 backup[set]=backup[set]*10+keycode-'0';
                }
                else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
            }
            }
          }
      } break;    
      
      
     case 5:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
                if(bmenu==0)
                {
                control(bmenus,0);
                }
                break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (bmenu>0) bmenu--;
                else bmenu=4-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (bmenu<(4-1)) bmenu++;
                else bmenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(bmenu!=0)
          {
               set=5;  
               if ((backup[set]<2&&bmenu==3)||
                   (backup[set]<10&&(bmenu==1||bmenu==2)))
                backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
            }
            }
          }
      } break;   
      
     case 6:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
                if(file<2)
                {
                control(files,file);
                }
                break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (file>0) file--;
                else file=8-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (file<(8-1)) file++;
                else file=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(file>2)
          {
               set=7;  
               if ((backup[set]<10&&file==2)||
                   (backup[set]<1&&file==3)||
                   (backup[set]<2&&file==4)||
                   (backup[set]<4&&file==5)||
                   (backup[set]<3&&file==6)||
                   (backup[set]<6&&file==7))
                 backup[set]=backup[set]*10+keycode-'0';
               else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
            }
            }
          }
      } break;   
      
     case 7:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
                if(call<2)
                {
                control(calls,call);
		}
                break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (call>0) call--;
                else call=8-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (call<(8-1)) call++;
                else call=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(call>2)
          {
               set=8;  
               if ((backup[set]<10&&call==2)||
                   (backup[set]<1&&call==3)||
                   (backup[set]<2&&call==4)||
                   (backup[set]<4&&call==5)||
                   (backup[set]<3&&call==6)||
                   (backup[set]<6&&call==7)) 
                 backup[set]=backup[set]*10+keycode-'0';
               else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
            }
            }
          }
      } break;  
      
     case 8:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
                if(sms<2)
                {
                control(smss,sms);
                }
                break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (sms>0) sms--;
                else sms=8-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (sms<(8-1)) sms++;
                else sms=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(sms>2)
          {
               set=9;  
               if ((backup[set]<10&&sms==2)||
                   (backup[set]<1&&sms==3)||
                   (backup[set]<2&&sms==4)||
                   (backup[set]<4&&sms==5)||
                   (backup[set]<3&&sms==6)||
                   (backup[set]<6&&sms==7)) 
                 backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               edit();
               }
            }
            }
          }
      } break;  
      
    case 9:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT: 
              if(onum<4)
              {
              control(other,onum);
              }
              break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: runFile(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (onum>0) onum--;
                else onum=8-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (onum<(8-1)) onum++;
                else onum=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(onum>3)
          {
               set=11;  
               if  ((backup[set]<1&&(onum==4||onum==5))||
                   (backup[set]<10&&(onum==6||onum==7)))
               backup[set]=backup[set]*10+keycode-'0';
                else
                  backup[set]=keycode-'0';
               edit();
               }
          }
            }
          }
      } break;   
      
      
  case 12:
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
  case 13:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
        switch(keycode)
          {
          case LEFT_BUTTON: case '4': if (X>0) X-=5; else X=scr_w; break;
          case RIGHT_BUTTON: case '6': if (X<scr_w) X+=5; else X=0; break;
          case UP_BUTTON: case '2': if (Y>0) Y-=5; else Y=scr_h; break;
          case DOWN_BUTTON: case '8': if (Y<scr_h) Y+=5; else Y=0; break;
          }
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=1; break;
        case LEFT_SOFT: if (show_icon==1) show_icon=0; else show_icon=1; break;
        case LEFT_BUTTON: case '4': if (X>0) X--; else X=scr_w; break;
        case RIGHT_BUTTON: case '6': if (X<scr_w) X++; else X=0; break;
        case UP_BUTTON: case '2': if (Y>0) Y--; else Y=scr_h; break;
        case DOWN_BUTTON: case '8': if (Y<scr_h) Y++; else Y=0; break;
        default: mode=1; break;
        }
      }
    } break;
    
    
  case 15:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=3; break;
        case ENTER_BUTTON:
                          mode=3; OnRedraw(); break;
        case LEFT_SOFT:
          {
              if (seven>0) seven--;
                else seven=6;   
               OnRedraw(); break;
          }
        case RIGHT_SOFT: 
          {
             if (seven<6) seven++;
               else seven=0;
               OnRedraw(); break;
          }
        case UP_BUTTON:
           {
              if (dat>3) 
                dat=dat-4;
              else
                dat=dat+20;
              break;
           }
        case DOWN_BUTTON:
          {
            if (dat<20) 
                dat=dat+4;
            else
                dat=dat-20;
            break;
          }
        case LEFT_BUTTON:
          {
              if (dat>0) dat--;
                else dat=23;   
            break;
          }
        case RIGHT_BUTTON:
          {
              if (dat<23) dat++;
                else dat=0;
            break;
          }
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
                set=3;
                backup[set]=keycode-'0';
                edit();
                
            break;
          }
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SA cfg editor");
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
