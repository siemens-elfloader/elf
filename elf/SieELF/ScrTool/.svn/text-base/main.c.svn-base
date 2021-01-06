#include <swilib.h>
#include <playsound.h>
#include <sieapi.h>
#include "scrtool.h"
#include "conf_loader.h"
//注释这里编译成完全后台运行版本

static int   TaskHandle   = 0;//记录图形界面
static int   PlayHandle   = 0;//记录闹钟响铃
static byte  STATE;//记录运行界面类型,1为菜单,2为快捷菜单,3为闹钟界面
static byte  AUTO_EXIT = 0;//记录自动退出菜单状态
static byte  SUCC_HOOK = 0;//记录HOOK状态
static int   mCnt,mSlt,mCur;
//定义数据缓存区
static char *Gala=NULL;
//配置菜单
static char   PATHS[64],TITLE[32];
static TSCR   SCR[MAX_SCR];
static TAPP   APP[MAX_APP];
static TLunar NLi;
static GBSTMR TSKTMR,SCRTMR;
static short  OLScr;//屏幕亮灯原值
static TTime  t; 
static TDate  d;
static short  week=0;
static short  SWYD=0;
static byte   dmin=60;

#ifdef XTASK
static int    XTHandle=0;
#else
static CSM_DESC  icsmd;
//CSM_DESC* ocsmd;
static int  (*OICSMOnMessage)(CSM_RAM*,GBS_MSG*);
void (*OICSMOnClose)(CSM_RAM*);
#endif

//菜单标题信息
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};

