#include "..\inc\swilib.h"
#include "conf_loader.h"

#define TMR_SECOND 216
#define ELF_ID 0x3AC

extern const unsigned int cfgenable;

extern const unsigned int cfgx;
extern const unsigned int cfgy;
extern const unsigned int cfgx2;
extern const unsigned int cfgy2;

extern const unsigned int cfgcolor;
extern const unsigned int cfgbordercolor;
extern const unsigned int cfgfont;
extern const unsigned int cfgalign;
//extern const unsigned int cfgfontsize;
//extern const unsigned int cfgfontbold;

extern const unsigned int REFRESH;

extern const char root_dir[128];

CSM_DESC icsmd;
 
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

GBSTMR mytmr;


// ----------------------------------------------------------------------------

void TimerProc(void)
{
  GBS_SendMessage(MMI_CEPID,ELF_ID);
  GBS_StartTimerProc(&mytmr,REFRESH*TMR_SECOND/10,TimerProc);
}
/*
#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

int wsprintf_bytes(WSHDR *ws, unsigned int bytes)
{
	//char *str;
	if (bytes<=1024)
		return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
	 //str=BYTES_SG;
	else 
	{
		bytes>>=10;
		return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
		//str=KBYTES_SG;
	}  
}


*/  
// ----------------------------------------------------------------------------
#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

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


void Read_Paste(WSHDR *ws)
{
  unsigned int errcode;
  char filename[128];
  volatile int hFile = -1;
  
  sprintf(filename,"%s\\paste.tmo",root_dir);
  hFile = fopen(filename,A_ReadWrite,P_READ+P_WRITE,&errcode);

  if( hFile!=-1 )
    {
      int str_len = 0;
      fread(hFile,&str_len,2,&errcode);
      errcode=0;
      lseek(hFile,0,0,&errcode,&errcode);
      fread(hFile,ws->wsbody,(str_len+1)*2,&errcode);
     }
  fclose(hFile, &errcode);
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      //LockSched();  
      //ShowMSG(1,(int)"FreePaste config updated!");
      //UnlockSched();
      InitConfig();
    }
  }
  csm_result=(msg->msg==ELF_ID)?0:old_icsm_onMessage(data,msg);
  //check if freepaste is enabled first..
  if (cfgenable && IsGuiOnTop(idlegui_id)) //Если IdleGui на само?верх?  
  {
    GUI *igui=GetTopGUI();
    if (igui && GetDataOfItemByID(igui, 2)) //?он существует
    {
/*
#ifdef ELKA
      {
        void *canvasdata = BuildCanvas();
#else
      void *idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
        void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
        DrawCanvas(canvasdata, cfgx, cfgy, cfgx2, cfgy2, 1);
*/
        WSHDR *ws = AllocWS(256);
        Read_Paste(ws);
        //static const int font[3] = {0, 2, 7};
        static const int align[3] = {TEXT_ALIGNLEFT, TEXT_ALIGNMIDDLE, TEXT_ALIGNRIGHT};
        DrawString(ws,cfgx,cfgy,cfgx2,cfgy2, cfgfont/*font[cfgfontsize]+cfgfontbold*/,
                   TEXT_OUTLINE+align[cfgalign],GetPaletteAdrByColorIndex(cfgcolor),GetPaletteAdrByColorIndex(cfgbordercolor));
        
        FreeWS(ws);
//      }
    }
  }
  return(csm_result);
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

// ----------------------------------------------------------------------------

int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsmd.onClose=MyIDLECSM_onClose;
  icsm->constr=&icsmd;
  UnlockSched();
  InitConfig();
  GBS_StartTimerProc(&mytmr,TMR_SECOND,TimerProc);
  return 0;
}
