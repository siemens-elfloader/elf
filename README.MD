4. Создаем свой эльф 
Теперь создание эльфов стало совсем простым делом :) 
Проще всего подправить готовый пример: см. предыдущий раздел. 
Добавляем к проекту "Project->Add Files" файлы Siemens.c и main.c 
(А вот последняя версия мультиплатформенного Siemens.cpp с автоопределением типа мобилы). 
К проекту должны быть подключены файлы Func.asm (точка старта) и div.r79 (деление, см.Swilib выше) 
Корректируем в main.c функции: 
onkey - обработка клавиш (return 1 для выхода из эльфа) 
onredraw - перерисовка экрана (массива screen[132*176]) 
onstart, oncreate - функции вызываются при старте 
onclose, onexit - функции вызываются при выходе 
REDRAW() вызываем для перерисовки экрана (запуска onredraw) 
И ВСЕ! У Вас готовое приложение. Специфику Сименса знать не нужно вообще! 
Также см. примеры ниже. 

5. Пример 1. Работа с памятью и файлами 
меняем в любом примере main.c на: 
#include "E:\ARM\swilib.h" 

void ElfKiller(void){ // Используется для выхода из эльфа 
extern void *ELF_BEGIN; 
// здесь обычно еще освобождают память по mfree(), freeWS() 
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN); // Ничего не понятно :( 
} 

int main(char *exename, char *fname){ // Основная функция 
// в exename передается путь запущенного эльфа вида 4:\Zbin\xyz.elf 
// в fname передается имя файла, который выбран в CardExplorere, вида 0:\Misc\data.txt 
// или 0, если elf запущен сам 
char *mem; 
int i, err; 
int handle; 
if(fname){ 
// Работа с файлами стандартна: 
handle=fopen(fname,A_ReadWrite+A_BIN+A_Append+A_Create,P_READ+P_WRITE,&err); 
// Открыть для чтения и записи в двоичн. режиме с дозаписью (append), создать если нет 
// или handle=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err); // только для чтения - константы см. swilib.h 
if(handle!=-1){ //-1 = error 
mem=malloc(10000); // Выделить память: AllocWS() для строк (по 2б) 
if(mem!=0){ //0 = error 
i=fread(handle,mem,10000,&err); // Возвращает число прочитанных байт и ошибку в err 
// Делаем что-либо makesomebody(mem,i); 
fwrite(handle,mem,i,&err); 
mfree(mem); // Освободить память: FreeWS() для строк 
} 
fclose(handle); // Закрыть файл 
} 
} 
SUBPROC((void *)ElfKiller); // се загадка великая есть :) Но без нее низя! 
return(0); 
} 
// PS. Т.к. в x65 файловые чтение и запись проводятся блоками до 32767 байт, 
// вместо fread() и fwrite() используем их аналоги fread32() и fwrite32( аналогично) 

int fread32(int fh, char *buf, int len, unsigned int *err) // (с) Rst7 
{ 
int clen; 
int rlen; 
int total=0; 
while(len) 
{ 
if (len>16384) clen=16384; else clen=len; 
total+=(rlen=fread(fh, buf, clen, err)); 
if (rlen!=clen) break; 
buf+=rlen; 
len-=clen; 
} 
return(total); 
} 

Не забываем включить в каждый проект файл  Func.asm: 
PUBLIC ELF_BEGIN 
RSEG ELFBEGIN:DATA 
ELF_BEGIN 
defadr MACRO a,b 
PUBLIC a 
a EQU b 
ENDM 
END 

6. Пример 2. Вывод на экран и обработка клавиш 
Выводит маленький рисунок на экран, перемещаемый с помощью джойстика, 
и выходит по долгому нажатию красной кнопки. Сделан на примере TED-а (c) Rst7 
Смотреть снизу-вверх :) 
меняем в примере main.c на: 
#include "E:\ARM\swilib.h" 

typedef struct 
{ 
GUI gui; 
// WSHDR *ws1; 
// WSHDR *ws2; 
// int i1; 
}MAIN_GUI; 

