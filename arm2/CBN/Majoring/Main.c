
// Игра Majoring

//#define HIGHCOLOR // 16-битный режим
//#define GRAPH  // Графика
#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "..\random.h" // "Случайные" числа

char *Title="Majoring 0.4 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen;//[132*176]; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void enter(); // Нажат enter
void newgame(); // Начать новую игру

const char *errors[]={
  0,
"Щелкните на .maj файл уровня\0",
"Неверный .bmp файл!\0"
"Неверный .png файл!\0",
"maj: Нельзя открыть!\0",
"maj: Не MJ файл!\0",
"maj: Фигур менее 5 или более 32\0",
"maj: Длина строки должна быть строго 14\0"
};

#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
#define tab(xx,yy) data[(yy)*maxx+(xx)]

const int curcolor=0x1f, selcolor=0xffff, bkcolor=RGB16(0,44,22);
const int colw=RGB16(11,22,11), colb=RGB16(8,16,8);

char *bmp=0, *smbmp=0;
char filename[128]; // Храним имя файла
byte data[14*18*6], back[14*18*6];   // Буфер с данными поля

#define dat(x,y,l) data[(l)*maxxy+(y)*maxx+(x)]

const int maxx=14, maxy=18, maxxy=14*18, maxlevels=6; //7x9 (*2)
int curx=0,cury=0, curl=0, selx=-1, sely=-1, sell=0;
int points=0;
int maxfig;

void drawcur2(int curx, int cury, int color){
  int i;
  short *scr=screen+(cury*9+0)*width+curx*9+0;
  memsetw(scr+=width+1,color,7);
  for(i=0;i<7;i++,scr+=width){
    scr[0]=scr[7]=color;
  }
  memsetw(scr,color,7);
}

void drawcur(int curx, int cury, int *curlev, int color){
  int i;
  for(i=maxlevels;i>0;)
    if(dat(curx,cury,--i)) break;
    //if(data[(--i)*maxxy+cury*maxx+curx]) break;
  int dx=((*curlev=i)<<1)+3;
  short *scr=screen+(cury*9+dx)*width+curx*9+dx;
  for(i=0;i<9;i++,scr+=width)
    memsetw(scr,color,9);
}


void drawtable(){ // Рисукм табличку
  memsetw(screen,bkcolor,screensize>>1);
  int i,l,x0,y0;
  byte *b;
  for(l=0;l<maxlevels;l++){
    b=data+(l+1)*maxxy;
    for(i=maxxy;i>0;--i)
      if(*--b && *b<250){
        bitblt(screen,smbmp,x0=((i%maxx)-1)*9+(l<<1),y0=i/maxx*9+(l<<1), 20,20, 0,0, 0xffff,0);
        bitblt(screen,bmp, x0+3,y0+3, 16,16, ((*b-1)&3)<<4,(*b-1)>>2<<4, 0,0);
      }
  }
}

void onredraw(){ // Перерисовка экрана screen[132*176]
  drawtable();
  if(selx>=0) drawcur(selx,sely,&sell,RGB16(31,63,0));
  drawcur(curx,cury,&curl,RGB16(31,0,0));
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
      switch(keycode){ // Код клавиши
      case RED_BUTTON: case LEFT_SOFT: return 1; // Выход
      case GREEN_BUTTON: 
        newgame(); break;
      case LEFT_BUTTON: case '4':
        if(--curx<0) curx=maxx-1; break;
      case RIGHT_BUTTON: case '6': 
        if(++curx>=maxx) curx=0; break;
      case UP_BUTTON: case '2': 
        if(--cury<0) cury=maxy-1; break;
      case DOWN_BUTTON: case '8': 
        if(++cury>=maxy) cury=0; break;
      case ENTER_BUTTON: case '5': enter(); break;
      default: return 0;
  }
  onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

inline void savegame(){ // Записать игру
  int f;
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,data,sizeof(data),&err); 
    fclose(f,&err);
}}


void onclose(){ // Закрытие окна
  savegame();  // Сохраняем результаты
}

void onexit(){ // Выход
  if(bmp) mfree(bmp);
  if(smbmp) mfree(smbmp);
}

void oncreate(){ // Создание окна
  //REDRAW();//??
}

