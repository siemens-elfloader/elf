#include "main.h"
/*
#ifdef DEBUG
#define debug0(a1) \
  sprintf(lbf,a1); \
  fwrite(logf,lbf,strlen(lbf),&ul)
#define debug1(a1,a2) \
  sprintf(lbf,a1); \
  fwrite(logf,lbf,strlen(lbf),&ul)
#define debug2(a1,a2,a3) \
  sprintf(lbf,a1,a2,a3); \
  fwrite(logf,lbf,strlen(lbf),&ul)
#define debug3(a1,a2,a3,a4) \
  sprintf(lbf,a1,a2,a3,a4); \
  fwrite(logf,lbf,strlen(lbf),&ul)
#define debug4(a1,a2,a3,a4,a5) \
  sprintf(lbf,a1,a2,a3,a4,a5); \
  fwrite(logf,lbf,strlen(lbf),&ul)
#else
#define debug0(a1)
#define debug1(a1,a2)
#define debug2(a1,a2,a3)
#define debug3(a1,a2,a3,a4)
#define debug4(a1,a2,a3,a4,a5)
#endif
*/
const char sm_h=11;
const char sm_w[161]={
//  ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @
  2,3,2,4,4,6,6,2,2,2,4,4,2,2,2,4,4,4,4,4,4,4,4,4,4,4,3,3,3,4,3,4,6,
//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ `
  4,4,4,4,3,3,4,4,1,4,5,3,6,5,4,4,4,4,4,5,4,4,7,4,5,4,3,4,3,4,3,3,
//a b c d e f g h i j k l m n o p q r s t u v w x y z
  4,4,4,4,4,3,4,4,1,2,4,1,7,4,4,4,4,3,4,3,4,4,6,4,4,3,
//{|}~
//À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß
  4,4,4,4,5,4,6,4,4,4,4,4,6,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,4,4,5,4,
//à á â ã ä å æ ç è é ê ë ì í î ï ð ñ ò ó ô õ ö ÷ ø ù ú û ü ý þ ÿ
  4,4,4,4,5,4,4,4,4,4,4,4,6,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,4,4,5,4,
//¨ ª ¯ ¸ º ¿
  5,6,3,5,6,3};

#define stat_height 8
/*
#ifdef DEBUG
extern int logf;
extern unsigned int ul;
extern char lbf[2000];
#endif
*/
//char list_mode=1;
//PARAMETERS
extern const unsigned int col_bg;//1
extern const unsigned int col_tx;//0
unsigned int tx_fn=SMALL_FONT;
unsigned int tx_atr=0;
unsigned char h_s=2;
extern const unsigned int v_s;//1
extern const int words;//1
extern const int rem_rcr;//1
extern const unsigned int width;//1
extern const unsigned int parag;//1
extern const unsigned int status;
extern const int rem_cr;//1
extern const unsigned int space_lim;//1

//VARS
extern char *name;
extern FileBuff fb;
extern PageBuff pb;
extern int sh,sw;
extern unsigned int err;
extern WSHDR *ws;
extern char w,h;
extern unsigned int fsize;

#define MAXC 100
#define MAXL 100
char text[MAXL][MAXC];
char lines;

#pragma inline
char chrw(char c)
{
  if ((c>=0x20)&&(c<=0x7a)) return sm_w[c-0x20];
  else if (c>=0xC0) return sm_w[c-0xc0+91];
  else if ((c==0x0a)||(c==0x0a)) return 0;
  else if (c==0xA8) return sm_w[155];
  else if (c==0xAA) return sm_w[156];
  else if (c==0xAF) return sm_w[157];
  else if (c==0xB8) return sm_w[158];
  else if (c==0xBA) return sm_w[159];
  else if (c==0xBF) return sm_w[160];
  else if (c==0)  return sh+1;
  else return 4;
}

int FileBuff::FileSet(char *fname)
{
  if (!fname) return 0;
  file=fopen(fname,A_TXT+A_ReadOnly,P_READ,&err);
  if (file<=0) return 0;
  fpos=0;
  next=0;
  step=0;
  bufflen=fread(file,buff,buffsize,&err);
  if (!bufflen) eof=1;
  else eof=0;
  //debug2("FileSet-%s\nbufflen-%u\n",fname,bufflen);
  return 1;
}

char FileBuff::operator [](int pos)
{
  //debug1("FileBuff[]-%u\n",pos);
  if ((pos<fpos)||(pos>=fpos+bufflen))
  {
    fpos=lseek(file,pos,S_SET,&err,&err);
    if (fpos!=pos) {eof=1; return 0;} else eof=0;
    bufflen=fread(file,buff,buffsize,&err);
    if (!bufflen) {eof=1; return 0;} else eof=0;
  }
  return buff[pos-fpos];
}

void FileBuff::FileCl()
{
  if (!file) fclose(file,&err);
}

