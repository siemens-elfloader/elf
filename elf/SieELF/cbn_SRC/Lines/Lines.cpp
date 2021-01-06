
// lines.cpp --------------------------
//        Линии 1.14 (32&16bit colors)
// win32 ----------------VISUAL C++ 6.0
// Посвящается НС - человеку золотой души
// Список игр:  1.tetris 2.cards(mame) 3.lines(HC) 4.frog(Lude)
// Планы: 5.soko 6.fleet 7.steel(Cmup) 8.ufo 9.barby(Liza) 10.doom(Pashe) 11.3dlife ...

#include <ddraw.h>
#include "linesbmp.cpp"
//#include "mylib.h"
#include <windows.h>
#include "pack.h"
#define randomize() srand(GetTickCount())		
#define random(x) (unsigned long)rand()%(x) 
const rgbmask565=0xb35203;
int width=0, height=0, pitch, bitpix, shiftpix, rgbmask;// Разрешение экрана 
int screenx=0, screeny=0, rmousexit=0, bossflag=0, altabflag=0, window=0;
int rbutx, rbuty;
int wwidth, wheight;
char *boss=NULL;
char *filesnd[]={"move.wav","cantmove.wav","destroy.wav"};

LPDIRECTDRAW lpDDraw=NULL;
LPDIRECTDRAWSURFACE lpPrimarySurface=NULL; // lpSecondarySurface=NULL;
HANDLE Mutex=NULL;
HWND hWnd;
DDSURFACEDESC ddsd;   

#define DSOUND 5 
#include <dsound.h>
LPDIRECTSOUND m_pDirectSoundObj=0; 
UINT m_currentBufferNum=0;
LPDIRECTSOUNDBUFFER m_bufferPointers[DSOUND];
DWORD m_bufferSizes[DSOUND]; 


UINT LoadSound(char *wav, long wavsize, LPWAVEFORMATEX pWaveFormat=0){ 
  DSBUFFERDESC dsBufferDesc; 
  LPVOID pSoundBlock1, pSoundBlock2; 
  DWORD bytesSoundBlock1, bytesSoundBlock2; 
  long *wave=(long*)wav;
  if(!m_pDirectSoundObj) return 0;
  if(m_currentBufferNum >= DSOUND-1) return 0;
  ++m_currentBufferNum;
  if(!pWaveFormat){ // Разобрать структуру RIFF WAVE fmt data
    if(*wave=='FFIR' && wave[2]=='EVAW' && wave[3]==' tmf'); else return 0;
    pWaveFormat=(LPWAVEFORMATEX)(wav+20);
    wave=(long*)(wav+wavsize);
    wav+=12;
    while(*(long*)wav!='atad' && (wav+=*((long*)wav+1)+8)<(char*)wave);
    if(*(long*)wav!='atad') return 0;
    wavsize=*((long*)wav+1);
    wav+=8;
    if(wavsize>(char*)wave-wav) wavsize=(char*)wave-wav;
  } // Инициализировать структуру DSBUFFERDESC 
  memset(&dsBufferDesc, 0, sizeof(DSBUFFERDESC)); 
  dsBufferDesc.dwSize = sizeof(DSBUFFERDESC); 
  dsBufferDesc.dwFlags = DSBCAPS_CTRLDEFAULT; 
  dsBufferDesc.dwBufferBytes = wavsize; 
  dsBufferDesc.lpwfxFormat = pWaveFormat; 
  // Создать вторичный звуковой буфер 
  if(m_pDirectSoundObj->CreateSoundBuffer(&dsBufferDesc, 
      &m_bufferPointers[m_currentBufferNum], NULL)!=DS_OK) return 0; 
  // Сохранить размер буфера 
  m_bufferSizes[m_currentBufferNum] = dsBufferDesc.dwBufferBytes; 
  // Копировать звук. д-е
  if(m_bufferPointers[m_currentBufferNum]->Lock(0, m_bufferSizes[m_currentBufferNum], 
    &pSoundBlock1, &bytesSoundBlock1, &pSoundBlock2, &bytesSoundBlock2, 0) != DS_OK) return 0;
  memcpy(pSoundBlock1, wav, wavsize); 
  m_bufferPointers[m_currentBufferNum]->Unlock(pSoundBlock1, bytesSoundBlock1, pSoundBlock2, bytesSoundBlock2); 
  return m_currentBufferNum; 
} 

BOOL PlaySound(UINT bufferNum){ // Играть музыку
  if(bufferNum && bufferNum <= m_currentBufferNum){
    if(m_bufferPointers[bufferNum]->Stop()!=DS_OK) return 0;
    if(m_bufferPointers[bufferNum]->SetCurrentPosition(0)!=DS_OK) return 0;
    if(m_bufferPointers[bufferNum]->Play(0,0,0)!=DS_OK) return 0;
    return 1;
  }else return 0; 
} 

BOOL StopSound(UINT bufferNum){ // Остановить музыку
  if(bufferNum && bufferNum <= m_currentBufferNum){
    if(m_bufferPointers[bufferNum]->Stop()!=DS_OK) return 0;
    return 1;
  }else return 0; 
} 


int DSoundInit(void) {
  ZeroMemory(m_bufferPointers,sizeof(LPDIRECTSOUNDBUFFER)*DSOUND);
  if(DirectSoundCreate(NULL, &m_pDirectSoundObj, NULL)!=DS_OK) return 0; 
  if(m_pDirectSoundObj->SetCooperativeLevel(hWnd, DSSCL_NORMAL)!=DS_OK){ 
    m_pDirectSoundObj = 0; return 0;}
  return 1;
} 

void DrawScreen();
void prepscr();
//char *lockprimary(void){ return (lpPrimarySurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) == DD_OK)?((char *)ddsd.lpSurface):NULL;}
char *lockprimary(void){ 
  int hRet;
  do{
    hRet=lpPrimarySurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    if(hRet==DD_OK) break;
    if(hRet=DDERR_SURFACELOST){ if(lpPrimarySurface->Restore()==DD_OK){ prepscr();DrawScreen();} break;}
    if(hRet!=DDERR_WASSTILLDRAWING) break;
  }while(1);
  return (hRet==DD_OK)?((char *)ddsd.lpSurface+((window)?((screeny*pitch+screenx)<<shiftpix):0)):0;
}

inline void unlockprimary(void){ lpPrimarySurface->Unlock(ddsd.lpSurface);}

int getpitch(void){   // Получить параметры (длина строки экрана)
  if(!lockprimary()) return 0;
  unlockprimary();   return ddsd.lPitch/(bitpix>>3);}

