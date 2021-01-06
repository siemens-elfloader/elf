
// Редактор Edit 
// взято в http://cbn.narod.ru  (c)bn
// Подключить сорцы ZLib, взятые, например, тут: http://cbn.narod.ru/UnZipFull.rar
// Распаклвка 7z, rar не включена!

//#define NEWSGOLD // Независимо от типа мобилы (автоопред-е)
#include "..\swilib.h"
#include "tables.h"

char *Title="Edit 0.74 (c)bn";
extern char *screen;//[132*176]; // Экран 132*176*2
extern int width, height, screensize;
extern unsigned char SGOLD2, C65, S75, EL71;
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();

const char *errors[]={
  0,
  "Ошибка загрузки файла"
};

#define lightdelay 262/10
//#define lightdelay2 262/10
#define mindelay 262*60
#define byte unsigned char
#define false 0
#define null 0
#define true 1
#define boolean char

	const int FONMAX=0xe0;
	int FONSIZEY, FONSIZEYY, FONSIZEX, MAXY, MAXX, MAXHEX;//р-р шрифта и строк на экране;
        boolean cursoronly=false;//, cursoronly2=false;
	int wid=132, hei=176; 	// Р-ры экрана
	//int menunum, menupos, menustart, menuend, menumax, menuptr; //menu
        //int inputptr=0, inputnum=0;
        int curoldx=-1, curoldy=-1;
int p; //tmp
int f;
int menupos=0;
byte lastkey=0, inskey=0, hexkey=0, inputhex=0, keypressed=0;
byte tmpcolor;
volatile int sleepmin=0;

void rotate();
void movepgup();
void moveup();
void movedown();
void movepgdown();
void curup();
void curdown();
void curleft();
void curright();
void hexcurup();
void hexcurdown();
void hexcurleft();
void hexcurright();
void hexdown();
void hexup();
void enter();
void delete(int pos);
int getcurpos();
void savetext();
void keyshow();
void insert(byte sym, int pos);
void getPG(int *PG);
void hexyi(int x, int yy, byte ssym);
void ramka(int size);
void keycursor(int pos);
void insertkey();
int rundll2(char *exename, void *p1, void *p2, void *p3);
//Плугин для edit получает параметр p1=буфер_данных
//и возвращает размер модифицир.д-х

const int cachemax=64;
int cache[64], cachest=0, cachend=0;
byte font[4096+256]; //font all
byte *symptr[256], *symptr2[256]; //* символы
byte sym[256], sym2[256]; // стр. симв.
int PG[300/2+2], PGEX[300/2+2]; //* строк //176/2
byte PGper[300/2+2];

int menunum=0; //Текущее меню
int paramlength=0;
byte *param=0; //Все параметры free
byte *text=0; //Весь текст free
byte *dict=0, *logs=0; // Словарь и файл errors
char filename[128], dllname[128], *file;

int textend=0, textmax=0;
volatile int flags=0; // Размер текста 
const int fmodify=1, fnosave=1<<1, fhelp=1<<2, fsaving=1<<3, fdll=1<<4;  //Флаги flags
const int frotate=1, frotate2=1<<1, fedit=1<<2, fhex=1<<3, fenglish=1<<4, fkeylight=1<<5, 
  fxconst=1<<6, finsert=1<<7, fslowlight=1<<8, fesc=1<<9; //Флаги t.f
const int fdelcr=1<<10, fwrap=1<<11, fxspace=1<<12, findent=1<<13; 

struct parst{
  int f;	// Все флаги
  int pos;      // Тек. поз.
  char curx,curxx,cury; // Коорд. курсора
  byte m8k;    // 64k free mem blks
  byte font;    // Шрифт
  char ysize;   // Межстрочный интервал
  byte xsize;   // Ужатый шрифт  
  byte codepage; // Кодовая страница
  byte diction;  // Номер словаря
  byte color, bkcolor; // Цвета текста и фона
  byte filenamesize; // Длина имени файла ; // Далее идет имя файла (выравнено на 4 б! в конце 0)
  byte keypause;  // Пауза ожидания нажатия след. клав. при ред-ии
  byte keytable; // Кодировка рус/лат
  byte light,minexit;
  int zakl[5];  // Закладки
//  int temp;
} *par, t={0,0,0,0,0,  1,2,1,0,1,0, 0,0xff,0, 1,0,0,0, 0,0,0,0,0};

const byte title[]={'c','b','n',sizeof(struct parst),8,0,0,0};
const char extini[]=".ini";
const char exthlp[]=".txt";
const char extfnt[]=" .fnt";
const char extlst[]=" .lst";
const char extdll[]=".dll";

void initedit(){
  cachest=cachend=t.curx=t.curxx=t.cury=inputhex=inskey=hexkey=lastkey=keypressed=0;
  curoldx=curoldy=-1;
}

GBSTMR timer, lighttimer, mintimer;
void timer_proc(void){ // Функция выполняется по таймеру 10 раз в секунду
  if(!menunum && inskey && keypressed){
    insertkey();
  }
}

void timer_light(void){ // Функция выполняется по таймеру 10 раз в секунду
  if(t.light){
    if(sleepmin<5){
      SetIllumination(0,1,t.light,0);
      if(!(t.f&fkeylight)) SetIllumination(1,1,t.light,0);
    }else if(sleepmin==5){
      SetIllumination(0,1,0,0);
      if(!(t.f&fkeylight)) SetIllumination(1,1,0,0);
    }
    GBS_StartTimerProc(&lighttimer,lightdelay,timer_light);
  }
}

void timer_min(void){ // Функция выполняется ежеминутно
  ++sleepmin;
//  if(t.minexit && ++sleepmin>=t.minexit){
//    //RestartIDLETMR();
//    SetIDLETMR(1,(SGOLD2)?MSG_GUI_DESTROYED:0x98);
//  }else
    GBS_StartTimerProc(&mintimer,mindelay,timer_min);
}
//char debarea[10000], *deb=debarea;
//
//void debsave(){
//  int f;
//  f=fopen("0:\\ZBin\\gb\\log",A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE,&err);
//  if (f==-1) return;
//  fwrite(f,debarea,deb-debarea,&err);
//  fclose(f,&err);
//}
//
//void debug(int num, int val){
//  if(deb-debarea<9800){
//  sprintf(deb,"\n%d = %d",num,val);
//  deb+=strlen(deb);
//  }
//}

void getmaxy(){  // Пересчет MAXX,MAXY и width,height
  if(t.f&frotate){ wid=(C65)?130:height; hei=width;}
  else{ wid=width; hei=(C65)?130:height;}
  MAXX=wid/FONSIZEX;
  MAXY=(hei-1)/(FONSIZEY+t.ysize); 
  MAXHEX=(MAXX-4)/3;
  initedit();
}
  
