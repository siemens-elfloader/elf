#include "..\inc\swilib.h"
#include "IdleLinks.h"
#include "conf_loader.h"
#include "utils.h"
#include "navigation.h"

short *ScreenBuff;

// Здесь лежат все функции по рисованию на идле...

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

extern const char cl[4];
extern const char chpic[128];
extern const char frcol[4];

int CalcPic(char* picture)
{
  if(file_exists(picture))
  {
    return (int)picture;
  }
  else
  {
    return strtoul(picture, 0, 10);
  }
}

void Draw_DoLabel(TLabelData *Link)
{
  switch (Link->Type)
  {
  case 0:
    {
      WSHDR *elfname=AllocWS(strlen(Link->FileName) +1);
      wsprintf(elfname,Link->FileName);
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
    }
    break;
  case 1:
    {
      unsigned int* addr = (unsigned int*)GetFunctionPointer(Link->FileName);
      if (addr)
      {
        typedef void (*voidfunc)(); 
#ifdef NEWSGOLD          
        voidfunc pp=(voidfunc)*(addr+4);
#else 
        voidfunc pp=(voidfunc)addr; 
#endif 
        SUBPROC((void*)pp);
      }
    }
    break;
  case 2:
    {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul(Link->FileName, 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
    }
    break;          
  }  
}

void Draw_NSD(TLabelData *Label)
{
  if (Label->Enabled)
  {
    int pic;
    pic = CalcPic(Label->Pic);
    void *canvasdata = BuildCanvas();
    DrawCanvas(canvasdata,Label->x-1,
                          Label->y-1, 
                          Label->x+GetImgWidth(pic)+1, 
                          Label->y+GetImgHeight(pic)+1, 1); 
    DrawImg(Label->x,Label->y,pic);    
  }
}


void Draw_ScreenShot()
{ 

#ifdef LOG
  log("idle.c", "Draw screenshot", (char*)ScreenBuff);
#endif
  IMGHDR img={ScreenW(),ScreenH(),8 ,(char*)ScreenBuff};
  RECT rc;
  DRWOBJ drwobj;
  
  StoreXYWHtoRECT(&rc,0,0,ScreenW(),ScreenH());
  SetProp2ImageOrCanvas(&drwobj,&rc,0,&img,0,0);
  DrawObject(&drwobj);
}

void Draw_GUI(TLabelData *Label)
{
  //Draw_ScreenShot();
  if (Label->Enabled)
  {  
    int pic;
    pic = CalcPic(Label->Pic);     
    DrawImg(Label->x,Label->y,pic); 
  }

//    DrawCanvas(canvasdata,Label->x-1, Label->y-1,
//               Label->x+GetImgWidth(pic)+1,
//                                  Label->y+GetImgHeight(pic)+1, 1);  
     
}

void Draw_Select(TLabelData *Selected)
{
  if (Selected->Enabled)
  {
    extern const int BCFG_SELECT_TYPE;
    int pic;
    pic = CalcPic(Selected->Pic); 
    if (!BCFG_SELECT_TYPE)
    {
      extern const unsigned int BCFG_ROUND_X;
      extern const unsigned int BCFG_ROUND_Y;
      DrawRoundedFrame(Selected->x-1, Selected->y-1,
                               Selected->x+GetImgWidth(pic)+1,
                               Selected->y+GetImgHeight(pic)+1,BCFG_ROUND_X,BCFG_ROUND_Y,0,frcol,cl); 
      DrawImg(Selected->x,Selected->y,pic); 
    }
    else
    {
      DrawImg(Selected->x+GetImgWidth(pic)-GetImgWidth((int)chpic),
              Selected->y+GetImgHeight(pic)-GetImgHeight((int)chpic),(int)chpic);    
    }
  }
}

