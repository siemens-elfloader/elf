#ifndef _NATIVEADDRESSBOOK_H_
#define _NATIVEADDRESSBOOK_H_

#define NAB_CSM_NAME_LEN 32

#define NAB_SAVE 0 //save to adrbk
#define NAB_TEXT 1 //insert as text
#define NAB_SETC 2 //set as number
#define NAB_INSN 3 //insert as number

class NAbCSM
{
public:
  NAbCSM();
  ~NAbCSM();
  typedef struct _NAb_CSM
  {
    CSM_RAM csm_ram;
    void *ed_gui;
    int ed_gui_id;
    int ab_csm_id;
    char *number;
    int type;
    NativeAbData *nabd;
    NAbCSM *nab;
  }NAb_CSM;
  typedef struct _NAb_CSM_DESC
  {
    CSM_DESC csm_desc;
    WSHDR csm_name;
  }NAb_CSM_DESC;

  int CreateNAbCSM(void *ed_gui, int ed_gui_id, char *number, int type);
private:
  NAb_CSM_DESC nab_csm_desc;
  unsigned short csm_name_body[NAB_CSM_NAME_LEN];
  static int OnMessage(CSM_RAM *data, GBS_MSG *msg);
  static void OnCreate(CSM_RAM *data);
  static void OnClose(CSM_RAM *data);
};

#endif