void setcodepage(byte *sym, int page){ // Подг. табл. перекод. симв. (если измен.кодир,все большие)
  int i, A,P,a,p;
  memset(sym,0,0x100);
  if(sym!=sym2 && t.font>=5){
  for(i=0x20;i<0x100;i++)
    sym[i]=i;
  switch(page){
    case 0:  return; //dos
    case 1:  A=0xc0; P=0xd0; a=0xe0; p=0xf0; break; //win
    default: A=0xb0; P=0xc0; a=0xd0; p=0xe0; //iso
  }
  for(i=0;i<0x10;i++){
    sym[A+i]=(byte)(0x80+i);
    sym[P+i]=(byte)(0x90+i);
    sym[a+i]=(byte)(0xa0+i);
    sym[p+i]=(byte)(0xe0+i);
  }
  if(page!=1){sym[0xf0]=0x45; sym[0xf1]=0x65;}  //Ёё в Ее
  }else{
  switch(page){
    case 0:  A=0x80; P=0x90; a=0xa0; p=0xe0; break; //dos
    case 1:  A=0xc0; P=0xd0; a=0xe0; p=0xf0; break; //win
    default: A=0xb0; P=0xc0; a=0xd0; p=0xe0; //iso
  }
  for(i=0x20;i<0x80;i++)
    sym[i]=(byte)(i-0x20);
  for(i=0;i<0x10;i++){
    sym[A+i]=(byte)(0xa0+i);
    sym[P+i]=(byte)(0xb0+i);
    sym[a+i]=(byte)(0xc0+i);
    sym[p+i]=(byte)(0xd0+i);
  }
  if(page!=1){sym[0xf0]=0x25; sym[0xf1]=0x45;}  //Ёё в Ее
}}

void loadfont(){	//Загрузить шрифт
  int i, fontsize;
  byte *k;
  if(t.font!=2){
    memcpy(file,extfnt,6);
    *file=t.font+'0';
    if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
      if((fontsize=fread(f,font+(t.font<5?0:256),sizeof(font)-256,&err))<256*3) t.font=99;
      fclose(f,&err);
    }else t.font=99;
  }
  switch(t.font){
    case 5: case 6: case 7: case 8: case 9: //big font
      FONSIZEY=FONSIZEYY=fontsize/256; 
      memset(font,FONSIZEX=8,256); break;
    case 0: FONSIZEY=FONSIZEYY=6; FONSIZEX=4; break; //5x3
    case 1: FONSIZEY=FONSIZEYY=7; FONSIZEX=5; break; //6x3
    case 3: FONSIZEY=FONSIZEYY=8; FONSIZEX=7; break; //7x5
    case 4: FONSIZEY=9; FONSIZEYY=8; FONSIZEX=7; break; //8x5
    default: t.font=2; 
    case 2: memcpy(font,fontdef,sizeof(fontdef));
      FONSIZEY=FONSIZEYY=7; FONSIZEX=6; break; //6x4
  }
  if(t.font<5)
  for(i=0,k=font+FONMAX;i<FONMAX;i++){
    symptr[i]=k;
    k+=font[i];
  }
  setcodepage(sym,t.codepage);
  getmaxy();
}

void loadhelp(){
  savetext();
  flags|=fhelp;
  if(text) mfree(text);
  t.pos=cachest=cachend=menunum=0;
  text=0; flags=0;
  paramlength=0;
  memcpy(file,exthlp,5);
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return;
  textend=textmax=lseek(f,0,2,&err,&err);
  lseek(f,0,0,&err,&err);
  text=(byte*)malloc(textend);
  fread32(f, (byte*)text, textend, &err);
  fclose(f,&err);
  setcodepage(sym,t.codepage=1);
  flags|=fhelp;
}

inline void cls(){
  memset(screen,t.bkcolor,screensize);
}   

void oncreate(){
  //   mode=0;
//   SUBPROC((void *)execute);
//   DrawScreen();
//  t.light=1;////
  if(t.light)
    GBS_StartTimerProc(&lighttimer,lightdelay,timer_light);
  GBS_StartTimerProc(&mintimer,mindelay,timer_min);
}

int menumax(){
  int i=0;
  char **s=menus[menunum-1];
  while(*++s) ++i;
  return i;
}

void menuexit(){
  switch(menunum-1){
  case 1: menunum=1; menupos=0; break;
  case 2: menunum=1; menupos=1; break;
  case 3: menunum=1; menupos=2; break;
  case 4: menunum=2; menupos=0; break;
  case 5: menunum=2; menupos=1; break;
  case 6: menunum=2; menupos=2; break;
  case 0: default:  menunum=0; break;
  }
}

inline void invflag(int fl){
  if(t.f&fl) t.f&=~fl; else t.f|=fl; menunum=0;
}

int menuaction(){
  switch(((menunum-1)<<4)|(menupos+1)){
  //main menu
  case 3: if(!(t.f&fedit)) break;
  case 1: case 2: menunum=menupos+2; menupos=0; break;
  case 4: break; //words !!!
  case 5: invflag(fedit); initedit();; break;
  case 6:  switch(t.f&3){
    case 0: t.f|=frotate; break;
    case 1: t.f|=frotate2; break;
    case 2: case 3: t.f&=0xfffffffc; break;
    } getmaxy(); menunum=0; break;
  case 7: break; //errors
  case 8: invflag(fhex); initedit(); break;
  case 9: loadhelp(); break;
  case 10: return 1; //exit
  //options
  case 0x11: case 0x12: case 0x13: menunum=menupos+5; menupos=0; break;
  case 0x14: menunum=104; break;
  case 0x15: menunum=112; break;
  case 0x16: menunum=105; break;
//  case 0x17: menunum=113; break;
  case 0x17: menunum=114; break;
  case 0x18: menunum=106; break;
  case 0x19: menunum=109; break;
  case 0x1a: menunum=115; break;

  //закладки
  case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
    if(lastkey==LEFT_SOFT){ //goto label
      if(t.zakl[menupos]<textend)  t.pos=t.zakl[menupos];
    }else t.zakl[menupos]=t.pos; 
    menunum=0;  break;
  //blocks
  case 0x31: break; 
  case 0x35: if(flags&fmodify) SUBPROC((void*)savetext); menunum=0; break;
  case 0x3a: flags&=~fmodify; return 1; //no save & exit
  //fonts
  case 0x41:  case 0x42:  case 0x43:  case 0x44:  case 0x45:
  case 0x46:  case 0x47:  case 0x48:  case 0x49:  case 0x4a:
    t.font=menupos; loadfont();  cachest=cachend=menunum=0; break;
  //Абзацы
  case 0x51: invflag(fdelcr); break;
  case 0x52: invflag(fwrap); break;
  case 0x53: invflag(fxspace); break;
  case 0x54: invflag(fxconst); break;
  case 0x55: invflag(finsert); break;
  case 0x56: invflag(findent); break;
  case 0x57: invflag(fkeylight); break;
//  case 0x5a: invflag(fesc); break;
//  case 0x5b: menunum=200; break;
  //Кодировки
  case 0x61: case 0x62: case 0x63: setcodepage(sym,t.codepage=menupos); menunum=0; break;
  case 0x64: if(t.f&fenglish){ t.f&=~fenglish; menus=menuru;}
             else{ t.f|=fenglish; menus=menuen;} menunum=0; break;
  default: menunum=0; break;
  }
  return 0;
}

void newhex(int code){
  int pos=t.pos+t.cury*MAXHEX+t.curx;
  if(pos<textend){
    flags|=fmodify;
    switch(code){
    case -2:
      if(inputhex&1) text[pos]-=0x10;
      else text[pos]=(text[pos]&0xf0)|(((text[pos]&0xf)-1)&0xf);
      break;
    case -1: 
      if(inputhex&1) text[pos]+=0x10;
      else text[pos]=(text[pos]&0xf0)|(((text[pos]&0xf)+1)&0xf);
      break;
    default: 
      if(inputhex&1) text[pos]=(code<<4)|(text[pos]&0xf);
      else text[pos]=(text[pos]&0xf0)|code;
    }
}}

char decode(byte c){
  if(t.codepage==0 && c>=0xc0){
    if(c>=0xf0) c-=0x10;
    else c-=0x40;
  }return c;
}

