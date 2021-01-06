#include "../inc/swilib.h"

#ifndef NEWSGOLD
#define DEFAULT_DISC "0"
#else
#define DEFAULT_DISC "4"
#endif

const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;


static const char *percent_t="%t";
int x,y=1;
int flag='mm';
char *nill="";
char mmenu[50]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


//#define mod


char text_bevel_col[4]={0,0,0,0x64};
char text_col[4]={255,255,255,0x64};
int fps=30;
int img_x=0;
int img_y=0;



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




int strh2int(char* str)
{
  int n,c=0;
  if (*(str+strlen(str)-1)=='h') *(str+strlen(str)-1)='\0';
  while ((*str!='h')&&(*str))
  {
    if ((*str>='a')&&(*str <='f')) n=*str-('A'-('9'+1))-('a'-'A');
    else if ((*str>='A')&&(*str<='F')) n=*str-('A'-('9'+1));
    else if ((*str>='0')&&(*str<='9')) n=*str;
    c=c*16+(n-'0');
    str++;
  }
  return c;
}

int str2int(const char *str)
{
  int n,c=0;
  while(*str!='\0')
  {
    n=*str;
    c=c*10+(n-'0');
    str++;
  }
  return c;
}

void RunEntry(char *entry)
{
  typedef int (*func)(void);
  func ff;
  ff=(func)strh2int(entry);
  if (ff!=NULL) SUBPROC((void *)(*ff));
}

void RunShort(char *fname)
{
  int (*ff) (void);
  ff=(int(*)(void))GetFunctionPointer(fname);
  if(ff!=NULL)
    SUBPROC((void*)(*ff));
  else
    ShowMSG(1,(int)"NULL pointer function!");
}

void RunFile(char *fname)
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,fname,strlen(fname)+1);
  ExecuteFile(ws,0,nill);
  FreeWS(ws);
}


void RunSub(char *sub_name)
{
  char *fname=DEFAULT_DISC ":\\RedButMenu.elf";
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,fname,strlen(fname)+1);
  ExecuteFile(ws,0,sub_name);
  FreeWS(ws);
}


typedef struct
{
  enum {F,S,E,SUB} RunType;      //слуэебный. тип запускаемого...(не смог подобрать слов)
  char Name[32];        //название
  char Command[128];    //что запускать
  char IconUnSel[128];  //путь к пнгшке(номер картинки в проше)
  char IconSel[10][128];  //путь к пнгшке(*кам)(номер картинки в проше)
  int x;            //координата
  int y;            //координата
  int Png_Count;        //количество пнг-шек в аимации(если есть)
  int Sel_PicIsPng;     //служ. ѕнг-шка ли у нас стоит на выделенном пункте
  int UnSel_PicIsPng;   //--||--
  int Hotkey;       //гор€ча€ клавиша
  char Pass[32];        //пароль
  int UseCurr;          //использовать курсор, или нет

}TItem;

typedef struct
{
  int x;
  int y;
  int pic;
}TIndicator;

char png_folder[128];
TItem Items[50];
TIndicator Accu,Net,Clock,Desc;     //аккум, сеть, часы и название
int NumOfItems=0;
int Rows, Cols;
char Row[5];
char Col[5];
char Bg[128];
IMGHDR *img_sel[10][50];
IMGHDR *img_unsel[50];
IMGHDR *bg;
IMGHDR *curr;
char cur[128]=DEFAULT_DISC":\\zbin\\menu\\cur.png";
int ena_cache=1;

int GetNumber(char *str)
{
  if (*(str+strlen(str)-1)=='h')
    return (strh2int(str));
  else return (str2int(str));
}



void FillCoords();
void deleteIMGHDR(IMGHDR *img);


int n=0;

int Icons_UnSel[50];
int Icons_Sel[50][2];//{перва€ картинка, кол-во картинок в анимации}
//////////////////

#define CTYPE1 8
#define CTYPE2 0

void FreeIcons()
{
  if (bg) deleteIMGHDR(bg);
  if (curr) deleteIMGHDR(curr);
  for (int i=0;i<NumOfItems;i++)
  {
    for (int j=0; j<=Items[i].Png_Count;j++)
    {if (img_sel[j][i]) deleteIMGHDR(img_sel[j][i]);}
    if (img_unsel[i]) deleteIMGHDR(img_unsel[i]);

  }
}

