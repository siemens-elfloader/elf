#ifndef _SIEAPI_H_
#define _SIEAPI_H_ 
 #ifndef _SYSTEM_BUILD
  #pragma system_include
 #endif
#include <ysizet.h>
#include <siecxt.h>
_C_STD_BEGIN
 //�������Ĭ���̷�
#ifdef NEWSGOLD
  #ifdef ELKA
   #define DEFAULT_DISK "4"
  #else
   #define DEFAULT_DISK "0"
  #endif //newsgold
#else
  #define DEFAULT_DISK "0"
#endif //newsgold
 //������������ 

typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned char  byte;//0..255
typedef unsigned short word;
#define TYPVOID typedef void
#define TSTRUCT typedef struct 
#define elif    else if
#define color(x) (x<24)?GetPaletteAdrByColorIndex(x):(char *)(&(x))
#define idlegui_id(icsm) (((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b
#define TRAN_CBK GetPaletteAdrByColorIndex(23)
#define CTYPE1 0
#define CTYPE2 1
//����������������0-16!
#define FontEN "Large","Large bold","Large italic","Large italic bold","Medium","Medium bold","Medium italic","Medium italic bold","Small","Small bold","Small italic","Small italic bold"
#define FontCN "��ų���","��żӴ�","�����б","��Ŵ�б","�кų���","�кżӴ�","�к���б","�кŴ�б","С�ų���","С�żӴ�","С����б","С�Ŵ�б","С������","С������","΢������","�������","�к�����"
#define KeyName "�����","�����","�󰴼�","�Ұ���","�س���","�̼�","���"
 
 //�������ڽṹ
 TSTRUCT{
  ulong year;
  byte  month;
  byte  isLm;
  byte  day;
 }TLDate;
  //����ũ�����ͽṹ
 TSTRUCT{
  char year[10];//����
  char moth[10];//����   
  char dday[10];//���� 
  char hour[10];//ʱ��
  char nday[10];//���ջ����
 }TLunar;
 TSTRUCT{
  char R;
  char G;
  char B;
  char A;
 }color;
 //������������
 TSTRUCT{
  short l;//left
  short t;//top  
  short r;//Right;
  short b;//Bottom;
 }TRect;
 //������������
 TSTRUCT{
  char Pen[4];//������ɫ
  char Bsh[4];//�߿���ɫ
  byte Size;//�����С
 }TFont;
 //�����ļ��ṹ
 TSTRUCT{
  void *next;
  char *file;
  char *path;
  int   type;//1Ϊ�ļ���,0Ϊ�ļ�
 }TFile;
 //�����ļ��ṹ
 TSTRUCT{
  void *next;
  char *name;
  uint  cmd;//Ϊִ�й��ܴ���
 }TMenu;
 //����ʱ��ṹ
 TSTRUCT{
  ulong year;
  byte  month;
  byte  day; 
  byte  hour;
  byte  min;
  byte  sec;
  ulong millisec;
 }TDateTime;
 TSTRUCT{
  ulong y;
  byte  m;
  byte  d; 
  byte  h;
 }TCDate;
 //���庯�������ṹ
