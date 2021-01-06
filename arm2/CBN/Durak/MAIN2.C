
// Durak

#include "..\swilib.h"
#include "..\random.h"

extern short *screen; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
typedef unsigned char byte;
extern int width, height, screensize;
extern unsigned char SGOLD2, C65, S75, EL71;

char *Title="Durak 0.11 (c)bn";

enum{ msgloss=1, msgvictory, msgkozir};
#define forg for(i=0;i<strlen(girl);i++)

const char *errors[]={
  0,
  "Mess.bmp не найден!\0",
  "Cards.bmp не найден!\0",
  "Font.bmp шрифт не найден!\0",
//  "Мало памяти для буфера\0",
  "unknown error"
};

//размеры карт
#define cardx 19
#define cardy 27

char filename[128], *ext;
char *mess=0, *bmpcards=0, *fon=0, *font=0; //free
char *msg[128];
int maxmsg;

#define maxcards 37
char coloda[maxcards], player[maxcards], girl[maxcards], current[maxcards]; // Карты... выложены
char tmp1[maxcards], tmp2[maxcards];
byte fastfon=0, kozir=0; //козырь

const char girlbmp[]="Girl00.bmp";

int mode=0;
char level=0;
int curx=0;
int showmsg=0;

inline void centerbmp(char *bmp){
  if(bmp){
  int x=(width-*(short*)bmp)>>1, y=(height-*(short*)(bmp+2))>>1;
    bitblt(screen, bmp, x<0?0:x, y<0?0:y, 0,0,0,0,0,0);
  }
}

inline void cls(){ memsetd(screen,0,screensize>>2);}

inline void showfon(){ 
  if(fastfon) memcpy(screen,fon+4,screensize);
  else{
    cls();
    centerbmp(fon);
  }
//  showstart();
}

void drawcard(int x, int y, int card){ // нарисовать карту. 0=рубашка
  if(card){
    card=((card-6)&0xf)+(card>>4)*9;
  }else card=36;
  bitblt(screen,bmpcards, x,y, cardx,cardy, (card%6)*cardx, (card/6)*cardy, 0,0);
}

void showcards(char *who, int y, int deltax){
  int i,len,x=0, dx;
  if(len=strlen(who)){
    dx=width/(len+deltax);
    for(i=0;i<len;i++){
      drawcard(x,y,y?who[i]:0);
      x+=dx;
    }
  }
}

inline void showcursor(){
  int len=strlen(player);
  if(curx>=len) curx=0;
  if(len){
    bitblt(screen,bmpcards, width/len*curx,height-cardy, cardx,cardy, (38%6)*cardx, (38/6)*cardy, 0,0x40);
  }
}

inline void showcurrent(){
  char *s=current, *s1=tmp1, *s2=tmp2;
  while(*s){
    *s1++=*s++;
    if(*s) *s2++=*s++;
  }
  *s1=*s2=0;
  showcards(tmp1,(height>>1)-cardy-8,0);
  showcards(tmp2,height>>1,strlen(tmp1)-strlen(tmp2));
//  showcards(current,(height-cardy)>>1);
}

void onredraw(){ // Перерисовка экрана screen[132*176]
  showfon();
  showcards(girl,0,0);
  showcurrent();
  showcards(player,height-cardy,0);
  showcursor();
  if(showmsg){/////////вывести сообщение
    showmsg=0;
  }
}

void delcard(char *who, int pos){ //удалить карту
  who[pos]=who[strlen(who)-1];
  who[strlen(who)-1]=0;
}

int getcard(char *who){ // получить карту. return 0=no card
  int rnd;
  if(!*coloda) return 0;
  rnd=random(strlen(coloda));
  who[strlen(who)]=coloda[rnd];
  delcard(coloda,rnd);
//  coloda[rnd]=coloda[strlen(coloda)-1];
//  coloda[strlen(coloda)-1]=0;
  return 1;
}


int putcard(char card){ // выложить карту. return 0=низя
  char *cur=current+strlen(current)-1;
  char last=*cur;
  int i;
  if(strlen(current)&1){//защищаемся
    if((card>>4)==kozir && (last>>4)!=kozir); //можно
    else{
      if((card>>4)==(last>>4) && (card&0xf)>(last&0xf));//можно
      else return 0; //низя
    }
  }else{ //атакуем
    if(strlen(current)){
      for(i=0;i<strlen(current);i++)
        if((current[i]&0xf)==(card&0xf)) goto ata;
      return 0;
    }
  }
ata:  
  *++cur=card;
  *++cur=0;
  return 1;
}

inline void pickall(char *who){ //взять все карты
  strcat(who,current);
  *current=0;
}

void pickup(){ //взять из колоды до 6 карт
  while(strlen(player)<6)
    if(!getcard(player)) break;
  while(strlen(girl)<6)
    if(!getcard(girl)) break;
}

int findmin(char card){ //найти мин карту данной масти -1=нет
  int pos=-1, i;
  forg{
    if((girl[i]>>4)==(card>>4) && girl[i]>card)
      if(pos<0) pos=i;
      else if(girl[i]<girl[pos]) pos=i;
  }
  return i;
}

