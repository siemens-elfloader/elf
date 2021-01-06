#include "swilib.h"
#include "cfg_items.h"
#include "conf_loader.h"
#include "rect_patcher.h"

const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;




extern const unsigned int ipp;

CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);
int sock;
int connect_state;
char buf[65536];
int pbuf;


int receive;
 //intprogressbar=2;



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

int loaded;

typedef struct
{
  //char author[32];
  char date[64];
  char comm[4096]; 
  char title[64];
  char link[64];
  
  int num;
  char flag;
  unsigned int mood;  
}RSS;

RSS items[75];
char *item[75];
int length;


int x,y;
int mode;


//================================================

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};
const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};

unsigned int char8to16(int c)
{
  if (c>=128)
  {
    //Win->Dos
    c=wintranslation[c-128];
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {  
    if(c!=0xE) wsAppendChar(ws,char8to16(c));
  }
}
//===========================================

void create_connect(void)
{
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    //sa.ip=htonl(IP_ADDR(83,222,3,55));
    //sa.ip=htonl(IP_ADDR(85,112,149,157));
    //sa.ip=htonl(IP_ADDR(74,55,2,115));
    sa.ip=htonl(ipp);


    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      receive=1;
      REDRAW();
    }
    else
      closesocket(sock);
  }
}

void do_start_connection(void)
{
  SUBPROC((void *)create_connect);
  receive=0;
}

char req_buf[256];

void send_req(void)
{
  sprintf(req_buf,"GET /rss/ HTTP/1.0\r\nHost: www.bash.org.ru\r\n\r\n");
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
}



void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    
  }
}

extern const unsigned int limit;


void get_answer(void)
{
  int i=pbuf;
  if (i==limit)
    end_socket();
  else
  {
    i=recv(sock,buf+i,limit-i,0);
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}

//===========================================


int atoi(char *attr)
{
  int ret=0;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else {return (ret);}
  }
  
}


void GetMood(int xs);

void Parsing()
{
  
  item[0]=strstr(buf,"<item>");
  
  for (int j=1; j!=75; j++)
  {
    item[j]=strstr(item[j-1]+5,"<item>");
  }
  
  length=atoi(strstr(buf,"Content-Length: ")+16);
  
  for(int i=0; i!=75; i++)
  {
    //snprintf(items[i].author,32,"%s",strstr(item[i],"<author>")+8);
    //  for (int j=1; j!=33 ;j++) {if ((items[i].author)[j]=='<') {(items[i].author)[j]=0; break;}}
     
    
    //snprintf(items[i].date,64,"%s",strstr(item[i],"Date")+5);
    strncpy(items[i].date,strstr(item[i],"Date")+5,64);
    
    items[i].flag = atoi(strstr(items[i].date,"+")+1); 
    if (items[i].flag!=0) {loaded++;}
    
      for (int j=1; j!=65 ;j++) {if ((items[i].date)[j]=='+') {(items[i].date)[j]=0; break;}}
    
    
    
    
    //snprintf(items[i].comm,4096,"%s",strstr(item[i],"CDATA")+6);
    strncpy(items[i].comm,strstr(item[i],"CDATA")+6,4096);
      for (int j=0; j!=4097 ;j++) {
        
        if ((items[i].comm)[j]==']' && (items[i].comm)[j+1]==']') {(items[i].comm)[j]=0; break;}
        if ((items[i].comm)[j]=='&' && (items[i].comm)[j+1]=='l') {(items[i].comm)[j]='«'; (items[i].comm)[j+1]=0xE; (items[i].comm)[j+2]=0xE; (items[i].comm)[j+3]=0xE; }
        if ((items[i].comm)[j]=='<' && (items[i].comm)[j+1]=='b') {(items[i].comm)[j]=0xD; (items[i].comm)[j+1]=0xE; (items[i].comm)[j+2]=0xE; (items[i].comm)[j+3]=0xE; }
        if ((items[i].comm)[j]=='&' && (items[i].comm)[j+1]=='g') {(items[i].comm)[j]='»'; (items[i].comm)[j+1]=0xE; (items[i].comm)[j+2]=0xE; (items[i].comm)[j+3]=0xE; }
        if ((items[i].comm)[j]=='&' && (items[i].comm)[j+1]=='q') {(items[i].comm)[j]='"'; (items[i].comm)[j+1]=0xE; (items[i].comm)[j+2]=0xE; (items[i].comm)[j+3]=0xE; (items[i].comm)[j+4]=0xE; (items[i].comm)[j+5]=0xE; }
       }
    

    //snprintf(revis[i].elf,32,"%s",strstr(item[i],"/ARM/")+5);
    //  for (int j=1; ;j++) {if ((revis[i].elf)[j]=='/' || (revis[i].elf)[j]==' ') {(revis[i].elf)[j]=0; break;}}
      
      //snprintf(items[i].title,64,"%s",strstr(item[i],"<title>")+7);
      strncpy(items[i].title,strstr(item[i],"<title>")+7,64);
      for (int j=1; j!=65 ;j++) {if ((items[i].title)[j]=='<') {(items[i].title)[j]=0; break;}}
      
      
      //snprintf(items[i].link,64,"%s",strstr(item[i],"<link>")+6);
      strncpy(items[i].link,strstr(item[i],"<link>")+6,64);
      for (int j=1; j!=65 ;j++) {if ((items[i].link)[j]=='<') {(items[i].link)[j]=0; break;}}
      
      
    items[i].num=atoi(strstr(item[i],"uote/")+5);
    items[i].mood=255;  
  }
 REDRAW();
 receive=2;
}




