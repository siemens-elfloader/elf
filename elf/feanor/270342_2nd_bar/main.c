#include "G:\Iar\inc\swilib.h"
#include "G:\Iar\inc\cfg_items.h"

#pragma segment="CONFIG_C"
#define UPDATE_TIME 100

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);


  int LoadConfigData(const char *fname);

short *bar/* =(short*)0xA868C504*/;
/*36C: 0xA868C4E4   ; f219: RamMainscreenAccuIcon*/



#pragma swi_number=0x80DB
__swi __arm int MSA();



extern const unsigned int bar_1_X ;
extern const unsigned int bar_1_Y ;

extern const unsigned int bar_2_X ;
extern const unsigned int bar_2_Y ;

extern const unsigned int bar_3_X ;
extern const unsigned int bar_3_Y ;

extern const unsigned int bar_4_X ;
extern const unsigned int bar_4_Y ;

//========================================================================
void DrawIconFromBar(int x, int y, int num)
{
  char mm[128];
  sprintf(mm,"0:\\ZBin\\img\\2nd_bar\\%i.png",num);
  DrawImg(x,y,(int)mm);
}

//========================================================================


//========================================================================
int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{  
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    LoadConfigData("0:\\ZBin\\etc\\2nd_bar.bcfg");
  }
  
  int csm_result;
	
	 csm_result=old_icsm_onMessage(data, msg);
        
	
  if (IsGuiOnTop(idlegui_id))
  {
    GUI *igui=GetTopGUI();
    if (igui)
    {
		void* idata = GetDataOfItemByID(igui, 2);
		if (idata)
		{
			//void* canvasdata = ((void**)idata)[DISPLACE_OF_IDLECANVAS / 4];
			//DrawCanvas(canvasdata, cfgX, cfgY, cfgX + GetImgWidth(Icons[iCurrIcon]), cfgY + GetImgHeight(Icons[iCurrIcon]), 1);
			
		}
						
			//DrawImg(acc_X, acc_Y, *RamMSAccuIcon() );	
                
			DrawIconFromBar(bar_1_X, bar_1_Y, bar[0]);	
			DrawIconFromBar(bar_2_X, bar_2_Y, bar[1]);	
			DrawIconFromBar(bar_3_X, bar_3_Y, bar[2]);	
			DrawIconFromBar(bar_4_X, bar_4_Y, bar[3]);
                        
			//DrawImg(net_X, net_Y, *(RamMSAccuIcon()-1) );	
		
    }
  
  }
  return(csm_result);
}

//загрузка конфига
  int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,0,&ul))!=-1)
  {
    if (fread(f,buf,len,&ul)==len)
    {
      memcpy(cfg,buf,len);
      fclose(f,&ul);
    }
    else
    {
      fclose(f,&ul);
      goto L_SAVENEWCFG;
    }
  }
  else
  {
  L_SAVENEWCFG:
    if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,cfg,len,&ul)!=len) result=-1;
      fclose(f,&ul);
    }
    else
      result=-1;
  }
  mfree(buf);
  return(result);
}

//старт
int main(void)
{

    LoadConfigData("0:\\ZBin\\etc\\2nd_bar.bcfg");
  bar =(short*)(MSA()+0x20);

  
  
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  
  //GBS_StartTimerProc(&update_tmr, UPDATE_TIME, GetCurrentIcon);
	
  
  return 0;
}