char pair[9];//сколько пар
void findpair(int koz){ //найти пары для атаки, koz - козырной поиск
  int i;
  memset(pair,0,9);
  forg{
    if(koz || (girl[i]>>4)!=kozir)
      ++pair[(girl[i]&0xf)-6];
  }
}

void AIdefence(){ //защищаемся
  int i;
  int cnt=strlen(current);
  char cur=current[cnt-1];
  if((cur>>4)==kozir){ //если козырь
    if(cnt<4 && strlen(coloda)>6){ //если начало с козыря и много в колоде - берем
lget:      pickall(girl);  pickup(); return; 
    } 
    goto lkoz;
  }else{ //не козырь
    if((i=findmin(cur))<0){ //есть нет такой масти
lkoz:
      if((i=findmin((kozir<<4)+5))<0) goto lget; //если нет козырей берем
      if(strlen(coloda)<7 || cnt>8) ; //если мало осталось или много карт то ложим любой
      else{
        if((girl[i]&0xf)>9) goto lget; //жалко   rnd()
      }
    }
  }
  putcard(girl[i]);
  delcard(girl,i);
}

void AIatack(){ //атакуем
  int i,k,flag=0;
lll:  
  findpair(flag); //ищем некозырные пары
  for(k=0;k<6;k++)
    if(pair[k]>1) break;
  if(k>=6){ //нет пар - берем минимальную некозырную карту
    for(k=0;k<9;k++)
      if(pair[k]>0) break;
    if(k>=9){ //все козыри - ходим с минимального
      if(flag) return;/////error randcard here!!!
      flag=1;
      goto lll;
    }
  }
  forg{
    if(((flag || girl[i]>>4)!=kozir) && (girl[i]&0xf)==k+6) break;
  }
  putcard(girl[i]);
  delcard(girl,i);
}

void newgame(){
  int i,j;
  //заполнить колоду
  char *s=coloda;
  for(j=0;j<4;j++)
    for(i=0;i<9;i++) *s++=(i+6)+(j<<4);
  *s=*current=0; 
  curx=0;
  kozir=random(4);
  //раздать карты
  memset(player,0,37);
  memset(girl,0,37);
  for(i=0;i<6;i++){ 
    getcard(player); 
    getcard(girl);
  }
  //картинка
  *(char*)(girlbmp+5)=level+'0';
  strcpy(ext,girlbmp);
  if(fon) mfree(fon);
  if((fon=loadgraph(filename)) && *(short*)fon==width && *(short*)(fon+2)==height) fastfon=1;
}

void ai(){ //искусственный интеллект
  if(strlen(current)&1) AIdefence(); 
  else AIatack(); 
  if(!strlen(player) || !strlen(girl)) newgame(); //НЕВЕРНО!!! нужны еще проверки.. добавление колоды и т.п.
  //levelup
}


// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    //if(mode)//????
    switch(keycode){ // Код клавиши
    case RED_BUTTON: return 1; // Выход
    case LEFT_SOFT: case GREEN_BUTTON: newgame(); break;
  
    case LEFT_BUTTON: 
      if(curx>0) --curx; else curx=strlen(player)-1; break;
    case RIGHT_BUTTON: 
      if(curx<strlen(player)-1) ++curx; else curx=0; break;
      
    case UP_BUTTON: case DOWN_BUTTON: //взять карты
      pickall(player); ai(); break;

    case RIGHT_SOFT: case ENTER_BUTTON: // выложить
      if(putcard(player[curx])){
        delcard(player,curx);
        ai();
        break;
      }else return 0;
    default: return 0;
    }
//    onredraw(); DrawScreen(); // Перерисовать экран
    REDRAW();
  }
  return 0;
}


void onclose(){ // Закрытие окна
}

void onexit(){ // Выход
  if(mess) mfree(mess); // Освобождаем память
  if(bmpcards) mfree(bmpcards);
  if(fon) mfree(fon);
  if(font) mfree(font);
}


void oncreate(){ // Создание окна
  newgame();
}


int razdel[5];  //начало каждого раздела 0=служебный, 1=...

void txt(){
   int i, raz=0;
  char *s=mess, **ptr=msg;
  //перекодировка
//  for(i=0, s=data; i<datasize; i++,s++) *s=~*s; 
  //копирование в Daemons...
//  daemcopy(exename);
 //разбивка строк
  do{
    *ptr++=s;
    while(*++s && *s!=0xd);
    if(!*s) break;
    *s=0; s+=2;
  }while(1);
  *ptr=0;
  maxmsg=ptr-msg;
  //подготовить разделы
  i=0;
  while(i<maxmsg){
    if(*msg[i]=='['){
      razdel[raz++]=i+1;
    }
    ++i;
  }
  razdel[raz]=maxmsg;
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(filename,exename);
  ext=strrchr(filename,'\\')+1;
  strcpy(ext,"mess.bmp");
  if(!(mess=loadfile(filename))) return 1;
  txt();
  strcpy(ext,"cards.bmp");
  if(!(bmpcards=loadgraph(filename))) return 2;
  strcpy(ext,"font.bmp");
  if(!(font=loadfile(filename))) return 3;
//  if(!(back=(char*)malloc(screensize))) return 4;
  randomize();
  return 0;
}
