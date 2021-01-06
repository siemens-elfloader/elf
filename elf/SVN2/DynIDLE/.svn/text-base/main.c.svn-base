#include "..\inc\swilib.h"

GUI *igui;

unsigned int selected_item=4;

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void DrawSelectedFrame(void *gui, int f)
{
  const char color1[]={255,255,255,50};
  short **p=GetDataOfItemByID(gui,selected_item);
  int x1,x2,y1,y2;
  if (!p) return;
  if (!p[2]) return;
  x1=p[2][0];
  y1=p[2][1];
  x2=p[2][2];
  y2=p[2][3];
  if (f) DrawRoundedFrame(x1,y1,x2,y2,0,0,0,
			  color1,
			  color1);
    else
  DrawCanvas(BuildCanvas(),x1,y1,x2,y2,1);          
}

int my_keyhook(int submsg, int msg)
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  short **p;
  if (!icsm) return 0;
  if (!IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return 0;
  if (!(igui=GetTopGUI())) return 0;
  p=GetDataOfItemByID(igui,selected_item);
  if (!p) return 0;
  if (!p[2]) return 0;
  if ((msg==KEY_DOWN)||(msg==KEY_UP)||(msg==LONG_PRESS))
  {
    if ((msg==KEY_DOWN)||(msg==LONG_PRESS))
    {
      DrawSelectedFrame(igui,0);
      switch(submsg)
      {
      case RIGHT_SOFT:
	RemoveKeybMsgHook((void *)my_keyhook);
	RefreshGUI();
	SUBPROC((void *)ElfKiller);
	return 2;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
	selected_item=submsg-'1'+4;
	RefreshGUI();
	break;
      case LEFT_BUTTON:
	if (p[2][0])
	{
	  p[2][0]--;
	  p[2][2]--;
	}
	break;
      case RIGHT_BUTTON:
	if (p[2][2]<(ScreenW()-1))
	{
	  p[2][0]++;
	  p[2][2]++;
	}
	break;
      case UP_BUTTON:
	if (p[2][1])
	{
	  p[2][1]--;
	  p[2][3]--;
	}
	break;
      case DOWN_BUTTON:
	if (p[2][3]<(ScreenH()-1))
	{
	  p[2][1]++;
	  p[2][3]++;
	}
	break;
      case '7':
	if (p[2][2]>(p[2][0]+4)) p[2][2]--;
	break;
      case '9':
	if (p[2][2]<(ScreenW()-1)) p[2][2]++;
	break;
      case '8':
	if (p[2][3]>(p[2][1]+4)) p[2][3]--;
	break;
      case '0':
	if (p[2][3]<(ScreenH()-1)) p[2][3]++;
	break;
      }
      DrawSelectedFrame(igui,1);
    }
    return 2;
  }
  return 0;
}

int main(void)
{
  LockSched();
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  return 0;
}