//菜单按键操作
static int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//菜单HOOK操作命令
static void MENU_HOOK(void *gui, int cmd){
  TFile *FileList=MenuGetUserPointer(gui);
  if(cmd==3){ 
    FreeFile(FileList);
  }  
}
//菜单重画列表
static void MENU_DRAW(void *gui, int cur_item, void *user_pointer){
  WSHDR *ws;
  TFile *FileList=user_pointer;
  for(int n=0; n!=cur_item; n++) FileList=FileList->next;
  void *item=AllocMenuItem(gui);
  if(FileList){
    int len=strlen(FileList->file);
    ws=AllocMenuWS(gui,len+4);
    if(FileList->type){
       str_2ws(ws,FileList->file,len);
       wsInsertChar(ws,0x0002,1);
       wsInsertChar(ws,0xE008,1);
    }else{str_2ws(ws,FileList->file,len);}
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,"%t","错误!!!");
  }  
  SetMenuItemText(gui, item, ws, cur_item); 
}
//菜单按键初始化
static int MENU_SOFTKEYS[]={0,1,2};
//菜单软键名称
SOFTKEY_DESC MENU_PRESS[]={
  {0x0018,0x0000,(int)"打开"},
  {0x0001,0x0000,(int)"退出"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB MENU_TAB={MENU_PRESS,0};
//定义菜单结构
MENU_DESC MENU_STRUCT={
  8,
  MENU_ONKEY,
  MENU_HOOK,
  NULL,
  MENU_SOFTKEYS,
  &MENU_TAB,
  0x10,
  MENU_DRAW,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};
//定义按钮响应事件
static int MENU_ONKEY(void *gui, GUI_MSG *msg){
  TFile *sbtop=MenuGetUserPointer(gui);
  if(msg->keys==0x3D || msg->keys==0x18){
    int i=GetCurMenuItem(gui);
    SetMenuItemIcon(gui,i,0);
    for(int n=0; n!=i; n++) sbtop=sbtop->next;
    if(sbtop){      
      CloseCSM(TaskHandle);//CloseTask();
      RunAPP(sbtop->path);
      return(1);
    }
  }
  if((msg->keys==0x01 || msg->keys==RED_BUTTON)&&(TaskHandle)) CloseCSM(TaskHandle);//CloseTask();  
  return(0);
}
//搜索配置文件
static TFile *FindBCFGFile(){
  uint err;
  DIR_ENTRY de;
  int  len;
  TFile *filelist=0;
  char str[128];
  strcpy(str,PATHS);
  if(isdir(PATHS,&err))strcat(str,"*");
  if(FindFirstFile(&de,str,&err)){
    do{
      if(!(de.file_attr&FA_DIRECTORY)){
        TFile *sb=malloc(sizeof(TFile));
        //设置文件目录
        len=strlen(de.folder_name)+strlen(de.file_name)+2+1;
        sb->path=malloc(len);        
        strcpy(sb->path,de.folder_name);
        strcat(sb->path,"\\");
        strcat(sb->path,de.file_name);
        //设置文件名称
        sb->file=malloc(strlen(de.file_name)+1);        
        strcpy(sb->file,de.file_name);
        //隐藏扩展名
        if(!SHOW_EXT)sb->file[getstrpos(sb->file,'.')]=0;
        sb->type=0;
        sb->next=0;
        if(filelist){
          TFile *sbr, *sbt;
          sbr=(TFile *)&filelist;
          sbt=filelist;
          while(strcmp_nocase(sbt->file,sb->file)<0){
            sbr=sbt;
            sbt=sbt->next;
            if(!sbt) break;
          }
          sb->next=sbt;
          sbr->next=sb;
        } else{filelist=sb;}
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return filelist;
}
//创建主菜单
static int BrowserFileMenu(){ 
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
}
//结束配置菜单
//初始化生日显示数据
static void SetIDS(TSCR *INFO,int ENA,uint TYPE,int FONT,const char *PEN,const char *BUH){
  INFO->Show  = ENA;
  INFO->Size  = FontType(FONT);
  INFO->Style = TYPE;    
  memcpy(INFO->PEN,PEN,4);
  memcpy(INFO->BUH,BUH,4);
}
static void InitShow(void){
 SetIDS(&SCR[ 0],TEMP_ENA,TEMP_XT,TEMP_FT,TEMP_CS,TEMP_CB);
 SetIDS(&SCR[ 1],VOLT_ENA,VOLT_XT,VOLT_FT,VOLT_CS,VOLT_CB);
 SetIDS(&SCR[ 2],RAMT_ENA,RAMT_XT,RAMT_FT,RAMT_CS,RAMT_CB);
 SetIDS(&SCR[ 3],TEXT_ENA,TEXT_XT,TEXT_FT,TEXT_CS,TEXT_CB);
 SetIDS(&SCR[ 4],NETI_ENA,NETI_XT,NETI_FT,NETI_CS,NETI_CB);
 SetIDS(&SCR[ 5],CPUI_ENA,CPUI_XT,CPUI_FT,CPUI_CS,CPUI_CB);
 SetIDS(&SCR[ 6],GPRS_ENA,GPRS_XT,GPRS_FT,GPRS_CS,GPRS_CB);
 SetIDS(&SCR[ 7],WEEK_ENA,WEEK_XT,WEEK_FT,WEEK_CS,WEEK_CB);
 SetIDS(&SCR[ 8],DATE_ENA,DATE_XT,DATE_FT,DATE_CS,DATE_CB);
 SetIDS(&SCR[ 9],TIME_ENA,TIME_XT,TIME_FT,TIME_CS,TIME_CB);
 SetIDS(&SCR[10],CHSD_ENA,CHSD_XT,CHSD_FT,CHSD_CS,CHSD_CB);
 SetIDS(&SCR[11],NBIR_ENA,NBIR_XT,NBIR_FT,NBIR_CS,NBIR_CB);
 SetIDS(&SCR[12],OBIR_ENA,OBIR_XT,OBIR_FT,OBIR_CS,OBIR_CB);
}
#pragma inline  
static int wsprintf_bytes(WSHDR *ws, uint bytes){
  if(bytes<=1024)
    return(wsprintf(ws,"%uB",bytes));
  else{
    bytes>>=10;
    return(wsprintf(ws,"%uKB",bytes));
  }  
}
//显示内容配色和位置显示等
static void FillScreen(TSCR *INFO,uint x,uint y){  
  int wstyle =PixlsWidth(INFO->WS,INFO->Size);
  switch(INFO->Style){
    case 1:INFO->L=0;break;
    case 2:INFO->L=(ScreenW()-wstyle-1)/2;break;
    case 3:INFO->L= ScreenW()-wstyle-1;break;
   default:INFO->L= x;break;
  }  
  INFO->T=y;
  INFO->R=INFO->L+wstyle;  
  INFO->B=INFO->T+GetFontYSIZE(INFO->Size);
}

//对所有显示数据进行补始化
static void InitScreen(void){
  int c;
  char TEMP[16],Day[8],Res[LEN];
  if(SCR[0].Show){//显示温度信息 
    c=GetAkku(1,3)-0xAAA+15;
    wsprintf(SCR[0].WS,"%d.%d癈",c/10,c%10);
    FillScreen(&SCR[0],TEMP_X,TEMP_Y);
  }   
  if(SCR[1].Show){//显示电压信息
    if(VOLT_TY==0){
      c=GetAkku(0,9);
      wsprintf(SCR[1].WS,"%d.%02dV",c/1000,(c%1000)/10);
    }elif(VOLT_TY==1){
      c=*RamCap();
      wsprintf(SCR[1].WS,"%3d%%",c);
    }
    FillScreen(&SCR[1],VOLT_X,VOLT_Y);
  }
  if(SCR[2].Show){//显示剩余信息
    c=GetFreeRamAvail();
    wsprintf_bytes(SCR[2].WS,c);
    FillScreen(&SCR[2],RAMT_X,RAMT_Y);  
  } 
  if(SCR[3].Show){//显示定义信息
    wsprintf(SCR[3].WS,PNT_ONE,TEXT_CP);
    FillScreen(&SCR[3],TEXT_X,TEXT_Y);
  }         
  if(SCR[4].Show){//显示网络信息
    RAMNET *net_data=RamNet();
    c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(SCR[4].WS,"%c%ddB",c,net_data->power);
    FillScreen(&SCR[4],NETI_X,NETI_Y);
  }       
  if(SCR[5].Show){//显示CPU使用率
    c=GetCPULoad();
    wsprintf(SCR[5].WS,"%3d%%",c);
    FillScreen(&SCR[5],CPUI_X,CPUI_Y);
  }       
  if(SCR[6].Show){//显示GPRS流量
    //RefreshGPRSTraffic();
    c=*GetGPRSTrafficPointer();
    wsprintf_bytes(SCR[6].WS,c);
    FillScreen(&SCR[6],GPRS_X,GPRS_Y);
  }
  //定义时间信息
  if(SCR[7].Show){//显示当前星期    
    if(WEEK_FMT <4){
      for(byte i=0;i<16;i++){TEMP[i]=cWeekName[WEEK_FMT][week][i];}
      wsprintf(SCR[7].WS,TEMP,week);
    }elif(WEEK_FMT==4){
      wsprintf(SCR[7].WS,PNT_ONE,WeekGB[week]);
    }else{
      wsprintf(SCR[7].WS,PNT_ONE,WeekID[week]); 
    }
    FillScreen(&SCR[7],WEEK_X,WEEK_Y);
  }  
  if(SCR[8].Show){//显示当前日期
    for(byte i=0;i<16;i++){TEMP[i]=cDataFmt[DATE_FMT][i]; }
    if(DATE_FMT < 4)
      sprintf(TEMP,TEMP,d.year,d.month,d.day);
    elif(DATE_FMT <8)
      sprintf(TEMP,TEMP,d.month,d.day);
    elif(DATE_FMT == 8)
      sprintf(TEMP,"%04d年%02d月%02d日",d.year,d.month,d.day);
    else
      sprintf(TEMP,"%02d月%02d日",d.month,d.day);
    wsprintf(SCR[8].WS,PNT_ONE,TEMP);
    FillScreen(&SCR[8],DATE_X,DATE_Y);
  }  
  if(SCR[9].Show){//显示当前时间
    switch(TIME_FMT) {
    case 0: 
      sprintf(TEMP,"%02d:%02d",t.hour,t.min); 
      break;      
    case 1:
      if(t.hour <= 12) {
        sprintf(TEMP,"AM %02d:%02d",t.hour,t.min);
      } else {
        t.hour -= 12;
        sprintf(TEMP,"PM %02d:%02d",t.hour,t.min);
      } 
      break;      
    case 2:
      if(t.hour > 12) t.hour -= 12;
      sprintf(TEMP,"%02d:%02d",t.hour,t.min);
      break;      
    case 3: 
      sprintf(TEMP,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
      break;      
    case 4:
      if(t.hour <= 12){
        sprintf(TEMP,"AM %02d:%02d:%02d",t.hour,t.min,t.sec);
      } else {
        t.hour -= 12;
        sprintf(TEMP,"PM %02d:%02d:%02d",t.hour,t.min,t.sec);
      }
      break;
    case 5:
      sprintf(TEMP,"%02d点%02d分",t.hour,t.min);
      break;
    default:
      sprintf(TEMP,"%02d点%02d分%02d秒",t.hour,t.min,t.sec);
      break;
    }   
    wsprintf(SCR[9].WS,PNT_ONE,TEMP);
    FillScreen(&SCR[9],TIME_X,TIME_Y);
  }  
  if(SCR[10].Show){//显示农历信息
    CutWSTR(SCR[10].WS,0);
    GetDayOf(d,&NLi);
    if(SWYD<10){//显示农历日期 
      memcpy(SCR[10].WS->wsbody,NLi.year->wsbody,16);
    }elif(SWYD<20){//显示农历年份     
      memcpy(SCR[10].WS->wsbody,NLi.mday->wsbody,16); 
    }elif(SWYD<30){
      c=LunarTimeID(t.hour);
      wsprintf(SCR[10].WS,PNT_ONE,cSShi[c]);
    }else{//显示农历节气
      static word lunar;
      if(lunar=LunarHolId(d))
         LunarHolDay(SCR[10].WS,lunar);
      else
         SWYD=40;
    }
    if(SWYD++>=40)SWYD=0;
    FillScreen(&SCR[10],CHSD_X,CHSD_Y);
  }
  if(SCR[11].Show){//显示公历节日
    sprintf(Day,"N%02d.%02d:",d.month,d.day);
    MidStr(Gala,Day,Res);
    wsprintf(SCR[11].WS,PNT_ONE,Res);
    FillScreen(&SCR[11],NBIR_X,NBIR_Y);
  }
  if(SCR[12].Show){//显示农历节日  
    TDate o=GetOldDay(d);
    sprintf(Day,"P%02d.%02d:",o.month,o.day);
    MidStr(Gala,Day,Res);
    wsprintf(SCR[12].WS,PNT_ONE,Res);
    FillScreen(&SCR[12],OBIR_X,OBIR_Y);
  }
}
//在屏幕上画主菜单图标位置和文本信息
static void DrawGUI(void){ 
  GBS_StartTimerProc(&TSKTMR,20,DrawGUI); 
  short fSize,TextH=0;
  WSHDR *MWS=AllocWS(50);  
  void *TskCanvas=BuildCanvas(); 
  if((SUCC_HOOK)&&(TASK_ENA)&&(STATE==SCR_TASKS))   
  {//开始菜单代码--------文本区域-------- 
   fSize = FontType(ATEXT_FT);  
   if(DEST_ENA){
    TextH = GetFontYSIZE(fSize)+4;//文本高度
    if(TextH < SoftkeyH()) TextH = SoftkeyH(); 
   }
   short top=ScreenH()-TextH-OFFSET-1;//文本顶部位置 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//生成文本绘制区域   
   TRect iRC={0,top-PicSize-1,PicSize-1,top-1};//生成图标绘制区域
   short y=0,z=0,i=0,n=ScreenW()/PicSize;  
   short ts=(tRC.b-tRC.t-GetFontYSIZE(fSize))/2;//计算文本垂直偏移  
   n = PicSize +(ScreenW()-n*PicSize)/(n-1);//计算图标显示数
   if(mCnt>((ScreenW())/(n))){ i=mSlt-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;   
   //--------绘制图标和文本--
   while(i<mCnt){
    const char *s=APP[i].P;
    if(!((s)&&(strlen(s)))) s=AINO;    
    TRect tmp=iRC; tmp.l+=y; tmp.r+=y;     
    short picw =(PicSize-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    short pich =(PicSize-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawCanvas(TskCanvas, tmp.l,tmp.t,tmp.r,tmp.b, 1);  
    DrawImg(tmp.l+picw,tmp.t+pich,(uint)s);     
    if(i==mSlt){
      DrawRectangle(tmp.l,tmp.t,tmp.r,tmp.b,0,cfgBBDCol,TRAN_CBK);
      if(DEST_ENA){
        wsprintf(MWS,PNT_ONE,APP[i].N);
        DrawRectangle(tRC.l, tRC.t, tRC.r, tRC.b,0, cfgPBDCol, cfgPBGCol);        
        DrawString(MWS,tRC.l+3,tRC.t+ts,tRC.r-3,tRC.b-ts,fSize,1,ATEXT_CS,TRAN_CBK); 
      }       
    }
    y+=n;
    i++;
    if(++z>((ScreenW())/(n))-1) break;
   }     
   //自动关闭菜单
   if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TaskHandle)) CloseCSM(TaskHandle);//CloseTask();
   //结束菜单
  }elif((ALRM_ENA)&&(STATE==SCR_ALARM)){//闹钟界面 
   TRect ac={0,YDISP,ScreenW()-1,ScreenH()-1};
   DrawCanvas(TskCanvas, ac.l,ac.t,ac.r,ac.b, 1);
   DrawRectangle(ac.l, ac.t, ac.r, ac.b,0, ALRM_CBK, ALRM_CBK);  
   char PIC[64];
   sprintf(PIC,ALRM_PIC,mCur);
   wsprintf(MWS,PNT_ONE,ALRM); 
   fSize=FontType(ALRM_FT);
   TextH=GetFontYSIZE(fSize)+4;
   short wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   short pio=(ac.r-ac.l-GetImgWidth((int)PIC))/2;
   short pih=GetImgHeight((int)PIC);     
   TRect at={ac.l,ac.t,ac.r,ac.t+TextH}; 
   TRect ap={ac.l+pio,at.b,ac.l-pio,ac.b+pih};   
  //标题     
   DrawString(MWS, at.l+wso, at.t+2, at.r-wso, at.b-2,fSize,1,ALRM_CTX, TRAN_CBK); 
  //图标
   DrawImg(ap.l,ap.t,(uint)PIC);
  //定义
   wsprintf(MWS,PNT_ONE,WeekGB[week]);
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect aw={ac.l+wso,at.b+pih,ac.r-wso,at.b+pih+TextH}; 
   DrawString(MWS, aw.l, aw.t+2,aw.r,aw.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //时间
   wsprintf(MWS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect al={ac.l+wso,aw.b,ac.r-wso,aw.b+TextH}; 
   DrawString(MWS, al.l, al.t+2,al.r,al.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //显示日期PNT_YMD
   wsprintf(MWS,PNT_YMD,d.year,"年",d.month,"月",d.day,"日");
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect ad={ac.l+wso,al.b,ac.r-wso,al.b+TextH}; 
   DrawString(MWS, ad.l, ad.t+2,ad.r,ad.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
   //循环图片
   if(mCur%2){
     SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(ALRM_VIB);
   }else{
     if(ALIU_ENA)
        SetIllumination(0,1,5,0);
     else
        SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(0);
   }
   if(mCur>=ALRM_COT)mCur=0;
   mCur++;
  }//结束闹钟代码
  FreeWS(MWS);
}
//重画响应事件
static void TaskRedraw(GUI *gui){
  if(STATE!=SCR_MENUS) DrawGUI();
}

//菜单功能
static void APP_TRAF(char *Name, int i, int Type,char *Pic,char *File){
  APP[i].T = Type;
  APP[i].P = Pic;
  APP[i].C = File;
  APP[i].N = Name;
  if((APP[i].C)&&(strlen(APP[i].C)))mCnt+=1;
}

static void InitMenu(void){  
  mCnt=4;  
 for(byte i=0;i<MAX_APP;i++){
  switch(i){  
  case  0: APP_TRAF((char*)ANTO,i,    4,(char*)AITO,         ""); break;//关机
  case  1: APP_TRAF((char*)ANRT,i,    5,(char*)AIRT,         ""); break;//重启
  case  2: APP_TRAF((char*)ANLK,i,    6,(char*)AILK,         ""); break;//锁键
  case  3: APP_TRAF((char*)ANST,i,    7,(char*)AIST,         ""); break;//设置 
  case  4: APP_TRAF((char*)AN04,i, AT04,(char*)AI04,(char*)AF04); break;//配置
  case  5: APP_TRAF((char*)AN05,i, AT05,(char*)AI05,(char*)AF05); break;
  case  6: APP_TRAF((char*)AN06,i, AT06,(char*)AI06,(char*)AF06); break;
  case  7: APP_TRAF((char*)AN07,i, AT07,(char*)AI07,(char*)AF07); break;
  case  8: APP_TRAF((char*)AN08,i, AT08,(char*)AI08,(char*)AF08); break;
  case  9: APP_TRAF((char*)AN09,i, AT09,(char*)AI09,(char*)AF09); break;
  case 10: APP_TRAF((char*)AN10,i, AT10,(char*)AI10,(char*)AF10); break;
  case 11: APP_TRAF((char*)AN11,i, AT11,(char*)AI11,(char*)AF11); break;
  case 12: APP_TRAF((char*)AN12,i, AT12,(char*)AI12,(char*)AF12); break;
  case 13: APP_TRAF((char*)AN13,i, AT13,(char*)AI13,(char*)AF13); break;
  }
 }
}
//创建响应事件
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  switch(STATE){
  case SCR_TASKS://任务菜单
    AUTO_EXIT=0;
    InitMenu();
    mSlt=0;  
    break;
  case SCR_ALARM://任务闹钟
    PlayHandle=PlayMusic(ALRM_FILE, ALRM_VOL,ALRM_NUM);
    OLScr=GetIlluminationDataTable()[3];
    KbdUnlock();
    mCur=1; 
    break;
  }  
  gui->state=1;
}
//关闭响应事件
static void TaskClose(GUI *gui, void(*mfree_adr)(void *)){
  if(STATE!=SCR_MENUS)GBS_DelTimer(&TSKTMR);
  switch(STATE){
   case SCR_ALARM:
     PlayMelody_StopPlayback(PlayHandle); 
     SetIllumination(0,1,OLScr,0);
     SetVibration(0);  
     PlayHandle=0;
     KbdLock();
     break;
  }   
  gui->state=0;
}
//聚焦响应事件
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void(*mfree_adr)(void *)){
  gui->state=2;
}
//取消聚焦响应事件
static void TaskUnfus(GUI *gui, void(*mfree_adr)(void *)){
  if(gui->state!=2) return;
  gui->state=1; 
}
//定义功能执行操作函数
static void DoIt(int inx);
//主体按键操作功能
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    //DirectRedrawGUI();
    if((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;       
    if(msg->gbsmsg->submess==KeyButton(CALL_BTN)){//关闭菜单 
      CloseCSM(TaskHandle);//CloseTask(); 
      return(1);
    }    
    switch(msg->gbsmsg->submess){//选定操作          
      case  DOWN_BUTTON://下选定右选定      
      case RIGHT_BUTTON:if(++mSlt >=mCnt)mSlt=0;break;       
      case    UP_BUTTON://上选定右选定         
      case  LEFT_BUTTON:if(--mSlt<0)mSlt=mCnt-1;break;         
      case ENTER_BUTTON:if(STATE==SCR_TASKS)DoIt(mSlt); break;//执行对就的功能
    }  
   }
  }
  return(0);
}
static int TaskMethod8(void){return(0);}
static int TaskMethod9(void){return(0);}
static const void * const TaskMethods[11]={
 (void *)TaskRedraw,	//重画
 (void *)TaskCreate,	//创建
 (void *)TaskClose,	//关闭
 (void *)TaskFocus,	//聚焦
 (void *)TaskUnfus,	//取消聚焦
 (void *)TaskKeypress,	//按键操作
  0,
 (void *)kill_data,
 (void *)TaskMethod8,      //功能未知
 (void *)TaskMethod9,      //功能未知
  0
};

const RECT Canvas={0, 0, 0, 0};
static void TaskOnCreate(CSM_RAM *data){   
  GUI *TaskGui=malloc(sizeof(GUI));
  TASK_GUI *TaskCsm=(TASK_GUI*)data;
  zeromem(TaskGui,sizeof(GUI));
  TaskGui->canvas=(void *)(&Canvas);
  if(STATE==SCR_ALARM)TaskGui->flag30=2;
  TaskGui->methods=(void *)TaskMethods;
  TaskGui->item_ll.data_mfree=(void(*)(void *))mfree_adr();
  TaskCsm->CSM.state=0;
  TaskCsm->CSM.unk1 =0;
  if(STATE==SCR_MENUS)
     TaskCsm->TaskID=BrowserFileMenu();
  else
     TaskCsm->TaskID=CreateGUI(TaskGui); 
}

static void TaskKiller(void){
#ifndef DAEMON
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void(*)(void *))mfree_adr());
#endif
}
static void TaskOnClose(CSM_RAM *csm){  
  SUBPROC((void *)TaskKiller); 
}

static int TaskOnMessage(CSM_RAM *data, GBS_MSG *msg){
  TASK_GUI *TaskCsm=(TASK_GUI*)data;
  if((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==TaskCsm->TaskID)){
    TaskCsm->CSM.state=-3;
  }  
  return(1);
}

static const struct{
  CSM_DESC CSM;
  WSHDR NAME;
}TASK_CSM={{
  TaskOnMessage,
  TaskOnCreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  TaskOnClose,
  sizeof(TASK_GUI),
  1,
  &MINUSLL},{
  MTBody,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};
//创建GUI界面
static void BuildGUI(short MODE,char *NAME,byte TYPE){  
  LockSched();
  STATE=MODE;  
  char DUMMY[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&TASK_CSM.NAME),PNT_ONE,NAME);
  TaskHandle=CreateCSM(&TASK_CSM.CSM,DUMMY,TYPE);  
  UnlockSched();
}
//执行指定目录
static void RunDIR(char *dir,char *name){  
  strcpy(PATHS,dir);  
  strcpy(TITLE,name);
  BuildGUI(SCR_MENUS,name,0);
}
//执行菜单功能
static void DoIt(int i){ 
  CloseCSM(TaskHandle);
  switch((int)APP[i].T){   
   case 0: RunAPP(APP[i].C); break;
   case 1: RunCUT(APP[i].C); break;
   case 2: RunADR(APP[i].C); break;
   case 3: RunDIR(APP[i].C,APP[i].N); break;  
   case 4: SwitchPhoneOff(); break;
   case 5: RebootPhone();break;
   case 6: KbdLock();break;
   case 7: RunAPP((char *)cfn); break;
  }     
}
//按键挂钩,内存运行
static int DaemonKeyHook(int key, int m){  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(m==MODE_KBD+0x193)){ 
    if(IsUnlocked()&&(key==KeyButton(CALL_BTN))){
       BuildGUI(SCR_TASKS,TASK,0); 
       return(0);
    }    
  }
  return 0;
}
//挂勾系统时间刷新操作
static void TimerProc(void){
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);  
}
static int DaemonOnMessage(CSM_RAM* data,GBS_MSG* msg){  
  //获取系统时间和日期,星期
  GetDateTime(&d,&t);
  week = GetWeek(&d);  
  // 更新配置
  if(msg->msg == MSG_RECONFIGURE_REQ){
    if(strcmp_nocase(cfn,(char *)msg->data0)==0){                
      InitConfig();
      //重新加载节日文件数据
      if(FreeFileBuf(Gala)) Gala=LoadFileBuf(BIRS_FILE); 
      InitShow();
      LockSched();
      ShowMSG(1,(int)"参数已更新!");  
      UnlockSched();
    }
  }   
  //调用旧的消息事件
  #ifdef XTASK
  int Result=1;
  #else
  int Result=OICSMOnMessage(data,msg);
  #endif
  //自动关机 
   if((SHUT_ENA)&&(SHUT_TIME.hour==t.hour)&&(SHUT_TIME.min==t.min)&&(t.sec<=5)){
     #ifdef XTASK
     CloseCSM(XTHandle);
     #endif
     SwitchPhoneOff();//自动关机后,会不能释放内存
     return(Result);
   }
  //自动重启
   if((ROOT_ENA)&&(ROOT_TIME.hour==t.hour)&&(ROOT_TIME.min==t.min)&&(t.sec<=5)){
     #ifdef XTASK
     CloseCSM(XTHandle);
     #endif
     RebootPhone();
     return(Result);
   }
  //自定义手机启动管理
  if((TASK_ENA)&&(!SUCC_HOOK)){      
      AddKeybMsgHook((void *)DaemonKeyHook);
      SUCC_HOOK = 1;
  }elif((!TASK_ENA)&&(SUCC_HOOK)){
     if(TaskHandle) CloseCSM(TaskHandle); 
     RemoveKeybMsgHook((void *)DaemonKeyHook);  
     SUCC_HOOK = 0;
  }
  if(msg->msg==MSG_IPC){
    IPC_REQ *IPC;
    if(IPC=(IPC_REQ*)msg->data0){
      if(strcmp_nocase(IPC->name_to,SCR_NAME)==0){
        switch(msg->submess){
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if(!getCpuUsedTime_if_ena()){StartCpuUsageCount();}
          #endif
          GBS_StartTimerProc(&SCRTMR, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
  }     
  //屏显功能  
  byte ScrShow=0;
  switch(INFO_ENA){
   case 0: ScrShow = !IsUnlocked();  break;
   case 1: ScrShow =  IsUnlocked();  break;
   case 2: ScrShow = 1;  break;
   default:ScrShow = 0;  break;
  }      
  CSM_RAM *icsm;  
  if(icsm=FindCSMbyID(CSM_root()->idle_id)){
    if(IsGuiOnTop(idlegui_id(icsm))&&ScrShow){
      GUI *igui=GetTopGUI();
      InitScreen();//自定义功能显示
      if(igui){ 
       #ifdef ELKA
        {void *ScrCnv = BuildCanvas();
       #else
        void *idata  = GetDataOfItemByID(igui,2);
        if(idata)
        {void *ScrCnv =((void **)idata)[DISPLACE_OF_IDLECANVAS/4];         
       #endif       
        for(byte i=0; i<(sizeof(SCR)/sizeof(TSCR)); i++){
        if(SCR[i].Show){
          DrawCanvas(ScrCnv,SCR[i].L,SCR[i].T,SCR[i].R,SCR[i].B,1);
          DrawString(SCR[i].WS,SCR[i].L,SCR[i].T,SCR[i].R,SCR[i].B,SCR[i].Size,32,SCR[i].PEN,SCR[i].BUH);
         }          
        }
       }  
      }
    }
  }
  //获取日期信息    
  if((ALRM_ENA)&&(!PlayHandle)&&(!IsCalling())&&(t.min!=dmin)){//闹钟
    char cTime[12],TEMP[LEN];
    dmin = t.min;
    sprintf(cTime,"R%02d:%02d.",t.hour,t.min);
    if(MidStr(Gala,cTime,TEMP)){
      if(strlen(TEMP)>=7){
       if(TEMP[week]=='1'){
        BuildGUI(SCR_ALARM,ALRM,2);
       }
      }
    }
  }    
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)&&(PlayHandle)){//停止铃声
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if(pmsg->handler==PlayHandle){
      if(pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){        
       CloseCSM(TaskHandle);
      }
    }  
  }  
  return(Result);
}  
#ifdef XTASK
static void DaemonOnCreate(CSM_RAM *data){
#else
static void DaemonInit(void){
#endif
  for(byte i=0;i<MAX_SCR; i++) SCR[i].WS=AllocWS(50);
  Gala=LoadFileBuf(BIRS_FILE);
  NLi.year=AllocWS(50);
  NLi.mday=AllocWS(50);  
  InitShow();  
}

static void Destructor(void){  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
static void DaemonOnClose(CSM_RAM *data){ 
  if(SUCC_HOOK) RemoveKeybMsgHook((void *)DaemonKeyHook);
  if(IsTimerProc(&SCRTMR))GBS_DelTimer(&SCRTMR);
  for(byte i=0;i!=MAX_SCR; i++) FreeWS(SCR[i].WS);
  FreeFileBuf(Gala);
  FreeWS(NLi.year);
  FreeWS(NLi.mday);
  SUBPROC((void *)Destructor);  
}
#ifdef XTASK
static word XTBody[LEN];
static const struct{
  CSM_DESC CSM;
  WSHDR NAME;
}MAIN_CSM={{
  DaemonOnMessage,
  DaemonOnCreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  DaemonOnClose,
  sizeof(DAEMON_CSM),
  1,
  &MINUSLL},{
  XTBody,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};
#endif

int main(){
  InitConfig();  
  LockSched();
#ifdef XTASK
  char DUMMY[sizeof(DAEMON_CSM)];   
  wsprintf((WSHDR *)(&MAIN_CSM.NAME),PNT_ONE,(char *)(strrchr(ANTO,'-')+1));
  CSM_RAM *save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;   
  XTHandle=CreateCSM(&MAIN_CSM.CSM,DUMMY,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
#else
  DaemonInit();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  OICSMOnClose   = icsmd.onClose;
  OICSMOnMessage = icsmd.onMessage;
  icsmd.onClose  = DaemonOnClose;
  icsmd.onMessage= DaemonOnMessage;
  icsm->constr   = &icsmd;  
#endif
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);
  if(TASK_ENA){      
     AddKeybMsgHook((void *)DaemonKeyHook);   
     SUCC_HOOK = 1;
  }
  UnlockSched();
  return 0;
}