typedef struct 
{ 
CSM_RAM csm; 
int gui_id; 
}MAIN_CSM; 

const int minus11=-11; 
const unsigned int INK=0; 
const unsigned int PAPER=1; 
volatile int xx=0, yy=0; // Координаты отображения рисунка 

const char bmp[12]={0xFC,0x86,0xB3,0xA9,0xB1,0xA9,0x81,0xFF,0,0,0,0}; 
const IMGHDR img = {8,12,0x1,0,(char *)bmp}; 

//================================ 
//Вывод на экран 
//================================ 

void DrwImg(IMGHDR *img, int x, int y, int *pen, int *brush) 
{ 
RECT rc; 
DRWOBJ drwobj; 
StoreXYWHtoRECT(&rc,x,y,img->w,img->h); 
SetPropTo_Obj5(&drwobj,&rc,0,img); 
SetColor(&drwobj,pen,brush); 
DrawObject(&drwobj); 
} 

void DrawScreen(void) 
{ 
int *ink=GetPaletteAdrByColorIndex(INK); 
int *paper=GetPaletteAdrByColorIndex(PAPER); 
int x=xx; 
DrwImg((IMGHDR *)&img,x,yy,ink,paper); 
} 

//Перерисовка основного диалога 
void method0(MAIN_GUI *data){ 
DrawScreen(); 
} 

void method1(MAIN_GUI *data, void *(*malloc_adr)(int)){} 
void method2(MAIN_GUI *data, void (*mfree_adr)(void *)){} 
void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){} 
void method4(MAIN_GUI *data, void (*mfree_adr)(void *)){} 
void method7(MAIN_GUI *data, void (*mfree_adr)(void *)){} 
int method8(void){return(0);} // Пустая ф-я 
int method9(void){return(0);} // Пустая ф-я 

//------------------------------------------------------------------------------ 
// Осн. диалог - обработка кнопок 
//------------------------------------------------------------------------------ 
int method5(MAIN_GUI *data, GUI_MSG *msg) 
{ 
// if (msg->gbsmsg->msg==KEY_UP) // Клавиша отпущена 
if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS)) // Кл. нажата или удерживается 
switch(msg->gbsmsg->submess) 
{ 
case RED_BUTTON: 
return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI 
case UP_BUTTON: 
if(yy>0) --yy; break; 
case LEFT_BUTTON: 
if(xx>0) --xx; break; 
case DOWN_BUTTON: 
if(yy<130) ++yy; break; 
case RIGHT_BUTTON: 
if(xx<120) ++xx; break; 

// case GREEN_BUTTON: 
// case RIGHT_SOFT: 
// case ENTER_BUTTON: 
// case LEFT_SOFT: 
// case VOL_UP_BUTTON: 
// case VOL_DOWN_BUTTON: 
// case '0': 
// case '9': 
// case '#': 
// SUBPROC((void *)DoDiskAccess,1); 
// Др. процесс с низким приоритетом чтобы не тормозить перерисовку окна 
} 
DrawScreen(); 
return(0); 
} 

const void * const gui_methods[11]={ 
(void *)method0, //Redraw 
(void *)method1, //Create 
(void *)method2, //Close 
(void *)method3, //Focus 
(void *)method4, //Unfocus 
(void *)method5, //OnKey 
0, 
(void *)method7, //Destroy 
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

// ustk=malloc(STKSZ); // Выделяем память под что нам надо 
// info_ws=AllocWS(512); 

main_gui->gui.canvas=(void *)(&Canvas); 
main_gui->gui.flag30=2; 
main_gui->gui.methods=(void *)gui_methods; // Основные методы (см. выше) 
main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr(); // Ниже ниче не знаю :( 
csm->csm.state=0; 
csm->csm.unk1=0; 
csm->gui_id=CreateGUI(main_gui); // Собственно создание GUI 
} 

