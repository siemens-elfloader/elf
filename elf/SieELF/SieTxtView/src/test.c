
int vw_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if(msg->gbsmsg->submess==ENTER_BUTTON||msg->gbsmsg->submess==LEFT_SOFT)
    {
      int i=GetCurMenuItem(data);
      switch(i)
      {
        case 0 :
          MM_Sort();
          break;
        case 1 :
          MC_Filter();
          break;
        case 2 :
          MC_Refresh();
          break;
      }
    }
  }
  return (0);
}

const ZH_ITEM zh_vw_menu_item[3]={
  {"ÅÅÐò"},
  {"¹ýÂË"},
  {"Ë¢ÐÂ"},
};

void vw_menu_iconhndl(void *data, int curitem, void *unk)
{
  addtomenuitem(data, curitem, zh_vw_menu_item);
}

MENU_DESC vw_menu=
{
	8,vw_menu_onkey,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0x10,
	vw_menu_iconhndl,
	NULL,
	NULL,
	0
};