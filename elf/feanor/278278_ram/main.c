#include "..\inc\swilib.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

WSHDR *ws;

GBSTMR timer;

void timer_proc(void){REDRAW();GBS_StartTimerProc(&timer,216,timer_proc);}

int base = 0xA0000000;
char *ram=(char*)0xA0000000;
//char *ff=(char*)0xA0000000;
//char *ports=(char*)0xA8000000;


long i;
int x,y;
int mcur;
int xlimit=4;
int scr_w,scr_h;

//Flags
int menu=0;
  //0 -standart
  //1 -menu
  //2 -set addr
  //3 -edit byte
  //4 -lib expl
  //5 -ports





int full=0;

unsigned int libn=2;

int setx;
int sety;

void seti(int addr)
{ 
  if(setx==0 && base==0xA0000000) {sety=sety%2;}
  if(setx==0 && base==0xA8000000) {sety=8;}
  if(setx==1 && base==0xA8000000) {sety=sety%8;}
  
  
  DrawRoundedFrame(10,45,121,95,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  char addrs[9];
  sprintf(addrs,"%08X",addr+base/*+(1<<(4*(6-setx)))*/); 
  
  wsprintf(ws,"%c ",addrs[0]);
  DrawString(ws,25,50,115,172,3,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c  ",addrs[1]);
  DrawString(ws,35,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==0)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c  ",addrs[2]);
  DrawString(ws,45,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==1)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c    ",addrs[3]);
  DrawString(ws,55,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==2)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c    ",addrs[4]);
  DrawString(ws,65,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==3)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c     ",addrs[5]);
  DrawString(ws,75,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==4)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c      ",addrs[6]);
  DrawString(ws,85,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==5)?8:4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%c       ",addrs[7]);
  DrawString(ws,95,50,115,172,3,0,GetPaletteAdrByColorIndex((setx==6)?8:4),GetPaletteAdrByColorIndex(23));
  
  
  //wsprintf(ws,"%X ",sety<<((7-setx)) );
  //DrawString(ws,60,70,115,172,3,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
 // i=i+(1<<(4*(6-setx)));
}

int lib(int j)
{
  int n;
  unsigned char *lPtr=(unsigned char*)0xA0FD4000; //Начальный указатель BFL(смещение) 
  char func[4];
  long a;

  for(n=0;n<4;n++)
   {
    *(func+n)=*(lPtr+(j-1)*4+n); //Если еще есть то пишем ;)
   }
  
  a=func[3]*0x1000000+func[2]*0x10000+func[1]*0x100+func[0];
  //wsprintf(ws, "ff: %02X%02X%02X%02X  %X",func[3],func[2],func[1],func[0],a); 
  //DrawRoundedFrame(1,1,132,176,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1)); 
  //DrawString(ws,20,25,119,76,7, 0, GetPaletteAdrByColorIndex(4), GetPaletteAdrByColorIndex(1));
return(a); 
}



void runmenu()
{
  switch(mcur)
    {
    case 0: { if(base==0xA0000000) {base=0xA8000000; ram=(char*)0xA8000000;} else {base=0xA0000000; ram=(char*)0xA0000000;} }; break;
    case 1:  menu=(menu==0)?4:0;  break;
    case 2:  menu=(menu==0)?5:0;   break;
    }
  REDRAW();
}





void drawmenu()
{

  
  
  DrawRoundedFrame(0,45,90,175,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  
  DrawRoundedFrame(2,47+mcur*14,88,60+mcur*14,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%t","Память");
  DrawString(ws,4,48,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  wsprintf(ws,"%s",(base==0xA0000000)?"FF":"RAM");
  DrawString(ws,4,48,86,172,7,4,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%t","Lib expl.");
  DrawString(ws,4,62,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  wsprintf(ws,"%i",libn);
  DrawString(ws,4,62,86,172,7,4,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%t","I/0 ports");
  DrawString(ws,4,76,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%t","Карта рамы");
  DrawString(ws,4,90,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  //wsprintf(ws,"%i",i);
  //DrawString(ws,4,62,86,172,7,4,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws,"%t","Cохр. область");
  DrawString(ws,4,104,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
}




int GetColor(int rbyte)
{
  int cl=4;
  
    switch (rbyte)
    {
    case 0x00: case 0xFF: cl=22; break;
    case 0xB5: cl=7;break;
    }
    
  return(cl);
}



int ex=0;
int ey;


void edit(long addr)
{
  
  char v[3];
  sprintf(v,"%02X*",ey);
  DrawRoundedFrame(40,45,81,95,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  
  wsprintf(ws," %c",v[0]);
  DrawString(ws,50,55,128,172,3,0,GetPaletteAdrByColorIndex((ex==0)?8:4),GetPaletteAdrByColorIndex(23));
  wsprintf(ws," %c ",v[1]);
  DrawString(ws,60,55,128,172,3,0,GetPaletteAdrByColorIndex((ex==1)?8:4),GetPaletteAdrByColorIndex(23));
}

void fullmode()
{
  char wstr[8]; 
  
  if (x<0) {i=i-xlimit*1; x=0;}
  if (x>3) {i=i+xlimit*1; x=3;}
  int yu,yi=0; 

 for (yu=0; yu!=9; yu++)
 {
   sprintf(wstr, "%X",(i+base+yu*xlimit));   
   wsprintf(ws, "%c%c:",wstr[6],wstr[7]); 
    DrawString(ws,2,20+yu*15,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
   for (yi=0; yi!=xlimit; yi++)
    {

      wsprintf(ws, "%02X",ram[i+yu*4+yi]);
      DrawString(ws,17+yi*14,20+yu*15,128,172,7,(yu==x && yi==y)?256:0,GetPaletteAdrByColorIndex( GetColor(ram[i+yu*4+yi]) ),GetPaletteAdrByColorIndex(23));   
      
      //wsprintf(ws, "%c",ram[i+yu*4+yi]);
      //DrawString(ws,90+yi*8,20+yu*15,128,172,7,0,GetPaletteAdrByColorIndex( 4 ),GetPaletteAdrByColorIndex(23)); 
      
    }
 }
 
wsprintf(ws, "%3.3X: ",(i+base+y+x*xlimit));
DrawString(ws,5,5,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));


if (menu==2) {seti(i);}
if (menu==3) {edit(i+x*4+y);}
}


void viewmode()
{
  char wtr[9];
  
  if (x<0) {i=i-xlimit*1; x=0;}
  if (x>3) {i=i+xlimit*1; x=3;} 
   int yu,yi=0; 

 for (yu=0; yu!=9; yu++)
 {
  
   sprintf(wtr, "%X-",(base+i+yu*xlimit));   
   wsprintf(ws, "%c%c%c%c:",wtr[4],wtr[5],wtr[6],wtr[7]);
    
    DrawString(ws,2,20+yu*15,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
   for (yi=0; yi!=xlimit; yi++)
    {

      wsprintf(ws, "%02X",ram[i+yu*4+yi]);
      DrawString(ws,30+yi*14,20+yu*15,128,172,7,(yu==x && yi==y)?256:0,GetPaletteAdrByColorIndex( GetColor(ram[i+yu*4+yi]) ),GetPaletteAdrByColorIndex( 23 ));   
      
      wsprintf(ws, "%c",ram[i+yu*4+yi]);
      DrawString(ws,90+yi*8,20+yu*15,128,172,7,(yu==x && yi==y)?256:0,GetPaletteAdrByColorIndex( 4 ),GetPaletteAdrByColorIndex( 23 )); 
    }
 }
 
wsprintf(ws, "%08X:",(i+base+y+x*xlimit));
DrawString(ws,5,5,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));

wsprintf(ws, "0x%02X %i %c ",ram[i+x*4+y],ram[i+x*4+y],ram[i+x*4+y]);
DrawString(ws,5,5,128,172,7,4,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));

if (menu==2) {seti(i);}
if (menu==3) {edit(i+x*4+y);}
}



short portx;

void ports()
{
  if (portx==-1) {portx=0;} 
  DrawRoundedFrame(10,40,121,100,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  
  char *prt=(char*)0xF0000000;
// char *m=(char*)0xF0000000; //0x0014C004 EBU                                    --
// char *m=(char*)0xF1000000; //0x000044E2 USART0                                 ok!
// char *m=(char*)0xF1100000; //0x00004525 SSC0                                   ok!                                  
// char *m=(char*)0xF1300000; //0xF000C010 SIM Interface                          ok!
// char *m=(char*)0xF1800000; //0x000044E2 USART1                                 ok!
// char *m=(char*)0xF1B00000; //0xF043C000 DIF_SSC? (display SSC interface)       ok!
// char *m=(char*)0xF2200000; //0x???????? USB??
// char *m=(char*)0xF2800000; //0x0031C001 ?????                                  ok!
// char *m=(char*)0xF4000000; //0x00005003 PWM0?                                  ok!                                
// char *m=(char*)0xF4100000; //0x00005003 PWM1?                                  ok! 
// char *m=(char*)0xF4300000; //0xF023C000 PCL                                    --
// char *m=(char*)0xF4400000; //0xF040C000 SCU                                    --
// char *m=(char*)0xF4500000; //0x???????? PLL/CLKGEN??                           --
// char *m=(char*)0xF4600000; //0x???????? ?????                                  --
// char *m=(char*)0xF4700000; //0x???????? RTC                                    --
// char *m=(char*)0xF4800000; //0x00004604 I2C                                    ok!
// char *m=(char*)0xF4900000; //0x0001C002 GPTU0                                  --
// char *m=(char*)0xF4A00000; //0x0001C002 GPTU1                                  --                                  
// char *m=(char*)0xF4B00000; //0x0000C002 STM(System Timer)                      --
// char *m=(char*)0xF4C00000; //0xF024C010 ?????
// char *m=(char*)0xF4D00000; //0xF046C000 KEYPAD?                                ok!
// char *m=(char*)0xF6000000; //0xF022C010 DSP??                                  --
// char *m=(char*)0xF6001000; //---------- DSP Shared RAM??
// char *m=(char*)0xF6200000; //0xF003C010 GSM Cypher Unit???
// char *m=(char*)0xF6300000; //0xF004C000 ?????
// char *m=(char*)0xF6400000; //0xF021C000 GSM_TPU_UNIT???
// char *m=(char*)0xF6401000; //---------- DSP??
  
  
/*  0xF1000000 0x000044E2 USART0   Регистры USART (universal synchronous/asynchronous reciever/transmitter).одинаковы для обоих устройств - USART0 и USART1
      F1000000 USART0_CLC       USART - IrDA/BT (?)
      F1000004 USART0_PISEL 
      F1000008 USART0_ID 
      F1000010 USART0_CON 
      F1000014 USART0_BG 
      F1000018 USART0_FDV 
      F100001C USART0_PMW 
      F1000020 USART0_TXB 
      F1000024 USART0_RXB 
      F1000030 USART0_ABCON 
      F1000034 USART0_ABSTAT 
      F1000040 USART0_RXFCON 
      F1000044 USART0_TXFCON 
      F1000048 USART0_FSTAT 
      F1000068 USART0_FCSTAT 
      F1000070 USART0_ICR
 0xF1100000 0x00004525 SSC0
 0xF1300000 0xF000C010 SIM Interface
 0xF1800000 0x000044E2 USART1
 0xF1B00000 0xF043C000 DIF_SSC? (display SSC interface)
 0xF2200000 0x???????? USB?? 
 0xF2800000 0x0031C001 ?????
 0xF4000000 0x00005003 PWM0?
 0xF4100000 0x00005003 PWM1?
  
  
  
   0xF4800000 0x00004604 I2C
      F4800000 I2C_CLC
      F4800004 I2C_PISEL
      F4800008 I2C_ID 
      F4800010 I2C_SYSCON 
      F4800014 I2C_BUSCON 
      F4800018 I2C_RTB 
      F4800020 I2C_WHBSYSCON
*/
  
  
  
switch(portx)
{
 case 1: wsprintf(ws, "\n\n\n0xF1000000\n%02X%02X%02X%02X\n USART0_CLC",prt[0x1000000],prt[0x1000001],prt[0x1000002],prt[0x1000003]);   break;
 case 2: wsprintf(ws, "\n\n\n0xF1000004\n%02X%02X%02X%02X\n USART0_PISEL ",prt[0x1000004],prt[0x1000005],prt[0x1000006],prt[0x1000007]);   break;
 case 3: wsprintf(ws, "\n\n\n0xF1000008\n%02X%02X%02X%02X\n USART0_ID ",prt[0x1000008],prt[0x1000009],prt[0x100000A],prt[0x100000B]);   break;
 case 4: wsprintf(ws, "\n\n\n0xF1000010\n%02X%02X%02X%02X\n USART0_CON",prt[0x1000010],prt[0x1000011],prt[0x1000012],prt[0x1000013]);   break;
 case 5: wsprintf(ws, "\n\n\n0xF1000014\n%02X%02X%02X%02X\n USART0_BG ",prt[0x1000014],prt[0x1000015],prt[0x1000016],prt[0x1000017]);   break;
 case 6: wsprintf(ws, "\n\n\n0xF1000018\n%02X%02X%02X%02X\n USART0_FDV ",prt[0x1000018],prt[0x1000019],prt[0x100001A],prt[0x100001B]);   break;
 case 7: wsprintf(ws, "\n\n\n0xF100001C\n%02X%02X%02X%02X\n USART0_PMW ",prt[0x100001C],prt[0x100001D],prt[0x100001E],prt[0x100001F]);   break;
 case 8: wsprintf(ws, "\n\n\n0xF1000020\n%02X%02X%02X%02X\n USART0_TXB ",prt[0x1000020],prt[0x1000021],prt[0x1000022],prt[0x1000023]);   break;
 case 9: wsprintf(ws, "\n\n\n0xF1000024\n%02X%02X%02X%02X\n USART0_RXB ",prt[0x1000024],prt[0x1000024],prt[0x1000026],prt[0x1000027]);   break;
 case 10: wsprintf(ws, "\n\n\n0xF1000030\n%02X%02X%02X%02X\n USART0_ABCON  ",prt[0x1000030],prt[0x1000031],prt[0x1000032],prt[0x1000033]);   break;
 case 11: wsprintf(ws, "\n\n\n0xF1000034\n%02X%02X%02X%02X\n USART0_RXFCON ",prt[0x1000034],prt[0x1000035],prt[0x1000036],prt[0x1000037]);   break;
 case 12: wsprintf(ws, "\n\n\n0xF1000040\n%02X%02X%02X%02X\n USART0_TXFCON ",prt[0x1000040],prt[0x1000041],prt[0x1000042],prt[0x1000043]);   break;
 case 13: wsprintf(ws, "\n\n\n0xF1000048\n%02X%02X%02X%02X\n USART0_FSTAT ",prt[0x1000048],prt[0x1000049],prt[0x100004A],prt[0x100004B]);   break;
 case 14: wsprintf(ws, "\n\n\n0xF1000068\n%02X%02X%02X%02X\n USART0_FCSTAT ",prt[0x1000068],prt[0x1000069],prt[0x100006A],prt[0x100006B]);   break;
 case 15: wsprintf(ws, "\n\n\n0xF1000070\n%02X%02X%02X%02X\n USART0_ICR ",prt[0x1000070],prt[0x1000071],prt[0x1000072],prt[0x1000073]);   break;
 
 case 16: wsprintf(ws, "\n\n\n0xF1100000\n%02X%02X%02X%02X\n SSC0 -1",prt[0x1100000],prt[0x1100001],prt[0x1100002],prt[0x1100003]);   break;
 case 17: wsprintf(ws, "\n\n\n0xF1100004\n%02X%02X%02X%02X\n SSC0 -2",prt[0x1100004],prt[0x1100005],prt[0x1100006],prt[0x1100007]);   break;
 case 18: wsprintf(ws, "\n\n\n0xF1100008\n%02X%02X%02X%02X\n SSC0 -3",prt[0x1100008],prt[0x1100009],prt[0x110000A],prt[0x110000B]);   break;
 case 19: wsprintf(ws, "\n\n\n0xF1300000\n%02X%02X%02X%02X\n SIM Interface -1",prt[0x1300000],prt[0x1300001],prt[0x1300002],prt[0x1300003]);   break;
 case 20: wsprintf(ws, "\n\n\n0xF1300004\n%02X%02X%02X%02X\n SIM Interface -2",prt[0x1300004],prt[0x1300005],prt[0x1300006],prt[0x1300007]);   break;
 case 21: wsprintf(ws, "\n\n\n0xF1300008\n%02X%02X%02X%02X\n SIM Interface -3",prt[0x1300008],prt[0x1300009],prt[0x130000a],prt[0x130000b]);   break;
 case 22: wsprintf(ws, "\n\n\n0xF1B00000\n%02X%02X%02X%02X\n DIF_SSC -1",prt[0x1B00000],prt[0x1B00001],prt[0x1B00002],prt[0x1B00003]);   break;
 case 23: wsprintf(ws, "\n\n\n0xF1B00004\n%02X%02X%02X%02X\n DIF_SSC -2",prt[0x1B00004],prt[0x1B00005],prt[0x1B00006],prt[0x1B00007]);   break;
 case 24: wsprintf(ws, "\n\n\n0xF1B00008\n%02X%02X%02X%02X\n DIF_SSC -3",prt[0x1B00008],prt[0x1B00009],prt[0x1B0000A],prt[0x1B0000B]);   break;

 case 25: wsprintf(ws, ">>>");   break;
 
 case 1+25: wsprintf(ws, "\n\n\n0xF1800000\n%02X%02X%02X%02X\n USART1_CLC",prt[0x1800000],prt[0x1800001],prt[0x1800002],prt[0x1800003]);   break;
 case 2+25: wsprintf(ws, "\n\n\n0xF1800004\n%02X%02X%02X%02X\n USART1_PISEL ",prt[0x1800004],prt[0x1800005],prt[0x1800006],prt[0x1800007]);   break;
 case 3+25: wsprintf(ws, "\n\n\n0xF1800008\n%02X%02X%02X%02X\n USART1_ID ",prt[0x1800008],prt[0x1800009],prt[0x180000A],prt[0x180000B]);   break;
 case 4+25: wsprintf(ws, "\n\n\n0xF1800010\n%02X%02X%02X%02X\n USART1_CON",prt[0x1800010],prt[0x1800011],prt[0x1800012],prt[0x1800013]);   break;
 case 5+25: wsprintf(ws, "\n\n\n0xF1800014\n%02X%02X%02X%02X\n USART1_BG ",prt[0x1800014],prt[0x1800015],prt[0x1800016],prt[0x1800017]);   break;
 case 6+25: wsprintf(ws, "\n\n\n0xF1800018\n%02X%02X%02X%02X\n USART1_FDV ",prt[0x1800018],prt[0x1800019],prt[0x180001A],prt[0x180001B]);   break;
 case 7+25: wsprintf(ws, "\n\n\n0xF180001C\n%02X%02X%02X%02X\n USART1_PMW ",prt[0x180001C],prt[0x180001D],prt[0x180001E],prt[0x180001F]);   break;
 case 8+25: wsprintf(ws, "\n\n\n0xF1800020\n%02X%02X%02X%02X\n USART1_TXB ",prt[0x1800020],prt[0x1800021],prt[0x1800022],prt[0x1800023]);   break;
 case 9+25: wsprintf(ws, "\n\n\n0xF1800024\n%02X%02X%02X%02X\n USART1_RXB ",prt[0x1800024],prt[0x1800024],prt[0x1800026],prt[0x1800027]);   break;
 case 10+25: wsprintf(ws, "\n\n\n0xF1800030\n%02X%02X%02X%02X\n USART1_ABCON  ",prt[0x1800030],prt[0x1800031],prt[0x1800032],prt[0x1800033]);   break;
 case 11+25: wsprintf(ws, "\n\n\n0xF1800034\n%02X%02X%02X%02X\n USART1_RXFCON ",prt[0x1800034],prt[0x1800035],prt[0x1800036],prt[0x1800037]);   break;
 case 12+25: wsprintf(ws, "\n\n\n0xF1800040\n%02X%02X%02X%02X\n USART1_TXFCON ",prt[0x1800040],prt[0x1800041],prt[0x1800042],prt[0x1800043]);   break;
 case 13+25: wsprintf(ws, "\n\n\n0xF1800048\n%02X%02X%02X%02X\n USART1_FSTAT ",prt[0x1800048],prt[0x1800049],prt[0x180004A],prt[0x180004B]);   break;
 case 14+25: wsprintf(ws, "\n\n\n0xF1800068\n%02X%02X%02X%02X\n USART1_FCSTAT ",prt[0x1800068],prt[0x1800069],prt[0x180006A],prt[0x180006B]);   break;
 case 15+25: wsprintf(ws, "\n\n\n0xF1800070\n%02X%02X%02X%02X\n USART1_ICR ",prt[0x1800070],prt[0x1800071],prt[0x1800072],prt[0x1800073]);   break;
 
 case 41: wsprintf(ws, "\n\n\n0xF4000000\n%02X%02X%02X%02X\n PWM0 -1",prt[0x4000000],prt[0x4000001],prt[0x4000002],prt[0x4000003]);   break;
 case 42: wsprintf(ws, "\n\n\n0xF4000004\n%02X%02X%02X%02X\n PWM0 -2",prt[0x4000004],prt[0x4000005],prt[0x4000006],prt[0x4000007]);   break;
 case 43: wsprintf(ws, "\n\n\n0xF4000008\n%02X%02X%02X%02X\n PWM0 -3",prt[0x4000008],prt[0x4000009],prt[0x400000A],prt[0x400000B]);   break;
 
 
 case 44: wsprintf(ws, "\n\n\n0xF4100000\n%02X%02X%02X%02X\n PWM1 -1",prt[0x4100000],prt[0x4100001],prt[0x4100002],prt[0x4100003]);   break;
 case 45: wsprintf(ws, "\n\n\n0xF4100004\n%02X%02X%02X%02X\n PWM1 -2",prt[0x4100004],prt[0x4100005],prt[0x4100006],prt[0x4100007]);   break;
 case 46: wsprintf(ws, "\n\n\n0xF4100008\n%02X%02X%02X%02X\n PWM1 -3",prt[0x4100008],prt[0x4100009],prt[0x410000A],prt[0x410000B]);   break;

 case 47: wsprintf(ws, "\n\n\n0xF4D00000\n%02X%02X%02X%02X\n KEYPAD -1",prt[0x4D00000],prt[0x4D00001],prt[0x4D00002],prt[0x4D00003]);   break;
 case 48: wsprintf(ws, "\n\n\n0xF4D00004\n%02X%02X%02X%02X\n KEYPAD -2",prt[0x4D00004],prt[0x4D00005],prt[0x4D00006],prt[0x4D00007]);   break;
 case 49: wsprintf(ws, "\n\n\n0xF4D00008\n%02X%02X%02X%02X\n KEYPAD -3",prt[0x4D00008],prt[0x4D00009],prt[0x4D0000A],prt[0x4D0000B]);   break;
} 
  
DrawString(ws,5,5,116,172,3,2,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
}


void viewlib()
{
  DrawRoundedFrame(10,45,121,95,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(ws, "Func %i: %08X",libn,lib(libn) ); 
  DrawString(ws,15,55,116,172,3,2,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
}

static void OnRedraw(MAIN_GUI *data)
{
  LockSched();
  DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));  
  
  if (menu==4)
  {viewlib();} 
  else
  {
  
  
  if(  (base==0xA0000000 && i<0x1FFFFFF && i>-1)||(base==0xA8000000 && i<0x7FFFFF && i>-1)  )
  {
  if (full==1) {xlimit=8; fullmode();} else {xlimit=4; viewmode();}
  
  
  
  
  if (menu==1) {drawmenu();} 
  } 
  else
  {
    DrawRoundedFrame(55,20,75,100,0,0,3,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    DrawRoundedFrame(55,105,75,125,0,0,3,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    if (menu==2) {seti(i);}
  }
  
  if (menu==5) ports();
  
  }
 UnlockSched();
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
#ifdef ELKA
  DisableIconbar(1);
#endif
  GBS_StartTimerProc(&timer,2000,timer_proc);  
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
  GBS_StopTimer(&timer);
  FreeWS(ws);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconbar(1);
#endif
  data->gui.state=2;
  DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  
 if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
         {
           switch(msg->gbsmsg->submess)
          {
          case RED_BUTTON: if(menu==0) {return(1);} else menu=0; REDRAW(); break;
            
          case '9': case 0x0D: if (menu==0) {i=i+xlimit*8; REDRAW();}
                               if (menu==4) {libn=libn+10; REDRAW();} 
                               break;   
                               
          case '3': case 0x0E: if (menu==0) {i=(i<0x40)?i:i-xlimit*8; REDRAW();}
                               if (menu==3 && base==0xA8000000){ey=(1+ey)%0x100;  REDRAW();} 
                               
                               break; 
            
          case '8': case 0x3C: if (menu==0) {x++; REDRAW();}            
                               if (menu==1) {mcur=(mcur+1)%9; REDRAW();}    
                               if (menu==2) {i=i+(1<<(4*(6-setx))); REDRAW();}   
                               break; 
                               
          case '2': case 0x3B: if (menu==0) {x=(i==0)?x:x-1; REDRAW();} 
                               if (menu==1) {mcur=(mcur+8)%9; REDRAW();}    
                               if (menu==2) {i=i-(1<<(4*(6-setx))); REDRAW();}   
                               break;
            
          case '4': case 0x3D: if(menu==0) {y=(y+xlimit-1)%xlimit; REDRAW();}
                               if(menu==2){setx=(setx+6)%7; REDRAW();}
                               if(menu==3 && base==0xA8000000){ey=(0x10+ey)%0x100; REDRAW();}
                               if(menu==4){libn--; REDRAW();} 
                               if(menu==5){portx--; REDRAW();}
                               break;
          
          
          case '6': case 0x3E: if(menu==0) {y=(y+1)%xlimit; REDRAW();}
                               if(menu==2){setx=(setx+1)%7; REDRAW();} 
                               if(menu==3 && base==0xA8000000){ey=(1+ey)%0x100;  REDRAW();} 
                               if(menu==4){libn++; REDRAW();}
                               if(menu==5){portx++; REDRAW();}
                               break;
         
          case '7': if(menu==4){libn=libn-10; REDRAW();}  break;
          
          case GREEN_BUTTON:   if(base==0xA0000000) {base=0xA8000000; ram=(char*)0xA8000000;} else {base=0xA0000000; ram=(char*)0xA0000000;} ; REDRAW(); break;
            
          case 0x01: menu=(menu==0)?1:0; REDRAW(); break;
          case 0x04: menu=(menu==0)?2:0; REDRAW(); break; 
          
          
          case '5': if (menu==0  && base==0xA8000000) {menu=3; ey=ram[i+x*4+y]; edit(i+x*4+y); REDRAW(); break;}
                    if (menu==1) {runmenu(); REDRAW();}
                    if (menu==2) {i=i+(1<<(4*(6-setx))); REDRAW();}
                    if (menu==3) {ram[i+x*4+y]=ey; menu=0; REDRAW();}
                    if (menu==4){if(lib(libn)<0xA8000000) {i=lib(libn)-0xA0000000; base=0xA0000000;} else {i=lib(libn)-0xA8000000; base=0xA8000000;} menu=0; REDRAW();}
                    break;
           
           
          case '*': if (menu==0) {full=(full+1)%3; REDRAW();} break;
          
          case '0': REDRAW();  break;
          
          case '1': if(menu==3 && base==0xA8000000){ey=(ey-0x10)%0x100; REDRAW();}  
                    break;
          }
         }

  return(0);
}


extern void kill_data(void *p, void (*func_p)(void *));//Эта функция убивает эльф и освобождает память

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)
{
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
//  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}


void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем памчть если нужно и т.п.
{
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

static const struct//это структура цсм,разбираться не надо:)
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


void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MemView");
  FreeWS(ws);
}


int main(char *exename, char *fname)
{
  
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
  UnlockSched();
  scr_w=ScreenW();
  scr_h=ScreenH();
  ws = AllocWS(256);
  
  return 0;
}