char linessav[]="lines.sav", linesdat[]="lines.dat", linesini[]="lines.ini";
const maxrec=20, maxsrec=5, maxnsize=32, maxcolors=7; 
const maxcol=5;
int col[maxcol]={0x80d4ff, 90, 0xc8c8c8, 0x888888, 0xffffff};
const cdelta=7, mins888=10, maxs888=30;
const maxtry=1000;
long *record;
char *back=NULL, *load=NULL, *card, *show, *showend;
char *bbuf=NULL, *balls=NULL, *fbuf, *fon, *table;
byte *table2, unbyte;
int lastsyskey=0, iscardur=0, menuflag=0, lastgame=0, points=0, nosave=0;
int wait=0, time=0, flagend=0;
int menux, menuy, menuy0, menudy, menucnt, lastbmp; //menu
int sizexy=1, sizexy2=4, sizelxy, bufsize, ballkf, x0,y0;
int s888=mins888, maxnrec=10;
int cx,cy, ccx,ccy, c2x,c2y, ccflag=0;
int lx2, ly2;
int flagstart=0, delay=10, undoflag=0, undopoints;

#define tab(xx,yy) table[(yy)*l.x+(xx)]
#define tab2(xx,yy) table2[(yy)*lx2+(xx)]
inline void ifl(int par,int min,int max){ if(par<min) par=min; if(par>max) par=max;}
inline void showadd(char x, char y){ *showend++=x; *showend++=y;}
void nextball(void);
void dropball(int first=0);
int cmpdel(int x, int y);
int ismove(void);
char *loadfileex(char *filename, int rezerv=0);
long loadfilesize=0, loadfilenomsg=0;

int maxl=0;   // Всего игр
struct lst{   // Линии
int f,        // Флаги
    x,y,      // Размеры
    minx, miny, // Отступы в точках
    time,     // Время (1/5с) на ход
    wait,     // Ходов перед броском
    color,    // Цветов
    drop,     // Брошеных шариков за ход
    start,    // Брошеных к началу игры
    pick;     // Собрать для удаления
char *name,   // Название
    *tmp;
} l, *ll=NULL, *lll;

// Флаги
const lines =1,     // Собирать линиями (по умолч.)
blocks      =1<<1,  // Собирать блоками (не использ.)
squares     =1<<2,  // Собирать квадратами
nonext      =1<<3,  // Не показывать следующие шары
moveany     =1<<4,  // Перемещать по-любому
deldrop     =1<<5;  // 

const maxpar=24;
struct params{  // Параметры из файла
  char *name;   // Имя
  int  *in;     // Указатель на переменную
  int  flag;    // 0=число, -1=список, иначе биты
} *partmp, par[maxpar]={
{"16bit",&bitpix,16},
{"32bit",&bitpix,32},
{"blocks",&l.f,blocks},
{"color",&l.color,0},
{"delay",&delay,0},
{"deldrop",&l.f,deldrop},
{"drop",&l.drop,0},
{"height",&height,0},
{"lines",&l.f,lines},
{"minx",&l.minx,0},
{"miny",&l.miny,0},
{"moveany",&l.f,moveany},
{"nonext",&l.f,nonext},
{"nosave",&nosave,1},
{"pick",&l.pick,0},
{"rmousexit",&rmousexit,1},
{"squares",&l.f,squares},
{"start",&l.start,0},
{"time",&l.time,0},
{"wait",&l.wait,0},
{"width",&width,0},
{"window",&window,1},
{"x",&l.x,0},
{"y",&l.y,0}
};

char *getatoi(char *s, int *val){ // Получить число из строки
  char *ss,c;
  while(*s==' ') ++s;
  if(*s=='-' || (*s>='0' && *s<='9')){
    ss=s;
    while(*++s>='0' && *s<='9');
    c=*s; *s=0; *val=atoi(ss); *s=c;
  }else  *val=0;
  return s;
}

char *findparam(char *s){     // Получить значение параметра
  char cc, *ss=s;
  int r1=0, r2=maxpar-1, r3, rez, val;
  while((cc=*ss) && cc!=' ' && cc!=0xd && cc!='}' && cc!='{' && cc!='=') ++ss;
  *ss=0;
  do{
    r3=(r1+r2)>>1;
    if(!(rez=(*s-*par[r3].name)) && !(rez=strcmp(s,par[r3].name))) break;
    else
     if(rez<0) r2=r3-1;
     else r1=r3+1;
  }while(r1<=r2);
  if(rez){ *ss=cc;  return 0;}
  partmp=par+r3;
  *ss=cc;
  s+=strlen(partmp->name)-1;
  while(*++s==' ' || *s=='=');
  s=getatoi(s,&val);
  if(!partmp->flag){    //0
    if(!val) return 0;
    *partmp->in=val;
  }else 
    if(partmp->flag==-1){ //list
    if(!val) return 0;
    *partmp->in=(int)card;
    do{
      *card++=val;
      s=getatoi(s,&val);
    }while(val);
    *card++=0;
  }else
  *partmp->in|=partmp->flag;
  return s;
}

int loadparam(char *file){     // Получить параметры из файла (в card)
  int cc=0,flag=0;
  char *s,*ss,*sss,*ssss;
  if(!(s=ssss=loadfileex(file,20))) return 1;
  while(*s && *s!='[') *s++=' ';
  ss=s;
  do
    switch(*s){
      case 0: break;
      case '[': ++flag; ++cc; break;
      case ']': flag=0; break;
      case '}': case '{': case 9: *s=' '; break;
      case ';': case ':': case '/': case '?':
        do *s=' '; while(*++s && *s!=0xd); break;
      default: if(!flag && *s>='A' && *s<='Z') *s|=0x20;
    }
  while(*s++);
  if(!cc){
    MessageBox(NULL,"Нет [данных] в файле!",file,MB_OK);
    return 2;
  }
  if(!(card=(char *)GlobalAlloc(GPTR,(sizeof(struct lst)+maxnsize+maxrec*4)*cc))){
    MessageBox(NULL,"Недостаточно памяти!",NULL,MB_OK);
    return 3;
  }
  ZeroMemory(&l,sizeof(lst));
  lll=ll=(lst *)card;
  record=(long *)(ll+cc);
  card=(char*)(record+maxrec*cc);
  --lll; 
  s=ss;
  do{
    switch(*s){
      case '[': 
        if(lll>=ll){ 
          memcpy(lll,&l,sizeof(lst)); 
          ZeroMemory(&l,sizeof(lst));
        }
        ++lll;
        l.name=card;
        while(*++s && *s!=']' && *s!=0xd) *card++=*s;
        *card++=0;
        if(!*s) break;
        while(*++s && *s!=0xd && *s!=0xa && *s==' ');
        if(!*s) break;
        if(*s!=0xd && *s!=0xa){
          l.tmp=card; --s;
          while(*++s && *s!=0xd) *card++=*s;
          *card++=0;
        }break;
      case 0: case 0xd: case 0xa: case ' ': break;
      default: 
        if(!(sss=findparam(s))){
          sss=s;
          while(*++s && *s!=0xd);
          *s=0;
          MessageBox(NULL,sss,"Неверная строка в конфигурации",NULL);
          return 4;
        }
        s=sss-1;
     }
  }while(*s++);
  memcpy(lll,&l,sizeof(lst));
  show=showend=card;
  maxl=cc; //lll-ll+1;
  lll=ll;
  GlobalFree(ssss);
  return 0;
}
/*Структура ini файла:
Комментарий
[Имя игры 1]
параметры игры 1
[Имя игры 2]
параметры игры 2
...
*/

