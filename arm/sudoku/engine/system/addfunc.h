//addfunc.h - Библиотека дополнительных ф-ий

//Цвета RGBA {Красный (0-255), Зелёный (0-255), Синий (0-255), Альфа-Прозрачнсть (0-100)}

//Основные
char white[4]={255,255,255,100}; // = Белый 
char red[4]={255,0,0,100};       // = Красный
char green[4]={0,255,0,100};     // = Зелёный
char blue[4]={0,0,255,100};      // = Синий
char yellow[4]={255,255,0,100};  // = Жёлтый
char black[4]={0,0,0,100};       // = Чёрный
char alpha[4]={0,0,0,0};         // = Полностью прозрачный
//Дополнительные
char logo_color[4]={0xFF,0xFB,0xFF,0x64};   // = Белый с маленьким оттенком красного 
char logo_loadbar[4]={0xFC,0xCA,0x03,0x64}; // = Жёлтоватый
char white_85[4]={255,255,255,85};          // = Белый  85%
char msg_error[4]={250,0,0,70};             // = Красный - Ошибка!
char msg_info[4]={0,250,0,70};              // = Зелёный - Инфо!


#ifdef DEBUG
void debuglog(char *string)
{
  TDate date; TTime time; 
  
  char *t=malloc(512);
  sprintf(t,"%sdebug.log",elffolder);
  int logfile=fopen(t,A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  mfree(t);
  
  char *data=malloc(4096);
  GetDateTime(&date,&time);
  sprintf(data,">%d:%02d:%02d/%02d-%02d-%04d< = %s\r\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);
}
#else

void debuglog(char *string){}

#endif



void FULLREDRAW()
{
 TYPEREDRAW = 0;
 REDRAW();
}

void SMARTREDRAW()
{
 TYPEREDRAW = 1;
 REDRAW();
}



void fileext(char *path,char *filebody, int size) //Извлекает фаил из эльфы
{
 int file;
 unlink(path,0);
 file = fopen(path,A_WriteOnly+A_Create,P_WRITE,0);
 fwrite(file,filebody,size,0);
 fclose(file, 0);
}

int make_dirs(char *path) // Создаёт папки по путю, взято с SVN
{
  int c, i = 0;
  unsigned int io_error;
  char tmp[256], *s;
  strcpy(tmp, path);
  s = tmp;
  while((s = strchr(s, '\\')))
  {
    s++;
    c = *s;
    *s = 0;
    i += mkdir(tmp, &io_error);
    *s = c;
  }
  return (i);
}


int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24)
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
    else c-=8;
  c+=0x400;
  return (c);
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush) //Отрисовка IMGHDR
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

IMGHDR *CreateIMGHDRbyLastScreen(short x, short y, short w, short h, short maxw, short maxh) //Создание IMGHDR из скриншота или его фрагмента
{
  // x    - координата экрана x
  // y    - координата экрана y
  // w    - ширина фрагмента экрана от X
  // h    - высота фрагмента экрана от Y
  // maxw - ширина экрана
  // maxh - высота экрана
  
  IMGHDR *img = malloc(sizeof(IMGHDR));
  if ((x+w)<=maxw && (y+h)<=maxh)
   { 
    img->w     = w;
    img->h     = h;
    img->bpnum = 0x08;
    img->bitmap = malloc(h*w*2);
    char *scrbuf = RamScreenBuffer();
    for (int i=0;i<h;i++) memcpy(img->bitmap+w*i*2, scrbuf+x*2+(y+i)*maxw*2, w*2);
   } else
      {
       img->bitmap = malloc(1);
       ShowMSG(1, (int)"Ошибка!\nФрагмент больше экрана!");
      }
   return img;
}


IMGHDR *CreateIMGHDRbyfragmentIMGHDR(IMGHDR *img, short x, short y, short w, short h) //Создание IMGHDR из фрагмента IMGHDR
{
  IMGHDR *imgf = malloc(sizeof(IMGHDR));
  if ((x+w)<=img->w && (y+h)<=img->h)
   { 
    int bn;
    if (img->bpnum == 0x05) bn = 1;
    if (img->bpnum == 0x08) bn = 2;
    if (img->bpnum == 0x0A) bn = 4;
    
    imgf->w = w;
    imgf->h = h;
    imgf->bpnum = img->bpnum;
    imgf->bitmap = malloc(h*w*bn);
    for (int i=0;i<h;i++) memcpy(imgf->bitmap+w*i*bn, img->bitmap+x*bn+(y+i)*img->w*bn, w*bn);
   } else 
      {
        imgf->bitmap = malloc(1);
        ShowMSG(1, (int)"Ошибка!\nФрагмент больше заданного!");
      }  
   return imgf;
}

