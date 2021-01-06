
// AVP - антивирус
// Ищет и лечит эльфы вирусы v4 и v5
// взято с http://cbn.narod.ru  (c)bn

//#define NEWSGOLD //это Должно быть для любых телефонов
#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "font.h" // Шрифт

char *Title="AVP 0.4 (c)bn";

char curdir[128], *file;
typedef unsigned char byte;
extern int width, height;
extern char *screen; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void pr(); // Вывести строку prstr на консоль
char *prstr=0;

extern unsigned char SGOLD2;

const char *errors[]={
  0,"error"
};

// что-то лишнее из Command.elf (может и не использоваться)
volatile int running=0; // Флаг активности
int mode=0;
int f;
byte sym[256]; // стр. симв.
#define maxargv 32
int argc;
char *argv[maxargv];
void  cr();

#define maxlog 256
char blog[maxlog], *log=blog;

void onredraw(){ // Перерисовка экрана screen[132*176]
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    return 1;
  }
  return 0;
}


void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
//  GBS_DelTimer(&timer); //(у меня pickoff)???
}

void onexit(){ // Выход
}

void setcodepage(int page){ // Подг. табл. перекод. симв. (если измен.кодир,все большие)
  int i, A,P,a,p;
  memset(sym,0,0x100);
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
}

void parse(char *cmdlind){ // Получить argc, argv
  argc=0;
}

int exec(char *cmd){  // Выполнить команду
  //parse(cmd+??);
  return 0;
}

///////// Функции //////
int xx=0; //коорд.курсора

int cls(){
  memset(screen,0,screensize);
  xx=0;
//  pr("");
  return 0;
}

void cr(){  // Скроллинг текста вверх
  memcpy(screen, screen+width*10, width*160);
  memset(screen+width*160,0,width*16);
  xx=0;
}

void pr(){ // Вывести строку prstr на консоль
  int i,j,b,x;
  unsigned char *p;
  char *scr=screen+width*160;
  --prstr;
  x=xx;
  while(*++prstr){
    if(*prstr=='\\')
      switch(prstr[1]){
      case 'i': prstr+=2; return;
      case 'n': prstr+=2; cr(); break;
     }
    p=font+(sym[*(unsigned char*)prstr]<<3);
    x=xx;
    for(j=0;j<8;j++){
      b=*p++;
      for(i=0;i<8;i++,x++){
        if(b&0x80) scr[x]=0xff;
        b<<=1;
      }
      x+=width-8;
    }
    if((xx+=6)>=width-6){
      cr();
      xx=0;
    }
  }
}

inline print(char *s){
  prstr=s; pr();
}


int (*cmdfunc[10])(void)={0,cls};

int tmpstart(){
  int rez=0;
  if(cmdfunc[1])
    rez=cmdfunc[1]();
  return rez;
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(curdir,exename);
  file=strrchr(curdir,'\\')+1;
  setcodepage(1);
  return 0;
}


#define bodysize 4096 //размер вирусов v4,5
#define body7size 4196 //размер вируса v7
#define body3size 2176 //размер вируса v3
//#define body6size 2176 //размер вируса v6


char temp[128], path[128], tmp[128];
const char zbin[]="4:\\ZBin";
int viruses=0, allfiles=0;

void outlog(char *tm){
  while(*tm && log<blog+maxlog-2) *log++=*tm++;
  ++viruses;
}

void un(){ // Заражение (Тьфу! т.е. Лечение файла temp)
  int f, memsize, off=bodysize;
  char *mem, isvir=0;
if((f=fopen(temp,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
  ++allfiles;
  memsize=lseek(f,0,2,&err,&err);
  if(memsize==body3size){ //вероятно v3
    fclose(f,&err);
    unlink(temp,&err); //удалить
    strcpy(tmp,temp);
    strcpy(strrchr(tmp,'.'),".bin");
    fmove(tmp,temp,&err);
    outlog(temp);
    return;
  }
  if(memsize>4200){
    if(!(mem=(char*)malloc(memsize))){ print(" ERROR"); fclose(f,&err); return;}
    lseek(f,0,0,&err,&err);
    if(fread(f,mem,memsize,&err)==memsize){
      if(*(long*)(mem+off)==0x7f454c46){//elf   //mem[off]==0x7f && mem[off+1]==0x45 && mem[off+2]==0x4c){
        while(((off+=bodysize)<memsize-4) && *(long*)(mem+off)==0x7f454c46);// mem[off]==0x7f && mem[off+1]==0x45 && mem[off+2]==0x4c);
        off-=bodysize;
        isvir=1;
      }else{
        off=body7size;
        if(*(long*)(mem+off+4)==0x10101){ //virus2 detected!
          *(long*)(mem+off)=0x7f454c46; //дописать заголовок elf
          isvir=1;
        }
      }
      if(isvir){
      outlog(temp);
      fclose(f,&err);
      if((f=fopen(temp,A_WriteOnly+A_BIN+A_Truncate,P_WRITE,&err))>0){
        fwrite(f,mem+off,memsize-off,&err);
      }
     }
    }
    mfree(mem);
  }
  if(f>0) fclose(f,&err);
  }
}

void unvir(char *dir){ // Найти все эльфы в dir (использ.temp)
  //Код взят из вируса и раньше использ. чтобы их ЗАРАЗИТЬ
  static DIR_ENTRY dee;
  char *ptr;
  strcpy(temp,dir);
  ptr=temp+strlen(temp)+1;
  strcat(temp,"\\ .elf");  
  *ptr='*';
  if (FindFirstFile(&dee,temp,&err)){
    do{
      strcpy(ptr,SGOLD2?dee.file_name:((char*)&dee+169));
      un();
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
}


void find(char *dir){ // Найти все пути в dir (использ.path)
  static DIR_ENTRY de;
  char *ptr;
  strcpy(path,dir);
  unvir(path);
  ptr=path+strlen(path)+1;
  strcat(path,"\\*.*");  
  if (FindFirstFile(&de,path,&err)){
    do{
      strcpy(ptr,SGOLD2?de.file_name:((char*)&de+169));
      if(isdir(path,&err) && ((*(int*)(path+8))|0x20202020)!=0x6d656164) // Не заражать в папке Daem-ons
        unvir(path);
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}


void avp(){
  find((char*)zbin);
  *(char*)zbin='0';
  find((char*)zbin);
}

void oncreate(){ // Создание окна
  cls();
  print("AVP 0.4 (c)bn. Лечит вирусы v3-7");
  avp();
  char *s=blog;
  if(log!=blog){ 
    print(" ВИРУСЫ");
    do{
      cr();
      print(s);
      while(++s<log-1 && *s);
      if(s>=log-1) break;
      print(++s);
    }while(1);
  }
  cr();
  sprintf(temp,"ПРОВЕРЕНО эльфов: %d",allfiles);
  print(temp);
  cr();
  sprintf(temp,"Вылечено вирусов: %d",viruses);
  print(temp);
  if(viruses)
    print("  ВНИМАНИЕ! ВИРУСЫ!");
  REDRAW();
}