inline void memsetd(void *dest, int value, long dwords){
  //short *s=(short *)dest; while(--words>=0) *s++=value;}
_asm{ mov edi,dest
      mov eax,value
      mov ecx,dwords
      cld
      rep stosd
} }

inline void memsetw(void *dest, int value, long dwords){
  //short *s=(short *)dest; while(--words>=0) *s++=value;}
_asm{ mov edi,dest
      mov eax,value
      mov ecx,dwords
      cld
      rep stosw
} }

// Вывод числа val как на эл. часах р-м sizex
void _888(char *screen, int x, int y, int sizex, int shir, int val, int ndrawnul){
  screen+=((y*2*pitch+x)*(sizex+cdelta)+24*pitch)<<shiftpix;
  char *scr;
  long i, ssize=pitch<<shiftpix, dsize=ssize*sizex, sizexx=sizex<<shiftpix;
  int a[7];
  memsetd(a,col[1],7);
  switch(val%10){
  case 8: a[5]=*col;
  case 9: a[3]=*col;
  case 3: a[1]=a[2]=*col;
  case 7: a[0]=*col;
  case 1: a[4]=a[6]=*col; break;
  case 0: if(ndrawnul) a[0]=a[2]=a[3]=a[4]=a[5]=a[6]=*col; break;
  case 2: a[0]=a[1]=a[2]=a[4]=a[5]=*col; break;
  case 4: a[3]=a[4]=a[6]=a[1]=*col; break;
  case 6: a[5]=*col;
  case 5: a[0]=a[1]=a[2]=a[3]=a[6]=*col; break;
  }
if(shiftpix==2){
  for(i=0,scr=screen;i<shir;i++,scr+=ssize){
    memsetd(scr,a[0],sizex+shir);
    memsetd(scr+dsize,a[1],sizex+shir);
    memsetd(scr+dsize+dsize,a[2],sizex+shir);
  }
  for(i=0,scr=screen;i<(sizex<<1)+shir;i++,scr+=ssize){
    memsetd(scr,a[(i<sizex+shir)?3:5],shir);
    memsetd(scr+sizexx,a[(i<sizex)?4:6],shir);
  }
}else{
  for(i=0,scr=screen;i<shir;i++,scr+=ssize){
    memsetw(scr,a[0],sizex+shir);
    memsetw(scr+dsize,a[1],sizex+shir);
    memsetw(scr+dsize+dsize,a[2],sizex+shir);
  }
  for(i=0,scr=screen;i<(sizex<<1)+shir;i++,scr+=ssize){
    memsetw(scr,a[(i<sizex+shir)?3:5],shir);
    memsetw(scr+sizexx,a[(i<sizex)?4:6],shir);
  }
}
}

void rgb565(char *bmp, int ssize){  // Преобразовать rgb 565 по rgbmask
  _asm{
  mov edi,rgbmask
  mov esi,bmp
  mov ebx,ssize
  shr ebx,1
l555:
  mov cx,[esi]
  ;rgb565 в rgb888
  ;Параметры: cx,color  eax rez-t  edx used
  sub eax,eax
  rol cx,8
  mov al,cl
  and al,11111000b
  shl eax,8
  rol cx,5
  mov al,cl
  and al,11111100b
  shl eax,8
  rol cx,6
  mov al,cl
  and al,11111000b

  mov ecx,edi
  
  ;rgb888 в rgb??? по маске: B(обрез.бит,сдвинуть бит),G,R
  ;Параметры: ecx,mask  eax,color  dx rez-t
  shl eax,8
  shl ecx,8
  sub edx,edx
  ; b
  sub al,al
  xchg al,ah
  mov cl,ch
  and cl,0xf
  shr al,cl
  shr ecx,4
  mov cl,ch
  and cl,0xf
  shl ax,cl
  or dx,ax
  shr eax,8
  shr ecx,4
  ; g
  sub al,al
  xchg al,ah
  mov cl,ch
  and cl,0xf
  shr al,cl
  shr ecx,4
  mov cl,ch
  and cl,0xf
  shl ax,cl
  or dx,ax
  shr eax,8
  shr ecx,4
  ; r
  sub al,al
  xchg al,ah
  mov cl,ch
  and cl,0xf
  shr al,cl
  shr ecx,4
  mov cl,ch
  and cl,0xf
  shl ax,cl
  or dx,ax
    
  mov [esi],dx
  add esi,2
  dec ebx
  jnz l555
}}
void _32to16(char *buf, int ssize){
  /*
  short *b=(short*)buf;
  long *bb=(long*)buf,l;
  size>>=2;
  do{ l=*bb++;
      *b++=(short)(((l>>3) & 0x1f) |
           (((l>>10) & 0x3f)<<5) |
           (((l>>19) & 0x1f)<<11));

//555:
  *b++=(short)(((l>>3) & 0x1f) |
           (((l>>11) & 0x1f)<<5) |
           (((l>>19) & 0x1f)<<10));
  }while(--size>0);
  */
  _asm{
    mov esi,buf
    mov edi,esi
    mov ecx,ssize
    shr ecx,1
    shr ecx,1
    cld
ll32:lodsd
     mov  edx,eax
     shr  eax,3
     and  eax,0x1f
     xchg ebx,eax
     mov  eax,edx
     shr  eax,10
     and  eax,0x3f
     shl  eax,5
     or ebx,eax
     xchg eax,edx
     shr  eax,19
     and  eax,0x1f
     shl  eax,11
     or ebx,eax
     xchg eax,ebx
     stosw
     loop ll32
  }
if(rgbmask!=rgbmask565) 
  rgb565(buf,ssize);
}


void bblt(char *screen){ // Вывести 4 сис.кн.
  _asm{
    cld
    mov edi,screen
    mov esi,offset bmp
    mov ebx,esi
    add ebx,54
    add esi,[esi+10]
    add esi,88*21
    mov ecx,pitch
    sub ecx,88
    shl ecx,1
    shl ecx,1
    mov dh,22
ll1:mov dl,88
ll2:sub eax,eax
    lodsb
    shl eax,1
    shl eax,1
    mov eax,[ebx+eax]
    stosd
    dec dl
    jnz ll2
    sub esi,88+88
    add edi,ecx
    dec dh
    jnz ll1
}
}