void MemFreeOfIMGHDR(IMGHDR *img) // Очистка памяти от IMGHDR
{
 mfree(img);
 mfree(img->bitmap);
}

void DrawStringV2(char *text,int x1,int y1,int x2,int y2,int font,int text_attribute,const char *Pen,const char *Brush)
{
  WSHDR *text_ws = AllocWS(strlen(text) + 5);  
  ascii2ws(text_ws, text);
  DrawString(text_ws,x1,y1,x2,y2,font,text_attribute,Pen,Brush);
  FreeWS(text_ws); 
}

#define MSGERROR 0
#define MSGINFO  1

void ShowMessage(char *text, int font, int type) //Ну, это  показ сообщения в моей интерпретации, бывают 2-х типов
{
 char txt[128];
 if (type == 0)
  {
    sprintf(txt,"%s\n%s",LG_MSG_ERROR,text);
    DrawRectangle(5,5, SCRW - 6, SCRH - 6, 0, black, msg_error);
  }
 if (type == 1) 
  {
    sprintf(txt,"%s\n%s",LG_MSG_INFO,text);
    DrawRectangle(5,5, SCRW - 6, SCRH - 6, 0, black, msg_info);
  }
 
 DrawLine(3,5,7,5,0,black);
 DrawLine(5,3,5,7,0,black);
 DrawLine(SCRW - 8,SCRH - 6,SCRW - 4,SCRH - 6,0,black);
 DrawLine(SCRW - 6,SCRH - 8,SCRW - 6,SCRH - 4,0,black);
 DrawStringV2(txt,7,7, SCRW - 8, SCRH - 8, font, 0, black, alpha);
 MESSAGEWINDOW = 1;
 FULLREDRAW();
}

void MEMORYFREE(int counter) //Вызывается один раз, иначе Пик!!!!
{
  if (counter > 28) MemFreeOfIMGHDR(bgm_img);
  if (counter > 29) MemFreeOfIMGHDR(bgg_img);
  if (counter > 30 && SCRH>SCRHM) MemFreeOfIMGHDR(sudoku_img);
  
  if (counter > 29)  counter = 29;
  for(int i = 1;i < counter; i++) MemFreeOfIMGHDR(dig_img[i-1]);
}

void OpenFile(char *path, void *p)
{
     WSHDR *path_ws = AllocWS(256);
     wsprintf(path_ws, path);
     ExecuteFile(path_ws,0,p);
     FreeWS(path_ws);
}

void DrawSoftHeader(char *skl,char *skr,char *head,int font, int hfont, char *soft_col, char *head_col, char *soft_colg, char *head_colg) //Рисует Софты и Заголовок
{  
   char t[3]="%t";
   int w1,w2,wh,hf,hh;
  
   WSHDR *skl_ws=AllocWS(32);
   WSHDR *skr_ws=AllocWS(32);
   WSHDR *head_ws=AllocWS(32);
   
   wsprintf(skl_ws,t,skl);
   wsprintf(skr_ws,t,skr);
   wsprintf(head_ws,t,head);
  
   w1 = Get_WS_width(skl_ws, font);
   w2 = Get_WS_width(skr_ws, font);
   wh = Get_WS_width(head_ws, hfont);
   hf = GetFontYSIZE(font);
   hh = GetFontYSIZE(hfont);
   
   if (head>0)                            //Header
    {
     for (int i=0; i<(hh+2); i++)                                
     {                                                            
       int a=100 - (i*100)/(hh+2);
       char colh[4]={head_colg[0],head_colg[1],head_colg[2],a};
       DrawRoundedFrame(0,i,SCRW-1,i,0,0,0,colh,0);
     }
    } 
 
   if (skl>0)
    {
      for (int i=0; i<(4*SCRW/10); i++)      //Left                          
      {                                                            
       int a=100-(i*100)/(4*SCRW/10);
       char col1[4]={soft_colg[0],soft_colg[1],soft_colg[2],a};
       DrawRoundedFrame(i,SCRH-hf-2,i, SCRH - 2,0,0,0,col1,0);
      }
    }
      
   if (skr>0)
    {
      for (int i=0; i<=(4*SCRW/10); i++)      //Right                      
      {                                                            
       int a=(i*100)/(4*SCRW/10);
       char col2[4]={soft_colg[0],soft_colg[1],soft_colg[2],a};
       DrawRoundedFrame(i + (6*SCRW)/10,SCRH-hf-2,i + (6*SCRW)/10, SCRH - 2,0,0,0,col2,0);
      }
    }
    
     if (skl>0)   DrawString(skl_ws, 2, SCRH - hf - 2, w1+5, SCRH - 2, font,0,soft_col,0);
     if (skr>0)   DrawString(skr_ws, SCRW - w2 - 2, SCRH - hf - 2,SCRW, SCRH - 2, font,0,soft_col,0);
     if (head>0)  DrawString(head_ws, 0, 0, 2 + wh, 2 + hh, hfont,0,head_col,0);
    
    FreeWS(skl_ws);
    FreeWS(skr_ws);
    FreeWS(head_ws);
}

