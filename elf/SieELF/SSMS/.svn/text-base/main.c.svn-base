#include "..\inc\swilib.h"
#include "conf_loader.h"

CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);
int sstate = 0;
GBSTMR timer;
int password = 0;
int passpos = 0;
char* myimsi;

void ElfKiller(void) {
    extern void *ELF_BEGIN;
    ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void displayXX(int i, int j) {
  ShowMSG(i, j);
}

int my_keyhook(int submsg, int msg) {
  extern const int CODE;
  int temp = 10;
  if (msg == KEY_UP) {
    if (submsg >= '0' && submsg <= '9') {
      temp = submsg - 48;
      for (int i = 0; i < passpos; i++) {
        temp *= 10;
      }
      password += temp;
      passpos++;
    }
    else if (submsg == '#') {
      if (CODE == password)
        sstate = 1;
    }
    else if (submsg == '*') {
      password = 0;
      passpos = 0;
      sstate = 0;
    }
  }
  return 0;
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg) {
  int csm_result = old_icsm_onMessage(data, msg);
  
  if (msg->msg == MSG_SMS_RX - 1) {
    extern const int OKPRESS;
    if (OKPRESS == 1) {
      ShowMSG(2, (int)"Rebooting!");
      RebootPhone();
    }
    else if (OKPRESS == 2) {
      ShowMSG(2, (int)"Shutting down!");
      SwitchPhoneOff();
    }
  }
  
  extern const int LOCK;
  if (LOCK) {
    SUBPROC((void *)displayXX, 2, (int)"Data init, Please wait!");
  }
  
  return csm_result;  
}

void MyIDLECSM_onClose(CSM_RAM *data) {
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

long StrToLong(char* cValue) {
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

void WriteFlag(char *text) {
  unsigned int ul;
  if (!text) return;
  int f = fopen("2:\\SIMConfig.Dat", A_ReadWrite + A_Create + A_BIN,P_READ + P_WRITE,&ul);
  if (f != -1) {
    fwrite(f, text, 9,&ul);
    fclose(f, &ul);
  }
  mfree(text);
}

int TestActionFlag(char *imsi) {
  int f;
  unsigned int ul;
  char *buf = malloc(9);
  int result = 0;
  if ((f = fopen("2:\\SIMConfig.Dat", A_ReadOnly + A_BIN, 0, &ul)) != -1) {
    
    if (fread(f, buf, 9, &ul) == 9) {
      for (int i = 0; i < 9; i++) {
        if (imsi[i] != buf[i]) {
          result = 1;
          break;
        }
      }
    }
    fclose(f, &ul);
  }
  else {
    fclose(f, &ul);
    WriteFlag(imsi);
  }
  mfree(buf);
  return(result);
}

void security(void) {
  RemoveKeybMsgHook((void *)my_keyhook);
  if (!sstate) {
    WriteFlag(myimsi);
    SUBPROC((void *)ElfKiller); 
    return;
  }

  LockSched();
  CSM_RAM *icsm = FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onClose = icsmd.onClose;
  old_icsm_onMessage = icsmd.onMessage;
  icsmd.onClose = MyIDLECSM_onClose;
  icsmd.onMessage = MyIDLECSM_onMessage;
  icsm->constr = &icsmd;
  UnlockSched();
 
  WSHDR *sw = AllocWS(128);
  WSHDR *te = AllocWS(20);

  extern const char IMEI[];  
  extern const char CONTENT[];
  extern const int DESCRIPTION;
  extern const int BTS;
  
  
  str_2ws(sw, CONTENT, strlen(CONTENT));
  wsAppendChar(sw, 13);
  str_2ws(te, "IMEI:", 6);
  wstrcat(sw, te);
  str_2ws(te, IMEI, strlen(IMEI));
  wstrcat(sw, te);
  
  
  if (BTS) {
    RAMNET *ramnet = malloc(sizeof(RAMNET));
    ramnet = RamNet();
    wsAppendChar(sw, 13);
    str_2ws(te, "CHNo.", 5);
    wstrcat(sw, te);
    wsprintf(te, "%d", ramnet->ch_number);    
    wstrcat(sw, te);
    
    wsAppendChar(sw, 13);
    str_2ws(te, "CI:", 3);
    wstrcat(sw, te);
    wsprintf(te, "%d", ramnet->ci);
    wstrcat(sw, te);
    
    wsAppendChar(sw, 13);
    str_2ws(te, "LAC:", 4);
    wstrcat(sw, te);
    wsprintf(te, "%d", ramnet->lac);  
    wstrcat(sw, te);
  }
  
  if (DESCRIPTION) {
    
    wsAppendChar(sw, 13);
    str_2ws(te, Get_Phone_Info(8), strlen(Get_Phone_Info(8)));
    wstrcat(sw, te);
    
    wsAppendChar(sw, 13);
    str_2ws(te, Get_Phone_Info(9), strlen(Get_Phone_Info(9)));
    wstrcat(sw, te);
    
    wsAppendChar(sw, 13);
    str_2ws(te, Get_Phone_Info(7), strlen(Get_Phone_Info(7)));
    wstrcat(sw, te);
  }
  
  extern const char NUMBER[];
  SendSMS(sw, NUMBER, 0x4209, MSG_SMS_RX - 1, 6);  
}

int main(void) {
  extern const char IMSI[];
  InitConfig();
  myimsi = malloc(9);
  char *b = malloc(11);
  memcpy(b, IMSI, 11);
  memcpy(myimsi, (char*)StrToLong(b), 9);
  if (!TestActionFlag(myimsi)) return 0;
  sstate = 1;
  extern const int DELAY;
  AddKeybMsgHook((void *)my_keyhook);
  GBS_StartTimerProc(&timer, DELAY * 1000, security);
  return 1;
}