void bblt2(char *screen){ // Вывести 2 сис.кн.
  _asm{
    cld
    mov edi,screen
    mov esi,offset bmp
    mov ebx,esi
    add ebx,54
    add esi,[esi+10]
    add esi,88*21
    mov ecx,pitch
    sub ecx,44
    shl ecx,1
    shl ecx,1
    mov dh,22
ll1:mov dl,44
ll2:sub eax,eax
    lodsb
    shl eax,1
    shl eax,1
    mov eax,[ebx+eax]
    stosd
    dec dl
    jnz ll2
    sub esi,88+44
    add edi,ecx
    dec dh
    jnz ll1
}
}

void bblt16(char *screen){ // Вывести 4 сис.кн.
  _asm{
    cld
    mov edi,screen
    mov esi,offset bmp
    mov ebx,esi
    add ebx,54
    add esi,[esi+10]
    add esi,88*21
    mov ecx,pitch
    sub ecx,88
    shl ecx,1
    mov dh,22
ll1:mov dl,88
ll2:sub eax,eax
    lodsb
    shl eax,1
    mov eax,[ebx+eax]
    stosw
    dec dl
    jnz ll2
    sub esi,88+88
    add edi,ecx
    dec dh
    jnz ll1
}
}

void bblt162(char *screen){ // Вывести 2 сис.кн.
  _asm{
    cld
    mov edi,screen
    mov esi,offset bmp
    mov ebx,esi
    add ebx,54
    add esi,[esi+10]
    add esi,88*21
    mov ecx,pitch
    sub ecx,44
    shl ecx,1
    mov dh,22
ll1:mov dl,44
ll2:sub eax,eax
    lodsb
    shl eax,1
    mov eax,[ebx+eax]
    stosw
    dec dl
    jnz ll2
    sub esi,88+44
    add edi,ecx
    dec dh
    jnz ll1
}
}

inline int issyskeys(int x, int y){ return(x>=0 && y>=0 && x<88 && y<22)?(x/22+1):0;}
//inline int issyskeys2(int x, int y){ return((x-=(width-22))>0 && (y<22))?1:0;}

void smallball(char *to, UINT color, int kf){ // Уменьшенный в kf шарик цвета color-1
  --color;
  //if(color>=(UINT)l.color || !kf) return;
 ///char *from=balls+54+color*64*64*4-64*4; 
  int ii;
  int iii=((ii=64/kf)<<8)|kf;
  memcpy(to,fon,bufsize);
  to+=((ii=(sizexy-ii)>>1)*sizexy+ii)<<shiftpix;
  if(shiftpix==1) //16bits
  _asm{
        mov eax,color
        shl eax,13
        add eax,54-64*2
        add eax,balls
        mov esi,eax
        mov edi,to
        mov edx,iii
        mov ebx,sizexy
        shl ebx,1
        xor ecx,ecx
        mov cl,dh
        cld
ll0:    push  esi
        push  edi
        mov ah,dh
ll1:    mov al,dl
        movsw
ll2:    dec al
        jz  ll3
        add esi,2
        jmp ll2
ll3:    dec ah
        jnz ll1
        pop edi
        pop esi
        mov al,dl
ll4:    sub esi,128
        dec al
        jnz ll4
        add edi,ebx
        loop  ll0
    }else //32bits
    _asm{
        mov eax,color
        shl eax,14
        add eax,54-64*4
        add eax,balls
        mov esi,eax
        mov edi,to
        mov edx,iii
        mov ebx,sizexy
        shl ebx,1
        shl ebx,1
        xor ecx,ecx
        mov cl,dh
        cld
lg0:    push  esi
        push  edi
        mov ah,dh
lg1:    mov al,dl
        movsd
lg2:    dec al
        jz  lg3
        add esi,4
        jmp lg2
lg3:    dec ah
        jnz lg1
        pop edi
        pop esi
        mov al,dl
lg4:    sub esi,256
        dec al
        jnz lg4
        add edi,ebx
        loop  lg0
    }
}

void drawball(char *screen, int x ,int y, int kf){  // Нарисовать шарик (kf<0 - up/dn)
  screen+=(((y0+y*sizexy)*pitch+x0+x*sizexy)<<shiftpix);
  char *buf, *s, *ss;
  char z;
  int i,sizexy3;
  if((z=table[y*l.x+x]) && (z&0x7f)<=l.color && !(z<0 && (l.f&nonext))){
    smallball(buf=bbuf,(z&0x7f)+1,(z<0)?((kf==1)?kf+1:kf+2):(kf<0)?ballkf:kf);
    if(kf<0){ //up/dn 
      sizexy3=sizexy2*3;
      memcpy(buf=fbuf,fon,bufsize);
      s=fbuf+(sizexy2*(((ccflag%4)==3)?(sizexy/4):3));
      ss=bbuf+(sizexy2*3);
      for(i=0;i<((sizexy-5)>>2);i++,s+=sizexy3,ss+=(sizexy2<<2))
        memcpy(s,ss,sizexy3);
      }
  }
  else buf=fon;
//  for(i=0;i<(UINT)sizexy;i++,buf+=(sizexy<<shiftpix),screen+=(pitch<<shiftpix))
    //memcpy(screen,buf,sizexy<<shiftpix);
  if(shiftpix!=1) //32bits
  _asm{
        mov edi,screen
        mov esi,buf
        mov eax,sizexy
        mov edx,eax
        mov ebx,pitch
        sub ebx,eax
        shl ebx,1
        shl ebx,1
        cld
labbel: mov ecx,eax
        rep movsd
        add edi,ebx
        dec edx
        jnz labbel
  }else //16bits
  _asm{
        mov edi,screen
        mov esi,buf
        mov eax,sizexy
        mov edx,eax
        mov ebx,pitch
        sub ebx,eax
        shl ebx,1
        cld
labb:   mov ecx,eax
        rep movsw
        add edi,ebx
        dec edx
        jnz labb
  }
}


void getrgbmask(char *rgbmskarr){
  _asm{
      mov esi,rgbmskarr
      sub ecx,ecx
      mov edx,3
msk0: shl ecx,8
      lodsd
      sub cx,cx
msk1: inc cl
      shr eax,1
      jnc msk1
      xchg  ch,cl
msk2: inc cl
      shr eax,1
      jc msk2
      ;
      dec ch
      mov al,8
      sub al,cl
      xchg cl,al
      shl ch,4
      or  ch,cl
      dec edx
      jnz msk0
      shr ecx,8
      mov [rgbmask],ecx
} }