void Killer(void) // Выход 
{ 
extern void *ELF_BEGIN; 
// mfree(ustk); // Освобождаем память 
// FreeWS(info_ws); 
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN); 
} 

void maincsm_onclose(CSM_RAM *csm) 
{ 
// GBS_StopTimer(&light_tmr); 
SUBPROC((void *)Killer); 
} 

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){ 
return(1); 
} 

unsigned short maincsm_name_body[140]; 

const struct 
{ 
CSM_DESC maincsm; 
WSHDR maincsm_name; 
}MAINCSM = 
{ 
{ 
maincsm_onmessage, // Обработчик сообщений 
maincsm_oncreate, // Вызывается при создании 
// 0, // Для S75 убрать комментарии в 4х строчках 
// 0, // и раскомментировать в swilib.h строку #define NEWSGOLD 
// 0, 
// 0, 
maincsm_onclose, // Вызывается при закрытии 
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

int main(char *exename, char *fname) 
{ 
char dummy[sizeof(MAIN_CSM)]; 
// strcpy(filename,fname); // Сохраняем где-либо fname 
CreateCSM(&MAINCSM.maincsm,dummy,0); 
return 0; 
} 

7. Пример попроще. Запускаем фоновый процесс, рисуем по таймеру 
Добавляем к проекту "Project->Add Files" файл Siemens.c: 
// Siemens.c 0.1 
// Интерфейс мобилы для IAR 
// Здесь ничего не трогаем! (если не уверены) 
// Внешние функции вызываются при: 
extern int onstart(char *exename, char *fname); // Старте приложения. Возвращает 0 или 1 для выхода. 
extern void oncreate(); // Создании окна 
extern void onclose(); // Закрытии окна 
extern void onexit(); // Выходе 
extern void onredraw(void); // Перерисовке экрана 
extern int onkey(unsigned char keycode, int pressed); // Нажатии клавиши. Возвращает 0 или 1 для выхода. 

// В swilib.h комментируем // строку #define NEWSGOLD если не S75 
#include "E:\ARM\swilib.h" 
// Следующая строка задает 16 битный режим (RGB 565 по 2 байта на точку экрана screen) 
// закомментировав получим 8 битный режим (RGB 232 по 1 байту на точку) 
#define HIGHCOLOR 
#ifdef HIGHCOLOR 
short screen[132*176]; 
const int screensize=132*176*sizeof(short); 
const IMGHDR img = {(unsigned)132,(unsigned)176,8,0,(char*)screen}; 
#else 
char screen[132*176]; 
const int screensize=132*176*sizeof(char); 
const IMGHDR img = {(unsigned)132,(unsigned)176,5,0,(char*)screen}; 
#endif 

// Ниже читать уже не надо! :) 
typedef struct 
{ 
GUI gui; 
WSHDR *ws1; 
WSHDR *ws2; 
int i1; 
}MAIN_GUI; 

typedef struct 
{ 
CSM_RAM csm; 
int gui_id; 
}MAIN_CSM; 

void DrawScreen(){ 
RECT rc; DRWOBJ drwobj; 
StoreXYWHtoRECT(&rc,0,0,img.w,img.h); 
SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR*)&img); 
SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1)); 
DrawObject(&drwobj); 
} 
void method0(MAIN_GUI *data){ onredraw(); DrawScreen();} 
void method1(MAIN_GUI *data, void *(*malloc_adr)(int)){ oncreate(); data->gui.state=1;} 
void method2(MAIN_GUI *data, void (*mfree_adr)(void *)){ data->gui.state=0;} 
void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){ data->gui.state=2;} 
void method4(MAIN_GUI *data, void (*mfree_adr)(void *)){ if (data->gui.state!=2) return; data->gui.state=1;} 
int method5(MAIN_GUI *data, GUI_MSG *msg){ 
return onkey(msg->gbsmsg->submess, msg->gbsmsg->msg);} 
void method7(MAIN_GUI *data, void (*mfree_adr)(void *)){}// mfree_adr(data); 
int method8(void){return(0);} // Пустая ф-я 
int method9(void){return(0);} // Пустая ф-я 

