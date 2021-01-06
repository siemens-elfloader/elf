#include "..\inc\swilib.h"
typedef  unsigned char byte;
typedef  unsigned short word;
typedef  unsigned int dword;
typedef struct {
  byte unk[0x20];
  void *canvas;
  int NeedDrawCanvas;
}gui_ofs;
void main2 (gui_ofs* r0);
void main (gui_ofs* r0){ //dummy jumper 
  main2(r0);
}
#pragma swi_number=0x0c5
__swi __arm int IsIdleUiOnTop(void);


#pragma swi_number=0x1F8
__swi __arm unsigned int GetPlayStatus(void);

#pragma swi_number=0x40 
__swi __arm int GetVibraStatus (void);

#pragma swi_number=0x80CB 
__swi __arm unsigned char* RamRingtoneStatus (void);


enum systray{ST_x1=0,ST_y1=0,ST_x2=239,ST_y2=23};


//enum nettray_{NET_x1=6,NET_y1=4,NET_x2=57,NET_y2=23};
//enum icontray{IC_x1=62,IC_y1=0,IC_x2=180,IC_y2=23};
//enum battray_{BAT_x1=182,BAT_y1=0,BAT_x2=239,BAT_y2=23};

enum nettray_{NETO_x1=6-2,NETO_y1=4,NETO_x2=57-2,NETO_y2=19};
enum icontray{IC_x1=57,IC_y1=4,IC_x2=184,IC_y2=19};
enum battray_{BAT_x1=182+4,BAT_y1=4,BAT_x2=233+4,BAT_y2=19};

/*
enum nettray_text_{NET_x1=0,NET_y1=0,NET_x2=47,NET_y2=23};

void DrawNetText(void *canvas){
  RAMNET Res = *RamNet();

  WSHDR ws1loc, *ws1;
  unsigned short num[8];
  ws1=CreateLocalWS(&ws1loc,num,8);
  
  wsprintf(ws1,"%c%d",Res.ch_number>=512?'=':'-',Res.power);
    DrawCanvas(canvas,NET_x1,NET_y1,NET_x2,NET_y2,1);
  DrawString(ws1,NET_x1,NET_y1,NET_x2,NET_y2,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT|TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  
};
*/

/*
enum battray_{BAT_x1=190,BAT_y1=0,BAT_x2=237,BAT_y2=23};
inline void DrawBatText(void *canvas){
  int vl=GetAkkuCapacity();
  WSHDR ws1loc, *ws1;
  unsigned short num[4];
  ws1=CreateLocalWS(&ws1loc,num,4);
  wsprintf(ws1,"%02d%",vl);
  DrawCanvas(canvas,BAT_x1,BAT_y1,BAT_x2,BAT_y2,1);
  DrawString(ws1,BAT_x1,BAT_y1,BAT_x2,BAT_y2,FONT_SMALL_BOLD,TEXT_ALIGNLEFT|TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
};
*/

typedef struct {
  short unk1;
  short unk2;  
  int flag2;
  short int pic[3][6]; // s,1,2  level
  short int picGE[3][2][6]; //  s,1,2 Gprs,Edge level
  short int pic_copy[3][6]; // s,1,2  level
} pic_mem;



typedef int P_IsBooleanVoid(void);
typedef int P_IsBooleanPintPint(void *, void *);
typedef int P_IsBooleanIntInt(int, int);

#include "el71v45_adr.h"

inline void DrawNet(void *canvas){
  short respow[6]={98,88,79,70,61,1};
  pic_mem *netpic=(void*)NETPICS; // 
  RAMNET Res = *RamNet();
  if (netpic->unk1!=-1)  DrawCanvas(canvas,NETO_x1,NETO_y1,NETO_x2,NETO_y2,1);
  
  for (int i=0;i<6;i++)
    if (Res.power>respow[i]){
      int pic=IsGPRS()?(netpic->picGE[0][IsEDGE()][i]):netpic->pic[0][i];

       
      DrawImg(NETO_x1,NETO_y1,pic);   
      break;
    }
}

inline void DrawBat(void *canvas){
  
  DrawCanvas(canvas,BAT_x1,BAT_y1,BAT_x2,BAT_y2,1);
  DrawImg(BAT_x1,BAT_y1,GetBatIcon());
};

enum iconsELKA{ICO_locked=0x203,ICO_mplayer=0x206,ICO_vibra=0x258,ICO_gprs=0x1EC,ICO_gprsred=0x1EB,ICO_dumping=0x204,ICO_callout=0x1E5,ICO_SMS_both=0x209,ICO_SMS_recv=0x208,ICO_SMS_send=0x20A,ICO_net_na=0x267,ICO_BT_vis=0x1C6,ICO_BT_nvis=0x1C5,ICO_BT_ntrans=0x1C7,ICO_BT_trans=0x1C8,ICO_BT_headset=0x1C9,ICO_headset=0x1F0,ICO_decrypt=0x256,ICO_car=0x1e6,ICO_ringoff=0x1C2,ICO_ring_onlygroups=0x1E4};
enum some{ic_w=IC_x2-IC_x1,ico_width=16,ico_height=16,iconnar_height=24, ico_ofs_y=(iconnar_height-ico_height)/2,ico_beetwen=2,ico_ofs2=(ico_width+ico_beetwen)/2,ico_ofs1=(ic_w-ico_width)/2};

