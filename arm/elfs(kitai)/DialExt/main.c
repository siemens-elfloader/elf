#include "..\inc\swilib.h"
#include "conf_loader.h"

extern const char FUNC_FILE_NAME[];

extern const char REFRESH[];
extern const char QUIT[];
extern const char REBOOT[];
extern const char SHUTOFF[];

extern const int GREEN_LAUNCH_FLAG;
extern const int START_FLAG;

CSM_DESC icsmd, *oldicsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);
int (*old_ed_onkey)(GUI *gui, GUI_MSG *msg);
volatile int hook_state = 0;
char func_text[32768];
int text_size = 0;

void ElfKiller(void) {
  extern void *ELF_BEGIN;
  LockSched();
  CSM_RAM *icsm = FindCSMbyID(CSM_root()->idle_id);
  icsm->constr = oldicsmd;
  UnlockSched();
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int readListFile() {
  int f;
  unsigned int ul;
  int result = 0;
  
  if ((f = fopen(FUNC_FILE_NAME, A_ReadOnly + A_BIN, P_READ, &ul)) != -1) 
  {
    text_size = fread(f, func_text, 32766, &ul);
    fclose(f, &ul);
    if (text_size <= 0) 
	{
      result = 0;
    }
    else 
	{
      func_text[text_size] = '\0';
      result = 1;
    }
  }
  else
    result = -1;
  return result;
}

long StrToLong(char* cValue) 
{
  if (!cValue) return 0;
  long iValue = 0;
  long temp = 0;
  int len = strlen(cValue);
  int j = 0;
  for (int i = len; i > 0; i--) {
    if (cValue[i - 1] >= '0' && cValue[i - 1] <= '9') {
      temp = cValue[i - 1] - 48;
    }
    else if (cValue[i - 1] >= 'A' && cValue[i - 1] <= 'F') {
      temp = cValue[i - 1] - 55;
    }
    else if (cValue[i - 1] >= 'a' && cValue[i - 1] <= 'f') {
      temp = cValue[i - 1] - 87;
    }
    for (j = 0; j < len - i; j++)
      temp = (long) (temp * (long)16);
    iValue = (long) (iValue + temp);

  }
  return iValue;;
}

int RereadSettings() {
  InitConfig();
  if (readListFile() <= 0) return 0;
  return 1;
}

int runSystem(char *text) {
  
  int r = 0;
  char *p;
  /** 首先测试是否为系统功能*/
  if (strlen(text) == strlen(REFRESH)) {
    p = strstr(REFRESH, text);
    if (p) {
      DoIDLE();
      ShowMSG(1, (int)"Reflashing seting!");
      if (!RereadSettings()) {
        SUBPROC((void *)ElfKiller);
        r = 1;
      }
    }
  }
  
  if (strlen(text) == strlen(QUIT)) {  
    p = strstr(QUIT, text);
    if (p) {
      DoIDLE();
      ShowMSG(1, (int)"Quit DialExt!");
      SUBPROC((void *)ElfKiller);
      r = 1;
    }
  }

  if (strlen(text) == strlen(REBOOT)) {  
    p = strstr(REBOOT, text);
    if (p) {
      DoIDLE();
      ShowMSG(1, (int)"Rebooting phone!");
      RebootPhone();
      r = 1;
    }
  }
  
  if (strlen(text) == strlen(SHUTOFF)) {
    p = strstr(SHUTOFF, text);
    if (p) {
      DoIDLE();
      ShowMSG(1, (int)"Switching phone off!");
      SwitchPhoneOff();
      r = 1;
    }
  }
  return r;
}

char *getFuncText(WSHDR *key) {
  char *text = malloc(10);
  char *p;
  ws_2str(key, text, 10);
  if (runSystem(text)) return NULL;
  p = strstr(func_text, text);
  while (p) {
    
    if ( *(p + strlen(text)) == '=' && 
          (
            (
                p > func_text && 
                 (
                    *(p - 1) == '\n' || 
                    *(p - 1) == '\r'
                  ) ||
                p == func_text
              )
           )) {     //存在此项目
      p = p + strlen(text) + 1;
      mfree(text);
      text = malloc(128);
      memcpy(text, p, 128);
      for (int i = 0; i < 128; i++) {
        if (text[i] == '\r' || text[i] == '\n') {
          text[i] = '\0';
          return text;
        }
      }
      text[127] = '\0';
      return text;
    }
    else {
      p = strstr((p + strlen(text)), text);
    }
  }
  return NULL;
}

int runFile(char *file) {
  if (file) 
  {
    if (strlen(file)) 
	{
      WSHDR *ws;
      ws=AllocWS(150);
      str_2ws(ws, file, 128);
      ExecuteFile(ws, 0, 0);
      FreeWS(ws);
      return 1;
    }
  }
  return 0;
}

int runShorcut(char *shorcut) 
{

  void (*runfunc)(void);
  runfunc = (void (*)()) GetFunctionPointer(shorcut);
  if (runfunc) 
  {
    runfunc();
    return 1;
  }
  return 0;
}

int runAddress(long address) 
{
  void (*runaddr)(void);
  runaddr = (void (*)()) address;
  if (runaddr) 
  {
    runaddr();
    return 1;
  }
  return 0;
}

int runFunc(char *func) {
  if (!func) return 0;
  DoIDLE();
  if (func[0] >= '0' && func[0] <= '9') {
    if (func[1] == 'x' || func[1] == 'X') { //地址
      char *p;
      p = func + 2;
      runAddress(StrToLong(p));
    }
    else {
      runFile(func);
    }
  }
  else {
    runShorcut(func);
  }
  return 1;
}

int my_ed_onkey(GUI *gui, GUI_MSG *msg) {
  int r;
  int key = msg->gbsmsg->submess;
  int m = msg->gbsmsg->msg;
  EDITCONTROL ec;
  if (m == KEY_UP) {
    if ((key >= '0' && key <= '9') || (key == '*') || (key == '#')) {
      ExtractEditControl(gui, 1, &ec);
      runFunc(getFuncText(ec.pWS));
    }
  }
  r = old_ed_onkey(gui, msg);
  return(r);
}

void doSplices(GUI *gui) {
  static INPUTDIA_DESC my_ed;
  memcpy(&my_ed, gui->definition, sizeof(INPUTDIA_DESC));
  old_ed_onkey = my_ed.onKey;
  my_ed.onKey = my_ed_onkey;
  gui->definition = &my_ed;
}

int myIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg) 
{
  
#define edialgui_id (((int *)data)[DISPLACE_OF_EDGUI_ID/4])
  int csm_result;

  if (msg->msg == MSG_GUI_DESTROYED) 
  {
    if ((int)msg->data0 == edialgui_id) 
	{
      hook_state = 0;
    }
  }
  
  else if (msg->msg == MSG_RECONFIGURE_REQ) {
    RereadSettings();
  }
  
  if (!hook_state) 
  {
    if (IsGuiOnTop(edialgui_id)) 
	{
      GUI *igui = GetTopGUI();
      if (igui) 
	  {
        doSplices(igui);
	    hook_state = 1;
      }
    }
  }

  csm_result = old_icsm_onMessage(data, msg);
  return(csm_result);
}

void myIDLECSM_onClose(CSM_RAM *data) {
  
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data, old_icsm_onClose, &ELF_BEGIN, SEQKILLER_ADR());
}

int main(void) {
  if (!RereadSettings()) {
    ShowMSG(1, (int)"Can't find DialExt.txt!");
    return 0;
  }
  if (START_FLAG) {
    ShowMSG(1, (int)"DialExt starts successful!\nby HanikLZ 2007");
  }
  LockSched();
  CSM_RAM *icsm = FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd, icsm->constr, sizeof(icsmd));
  old_icsm_onMessage = icsmd.onMessage;
  old_icsm_onClose = icsmd.onClose;
  icsmd.onClose = myIDLECSM_onClose;
  icsmd.onMessage = myIDLECSM_onMessage;
  oldicsmd = icsm->constr;
  icsm->constr = &icsmd;
  UnlockSched();
  return 1;
}