void FreeSingleIcon(int num)
{
  for (int j=0; j<=Items[num].Png_Count;j++)
  {if (img_sel[j][num]) {deleteIMGHDR(img_sel[j][num]); img_sel[j][num]=0;}}
}

/////////////////

char *pps="%s%s";

char *concat(char *s1,char *s2)
{
  int l;
  char *str=malloc((l=strlen(s1))+strlen(s2)+1);
  strcpy(str,s1);
  strcpy(str+l,s2);
  return str;
}

void FillIcons()
{
  int j;
  for (int i=0;i<NumOfItems;i++)
  {
    if (!Items[i].Sel_PicIsPng) {Icons_Sel[i][0]=GetNumber(Items[i].IconSel[0]);}
    else
    {
      for (j=0;j<=Items[i].Png_Count;j++)
      {
        if (strstr(Items[i].IconSel[j],":\\")==0)       //полный путь или нет...
          sprintf(Items[i].IconSel[j],concat(png_folder,Items[i].IconSel[j]));
      }
    }
    if (!Items[i].UnSel_PicIsPng) Icons_UnSel[i]=GetNumber(Items[i].IconUnSel);
    else
      if (strstr(Items[i].IconUnSel,":\\")==0)
        sprintf(Items[i].IconUnSel,concat(png_folder,Items[i].IconUnSel));

  }
}

int isFile(char *fname)
{
  return (strstr(fname,".")!=0);
}

int isSub(char *fname)
{
  return (strstr(fname,".sub")!=0);
}

void FillRunType()
{
  for (int i=0;i<NumOfItems;i++)
  {
    if (isSub(Items[i].Command)) Items[i].RunType=SUB;
    else if (isFile(Items[i].Command)) Items[i].RunType=F;
    else if ((strlen(Items[i].Command)==15)&&(strstr(Items[i].Command,"_")!=0))  Items[i].RunType=S;
    else Items[i].RunType=E;
  }
}

//int Accu_First;
//int Net_First;

void FillMisc()
{
  Rows=GetNumber(Row);
  Cols=GetNumber(Col);
}

void BruteForce(int num)
{
  int row=GetNumber(Row);
  int col=GetNumber(Col);
  for (int i=0;i<col;i++)
    for (int j=0;j<row;j++)
      if ((j*col+i)==num)
      {
        y=j;
        x=i;
        break;
      }
}

int count=0; //счетчик активных пунктов