//-------------------------------Input msg------------------------------//


int _id;
const HEADER_DESC _hdr={0,0,131,21,NULL,(int)"Show quote",LGP_NULL};
int _onkey(GUI *data, GUI_MSG *msg)
{/*
  WSHDR *ws=AllocWS(64);
  if (msg->keys==0x0FFF || msg->keys==VOL_DOWN_BUTTON)//0xFFF
  {
    EDITCONTROL ec;
    char *s;
    ExtractEditControl(data,2,&ec);	
    ws=ec.pWS;
  }*/
  if(msg->keys==LEFT_SOFT || msg->keys==RED_BUTTON)
  {
	return 1;
  }
return(0);
}

void _ghook(GUI *gui, int cmd)
{ 
 // static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Exit"};
/*  if (cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);
  }*/
  if(cmd==0xA)
  {
    DisableIDLETMR();
  }
  if (cmd==0x0C)
  {
    EDIT_SetCursorPos(gui,1);
  }
  if(cmd==0x03){}
}

void _locret(void){}

SOFTKEY_DESC _sk[]=
{
  {0x0018,0x0000,(int)"ok"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB _skt=
{
  _sk,0
};

const INPUTDIA_DESC _desc=
{
  1,
  _onkey,
  _ghook,
  (void *)_locret,
  0,
  &_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  0x00000000,
  0x40000000
};

void CreateEC(int i)
{    
   void *ma=malloc_adr();
   void *eq=AllocEQueue(ma, mfree_adr());
   EDITCONTROL ec;
   PrepareEditControl(&ec);

   WSHDR *ws=AllocWS(10240);   
   WSHDR *wss=AllocWS(10240);
   
   ascii2ws(ws,items[x].date);
/*   wsInsertChar(ws,'\r',ws->wsbody[0]+1);
   wsInsertChar(ws,'\n',ws->wsbody[0]+2);*/
   ascii2ws(wss,items[x].comm);
   wstrcat(ws,wss);
   
   ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,ws->wsbody[0]);
   AddEditControlToEditQend(eq,&ec,ma);
   
   patch_header(&_hdr);
   patch_input(&_desc);
   
   FreeWS(ws);
   FreeWS(wss); 
   _id=CreateInputTextDialog(&_desc,&_hdr,eq,1,0);
}
//===========================================


extern const char hist_path[64];
extern const unsigned int ic;

const char _fstr[]="%s\\q%i.bash";
const char _oktotorp[]="#";


void GetMood(int xs)
{  
  if(items[xs].mood==255) 
  {
  int xx=0;
  char path[96]; 
  sprintf(path,"%s\\q%i.bash",hist_path,atoi(strstr(items[xs].title,_oktotorp)+1 ) );
  unsigned int ul;
  int f;
  char* buffer;
  FSTATS StatBuffer;
 
  int size;
  if ((f=fopen(path,A_ReadOnly,P_READ,&ul))!=-1)
      {
        GetFileStats(path,&StatBuffer,&ul);
        size=StatBuffer.size;
        buffer=malloc(size);
        fread(f, buffer,size, &ul);

        xx=atoi(strstr(buffer,"MOOD: ")+6);

        fclose(f,&ul);
        mfree(buffer);
        items[xs].mood=30;
      }
  items[xs].mood=xx;
  }  
}

extern const char ic_path[64];

void DrawMoodIcon(int x, int y, int ic)
{
  char pth[96];
  
  sprintf(pth,"%s\\%i.png",ic_path,ic);
  DrawImg(x,y,(int)pth);
}



void Save(int xs)
{
  const int def_mood=30;
  
  char path[96]; 
  sprintf(path,"%s\\q%i.bash",hist_path,atoi(strstr(items[xs].title,_oktotorp)+1 ) );
  
  char buff[4096];
  sprintf(buff,"QUOTE: %s\n\rDATE: %s\n\rMOOD: %i\n\r ",items[xs].comm,items[xs].date,def_mood);
  items[xs].mood=def_mood;
    
  unsigned int ul;  
  int f=fopen(path,A_WriteOnly+A_Create,P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,buff,strlen(buff),&ul);
    fclose(f,&ul);
    REDRAW();
    
  }
}

