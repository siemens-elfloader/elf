#ifdef NEWSGOLD
#include "..\inc\swilib.h"
#include "swilib2.h"
#include "player_tags.h"
#include "strings.h"
#include "NatICQ.h"
#include "main.h"
  int scr_w;
  extern unsigned long  strtoul (const char *nptr,char **endptr,int base); //must overwrite
//  extern const char CsmAdr[];
  unsigned int pcsmid=0;
  //extern const unsigned int cX;
  extern const unsigned int cfnt;
  extern int Is_Id3tag_Enabled;
  extern const char CsmAdr[9];
  const unsigned int cfnt=FONT_SMALL_BOLD;
  char teast2[256];
  char teast3[256];
  
  void *pcsmadr=NULL;
  WSHDR *wstag=NULL;
  word tagw=0;
//------------------------------------

int CurrentXStatus;

void  initTags(){
  pcsmadr=(void *)strtoul(CsmAdr,NULL,16);
  if (!wstag)    wstag=AllocWS(256);
};
//------------------------------------
 void GetTags()
 {
   if((CurrentXStatus!=11)||(!Is_Id3tag_Enabled))
   {
     sprintf(teast3, "zaebaloaq");
   }
   else
     if(Is_Id3tag_Enabled)
     {
   {
 L1://Respect to Rst7
  if (pcsmid){
    CSM_RAM *csmp=FindCSMbyID(pcsmid);
    if (csmp){
      WSHDR *fn=((WSHDR **)csmp)[0x2C/4];
      if (!fn)return;
      if (!fn->wsbody) return;
      if (fn->wsbody[0])        ;
#ifdef ELKA
        WSHDR **wws=((WSHDR ***)csmp)[(0x18C/4)]-1;
 #else
        WSHDR **wws=((WSHDR ***)csmp)[(0x170/4)]-1;
#endif
      if (wws)        {
        WSHDR *tws;
        const char unk[]="Unknown";
        const char pr[]="%w - %w";
        if (!(tws=wws[2]));else
          if (!(tws->wsbody));else
            if (tws->wsbody[0])      
              wstrcpy(wstag,tws);
             else  wsprintf(wstag,"%t",unk);
        if (!(tws=wws[1]));else
          if (!(tws->wsbody));else
            if (tws->wsbody[0])     
              wsprintf(wstag,pr,wstag,tws);
             else
              wstrcpy(wstag,fn);            
         //Патчим строку на предмет win1251
        int i=1;
        int c;
        tagw=0;
        while(i<=wstag->wsbody[0])		{
          c=wstag->wsbody[i];
          if (c==0xA8) c=0x401;
          if (c==0xAA) c=0x404;
          if (c==0xAF) c=0x407;
          if (c==0xB8) c=0x451;
          if (c==0xBA) c=0x454;
          if (c==0xBF) c=0x457;
          if ((c>=0xC0)&&(c<0x100)) c+=0x350;
          wstag->wsbody[i++]=c;
          tagw+=GetSymbolWidth(c,cfnt);
        }
      }else;
    }
    else    pcsmid=0;
  }
  else  {
    CSM_RAM *p=((void **)CSM_root()->csm_q)[2];
    while(p)
    {
      if (p->constr==pcsmadr) break;
      p=p->next;
    }
    if (p)
    {
      pcsmid=p->id;
    goto L1;
    }
  }
  convWS_to_ANSI(wstag, teast2);
  if(_GetPlayStatus()==2)
  {
  if(strcmp(teast2,teast3)) 
  {
//  ShowMSG(1,(int)teast2);
  CurrentXStatus=0;
  set_my_xstatus();  
  set_my_xstatus2();
  strcpy(teast3, teast2);
  CurrentXStatus=11;
  }
   }
  else
  {
    if((teast3[0]!='N'&&teast3[8]!='P')&&(_GetPlayStatus()!=1)) 
  {
    CurrentXStatus=0;
  set_my_xstatus();
  sprintf(teast2, "Nothing Played"); 
  set_my_xstatus2();
  strcpy(teast3, teast2);
  CurrentXStatus=11;
  }
  }
   }
     }
};  


int  ShowTag(void){
  if (pcsmadr&&((_GetPlayStatus()==2)));else return 2;
  GUI *igui;
/*  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (!icsm) return 0;
  if (!IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return 0;  
  */
  if (!TopG(DISPLACE_OF_IDLEGUI_ID))return 0;
  
  if (!(igui=GetTopGUI())) return 0;
  if (igui){
#ifdef ELKA
    {
      void *canvasdata = BuildCanvas();
#else
    void *idata = GetDataOfItemByID(igui, 2);
    if (idata)
    {
      void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];        
#endif        
      
      DrawCanvas(canvasdata,cTgr.x, cTgr.y,cTgr.x2, cTgr.y+GetFontYSIZE(cfnt), 1);  

      if (tagw<scr_w)
        DrawString(wstag,cTgr.x,cTgr.y,cTgr.x2,cTgr.y+GetFontYSIZE(cfnt),cfnt,TEXT_ALIGNMIDDLE,(char*)clr,GetPaletteAdrByColorIndex(23));
      else{
        static byte dir=0;
        int dif=tagw-scr_w;
        static short sm=0;
//        int step=(7*tagw)/scr_w;
        int step=4+(3*tagw)/scr_w;        
        sm+=step*(dir?-1:1);
        
        DrawScrollString(wstag,cTgr.x,cTgr.y,cTgr.x2,cTgr.y+GetFontYSIZE(cfnt)+10,sm+1,cfnt,TEXT_ALIGNLEFT,(char*)clr,GetPaletteAdrByColorIndex(23));
        if ((sm-step)<0)dir=0;else
         if ((sm)>dif)dir=1;
      }
    }
  }
  return 1;
} ;

#endif
