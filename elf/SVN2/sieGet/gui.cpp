#include "include.h"
#include "gui.h"

typedef struct
{
  GUI gui;
  AbstractGUI *gui_class;
} MAIN_GUI;

void gui_onredraw (AbstractGUI *data);
void gui_oncreate (AbstractGUI *data, void *(*malloc_adr)(int));
void gui_onclose  (AbstractGUI *data, void (*mfree_adr)(void *));
void gui_onfocus  (AbstractGUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *));
void gui_onunfocus(AbstractGUI *data, void (*mfree_adr)(void *));
int  gui_onkey    (AbstractGUI *data, GUI_MSG *msg);
void gui_ondestroy(AbstractGUI *data, void (*mfree_adr)(void *));
int  gui_method8  (void) {return(0);}; // Пустая ф-я
int  gui_method9  (void) {return(0);};// Пустая ф-я

const void * const gui_methods[11]={
  (void *)gui_onredraw,
  (void *)gui_oncreate,
  (void *)gui_onclose,
  (void *)gui_onfocus,
  (void *)gui_onunfocus,
  (void *)gui_onkey,
  0,
  (void *)gui_ondestroy,	
  (void *)gui_method8,
  (void *)gui_method9,
  0
};

void gui_onredraw(AbstractGUI *data)
{
    data->onRedraw();
}

void gui_oncreate(AbstractGUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
  data->onCreate();
}

void gui_onclose(AbstractGUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
  data->onClose();
}

void gui_onfocus(AbstractGUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  data->onFocus();
}

void gui_onunfocus(AbstractGUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
  data->onUnFocus();
}

int gui_onkey(AbstractGUI *data, GUI_MSG *msg)
{
  return data->onKey(msg->gbsmsg->submess, msg->gbsmsg->msg, msg->keys);
}

void gui_ondestroy(AbstractGUI *data, void (*mfree_adr)(void *))
{
}


//==========================   AbstractGUI   ========================

void AbstractGUI::Create()
{
  zeromem(&gui, sizeof(GUI));
  gui.canvas = &Canvas;
  gui.flag30 = 0;
  gui.methods = (void *)gui_methods;
  gui.item_ll.data_mfree = (void (*)(void *))mfree_adr();
  gui_id = CreateGUI(this);
}

void AbstractGUI::Close()
{
  if (gui_id)
    GeneralFunc_flag1(gui_id, 0);
}

AbstractGUI::AbstractGUI()
{
  gui_id = 0;
  StoreXYXYtoRECT(&Canvas, 0, YDISP, ScreenW()-1, ScreenH()-1);
}

AbstractGUI::~AbstractGUI()
{
  if (gui_id)
    Close();
}