char FileBuff::Get()
{
  char t;
  t=this->operator[](next);
  if (t) next++;
  NextR();
  if ((t==0xd)&&(Next()==0xa)) {next++;t=0xa;}
  else if (t==0x20)  while (Next()==0x20) next++;
  if ((rem_rcr)&&((t==0xd||(t==0xa))))
  {
    NextR();
    char tc=Next();
    while  ((tc==0xa)||(tc==0xd)) {next++;tc=Next();}
  }
  if ((rem_cr)&&((t==0xd||(t==0xa))))
  {
    NextR();
    if (Next()!=0x20) 
      t=0x20;
  }
  NextR();
  return t;
}

void FileBuff::Set(long fpos)
{
  next=fpos;
  step=0;
}

char FileBuff::Next()
{
  step++;
  return this->operator[](next+step);
}

void FileBuff::NextR()
{
  step=0;
}

long FileBuff::Pos()
{
  return next;
}

char FileBuff::EOF()
{
  return eof;
}

void PageBuff::Init(unsigned long pos)
{
  do
  {
#ifdef DEBUG
  sprintf(lbf,"FormatPage\n");
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif 
    FormatPage();
  }
  while ((last->strt+last->len)<pos);
  
}

void PageBuff::Destroy()
{
  page* next=pages;
  while (next)
  {
    pages=next;
    next=pages->next;
    mfree(pages);
  }
}

char IsSpace(char tmp)
{
  return ((tmp==0x20)||(tmp==0x0a)||(tmp==0x0d)||(tmp=='.')||(tmp==',')||(tmp==':')||(tmp=='!')||(tmp==';')||(tmp=='\'')||(tmp=='"')||(tmp=='?')||(tmp==')')||(tmp=='(')||(tmp=='-'));
}

void PageBuff::FPage(page *pg)
{
  for (int i=0;i<MAXL;i++)
    for (int j=0;j<MAXC;j++)
      text[i][j]=0;
  char y,ln=0;
  if (status) y=stat_height;
  else y=0;
  char x,ch;
  char wordc;
  char prg=curr->prg&1;
  fb.Set(pg->strt);
  do
  {
#ifdef DEBUG
  sprintf(lbf,"y-%u\n",y);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif 
    x=0;ch=0;
    wordc=words;
    fb.NextR();
    char t=fb.Next();
    if (t==0x20) {fb.Get();t=fb.Next();}
    if ((prg)&&(parag)) {ch++;text[ln][0]=0x20; x+=chrw(text[ln][0]);}
    while (x+chrw(t)<sw)
    {
#ifdef DEBUG
  sprintf(lbf,"x-%u\n",x);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif 
      t=fb.Get();
      if ((t==0x0a)||(t==0x0d))
      {
        text[ln][ch]=0x0a;
        break;
      }
      text[ln][ch]=t;
      x+=chrw(t)+h_s;
      ch++;
      if (wordc==2)
      {
        char wx=0;
        char count=0;
        fb.NextR();
        char tmp=fb.Next();
        while ((!IsSpace(tmp))&&(!fb.EOF())&&(wx+x<sw))
        {
          wx+=chrw(tmp)+h_s;
          count++;
          tmp=fb.Next();
        }
        if (wx+x>=sw)
        {
          wordc=1;
          if (count>2)
          {
            char count2=0;
            while ((!IsSpace(tmp))&&(!fb.EOF()))
            {
              tmp=fb.Next();
              count2++;
            }
            if (count+count2>=4)
            {
              count2+=count;
              fb.NextR();
              while ((x+chrw(fb.Next())<sw)&&(count2>2)&&(count>0));
              {
                text[ln][ch]=fb.Get();
                x+=chrw(text[ln][ch])+h_s;
                ch++;
                count2--;
                count--;
              }
              text[ln][ch]='-';
              x+=chrw(text[ln][ch])+h_s;
              ch++;
              break;
            }
          }
        }
      }
      if (wordc==1)
      {
        char wx=0;
        fb.NextR();
        char tmp=fb.Next();
        while ((!IsSpace(tmp))&&(!fb.EOF())&&(wx+x<2*sw))
        {
          wx+=chrw(tmp)+h_s;
          tmp=fb.Next();
        }
        if (wx+x>=sw)
        {
          if (wx<sw) 
            break;
          else wordc=0;
        }
      } 
      fb.NextR();
      t=fb.Next();
    }
    prg=0;
    if (x>=sw)
    {
      fb.NextR();
      char tmp=fb.Next();
      if ((tmp==0x0a)||(tmp==0x0d))
      {
        fb.Get();
        prg=1;
      }
    }
    if (text[ln][ch]==0xa) prg=1;
    if ((ch>=1)&&(text[ln][ch-1]==0x20)) text[ln][ch-1]=0;
    y+=sm_h+v_s;
    ln++;
  }
  while (y+sm_h<sh);
  if (prg) curr->prg|=2;
  lines=ln;
  pg->len=fb.Pos()-pg->strt;
}

