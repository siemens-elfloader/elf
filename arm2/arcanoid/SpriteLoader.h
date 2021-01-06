#include <swilib.h>
//палево млин,но чем-то лучше способа прорисовки бонусов :)
//вполне неплохо отлажено,на небольших спрайтах не тормозит..надеюсь кому-то пригодится


//сперва грузим при старте проги сами первичные спрайты,затем юзаем InitSprite для инициализации спрайта
//и DrawSprites для прорисовки
//при выходе из проги чистим загруженные спрайты

typedef struct
{
  IMGHDR **img;
  char active;
  short x,y;
  char num; //кол-во картинок в анимешке
  short time; //время между кадрами,для переключалки.Задается по стандарту в 2
  char sw; //переключалка кадров,чисто статичный объект,ничего интересного
  int counter; //счетчик для все той-же переключалки,опять таки ничего интересного
  short N; //номер спрайта в буфере
  short ovr; // кол-во зацикливаний анимации спрайта
  
  short ex,ey; //конечные координаты движения спрайта
  signed char x_incr,y_incr; //инкременты по иксам и игрекам
  char isMoving; //есть ли надобность двигацца?
  short uid; //id,заданный юзером.Например можно инициализировать группу спрайтов с одним uid,а потом допустим нам надо отловить ИМЕННО их координаты.Мы по этому uиду отыскиваем спрайты через GetSprite и в цикеле напр. отлавливаем :)
  short udv; //User Defined Variable
}TSPRITE; //неплохо бы эту структуру сделать статичной для SpriteLoader'a,а для инита спрайтов  сделать поменьше


#define MAX_SPRITES 128
extern TSPRITE *sprites;



//не забываем про MAX_SPRITES!
void DrawSprites(); //прорисовка
void LoadSprite(char *name,char num,short time,TSPRITE *sprite); //загрузка из файла
void FreeSprite(TSPRITE *sprite); //очистка загруженного из файла спрайта
short InitSprite(TSPRITE *sprite,short uid,short x,short y,short repeat_num); //инициализация перед прорисовкой
short InitMSprite(TSPRITE *sprite,short uid,short x,short y,signed char x_incr,signed char y_incr,short ex,short ey); //движущийся спрайт,по окнчании движения делает садо-мазо :)

void SetSpriteCoordinaties(short N,short x,short y); //задаем координаты спрайту с известным номером в буфере(номер возвращает InitSprite)
void GetSpriteCoordinaties(short N,short *x,short *y); //получаем координаты спрайта с известным номером
short GetSpriteWidth(short N);
short GetSpriteHeight(short N);
void StopSprite(short N); //киляем рисующийся спрайт
void DumpActiveSprites();

TSPRITE *GetSprite(short num);

void InitSpriteBuffer();
void DeinitSpriteBuffer();

//пример юзания
/*
TSPRITE my_sprite1;
TSPRITE my_sprite2;

void StartProgram() //OnCreate
{
  InitSpriteBuffer();
  LoadSprite("images\\anim1.png",4,&my_sprite1);
  LoadSprite("images\\anim2.png",6,&my_sprite2);
}

void RedrawScreen() //нуждается в зацикливании по таймеру
{
  DrawSprites();
}

void FreeMemory() //OnClose
{
  DeinitSpriteBuffer();
  FreeSprite(&my_sprite1);
  FreeSprite(&my_sprite2);
}

void Activate1()
{
  //в принципе можно и в цикле инициализировать массив спрайтов,разве что тормозить может
  InitSprite(&my_sprite1,100,100);
  InitSprite(&my_sprite2,200,200);
}*/