inline void showrec(char *screen, int x, int y, int value){  // Отобразить все число
  for(int xx=x+maxsrec-1;xx>=x;xx--){  _888(screen,xx,y,s888,4,value,value); value/=10;}}

void newrec(void){  // Проверка нового рекорда
  if(!lastgame) return;
  long *r=record+(lastgame-1)*maxrec;
  for(int i=0;i<maxrec;i++,r++)
    if(points>*r){
      memmove(r+1,r,(maxrec-i-1)*sizeof(long));
      *r=points;
      return;
    }
}

void showallrec(char *screen){  // Отобразить все рекорды
  long *r=record+(lll-ll)*maxrec;
  for(int i=0;i<maxnrec-1 && i<maxrec;)
    showrec(screen,0,++i,*r++);
}

void DrawChange(void) { // Нарисовать изменения
  char *screen;
  if(screen=lockprimary()){
    while(showend>show){
      if(*--showend==(char)255) showrec(screen,0,0,points);
      else drawball(screen,*(showend-1),*showend,ballkf);
      --showend;
    }
    unlockprimary();
  }
  showend=show;
}

void DrawScreen(void) { // Все нарисовать
  int x,y;
  char *screen;
  if(screen=lockprimary()){
    for(x=0;x<l.x;x++)
      for(y=0;y<l.y;y++)
        drawball(screen,x,y,ballkf);
    showrec(screen,0,0,points);
    unlockprimary();
  }
  showend=show;
}

inline void clrscr(char *screen){  // Очистка экрана
  for(int i=0;i<height;i++,screen+=(pitch<<shiftpix))
    ZeroMemory(screen,width<<shiftpix);
}

void bosscopy(char *screen=0, int toboss=0){
  char *scr=((screen)?screen:lockprimary())-((screeny*pitch+screenx)<<shiftpix);
  if(scr){
    memcpy((toboss)?boss:scr,(toboss)?scr:boss,wwidth*wheight<<shiftpix);
    if(!screen) unlockprimary();
} }

void prepscr(void){  // Подготовка экрана
  char *screen;
  if(screen=lockprimary()){
    if(window) bosscopy(screen);
    clrscr(screen);
    if(shiftpix==1) bblt16(screen); else bblt(screen);
    showallrec(screen);
    unlockprimary();
  }
}

void newgame(void){   // Новая игра
  int sx, sx1, i, ii, iii, sizex;
  char *ff;
  menuflag=ccflag=flagend=undoflag=ccx=ccy=0;
  showend=show;
  newrec();
  points=0;
  if(load && load[5]<=maxl) lll=ll+load[5]-1;
if(lastgame!=lll-ll+1){
  lastgame=lll-ll+1;
  memcpy(&l,lll,sizeof(lst));
  sizexy=(height-l.miny-l.miny)/l.y;
  sizexy2=sizexy<<shiftpix;
  sizelxy=l.x*l.y;
  sizex=(width-(mins888+cdelta)*maxsrec-l.minx-l.minx)/l.x;
  if(sizex<sizexy) sizexy=sizex;
  x0=(width-sizexy*l.x);
  y0=(height-sizexy*l.y)>>1;
  s888=x0/maxsrec-cdelta;
  if(s888>maxs888) s888=maxs888;
  //x0-=(s888+cdelta)*maxsrec;
  //x0>>=1;
  maxnrec=(height-24)/(s888+cdelta)/2;
  //x0=width-sizexy*l.x-x0;
  x0=(s888+cdelta)*maxsrec; //+x0;
  ballkf=64/sizexy+1;
  bufsize=sizexy*(sizexy<<shiftpix);
  if(bbuf) GlobalFree(bbuf);
  if(!(bbuf=(char *)GlobalAlloc(GPTR,((bufsize<<1)+bufsize)+sizelxy+16+(lx2=l.x+2)*(ly2=l.y+2)))) return;
  fbuf=bbuf+bufsize;
  fon=fbuf+bufsize;
  table=fon+bufsize;
  // Заголовок для з-и
  *(long*)table='eniL';
  table[4]=maxl;
  table[5]=lastgame;
  table[6]=l.x;
  table[7]=l.y;
  table+=16;
  // Таблица поиска пути
  table2=(byte*)table+sizelxy+lx2+1;
  // Нарисовать фон в fon
  sx=sizexy<<shiftpix;
  sx1=(sizexy+1)<<shiftpix;
  if(shiftpix==1){  //16 bit
  memsetw(fon+sx,col[2],(bufsize-sx-sx)>>shiftpix);
  memsetw(fon+sx1,col[4],sizexy+1);
  memsetw(fon+sx+sx1,col[4],sizexy+1);
  memsetw(fon+bufsize-sx-sx1,col[3],sizexy+1);
  memsetw(fon+bufsize-sx-sx-sx1,col[3],sizexy+1);
  for(i=0,ff=fon;i<sizexy-1;i++,ff+=sx){
    *(short*)ff=*((short*)(ff+sx)-1)=0;
    *((short*)ff+1)=(short)col[4];
    *((short*)(ff+sx)-3)=*((short*)(ff+sx)-2)=(short)col[3];
  }}else{  //32 bit
  memsetd(fon+sx,col[2],(bufsize-sx-sx)>>shiftpix);
  memsetd(fon+sx1,col[4],sizexy+1);
  memsetd(fon+sx+sx1,col[4],sizexy+1);
  memsetd(fon+bufsize-sx-sx1,col[3],sizexy+1);
  memsetd(fon+bufsize-sx-sx-sx1,col[3],sizexy+1);
  for(i=0,ff=fon;i<sizexy-1;i++,ff+=sx){
    *(long*)ff=*((long*)(ff+sx)-1)=0;
    *((long*)ff+1)=col[4];
    *((long*)(ff+sx)-3)=*((long*)(ff+sx)-2)=col[3];
  }}
  sizelxy=l.x*l.y;
} 
  if(load){ // Загрузка
    i=0;
    if(l.x==load[6] && l.y==load[7]){ memcpy(table,load+16,sizelxy); ++i;}
    if((ii=loadfilesize-(iii=16+(int)load[6]*load[7]))>maxl*maxrec*4) ii=maxl*maxrec*4; 
    memcpy(record,load+iii,ii);
    if(window){
      screenx=*(short*)(load+8);
      screeny=*(short*)(load+10);
      if(screenx<0) screenx=0; if(screenx>wwidth-width) screenx=wwidth-width;
      if(screeny<0) screeny=0; if(screeny>wheight-height) screeny=wheight-height;
    }
    points=*(long*)(load+12);
    GlobalFree(load); load=0;
    if(!i) goto in123;
  }else{
in123:
    ZeroMemory(table,sizelxy);
    i=l.drop;
    l.drop=l.start;
    nextball();
    l.drop=i;
    dropball(1);
  }
  prepscr();
  DrawScreen();
  wait=l.wait; 
  time=l.time;
  flagstart=1;
}