typedef struct{
    int counter;
    int isdumping;
    char unkb[0x18];
    short bar1[6];
    short bar2[6];    
}ico_cache;

void main2(gui_ofs* r0)
{
  pic_mem *netpic=(void*)NETPICS; 
  ico_cache *ramcache=(void*)RAMCACHE; 

  int stacked_img[20];
  int icon_cntr=0;
  int needBG=0;
  void *canvas=NULL;
  if (r0){
    needBG=r0->NeedDrawCanvas;
    canvas=r0->canvas;
  }
  if (!IsIdleUiOnTop()){
    netpic->flag2=1;
  }else{
    if (!netpic->flag2)goto Draw;
  }
  DrawCanvas(canvas,ST_x1,ST_y1,ST_x2,ST_y2,1);
  netpic->unk1=-1;
  netpic->unk2=-1;  
Draw:
  
  DrawNet(canvas);
  DrawBat(canvas);  
//icons------------------------------------
//locked
  if (!IsUnlocked())stacked_img[icon_cntr++]=ICO_locked; //1
//player
  int ps=GetPlayStatus();
  if (ps)stacked_img[icon_cntr++]=ICO_mplayer+2-ps; //2
//vibre  
  if (GetVibraStatus())stacked_img[icon_cntr++]=ICO_vibra; //3
//gprs state  
  if (IsGPRSEnabled())
    stacked_img[icon_cntr++]=IsGPRSConnected()?ICO_gprs:ICO_gprsred; //4
// File Saving
  //  if (((ramcache->isdumping&&0x0200) stacked_img[icon_cntr++]=ICO_dumping; ??
  if (((ramcache->isdumping<<0x12)<0)) stacked_img[icon_cntr++]=ICO_dumping; //5
//calling (outgoing)
/*
    native firmare work same 
  P_IsBooleanVoid   *const Iscal   = (P_IsBooleanVoid*) 0xA05BCDC7;
  */
  if (IsCalling()) {
    if (isDecryption())    stacked_img[icon_cntr++]=ICO_decrypt; //11
    stacked_img[icon_cntr++]=ICO_callout; //6
  }else{
//calls_from    
    if (AlertCallsFrom())   stacked_img[icon_cntr++]= ICO_ring_onlygroups;  //14
  }
// SMS send/recv  
  int sm=(GetSMSState())&0x3;
  if (sm){
    if (sm==3)sm=ICO_SMS_both;else
          if (sm==2)sm=ICO_SMS_recv;else sm=ICO_SMS_send;
    stacked_img[icon_cntr++]=sm;          //7
  }
// net access NA  
  byte tmp2,tmp1;
  GetNetworkAccess(&tmp1,&tmp2);  //if first =4 n/a if 1 - net search if 0 -good
  if ((byte)tmp1==4) stacked_img[icon_cntr++]=ICO_net_na; //  8  
// Bluetooth
  if (!GetCurrAudioPath())stacked_img[icon_cntr++]=ICO_BT_headset;else { //  9  
    if (GetBTstate(0,1)||(GetBTstate(0,2))){
     if (GetBTstate(0,4)){ //check transfer
       stacked_img[icon_cntr++]=ICO_BT_ntrans+BT_GetLocVisibility();
     }else
       stacked_img[icon_cntr++]=ICO_BT_nvis+BT_GetLocVisibility();
    };
    
  }
//headset
if (GetHeadSet (2,0) )       stacked_img[icon_cntr++]=ICO_headset; //10
//car
if (GetHeadSet (-1,1) )       stacked_img[icon_cntr++]=ICO_car; //12

//ring settings
//LockSched()  -called in firmware
if (*RamRingtoneStatus())stacked_img[icon_cntr++]=ICO_ringoff; //13
//UnlockSched()




  int stx=IC_x1+ico_ofs1-(icon_cntr-1)*ico_ofs2;
  DrawCanvas(canvas,IC_x1,IC_y1,IC_x2,IC_y2,1);
  for (int i=0;i<icon_cntr;i++){
     
     DrawImg(stx,IC_y1,stacked_img[i]);
     stx+=ico_width+ico_beetwen;
  }
  
 return;
}


/*
NOT  display icons

0x1c4 -podnyatay trubka
0x1f1 - domik
0x266 - telefon c kluchom
0x205 -mafon - autoanswer
1e0 - strelka+telefon - divert
0x27a -TTY  if (GetHeadSet (2,2) )       stacked_img[icon_cntr++]=ICO_tty; 

*/













