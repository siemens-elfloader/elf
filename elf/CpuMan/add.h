//#include "..\inc\swilib.h"
char st[32];
static const char cl[]={0xFF,0xFF,0xFF,0x00};
void *day(void)
{ char *dayss[8]={" ","Понедельник","Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье"},
   *mounthss[13]={" ","Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
  TDate date;
  TTime time;
  WSHDR *ws=AllocWS(256);
  GetDateTime(&date,&time);
  int dayy=date.day;
  while(dayy>7)
  {dayy=dayy-7;   
  }
  char *sc=date.day<10?"0":"";
  wsprintf(ws,"Date  %s,%s%d %s",dayss[dayy],sc,date.day,mounthss[date.month]);
  DrawString(ws,20,20,60,60,1,2,cl,cl);
return 0;
}

/*static const char red[]={0xFF,0x00,0x00,0x99};
static const char white[]={0xFF,0xFF,0xFF,0x99};
static const char black[]={0x00,0x00,0x00,0x90};
static const char proz[]={0xFF,0xFF,0xFF,0x00};
void *time()
{ TDate date;
  TTime time;
  WSHDR *ws=AllocWS(256);
  GetDateTime(&date,&time);
 //char *s=time.min<10?"0":"";
  DrawRoundedFrame(0,40,131,60,0,0,1,black,black);
  wsprintf(ws,"Время %d:%d:%d",time.hour,time.min,time.sec);
  DrawString(ws,0,40,131,60,1,0,red,white); 
return 0;
}
void *day()
{ char *dayss[8]={" ","Понедельник","Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье"},
   *mounthss[13]={" ","Январь","Февраль","Март","Апрель","Май","Июня","Июля","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
  TDate date;
  TTime time;
  WSHDR *ws=AllocWS(256);
  GetDateTime(&date,&time);
  int dayy=date.day;
  while(dayy>7)
  {dayy=dayy-7;   
  }
//  char *sc=date.day<10?"0":"";
  DrawRoundedFrame(0,0,131,175,0,0,1,black,black);
  wsprintf(ws,"%s,%d %s %dг.",dayss[dayy],date.day,mounthss[date.month],date.year);
  DrawString(ws,0,0,131,40,1,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
return 0;
}
unsigned int* ErrorNumber;
void *mamory()
{    DrawRoundedFrame(0,0,131,175,0,0,1,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
     WSHDR *ws=AllocWS(256);
     wsprintf(ws,"Свободное место:");
     DrawString(ws,2,2,131,175,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
     int t0 = GetTotalFlexSpace(0, ErrorNumber)/1024;
     int t1 = GetTotalFlexSpace(1, ErrorNumber)/1024;
     int t2 = GetTotalFlexSpace(2, ErrorNumber)/1024;
     int t4 = GetTotalFlexSpace(4, ErrorNumber)/1024;
         
     int f0 = GetFreeFlexSpace(0, ErrorNumber)/1024;
     int f1 = GetFreeFlexSpace(1, ErrorNumber)/1024;
     int f2 = GetFreeFlexSpace(2, ErrorNumber)/1024;
     int f4 = GetFreeFlexSpace(4, ErrorNumber)/1024;
     
     int p0 = (f0*100)/t0;
     int p1 = (f1*100)/t1;
     int p2 = (f2*100)/t2;
     int p4 = (f4*100)/t4;
     
     char* c=(t4==0)?"N/A":" ";
     wsprintf(ws, "0:%d Kb %d Kb [%d%%]\n1:%d Kb %d Kb [%d%%]\n2:%d Kb %d Kb [%d%%]\n4:%d Kb %d Kb [%d %%] %s",t0,f0,p0,t1,f1,p1,t2,f2,p2,t4,f4,p4,c);
  DrawString(ws,2,25,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
   DrawRoundedFrame(10,100,110,105,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
DrawRoundedFrame(10,100,10+p0,105,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(4)); 
   DrawRoundedFrame(10,110,110,115,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
DrawRoundedFrame(10,110,10+p1,115,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(4)); 
   DrawRoundedFrame(10,120,110,125,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
DrawRoundedFrame(10,120,10+p2,125,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(4)); 
if(t4!=0)
{
   DrawRoundedFrame(10,130,110,135,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
DrawRoundedFrame(10,130,10+p4,135,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(4)); 
}
return 0;
}

void *net()
{ RAMNET *rn=RamNet();
  char* std;
  WSHDR *ws=AllocWS(128);
  DrawRoundedFrame(0,0,131,175,0,0,1,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  if (rn->ch_number>=255) std="DCS"; else {if (rn->ch_number>=128) std="EGSM"; else std="GSM";};
  wsprintf(ws, "Network: \n RX: %d  RXAM: %d\n  [%d-%d]:%d \n C1:%d C2:%d ??: %d \n %s",rn->power,(rn->ch_number>=255)?rn->power+rn->c2:rn->power+rn->c1,rn->ci,rn->lac,rn->ch_number,rn->c1,rn->c2,rn->unk2, std);
  DrawString(ws,2,2,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
return 0;
}    
void *neigbours()
{   RAMNET *rn=RamNet();
    RAMNET *rn1=RamNet()+1;
    RAMNET *rn2=RamNet()+2;
    RAMNET *rn3=RamNet()+3;
    RAMNET *rn4=RamNet()+4;
    RAMNET *rn5=RamNet()+5;
    RAMNET *rn6=RamNet()+6;
    WSHDR *ws=AllocWS(128);
  DrawRoundedFrame(0,0,131,175,0,0,1,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(ws, "Neighbours");
  DrawString(ws,2,2,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "M[%d%s]:%i-%i-%i",rn->power,(rn->power<100)?"dB":"d",rn->ci,rn->lac,rn->ch_number);
  DrawString(ws,2,15,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "1[%d%s]:%i-%i-%i",rn1->power,(rn1->power<100)?"dB":"d",rn1->ci,rn1->lac,rn1->ch_number);
  DrawString(ws,2,28,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "2[%d%s]:%i-%i-%i",rn2->power,(rn2->power<100)?"dB":"d",rn2->ci,rn2->lac,rn2->ch_number);
  DrawString(ws,2,41,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "3[%d%s]:%i-%i-%i",rn3->power,(rn3->power<100)?"dB":"d",rn3->ci,rn3->lac,rn3->ch_number);
  DrawString(ws,2,54,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "4[%d%s]:%i-%i-%i",rn4->power,(rn4->power<100)?"dB":"d",rn4->ci,rn4->lac,rn4->ch_number);
  DrawString(ws,2,67,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "5[%d%s]:%i-%i-%i",rn5->power,(rn5->power<100)?"dB":"d",rn5->ci,rn5->lac,rn5->ch_number);
  DrawString(ws,2,80,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws, "6[%d%s]:%i-%i-%i",rn6->power,(rn6->power<100)?"dB":"d",rn6->ci,rn6->lac,rn6->ch_number);
  DrawString(ws,2,93,128,172,7,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
  
   DrawRoundedFrame(1,1,32,17,0,0,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  if(rn->power!=0) DrawRoundedFrame(2,2+((rn->power)/10),5,16,0,0,0,GetPaletteAdrByColorIndex( ((rn->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn->ch_number)<255)?2:4) );
  if(rn1->power!=0) DrawRoundedFrame(7,2+((rn1->power)/10),10,16,0,0,0,GetPaletteAdrByColorIndex( ((rn1->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn1->ch_number)<255)?2:4) );
  if(rn2->power!=0) DrawRoundedFrame(12,2+((rn2->power)/10),15,16,0,0,0,GetPaletteAdrByColorIndex( ((rn2->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn2->ch_number)<255)?2:4) );
  if(rn3->power!=0) DrawRoundedFrame(17,2+((rn3->power)/10),20,16,0,0,0,GetPaletteAdrByColorIndex( ((rn3->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn3->ch_number)<255)?2:4) );
  if(rn4->power!=0) DrawRoundedFrame(22,2+((rn4->power)/10),25,16,0,0,0,GetPaletteAdrByColorIndex( ((rn4->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn4->ch_number)<255)?2:4) );
  if(rn5->power!=0) DrawRoundedFrame(27,2+((rn5->power)/10),30,16,0,0,0,GetPaletteAdrByColorIndex( ((rn5->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn5->ch_number)<255)?2:4) );
  if(rn6->power!=0) DrawRoundedFrame(32,2+((rn6->power)/10),35,16,0,0,0,GetPaletteAdrByColorIndex( ((rn6->ch_number)<255)?2:4 ),GetPaletteAdrByColorIndex( ((rn6->ch_number)<255)?2:4) );

  return 0;
}
void info()
{ WSHDR *ws=AllocWS(256); 
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  RAMNET *rn=RamNet();
  int dayy=0;
  char ss[32],ss1[32],ss3[32],ss4[32],ss5[32],ss6[32],ss7[32];
  char *days[8]={" ","Вс","Пн","Вт","Ср","Чт","Пт","Сб"},
       *mounth[13]={" ","Янв","Фев","Март","Апр","Май","Июн","Июл","Авг","Сент","Окт","Ноя","Дек"};
  dayy=date.day;
  while(dayy>7)
  {dayy=dayy-7;   
  }
  char *s=date.day<10?"0":"";
  sprintf(ss,"Date  %s,%s%d %s",days[dayy],s,date.day,mounth[date.month]);
  int len=strlen(ss);
    for(int j=0;j<len;j++)
    {BM1NAME[j]=ss[j];}

  char *t2=time.sec<10?"0":"";
  char *t=time.min<10?"0":"";
  sprintf(ss1,"Time %d:%s%d:%s%d",time.hour,t,time.min,t2,time.sec);
  int len2=strlen(ss1);
    for(int j=0;j<len2;j++)
     {BM2NAME[j]=ss1[j];}
  sprintf(ss3,"Заряд АКБ %d %%",*RamCap());
  int len3=strlen(ss3);
    for(int j=0;j<len3;j++)
     {BM3NAME[j]=ss3[j];}
  int f0 = GetFreeFlexSpace(0, ErrorNumber)/1024;
  sprintf(ss4,"Free disc 0: %d kb",f0);
  int len4=strlen(ss4);
    for(int j=0;j<len4;j++)
     {BM4NAME[j]=ss4[j];}
  sprintf(ss5,"CPU Load %d %%",GetCPULoad());
  int len5=strlen(ss5);
    for(int j=0;j<len5;j++)
     {BM5NAME[j]=ss5[j];}

  sprintf(ss6,"Уров.сети %d db",rn->power);
  int len6=strlen(ss6);
    for(int j=0;j<len6;j++)
    {BM6NAME[j]=ss6[j];} 
    
    sprintf(ss7,"FreeRam: %d b",GetFreeRamAvail()/1000);
  int len7=strlen(ss7);
    for(int j=0;j<len7;j++)
    {BM7NAME[j]=ss7[j];} 
}

*/

//==========================
//     11 методов:)
//==========================
void OnRedraw(MAIN_GUI *data) // OnRedraw
{show();
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память

  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  CloseCSM(MAINCSM_ID);

}



int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  int i = 0;
  if ( msg->gbsmsg->msg == KEY_DOWN ) 
  { if(msg->keys==RED_BUTTON) return 1;
    if(msg->keys==RIGHT_SOFT) show();;
    
     }
  if ( msg->gbsmsg->msg == LONG_PRESS ) 
  {
   }
  return(i);
}

#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}
#else
extern void kill_data(void *p, void (*func_p)(void *));

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif


int method8(void){return(0);}


int method9(void){return(0);}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	//Destroy
  #else
  (void *)kill_data,	//Destroy
  #endif
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,129,129};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}
