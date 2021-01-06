#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "menu.h"
#include "bmplib.h"
#include "lang.h"

extern unsigned int pic_id;
const char *d="%d";

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF) //select
  {
    EDITCONTROL ec;
    char str[8];
    int id=0;
    ExtractEditControl(data, 1,&ec);
    ws_2str(ec.pWS, str, 127);
    for(int i=0; str[i]!=0; i++)
      id=id*10+(str[i]-'0');
    if(GetPITaddr(id)) pic_id=id;
    return 0xFF;
  }
  /*if (msg->keys==0xFF0)  // Back
  {
    pic_id<<8;
  }*/
  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    /*void ed_inp_redraw(void *data);
    int key=msg->gbsmsg->submess;
    switch(key)
    {
    case LEFT_BUTTON: if(pic_id) pic_id--; DirectRedrawGUI(); break;
    case RIGHT_BUTTON: pic_id++; DirectRedrawGUI(); break;
    }
    return 0;*/
  }
  return(0); //Do standart keys
  //1: close
}

/*void ed_inp_redraw(void *data)
{
  DrawImg(ScreenW()/2, ScreenH()/2, pic_id);
}*/

void ed1_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"View"};
  //static SOFTKEY_DESC sk_back={0x0FF0,0x0000,(int)"Back"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_CREATE)
  {
    EDIT_SetFocus(data,2);
    EDIT_SetCursorPos(data,2);
  }
  if (cmd==TI_CMD_REDRAW)
  {
    EDITCONTROL ec;
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
   // SetSoftKey(data,&sk_back,SET_SOFT_KEY_N ? 0 : 1);
    ExtractEditControl(data,1,&ec);
  }
}

void ed1_locret(void){}

static SOFTKEY_DESC input_number_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static SOFTKEYSTAB input_number_skt=
{
  input_number_sk,0
};

HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)"Picture ID:",LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &input_number_skt,
  {0,0,0,0},
  FONT_MEDIUM,
  100,
  101,
  0,
  0,
  0x40000000
};

int CreateEdInputNumber()
{
  void *ma=malloc_adr();
  void *eq;
  
  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  WSHDR *ews=AllocWS(128);
  
  wsprintf(ews, "%d", pic_id);
  ConstructEditControl(&ec, ECT_NORMAL_NUM, ECF_DISABLE_POINT,  ews, 4);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);
  
  FreeWS(ews);
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

//=================================================================================

#define OPTIONS_ITEMS_N 4

int icon_array[1];

MENUITEM_DESC options_items[OPTIONS_ITEMS_N]=
{
    {icon_array,(int)"Input number",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, 
    {icon_array,(int)"Save as BMP",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, 
    {icon_array,(int)"Save Bitmap",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
    {icon_array,(int)"About",                 LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, 
};

void options_create_number(GUI *gui)
{
  CreateEdInputNumber();
  GeneralFuncF1(2);
}

void options_save(GUI *gui)
{
    IMGHDR *img=GetPITaddr(pic_id);
    enum{palette_size=12};
     char palette[palette_size]={0x00, 0xf8, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00};
    char *bitmap=NULL;
    switch(img->bpnum)
    {
        case 0x88:
            bitmap=SieRastrDecoder(img->bitmap, img->w*img->h);
            SaveBMP("0:\\1.bmp", bitmap, img->w, img->h, palette, palette_size, 16, BI_BITFIELDS);
            mfree(bitmap);
        break;
        default:
            ShowMSG(1, (int)"Error");
  }
    GeneralFuncF1(2);
}

void options_about(GUI *gui)
{
  const char *prf="SPView 0.1\n(c)FIL\nCompiled at ";
  char *about=malloc(strlen(prf)+20);
  sprintf(about, "%s%s", prf, __DATE__);
  ShowMSG(0, (int)about);
  mfree(about);
  GeneralFuncF1(2);
}

void options_save_bitmap(GUI *gui)
{
    IMGHDR *img=GetPITaddr(pic_id);
    unsigned int err;
    char fname[128];
    sprintf(fname, "0:\\Pictures\\%d.bitmap", pic_id);
    int fp=fopen(fname, A_WriteOnly+A_Create, P_WRITE, &err);
    if(fp!=-1)
    {
        fwrite(fp, img->bitmap, img->w*img->h*4, &err);
        fclose(fp, &err);
    }
    //char *buf = malloc(img->w*img->h*4);
   // rgb16torgb32(img,buf,img->w*img->h*2);
   // write_png_argb32("0:\\1.png",buf,ScreenW(),ScreenH(),ScreenW()*4);
   // mfree(buf);
    GeneralFuncF1(2);
}

const MENUPROCS_DESC options_procs[OPTIONS_ITEMS_N]=
{
  options_create_number,
  options_save,
  options_save_bitmap,
  options_about,
};

int options_softkeys[]={0,1,2};

SOFTKEY_DESC options_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB options_skt=
{
  options_sk,0
};

MENU_DESC options_struct=
{
  8, NULL, NULL, NULL,
  options_softkeys,
  &options_skt,
  0x00000001,
  NULL,
  options_items,   //Items
  options_procs,   //Procs
  OPTIONS_ITEMS_N //n
};

HEADER_DESC options_header={0,0,0,0,NULL,(int)"Options:",LGP_NULL};

int CreateOptionsMenu(void)
{

    icon_array[0]=1336;
    patch_header_small((HEADER_DESC*)(&options_header));
    return CreateMenu(1, 0, &options_struct, &options_header, 0, OPTIONS_ITEMS_N, 0, 0);
}

//всетаки плачет по этой хуйне си++