void Parse(char *str)
{
  if (*str=='[')
  {
    if (NumOfItems++) n++;
    str++;
    if (!strncmp(str,"Item*",5))     //пункт выделенн
    {
      if (++count<=1) //чтобы не было нескольких активных пунктов
      {
        mmenu[0]=0;
        mmenu[n]=1;
        BruteForce(n);   //подбираем значен€ x и y дл€ n
      }
    }
    Items[n].UseCurr=1; //а вдрyг все-таки нужeн?..
    return;
  }
  if (!strncmp(str,"accu_x=",7))
  {
    str+=7;
    Accu.x=GetNumber(str);
    return;
  }
  if (!strncmp(str,"x=",2))
  {
    str+=2;
    Items[n].x=GetNumber(str) ;
    return;
  }
  if (!strncmp(str,"y=",2))
  {
    str+=2;
    Items[n].y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"command=",8))
  {
    str+=8;
    strcpy(Items[n].Command,str);
    return;
  }
  if (!strncmp(str,"name=",5))
  {
    str+=5;
    strcpy(Items[n].Name,str);
    return;
  }
  if (!strncmp(str,"icon_sel=",9))
  {
    str+=9;
    //
    Items[n].UseCurr=0;  //курсор нам не нужен
    if (isFile(str)) //это-файл
    {
      int i=0;
      Items[n].Sel_PicIsPng=1;
      while ((*str))
      {
        if (*str=='|') {Items[n].Png_Count++; i=0; str++; }      //считываем названи€ файлов до символа |
        else Items[n].IconSel[Items[n].Png_Count][i++]=*str++;
      }
    }
    else
    {
      Items[n].Sel_PicIsPng=0;
      strcpy(Items[n].IconSel[0],str);
    }

    return;
  }
  if (!strncmp(str,"icon_unsel=",11))
  {
    str+=11;
    strcpy(Items[n].IconUnSel,str);
    if (isFile(str)) //это-путь->иконка в пнг
      Items[n].UnSel_PicIsPng=1;
    else Items[n].UnSel_PicIsPng=0;
    return;
  }
  if (!strncmp(str,"anim_count=",11))
  {
    str+=11;
    Icons_Sel[n][1]=GetNumber(str);
    return;
  }
  if (!strncmp(str,"accu_y=",7))
  {
    str+=7;
    Accu.y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"net_x=",6))
  {
    str+=6;
    Net.x=GetNumber(str);
    return;
  }
  if (!strncmp(str,"net_y=",6))
  {
    str+=6;
    Net.y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"clock_x=",8))
  {
    str+=8;
    Clock.x=GetNumber(str);
    return;
  }
  if (!strncmp(str,"clock_y=",8))
  {
    str+=8;
    Clock.y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"desc_x=",7))
  {
    str+=7;
    Desc.x=GetNumber(str);
    return;
  }
  if (!strncmp(str,"desc_y=",7))
  {
    str+=7;
    Desc.y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"accu_pic=",9))
  {
    str+=9;
    Accu.pic=GetNumber(str);
    return;
  }
  if (!strncmp(str,"net_pic=",8))
  {
    str+=8;
    Net.pic=GetNumber(str);
    return;
  }
  if (!strncmp(str,"rows=",5))
  {
    str+=5;
    strcpy(Row,str);
    return;
  }
  if (!strncmp(str,"cols=",5))
  {
    str+=5;
    strcpy(Col,str);
    return;
  }
  if (!strncmp(str,"hotkey=",7))
  {
    str+=7;
    Items[n].Hotkey=GetNumber(str);
    return;
  }
  if (!strncmp(str,"pass=",5))
  {
    str+=5;
    strcpy(Items[n].Pass,str);
    return;
  }
  if (!strncmp(str,"bg_img=",7))
  {
    str+=7;
    strcpy(Bg,str);
    //ShowMSG(1,(int)Bg);
    return;
  }
  if (!strncmp(str,"text_col=",9))
  {
    int i=0;
    int j=0;
    char col[5];
    str+=9;
    for (j=0;j<4;j++)
    {
      i=0;
      while ((*str!=' ')&&(*str)) col[i++]=*str++;
      str++;
      col[i]='\0';
      text_col[j]=GetNumber(col);
    }
    return;
  }
  if (!strncmp(str,"bevel_col=",10))
  {
    int i=0;
    int j=0;
    char col[5];
    str+=10;
    for (j=0;j<4;j++)
    {
      i=0;
      while ((*str!=' ')&&(*str)) col[i++]=*str++;
      str++;
      col[i]='\0';
      text_bevel_col[j]=GetNumber(col);
    }
    return;
  }
  if (!strncmp(str,"img_fps=",8))
  {
    str+=8;
    fps=GetNumber(str) ;
    return;
  }
  if (!strncmp(str,"png_folder=",11))
  {
    str+=11;
    strcpy(png_folder,str);
    return;
  }
  if (!strncmp(str,"w_x=",4))
  {
    str+=4;
    img_x=GetNumber(str);
    return;
  }
  if (!strncmp(str,"w_y=",4))
  {
    str+=4;
    img_y=GetNumber(str);
    return;
  }
  if (!strncmp(str,"cur_pic=",8))
  {
    str+=8;
    strncpy(cur,str,strlen(str));
    cur[strlen(str)]='\0';
    return;
  }
  if (!strncmp(str,"cache=",6))
  {
    //    ShowMSG(1,(int)"aasd");
    str+=6;
    ena_cache=GetNumber(str);
    return;
  }
  if (*str==';') return;    //коментарии
}



char *cfg=DEFAULT_DISC":\\Zbin\\Menu\\Menu.cfg";
//char *cfg="0:\\Menu.cfg";