char *loadfileex(char *filename, int rezerv){
  HANDLE handle;
  char *buf;
  if((handle=CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, 
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY 
    | FILE_FLAG_SEQUENTIAL_SCAN, NULL))==INVALID_HANDLE_VALUE){
    if(!loadfilenomsg)
    MessageBox(NULL,"Не могу открыть файл!",filename,MB_OK);
    loadfilesize=0;
    return 0;
  }
  loadfilesize=GetFileSize(handle,NULL);
  if(!(buf=(char *)GlobalAlloc(GPTR, loadfilesize+rezerv))){
    if(!loadfilenomsg)
    MessageBox(NULL,"Недостаточно памяти для загрузки файла!",filename,MB_OK);
    loadfilesize=0;
    return 0;
  }
  ReadFile(handle,buf,loadfilesize,&(DWORD&)loadfilesize,0);
  CloseHandle(handle);
  return buf;
}

// lines.sav: LINE (Всего_таблиц_рекордов Текущая_игра X Y)4б   
void savegame(void){  // Сохранить игру
  //table-8, l.x*l.y+8
  //record, maxl*maxrec*4
  DWORD writebytes;
  HANDLE handle;
  if((handle=CreateFile(linessav, GENERIC_WRITE, NULL, NULL, 
    CREATE_ALWAYS	, FILE_ATTRIBUTE_NORMAL, NULL))==INVALID_HANDLE_VALUE){
    MessageBox(NULL,"Не могу создать файл!",linessav,MB_OK);
    return; }
  if(window){*(short*)(table-8)=screenx; *(short*)(table-6)=screeny;}
  *(long*)(table-4)=points;
  WriteFile(handle,table-16,sizelxy+16,&writebytes,NULL);
  WriteFile(handle,record,maxl*maxrec*4,&writebytes,NULL);
  CloseHandle(handle);
}

void showmenu(void){  // Меню выбора игры
  char *screen;
  if(screen=lockprimary()){
    clrscr(screen);
    if(shiftpix==1) bblt162(screen); else bblt2(screen);
    unlockprimary();
  }
  HDC hdc;
  TEXTMETRIC tm;
  int i,x,y,x0,xxmin;
  menuflag=1;
  //undoflag=0;
  if(hdc=GetDC(hWnd)){
    GetTextMetrics(hdc,&tm);
    SetBkColor(hdc,0);
    SetTextColor(hdc,0xffffff);
    xxmin=tm.tmAveCharWidth<<3;
    menudy=max(tm.tmHeight,6);
    menux=maxl/(height/menudy)+1;
    menuy=maxl/menux+1;
    menux=maxl/menuy+1;
    menuy0=(height-menuy*menudy)>>1;
    x0=width/(menux+1);
    for(i=-1,x=1;x<=menux;x++)
      for(y=0;y<menuy;y++)
        if(++i<maxl)
          TextOut(hdc, x0*x-xxmin+screenx, menuy0+y*menudy+screeny, (ll+i)->name,strlen((ll+i)->name)); 
    ReleaseDC(hWnd,hdc);
  }
}

void selgame(int x, int y){   // Игра выбрана?
  switch(issyskeys(x,y)){
  case 1: SendMessage(hWnd, WM_CLOSE, 0, 0); return;
  case 2: if(flagstart){ menuflag=0; prepscr(); DrawScreen();} return;
  case 3: return;
  }
//  if(issyskeys2(x,y)){ SendMessage(hWnd, WM_CLOSE, 0, 0); return;}
  if((y-=menuy0)<0 || (y=y/menudy)>=menuy) return;
  x=x/(width/menux);
  int i;
  if((i=x*menuy+y)>=maxl) return;
  lll=ll+i;
  newgame();
}

///////////Init////////
int Init(void){ // Инициализация
  randomize();
  if(!(balls=loadfileex(linesdat))) return 1;
  if(loadparam(linesini)) return 2;
  for(lll=ll;lll<ll+maxl;lll++){
    memcpy(&l,lll,sizeof(lst));
    ifl(l.x,2,254);
    ifl(l.y,2,254);
    ifl(l.color,1,maxcolors);
    ifl(l.pick,2,l.x*l.y); 
    ifl(l.drop,1,l.x*l.y);
    if(!l.start) l.start=l.drop;
    if(l.f&squares) l.pick=4;
    if(l.wait) ++l.wait;
    memcpy(lll,&l,sizeof(lst));
  }lll=ll;
  if(!nosave){
    ++loadfilenomsg;
    load=loadfileex(linessav);
    if(load && *(long*)load!='eniL'){ GlobalFree(load); load=0;}
    --loadfilenomsg;
  }
   //selgame();
  //newgame();
   return 0;
}

int square(int x, int y, char color){ // Квадрат?
  if(x<0 || y<0 || x>=l.x-1 || y>=l.y-1) return 0;
  return (tab(x,y)==color && tab(x+1,y)==color && tab(x,y+1)==color && tab(x+1,y+1)==color);
}

void delsquare(int x, int y){ // Удалить квадрат
  tab(x,y)=tab(x+1,y)=tab(x,y+1)=tab(x+1,y+1)=0;
  showadd(x,y); showadd(x+1,y); showadd(x,y+1); showadd(x+1,y+1);
}

int cmpdel(int x, int y){  // Проверить позицию x,y на удаление + showadd
  int x1,x2,x3,x4,x5,x6;
  int y1,y2,y3,y4,y5,y6;
  int n=0;
  char c;
if((c=tab(x,y))>0){
  if(l.f&squares){  // Квадратами
    x1=square(x,y,c);
    x2=square(x-1,y,c);
    x3=square(x,y-1,c);
    x4=square(x-1,y-1,c);
    if(x1){ n=4; delsquare(x,y);}
    if(x2){ n+=4-((n)?2:0); delsquare(x-1,y);}
    if(x3){ n+=4-((n)?2:0); delsquare(x,y-1);}
    if(x4){ n+=4-((n)?2:0); delsquare(x-1,y-1);}
    l.pick=4;
  }else{
  x1=x3=x5=x;
  y1=y3=y5=y;
  //вертикально
  while(--y1>=0 && tab(x,y1)==c); y2=++y1;
  while(++y2<l.y && tab(x,y2)==c);
  //горизонтально
  while(--x1>=0 && tab(x1,y)==c); x2=++x1;
  while(++x2<l.x && tab(x2,y)==c);
  //слева сверху вниз вправо
  --x3,--y3;
  while(x3>=0 && y3>=0 && tab(x3,y3)==c) --x3,--y3; 
  x4=++x3+1; y4=++y3+1;
  while(x4<l.x && y4<l.y && tab(x4,y4)==c) ++x4,++y4;
  //справа сверху вниз влево
  ++x5,--y5;
  while(x5<l.x && y5>=0 && tab(x5,y5)==c) ++x5,--y5; 
  x6=--x5-1; y6=++y5+1; 
  while(x6>=0 && y6<l.y && tab(x6,y6)==c) --x6,++y6;
  //рез-т (кол-во шаров)
  if(y2-y1>=l.pick){ n=y2-y1; while(y1<y2){ tab(x,y1)=0; showadd(x,y1++);}}
  if(x2-x1>=l.pick){ n+=x2-x1-((n)?1:0); while(x1<x2){ tab(x1,y)=0; showadd(x1++,y);}}
  if(y4-y3>=l.pick){ n+=y4-y3-((n)?1:0); while(y3<y4){ tab(x3,y3)=0; showadd(x3++,y3++);}}
  if(y6-y5>=l.pick){ n+=y6-y5-((n)?1:0); while(y5<y6){ tab(x5,y5)=0; showadd(x5--,y5++);}}
  }
  if(n){ showadd((char)255,(char)255);  points+=(n-l.pick+1)*l.pick; PlaySound(3);
} }
  return (l.f&deldrop)?0:n;
}