const void * const gui_methods[11]={ 
(void *)method0, //Redraw 
(void *)method1, //Create 
(void *)method2, //Close 
(void *)method3, //Focus 
(void *)method4, //Unfocus 
(void *)method5, //OnKey 
0, 
(void *)method7, //Destroy 
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
// ustk=malloc(STKSZ); // Выделяем память 
// info_ws=AllocWS(512); 
main_gui->gui.canvas=(void *)(&Canvas); 
main_gui->gui.flag30=2; 
main_gui->gui.methods=(void *)gui_methods; 
main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr(); 
csm->csm.state=0; 
csm->csm.unk1=0; 
csm->gui_id=CreateGUI(main_gui); 
} 

void Killer(void){ 
extern void *ELF_BEGIN; 
extern void kill_data(void *p, void (*func_p)(void *)); 
onexit(); 
kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr()); 
// ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN); 
} 

void maincsm_onclose(CSM_RAM *csm) 
{ 
onclose(); 
SUBPROC((void *)Killer); 
} 

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){ 
MAIN_CSM *csm=(MAIN_CSM*)data; 
if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id)) 
csm->csm.state=-3; 
return(1); 
} 

const int minus11=-11; 
unsigned short maincsm_name_body[140]; 

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

int main(char *exename, char *fname){ 
char dummy[sizeof(MAIN_CSM)]; 
if(onstart(exename,fname)) SUBPROC((void *)Killer); 
else CreateCSM(&MAINCSM.maincsm,dummy,0); 
return 0; 
} 

Теперь корректируем (если нужно) файл main.c: 
// Main.c 0.1 
// Demo 3: Пример попроще: Запускаем фоновый процесс, рисуем по таймеру 

#include "E:\ARM\swilib.h" 
extern short screen[132*176]; // Экран 132*176*2 
extern void DrawScreen(); // Функция перерисовки экрана 
void onredraw(void); 

//#define RGB8(R,G,B) (B+(G<<2)+(R<<5)) 
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11)) 

char *buf=0; // Какой-то буфер (для примера выделения памяти) 
int bufsize=10000; // Его размер 
volatile int started=0; // Процесс проверяет флаг и выходит если =0 
int color=0; 

GBSTMR timer; 
void timer_proc(void){ // Функция выполняется по таймеру 10 раз в секунду 
if(started){ 
REDRAW(); // Перерисовать экран 
} 
GBS_StartTimerProc(&timer,262/10,timer_proc); // Стартуем таймер с частотой 10 раз в секунду 
// Он выполняется однократно поэтому его нужно постоянно запускать 
} 

void execute(){ // Фоновый процесс 
started=1; 
while(started){ // Пока нет команды на останов 
onredraw(); // ТОЛЬКО для примера, на деле делаем что-либо еще 
} 
} 

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода. 
// if(!fname) return 1; // Если не задано имя файла выходим 
buf=(char *)malloc(bufsize); // Выделяем память и т.п. 
if(!buf) return 1; // Не получилось - выходим 
// Здесь делаем что-либо 
return 0; 
} 

void oncreate(){ // Создание окна 
SUBPROC((void *)execute); // Запускаем фоновый процесс 
GBS_StartTimerProc(&timer,262/10,timer_proc); // Стартуем таймер с частотой 10 раз в секунду 
} 

void onclose(){ // Закрытие окна 
started=0; // Сигнал на остановку фонового процесса 
GBS_StopTimer(&timer); // Останавливаем таймер 
// Сохраняем конфигурацию если надо 
} 

void onexit(){ // Выход 
if(buf) mfree(buf); // Освобождаем память 
} 

void onredraw(void){ // Перерисовка экрана screen[132*176] 
int i,j; 
for(i=0,j=color++;i<132*176;i++){ 
screen[i]=j++; 
} 
} 