void Load_cfg()
{
  unsigned int ul;
  unsigned int size;
  int f;
  char *mem;
  char str[256]="";
  Accu.pic=-1;
  Net.pic=-1;
  f=fopen(cfg, A_ReadOnly + A_BIN, P_READ, & ul );
  if (f==-1)
  {
    ShowMSG(1,(int)"Can't open cfg");
    fclose(f,&ul);
    return;
  }
  mem=malloc(10000);
  if (mem!=0)
  {
    int i,j=0;
    size=fread(f,mem,9999,&ul);
    i=0;
    while (i<size)
    {
      j=0;
      while (((*(mem+i)!='\r')&&((*(mem+i)!='\n')))&&(i<size)) {*(str+j)=*(mem+i); j++;i++;}
      *(str+j)='\0';
      Parse(str);
      while (((*(mem+i)>'z')||(*(mem+i)<'a'))&&(*(mem+i)!='[')&&(*(mem+i)!=';')) i++;   //пропускаем нежелательные символы :)
    }
  }
  mfree(mem);
  fclose(f,&ul);
  FillIcons();
  FillRunType();
  FillMisc();
}










///////////////////////////////////////////////////////////////////////////////////////




void Menu();

int pic;

GBSTMR timer,timer2;
TTime time;
TDate date;

char pass[9];
char view[9];
int pos=0;

typedef struct {
  char R;
  char G;
  char B;
  char A;
}color;
////////////////////////////////////////////
void deleteIMGHDR(IMGHDR *img)
{
  mfree(img->bitmap);
  mfree(img);
}