void SaveAll(void)
{  
  for (int h=0; h<(loaded-1); h++)
  {
    Save(h);
  }
  REDRAW();   
}

//===========================================

void Info()
{
  WSHDR *ws = AllocWS(128);
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(1));
  if(receive==2)
  {
    ascii2ws(ws,items[x].title);
    DrawString(ws,5,25,ScreenW()-5,ScreenH()-5,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
    ascii2ws(ws,items[x].link);
    DrawString(ws,5,25+GetFontYSIZE(FONT_SMALL),ScreenW()-5,ScreenH()-5,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
  }    
  else return;  
  FreeWS(ws);  
}



void OnRedraw(MAIN_GUI *data)
{ 
  WSHDR *ws = AllocWS(4096);
  WSHDR *wsx = AllocWS(4096);
//  DisableIconBar(1);
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(1));
  int y1=YDISP;
  int bar=7;  
  
  if(receive==2) {bar=4;}
  if(receive==0) {bar=2;}
  if(receive==1) {  if(pbuf==0) {bar=22;} else {bar=7;} }
  
  
  DrawRoundedFrame(ScreenW()/2,y1+5,ScreenW()-5,y1+10,0,0,0,GetPaletteAdrByColorIndex(bar),GetPaletteAdrByColorIndex(23));
  DrawRoundedFrame(ScreenW()/2,y1+5,ScreenW()/2+(pbuf*(ScreenW()/2-5)/limit),y1+10,0,0,3,GetPaletteAdrByColorIndex(bar),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws, "%i/%i",pbuf,limit);
  DrawString(ws,5,y1+15,ScreenW()-3,ScreenH()-1,FONT_SMALL,4,GetPaletteAdrByColorIndex((receive==2)?4:22),GetPaletteAdrByColorIndex(23));   
  
  if(receive==2)
  {      
   if (mode==0)
   {
       int k=sdiv(GetFontYSIZE(FONT_SMALL),(ScreenH()-(3*GetFontYSIZE(FONT_SMALL)))-5);//кол-во итемов
/*       wsprintf(wsx, "%d/%d %d %d",loaded,k,-(k/2),k/2); 
       DrawString(wsx,3,3,128,35,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));*/
       wsprintf(wsx, "Loaded %d",loaded); 
       DrawString(wsx,3,y1+3,128,y1+35,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       if(k<loaded) k=loaded;
       for(int i=-2;i<(k/2)-2;i++)
       {
        if (items[x+i].flag!=0 && x+i>-1 && i!=0)  
        { 
          ascii2ws(ws,items[x+i].title);    
         //DrawString(ws,35,20,128,35,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
         
          if(ic)
          {
           GetMood(x+i);  
           DrawMoodIcon(110,19,items[x+i].mood);
          }
          
          wsprintf(wsx, "%i  %w",x+i,ws); 
          DrawString(wsx,3,y1+30+((i+2)*GetFontYSIZE(FONT_SMALL)),128,y1+35+((i+3)*(GetFontYSIZE(FONT_SMALL)*2)),FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
         }
       }
           
    //-------------------------------  
      /*if (items[x-2].flag!=0 && x-2>-1)  
      {
        ascii2ws(ws,items[x-2].title);    
       //DrawString(ws,35,20,128,35,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
        if(ic)
        {
         GetMood(x-2);  
         DrawMoodIcon(110,19,items[x-2].mood);
        }
        
        wsprintf(wsx, "%i  %w",x-2,ws); 
        DrawString(wsx,3,20,128,35,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
    //-------------------------------
      if (items[x-1].flag!=0 && x-1>-1)  
      {
        ascii2ws(ws,items[x-1].title);  
       //DrawString(ws,35,40,128,55,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
        if(ic)
        {
         GetMood(x-1);  
         DrawMoodIcon(110,39,items[x-1].mood);
        }        
        wsprintf(wsx, "%i  %w",x-1,ws); 
        DrawString(wsx,3,40,128,55,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }*/
    //-------------------------------
    
        ascii2ws(ws,items[x].title);  
       //DrawString(ws,35,60,128,75,7,32,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
       
        if(ic)
        {
         GetMood(x); 
         DrawMoodIcon(110,y+29+(GetFontYSIZE(FONT_SMALL)*2),items[x].mood);
        }
        
        wsprintf(wsx, "%i  %w",x,ws); 
        DrawString(wsx,3,y1+30+(GetFontYSIZE(FONT_SMALL)*2),128,y1+35+(GetFontYSIZE(FONT_SMALL)*3),FONT_SMALL,32,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
    
    //-------------------------------
      /*if (items[x+1].flag!=0)  
      {
        ascii2ws(ws,items[x+1].title);  
       //DrawString(ws,35,80,128,95,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if(ic)
       {
         GetMood(x+1);
         DrawMoodIcon(110,79,items[x+1].mood);
       }        
  
       wsprintf(wsx, "%i  %w",x+1,ws); 
       DrawString(wsx,3,80,128,95,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
    //-------------------------------
      if (items[x+2].flag!=0)  
      {
        ascii2ws(ws,items[x+2].title);  
       //DrawString(ws,35,100,128,115,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if(ic){
       GetMood(x+2);   
       DrawMoodIcon(110,99,items[x+2].mood);
       }
        
        wsprintf(wsx, "%i  %w",x+2,ws); 
       DrawString(wsx,3,100,128,115,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }*/
    //-------------------------------  
      DrawRoundedFrame(2,ScreenH()-(5*GetFontYSIZE(FONT_SMALL)),ScreenW()-3,ScreenH()-3,0,0,0,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(1));
      ascii2ws(ws,items[x].comm);
      DrawString(ws,4,ScreenH()-(5*GetFontYSIZE(FONT_SMALL))+5,ScreenW()-5,ScreenH()-5,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }//if(mode==0)
  
  
    if (mode==1)
    {       
      DrawRoundedFrame(0,y1+0,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(1));  
      
      //ascii2ws(ws,items[x].author);
      //DrawString(ws,5,3+y*GetFontYSIZE(8),128,174,8,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
      
      ascii2ws(ws,"+1");
      DrawString(ws,5,y1+3+(y-1)*GetFontYSIZE(FONT_SMALL_BOLD),ScreenW()-5,ScreenH()-5,FONT_SMALL_BOLD,1,GetPaletteAdrByColorIndex( !(y-3)?2:0 ),GetPaletteAdrByColorIndex(23)); 
      
      ascii2ws(ws,"-1");
      DrawString(ws,5,y1+3+(y-1)*GetFontYSIZE(FONT_SMALL_BOLD),ScreenW()-5,ScreenH()-5,FONT_SMALL_BOLD,4,GetPaletteAdrByColorIndex( !(y-2)?2:0 ),GetPaletteAdrByColorIndex(23)); 
      
      wsprintf(ws,"%d/%d",x+1,loaded);
      DrawString(ws,5,y1+3+y*GetFontYSIZE(FONT_SMALL_BOLD),ScreenW()-5,ScreenH()-5,FONT_SMALL_BOLD,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
      
      ascii2ws(ws,items[x].date);
      DrawString(ws,5,y1+3+(y+2)*GetFontYSIZE(FONT_SMALL_BOLD),ScreenW()-5,ScreenH()-5,FONT_SMALL_BOLD,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
        
      ascii2ws(ws,items[x].comm);
      DrawString(ws,5,y1+3+(y+4)*GetFontYSIZE(FONT_SMALL),ScreenW()-5,ScreenH()-5,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
       
      DrawRoundedFrame(0,y1+0,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(23));
      
      //ascii2ws(ws,items[x].comm);
      //DrawString(ws,5,3+(y+1)*GetFontYSIZE(7),128,174,7,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    }  
  }//if(recive==2)
  
  
  if(receive==0)
  {
    wsprintf(ws, "No connect");
    DrawString(ws,25,y1+40,ScreenW()-5,ScreenH()-5,FONT_MEDIUM_BOLD,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(22));  
  }    
  FreeWS(ws);
  FreeWS(wsx);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT: if (mode==0) { return 1; } else { mode=0; } REDRAW(); break;
    
    case GREEN_BUTTON: do_start_connection(); break;
    
    case '6': case RIGHT_BUTTON: if (mode==1)  {x=(x+1)%(loaded);  y=0;}                         REDRAW(); break;
    case '4': case LEFT_BUTTON:  if (mode==1)  {x=(x+loaded-1)%(loaded); y=0; REDRAW();}  if (mode==0 && receive==2){Info();}   break;
    
    case '8': case DOWN_BUTTON: case VOL_DOWN_BUTTON: if (mode==0)  {x=(x+1)%(loaded);} if (mode==1)  {y--;}REDRAW(); break;
    case '2': case UP_BUTTON:   case VOL_UP_BUTTON:   if (mode==0) {x=(x+loaded-1)%(loaded);} if (mode==1)  {y++;}REDRAW(); break;
    
    case '5': case ENTER_BUTTON: mode=!mode; y=0; REDRAW(); break;
    
    case '*':  if(receive==2) {SaveAll(); REDRAW(); } break;
    case '#':  if(receive==2) {Save(x); REDRAW();}    break;
    case '0':  if(mode==1) CreateEC(x); REDRAW();     break;
    }
    
  }

  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    { 
    
    
    case '6': case RIGHT_BUTTON: if (mode==1)  {x=(x+1)%(loaded);  y=0;       REDRAW();} break;
    case '4': case LEFT_BUTTON:  if (mode==1)  {x=(x+loaded-1)%(loaded); y=0; REDRAW();}  break;
    
    case '8': case DOWN_BUTTON: case VOL_DOWN_BUTTON: if (mode==0)  {x=(x+1)%(loaded);} if (mode==1)  {y--;}REDRAW(); break;
    case '2': case UP_BUTTON:   case VOL_UP_BUTTON:   if (mode==0) {x=(x+loaded-1)%(loaded);} if (mode==1)  {y++;}REDRAW(); break;

    
    //case '*':  if(receive==2) {SaveAll(); REDRAW(); } break;
    //case '#':  if(receive==2) {Save(x); REDRAW();}    break;
    }
    
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
/*void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
kill_data(data,mfree_adr);
}*/

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
  (void *)kill_data,	
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{/*
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
  */
  MAIN_CSM*csm=(MAIN_CSM*)data;
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
//  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  //patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);  
  do_start_connection();  
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
    
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    InitConfig();
  }
  
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:

          //Если посылали запрос
          SUBPROC((void *)send_req);
          //progressbar=7;
          REDRAW();
        
        break;
      case ENIP_SOCK_DATA_READ:

          //Если посылали send
          SUBPROC((void *)get_answer);
          //progressbar=4;
          REDRAW();


        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        connect_state=0;
        //progressbar=21;
        //Save();
        Parsing();
        //progressbar=22;
        sock=-1;
        break;
      }
    }
    
  }
  return(1);
}

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

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Bash.org.ru");
}


int main(char *exename, char *fname)
{
  InitConfig();
  
  unsigned int err=0;
  mkdir(hist_path, &err);
  /*
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();
*/
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}