void keyshow(){ //Показать клавишу и запустить таймер
  int i=0,len;
  char *s=keylines[t.keytable+inskey-'0'];
  if(t.f&frotate2) rotate();
  ramka(len=strlen(s));
  if(!len) ++len;
  while(*s) hexyi(i++,MAXY,sym[decode(*s++)&0xff]);
  keycursor((keypressed-1)%len);
  if(t.f&frotate2) rotate();
  DrawScreen();
  GBS_StartTimerProc(&timer,262/(t.keypause+1),timer_proc);
}


void insertkey(){ //Вставить символ
  char *s=keylines[t.keytable+inskey-'0'];
  int i=strlen(s);
  if(!i) ++i;
  char b=decode(s[(keypressed-1)%i]);
  if(t.f&finsert) text[getcurpos()]=b;
  else insert(b,getcurpos());
  //getPG(PG);
  inskey=keypressed=0; curright(); t.curxx=t.curx;
  cursoronly=false;
  onredraw(); DrawScreen();
}

//------------------------------------------------------------------------------
// Осн. диалог - обработка кнопок
//------------------------------------------------------------------------------
int onkey(unsigned char keycode, int pressed){
  switch(pressed){      
  case KEY_UP: // Клавиша отпущена
    //SetIllumination(0,1,t.light,0);
    //;R0 id устройства 0-дисплей,1-кл,2-дин.свет
    ///;R1 1
    //;R2 яркость подсветки
    //;R3 задержка гашения
    //GBS_StartTimerProc(&lighttimer,262*65,timer_light);
    break; 
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
//    if(keycode==RED_BUTTON) return 1;
  case KEY_DOWN: // Клавиша нажата
   sleepmin=0;
   if((keycode==RED_BUTTON && !menunum) || (keycode==GREEN_BUTTON && !t.f&fedit)) return 1;
    switch(menunum){
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: // in menu
      switch(keycode){
      case '0': keycode='9'+1;
      case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': 
        menupos=keycode-'1'; lastkey=keycode; if(menuaction()) return 1; break;
      case RED_BUTTON: menuexit(); break;
      case RIGHT_SOFT: case LEFT_SOFT: case ENTER_BUTTON: //enter
        lastkey=keycode; if(menuaction()) return 1; break;
      case UP_BUTTON: case LEFT_BUTTON: case '*': //up
        if(menupos>0) --menupos;
        else menupos=menumax()-1;
        break;
      case DOWN_BUTTON: case RIGHT_BUTTON: case '#': //down
        if(menupos<menumax()-1) ++menupos;
        else menupos=0;
        break;
      default: menuexit();
      } break;// special modes
    case 104: if(keycode>='0' && keycode<='6'){
        t.ysize=keycode-'2'; getmaxy();
      } menunum=0; break;
    case 112: if(keycode>='0' && keycode<='4'){
        t.xsize=keycode-'0';// getmaxy();//???
      } menunum=0; break;
    case 113: if(keycode>'0' && keycode<='9'){
        t.m8k=keycode-'0';
      } menunum=0; break;
    case 114: if(keycode>='0' && keycode<='3'){
        t.keypause=keycode-'0';
      } menunum=0; break;
    case 115: if(keycode>='0' && keycode<='9'){ ++menunum; tmpcolor=keycode-'0';} else menunum=0; break;
    case 116: if(keycode>='0' && keycode<='9') t.light=tmpcolor*10+keycode-'0';  
      if(t.light) GBS_StartTimerProc(&lighttimer,lightdelay,timer_light);
      menunum=0; break;
    case 200: 
      if(keycode>='0' && keycode<='9'){
        t.minexit=(keycode-'0');
      } menunum=0; break;
    case 105: if(keycode>='0' && keycode<='9'){
        t.diction=keycode-'0';
      } menunum=0; break;
    case 106:  if(keycode>='0' && keycode<='7'){ ++menunum; tmpcolor=(keycode-'0')<<5;} else menunum=2; break;
    case 107:  if(keycode>='0' && keycode<='7'){ ++menunum; tmpcolor|=((keycode-'0')<<2);} else menunum=2; break;
    case 108:  if(keycode>='0' && keycode<='7') t.color=tmpcolor|((keycode-'0')>>1);  
      if(t.color==t.bkcolor) t.color=!t.bkcolor; menunum=2; break;
    case 109:  if(keycode>='0' && keycode<='7'){ ++menunum; tmpcolor=(keycode-'0')<<5;} else menunum=2; break;
    case 110:  if(keycode>='0' && keycode<='7'){ ++menunum; tmpcolor|=((keycode-'0')<<2);} else menunum=2; break;
    case 111:  if(keycode>='0' && keycode<='7') t.bkcolor=tmpcolor|((keycode-'0')>>1);  
      if(t.color==t.bkcolor) t.bkcolor=!t.color; menunum=2; break;
    case 8: //statistic
    default: menunum=0; break;
    //
    case 0: // view & edit modes
    if(t.f&frotate)
      switch(keycode){
      case UP_BUTTON:  keycode=(t.f&frotate2)?RIGHT_BUTTON:LEFT_BUTTON; break;
      case DOWN_BUTTON:  keycode=(t.f&frotate2)?LEFT_BUTTON:RIGHT_BUTTON; break;
      case LEFT_BUTTON:  keycode=(t.f&frotate2)?UP_BUTTON:DOWN_BUTTON; break;
      case RIGHT_BUTTON: keycode=(t.f&frotate2)?DOWN_BUTTON:UP_BUTTON; break;
      }
    if(t.f&fhex){ //HEX mode
      if(t.f&fedit){
      cursoronly=false;
      switch(keycode){
        case RIGHT_SOFT: menunum=1; menupos=0; break; //main menu
  	case UP_BUTTON:  hexcurup(); break;
	case DOWN_BUTTON:  hexcurdown(); break;
	case LEFT_BUTTON:  hexcurleft(); break;
	case RIGHT_BUTTON: hexcurright(); break;
        case '*': newhex(-1); break;
        case '#': newhex(-2); break;
       case RED_BUTTON: 
        if(t.f&fesc) return 1;
      case ENTER_BUTTON: case GREEN_BUTTON:
      case LEFT_SOFT:  ++inputhex; break;
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': 
        case '7': case '8': case '9': 
         if(!(hexkey>='0' && hexkey<='9')) inputhex=0; 
         ++inputhex; newhex(keycode-'0'); 
         if(inputhex>1){ inputhex=0; hexcurright(); cursoronly=false;}
         break;
      default: return 0; ///break; !!!
      } hexkey=keycode;
      }else{
      switch(keycode){
    case RIGHT_SOFT: menunum=1; menupos=0; break; //main menu
    case '5':
    case ENTER_BUTTON: menunum=8; break; //statshow()
    case RED_BUTTON: 
       if(t.f&fesc) return 1;
    case LEFT_SOFT: break;
    case LEFT_BUTTON: //if((t.f&3)==1){ hexdown(); break;}
    case '2':
    case UP_BUTTON: hexup(); break;
    case RIGHT_BUTTON: //if((t.f&3)==1){ hexup(); break;}
    case DOWN_BUTTON: 
     default:  hexdown(); break;
      }}}else
    if(t.f&fedit){ //EDIT TEXT
     cursoronly=false;
     if(inskey){
       if(inskey==keycode){ ++keypressed; keyshow(); return 0;}
       else if(keycode==RED_BUTTON){ inskey=keypressed=0; break;}
         else insertkey();
     }switch(keycode){
        case RIGHT_SOFT: menunum=1; menupos=0; break; //main menu
  	case UP_BUTTON:    curup(); break;
	case DOWN_BUTTON:  curdown(); break;
	case LEFT_BUTTON:  curleft(); break;
	case RIGHT_BUTTON: curright(); break;
        case ENTER_BUTTON:  enter(); break;
        case '*': if((t.keytable+=10)>40) t.keytable=0; break;//меню надо бы...
        case LEFT_SOFT: curleft();
        case RED_BUTTON:  
          if(t.f&fesc) return 1;
        case GREEN_BUTTON:
          delete(getcurpos()); cursoronly=false; break;
     default:
      if(keycode>='0' && keycode<='9'){
        inskey=keycode; keypressed=1;
        keyshow(); return 0;
      }
     } lastkey=keycode;
    }else{ //VIEW TEXT
    switch(keycode){
    case GREEN_BUTTON: return 1;
    case RIGHT_SOFT: menunum=1; menupos=0; break; //main menu
    case '5':  
    case ENTER_BUTTON: menunum=8; break; //statshow()
    case RED_BUTTON: 
       if(t.f&fesc) return 1;
    case LEFT_SOFT: break;
    case LEFT_BUTTON: if((t.f&3)==3){ movepgdown(); break;}
    case '2': 
    case UP_BUTTON: movepgup(); break;
    case RIGHT_BUTTON: if((t.f&3)==3){ movepgup(); break;}
    case DOWN_BUTTON: 
     default:  movepgdown(); break;
    }
//    lastkey=keycode;
   } break; //end viewkeys
    }
    onredraw(); DrawScreen(); // Перерисовать экран
    break;
  }
  return 0;
}