IMGHDR *alpha(IMGHDR *img, char a, int nw, int del)
{
  int i;
  color *r=(color*)img->bitmap;
  for(i=0;i<img->h*img->w; i++, r++)
    if(r->A>a)
      r->A-=a;
    else
      r->A=0;
    return img;
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

////////////////////////////////////////////



int png_pic=0;

void Menu()
{
  int h=ScreenH();
  int w=ScreenW();
  int w_c=1;
  int h_c=1;
  char clt[]={0xD1,0xDE,0xE7,0x64};
  int sel_x,sel_y,sel;
  WSHDR *ws=AllocWS(256);
  char const curbcol[]={0,0,0,80};
  char const bgcol[]={0,0,0,43};
  char const framecol[]={255,255,255,100};
  int i;
  int img_w,img_h,sel_w,sel_h;
  if ((strlen(Bg)==0))
  {
    void *canvasdata=BuildCanvas();
    DrawCanvas(canvasdata, img_x, img_y, w, h, 0);
  }
  else
  {
#ifdef mod
    void *canvasdata=BuildCanvas();
    DrawCanvas(canvasdata, img_x, img_y, w, h, 0);
#endif
    if (!bg) {bg=CreateIMGHDRFromPngFile(Bg,CTYPE2);}
    DrwImg(bg,img_x,img_y,GetPaletteAdrByColorIndex(0),
           GetPaletteAdrByColorIndex(1));
  }
  for (i=0;i<NumOfItems;i++)
  {
    if (mmenu[i]==1)         //если выделенный пункт...
    {
      int t;
      t=(Items[i].UnSel_PicIsPng)?((int)Items[i].IconUnSel):(Icons_UnSel[i]);
      img_w=GetImgWidth(t);
      img_h=GetImgHeight(t);
      t=(Items[i].Sel_PicIsPng)?((int)Items[i].IconSel):(Icons_Sel[i][0]);
      sel_w=GetImgWidth(t);
      sel_h=GetImgHeight(t);
      sel=i;
      sel_x=Items[i].x;
      sel_y=Items[i].y;
      if (sel_w>img_w) sel_x=Items[i].x-((sel_w-img_w)/2);
      else sel_x=Items[i].x+((img_w-sel_w)/2);
      if (sel_h>img_h) sel_y=Items[i].y-((sel_h-img_h)/2);
      else sel_y=Items[i].y+((img_h-sel_h)/2);
    }
    else    //пункт невыделенный
    {
#ifndef mod
      if (Items[i].UnSel_PicIsPng)      //картинка в пнг
      {
        if (!img_unsel[i]) img_unsel[i]=CreateIMGHDRFromPngFile(Items[i].IconUnSel,CTYPE2);
        DrwImg(img_unsel[i],Items[i].x,Items[i].y,GetPaletteAdrByColorIndex(0),
               GetPaletteAdrByColorIndex(1));
      }
      else DrawImg(Items[i].x,Items[i].y,(int)Icons_UnSel[i]);
#endif
    }
  }
  wsprintf(ws,percent_t,Items[sel].Name);
  DrawString(ws,Desc.x,Desc.y,w,h,FONT_SMALL,32,text_col, text_bevel_col);
  GetDateTime(&date,&time);
  wsprintf(ws,"%02i:%02i",time.hour,time.min);
  DrawString(ws,Clock.x,Clock.y,w,h,FONT_SMALL,32,text_col,text_bevel_col);
  if (Items[sel].UseCurr==0)      //если указана иконка выделенного пункта
  {
    if (Items[sel].Sel_PicIsPng==1)     //если иконка в пнг
    {
      if (!img_sel[png_pic][sel]) img_sel[png_pic][sel]=CreateIMGHDRFromPngFile(Items[sel].IconSel[png_pic],CTYPE2);
      DrwImg(img_sel[png_pic][sel],sel_x,sel_y,GetPaletteAdrByColorIndex(0),
             GetPaletteAdrByColorIndex(1));
      if (flag=='mm') png_pic++;
      if ((png_pic>Items[sel].Png_Count)) png_pic=0;
    }
    else    //из прошивки
    {
      DrawImg(sel_x,sel_y,pic);
      if ((flag=='mm'))         //чтоб анмаци€ не поигравалась, кода окошко доп. инф-ии активно
      {
        if (pic>=Icons_Sel[sel][0]+Icons_Sel[sel][1]-1) pic=Icons_Sel[sel][0];
        else pic++;
      }
    }
  }
  else      //иконка не указана->рисуем курсорчег
  {
    int t2;
    t2=(Items[sel].UnSel_PicIsPng)?((int)Items[sel].IconUnSel):(Icons_UnSel[sel]);
    int iw=GetImgWidth(t2);
    int ih=GetImgHeight(t2);
    int ch=GetImgHeight((int)cur);
    int cw=GetImgWidth((int)cur);
    //рисуем картинку невыделенного пункта
#ifndef mod
    if (Items[i].UnSel_PicIsPng)
    {
      if (!img_unsel[sel]) img_unsel[sel]=CreateIMGHDRFromPngFile(Items[sel].IconUnSel,CTYPE2);
      DrwImg(img_unsel[sel],Items[sel].x,Items[sel].y,GetPaletteAdrByColorIndex(0),
             GetPaletteAdrByColorIndex(1));
    }
    else DrawImg(Items[sel].x,Items[sel].y,(int)Icons_UnSel[sel]);
#endif


    /////
    if (!curr) curr=CreateIMGHDRFromPngFile(cur,CTYPE2);       //курсорчег
#ifdef mod
    DrwImg(curr, Items[sel].x, Items[sel].y,GetPaletteAdrByColorIndex(0),
           GetPaletteAdrByColorIndex(1));
#else
    DrwImg(curr, (Items[sel].x+iw-(cw/2)), (Items[sel].y+ih-(ch/2)),GetPaletteAdrByColorIndex(0),
           GetPaletteAdrByColorIndex(1));
#endif
  }

  if (Accu.pic>0)        //если не указана картинка, то не показывать
  {
    if (*RamCap()>=3)DrawImg(Accu.x, Accu.y, Accu.pic);
    if (*RamCap()>=7) DrawImg(Accu.x, Accu.y, Accu.pic+1);
    if (*RamCap()>=17) DrawImg(Accu.x, Accu.y, Accu.pic+2);
    if (*RamCap()>=25) DrawImg(Accu.x, Accu.y, Accu.pic+3);
    if (*RamCap()>=32) DrawImg(Accu.x, Accu.y, Accu.pic+4);
    if (*RamCap()>=40) DrawImg(Accu.x, Accu.y, Accu.pic+5);
    if (*RamCap()>=47) DrawImg(Accu.x, Accu.y, Accu.pic+6);
    if (*RamCap()>=55) DrawImg(Accu.x, Accu.y, Accu.pic+7);
    if (*RamCap()>=62) DrawImg(Accu.x, Accu.y, Accu.pic+8);
    if (*RamCap()>=70) DrawImg(Accu.x, Accu.y, Accu.pic+9);
    if (*RamCap()>=78) DrawImg(Accu.x, Accu.y, Accu.pic+10);
    if (*RamCap()>=85) DrawImg(Accu.x, Accu.y, Accu.pic+11);
  }
  RAMNET *rn=RamNet();
  if (Net.pic>0)   //если не указана картинка, то не показывать
  {
    if (rn->power<=139) DrawImg(Net.x,Net.y, Net.pic);
    if (rn->power<=126) DrawImg(Net.x,Net.y, Net.pic+1);
    if (rn->power<=113) DrawImg(Net.x,Net.y, Net.pic+2);
    if (rn->power<=100) DrawImg(Net.x,Net.y, Net.pic+3);
    if (rn->power<=87) DrawImg(Net.x,Net.y, Net.pic+4);
    if (rn->power<=74) DrawImg(Net.x,Net.y, Net.pic+5);
  }
  if (flag=='wi')
  {
    TDate date;
    TTime time;
    GetDateTime(&date,&time);
    int size=GetFontYSIZE(FONT_SMALL);
    DrawRoundedFrame( 0, 0, w, h, 0, 0, 0, curbcol, bgcol );
    DrawRoundedFrame( w/2-50*w_c, h/2-40*h_c, w/2+50*w_c, h/2+40*h_c, 7, 7, 0, framecol, curbcol );
    WSHDR *ws1 = AllocWS(256);
    wsprintf(ws1, "%t: %i:%02i:%02i","¬рем€",time.hour,time.min,time.sec);
    DrawString(ws1,w/2-45*w_c,h/2-37*h_c,w,h,FONT_SMALL,32,clt,GetPaletteAdrByColorIndex(1));
    wsprintf(ws1, "RAM: %i Kb",GetFreeRamAvail()/1024);
    DrawString(ws1,w/2-45*w_c,h/2-17*h_c,w,h,FONT_SMALL,32,clt,GetPaletteAdrByColorIndex(1));
    wsprintf(ws1, "%i,%03i=%i%%, %i∞C",GetAkku(0,2)/1000,GetAkku(0,2)%1000,*RamCap(),(GetAkku(1,3)-0xAAA+15)/10);
    DrawString(ws1,w/2-45*w_c,h/2+3*h_c,w,h,FONT_SMALL,32,clt,GetPaletteAdrByColorIndex(1));
    RAMNET *rn=RamNet();
    char* std;
    if (rn->ch_number>=255) std="GSM 1800"; else {if (rn->ch_number>=128) std="EGSM 900"; else std="GSM 900";};
    wsprintf(ws1, "%i db,%s",rn->power,std);
    DrawString(ws1,w/2-45*w_c,h/2+23*h_c,w,h,FONT_SMALL,32,clt,GetPaletteAdrByColorIndex(1));
    FreeWS(ws1);
  }
  if (flag=='pw')          //окошко пассворда
  {
    WSHDR *ws2 = AllocWS(256);
    DrawRoundedFrame( 0, 0, w, h, 0, 0, 0, curbcol, bgcol );
    wsprintf(ws2,"%s","Enter Password");
    DrawString(ws2,w/2-45,h/2-10-GetFontYSIZE(FONT_SMALL),w,h,FONT_SMALL,32,clt,GetPaletteAdrByColorIndex(1));
    DrawRoundedFrame( w/2-45, h/2-10, w/2+45, h/2+10, 0, 0, 0, framecol, curbcol );
    wsprintf(ws2,"%s",view);
    DrawString(ws2,w/2-45*w_c+2,h/2-10*h_c+3,w,h,7,32,clt,GetPaletteAdrByColorIndex(1));
    FreeWS(ws2);
  }
  FreeWS(ws);
  GBS_StartTimerProc(&timer,216/fps,Menu);
}




void OnRedraw(MAIN_GUI *data)
{
  pic=Icons_Sel[y*Cols+x][0];
  Menu();
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeIcons();
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  REDRAW();
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  GBS_DelTimer(&timer);
  if (data->gui.state!=2) return;
  data->gui.state=1;
}



void run()
{
  char *file=malloc(strlen(Items[y*Cols+x].Command)+1);
  strcpy(file,Items[y*Cols+x].Command);
  char type;
  type=Items[y*Cols+x].RunType;
  switch (type)
  {
  case F:RunFile(file);break;
  case S:RunShort(file);break;
  case E:RunEntry(file);break;
  case SUB:RunSub(file);break;
  }
  mfree(file);
}




int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    if (flag!='pw')
    {
      switch(msg->gbsmsg->submess)
      {
      case RED_BUTTON: {if (flag=='mm') return (1); else flag='mm'; REDRAW(); } break;
      case ENTER_BUTTON:
        {
          pos=0;
          view[0]='\0';
          pass[0]='\0';
          if (strlen(Items[y*Cols+x].Pass)==0)  run();
          else {flag='pw'; REDRAW();}
        } break;
      case LEFT_BUTTON:
        {
          if (flag=='mm')
          {
            mmenu[y*Cols+x]=0;
            if (!ena_cache) FreeSingleIcon(y*Cols+x);
            mmenu[y*Cols+(x=(x-1+Cols)%Cols)]=1;
            REDRAW();
          }
        }break;
      case UP_BUTTON:
        {
          if (flag=='mm')
          {
            mmenu[y*Cols+x]=0;
            if (!ena_cache) FreeSingleIcon(y*Cols+x);
            mmenu[(y=(y-1+Rows)%Rows)*Cols+x]=1;
            REDRAW();
          }
        }break;
      case RIGHT_BUTTON:
        {
          if (flag=='mm')
          {
            mmenu[y*Cols+x]=0;
            if (!ena_cache) FreeSingleIcon(y*Cols+x);
            mmenu[y*Cols+(x=(x+1+Cols)%Cols)]=1;
            REDRAW();
          }
        }break;
      case DOWN_BUTTON:
        {
          if (flag=='mm')
          {
            mmenu[y*Cols+x]=0;
            if (!ena_cache) FreeSingleIcon(y*Cols+x);
            mmenu[(y=(y+1+Rows)%Rows)*Cols+x]=1;
            REDRAW();
          }
        } break;

      case 0x04:
        {
#ifdef NEWSGOLD
          return(1);
#else
          flag=(flag=='mm')?'wi':'mm'; REDRAW();
#endif
        }
#ifdef NEWSGOLD
      case 0x01:
        {
          flag=(flag=='mm')?'wi':'mm'; REDRAW();
        }break;
#endif
      case GREEN_BUTTON:  //разворачиваем окошко
        {

        }break;
      }
      for (int i=0;i<NumOfItems;i++)
      {
        if (msg->gbsmsg->submess==Items[i].Hotkey)      //”важаемые туристы, сейчас наш путь пройдет через
        {                                             //∆ќѕ”, так что сильно не засматривайтесь
          if (flag=='mm')
          {
            mmenu[y*Cols+x]=0;
            BruteForce(i);   //находим x и y
            mmenu[y*Cols+x]=1;
            REDRAW();
            pos=0;
            view[0]='\0';
            pass[0]='\0';
            if (strlen(Items[y*Cols+x].Pass)==0) run();
            else {flag='pw'; REDRAW();}
          }
        }
      }
    }
    else
    {
      if ((msg->gbsmsg->submess>='0')&&(msg->gbsmsg->submess<='9'))
        if (pos<=8)
        {
          pass[pos]=msg->gbsmsg->submess;
          view[pos]='*';
          pos++;
          pass[pos]='\0';
          view[pos]='\0';
          REDRAW();
        }
      if (msg->gbsmsg->submess==RED_BUTTON)
      {flag='mm';REDRAW();}
      if (msg->gbsmsg->submess==ENTER_BUTTON)
      {
        if ((!strcmp(pass,Items[y*Cols+x].Pass))&&(*pass!='\0')) {flag='mm'; REDRAW();  run();}
        else
        {
          ShowMSG(1,(int)"Incorrect Password");
          flag='mm';
          REDRAW();
        }
      }
    }
  }

  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}

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

const RECT Canvas={0,0,131,175};
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
  Load_cfg();

}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&timer);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Menu");
  FreeWS(ws);
}




int main(char *exename, char *fname)
{
  *cfg=*cur=*exename; //прописываем правильную букоффку диска-)
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();
  return 0;
}