// keycode - код клавиши, pressed - нажата/отпущена/удерживается 
int onkey(unsigned char keycode, int pressed){ // Обработчик клавиш. Вернуть 0 или 1 для выхода 
switch(pressed){ 
case KEY_UP: break; // Клавиша отпущена 
case LONG_PRESS: // Клавиша удерживается долго (повтор) 
case KEY_DOWN: // Клавиша нажата 
switch(keycode){ // Код клавиши 
case RED_BUTTON: return 1; // Выход 
case LEFT_SOFT: case RIGHT_BUTTON: case UP_BUTTON: case ENTER_BUTTON: // Делаем что-либо 
case '0': case '9': case '#': case '*': break; 
default: return 0; 
} 
onredraw(); DrawScreen(); // Перерисовать экран 
} 
return 0; 
} 
//#define MSG_GUI_DESTROYED 152 //для не s75 если у Вас нет в swilib.h 


8. Пример 4. Резидентная программа 
[...] 

9. FAQ 
Собран на основе ответов Rst7 (спасибо ему:) 

- почему в iar cu конструкция char c[100]; int a=*(int*)(c+5) выключает трубу? 
Потому что ты пытаешься читать int по некруглому адресу - проц это посылает нах - генерирует исключение... Если тебе надо такое делать, то читай побайтно и собирай в отдельный инт. 

- обязательно при выходе освобождать всю память по mfree()? 
Всю, которую занял - обязательно 

- как отлаживать эльфы кроме как копировать их на телефон и писать лог? 
Дебаггером Хаосовским... Ищешь BLX R4 в загрузчике эльфов, ставишь туда точку останова и вперед... 

