#include <swilib.h>
#include <playsound.h>
#include <sieapi.h>
#include "scrtool.h"
#include "conf_loader.h"
//ע������������ȫ��̨���а汾

static int   TaskHandle   = 0;//��¼ͼ�ν���
static int   PlayHandle   = 0;//��¼��������
static int   mCnt,mSlt,mAlm;//mCntΪ�˵�����,mSltΪѡ���Ĳ˵�,mAlm���Ӳ˵�ͼƬ
//�������ݻ�����
static char *Gala=NULL;
//���ò˵�
static char   PATHS[64],TITLE[32];
static TSCR   SCR[MAX_SCR];
static TAPP   APP[MAX_APP];
static GBSTMR SCRTMR,TSKTMR;
static short  OLScr;//��Ļ����ԭֵ
static TTime  t; 
static TDate  d;
static TCDate s={0,0,0,12};
static byte   week=0;//��¼���ڵ�����λ��
static byte   dmin=60;//�������Ӳ��ֵ�����
static byte   STATE;//��¼���н�������,1Ϊ�˵�,2Ϊ��ݲ˵�,3Ϊ���ӽ���
static byte   AUTO_EXIT = 0;//��¼�Զ��˳��˵�״̬
static byte   SUCC_HOOK = 0;//��¼HOOK״̬

#ifdef XTASK
static int    XTHandle=0;
#else
static CSM_DESC  icsmd;
//CSM_DESC* ocsmd;
static int (*OICSMOnMessage)(CSM_RAM*,GBS_MSG*);
void (*OICSMOnClose)(CSM_RAM*);
#endif

//�˵�������Ϣ
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};