void onexit(){
  if(param) mfree(param);
  if(text) mfree(text);
  if(dict) mfree(dict);
  if(logs) mfree(logs);
//    debsave();//////
}

void menualloc(){
  int i;
  byte *k;
  for(i=0,k=fontdef+FONMAX;i<FONMAX;i++){
    symptr2[i]=k;
    k+=fontdef[i];
  }
  setcodepage(sym2,1);
}

inline int strsize(char *s){
  return (strlen(s)+4)&0xfc;
}

int loadini(char *fname){
  int fnsize, fnamesize;
  byte *ptr;
  char tmp[4];
  memcpy(file,extini,5);
  if(fname && fname[1]==':'){ //есть файл
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1){ //no ini file
lab1:    
    paramlength=8+sizeof(struct parst)+(fnsize=strsize(fname));
    param=(byte*)malloc(paramlength);
    memcpy(param,title,8);
    //*(int*)(param+4)=8;
    par=(struct parst*)(param+8);
    memcpy(param+paramlength-fnsize, fname, t.filenamesize=strlen(fname)+1);
  }else{ //find in ini file
    if((paramlength=lseek(f,0,2,&err,&err))<10+sizeof(struct parst)){ fclose(f,&err); goto lab1;}
    lseek(f,0,0,&err,&err);
    param=(byte*)malloc(paramlength+sizeof(struct parst)+(fnsize=strsize(fname)));
    fread32(f, param, paramlength, &err);
    fclose(f,&err);
    if(!(param[0]=='c' && param[1]=='b' && param[3]==sizeof(struct parst))) goto lab1;
    fnamesize=strlen(fname)+1;
    ptr=param+8;
    do{
      par=(struct parst*)ptr;
      if(par->filenamesize==fnamesize && !memcmp((char*)par+sizeof(struct parst),fname,fnamesize)) break;
    }while((ptr+=sizeof(struct parst)+((par->filenamesize+3)&0xfc)) < param+paramlength);
    if(ptr<param+paramlength){ //found
      memcpy(&t,par,sizeof(struct parst));
    }else{ //not found!
      paramlength+=sizeof(struct parst)+fnsize;
      memcpy(&t,param+*(int*)(param+4),sizeof(struct parst));////?? last cfg
      t.pos=t.curx=t.cury=t.curxx=t.zakl[0]=t.zakl[1]=t.zakl[2]=t.zakl[3]=t.zakl[4]=0; //NULL init
      par=(struct parst*)ptr;
      memcpy(par,&t,sizeof(struct parst));
      memcpy(param+paramlength-fnsize, fname, t.filenamesize=strlen(fname)+1);
    }
    *(int*)(param+4)=(byte*)par-param;
  }}else{ //fname=0
    if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1){ //no ini file
lab2:
      par=&t; //help only
      paramlength=0;
    }else{ //last filename from ini
      if((paramlength=lseek(f,0,2,&err,&err))<10+sizeof(struct parst)){ fclose(f,&err); goto lab2;}
      lseek(f,0,0,&err,&err);
      param=(byte*)malloc(paramlength);
      fread32(f, param, paramlength, &err);
      fclose(f,&err);
      if(!(param[0]=='c' && param[1]=='b' && param[3]==sizeof(struct parst))) goto lab2;
      par=(struct parst*)(param+*(int*)(param+4));
      memcpy(&t,par,sizeof(struct parst));
  }}