void PageBuff::FormatPage(unsigned int fpos)
{
  if (!pages)
  {
    pages=(page*)malloc(sizeof(page));
    pages->next=NULL;
    pages->prev=NULL;
    pages->strt=fpos;
    FPage(pages);
    last=pages;
    curr=pages;
    curr->prg=0;
  }
  else
  {
    last->next=(page*)malloc(sizeof(page));
    last->next->prev=last;
    if  (last->prg&2) last->next->prg=1;
    else last->next->prg=0;
    last=last->next;
    last->next=NULL;
    last->strt=last->prev->strt+last->prev->len+1;
    FPage(last);
    curr=last;
  }
}

void PageBuff::DrawLine(char ln)
{
  char i=0,wd=0,sp=0;
  while ((text[ln][i])&&(text[ln][i]!=0xa))
  {
    if ((text[ln][i]!=0x20)||(i==0))
      wd+=chrw(text[ln][i])+1+h_s;
    else
      sp++;
    i++;
  }
  if (text[ln][i]==0xa)
    text[ln][i]=0;
  else
    if (width)
    {
      char wsp=(sw-wd)/sp;
      if ((space_lim)&&(space_lim<wsp)) wsp=space_lim;
      char buff[2]={0,0};
      i=0;
      sp=0;
      wd=0;
      while (text[ln][i])
      {
        if ((text[ln][i]!=0x20)||(i==0))
        {
          buff[0]=text[ln][i];
          wsprintf(ws,"%t",&(buff[0]));
          DrawString(ws,wd+wsp*sp,ln*(sm_h+v_s)+((status==1)?stat_height:0),sw,(ln+1)*(sm_h+v_s)+((status==1)?stat_height:0),SMALL_FONT,0,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(col_bg));      
          wd+=chrw(text[ln][i])+1+h_s;
        }
        else sp++;
        i++;
      }
      return;
    }   
  wsprintf(ws,"%t",&(text[ln][0]));
  DrawString(ws,0,ln*(sm_h+v_s)+((status==1)?stat_height:0),sw,(ln+1)*(sm_h+v_s)+((status==1)?stat_height:0),SMALL_FONT,0,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(col_bg));
}

void PageBuff::DrawPage()
{
  FPage(curr);
  if (status==1) 
  {
    int tmp=(curr->strt+curr->len)/128;
    int tmp2=fsize/128+((fsize%128>0)?1:0);
    TTime tm;
    GetDateTime(NULL, &tm);
    wsprintf(ws," %u/%u",tmp,tmp2);
    DrawString(ws,0,0,sw-1,stat_height,5,0,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
    tmp=((curr->strt+curr->len)*100)/fsize;
    tmp2=((curr->strt+curr->len)*10000)/fsize - (((curr->strt+curr->len)*100)/fsize)*100;
    wsprintf(ws,"%u.%02u",tmp,tmp2);
    DrawString(ws,0,0,sw-1,stat_height,5,2,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(ws,"%02u:%02u ",tm.hour,tm.min);
    DrawString(ws,0,0,sw-1,stat_height,5,4,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
  }
  char ln=0;
  while (ln<lines)
  {
    DrawLine(ln);
    ln++;
  }
  if (status==2) 
  {
    int tmp=(curr->strt+curr->len)/128;
    int tmp2=fsize/128+((fsize%128>0)?1:0);
    TTime tm;
    GetDateTime(NULL, &tm);
    wsprintf(ws," %u/%u",curr->strt,tmp,tmp2);
    DrawString(ws,0,sh-stat_height,sw-1,sh,5,0,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
    tmp=((curr->strt+curr->len)*100)/fsize;
    tmp2=((curr->strt+curr->len)*10000)/fsize - (((curr->strt+curr->len)*100)/fsize)*100;
    wsprintf(ws,"%u.%02u",tmp,tmp2);
    DrawString(ws,0,sh-stat_height,sw-1,sh,5,2,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(ws,"%02u:%02u ",tm.hour,tm.min);
    DrawString(ws,0,sh-stat_height,sw-1,sh,5,4,GetPaletteAdrByColorIndex(col_tx),GetPaletteAdrByColorIndex(23));
  }
}

void PageBuff::Next()
{
  if (curr==last)
  {
    if (fb.EOF()==1) return;
    page *tmp=(page*)malloc(sizeof(page));
    last->next=tmp;
    tmp->next=NULL;
    tmp->strt=last->strt+last->len+1;
    tmp->prev=last;
    if  (last->prg&2) tmp->prg=1;
    else tmp->prg=0;
    last=tmp;
 }
  curr=curr->next;
}

void PageBuff::Prev()
{
  if (curr!=pages)
    curr=curr->prev;
}
