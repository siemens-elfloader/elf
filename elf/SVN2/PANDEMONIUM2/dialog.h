#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "include.h"
#include "csm.h"
#include "list.h"
#include "langpack.h"
#include "iconpack.h"

class PandemonuimDialog: public DialogCSM
{
public:
  virtual void onCreate();
  virtual int onMessage(GBS_MSG *msg);
  virtual void onClose();
  
  PandemonuimDialog();
  ~PandemonuimDialog();
  List * list;
  
//  void RefreshList();
private:
  IconPack * iconpack;
};

//

#endif