_C_LIB_DECL
 __INTRINSIC ulong strtoul(const char *nptr,char **endptr,int base); 
 __INTRINSIC long strtol(const char *nptr,char **endptr,int base);
 __INTRINSIC int  strlpos(char *str,char c); 
 //��ȡ���ֻ���Ӧ�����ı��ĳ���
 __INTRINSIC short PixlsWidth(WSHDR *ws, int font); 
 //�ִ��ȽϺ���
 __INTRINSIC int  toupper(int c);
 __INTRINSIC int  ExtStrcmp(char *a,char *b);
 __INTRINSIC int  strcmp_nocase(const char *s1,const char *s2); 
 __INTRINSIC int  cmpstr_nocase(const char *s, const char *d);
 //��Ļ���Ʒ�Χ����
 __INTRINSIC void patch_rect(RECT*rc,int x,int y, int x2, int y2);//�趨����
 __INTRINSIC void patch_header(const HEADER_DESC* head);//�趨ͷ����
 __INTRINSIC void patch_input(const INPUTDIA_DESC* inp);//�趨��������
 __INTRINSIC void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2);//�趨�Ի�������
 //�򿪳����Ӧ��Ĭ�������ļ�(*.BCFG)
 __INTRINSIC void OpenBCFGFile(void);
 //�ض��廭������
 __INTRINSIC void DrawCanvasExt(void *canvas, RECT rc,int mode);
 __INTRINSIC void DrawCanvasRect(void *canvas, TRect rc,int mode);
 __INTRINSIC void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute);
 __INTRINSIC void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute);
 //�ͷų����ڴ�
 __INTRINSIC void kill_data(void *data, void (*func_p)(void *));
 __INTRINSIC void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
 //�ִ�ת������
 __INTRINSIC void str2ws_unicode(WSHDR* ws, char* str, int len);
 __INTRINSIC void ws2str_unicode(char* str, WSHDR* ws, int *len);
 __INTRINSIC char* unicodeSwitch(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* utf82unicode(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* unicode2utf8(char *str, int *len); 
 //UNICODE�������ӵ�WS������
 __INTRINSIC void BSTRAdd(word *pDst, const word * pSrc, int Count);
 
 //��ȡ�ļ�����չ��
 __INTRINSIC void CutFileExt(char *filename,char *ext);
 //�����ļ�����
 __INTRINSIC void RunCUT(char *s);//ִ�п��
 __INTRINSIC void RunAPP(char *s);//���ļ�
 __INTRINSIC void RunADR(char *s);//ִ�е�ַ 
 //UTF8�ļ��������ͷ�
 __INTRINSIC char *LoadFileBuf(const char *FileName);
 __INTRINSIC int  FreeFileBuf(char *Buffer);
 //��ȡ�ֻ��ڲ���Ӧ������
 __INTRINSIC byte FontSize(byte inx);
 //���������ļ�,֧���ֻ��ڲ����������ļ�
 __INTRINSIC int PlayMusic(const char *fname, byte volume, byte repeat);
 //��̬�˵���������
 __INTRINSIC TMenu *BuildMenu(char *Title[]);
 __INTRINSIC void DrawMenu(void *gui, int cur_item, void *user_pointer);
 __INTRINSIC void FreeMenu(TMenu *Menu);
 __INTRINSIC int  MenuCount(TMenu *Menu);
 //�ļ��˵���غ���
 __INTRINSIC int  FileCount(TFile *File);
 __INTRINSIC void FreeFile(TFile *File);
 //ý�幦���Ƿ�ʹ����-------------
 __INTRINSIC int IsMediaActive(void);
 //ʮ������ת��Ϊʮ����-----------
 __INTRINSIC ulong HexToInt(char *HEX);
 //����ת��
 __INTRINSIC void  Ascii2WS(word *data,WSHDR *ws, const char *s, int maxlen);
 __INTRINSIC void  WS2Ascii(word *data, WSHDR *ws, char *s, int maxlen);
 __INTRINSIC void  FreeFontLib(word *data);//�ͷ��ֿ��ڴ�
 __INTRINSIC word *LoadFontLib(void);//�����ֿ��ڴ�
 //��ȡũ�����ں���
 __INTRINSIC TLunar  GetLunar(TDate d,byte hour);//��ȡũ���ִ�
 __INTRINSIC TLDate  GetLDate(TDate d);//��ȡũ������
 __INTRINSIC byte  LunarTermId(TDate d);//���ض�Ӧ�Ķ�ʮ�Ľ���ID(1..24)
 __INTRINSIC byte  LunarYearId(ulong year);//����ĳ�����Ƿ�����
 __INTRINSIC byte  LunarTimeID(byte hour);//����ʱ����Ф˳��
 __INTRINSIC word  BetweenDaySum(TDate start,TDate end);//����������֮�������
 __INTRINSIC word  GetDayFromYearBegin(ulong AYear,byte AMonth,byte ADay);// ȡĳ���ڵ����������
 __INTRINSIC byte  FileExists(char *FileName,int *Handle);//�ж��ļ��Ƿ����!
 __INTRINSIC void *CreateCanvas();//��������ָ��
 __INTRINSIC short MidStr(const char *src,const char *sub,char *result);//��ȡ���ִ�
 __INTRINSIC short MidCat(const char *src,const char *sub,char *res,char cat);
 __INTRINSIC short FindSub(const char *src,const char *sub,char *result);
//PNGת����غ��� 
 __INTRINSIC IMGHDR_Draw(IMGHDR *Handle, int x, int y, char *pen, char *brush);
 __INTRINSIC IMGHDR_Delete(IMGHDR *Handle);
 __INTRINSIC void  IMGHDR_Free(IMGHDR *Handle);
 __INTRINSIC color IMGHDR_Color(IMGHDR *Handle, int x, int y);
 __INTRINSIC IMGHDR *IMGHDR_Alpha(IMGHDR *Handle, char a, int nw, int del);
 __INTRINSIC IMGHDR *IMGHDR_Sample(IMGHDR *Handle, int px, int py, int fast, int del);
 __INTRINSIC IMGHDR *IMGHDR_Handle(int x,int y,const char *pic_path,int pic_size);
 __INTRINSIC uint  KeyButton(uint Button);
 __INTRINSIC word  SumDays(word Year,word Month);
 __INTRINSIC TRect SetRect(short Left,short Top, short Rigth,short Bottom);
 __INTRINSIC byte  Odd(byte num);
_END_C_LIB_DECL
_C_STD_END
//����ִ�д���

#pragma inline
static byte Odd(byte num){
  return(num%2==0?1:0);
}
#pragma inline
static byte LunarTimeID(byte hour){
  switch(hour){  
  case  1:
  case  2:return(1);break;
  case  3:
  case  4:return(2);break;
  case  5:
  case  6:return(3);break;
  case  7:
  case  8:return(4);break;
  case  9:
  case 10:return(5);break;
  case 11:
  case 12:return(6);break;
  case 13:
  case 14:return(7);break;
  case 15:
  case 16:return(8);break;
  case 17:
  case 18:return(9);break;
  case 19:
  case 20:return(10);break;
  case 21:
  case 22:return(11);break;
  default:return(0);break;
  }  
}

#pragma inline
static TRect SetRect(short Left,short Top, short Right,short Bottom){
 TRect RC={Left,Top,Right,Bottom};
 return(RC);
}

#pragma inline
static word SumDays(word Year,word Month){
  word b=MonthSum[Month-1];
  if(Year%4==0&&b>2)
    b=b+1;
  return(b);
}

#pragma inline
static uint KeyButton(uint Button){
  switch(Button){
   case  0:return(LEFT_SOFT);
   case  1:return(RIGHT_SOFT);
   case  2:return(LEFT_BUTTON);
   case  3:return(RIGHT_BUTTON);
   case  4:return(ENTER_BUTTON);
   case  5:return(GREEN_BUTTON);
   default:return(RED_BUTTON);
  }
}
#pragma inline//��ȡc��str�ִ���λ��
static int getstrpos(char *str,char c){
  int cur = 0;
  for (int inx=1;inx<=strlen(str);inx++)
  {
    if(str[inx]==c){cur=inx;break;}
  }
  return cur;
}

#pragma inline//��ȡ���ļ�����
static void CutFileExt(char *filename,char *ext){
  if(strlen(filename)>strlen(ext))filename[strlen(filename)-strlen(ext)]=0;
}
#pragma inline//���п��
static void RunCUT(char *s){
 if ((s)&&(strlen(s))){
 uint* addr = (uint*)GetFunctionPointer(s);
 if (addr){
   TYPVOID (*voidfunc)(); 
  #ifdef NEWSGOLD          
         voidfunc pp=(voidfunc)*(addr+4);
  #else 
         voidfunc pp=(voidfunc)addr; 
  #endif 
         SUBPROC((void*)pp);
 }
 }
}
#pragma inline//����ELF����
static void RunAPP(char *s){
  if ((s)&&(strlen(s))){
      WSHDR *ws=AllocWS(128);
      wsprintf(ws,"%s",s);
      //str_2ws(ws,s,strlen(s));
      ExecuteFile(ws, 0,0);
      FreeWS(ws);
      //GeneralFuncF1(1);
  }
}
#pragma inline//���е�ַ����
static void RunADR(char *s){  
  if ((s)&&(strlen(s))){
      TYPVOID (*voidfunc)(); 
      uint addr=strtoul(s, 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp); 
  }
}
#pragma inline//�ִ��ȽϺ���
static int ExtStrcmp(char *a,char *b)
{
  int state=0,max=strlen(a);
  if(strlen(a)>strlen(b)) max = strlen(b);
  for(int i=0;i<max;i++){
    if(a[i]!=b[i]){state=0; break;}else{state=1;}
  } 
  return(state);
}
#pragma inline//���ݺϲ�
static void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
  uint nSize = *pDst, i=1;
  while(*pSrc != '\0' && i<=Count) *(pDst+ nSize+i++) = *pSrc++;
  *pDst = nSize+i-1;
}
#pragma inline//��ǰ����ת��Ϊũ������
static TLDate GetLDate(TDate d)
{/*����ÿ��ǰ�������*/
/*---ȡ��ǰ�����ꡢ�¡���---*/
int cYear=d.year,cMonth=d.month,cDay=d.day;
static int nTheDate,nIsEnd,m,k,n,i,nBit;
/*---���㵽��ʼʱ��1921��2��8�յ�������1921-2-8(���³�һ)---*/
nTheDate=(cYear-1921)*365+(cYear-1921)/4+cDay+MonthSum[cMonth-1]-38;
if((!(cYear%4))&&(cMonth>2))
  nTheDate = nTheDate+1;
/*--����ũ����ɡ���֧���¡���---*/
nIsEnd = 0;
m      = 0;
while(nIsEnd != 1){
  n = k= wLunar[m]<4095?11:12;
  while(n>=0){
   //��ȡwLunar(m)�ĵ�n��������λ��ֵ
   nBit = wLunar[m];
   for(i=1;i<n+1;i++) nBit = nBit/2;
   nBit = nBit % 2;
   if (nTheDate <= (29+nBit)){
    nIsEnd = 1;
    break;
   }
   nTheDate = nTheDate-29-nBit;
   n = n-1;
  }
  if(nIsEnd) break;
  m = m+1;
}
cYear  = 1921+m;
cMonth = k-n+1;
cDay   = nTheDate;
if (k == 12){
  if (cMonth == wLunar[m] / 65536+1)
      cMonth = 1-cMonth;
  else if (cMonth > wLunar[m] / 65536+1)
      cMonth = cMonth-1;
}
TLDate o;
o.year =cYear;
o.month=(o.isLm=cMonth<1)?-1*cMonth:cMonth;
o.day  =cDay;
return(o);
}
#pragma inline//��ȡũ��������Ϣ
static TLunar GetLunar(TDate d,byte hour){ 
 TLunar cn;
 TLDate L = GetLDate(d);
 /*--����ũ����ɡ���֧������ ==> ����*/
 short SUM = (L.year-4)%60;
 byte    m = SUM%10; 
 byte    n = SUM%12; 
 sprintf(cn.year,PST_4,cTGan[m],cDZhi[n],cSXin[n],cnStr[0]); 
 /*--����ũ����ɡ���֧������ ==> ����*/ 
 TDate dm={d.year,d.month,1};
 for(byte day=1;day<15;day++){
     dm.day  = day;
     if(LunarTermId(dm)){
        break;
     }       
 }
 switch(m){//m��������֧
  case 0://0,5�׼�֮��
  case 5:m=0;break;
  case 1://1,6�Ҹ�֮��
  case 6:m=1;break;
  case 2://2,7����֮��
  case 7:m=2;break;
  case 3://3,8����֮��
  case 8:m=3;break;  
 default:m=4;break;//4,9���֮��
 } 
 n=(d.month==1&&dm.day>d.day)?12:d.month-1;
 if(dm.day>d.day)n--;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
 m=sGId[n][m];
 n=sZId[n];
 sprintf(cn.moth,PST_4,cTGan[m],cDZhi[n],cSXin[n],cnStr[1]);
 /*--����ũ����ɡ���֧������ ==> ����*/  
 byte  M = d.month;
 short B = d.year/100;
 short C = d.year%100;
 if(M==1 || M==2){
   M = (M==1)?13:14;
   B = (d.year-1)/100;
   C = (d.year-1)%100;
 }
 SUM = (short)(B/4)+5*C+(short)(C/4) +(short)(3*(M+1)/5)+d.day;
 M = (d.month%2==0)?6:0;
 m = (4*B+SUM-3)%10-1; 
 n = (8*B+SUM+7+M)%12-1; 
 m = m>10?9:m;
 n = n>12?11:n;
 sprintf(cn.dday,PST_4,cTGan[m],cDZhi[n],cSXin[n],cnStr[2]); 
  /*--����ũ����ɡ���֧������ ==> ʱ��*/
 n=LunarTimeID(hour);
 switch(m){//m��������֧
  case 0://0,5�׼�֮��
  case 5:m=n>=10?n-10:n+0;break;
  case 1://1,6�Ҹ�֮��
  case 6:m=n>= 8?n- 8:n+2;break;
  case 2://2,7����֮��
  case 7:m=n>= 6?n- 6:n+4;break;
  case 3://3,8����֮��
  case 8:m=n>= 4?n- 4:n+6;break;    
 default:m=n>= 2?n- 2:n+8;break;//4,9���֮��
 } 
 sprintf(cn.hour,PST_4,cTGan[m],cDZhi[n],cSXin[n],cnStr[3]); 
 /*--����ũ���� --*/
 if(m=LunarTermId(d))
   sprintf(cn.nday,PST_3,cnStr[5],cnStr[6],sTerm[m-1]);//����;
 else{
   n=L.day%10!=0?L.day%10-1:9;
   if(L.day<=10)     m=0;
   else if(L.day<20) m=1;
   else if(L.day<30) m=2;
   else              m=3;
   if(L.isLm){//����
      sprintf(cn.nday,PST_4,cnStr[4],cnMth[L.month-1],cnShi[m],cnNum[n]);
   }else{
      sprintf(cn.nday,PST_4,cnMth[L.month-1],cnStr[1],cnShi[m],cnNum[n]);
   }
 }
 return(cn);
} 
#pragma inline
static short PixlsWidth(WSHDR *ws, int font){  
  word *body=ws->wsbody;
  short len=body[0];
  short wln=len>0?2:0;
  while(len>0){
    wln+=GetSymbolWidth(body[len],font);
    len--;
  }
  return(wln);
}

#pragma inline=forced
static int toupper(int c){ if ((c>='a')&&(c<='z')) c+='A'-'a';  return(c);}

#pragma inline
static int strcmp_nocase(const char *s1,const char *s2){
  int i,c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
#pragma inline
static int cmpstr_nocase(const char *s, const char *d){
  int cs;
  int ds;
  do{
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}
#pragma inline
static void str2ws_unicode(WSHDR* ws, char* str, int len){
  int i = 0;
  char *p = str;
  while ((p-str) < len-1) {
    ws->wsbody[++i] = (*(p+1) << 8)+*p;
    p += 2;
  }
  ws->wsbody[0] = i;
}
#pragma inline
static void ws2str_unicode(char* str, WSHDR* ws, int *len){	//ע�ⷶΧ
  for (int i = 0; i < ws->wsbody[0]; i++) {
  	*(str+(i << 1)) = ws->wsbody[i+1] & 0xFF;
  	*(str+(i << 1)+1) = ws->wsbody[i+1] >> 8;
	}
	*len = ws->wsbody[0] << 1;
}
#pragma inline
static char* unicodeSwitch(char *str, int len, int *rlen, int *llen){
  if (!str) return NULL;
  int i = 0, l = len >> 1 << 1;
  char *p = malloc(l);
  while (i < l) {
    *(p+i) = *(str+i+1);
    *(p+i+1) = *(str+i);
    i += 2;
  }
  *rlen = *llen = l;
  return p;
}
#pragma inline
static char* utf82unicode(char *str, int len, int *rlen, int *llen){
  if (!str) return NULL;
  
/*
  char *ms = malloc (50);
  sprintf(ms, "%d, %d", j, l);
  ShowMSG(1, (int) ms);
  mfree(ms);*/
  
  int i = 0, j = 0, l = len, bl = len << 1;
  char* s = malloc(bl);
  char c;
  *rlen = *llen = 0;
  bl -= 3;
  for (i = 0; i < l; i++) {
    c = str[i];
    if ((c >> 7) == 0x0) {  //���ֽڱ���
      s[j++] = c;
      s[j++] = 0x0;
      (*llen)++;
    }
    else if ((c >> 5) == 0x6 && i < l-1) { //˫�ֽڱ���
      s[++j] = ((c & 0x1f) >> 2);
      s[j-1] = c << 6;
      c = str[++i];
      s[j-1] = s[j-1] | (c & 0x3f);
      j++;
      (*llen) += 2;
    }
    else if ((c >> 4) == 0xe && i < l-2) { //���ֽڱ���
      s[++j] = c << 4;
      c = str[++i];
      s[j] = s[j] | ((c >> 2) & 0xf);
      s[j-1] = c << 6;
      c = str[++i];
      s[j-1] = s[j-1] | (c & 0x3f);
      j++;
      (*llen) += 3;
      
    }
    else
    	break;
    (*rlen) += 2;
  }

  if (*rlen < (l << 1)) {
   	char *r = malloc(*rlen);
   	memcpy(r, s, *rlen);
   	mfree(s);
   	s = r;
  }
  return s; 
}
#pragma inline
static char* unicode2utf8(char *str, int *len){
  if (!str) return NULL;

  int i = 0, j = 0;
  char* s = malloc((*len) << 1);
  
  int c;
  for (i = 0; i < (*len)-1; i += 2) {
    c = (str[i+1] << 8) | str[i];
    if (c < 0x80) {  //���ֽڱ���
      s[j++] = (char) c;
    }
    else if (c > 0x7f && c < 0x800) { //˫�ֽڱ���
    	s[j++] = (c >> 6) | 0xc0;
    	s[j++] = c & 0x3f | 0x80;
    }
    else if (c > 0x7ff && c < 0x10000) { //���ֽڱ���
      s[j++] = (c >> 12) | 0xe0;
      s[j++] = (c >> 6) & 0x3f | 0x80;
      s[j++] = c & 0x3f | 0x80;
    }
  }
  *len = j;
  return s; 
}

#pragma inline
static void patch_rect(RECT*rc,int x,int y, int x2, int y2){
  rc->x =x;
  rc->y =y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
static void patch_header(const HEADER_DESC* head){
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
static void patch_input(const INPUTDIA_DESC* inp){
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
static void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2){
  dialog->rc.x  = x;
  dialog->rc.y  = y;
  dialog->rc.x2 = x2;
  dialog->rc.y2 = y2;
}
#pragma inline
static void OpenBCFGFile(void){   
  extern const char *successed_config_filename;
  if ((successed_config_filename)&&(strlen(successed_config_filename))){
   WSHDR *ws = AllocWS(150);
   str_2ws(ws, successed_config_filename, 128);
   ExecuteFile(ws, 0, 0);
   FreeWS(ws);
   GeneralFuncF1(1);
  }
}
#pragma inline
static void DrawCanvasExt(void *canvas, RECT rc,int mode)
{ DrawCanvas(canvas, rc.x, rc.y, rc.x2, rc.y2, mode); }
#pragma inline
static void DrawCanvasRect(void *canvas, TRect rc,int mode)
{ DrawCanvas(canvas, rc.l, rc.t, rc.r, rc.b, mode); }
#pragma inline
static void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.x, rc.y, rc.x2, rc.y2, Font.Size,text_attribute,Font.Pen, Font.Bsh); }
#pragma inline
static void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.l, rc.t, rc.r, rc.b, Font.Size,text_attribute,Font.Pen, Font.Bsh); }
#pragma inline//�����ļ�������
static char *LoadFileBuf(const char *FileName){
  int f;
  char *buf=0;  
  uint err,fsize;  
  if ((f=fopen(FileName,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
   fsize  =lseek(f,0,S_END,&err,&err);
   if (fsize<=0){
     fclose(f,&err);     
   }else{       
    lseek(f,0,S_SET,&err,&err);
    buf=malloc(fsize+1);
    fread(f,buf,fsize,&err);    
    fclose(f,&err); 
    buf[fsize]=0;   
   }
  }
  return(buf);
}
#pragma inline//�ͷ��ļ�������
static int FreeFileBuf(char *Buffer){
  if(Buffer){
    mfree(Buffer);
    return(1);
  }else return(0);
}
#pragma inline//��ȡ��������
static byte FontSize(byte inx){
 switch(inx){
 #ifdef NEWSGOLD
  #ifdef ELKA
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(2);//#define FONT_LARGE_ITALIC 2
     case  3:return(3);//#define FONT_LARGE_ITALIC_BOLD 3
     case  4:return(4);//#define FONT_MEDIUM 4
     case  5:return(5);//#define FONT_MEDIUM_BOLD 5
     case  6:return(6);//#define FONT_MEDIUM_ITALIC 6
     case  7:return(7);//#define FONT_MEDIUM_ITALIC_BOLD 7
     case  8:return(8);//#define FONT_SMALL 8
     case  9:return(9);//#define FONT_SMALL_BOLD 9
     case 10:return(10);//#define FONT_SMALL_ITALIC 10
     case 11:return(11);//#define FONT_SMALL_ITALIC_BOLD 11
     case 12:return(8);//#define FONT_NUMERIC_SMALL 8
     case 13:return(9);//#define FONT_NUMERIC_SMALL_BOLD 9
     case 14:return(8);//#define FONT_NUMERIC_XSMALL 8
     case 15:return(0);//#define FONT_NUMERIC_LARGE 0
  default   :return(4);//#define FONT_NUMERIC_MEDIUM 4
  #else //#ifdef ELKA
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(0);//#define FONT_LARGE_ITALIC 0
     case  3:return(1);//#define FONT_LARGE_ITALIC_BOLD 1
     case  4:return(2);//#define FONT_MEDIUM 2
     case  5:return(3);//#define FONT_MEDIUM_BOLD 3
     case  6:return(2);//#define FONT_MEDIUM_ITALIC 2
     case  7:return(3);//#define FONT_MEDIUM_ITALIC_BOLD 3
     case  8:return(7);//#define FONT_SMALL 7
     case  9:return(8);//#define FONT_SMALL_BOLD 8
     case 10:return(7);//#define FONT_SMALL_ITALIC 7
     case 11:return(8);//#define FONT_SMALL_ITALIC_BOLD 8
     case 12:return(4);//#define FONT_NUMERIC_SMALL 4
     case 13:return(5);//#define FONT_NUMERIC_SMALL_BOLD 5
     case 14:return(6);//#define FONT_NUMERIC_XSMALL 6
     case 15:return(9);//#define FONT_NUMERIC_LARGE 9
  default   :return(10);//#define FONT_NUMERIC_MEDIUM 10
  #endif //#ifdef NEWSGOLD
 #else //#ifdef NEWSGOLD
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(0);//#define FONT_LARGE_ITALIC 0
     case  3:return(1);//#define FONT_LARGE_ITALIC_BOLD 1
     case  4:return(2);//#define FONT_MEDIUM 2
     case  5:return(3);//#define FONT_MEDIUM_BOLD 3
     case  6:return(2);//#define FONT_MEDIUM_ITALIC 2
     case  7:return(3);//#define FONT_MEDIUM_ITALIC_BOLD 3
     case  8:return(7);//#define FONT_SMALL 7
     case  9:return(8);//#define FONT_SMALL_BOLD 8
     case 10:return(7);//#define FONT_SMALL_ITALIC 7
     case 11:return(8);//#define FONT_SMALL_ITALIC_BOLD 8
     case 12:return(4);//#define FONT_NUMERIC_SMALL 4
     case 13:return(5);//#define FONT_NUMERIC_SMALL_BOLD 5
     case 14:return(6);//#define FONT_NUMERIC_XSMALL 6
     case 15:return(9);//#define FONT_NUMERIC_LARGE 9
  default   :return(10);//#define FONT_NUMERIC_MEDIUM 10
 #endif //#ifdef NEWSGOLD
 }
}
#pragma inline//���������ļ�
static int PlayMusic(const char *fname, byte volume, byte repeat){
    int Handle=0;
    FSTATS fstats;
    uint err;
    if((GetFileStats(fname,&fstats,&err)!=-1)&&(!IsCalling())){
      PLAYFILE_OPT INFO;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);      
      zeromem(&INFO,sizeof(PLAYFILE_OPT));
      INFO.repeat_num=repeat;
      INFO.time_between_play=0;
      INFO.play_first=0;
      INFO.volume=volume;
     #ifdef NEWSGOLD
      INFO.unk6=1;
      INFO.unk7=1;
      INFO.unk9=2;
      Handle=PlayFile(0x10, sndPath, sndName, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
     #else
      #ifdef X75
      INFO.unk4=0x80000000;
      INFO.unk5=1;
      Handle=PlayFile(0xC, sndPath, sndName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
      #else
      INFO.unk5=1;
      Handle=PlayFile(0xC, sndPath, sndName, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
      #endif
     #endif
      FreeWS(sndPath);
      FreeWS(sndName);
    }
   return(Handle);
}
#pragma inline//�����ִ�����
static uint CountTitle(char *Title[]){
 int max=0;
 for (int i=0; Title[i]!=NULL; i++)
    max++;
 return(max-1); 
}
#pragma inline//�����˵�����
static TMenu *BuildMenu(char *Title[]){
  TMenu *Menu=0;
  for (int i=0; Title[i]!=NULL; i++){
        TMenu *sbl=malloc(sizeof(TMenu));
        sbl->name=malloc(strlen(Title[i])+1);        
        strcpy(sbl->name,Title[i]);
        sbl->cmd=i;
        sbl->next=0;
        if (Menu){
          TMenu *sbr, *sbt;
          sbr=(TMenu *)&Menu;
          sbt=Menu;
          while(strcmp_nocase(sbt->name,sbl->name)<0){
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
          }
          sbl->next=sbt;
          sbr->next=sbl;
        } else{Menu=sbl;}
  }
  return(Menu);
}
#pragma inline//�����˵��б�
static void DrawMenu(void *gui, int cur_item, void *user_pointer){
  WSHDR *ws;
  TMenu *Menu=user_pointer;
  void *item=AllocMenuItem(gui);
  for (int n=0; n!=cur_item; n++) 
  {
    Menu=Menu->next;
  }  
  if (Menu)
  {
    int len=strlen(Menu->name);
    ws=AllocMenuWS(gui,len+4);
    //str_2ws(ws,Menu->name,len);
    utf8_2ws(ws,Menu->name,len);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,"%t","Error!");
  }    
  SetMenuItemText(gui, item, ws, cur_item);       
}
#pragma inline//�ͷŲ˵���Դ
static void FreeMenu(TMenu *Menu){
  while(Menu){
      TMenu *sb=Menu;
      Menu=Menu->next;
      mfree(sb->name);
      mfree(sb);
  } 
  mfree(Menu);
}
#pragma inline//��ȡ�˵�����
static int MenuCount(TMenu *Menu){
  int i=0;
  TMenu *sb=(TMenu*)&Menu;
  while((sb=sb->next)) i++;
  return (i);
}
#pragma inline//��ȡ�ļ�����
int FileCount(TFile *File){
  int i=0;
  TFile *sb=(TFile*)&File;
  while((sb=sb->next)) i++;
  return (i);
}
#pragma inline//�ͷ��ļ���Դ
static void FreeFile(TFile *File){
  while(File){
      TFile *sb=File;
      File=File->next;
      mfree(sb->path);
      mfree(sb->file);
      mfree(sb);
  } 
  mfree(File);
}
#pragma inline//��ȡ����״̬
static int IsMediaActive(void){
  char s[40];
  sprintf(s,RamMediaIsPlaying());
#ifdef NEWSGOLD
  if (s[0]==1) return 1;
#else
  if (s[0]==2) return 1;// SGOLD s[0]!=2    
#endif 
  return 0;
}
#pragma inline
static ulong HexToInt(char *HEX) { 
 ulong result=0; 
 for(int i=0 ; i<strlen(HEX) ; i++) 
 { 
  if(*(HEX+i)>='A'&&*(HEX+i)<='F') 
  { 
   result*=16; 
   result+=*(HEX+i)-'A'+10; 
  } 
  if(*(HEX+i)>='0'&&*(HEX+i)<='9') 
  { 
  result*=16; 
  result+=*(HEX+i)-'0'; 
  } 
 }
 return(result); 
}
#pragma inline
static byte FileExists(char *FileName,int *Handle){
  int ul;
  *Handle=fopen(FileName,A_ReadOnly+A_BIN,P_READ,&ul);
  if(*Handle==-1) return 0; else return 1;
}
#pragma inline
static word *LoadFontLib(void){  
  int ul;
  word *data = 0;
  char cnfont[]="4:\\ZBin\\ETC\\cnfont.dat"; 
  int handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  if(handle == -1){
    cnfont[0] = '0';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle == -1){
    cnfont[0] = '1';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle == -1){
    cnfont[0] = '2';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle != -1){
    data=(word *)malloc(73808);
    if (fread(handle,(void*)data,73808,&ul)!=73808){
      mfree((void*)data);
      data = 0;
    }
    fclose(handle,&ul);
  }
  return(data);
}
#pragma inline
static void FreeFontLib(word *data){
  if (data){
    mfree(data);
    data = 0;
  }
}
#pragma inline
static void WS2Ascii(word *data, WSHDR *ws, char *s, int maxlen){
  int len=ws->wsbody[0];
  if(maxlen != 0 && len > maxlen)
    len = maxlen;
  if(data == 0){
    ws_2str(ws, s, len);
    return;
  }
  int i,j=0;
  word temp;
  for(i=1; i<=len; i++){
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (byte)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5){
      s[j++] = (byte)(data[temp-0x4E00+32004]>>8);
      s[j++] = (byte)((data[temp-0x4E00+32004]<<8)>>8);
    }else s[j++] = '?';
  }
  s[j] = 0;
}
#pragma inline
static void Ascii2WS(word *data,WSHDR *ws, const char *s, int maxlen){
  if(data == 0){
    wsprintf(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  byte uc,uc2;
  CutWSTR(ws,0);
  while((uc=*s++) && (maxlen == 0 || s-p<maxlen)){
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else{
      uc2=*s++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else{
        wsAppendChar(ws, data[(uc-129)*127+(uc2-128)]);
      }
    }
  }
}
#pragma inline// ����ĳ�����Ƿ�����
static byte LunarYearId(ulong year){  
  return (year%4==0)&&((year%100!=0)||(year%400==0));
}
#pragma inline
static word MonthMaxDay(int year,int month){
  word result;
  switch(month){ 
  case  4: 
  case  6: 
  case  9: 
  case 11:result= 30; break;
  case  2:result= 28+LunarYearId(year);break;
  default:result= 31;
 }
 return result;
}
#pragma inline// ȡĳ���ڵ������������������ 1582 �� 10 �µ��������
static word GetDayFromYearBegin(ulong AYear,byte AMonth,byte ADay){
  word Result=0;
  for(int i= 1;i<= AMonth-1;i++){
    Result+=MonthMaxDay(AYear, i);
  }
  Result+=ADay;
  return Result;
}
#pragma inline
static word BetweenDaySum(TDate start,TDate end){
word sum=0;
TDate e = end;
TDate s = start;
if (s.month>12||e.month>12||s.month<1||e.month<1){return(sum);}
if (s.day<1||e.day<1||s.day>MonthMaxDay(s.year,s.month)||e.day>MonthMaxDay(e.year,e.month)){return(sum);}
if ((s.year>e.year)||(s.year==e.year&&s.month>e.month)||(s.year==e.year&&s.month==e.month&&s.day>e.day)){
  s.year^=e.year^=s.year^=e.year;
  s.month^=e.month^=s.month^=e.month;
  s.day^=e.day^=s.day^=e.day;
}
sum=e.day;
for(;!(s.year==e.year&&s.month==e.month);s.month++){
  sum+=MonthMaxDay(s.year,s.month);
  if(s.month==12){
     s.year++;
     s.month=0;
  }
}
sum=sum-s.day;
return(sum);
}
#pragma inline//��ȡ��ʮ�Ľ�������IDֵ
static byte LunarTermId(TDate d){ 
 if((d.year>LHYear)||(d.year<LLYear))return 0; 
 int Flag=HolDay[(d.year-LLYear)*12+d.month-1]; 
 int day=(Flag & 0x0F)+15;
 if (d.day<15) day=15-((Flag >> 4) & 0x0F);
 if (d.day==day){
   Flag=(d.month-1)*2;
   return(d.day>15?Flag+2:Flag+1);
 }else return 0;
}
#pragma inline//��ȡ����
static void *CreateCanvas()
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm){
    if (IsGuiOnTop(idlegui_id(icsm))){
      GUI *igui=GetTopGUI();      
      #ifdef ELKA
       return(BuildCanvas());
      #else
       void *idata = GetDataOfItemByID(igui,2);
       if(idata){
         return(((void **)idata)[DISPLACE_OF_IDLECANVAS/4]);         
       }
      #endif
    }
  }
  return NULL;
}
#pragma inline//��ȡ�ִ�
static short MidStr(const char *src,const char *sub,char *res){
  char *s=strstr(src,sub);
  if(s){  
      int c,i=0;
      char tmp[256];
      s+=strlen(sub);       
      while(((c=*s++)!=0x0A)&&(i<(sizeof(tmp)-1))){
        tmp[i++]=c;
      }
      tmp[i]=0;
      strcpy(res,tmp);
      return 1;
  }else{res[0]=0; return 0;}
}
#pragma inline//��ȡ�ִ�
static short MidCat(const char *src,const char *sub,char *res,char cat){
  char *s=strstr(src,sub);
  if(s){  
      int c,i=0;
      char tmp[256];
      s+=strlen(sub);       
      while(((c=*s++)!=cat)&&(i<(sizeof(tmp)-1))){
        tmp[i++]=c;
      }
      tmp[i]=0;
      strcpy(res,tmp);
      return 1;
  }else{res[0]=0; return 0;}
}
#pragma inline//�����ִ�
static short FindSub(const char *src,const char *s,char *res){
  char *p = strstr(src,s);
  if(p){
    char *sub = strchr(p,0x0A);
    word len = strlen(s);
    strncpy(res,p+len,sub-p-len);
    return 1;
  }else{return 0;}
}
#pragma inline//��ʼIMGHDR
static color IMGHDR_Color(IMGHDR *Handle, int x, int y){
  color *bm=(color*)Handle->bitmap;
  if(x < Handle->w && x>=0 && y < Handle->h && y>=0) 
    return *(bm+x+y*Handle->w);
  else
    return (color){0,0,0,0};
}
#pragma inline//��ʼIMGHDR
static void IMGHDR_Free(IMGHDR *Handle)
{
  int x, y;
  for(y=0; y<Handle->h; y++)
    for(x=0; x<Handle->w; x++)
      setcolor(Handle, x, y, (color){0,0,0,0});
}
#pragma inline//����IMGHDR
IMGHDR *IMGHDR_Create(int w, int h, int type){
  IMGHDR *img=malloc(sizeof(IMGHDR));
  img->w=w; 
  img->h=h; 
  img->bpnum=type;
  img->bitmap=malloc(h*w*sizeof(color));
  IMGHDRFree(img);
  return img;
}
#pragma inline//�ͷ�IMGHDR
static IMGHDR_Delete(IMGHDR *Handle){
  mfree(Handle->bitmap);
  mfree(Handle);
}
#pragma inline//����IMGHDR
static IMGHDR *IMGHDR_Sample(IMGHDR *Handle, int px, int py, int fast, int del){
  if (px==100 && py==100) return Handle;

  long newx = (Handle->w*px)/100,
  newy = (Handle->h*py)/100;
  
  float xScale, yScale, fX, fY;
  xScale = (float)Handle->w  / (float)newx;
  yScale = (float)Handle->h / (float)newy;
  
  IMGHDR *TEMP=IMGHDR_Create(newx,newy,CTYPE1);
  if (fast) {
    for(long y=0; y<newy; y++){
      fY = y * yScale;
      for(long x=0; x<newx; x++){
        fX = x * xScale;
        setcolor(TEMP,  x,  y, getcolor(Handle, (long)fX,(long)fY));
      }
    }
  }else {
    long ifX, ifY, ifX1, ifY1, xmax, ymax;
    float ir1, ir2, ig1, ig2, ib1, ib2, ia1, ia2, dx, dy;
    char r,g,b,a;
    color rgb1, rgb2, rgb3, rgb4;
    xmax = Handle->w-1;
    ymax = Handle->h-1;
    for(long y=0; y<newy; y++){
      fY   = y * yScale;
      ifY  = (int)fY;
      ifY1 = min(ymax, ifY+1);
      dy   = fY-ifY;
      for(long x=0; x<newx; x++){
        fX   = x * xScale;
        ifX  = (int)fX;
        ifX1 = min(xmax, ifX+1);
        dx   = fX-ifX;
        rgb1= IMGHDR_Color(Handle, ifX,ifY);
        rgb2= IMGHDR_Color(Handle, ifX1,ifY);
        rgb3= IMGHDR_Color(Handle, ifX,ifY1);
        rgb4= IMGHDR_Color(Handle, ifX1,ifY1);
        
        ir1 = rgb1.R * (1-dy)+rgb3.R * dy;
        ig1 = rgb1.G * (1-dy)+rgb3.G * dy;
        ib1 = rgb1.B * (1-dy)+rgb3.B * dy;
        ia1 = rgb1.A * (1-dy)+rgb3.A * dy;
        ir2 = rgb2.R * (1-dy)+rgb4.R * dy;
        ig2 = rgb2.G * (1-dy)+rgb4.G * dy;
        ib2 = rgb2.B * (1-dy)+rgb4.B * dy;
        ia2 = rgb2.A * (1-dy)+rgb4.A * dy;
        
        r = (char)(ir1 * (1-dx)+ir2 * dx);
        g = (char)(ig1 * (1-dx)+ig2 * dx);
        b = (char)(ib1 * (1-dx)+ib2 * dx);
        a = (char)(ia1 * (1-dx)+ia2 * dx);
        
        setcolor(TEMP, x,y,RGBA(r,g,b,a));
      }
    }
  }
  if(del)IMGHDR_Delete(Handle);
  return TEMP;  
}
#pragma inline//ת��PNG��IMGHDR
static IMGHDR *IMGHDR_Handle(int x,int y,const char *pic_path,int pic_size){
  //unsigned int pic_op = 50;
  IMGHDR *handle=0;
  if(strlen(pic_path))
  {
    FSTATS fstats;
    unsigned int err;     
    if (GetFileStats(pic_path,&fstats,&err)!=-1)
    {
      #ifdef NEWSGOLD
      if(handle=CreateIMGHDRFromPngFile(pic_path, CTYPE2)){                                                    
         handle=IMGHDR_Sample(handle, pic_size, pic_size, 0, 1);
      }      
      #else
      #ifdef X75
      if(handle=CreateIMGHDRFromPngFile(pic_path, CTYPE2)){                                                    
         handle=IMGHDR_Sample(handle, pic_size, pic_size, 0, 1);  
      }
      #else
         handle=CreateIMGHDRFromPngFile(pic_path,CTYPE2);
      #endif
      #endif
    }
  }
  return handle;
}
#pragma inline//͸��IMGHDR
static IMGHDR *IMGHDR_Alpha(IMGHDR *Handle, char a, int nw, int del){
  int i;
  color *r=(color*)Handle->bitmap;
  for(i=0;i<Handle->h*Handle->w; i++, r++)
    if(r->A>a)
      r->A-=a;
    else
      r->A=0;
    return Handle;
}
#pragma inline//��ʾIMGHDR
static IMGHDR_Draw(IMGHDR *Handle, int x, int y, char *pen, char *brush){
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,Handle->w,Handle->h);
  SetPropTo_Obj5(&drwobj,&rc,0,Handle);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}
#endif/*SIEAPI_H_*/

//�����������ñ�
#if defined(_STD_USING)
 using _CSTD Ascii2WS;
 using _CSTD BetweenDaySum;
 using _CSTD BSTRAdd;
 using _CSTD BuildMenu;
 using _CSTD cmpstr_nocase;
 using _CSTD CreateCanvas;
 using _CSTD CutFileExt;
 using _CSTD DrawCanvasExt;
 using _CSTD DrawCanvasRect;
 using _CSTD DrawMenu;
 using _CSTD DrawStringExt;
 using _CSTD DrawStringRect;
 using _CSTD ExtStrcmp;
 using _CSTD FileCount;
 using _CSTD FileExists;
 using _CSTD FindSub;
 using _CSTD FontSize;
 using _CSTD FreeFile;
 using _CSTD FreeFileBuf;
 using _CSTD FreeFontLib;
 using _CSTD FreeMenu;
 using _CSTD GetDayFromYearBegin;
 using _CSTD GetLunar;
 using _CSTD GetLDate;
 using _CSTD getstrpos;
 using _CSTD HexToInt;
 using _CSTD IMGHDR_Alpha;
 using _CSTD IMGHDR_Color;
 using _CSTD IMGHDR_Delete;
 using _CSTD IMGHDR_Draw;
 using _CSTD IMGHDR_Free;
 using _CSTD IMGHDR_Handle;
 using _CSTD IMGHDR_Sample;
 using _CSTD IsMediaActive;
 using _CSTD KeyButton;
 using _CSTD kill_data;
 using _CSTD LoadFileBuf;
 using _CSTD LoadFontLib;
 using _CSTD LunarHolID;
 using _CSTD LunarYearId;
 using _CSTD MenuCount;
 using _CSTD MidCat;
 using _CSTD MidStr;
 using _CSTD OpenBCFGFile;
 using _CSTD patch_dialog;
 using _CSTD patch_header;
 using _CSTD patch_input;
 using _CSTD patch_rect;
 using _CSTD PixlsWidth;
 using _CSTD PlayMusic;
 using _CSTD RunADR;
 using _CSTD RunAPP;
 using _CSTD RunCUT;
 using _CSTD seqkill;
 using _CSTD SetRect;
 using _CSTD str2ws_unicode;
 using _CSTD strcmp_nocase;
 using _CSTD strtol;
 using _CSTD strtoul;
 using _CSTD SumDays;
 using _CSTD toupper;
 using _CSTD unicode2utf8;
 using _CSTD unicodeSwitch;
 using _CSTD utf82unicode;
 using _CSTD WS2Ascii;
 using _CSTD ws2str_unicode;
 using _CSTD Odd;
#endif /* �����������ñ� */
 