//�˵���������
static int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//�˵�HOOK��������
static void MENU_HOOK(void *gui, int cmd){
  TFile *FileList=MenuGetUserPointer(gui);
  if(cmd==3){ 
    FreeFile(FileList);
  }  
}
//�˵��ػ��б�
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
    wsprintf(ws,"%t","����!!!");
  }  
  SetMenuItemText(gui, item, ws, cur_item); 
}
//�˵�������ʼ��
static int MENU_SOFTKEYS[]={0,1,2};
//�˵��������
SOFTKEY_DESC MENU_PRESS[]={
  {0x0018,0x0000,(int)"��"},
  {0x0001,0x0000,(int)"�˳�"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB MENU_TAB={MENU_PRESS,0};
//����˵��ṹ
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
//���尴ť��Ӧ�¼�
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
//���������ļ�
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
        //�����ļ�Ŀ¼
        len=strlen(de.folder_name)+strlen(de.file_name)+2+1;
        sb->path=malloc(len);        
        strcpy(sb->path,de.folder_name);
        strcat(sb->path,"\\");
        strcat(sb->path,de.file_name);
        //�����ļ�����
        sb->file=malloc(strlen(de.file_name)+1);        
        strcpy(sb->file,de.file_name);
        //������չ��
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
//�������˵�
static int BrowserFileMenu(){ 
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
}
//�������ò˵�
//��ʼ��������ʾ����
static void SetIDS(TSCR *INFO,int ENA,uint TYPE,int FONT,const char *PEN,const char *BUH){
  INFO->Show  = ENA;
  INFO->Size  = FontSize(FONT);
  INFO->Style = TYPE;    
  memcpy(INFO->PEN,PEN,4);
  memcpy(INFO->BUH,BUH,4);
}
static void InitShow(void){
 SetIDS(&SCR[ 0],TEMP_ENA,TEMP_T,TEMP_FT,TEMP_CS,TEMP_CB);
 SetIDS(&SCR[ 1],VOLT_ENA,VOLT_T,VOLT_FT,VOLT_CS,VOLT_CB);
 SetIDS(&SCR[ 2],RAMT_ENA,RAMT_T,RAMT_FT,RAMT_CS,RAMT_CB);
 SetIDS(&SCR[ 3],NETI_ENA,NETI_T,NETI_FT,NETI_CS,NETI_CB);
 SetIDS(&SCR[ 4],MGPS_ENA,MGPS_T,MGPS_FT,MGPS_CS,MGPS_CB);
 SetIDS(&SCR[ 5],CPUI_ENA,CPUI_T,CPUI_FT,CPUI_CS,CPUI_CB);
 SetIDS(&SCR[ 6],GPRS_ENA,GPRS_T,GPRS_FT,GPRS_CS,GPRS_CB);
 SetIDS(&SCR[ 7],TIME_ENA,TIME_T,TIME_FT,TIME_CS,TIME_CB);
 SetIDS(&SCR[ 8],TEXT_ENA,TEXT_T,TEXT_FT,TEXT_CS,TEXT_CB);
 SetIDS(&SCR[ 9],WEEK_ENA,WEEK_T,WEEK_FT,WEEK_CS,WEEK_CB);
 SetIDS(&SCR[10],DATE_ENA,DATE_T,DATE_FT,DATE_CS,DATE_CB); 
 SetIDS(&SCR[11],CHSY_ENA,CHSY_T,CHSY_FT,CHSY_CS,CHSY_CB);
 SetIDS(&SCR[12],CHSM_ENA,CHSM_T,CHSY_FT,CHSY_CS,CHSY_CB);//CHSM_FT,CHSM_CS,CHSM_CB);
 SetIDS(&SCR[13],CHSD_ENA,CHSD_T,CHSY_FT,CHSY_CS,CHSY_CB);//CHSD_FT,CHSD_CS,CHSD_CB);
 SetIDS(&SCR[14],CHSH_ENA,CHSH_T,CHSY_FT,CHSY_CS,CHSY_CB);//CHSH_FT,CHSH_CS,CHSH_CB);
 SetIDS(&SCR[15],CHMD_ENA,CHMD_T,CHSY_FT,CHSY_CS,CHSY_CB);//CHMD_FT,CHMD_CS,CHMD_CB);
 SetIDS(&SCR[16],NBIR_ENA,NBIR_T,NBIR_FT,NBIR_CS,NBIR_CB);
 SetIDS(&SCR[17],OBIR_ENA,OBIR_T,OBIR_FT,OBIR_CS,OBIR_CB);
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
//��ʾ������ɫ��λ����ʾ��
static void FillScreen(TSCR *INFO,uint x,uint y){  
  short L =PixlsWidth(INFO->WS,INFO->Size);
  short H =GetFontYSIZE(INFO->Size);
  switch(INFO->Style){
    case 1:INFO->L=0;break;
    case 2:INFO->L=(ScreenW()-L-1)/2;break;
    case 3:INFO->L= ScreenW()-L-1;break;
   default:INFO->L= x;break;
  }  
  INFO->T=y;
  INFO->R=INFO->L+L;  
  INFO->B=INFO->T+H;
}

//��������ʾ���ݽ��в�ʼ��
static void InitScreen(void){
int c; char TEMP[LEN]; 
byte state=d.year!=s.y||d.month!=s.m||d.day!=s.d||LunarTimeID(t.hour)!=s.h;  
if(SCR[0].Show){//��ʾ�¶���Ϣ 
    c=GetAkku(1,3)-0xAAA+15;
    wsprintf(SCR[0].WS,"%d.%d�C",c/10,c%10);
    FillScreen(&SCR[0],TEMP_X,TEMP_Y);
}   
if(SCR[1].Show){//��ʾ��ѹ��Ϣ
    if(VOLT_M==0){
      c=GetAkku(0,9);
      wsprintf(SCR[1].WS,"%d.%02dV",c/1000,(c%1000)/10);
    }else{
      c=*RamCap();
      wsprintf(SCR[1].WS,"%3d%%",c);
    }
    FillScreen(&SCR[1],VOLT_X,VOLT_Y);
}
if(SCR[2].Show){//��ʾʣ����Ϣ
    c=GetFreeRamAvail();
    wsprintf_bytes(SCR[2].WS,c);
    FillScreen(&SCR[2],RAMT_X,RAMT_Y);  
}       
if(SCR[3].Show||SCR[4].Show){//��ʾ������Ϣ   
   RAMNET *net=RamNet();
   if(SCR[3].Show){//�ź�ǿ��
     c=(net->ch_number>=255)?'=':'-';
     wsprintf(SCR[3].WS,"%c%ddB",c,net->power);
     FillScreen(&SCR[3],NETI_X,NETI_Y);
   }
   if(SCR[4].Show){//��վ����    
     wsprintf(SCR[4].WS,"%u-%u",net->ci,net->lac);
     FillScreen(&SCR[4],MGPS_X,MGPS_Y);
   }
}    
if(SCR[5].Show){//��ʾCPUʹ����
    c=GetCPULoad();
    wsprintf(SCR[5].WS,"%3d%%",c);
    FillScreen(&SCR[5],CPUI_X,CPUI_Y);
}       
if(SCR[6].Show){//��ʾGPRS����
    c=*GetGPRSTrafficPointer();
    wsprintf_bytes(SCR[6].WS,c);
    FillScreen(&SCR[6],GPRS_X,GPRS_Y);
} 
if(SCR[7].Show){//��ʾ��ǰʱ��
    c=t.hour;
    if((TIME_FMT==0||TIME_FMT==1)&&(c > 12)) c -= 12;
    switch(TIME_FMT){
     case 0:
     case 2:sprintf(TEMP,"%02d:%02d",c,t.min);break;
     case 1:
     case 3:sprintf(TEMP,"%02d:%02d:%02d",c,t.min,t.sec);break;
     case 4:sprintf(TEMP,"%02d��%02d��",c,t.min);break;
    default:sprintf(TEMP,"%02d��%02d��%02d��",c,t.min,t.sec);break;
    } 
    wsprintf(SCR[7].WS,PNT_ONE,TEMP);
    if(TIME_FMT==0||TIME_FMT==1){
    //����:0xE438; ����:0xE439
      if(t.hour<=12)
        wsAppendChar(SCR[7].WS,0xE438);
      else
        wsAppendChar(SCR[7].WS,0xE439);
    }
    FillScreen(&SCR[7],TIME_X,TIME_Y);
}  
if(state)
{//�Ƿ����
  if(SCR[8].Show){//��ʾ������Ϣ
    wsprintf(SCR[8].WS,PNT_ONE,TEXT_CP);
    FillScreen(&SCR[8],TEXT_X,TEXT_Y);
  }     
  if(SCR[9].Show){//��ʾ��ǰ����    
    wsprintf(SCR[9].WS,PNT_ONE,cwName[WEEK_FMT][week]);
    FillScreen(&SCR[9],WEEK_X,WEEK_Y);
  }  
  if(SCR[10].Show){//��ʾ��ǰ����
    if(DATE_FMT < 5)
      sprintf(TEMP,cDataFmt[DATE_FMT],d.year,d.month,d.day);
    else
      sprintf(TEMP,cDataFmt[DATE_FMT],d.month,d.day);
    wsprintf(SCR[10].WS,PNT_ONE,TEMP);
    FillScreen(&SCR[10],DATE_X,DATE_Y);
  }  
  //��ȡ������Ϣ
  TLunar cn = GetLunar(d,t.hour);
  if(SCR[11].Show){//��ʾũ������
    wsprintf(SCR[11].WS,PNT_ONE,cn.year);
    FillScreen(&SCR[11],CHSY_X,CHSY_Y);
  }
  if(SCR[12].Show){//��ʾũ������
    wsprintf(SCR[12].WS,PNT_ONE,cn.moth);
    FillScreen(&SCR[12],CHSM_X,CHSM_Y);
  }     
  if(SCR[13].Show){//��ʾũ������
    wsprintf(SCR[13].WS,PNT_ONE,cn.dday);
    FillScreen(&SCR[13],CHSD_X,CHSD_Y);
  }
  if(SCR[14].Show){//��ʾũ��ʱ��
    wsprintf(SCR[14].WS,PNT_ONE,cn.hour);
    FillScreen(&SCR[14],CHSH_X,CHSH_Y);
  }  
  if(SCR[15].Show){//��ʾũ������SWDZ
    wsprintf(SCR[15].WS,PNT_ONE,cn.nday);
    FillScreen(&SCR[15],CHMD_X,CHMD_Y);
  }  
  char Day[8];
  if(SCR[16].Show){//��ʾ��������
    sprintf(Day,"N%02d.%02d:",d.month,d.day);
    MidStr(Gala,Day,TEMP);
    wsprintf(SCR[16].WS,PNT_ONE,TEMP);
    FillScreen(&SCR[16],NBIR_X,NBIR_Y);
  }
  if(SCR[17].Show){//��ʾũ������  
    TLDate o=GetLDate(d);
    sprintf(Day,"P%02d.%02d:",o.month,o.day);
    MidStr(Gala,Day,TEMP);
    wsprintf(SCR[17].WS,PNT_ONE,TEMP);
    FillScreen(&SCR[17],OBIR_X,OBIR_Y);
  }   
}
s.y = d.year;
s.m = d.month;
s.d = d.day;
s.h = LunarTimeID(t.hour);
}
//����Ļ�ϻ����˵�ͼ��λ�ú��ı���Ϣ
static void DrawGUI(void){ 
  GBS_StartTimerProc(&TSKTMR,20,DrawGUI); 
  short fSize,TextH=0;
  WSHDR *MWS=AllocWS(50);  
  void *TskCanvas=BuildCanvas(); 
  if((SUCC_HOOK)&&(TASK_ENA)&&(STATE==SCR_TASKS))   
  {//��ʼ�˵�����--------�ı�����-------- 
   fSize = FontSize(ATEXT_FT);  
   if(DEST_ENA){
    TextH = GetFontYSIZE(fSize)+4;//�ı��߶�
    if(TextH < SoftkeyH()) TextH = SoftkeyH(); 
   }
   short top=ScreenH()-TextH-OFFSET-1;//�ı�����λ�� 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//�����ı���������   
   TRect iRC={0,top-PicSize-1,PicSize-1,top-1};//����ͼ���������
   short y=0,z=0,i=0,n=ScreenW()/PicSize;  
   short ts=(tRC.b-tRC.t-GetFontYSIZE(fSize))/2;//�����ı���ֱƫ��  
   n = PicSize +(ScreenW()-n*PicSize)/(n-1);//����ͼ����ʾ��
   if(mCnt>((ScreenW())/(n))){ i=mSlt-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;   
   //--------����ͼ����ı�--
   while(i<mCnt){
    const char *s=APP[i].P;
    if(!((s)&&(strlen(s)))) s=AINO;    
    TRect tmp=iRC; tmp.l+=y; tmp.r+=y;     
    short picw =(PicSize-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    short pich =(PicSize-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawCanvas(TskCanvas, tmp.l,tmp.t,tmp.r,tmp.b, 1);  
    DrawImg(tmp.l+picw,tmp.t+pich,(uint)s);     
    if(i==mSlt){
      DrawRectangle(tmp.l,tmp.t,tmp.r,tmp.b,0,BBDCol,TRAN_CBK);
      if(DEST_ENA){
        wsprintf(MWS,PNT_ONE,APP[i].N);
        DrawRectangle(tRC.l, tRC.t, tRC.r, tRC.b,0, PBDCol, PBGCol);        
        DrawString(MWS,tRC.l+3,tRC.t+ts,tRC.r-3,tRC.b-ts,fSize,1,ATEXT_CS,TRAN_CBK); 
      }       
    }
    y+=n;
    i++;
    if(++z>((ScreenW())/(n))-1) break;
   }     
   //�Զ��رղ˵�
   if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TaskHandle)) CloseCSM(TaskHandle);//CloseTask();
   //�����˵�
  }elif((ALRM_ENA)&&(STATE==SCR_ALARM)){//���ӽ��� 
   TRect ac={0,YDISP,ScreenW()-1,ScreenH()-1};
   DrawCanvas(TskCanvas, ac.l,ac.t,ac.r,ac.b, 1);
   DrawRectangle(ac.l, ac.t, ac.r, ac.b,0, ALRM_CBK, ALRM_CBK);  
   char PIC[64];
   sprintf(PIC,ALRM_PIC,mAlm);
   wsprintf(MWS,PNT_ONE,ALRM); 
   fSize=FontSize(ALRM_FT);
   TextH=GetFontYSIZE(fSize)+4;
   short wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   short pio=(ac.r-ac.l-GetImgWidth((int)PIC))/2;
   short pih=GetImgHeight((int)PIC);     
   TRect at={ac.l,ac.t,ac.r,ac.t+TextH}; 
   TRect ap={ac.l+pio,at.b,ac.l-pio,ac.b+pih};   
  //����     
   DrawString(MWS, at.l+wso, at.t+2, at.r-wso, at.b-2,fSize,1,ALRM_CTX, TRAN_CBK); 
  //ͼ��
   DrawImg(ap.l,ap.t,(uint)PIC);  
   wsprintf(MWS,PNT_ONE,cwName[4][week]);
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect aw={ac.l+wso,at.b+pih,ac.r-wso,at.b+pih+TextH}; 
   DrawString(MWS, aw.l, aw.t+2,aw.r,aw.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //ʱ��
   wsprintf(MWS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect al={ac.l+wso,aw.b,ac.r-wso,aw.b+TextH}; 
   DrawString(MWS, al.l, al.t+2,al.r,al.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //��ʾ����PNT_YMD
   wsprintf(MWS,PNT_YMD,d.year,"��",d.month,"��",d.day,"��");
   wso=(ac.r-ac.l-PixlsWidth(MWS,fSize))/2;
   TRect ad={ac.l+wso,al.b,ac.r-wso,al.b+TextH}; 
   DrawString(MWS, ad.l, ad.t+2,ad.r,ad.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
   //ѭ��ͼƬ
   if(mAlm%2){
     SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(ALRM_VIB);
   }else{
     if(ALIU_ENA)
        SetIllumination(0,1,5,0);
     else
        SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(0);
   }
   if(mAlm>=ALRM_COT)mAlm=0;
   mAlm++;
  }//�������Ӵ���
  FreeWS(MWS);
}
//�ػ���Ӧ�¼�
static void TaskRedraw(GUI *gui){
  if(STATE!=SCR_MENUS) DrawGUI();
}

//�˵�����
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
  case  0: APP_TRAF((char*)ANTO,i,    4,(char*)AITO,         ""); break;//�ػ�
  case  1: APP_TRAF((char*)ANRT,i,    5,(char*)AIRT,         ""); break;//����
  case  2: APP_TRAF((char*)ANLK,i,    6,(char*)AILK,         ""); break;//����
  case  3: APP_TRAF((char*)ANST,i,    7,(char*)AIST,         ""); break;//���� 
  case  4: APP_TRAF((char*)AN04,i, AT04,(char*)AI04,(char*)AF04); break;//����
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
//������Ӧ�¼�
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  switch(STATE){
  case SCR_TASKS://����˵�
    AUTO_EXIT=0;
    InitMenu();
    mSlt=0;  
    break;
  case SCR_ALARM://��������
    KbdUnlock();
    PlayHandle=PlayMusic(ALRM_FILE, ALRM_VOL,ALRM_NUM);
    OLScr=GetIlluminationDataTable()[3];    
    mAlm=1; 
    break;
  }  
  gui->state=1;
}
//�ر���Ӧ�¼�
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
//�۽���Ӧ�¼�
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void(*mfree_adr)(void *)){
  gui->state=2;
}
//ȡ���۽���Ӧ�¼�
static void TaskUnfus(GUI *gui, void(*mfree_adr)(void *)){
  if(gui->state!=2) return;
  gui->state=1; 
}
//���幦��ִ�в�������
static void DoIt(int inx);
//���尴����������
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    //DirectRedrawGUI();
    if((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;       
    if(msg->gbsmsg->submess==KeyButton(CALL_BTN)){//�رղ˵� 
      CloseCSM(TaskHandle);//CloseTask(); 
      return(1);
    }    
    switch(msg->gbsmsg->submess){//ѡ������          
      case  DOWN_BUTTON://��ѡ����ѡ��      
      case RIGHT_BUTTON:if(++mSlt >=mCnt)mSlt=0;break;       
      case    UP_BUTTON://��ѡ����ѡ��         
      case  LEFT_BUTTON:if(--mSlt<0)mSlt=mCnt-1;break;         
      case ENTER_BUTTON:if(STATE==SCR_TASKS)DoIt(mSlt); break;//ִ�жԾ͵Ĺ���
    }  
   }
  }
  return(0);
}
static int TaskMethod8(void){return(0);}
static int TaskMethod9(void){return(0);}
static const void * const TaskMethods[11]={
 (void *)TaskRedraw,	//�ػ�
 (void *)TaskCreate,	//����
 (void *)TaskClose,	//�ر�
 (void *)TaskFocus,	//�۽�
 (void *)TaskUnfus,	//ȡ���۽�
 (void *)TaskKeypress,	//��������
  0,
 (void *)kill_data,
 (void *)TaskMethod8,      //����δ֪
 (void *)TaskMethod9,      //����δ֪
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
//����GUI����
static void BuildGUI(short MODE,char *NAME,int Type){  
  LockSched();
  STATE=MODE;  
  char DUMMY[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&TASK_CSM.NAME),PNT_ONE,NAME);
  TaskHandle=CreateCSM(&TASK_CSM.CSM,DUMMY,Type);  
  UnlockSched();
}
//ִ��ָ��Ŀ¼
static void RunDIR(char *dir,char *name){  
  strcpy(PATHS,dir);  
  strcpy(TITLE,name);
  BuildGUI(SCR_MENUS,name,0);
}
//ִ�в˵�����
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
//�����ҹ�,�ڴ�����
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
//�ҹ�ϵͳʱ��ˢ�²���
static void TimerProc(void){
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);  
}
static int DaemonOnMessage(CSM_RAM* data,GBS_MSG* msg){  
  //��ȡϵͳʱ�������,����
  GetDateTime(&d,&t);
  week = GetWeek(&d);
  // ��������
  if(msg->msg == MSG_RECONFIGURE_REQ){
    if(strcmp_nocase(cfn,(char *)msg->data0)==0){ 
      s.y = 0;
      s.m = 0;
      s.d = 0;
      s.h = 12;
      InitConfig();
      //���¼��ؽ����ļ�����
      if(FreeFileBuf(Gala)) Gala=LoadFileBuf(BIRS_FILE); 
      InitShow();
      LockSched();
      ShowMSG(1,(int)"�����Ѹ���!");  
      UnlockSched();
    }
  }   
  //���þɵ���Ϣ�¼�
  #ifdef XTASK
  int Result=1;
  #else
  int Result=OICSMOnMessage(data,msg);
  #endif
  //�Զ��ػ� 
   if((SHUT_ENA)&&(SHUT_TIME.hour==t.hour)&&(SHUT_TIME.min==t.min)&&(t.sec<=5)){
     #ifdef XTASK
     CloseCSM(XTHandle);
     #endif
     SwitchPhoneOff();//�Զ��ػ���,�᲻���ͷ��ڴ�
     return(Result);
   }
  //�Զ�����
   if((ROOT_ENA)&&(ROOT_TIME.hour==t.hour)&&(ROOT_TIME.min==t.min)&&(t.sec<=5)){
     #ifdef XTASK
     CloseCSM(XTHandle);
     #endif
     RebootPhone();
     return(Result);
   }
  //�Զ����ֻ���������
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
  //���Թ���  
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
      InitScreen();//�Զ��幦����ʾ
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
  //��ȡ������Ϣ    
  if((ALRM_ENA)&&(!PlayHandle)&&(!IsCalling())&&(t.min!=dmin)){//����
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
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)&&(PlayHandle)){//ֹͣ����
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if(pmsg->handler==PlayHandle){
      if(pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){        
       CloseCSM(TaskHandle);
      }
    }  
  }  
  //resc = d.day;
  return(Result);
}  
#ifdef XTASK
static void DaemonOnCreate(CSM_RAM *data){
#else
static void DaemonInit(void){
#endif
  for(byte i=0;i<MAX_SCR; i++) SCR[i].WS=AllocWS(60);
  Gala=LoadFileBuf(BIRS_FILE);
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
