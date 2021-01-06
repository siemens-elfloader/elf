#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "..\inc\sieapi.h"
#include "conf_loader.h"

extern const char *cfn;
extern const TDate ymd;
extern const char cData[64];
extern const char FND_COLOR[];//今天颜色
extern const char FNC_COLOR[];//课程颜色
extern const char FNL_COLOR[];//线条颜色
extern const char FNM_COLOR[];//时间颜色
extern const char FNW_COLOR[];//周次颜色
extern const char FNT_COLOR[];//标题颜色
//背景
extern const char BGC_COLOR[];//选中
extern const char BGA_COLOR[];//全部
extern const char BGW_COLOR[];//周次
extern const char BGT_COLOR[];//标题
extern const char BGM_COLOR[];//上午
extern const char BGP_COLOR[];//下午
extern const char BGN_COLOR[];//晚上

static byte p_x=1, p_y=1; //移动查看选中项
static char *Data;
static byte  Kcb=6;

typedef struct{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct{
  GUI gui;
} MAIN_GUI;


static const char ver[16] = "课程表v2.06";

static byte dlt=0;
static TDate d;
static TTime t;

unsigned int MAINCSM_ID = 0;
static byte ac=10;

static void onRedraw(MAIN_GUI *data){
  WSHDR* ws = AllocWS(20);
  static short LW,week;
  static TRect rc;
#ifdef ELKA
  static byte aa=2;
  static byte ad=24;
  static byte y1=28;
  static byte y2=24;
  static byte ww=29;  
#else
  static byte aa=1;
  static byte ad=1;
  static byte y1=18;
  static byte y2=14;  
  static byte ww=16;  
#endif
  word OHigh=y1+y2+ad;  
  word Right=ww*8+aa+2;
  word Left =aa+1;
  word YSize =GetFontYSIZE(FONT_SMALL);
  //时间日期星期
  GetDateTime(&d, &t);
  //计算周次
  week=((d.year-ymd.year)*365+SumDays(d.year,d.month)-SumDays(ymd.year,ymd.month)+d.day-ymd.day)/7+1;
  //底色
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,BGA_COLOR,BGA_COLOR);
  //课程表标题
  wsprintf(ws,PNT_ONE,ver);
  DrawString(ws,0,YDISP+2, ScreenW()-1,3+YDISP+YSize,8,2,FNT_COLOR,TRAN_CBK);
  //画周次时间信息
  WSHDR* wsL = AllocWS(4);
  wsAppendChar(wsL,0xE405);  
  if(t.hour>12){
     t.hour-=12;
     wsprintf(ws, "%w:%dW %02d-%02d %02d:%02dP",wsL,week,d.month,d.day,t.hour,t.min);       
  }else{
     wsprintf(ws, "%w:%dW %02d-%02d %02d:%02dA",wsL,week,d.month,d.day,t.hour,t.min);
  }     
  DrawString(ws,0,YDISP+YSize+6,ScreenW()-1,YDISP+YSize*2+6,FONT_SMALL_BOLD,2,FNT_COLOR,TRAN_CBK);
  FreeWS(wsL);
  //画背景框  1.时间；2.星期；3.上午；4.下午；5.晚上 width*2+aa
  DrawRectangle(Left,OHigh,      ww*2+aa+2,y1+ad+y2*11,0,BGT_COLOR,BGT_COLOR);  // 1.时间
  DrawRectangle(Left,OHigh,      Right,    y1+ad+y2*2 ,0,BGW_COLOR,BGW_COLOR);  // 2.星期
  DrawRectangle(Left,y1+y2*2+ad, Right,    y1+ad+y2*6 ,0,BGM_COLOR,BGM_COLOR); // 3.上午
  DrawRectangle(Left,y1+y2*6+ad, Right,    y1+ad+y2*ac,0,BGP_COLOR,BGP_COLOR); // 4.下午
  DrawRectangle(Left,y1+y2*ac+1, Right,    y1+ad+y2*11,0,BGN_COLOR,BGN_COLOR); // 5.晚上
 //选中背景
  if(dlt==0){
    if(p_x==7) p_x=6;
    rc=SetRect(ww*(p_x+1)+4,y1+y2*(p_y+1)+1,ww*(p_x+2)+4,y1+y2*(p_y+2));  
  }else{
    rc=SetRect(ww*2+4,y1+y2*(p_y+1)+1,ww*8+4,y1+y2*(p_y+2));
  }
  DrawRectangle(rc.l,rc.t,rc.r,rc.b,0,BGC_COLOR,BGC_COLOR); 
  short L=rc.l,R=rc.r;
  //课程表线及课程数据
  for(byte i=0;i<=7;i++){
   for(byte j=0;j<=ac;j++){
   //画线框
   DrawLine(Left, y1+ad+y2*(j+1),ww*(7+1)+3,y1+ad+y2*(j+1), 0,FNL_COLOR); //下
   DrawLine(Left, y1+ad*2,       Left,      y1+y2*(ac+1)+ad,0,FNL_COLOR); //左
   DrawLine(Right,y1+ad*2,       Right,     y1+y2*(ac+1)+ad,0,FNL_COLOR); //右
   rc=SetRect(ww*(i+1)+aa+2,y1+y2+ad,ww*(i+1)+aa+2,y1+ad+y2*(ac+1)); 
   if(!dlt && i && i!=7){
     DrawLine(rc.l,rc.t,rc.r,rc.b,0,FNL_COLOR); //其它竖线，短
   }else if(i==1){
     DrawLine(rc.l,rc.t,rc.r,rc.b,0,FNL_COLOR); //第二根竖线，重复，粗线
   }
   LW=ww*(i+1)+5;
   //星期
   if(j==0 && i>0){  
     wsprintf(ws,PNT_ONE,"时间");
     rc=SetRect(3,OHigh+3,ww*2+5,OHigh+YSize);
     DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNW_COLOR,TRAN_CBK);
     if(dlt==0 && i!=7){       
       rc.l=LW;
       rc.r=LW+R-L;
       wsprintf(ws,PNT_ONE,WeekID[i-1]);
     }else if(dlt==1 && i==p_x){       
       rc.l=L;
       rc.r=R;
       wsprintf(ws,PNT_ONE,WeekGB[i-1]);
     }
     DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNW_COLOR,TRAN_CBK);   
   }
   //课程数据
   if(j<9){
    char TEMP[6],Res[16];
    sprintf(TEMP,"%d.%d:",i,j+1);
    MidStr(Data,TEMP,Res);
    wsprintf(ws,PNT_ONE,Res);
    week=OHigh+j*(YSize+2)+4+YSize;
    rc=SetRect(LW,week,LW+R-L,week+YSize); 
    if(dlt==1 && i==p_x){      
      DrawString(ws,L,rc.t,R,rc.b,8,2,FNC_COLOR,TRAN_CBK);    
    }else if(i==0){  
      rc=SetRect(3, week,ww*2+5,week+YSize);
      DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNM_COLOR,TRAN_CBK);       
    }else if(dlt==0 && i>0){
      strncpy(TEMP,Res,2);      
      TEMP[2]=0;
      wsprintf(ws,PNT_ONE,TEMP);      
      if(i==GetWeek(&d)+1){
         if(j+2==p_y)
           DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNC_COLOR,TRAN_CBK);   
         else
           DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FND_COLOR,TRAN_CBK);
      }else{
        DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNC_COLOR,TRAN_CBK);      
      }
    }
   }
  }
}
FreeWS(ws);
}
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)){  
  Data=LoadFileBuf(cData);
  GetDateTime(&d, &t);
  p_x=GetWeek(&d)+1;
  if(p_x==7){dlt=1;Kcb=7;}
  if(t.hour<=7) p_y=1; //morning 1
  elif(t.hour<=11) p_y=t.hour%7+2; //morning 1-4
  elif(t.hour<=14) p_y=6; //afternoon 5
  elif(t.hour<=17) p_y=t.hour%10+2; //afternoon 5-7
  elif(t.hour<=19) p_y=8;
  elif(t.hour<=20) p_y=9;
  elif(t.hour<=21) p_y=ac;
  //elif(t.hour>=22) { p_y=1; p_x=GetWeek(&d)+2; } //next morning 1
  else { p_y=1; p_x=GetWeek(&d)+2; }//p_y=8; //night 8
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)){
  data->gui.state=0;
  FreeFileBuf(Data);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
  data->gui.state=2;
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)){
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg){
  char TEMP[64];
  if (msg->gbsmsg->msg==KEY_DOWN){   
    switch(msg->gbsmsg->submess){
      case UP_BUTTON:    if(p_y>1)    p_y--; else p_y=ac; REDRAW(); break;
      case DOWN_BUTTON:  if(p_y<ac)   p_y++; else p_y=1;  REDRAW(); break;
      case LEFT_BUTTON:  if(p_x>1)    p_x--; else p_x=Kcb;REDRAW(); break;
      case RIGHT_BUTTON: if(p_x<Kcb)  p_x++; else p_x=1;  REDRAW(); break;
      case ENTER_BUTTON: if(dlt==0){dlt=1;Kcb=7;}else{dlt=0;Kcb=6;}  REDRAW(); break;
      case LEFT_SOFT:sprintf(TEMP,"%s\n%s",ver,"修改:玫瑰!\n感谢:\nzhangxxx");
                     LockSched();
                     ShowMSG(1,(int)TEMP);  
                     UnlockSched();break;
      case GREEN_BUTTON:RunAPP((char *)cfn);break;
      case RED_BUTTON:
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
    }
  }
  return(0);
}

static int method8(void){return(0);}
static int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){
  char TEMP[64];
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(msg->msg == MSG_RECONFIGURE_REQ){    
    if(strcmp_nocase(cfn,(char *)msg->data0)==0){                
      InitConfig();
      //重新加载节日文件数据
      if(FreeFileBuf(Data)) Data=LoadFileBuf(cData);
      sprintf(TEMP,"%s\n%s",ver,"参数已更新!");
      LockSched();
      ShowMSG(1,(int)TEMP);  
      UnlockSched();  
    }
  }    
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))  {
    csm->csm.state=-3;
  }
  return(1);
}

const RECT Canvas={0,0,0,0};

static void maincsm_oncreate(CSM_RAM *data){
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));	
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;	
  csm->gui_id=CreateGUI(main_gui);  
}

static void maincsm_onclose(CSM_RAM *csm){
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

const struct{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM ={{
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
  },{
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void){
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),PNT_ONE,ver);
}

int main(void){  
  InitConfig();
  LockSched();  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