- что делают SUBPROC ? REDRAW ? 
SUBPROC - вызов функции в контексте другого потока с малым приоритетом для того, чтобы не тормозить GUI, если надо что-то долго делать (например в TED\'е грузить текст, в MegaDial\'е искать имена в записной книжке) 
REDRAW - вызвать метод onRedraw отображаемого GUI (можно из контекста процесса-помощника) 

Ответы от cbn: 
- как получить дату/время? 
TDate date; TTime time; 
GetDateTime(&date,&time); 
sprintf(s,"%d:%02d",time.hour,time.min); 
sprintf(ss,"%02d-%02d-%04d",date.day, date.month,date.year); 

- IAR пишет: неизвестная функция div_32a (или адрес ELF_BEGIN) 
К проекту должны быть подключены соответственно файлы div.r79 и func.asm 

- приложение работает слишком медленно - как переписать на асм? 
С переписыванием на асм спешить не стоит - сначала нужно убедиться что си версия работает без ошибок. Наибольшее ускорение дает правильно написанный АЛГОРИТМ, нужно попытаться его улучшить. В компиляторе включить максимальную оптимизация по скорости. 
И уже последний этап - замерить или прикинуть какие части кода выполняются наиболее долго (80% времени проца занимает 20% кода) и переписать их. 

Пример: добавляем в func.asm функцию myfunc(a,b,c,d) 
вставляем ПЕРЕД ELF_BEGIN ее код 
    PUBLIC myfunc 
myfunc: PUSH {R4-R6,LR} 
    ;делаем что-то с R4-R6 (можно до R12) 
    POP {R4-R6,PC} ; Возврат 
    ;или делать BX LR не сохраняя его 
Вызов из Си: 
extern int myfunc(int a,int b,int c, int d); 
myfunc(a,b,c,d); 
Первые 4 параметра передаются соотв. в регистрах R0-R3, остальные через стек. 
Результат возвращается в R0. 
Систему команд АРМ смотрим тут и тут 

- почему на х65-75 не открываются файлы с карточки (MMC)? 
В fopen() должно быть P_READ вместо 0 

- как вывести на экран рисунок bmp? 
См. тут 

- есть ли вирусы на эльфах и как с ними бороться? 
См. тут 

-как портировать имеющиеся исходники в IAR ? 
Сложно. см. тут 

-как отлаживать эльф? 
Несложного отладчика нет :( придумываем сами 
Можно попробовать выводить значение параметра на экран 
char s[128]; sprintf(s,"Значение a= %d",a); ShowMSG(1,(int)s); //или через DrawString(...) 
или писать в лог: #define logsize 10000 
char log[logsize], *ptr=log; 
void debug(char *s){ if(ptr<log+logsize-strlen(s)-3){ 
strcpy(ptr,s); ptr+=strlen(s); *ptr++=0xd; *ptr++=0xa;}} 
а при выходе: fwrite(f,log,ptr-log,&err); 
Если получаем пикофф - исключаем часть функций до тех пор пока не находим кто виновник. 

- как найти все файлы в папке? 
void findlist(char *dir){ //dir - папка, например "0:","0:\\Misc" 
static DIR_ENTRY de; unsigned int err; 
char path[128]; strcpy(path,dir); 
char *ptr=path+strlen(path)+1; 
strcat(path,"\\*.*"); //или "\\*.wav" т.е. то что нужно искать 
if (FindFirstFile(&de,path,&err)){ 
do{ strcpy(ptr,de.file_name); 
//if(isdir(path,&err)) somedir(path); else //если это папка то делаем то-то, иначе 
somefile(path); //делаем с найденным файлом что нам нужно 
}while(FindNextFile(&de,&err)); 
}FindClose(&de,&err);} 

- как из эльфа запустить др. эльф? 
void execelf(char *exename, char *fname){ //fname-параметр (имя файла), передаваемый в эльф 
WSHDR *ws=AllocWS(256); 
str_2ws(ws,exename,strlen(exename)+1); 
ExecuteFile(ws,0,fname); FreeWS(ws);} 

- как воспроизвести стандартный звук? 
Ответ от Geka: PlaySound(1,0,0,n,0) где n-номер станд.звука 

- как воспроизвести звуковой файл? 
Ответ от KreN (спасибо за разъяснения): 
typedef struct{ unsigned int unk1,unk2,unk3,volume;} SFO; 
#pragma swi_number=74 
__swi __arm void PlayFile(int _C,WSHDR* folder,WSHDR* filename,int cepid, int _167,SFO* options); 
void PlayMelody(int type_melody){ 
SFO unk1; WSHDR *ws1=AllocWS(50), *ws2=AllocWS(30); 
str_2ws(ws1,natisq_path,49); 
unk1.unk1=1; unk1.unk2=0; unk1.unk3=0; unk1.volume=3; 
wsprintf(ws2,"message.wav"); 
PlayFile(0xC,ws1,ws2,GBS_GetCurCepid(),0x167,&unk1); 
FreeWS(ws1); FreeWS(ws2);} 
PS(cbn): структура SFO сложнее, со звуком много несовмест. (пикофф) на разных моделях, данных мало... 

- как работать с float,double,long long,... (не хватает библ., пишет что не найдены div_32a, div_64a, doubleToLong, float...)? 
Kren: В меню Project->Options->Library Configuration выбрать Normal. Нужные библ. подкл. автоматически. 
cbn: век живи - век учись (не знал). Помните что ввиду отсутствия сопроцессора все операции с float,double эмулируются через функции и работают _медленно_. 


Автор инструкции: Воробьев Александр (cbn)   Сайт   Почта
	int f;
int f2;
char *buffer;
  if((f=fopen(ptr,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
     {ShowMSG(1,(int)"Прочитали");
      buffer = malloc(0x6);
      lseek(f, 0xD, S_SET, &err, &err);
      fread32(f, buffer, 0x60, &err);
      
     }
  else ShowMSG(1,(int)"Can't open");
  
  if( (f2=fopen("0:\\z1.txt",A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE,&err))!=-1) //Создаем выходной файл
     { ShowMSG(1,(int)"Create");
       fwrite32(f2,buffer,0x60,&err);
       fclose(f2,&err);
     }
  else ShowMSG(1,(int)"Can't creat");
  fclose(f, &err);