#define ttt if(*tt==(byte)253) return 0; if(*tt==(byte)254) *tt=Ni+1

int ismove(void){  // Можно ли переместить ccx,ccy в cx,cy
  // Волновой алгоритм поиска (взято от Медноногова)
  //if(l.f&moveany) return 0;
  byte *t, *tt;
  int i,j,k,Ni=0,size2=lx2*l.y;
  undoflag=0;
  memset(table2-lx2-1,255,lx2*ly2);
  for(j=k=0;j<l.y;j++)
    for(i=0;i<l.x;i++)
      if(table[k++]<=0) --tab2(i,j);
  tab2(cx,cy)=0;
  tab2(ccx,ccy)=(byte)253;
  do
    for(i=0,t=table2;i<size2;i++,t++)
      if(*t==Ni){
        tt=t+1; ttt;
        tt=t-1; ttt;
        tt=t+lx2; ttt;
        tt=t-lx2; ttt;
      }
  while(++Ni<252);
  return 1;
}

void nextball(void){ // Следующие шарики показать
  int i,j,k;
  for(i=0,j=0;i<l.drop;i++){
    while(table[k=random(sizelxy)]!=0) if(++j>maxtry) return;
    table[k]=(char)((random(l.color)+1)|0x80);
    showadd(k%l.x,k/l.x);
  }
}

void dropball(int first){  // Бросить n шариков
  int i,j,k,m;
  for(i=0,m=0;i<sizelxy;i++)
    if(table[i]<0){ table[i]&=0x7f; ++m; showadd(i%l.x,i/l.x); cmpdel(i%l.x,i/l.x);}
if(!first)
  while(m++<l.drop){ 
    j=0;
    while(table[k=random(sizelxy)]) if(++j>maxtry){ ++flagend; return;}
    table[k]=(char)(random(l.color)+1);
    showadd(k%l.x,k/l.x); cmpdel(k%l.x,k/l.x);
  }
  nextball();
  time=l.time;
}

void movestep(void){  // Пошаговое перемещение из ccx,ccy в cx,cy
  byte m,o=0,c=tab(ccx,ccy);
  int mx,my;
  do{
    m=tab2(mx=ccx,my=ccy+1);
    if(tab2(ccx,ccy-1)<m) m=tab2(mx=ccx,my=ccy-1);
    if(tab2(ccx+1,ccy)<m) m=tab2(mx=ccx+1,my=ccy);
    if(tab2(ccx-1,ccy)<m) m=tab2(mx=ccx-1,my=ccy);
    tab(ccx,ccy)=o;
    o=tab(mx,my);
    tab(mx,my)=c;
    showadd(ccx,ccy);
    showadd(mx,my);
    DrawChange();
    ccx=mx; ccy=my;
    Sleep(delay);
  }while(m);
}

int getpos(int x, int y){   // Позиция мышки на поле
  if((x-=x0)<0 || (y-=y0)<0) return 1;
  if((x/=sizexy)>=l.x || (y/=sizexy)>=l.y) return 1;
  cx=x; cy=y;
  return 0;
}

int tabempty(void){ // Нет больше шариков
  for(int i=0;i<sizelxy;i++)
    if(table[i]>0) return 0;
  return 1;
}

int tabfull(void){ // Нет своб. места
  for(int i=0;i<sizelxy;i++)
    if(table[i]<=0) return 0;
  return 1;
}

void undo(void){
  points=undopoints;
  memcpy(table,table2,sizelxy);
  DrawScreen();
  undoflag=0; time=l.time;
}

void showupdn(void){
  char *screen;
  if(screen=lockprimary()){
    drawball(screen,ccx,ccy,((++ccflag)%2)?-1:ballkf);
    unlockprimary();
  }
}

void lbuttondown(int x, int y){ // Лев. кн. нажата
  if(menuflag){ selgame(x,y); return;}
  switch(issyskeys(x,y)){
  case 1: SendMessage(hWnd, WM_CLOSE, 0, 0); return;
  case 2: showmenu(); return;
  case 3: newgame(); return;
  case 4: if(undoflag) undo(); return;
  }
  if(getpos(x,y)) return;
  if(table[cx+cy*l.x]>0){
    if(ccflag){ showadd(ccx,ccy); DrawChange();}
    ccx=cx; ccy=cy; ++ccflag; return;
  }
  if(!ccflag) return;
  if(ismove()){ PlaySound(2); return;}
  c2x=ccx; c2y=ccy; unbyte=tab(cx,cy);
  movestep(); PlaySound(1);
  memcpy(table2,table,sizelxy); undopoints=points; //undo
  table2[c2y*l.x+c2x]=table2[cy*l.x+cx]; table2[cy*l.x+cx]=unbyte; undoflag=1;
  //showadd(cx,cy); showadd(ccx,ccy);
  //tab(cx,cy)=tab(ccx,ccy); tab(ccx,ccy)=0;
  ccflag=0;
  if(cmpdel(cx,cy)){
    if(tabempty()) dropball();
  }else
    if(wait){ if(!--wait){ wait=l.wait; dropball();}
    }else dropball();
  if(flagend || tabfull()) newgame();
  else
    DrawChange();
}