// Файл вида: MJ всего_фишек 2б
// данные 6 уровней типа: 100010010010
// перекодируем в back
int loadmaj(){ // Загрузить конф. игры из текст. файла
  int i,j,l;
  char *ini, *s, *ss=(char*)back;
  if(!(ini=loadfile(filename))) return 4;
  if(loadfilesize<32 || *(short*)ini!=0x4a4d){ mfree(ini); return 5;} //'MJ'
  maxfig=((ini[2]-'0')*10+ini[3]-'0');
  if(maxfig<5||maxfig>32){ mfree(ini); return 6;}
  ini[loadfilesize-2]=ini[loadfilesize-1]=0;
  //копируем данные
  s=ini+5;
  for(l=0;l<maxlevels;l++){
    for(j=0;j<maxy;j++){
      for(i=0;i<maxx;i++){
        *ss++=(*++s=='1')?(byte)255:0;
        if(!*s) goto lll;
      }
      if(!*++s) goto lll;
      if(*s!=0xd){ mfree(ini); return 7;} // длина строки не 14! error!
      ++s;
    }
    while(*++s==0xd) ++s;
    if(!*s) break;
    --s;
  }
lll: mfree(ini);
  // убрать лишние 1, объединив в четверки!
  s=(char*)back;
  --s;
  for(i=0;i<sizeof(back);i++)
    if(*++s) s[1]=s[maxx]=s[maxx+1]=0;
  return 0;
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  int f,i;
  Randomize();
//  char *fname="0:\\ZBin\\maj\\1.maj";
  if(!fname || fname[1]!=':') return 1;
  memcpy(exename+(i=strlen(exename)-3),"bmp",4);
  if(!(bmp=loadgraph(exename))) return 2;
  memcpy(exename+i,"png",4);
  if(!(smbmp=loadgraph(exename))) return 3;
  //
  strcpy(filename,fname);
  if(f=loadmaj()) return f;
  memcpy(filename+strlen(filename)-3,"sav",4);
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,data,sizeof(data),&err);
    fclose(f,&err);
  }else newgame();
  return 0;
}

//////////////// Ниже специфичные maj функции /////////////////////

void newgame(){ // Начать новую игру
  int i, j, cnt, num, fig=0;
  points=0;
  memcpy(data,back,sizeof(data));
  for(i=cnt=0;i<sizeof(data);i++)
    if(data[i]) ++cnt;
  while(cnt>0){
    num=(unsigned)randint(cnt);
      //Random()%cnt;
    for(i=j=0;i<sizeof(data);i++)
      if(data[i]==(byte)255 && ++j>=num){
        data[i]=(fig>>1)+1;
        data[i+1]=data[i+maxx]=data[i+maxx+1]=254;
        break;
      }
    --cnt;
    if(++fig>=(maxfig<<1)) fig=0;
  }
}

int empty(){
  for(int i=0;i<sizeof(data);i++)
    if(data[i]) return 0;
  return 1;
}

void delcell(int x, int y, int l){
  byte *b=data+(l)*maxxy+(y)*maxx+(x);
  *b=b[1]=b[maxx]=b[maxx+1]=0;
}

int freecell(int x, int y, int l){ //1=не занят сверху
  if(++l==maxlevels) return 1;
  byte *b=data+(l)*maxxy+(y)*maxx+(x);
  if(*b||b[1]||b[maxx]||b[maxx+1]) return 0;
  return 1;
}

    
int freecell3(int x, int y, int l){ //1=не занят 1 или 2 фишками
  if(y<2 || y>maxy-3) return 1;
  if(dat(x,y,l)) return 0;
  if(x<1 || x>maxx-2) return 1;
  if(dat(x+1,y,l) && dat(x-1,y,l)) return 0;
  return 1;
}  

int freecell2(int x, int y, int l){ //1=не занят по бокам
  return freecell3(x,y-2,l)||freecell3(x,y+2,l);
}

     
void enter(){ // Нажат enter
  byte b;
  if((b=dat(curx,cury,curl)) && b<250 && freecell(curx,cury,curl) && freecell2(curx,cury,curl)){
  if(selx>=0 && !(curx==selx && cury==sely && curl==sell)
     && dat(curx,cury,curl)==dat(selx,sely,sell)){ //ок
    delcell(curx,cury,curl);
    delcell(selx,sely,sell);
    selx=sely=-1;
    if(empty()) newgame();
  }else{
     selx=curx; sely=cury; sell=curl;
  }
}}

