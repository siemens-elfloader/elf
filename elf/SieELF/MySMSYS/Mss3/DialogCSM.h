#ifndef _DIALOGCSM_H_
#define _DIALOGCSM_H_
#define DLGCSM_NAME_LEN 32

class DialogCSM
{
  typedef struct _DLG_CSM
  {
    CSM_RAM csm_ram;
    int gui_id;
    DialogCSM *dlg;
  }DLG_CSM;
public:
  DialogCSM();
  ~DialogCSM();
  int CreateDialogCSM(int submsg, void *ipc_data);
  void UpdateNameDlgCSM(DLG_CSM *dlg_csm, int lgp);
private:
  int submsg;
  void *ipc_data;
  DLGCSM_DESC dlg_csm_desc;
  unsigned short csm_name_body[DLGCSM_NAME_LEN];
  static int OnMessage(CSM_RAM *data, GBS_MSG *msg);
  static void OnCreate(CSM_RAM *data);
  static void OnClose(CSM_RAM *data);
};



#endif