void DrawRightSoft(char *str, int font, char *soft_col, char *soft_colg) //Рисует правую продолговатую софту
{
   int w,h;
   char t[3]="%t";
  
   WSHDR *str_ws=AllocWS(32);  
   wsprintf(str_ws,t,str);

   w = Get_WS_width(str_ws, font);
   h = GetFontYSIZE(font);
   
   for (int i=0; i<=(6*SCRW/10); i++)                  
    {                                                            
      int a=(i*100)/(6*SCRW/10);
      char col[4]={soft_colg[0],soft_colg[1],soft_colg[2],a};
      DrawRoundedFrame(i + (4*SCRW)/10,SCRH-h-2,i + (4*SCRW)/10, SCRH - 2,0,0,0,col,0);
    }
   DrawString(str_ws, SCRW - w - 2, SCRH - h - 2, SCRW, SCRH - 2, font,0,soft_col,0);
   FreeWS(str_ws);
}

char SECRETFUNCTION(char *exename) //0x00 - нормально,  0x01 - не прошёл проверку
{
 char imei[15];
 char imei2[25];
 char freespace[25]="This may be your market!";
 
 int addr;
 memcpy(imei,  (char*)0xA000065C, 15);
 
 imei2[0]  = imei[12] - 0x20;
 imei2[1]  = imei[13] - 0x20;
 imei2[2]  = imei[14] - 0x20;
 
 imei2[3]  = imei[8]  - 0x20;
 imei2[4]  = imei[9]  - 0x20;
 imei2[5]  = imei[10] - 0x20;
 imei2[6]  = imei[11] - 0x20;
 
 imei2[7]  = imei[4]  - 0x20;
 imei2[8]  = imei[5]  - 0x20;
 imei2[9]  = imei[6]  - 0x20;
 imei2[10] = imei[7]  - 0x20;
 
 imei2[11] = imei[0]  - 0x20;
 imei2[12] = imei[1]  - 0x20;
 imei2[13] = imei[2]  - 0x20;
 imei2[14] = imei[3]  - 0x20;
 
 FSTATS stat;
 GetFileStats(exename, &stat, 0);
 char *elfcopy = malloc(stat.size);
 
 int elf = fopen(exename,A_ReadWrite+A_BIN,P_WRITE,0);
 fread(elf, elfcopy, stat.size,0);

 for (int i=0;i<stat.size; i++) if(memcmp(elfcopy+i,freespace,25)==0) {addr  = i;goto VAR1;}
 for (int i=0;i<stat.size; i++) if(memcmp(elfcopy+i,imei2,15)==0) goto VAR2;
 
 if (stat.size == 0)
 { 
VAR1:
  lseek(elf, addr, S_SET, 0, 0);
  fwrite(elf, imei2, 25, 0);
  addr = 0x01;
  goto END_SF; 
 }
 
 if (stat.size == 0)
 { 
VAR2:
  addr = 0x01;
  goto END_SF;
 }
 
 //3564 2700 3704 348 => 348 3704 2700 3564 - 0x20
 
  addr = 0x00;
   
END_SF:
  mfree(elfcopy);
  fclose(elf, 0);
  return addr;
}