/////////////
int DDrawInit(HWND hWnd) {  // Иниц. Ddraw
//  DDSCAPS ddscaps;
  if (DirectDrawCreate(NULL, &lpDDraw, NULL) != DD_OK) return 0;
if(!window){
  if (lpDDraw->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) != DD_OK) return 0;
  if (lpDDraw->SetDisplayMode(width, height, bitpix) != DD_OK) return 0;
}else
  if (lpDDraw->SetCooperativeLevel(hWnd, DDSCL_NORMAL) != DD_OK) return 0;
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  //ddsd.dwBackBufferCount=1;
  ddsd.dwFlags = DDSD_CAPS;
  if (lpDDraw->CreateSurface(&ddsd, &lpPrimarySurface, NULL) != DD_OK) return 0;
  //ZeroMemory(&ddscaps, sizeof(ddscaps));
  //ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
  //if (lpPrimarySurface->GetAttachedSurface(&ddscaps,&lpSecondarySurface) != DD_OK) return 0;
if(bitpix==16){  
  DDPIXELFORMAT lpDDpixel;
  long rgbs[3];
  ZeroMemory(&lpDDpixel, sizeof(DDPIXELFORMAT));
  lpDDpixel.dwSize=sizeof(DDPIXELFORMAT);
  lpPrimarySurface->GetPixelFormat(&lpDDpixel);
  rgbs[0]=lpDDpixel.dwRBitMask;
  rgbs[1]=lpDDpixel.dwGBitMask;
  rgbs[2]=lpDDpixel.dwBBitMask;
  getrgbmask((char*)rgbs);
}
  return 1;
}

void CleanUp(){   // Освободить ресурсы
  //if(lpSecondarySurface) lpSecondarySurface->Release();
  if(m_pDirectSoundObj){
    for(UINT i=1;i<=m_currentBufferNum;i++)
      if(m_bufferPointers[i]) m_bufferPointers[i]->Release();
    m_pDirectSoundObj->Release();
  }
  if(lpPrimarySurface) lpPrimarySurface->Release();
  if(lpDDraw) lpDDraw->Release();
  if(!load) GlobalFree(load);
  if(!ll)   GlobalFree(ll);
  if(!balls) GlobalFree(balls);
  if(!bbuf) GlobalFree(bbuf);
  if(!boss) GlobalFree(boss);
  if(Mutex) ReleaseMutex(Mutex);
}

LRESULT CALLBACK DDrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    //case WM_CREATE: return 0;
    case WM_TIMER:
      if(altabflag!=1){
      if(altabflag==2){altabflag=menuflag=bossflag=0; prepscr(); DrawScreen();}
      if(!menuflag && !bossflag){
        if(ccflag) showupdn(); //PlaySound(4);
        if(time && !--time){ dropball(); if(flagend) newgame(); else DrawChange();}
      }}return 0;
    case WM_KEYDOWN:  if(wParam==VK_ESCAPE) SendMessage(hWnd, WM_CLOSE, 0, 0);  return 0;
//    case WM_MOUSEMOVE: return 0;
    case WM_LBUTTONDOWN: if(!bossflag) lbuttondown(LOWORD(lParam)-screenx,HIWORD(lParam)-screeny); return 0;
//    case WM_LBUTTONUP:  lbuttonup(LOWORD(lParam),HIWORD(lParam));  return 0;
    case WM_RBUTTONDOWN: rbutx=LOWORD(lParam); rbuty=HIWORD(lParam); return 0;
    case WM_RBUTTONUP: 
      if(window){
      if(bossflag){ bossflag=0; prepscr(); DrawScreen(); return 0;}
      if(abs(LOWORD(lParam)-rbutx)>10 || abs(rbuty-HIWORD(lParam))>10){
        screenx+=LOWORD(lParam)-rbutx; 
        screeny+=HIWORD(lParam)-rbuty;
        if(screenx<0) screenx=0; if(screenx>wwidth-width) screenx=wwidth-width;
        if(screeny<0) screeny=0; if(screeny>wheight-height) screeny=wheight-height;
        prepscr(); DrawScreen();
      }else{
        bosscopy();
        ++bossflag;
      }}
      return 0;
    case WM_SETFOCUS:  
      if(flagstart) altabflag=2;
        //prepscr(); DrawScreen();
      return 0;
    case WM_KILLFOCUS: altabflag=1; return 0;
    case WM_DESTROY: KillTimer(hWnd, 1); 
      if(!nosave) savegame(); 
      CleanUp(); PostQuitMessage(0); return 0;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASS wndClass;
  MSG msg;
  int i;
  if(!(Mutex=CreateMutex(0,0,"ScreenSL"))) return 10;
  if(GetLastError()==ERROR_ALREADY_EXISTS) return 11;
//  getargv(lpCmdLine);	
  if(i=Init()){ CleanUp(); return i;}
  ZeroMemory(&wndClass, sizeof(wndClass));
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = DDrawWndProc;
  wndClass.hInstance = hInstance;
  wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndClass.lpszClassName = "Lines 2006";
  RegisterClass(&wndClass);
  hWnd = CreateWindowEx(WS_EX_TOPMOST, wndClass.lpszClassName, "Lines", WS_POPUP | WS_MAXIMIZE, 0, 0, 
    GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  wwidth=GetSystemMetrics(SM_CXSCREEN);
  wheight=GetSystemMetrics(SM_CYSCREEN);
  if(!width) width=wwidth;
  if(!height) height=wheight;
  if(!bitpix) bitpix=32;
  if(!DDrawInit(hWnd)){ 
     MessageBox(hWnd,"Не могу запустить DirectX",0,MB_OK | MB_ICONEXCLAMATION);
     CleanUp(); return 12;
  }
  if(!(pitch=getpitch())){ CleanUp(); return 13;}
  if(!DSoundInit()){ 
     MessageBox(hWnd,"Не могу запустить DirectSound",0,MB_OK | MB_ICONEXCLAMATION);
     CleanUp(); return 12;
  }
  switch(bitpix>>3){ 
    case 2: shiftpix=1; 
      _32to16(bmp+54,*(long*)(bmp+10)-54); 
      _32to16(balls+54,maxcolors<<14); 
      _32to16((char*)col,maxcol<<2); 
      i=maxcol;
      while(--i>=0)
        col[i]=*((short*)col+i);
      break;
    case 4: shiftpix=2; break;
    default: shiftpix=0; 
  }
  //load sound
  char *snd;
  ++loadfilenomsg; // иначе виснет!!!
  for(i=0;i<3;i++){
    if(!(snd=loadfileex(filesnd[i])) || !LoadSound(snd,loadfilesize)){
      MessageBox(hWnd,"Ошибка загрузки звука!",filesnd[i],MB_OK); return 14; } 
    GlobalFree(snd);
  }
  if(window){
    if(!(boss=(char*)GlobalAlloc(GPTR,wwidth*wheight<<shiftpix))){ CleanUp(); return 14;}
    bosscopy(0,1);
  }
  newgame();
  SetTimer(hWnd, 1, 200, 0);
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
