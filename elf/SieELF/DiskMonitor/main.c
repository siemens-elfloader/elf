#include "..\inc\swilib.h"
#include "cfg.h"

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

extern const int cfgShowIn;

extern const char PIC_PATH[];

extern const int cfgShow0;
extern const unsigned int PicX0;
extern const unsigned int PicY0;
extern const RECT cfgRect0;
extern const int cfgOrient0;
extern const char cfgBorderCol0[4];
extern const char cfgBGCol0[4];
extern const char cfgFillCol0[4];

extern const int cfgShow1;
extern const unsigned int PicX1;
extern const unsigned int PicY1;
extern const RECT cfgRect1;
extern const int cfgOrient1;
extern const char cfgBorderCol1[4];
extern const char cfgBGCol1[4];
extern const char cfgFillCol1[4];

extern const int cfgShow2;
extern const unsigned int PicX2;
extern const unsigned int PicY2;
extern const RECT cfgRect2;
extern const int cfgOrient2;
extern const char cfgBorderCol2[4];
extern const char cfgBGCol2[4];
extern const char cfgFillCol2[4];

extern const int cfgShow4;
extern const unsigned int PicX4;
extern const unsigned int PicY4;
extern const RECT cfgRect4;
extern const int cfgOrient4;
extern const char cfgBorderCol4[4];
extern const char cfgBGCol4[4];
extern const char cfgFillCol4[4];

CSM_DESC icsmd;

#pragma inline=forced
int toupper(int c)
{
  if ((c >= 'a') && (c <= 'z'))
    c += 'A' - 'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i = (c = toupper(*s1++)) - toupper(*s2++))) 
    if (!c)
      break;
  return(i);
}

void ShowDisk(int n, void *CanvasData, const RECT *Rect, int Orient,
              const char *Border, const char *BG, const char *Fill,
              unsigned int PicX, unsigned int PicY)
{
  unsigned int flex_free, flex_total, err;
  unsigned char ratio;
  char pic_name[128];

  flex_free  = GetFreeFlexSpace(n, &err) >> 10;
  flex_total = GetTotalFlexSpace(n, &err) >> 10;
  ratio = 100 * (flex_total - flex_free) / flex_total;
  DrawCanvas(CanvasData, Rect->x, Rect->y, Rect->x2, Rect->y2, 1);

  if (!Orient)
  {
    // hor
    DrawRectangle(Rect->x, Rect->y, Rect->x2, Rect->y2 - 1,
            0, Border, BG);
    DrawRectangle(Rect->x, Rect->y, Rect->x + (Rect->x2 - Rect->x) * ratio / 100 - 1, Rect->y2 - 1,
            0, Border, Fill);
  }
  else
  {
    // vert
    DrawRectangle(Rect->x, Rect->y, Rect->x2 - 1, Rect->y2,
            0, Border, BG);
    DrawRectangle(Rect->x, Rect->y + (Rect->y2 - Rect->y) * (100 - ratio) / 100 - 1, Rect->x2 - 1, Rect->y2,
            0, Border, Fill);
  }

  snprintf(pic_name, 127, "%s\\%i.png", PIC_PATH, n);
  DrawCanvas(CanvasData, PicX, PicY, PicX + GetImgWidth((int)pic_name), PicY + GetImgHeight((int)pic_name), 1);
  DrawImg(PicX, PicY, (int)pic_name);

}

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);


void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data, old_icsm_onClose, &ELF_BEGIN, SEQKILLER_ADR());
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename, (char *)msg->data0) ==0)
    {
      ShowMSG(1, (int)"DiskMon config updated!");
      InitConfig();
    }
  }
  csm_result = old_icsm_onMessage(data, msg);

  if (IsGuiOnTop(idlegui_id))
  {
    GUI *igui = GetTopGUI();
    if (igui)
    {
#ifdef ELKA
      {
        void *canvasdata = BuildCanvas();
#else
      void *idata = GetDataOfItemByID(igui, 2);
      if (idata)
          {
        void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif          
        if (cfgShow0)
          ShowDisk(0, canvasdata, &cfgRect0, cfgOrient0, cfgBorderCol0, cfgBGCol0, cfgFillCol0, PicX0, PicY0);

        if (cfgShow1)
          ShowDisk(1, canvasdata, &cfgRect1, cfgOrient1, cfgBorderCol1, cfgBGCol1, cfgFillCol1, PicX1, PicY1);
        
        if (cfgShow2)
          ShowDisk(2, canvasdata, &cfgRect2, cfgOrient2, cfgBorderCol2, cfgBGCol2, cfgFillCol2, PicX2, PicY2);
        
        if (cfgShow4)
          ShowDisk(4, canvasdata, &cfgRect4, cfgOrient4, cfgBorderCol4, cfgBGCol4, cfgFillCol4, PicX4, PicY4);
      }
    }
  }
  return(csm_result);
}


int main(void)
{
  InitConfig();
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd, icsm->constr, sizeof(icsmd));
  old_icsm_onMessage = icsmd.onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onMessage = MyIDLECSM_onMessage;
  icsmd.onClose=MyIDLECSM_onClose;
  icsm->constr = &icsmd;
  UnlockSched();
  return 0;
}