////////////////
  if(!paramlength || (f=fopen((char*)par+sizeof(struct parst),A_ReadOnly+A_BIN,P_READ,&err))==-1){ //open help
    paramlength=0;
    flags|=fhelp;
    memcpy(file,exthlp,5);
    if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 1;
  }
  fread(f,tmp,4,&err);
  if((*tmp==0x50 && tmp[1]==0x4b)||(*tmp=='R' && tmp[1]=='a')||(*tmp=='7' && tmp[1]=='z')){
    fclose(f,&err);
    flags|=fnosave; 
    if(!(text=(byte*)loadfile((char*)par+sizeof(struct parst)))) return 1;
    textend=textmax=loadfilesize;
  }else{
  textend=lseek(f,0,2,&err,&err);
  textmax=textend+((flags&fhelp)?0:(t.m8k<<13));
  lseek(f,0,0,&err,&err);
  if(!(text=(byte*)malloc(textmax))){ fclose(f,&err); return 1;}
  fread32(f, (byte*)text, textend, &err);
  fclose(f,&err);
  }
  //dll
  if((f=fopen(dllname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fclose(f,&err);
    flags|=(fnosave | fdll); 
    text[textend-1]=0;
    textend=rundll2(dllname,text,(void*)textend,0);
  }
  return 0;
}

void saveini(){
  memcpy(file,extini,5);
  if(paramlength && (f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    memcpy(par,&t,sizeof(struct parst));
    fwrite32(f, param, paramlength, &err);
    fclose(f,&err);
  }
}

void savetext(){
  if(!(flags&(fsaving|fhelp|fnosave))){
  if(flags&fmodify){ 
    flags|=fsaving;
    if(paramlength && (f=fopen((char*)par+sizeof(struct parst),A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
      fwrite32(f, (byte*)text, textend, &err);
      fclose(f,&err);
    }
    flags&=~(fsaving|fmodify);
}}}

void correct(){  //Соответствия значений
  if(t.pos>=textend) t.pos=0; //...
  if(t.f&fenglish) menus=menuen;
  if(t.f&fedit) initedit();
}

void getPG(int *PG){	// Получить указатели строк на экране
  int i,len,pos=t.pos, spos, npos;
  byte ssym, nfirst=0;
  for(i=0;i<=MAXY;i++){ PG[i]=0; PGper[i]=0;}
  for(i=0;i<=MAXY;i++){
	PG[i]=spos=pos;
	len=1;
        --pos;
	while(len<wid && ++pos<textend){
          if(text[pos]==0xd && (t.f&(fdelcr|fedit) || flags&fhelp || (pos<textend-3 && text[pos+2]==0xd))){
            // do pos+=2; while(text[pos]==0xd && pos+2<textend && text[pos+2]==0xd);
        //    pos+=2; 
            break;
          }
          if(nfirst && pos>0 && !sym[text[pos]] && !sym[text[pos-1]]) continue;
          nfirst=1;
//          if(ftab && text[pos]==0x2e && pos>1 && pos<textend-2 && getsym[text[pos-2]&0xff]!=0 
//           && text[pos-2]!=0x2e &&(text[pos-1]<0x30 || text[pos-1]>0x39) && (text[pos+1]==0x20 
//           || text[pos+1]==0xd)){ 
//              bnextab=true; ++pos; x+=fon[0xe]; break;
//           }
//          if((ssym=sym[text[pos]])!=0) bissym=true;
//          if(!(ssym==0 && prevsym==0)){  x+=fon[sym]; if(sym==0) ++cntspaces; }

	  ssym=sym[text[pos]];
          len+=(t.f&(fedit|fxconst))?FONSIZEX:font[ssym];
          //++pos;
	}
        //if(pos>=textend) break;//УДАЛЕНО
        if(pos<textend && text[pos]==0xd) pos+=2; //добавли pos<textend
	else{
          --pos;
          npos=pos;
          while(--pos>spos && text[pos]!=0x20 && !perenos[text[pos]]);
          if(pos==spos){ pos=npos; continue;}
          if(text[pos-1]==0x20) continue;
          if(perenos[text[pos]]==1) PGper[i]=1;
          ++pos;
        }
  }
  //if(pos>=textend) PG[i]=textend; //УДАЛЕНО
}

void rotate(){
  char *s=screen, *ss=screen+screensize, c;
  while(s<ss){ c=*s; *s++=*--ss; *ss=c;}
  if(C65){
    memcpy(screen,screen+(176-130)*132,132*130);
    memset(screen+132*130,t.bkcolor,(176-130)*132);
  }
}


void cursor(int x, int y){ // Нарисовать курсор в curx,cury
  byte *s, *ss;
  int i,j;
  if(x>=0 && y>=0){
    if(t.f&fhex){ //hex
  if(t.f&frotate){//rotate
    if(t.f&frotate2) rotate();  
    ss=(byte*)screen +hei+hei-1-(FONSIZEY+t.ysize)*(y+2)+FONSIZEX*hei*3;
    s=ss+(FONSIZEX*hei*x<<1);
    ss+=FONSIZEX*hei*((MAXHEX<<1)+x+1);
    for(j=0;j<FONSIZEX+FONSIZEX;j++){
      for(i=0;i<FONSIZEY+t.ysize;i++,s++)
        *s=(*s==t.bkcolor)?t.color:t.bkcolor;
      s+=hei-(FONSIZEY+t.ysize);
    }
    for(j=0;j<FONSIZEX;j++){
      for(i=0;i<FONSIZEY+t.ysize;i++,ss++)
        *ss=(*ss==t.bkcolor)?t.color:t.bkcolor;
      ss+=hei-(FONSIZEY+t.ysize);
    }
    if(t.f&frotate2) rotate();  
  }else{ //norotate
    ss=(byte*)screen+(FONSIZEY+t.ysize)*wid*(y+1)+wid+FONSIZEX*3;
    s=ss+(FONSIZEX*x<<1);
    ss+=FONSIZEX*((MAXHEX<<1)+x+1);
    for(j=0;j<FONSIZEY+t.ysize;j++){
      for(i=0;i<FONSIZEX+FONSIZEX;i++,s++)
        *s=(*s==t.bkcolor)?t.color:t.bkcolor;
      s+=wid-FONSIZEX-FONSIZEX;
      for(i=0;i<FONSIZEX;i++,ss++)
        *ss=(*ss==t.bkcolor)?t.color:t.bkcolor;
      ss+=wid-FONSIZEX;
    }
  }
    }else{ //no hex
  if(t.f&frotate){//rotate
    if(t.f&frotate2) rotate();  
    s=(byte*)screen+FONSIZEX*x*hei+hei+hei-1-(FONSIZEY+t.ysize)*(y+1);
    for(j=0;j<FONSIZEX;j++){
      for(i=0;i<FONSIZEY+t.ysize;i++,s++)
        *s=(*s==t.bkcolor)?t.color:t.bkcolor;
      s+=hei-(FONSIZEY+t.ysize);
    }
    if(t.f&frotate2) rotate();  
  }else{//norotate
    s=(byte*)screen+(FONSIZEY+t.ysize)*wid*y+FONSIZEX*x+1;
    for(j=0;j<FONSIZEY+t.ysize;j++){
      for(i=0;i<FONSIZEX;i++,s++)
        *s=(*s==t.bkcolor)?t.color:t.bkcolor;
      s+=wid-FONSIZEX;
    }
  }
  }}
  curoldx=x; curoldy=y;
}

void menucursor(){
  int i;
  byte *s=(byte*)screen;//+132*5;
  for(i=0;i<width*13;i++,s++)
    *s=(*s==t.bkcolor)?t.color:t.bkcolor;
  s=(byte*)screen+(menupos+1)*10*width+width*5;
  for(i=0;i<width*8;i++,s++)
    *s=(*s==t.bkcolor)?t.color:t.bkcolor;
}

void menushow(){ // Отобразить меню
  char **menu;
  byte *s;
  TDate date;
  TTime time;
  int ssym,b, j,k, x,y=width*2,xy;
  if(menunum>0 && menunum<9){
  if(menunum==8){ //statistic
    menupos=0;
    GetDateTime(&date,&time);
    menu=menus[menunum-1];
    //s=(byte*)*menu++;
    sprintf(*menu++ +7,"%d:%02d",time.hour,time.min);//ВРЕМЯ
    s=(byte*)par+sizeof(struct parst);
    memcpy(*menu++,s,strlen((char*)s)<19?strlen((char*)s)+1:20);//Имя файла
    sprintf(*menu++ +11,"%d/%d",t.pos>>7,textend>>7); //Страница
    j=textend?textend:1;
    k=t.pos*100/j;
    sprintf(*menu++ +14,"%d.%02d%%",k, (t.pos*100-k*j)*100/j );
            //(t.pos*10000/j)%100); //Прочитано
    sprintf(*menu++ +14,"%dKb",textend>>10); //Размер файла
    if((j=textmax-textend)<1024) sprintf(*menu++ +15,"%d",j);
    else sprintf(*menu++ +15,"%dKb",j>>10);
    sprintf(*menu++ +15,"%dKb",GetFreeRamAvail()>>10);
    sprintf(*menu++ +15,"%dKb",GetFreeFlexSpace(*s-'0',&err)>>10);
    sprintf(*menu++ +14,"%dKb",GetTotalFlexSpace(*s-'0',&err)>>10);
  }
  cls();
  menu=menus[menunum-1];
  while((s=(byte*)*menu++)){
    x=24;
    y+=10*width;
    if(y+8*width>screensize) break;
    while(*s){
      ssym=sym2[*s];
      if(ssym==0)  x+=fontdef[ssym];
      else
      for(j=0;j<fontdef[ssym];j++){
        b=*(symptr2[ssym]+j);
        ++x;
        xy=x+y;
        for(k=0;k<7;k++,xy-=width){
          if(b&1) screen[xy]=t.color; 
          b>>=1;
        }
      }
      ++s;
     }//while
   }//while
   menucursor();
  }
}

#define symshow \
      for(j=0;j<font[ssym];j++){\
        b=*(symptr[ssym]+j);\
        x+=rot?hei:1;\
        xy=x+y;\
        for(k=0;k<FONSIZEYY;k++,xy-=rot?-1:wid){\
          screen[xy]=(b&1)?t.color:t.bkcolor; \
            b>>=1;}}\

void viewshow(){ // Отобразить страницу текста
  getPG(PG);
  int rot=t.f&frotate, edit=t.f&(fedit|fxconst);
  int i,j,k, y=rot?(hei+hei-1):0, x,xy, pos, npos, dx=0, dy=(FONSIZEY+t.ysize)*wid;
  int b,ssym,nfirst=0;
  cls();
  for(i=0;i<MAXY;i++){
	pos=PG[i]-1;
	npos=PG[i+1];
	x=1;
   if(rot){ if((y-=(FONSIZEY+t.ysize))<0) return;
   }else if((y+=dy)>=screensize) return;//
    while(++pos<textend && pos<npos){
      if(nfirst && pos>0 && !sym[text[pos]] && !sym[text[pos-1]]) continue;
      nfirst=1;
      ssym=sym[text[pos]];
      if(ssym==0){
        x+=((edit)?FONSIZEX:font[ssym])*(rot?hei:1);
      }else{
      if(edit) x+=((dx=FONSIZEX-font[ssym])>>1)*(rot?hei:1);
      symshow
      if(edit) x+=((dx>>1)+(dx&1))*(rot?hei:1);
     }
    }
    if(PGper[i]){
      ssym='-'-0x20;
      symshow
    }
  }if(rot && (t.f&frotate2)) rotate();  
}

void hexshow(){
  int i,j, pos=t.pos, x,xx;
  char ss[100], *s;
  cls();
  sprintf(ss,"%X",pos);
  s=ss+strlen(ss);
  *--s='0'; *--s='0';
  for(i=0;i<strlen(ss);i++) hexyi(i,1,sym[ss[i]]);
  for(j=2;j<=MAXY && pos<textend;j++){
    sprintf(s=ss,"%02X",pos);
    while(*++s);
    hexyi(0,j,sym[s[-2]]);
    hexyi(1,j,sym[s[-1]]);
    for(i=0, x=2, xx=3+(MAXHEX<<1); i<MAXHEX && pos<textend; i++){
      hexyi(++xx,j,sym[text[pos]]);
      sprintf(s=ss,"%02X",text[pos]);
      hexyi(++x,j,sym[*s]); hexyi(++x,j,sym[s[1]]);
     // ++x;
      ++pos;
    }
  }if((t.f&frotate) && (t.f&frotate2)) rotate();  
}

#define symshow2 \
      xx=x; bb=font+256+ssym*FONSIZEY;\
      for(j=0;j<FONSIZEY;j++){\
        b=*bb++;\
        xx+=(rot?-1:wid);\
        xy=xx+y;\
        for(k=0;k<FONSIZEX;k++,xy+=(rot?hei:1)){\
          screen[xy]=(b&0x80)?t.color:t.bkcolor; \
          b<<=1;\
        }\
       }\


void hexyi(int x, int yy, byte ssym){
  int rot=t.f&frotate;
  int b,j,k, xy,y,dy,xx;
  byte *bb;
  if(t.font<5){
   y=rot?(hei+hei-1):0;
   dy=(FONSIZEY+t.ysize)*wid;
   if(rot){ if((y-=(FONSIZEY+t.ysize)*yy)<0) return;
   }else if((y+=dy*yy)>=screensize) return;//
   x=FONSIZEX*x*(rot?hei:1);
   symshow
  }else{
    dy=(FONSIZEY+t.ysize)*wid;
    y=(rot?(hei+hei+FONSIZEY+t.ysize-1):-dy);
    if(rot){ if((y-=(FONSIZEY+t.ysize)*yy)<FONSIZEY+t.ysize) return;
    }else if((y+=dy*yy)>=screensize-dy) return;//
    x=FONSIZEX*(x)*(rot?hei:1);
    symshow2
  }
}

void ramka(int size){
  int i,j;
  char *s;
  size=(size+1)*FONSIZEX;
  if(t.f&frotate){
    s=screen;
    i=hei-(FONSIZEY+t.ysize)*(MAXY-1);
    for(j=0;j<size;j++,s+=hei){
      memset(s,t.bkcolor,i); s[i+1]=t.color;
    }
    memset(s,t.color,i+1);
  }else{
    s=screen+(MAXY-1)*(FONSIZEY+t.ysize)*wid;
    memset(s,t.color,size);
    s+=wid;
    for(j=0;j<FONSIZEY+t.ysize;j++,s+=wid){
      memset(s,t.bkcolor,size);
      s[size]=t.color;
    }
    if(s<=screen+screensize-wid) memset(s,t.color,size); 
  }
}

void curinv(byte *s, int size){
  while(--size>=0){
    *s=(*s==t.bkcolor)?t.color:t.bkcolor;
    ++s;
  }
}

void keycursor(int xpos){
  int i,j;
  char *s;
  if(t.f&frotate){
    i=hei-(FONSIZEY+t.ysize)*(MAXY-1);
    s=screen+FONSIZEX*xpos*hei+i-FONSIZEY-t.ysize-2;
    for(j=0;j<FONSIZEX;j++,s+=hei){
      curinv((byte*)s,FONSIZEY+t.ysize);
    }
  }else{
    s=screen+(MAXY-1)*(FONSIZEY+t.ysize)*wid + xpos*FONSIZEX+wid;
    for(j=0;j<FONSIZEY+t.ysize;j++,s+=wid){
      curinv((byte*)s,FONSIZEX);
    }
  }
}

void viewshow2(){ // Отобразить страницу текста большого шрифта!
  getPG(PG);
  int rot=t.f&frotate;
  int i,j,k, dy=(FONSIZEY+t.ysize)*wid, y=(rot?(hei+hei+FONSIZEY+t.ysize-1):-dy), x,xy, xx, pos, npos;//, dx=0;
  int b,ssym,nfirst=0;
  byte *bb;
  cls();
  for(i=0;i<MAXY;i++){
    pos=PG[i]-1;
    npos=PG[i+1];
    x=1;
    if(rot){ if((y-=(FONSIZEY+t.ysize))<FONSIZEY+t.ysize) return;
    }else if((y+=dy)>=screensize-dy) return;//
    while(++pos<textend && pos<npos){
      if(nfirst && pos>0 && !sym[text[pos]] && !sym[text[pos-1]]) continue;
      nfirst=1;
      ssym=sym[text[pos]];
      if(ssym!=0){
       symshow2
      }
       x+=FONSIZEX*(rot?hei:1);
    }
    if(PGper[i]){
      ssym='-';
      symshow2
    }
  }if(rot && (t.f&frotate2)) rotate();  
}

typedef long Elf(char*, void*, void*, void*);

int rundll2(char *exename, void *p1, void *p2, void *p3){
    int f, l, size, msize, exoff;
    unsigned int err;
    char *mem;
    long *tab;
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
    if((l=lseek(f,0,2,&err,&err))<16) return 0;
    lseek(f,l-4,0,&err,&err);
    fread(f,&size,4,&err);
    lseek(f,0,0,&err,&err);
    msize=(size>l)?size:l;
    //if(size<l-4) return 0;
    if(!(mem=(char*)malloc(msize))) return 0;
    zeromem(mem,msize);
    fread(f,mem,msize,&err);
    fclose(f,&err);
    tab=(long*)(mem+l);
    *--tab=0;
    exoff=*--tab;
    *tab=0;
    while(*--tab);
    while(*++tab){
      *(long*)(mem+*tab)+=(long)mem;
      *tab=0;
    }
    l=((Elf*)(mem+exoff))(p1,p2,p3,0);
    mfree(mem);
  return l;
}

int onstart(char *exename, char *fname){
  if(fname[1]==':' && strrchr(fname,'.')){
    strcpy(dllname,exename);
    strcpy(strrchr(dllname,'\\')+1,strrchr(fname,'.')+1);
    strcat(dllname,extdll);
    //ShowMSG(1,(int)dllname);
  }
  strcpy(filename,exename);
  file=strrchr(filename,'.');
//  file=filename+strlen(filename);
//  while(file>filename && *--file!='.');
  if(loadini(fname)) return 1;
  loadfont();
  correct();
  menualloc();
  return 0; 
}

//////////
void movedown(){
  if((p=PG[1])!=0 && p<textend) t.pos=p;
}

void cachepush(int pos){
  if(cachend>=cachemax) cachend=0;
  cache[cachend++]=pos;
  if(cachend==cachest) 
    if(++cachest>=cachemax) cachest=0;
}

int cachepop(){
  if(cachend==cachest) return -1; //no cache
  if(!cachend) cachend=cachemax;
  return cache[--cachend];
}

void movepgdown(){
  if((p=PG[MAXY]) && p<textend){ cachepush(t.pos); t.pos=p;}
}

void moveup(){
  t.pos-=2;
  while(--t.pos>0 && text[t.pos]!=0xd);
  if(t.pos<=0){ t.pos=0; return;}
  t.pos+=2;
  getPG(PGEX);
  for(p=1;p<=MAXY;p++)
    if(PGEX[p]==PG[0]){ t.pos=PGEX[p-1]; return;}
}

void movepgup(){
  int i;
  if((i=cachepop())<0){
    if((t.pos-=MAXX*MAXY)<0) t.pos=0;
  }else t.pos=i;
//  int i, p, curpos, *pgg=PG;
//  if((curpos=pgg[0])==0) return;
//  for(i=0;i<MAXY;i++){
//    t.pos-=2;
//    while(--t.pos>0 && text[t.pos]!=0xd);
//  }
//  if(t.pos<0) t.pos=0;
//  do{
//    getPG(pgg);
//    for(p=1;p<=MAXY;p++)
//      if(pgg[p]==curpos){
//        if(t.pos==0) return;
//        pgg=(pgg==PG)?PGEX:PG;
//        t.pos=pgg[p]; return;
//      }
//    if(!((p=pgg[MAXY])!=0 && p<textend)) return;
//    t.pos=p;
//    pgg=(pgg==PG)?PGEX:PG;
//  }while(true);
}


int getcurpos(){	// Получ. позицию курсора в тексте
  return PG[t.cury]+t.curx;
}

void curright(){
  if(PG[t.cury]+(++t.curx)>=PG[t.cury+1]){
    if(t.cury<MAXY-1){ ++t.cury; cursoronly=true;}
    else movedown();
    t.curx=0;
    //else --text.curx;
  }else cursoronly=true;
}

void curleft(){
  if(--t.curx<0){
    if(t.cury>0){ --t.cury; cursoronly=true;}
    else{ moveup(); getPG(PG);}
    t.curx=PG[t.cury+1]-PG[t.cury]-1;
  }else cursoronly=true;
}

void curdown(){
  if(lastkey==UP_BUTTON || lastkey==DOWN_BUTTON) t.curx=t.curxx;
  else t.curxx=t.curx;
  if(t.cury<MAXY-1){ ++t.cury; cursoronly=true;}
  else{ movedown(); getPG(PG);}
  if(t.curx>=(p=PG[t.cury+1]-PG[t.cury]))
    t.curx=p-1;
}

void curup(){
  if(lastkey==UP_BUTTON || lastkey==DOWN_BUTTON) t.curx=t.curxx;
  else t.curxx=t.curx;
  if(t.cury>0){ --t.cury; cursoronly=true;}
  else { moveup(); getPG(PG);}
  if(t.curx>=(p=PG[t.cury+1]-PG[t.cury]))
    t.curx=p-1;
}

void hexcurright(){
  if(++t.curx<MAXHEX) cursoronly=true;
  else{
    if(t.cury<MAXY-2){ ++t.cury; cursoronly=true;}
    else{ hexdown(); t.cury=0;}
    t.curx=0;
  }
}

void hexcurleft(){
  if(--t.curx<0){
    if(t.cury>0){ --t.cury; cursoronly=true;}
    else{ hexup(); t.cury=MAXY-2;}
    t.curx=MAXHEX-1;
  }else cursoronly=true;
}

void hexcurdown(){
  if(t.cury<MAXY-2){ ++t.cury; cursoronly=true;}
  else{ hexdown(); t.cury=0;}
}

void hexcurup(){
  if(t.cury>0){ --t.cury; cursoronly=true;}
  else { hexup(); t.cury=MAXY-2;}
}

void insert(byte sym, int pos){	// Вставить в поз. курсора символ
  if(pos<textend && textend<textmax){
  flags|=fmodify;
  memmov(text+pos+1,text+pos,++textend-pos);
  text[pos]=sym;
  }
}

void enter(){
  insert((byte)0xd,p=getcurpos()); 
  insert((byte)0xa,++p);
  if(t.cury<MAXY-1){ ++t.cury; t.curx=0;}
}    

void insertbytes(byte *b, int from, int cnt, int pos){	// Вставить в поз. курсора символы
  if(textend+cnt<textmax){
  flags|=fmodify;
  memmov(text+pos+cnt,text+pos,textend-pos);
  memmov(text+pos,b+from,cnt);
  textend+=cnt;
  while(--cnt>=0)
    curright();
  cursoronly=false;
}}

void delete(int pos){	// Удалить символ в поз.курсора
  if(textend>0 && pos<textend){
  flags|=fmodify;
  memcpy(text+pos,text+pos+1,--textend-pos+2);
}}

void correct0xd(){	//уд./доб. лишние 0xd 0xa (после ред-я)
  for(int pos=0;pos<textend;pos++)
    switch(text[pos]){
      case 0xd: if(text[++pos]!=0xa) insert((byte)0xa,pos); break;
      case 0xa: delete(pos); --pos; break;
      case 0: return;
    }
}

void deltab(){
  for(p=0;p<textend;p++)
    if(text[p]==9) text[p]=0x20;
}

/*
int loadmenu(int p){	// Загрузить меню в bufptr, указатели в scrptr
  int ptr=scrptr, pos=loadbuf(p);			// ptr-1 возвр-т число записей
  do{
    scr[++scrptr]=pos;
    while(buf[pos]!=0 && buf[pos]!=0xd) ++pos;
    if(buf[pos]==0) break;
    buf[pos]=0;
    pos+=2;
  }while(true);
  if(buf[pos-2]==0) --scrptr;
  scr[++scrptr]=0;
  scr[ptr]=scrptr-ptr;
  ++scrptr;
  return ptr+1;
}

// БЛ.! Как меня достали эти эльфы!!!
// и  их еб..е пикоффы
// не могли сделать без выравнивания на слова как в нормальном х86!!!!
// пусть бы скорость падала - пофигу...
// Ни отладчика ничего нету... МАРАЗМ!!!!
// Написание эльфов - занятие для мазохистов.

int loadbuf(int ptr){	// Загрузить файл в bufptr
  int pos;
  char *name=new String(buf,ptr,vm.strlen(buf,ptr));
//new File().debugWrite("0:/Debug1", "\n"+new String(buf,ptr,strlen(buf,ptr)+5));//////
  io.is = getClass().getResourceAsStream(name);
  if(io.is==null) throw new IOException("Error open: " + name);
  pos=io.is.read(buf,bufptr,io.is.available());
  io.is.close();
  if(pos==0) throw new IOException ("Null data: "+name);
  buf[bufptr+pos++]=0;
  bufptr+=pos;
  return bufptr-pos;
}

//////////

int getlastpos(int pos){ // Получить последний символ в строке
  byte b;
  int i, x=(btab)?tab:0, sym, prevsym=0, startpos=pos, endpos, cntspaces=0;
  --pos;  
  while(x<height && ++pos<textend-1){
    if(!fdelcr){
       if(text[pos]==0xd){ bnextab=true; ++pos;  break;}
    }else 
      if(text[pos]==0xd && pos<textend-3 && text[pos+2]==0xd){
       // do pos+=2; while(text[pos]==0xd && pos+2<textend && text[pos+2]==0xd);
        bnextab=true; ++pos; break;
      }
    if(ftab && text[pos]==0x2e && pos>1 && pos<textend-2 && getsym[text[pos-2]&0xff]!=0 && text[pos-2]!=0x2e &&(text[pos-1]<0x30 || text[pos-1]>0x39) && (text[pos+1]==0x20 || text[pos+1]==0xd)){ bnextab=true; ++pos; x+=fon[0xe]; break;}
    if((sym=getsym[text[pos]&0xff]&0xff)!=0) bissym=true;
    if(!(sym==0 && prevsym==0)){  x+=fon[sym]; if(sym==0) ++cntspaces; }
    prevsym=sym;
 //   ++pos;
  }
  if(pos>textend-1) pos=textend-1;
  if(bnextab) if(x<height) return pos; else bnextab=false;
  //if(pos>=textend-1) return textend-1;//pos;//
  endpos=pos;
  ++pos;
  if(fshirina && getsym[text[endpos]&0xff]==0) --cntspaces;
  while(--pos>startpos && (sym=getsym[text[pos]&0xff]&0xff)!=0) x-=fon[sym];
  if(pos<=startpos){
    pos=startpos;
    //if(!fperenos) 
    return endpos;//
  }
  if(!fperenos){
    if(fshirina && cntspaces>0) spaces=(height-x)/(cntspaces*fon[0]);
    return pos;
  } //perenos
  startpos=pos;
  pos=endpos;
  bperenos=false;
 // if(endpos<textend-1 && text[endpos+1]==0x20) return endpos;//error
  while(startpos>0 && sign[getsym[text[startpos]&0xff]&0xff]<2) --startpos;
  ++startpos;
  if(endpos-startpos<2) return startpos;
  --endpos;
  while(--endpos>startpos){
    if((b=sign[getsym[text[endpos]&0xff]&0xff])==1){ bperenos=true; break;}
    else if(b==0 && sign[getsym[text[endpos+1]&0xff]&0xff]==0)
        { bperenos=true; break;}
  }
  if(bperenos) return endpos+1;
  return startpos;
}


void bookscreen(int pos){	// Нарисовать буквы в массиве screen с поз.pos, задать textnextpos и textcachepos
  if(lastcodepage!=codepage) prepgetsym(codepage);
  int b, prevsym, lastpos, i,j, xxy, tmpspaces, fonsizeyy=(fonsizey>8)?8:fonsizey;
  int sym,fonsym,cutline=0,xy=width+width+fondeltay;
  for(i=0;i<screenlength;i++) screen[i]=bkcolor; // Залить фон
  if(pos<0) pos=0; else
  if(pos>=textend){ 
    textnextpos=pos=textcachepos=textend; textout(0,0,eof,0,0,0);
  }else{
  //if(pos < textstart || pos > textstart+textbufsize-textrezerv) readcache(pos-textrezerv);
  textcachepos=pos;
  //pos-=textstart;//////!!
  btab=bnextab=ballspace=false;
  while((xxy=(xy-=(fonsizey+fondeltay)))>=width-1){
    if(xy==width-1) cutline=1;
    spaces=prevsym=0;
    btab=bnextab;
    //textend-=2;////////
    do{
      bperenos=bnextab=bissym=false;
      lastpos=getlastpos(pos); /////
      if(!bissym && ballspace) pos=lastpos+1;
      else break;
    }while(lastpos<textend-1);
    //textend+=2;///////
    ballspace=!bissym;
    if(btab) xy+=tab*width;
    while(pos<lastpos && pos<textend){ 
      sym=getsym[text[pos]&0xff]&0xff;
      if(!(sym==0 && prevsym==0)){
       tmpspaces=spaces;
       do{
        //drawsym();
      if(xy+width*((fonsym=fon[sym])-1)<screenlength){
        for(j=0;j<fonsym;j++){
         b=(fon[fonidx[sym]+j])>>cutline;
         for(i=cutline;i<fonsizeyy;i++){
           if((b&1)!=0) screen[xy+i]=foncolor;
           b>>=1;
         } xy+=width;}
        }
        //end drawsym()
       }while(sym==0 && tmpspaces-->0);
      }
      prevsym=sym;
      ++pos;
    }
    if(bperenos && (xy+width*(fon[sym=0xd]-1))<screenlength){
       //sym=0xd;
       for(j=0;j<fon[sym];j++){
         b=(fon[fonidx[sym]+j])>>cutline;
         for(i=cutline;i<fonsizeyy;i++){
           if((b&1)!=0) screen[xy+i]=foncolor;
           b>>=1;
         }xy+=width;}
    }
    //btab=bnextab; bnextab=false;
    if(pos>=textend-1) break;
    xy=xxy;
  }
    textnextpos=pos;//+textstart;
    //if(textnextpos > textstart+textbufsize-textrezerv) readcache(textnextpos-textrezerv);
  }
  if(frotate) rotate();
  //if(textnextpos>textend-1) textnextpos=textend-1;
  image=Image.createRGBImage( screen, width, height, false); 
}
*/

void onclose(){
 // mode=100;
//  debsave();//!!!!!!!!
  GBS_DelTimer(&timer);
  GBS_DelTimer(&lighttimer);
  GBS_DelTimer(&mintimer);
  savetext();
  saveini();
//  terminate=true;
//  while(isexecute);//??? 
//  saveini();
}

void onredraw(){ ////////////////////////////!!!!! curonly not work!!!
  if(menunum) menushow();
  else{
  if((t.f&fedit) && cursoronly){ cursoronly=false; cursor(curoldx,curoldy); }
  else{
    if(t.f&fhex) hexshow();
      else if(t.font<5) viewshow(); 
         else viewshow2();
  }
  if(t.f&fedit) cursor(t.curx, t.cury);
  }
}

void hexdown(){
  int i=(MAXY-1)*MAXHEX;
  if((t.pos+i)<textend) t.pos+=i;
}

void hexup(){
  int i=(MAXY-1)*MAXHEX;
  if((t.pos-=i)<0) t.pos=0;
}

