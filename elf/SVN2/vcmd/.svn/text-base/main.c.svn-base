#include "..\inc\swilib.h"
#include <stdbool.h>
#include "conf_loader.h"
#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#include "..\inc\mplayer.h"
#endif

#define IPC_CHECK_DOUBLERUN 1
//#define KEY '2'//debug!!
#define KEY PTT_BUTTON//код клавиши
#define INTERVAL_SPELLTIME 4//интервал до завершения произношения времени
#define INTERVAL_CHECK_CALL 2//интервал проверки завершения звонка

const int minus11=-11;
const char ipc_my_name[32]="vcmd";

typedef struct {
 CSM_RAM csm;
} MAIN_CSM;

enum {STATUS_PREP_IDLE, STATUS_IDLE, STATUS_PREP_LIST, STATUS_LIST_CMDS, STATUS_RUN_CMD, STATUS_QUIT, STATUS_PROC_CFG};
typedef enum {CMD_TIME, CMD_CALL, CMD_EXEC, CMD_PLAY, CMD_SIM, CMD_QUIT} tCmdType;
typedef struct {
 tCmdType type;
 char *sndfile, *param1, *param2;
 void *next;
} tCmd;

extern const int ENA_MSGS;//включены сообщения о старте и выходе?
extern const unsigned int INTERVAL_NEXTCMD;//интервал между воспроизведениями команд
extern const char vcmdcfg_fname[128];
extern const char quit_fname[128];
//---------------------------------------------------------------------------
char *scfg;//текстовый конфиг
tCmd *cmd, *pcmd, *pcur;//список команд, текущая/следующая команда, временный указатель на текущую команду
int mode, ncmd, my_csm_id;//режим, номер текущей команды, id нашего CSM
GBSTMR tmrListCmd, tmrSetIdle;
IPC_REQ gipc;
//---------------------------------------------------------------------------
extern void kill_data(void *p, void (*func_p)(void*));
static void Killer();

void Play(const char *fname) {
 PLAYFILE_OPT pfo;
 WSHDR *sndPath=AllocWS(128);
 WSHDR *sndFName=AllocWS(128);
 char s[128];
 const char *p=strrchr(fname,'\\')+1;

 str_2ws(sndFName, p, 128);
 strncpy(s, fname, p-fname);
 s[p-fname]='\0';
 str_2ws(sndPath, s, 128);

 zeromem(&pfo, sizeof(PLAYFILE_OPT));
 pfo.repeat_num=1;
 pfo.time_between_play=0;
 pfo.play_first=0;
 pfo.volume=6;
#ifdef NEWSGOLD
 pfo.unk6=1;
 pfo.unk7=1;
 pfo.unk9=2;
 PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfo);
#else
#ifdef X75
 pfo.unk4=0x80000000;
 pfo.unk5=1;
 PlayFile(0xC, sndPath, sndFName, 0, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfo);
#else
 pfo.unk5=1;
 PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfo);
#endif
#endif
 FreeWS(sndPath);
 FreeWS(sndFName);
}

char *loadfile(const char *filename) {
 int f;
 unsigned int err, size;
 char *buf=NULL;

 if ((f=fopen(filename, A_ReadOnly+A_BIN, 0, &err))!=-1) {
  if (size=lseek(f, 0, S_END, &err, &err)) {
   buf=(char*)malloc(size+1);
   lseek(f, 0, S_SET, &err, &err);
   if (fread(f, buf, size, &err)!=size) {
    mfree(buf);
    buf=NULL;
   }
   else
    buf[size]='\0';
  }
  fclose(f, &err);
 }
 return buf;
}

char *pstrspn(char *s1, char *s2) {
 while (*s1) {
  char *p2=s2;
  while (*p2 && *s1!=*p2)
   p2++;
  if (!*p2)
   return s1;
  s1++;
 }
 return s1;
}
//---------------------------------------------------------------------------
bool ParseCmd(char *scfg, tCmd *cmd) {
 char *p=scfg, *end=scfg+strlen(scfg);
 int c;

 //Определение имени файла
 c=strcspn(p, "| \r\n");
 if (c==0)//нет имени файла?
  return false;
 p[c]='\0';
 cmd->sndfile=p;

 //Определение типа команды
 p=pstrspn(p+c+1, "| \r\n");
 if (!*p)//нет типа команды?
  return false;
 c=strcspn(p, "| \r\n");
 p[c]='\0';
 if (!strcmpi(p, "TIME")) {
  cmd->type=CMD_TIME;
  return true;
 }
 else if (!strcmpi(p, "CALL"))
  cmd->type=CMD_CALL;
 else if (!strcmpi(p, "SIM"))
  cmd->type=CMD_SIM;
 else if (!strcmpi(p, "EXEC"))
  cmd->type=CMD_EXEC;
 else if (!strcmpi(p, "PLAY")) {
  cmd->type=CMD_PLAY;
  return true;
 }
 else if (!strcmpi(p, "QUIT")) {
  cmd->type=CMD_QUIT;
  return true;
 }
 else
  return false;

 //Определение параметров
 p=pstrspn(p+c+1, "| \r\n");
 if (!*p)//нет параметров?
  return false;
 c=strcspn(p, "| \r\n");
 p[c]='\0';
 cmd->param1=p;
 if (cmd->type==CMD_EXEC) {
  p+=c+1;
  if (p>=end)
   cmd->param2="";
  else
   cmd->param2=p;
 }
 return true;
}

tCmd* ParseConfig(char *scfg) {
 char *p=scfg, *end=scfg+strlen(scfg);
 int c;
 tCmd cmd, *first=NULL, *cur, *prev=&cmd;

 do {
  p=pstrspn(p, " \r\n");//пропускаем от начала пробелы
  if (!*p)
   break;
  c=strcspn(p, "\r\n");//ищем конец строки. Внутри строки допустимы пробелы!
  p[c]='\0';
  if (ParseCmd(p, &cmd)) {
   cur=(tCmd*)malloc(sizeof(tCmd));
   if (!first)
    first=cur;
   *cur=cmd;//скопировали содержимое новой ком.
   prev->next=cur;//установили ссылку с пред.
   cur->next=NULL;//след. ком. неизвестна
   prev=cur;//передвинули указатель вперёд
  }
  p+=c+1;
 } while (p<end && *p);
 cur=(tCmd*)malloc(sizeof(tCmd));
 cur->type=CMD_QUIT; cur->sndfile=(char*)quit_fname; cur->next=NULL;
 if (first) {//список не пустой?
  prev->next=cur;//добавляем в конец списка команду выхода
 }
 else
  first=cur;
 return first;
}

void FreeCmdList(tCmd *cmd) {
 tCmd *p;

 while (cmd) {
  p=cmd->next;
  mfree(cmd);
  cmd=p;
 }
}
//---------------------------------------------------------------------------
void SpellCommand() {
 if (mode==STATUS_LIST_CMDS) {//идёт проговаривание команд?
  if (pcmd) {//и список команд не закончился?
   Play(pcmd->sndfile);
#ifdef NEWSGOLD
   int wl=GetWavLen(pcmd->sndfile);
   GBS_StartTimerProc(&tmrListCmd, (wl+INTERVAL_NEXTCMD)<<8, SpellCommand);
#else
   TWavLen wl;
   zeromem(&wl, sizeof(wl));
   wl.type=0x2000; wl.wfilename=AllocWS(128);
   str_2ws(wl.wfilename, pcmd->sndfile, 128);
   GetWavLen(&wl);
   GBS_StartTimerProc(&tmrListCmd, (wl.length>>2)+(INTERVAL_NEXTCMD<<8), SpellCommand);
   FreeWS(wl.wfilename);
#endif
   ncmd++; pcur=pcmd; pcmd=pcmd->next;
  }
  else
   mode=STATUS_IDLE;
 }
}

void SetIdle_TIME() {
 mode=STATUS_IDLE;
}

void SetIdle_CALL() {
 if (IsCalling())
  GBS_StartTimerProc(&tmrSetIdle, 2<<8, SetIdle_CALL);
 else
  mode=STATUS_IDLE;
}

void RunCommand() {
 int len;
 WSHDR *ws;
 static IPC_REQ ipc_multisim;

 switch (pcur->type) {
 case CMD_TIME:
  SpellTime();
  GBS_StartTimerProc(&tmrSetIdle, INTERVAL_SPELLTIME<<8, SetIdle_TIME);
  break;
 case CMD_CALL:
  MakeVoiceCall(pcur->param1, 0x10, 0x20C0);
  GBS_StartTimerProc(&tmrSetIdle, INTERVAL_CHECK_CALL<<8, SetIdle_CALL);
  break;
 case CMD_EXEC:
  len=strlen(pcur->param1)+1;
  ws=AllocWS(len<<1);
  str_2ws(ws, pcur->param1, len);
  ExecuteFile(ws, 0, pcur->param2);
  FreeWS(ws);
  mode=STATUS_IDLE;
  break;
 case CMD_SIM:
  ipc_multisim.name_to="MultiSim";
  ipc_multisim.name_from="vcmd";
  ipc_multisim.data=(void*)StrToInt(pcur->param1, NULL);
  GBS_SendMessage(MMI_CEPID, MSG_IPC, 1, &ipc_multisim);
  mode=STATUS_IDLE;
  break;
#ifdef NEWSGOLD
 case CMD_PLAY:
  MPlayer_Start();
  mode=STATUS_IDLE;
  break;
#endif
 default:
  ShowMSG(1, (int)"Under construction!");
  mode=STATUS_IDLE;
  break;
 }
}
//---------------------------------------------------------------------------
int my_keyhook(int submsg, int msg) {
 if (submsg!=KEY || IsCalling())
  return 0;
 switch (msg) {
 case KEY_DOWN:
  return 0;
 case KEY_UP:
  switch (mode) {
  case STATUS_PREP_LIST://готовы к перечисленю команд
   mode=STATUS_LIST_CMDS; ncmd=0; pcmd=cmd;
   SUBPROC((void*)SpellCommand);//воспроизведение списка команд
   break;
  case STATUS_LIST_CMDS://идёт перечисление команд
   if (pcur->type==CMD_QUIT) {
    LockSched();
    mode=STATUS_QUIT;
    if (ENA_MSGS)
     ShowMSG(1, (int)"Voice commands disabled!");
    UnlockSched();
    CloseCSM(my_csm_id);
   }
   else {
    mode=STATUS_RUN_CMD;
    SUBPROC((void*)RunCommand);//запуск команды на выполнение
   }
   break;
  case STATUS_PREP_IDLE:
   mode=STATUS_IDLE;
   if (ENA_MSGS)
    ShowMSG(1, (int)"Commands enumeration cancelled");
   break;
  }
  break;
 case LONG_PRESS:
  switch (mode) {
  case STATUS_IDLE:
   mode=STATUS_PREP_LIST;//готовимся к перечисленю команд
   break;
  case STATUS_LIST_CMDS://идёт перечисление команд
   mode=STATUS_PREP_IDLE;
   break;
  }
 }
 return 2;
}
//---------------------------------------------------------------------------
void CheckDoubleRun(void) {
 LockSched();
 if ((int)(gipc.data)!=-1) {
  CloseCSM(my_csm_id);
  if (ENA_MSGS)
   ShowMSG(1, (int)"Voice commands already started!");
 }
 else {
  if (ENA_MSGS)
   ShowMSG(1, (int)"Voice commands enabled!");
 }
 UnlockSched();
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg) {
 IPC_REQ *ipc;

 switch (msg->msg) {
 case MSG_RECONFIGURE_REQ:
  if (strcmpi(successed_config_filename, (char*)msg->data0)==0) {
   if (ENA_MSGS)
    ShowMSG(1, (int)"vcmd config updated!");
   InitConfig();
   mode=STATUS_PROC_CFG;//создание списка команд не должно выполняться параллельно
   FreeCmdList(cmd);
   mfree(scfg);
   scfg=loadfile(vcmdcfg_fname);
   if (scfg==NULL) {//если не смогли прочитать файл с командами - придётся создать пустой конфиг
    scfg=(char*)malloc(1); scfg[0]='\0';
   }
   cmd=ParseConfig(scfg);//всегда добавляется CMD_QUIT
   mode=STATUS_IDLE;
  }
  break;
 case MSG_IPC:
  ipc=(IPC_REQ*)msg->data0;
  if (ipc!=NULL && strcmpi(ipc->name_to, ipc_my_name)==0 && msg->submess==IPC_CHECK_DOUBLERUN) {//Если приняли свое собственное сообщение, значит запускаем чекер
   if (ipc->name_from==ipc_my_name)
    SUBPROC((void*)CheckDoubleRun);
   else
    ipc->data=(void*)my_csm_id;
  }
  break;
 }
 return 1;
}

static void maincsm_oncreate(CSM_RAM *data) {
 gipc.name_to=ipc_my_name;
 gipc.name_from=ipc_my_name;
 gipc.data=(void *)-1;
 GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_CHECK_DOUBLERUN, &gipc);
}

static void Killer() {
 extern void *ELF_BEGIN;
 GBS_DelTimer(&tmrListCmd);
 RemoveKeybMsgHook((void*)my_keyhook);
 FreeCmdList(cmd);
 mfree(scfg);
 kill_data(&ELF_BEGIN, (void (*)(void*))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm) {
 SUBPROC((void*)Killer);
}
//---------------------------------------------------------------------------
static unsigned short maincsm_name_body[140];

static const struct {
 CSM_DESC maincsm;
 WSHDR maincsm_name;
} MAINCSM = {
 {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
 },
 {
  maincsm_name_body,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139
 }
};

static void UpdateCSMname() {
 wsprintf((WSHDR*)(&MAINCSM.maincsm_name), "vcmd");
}
//---------------------------------------------------------------------------
void main() {
 InitConfig();//читаем конфиг
 scfg=loadfile(vcmdcfg_fname);
 if (scfg) {
  CSM_RAM *save_cmpc;
  MAIN_CSM main_csm;
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  my_csm_id=CreateCSM(&MAINCSM.maincsm, &main_csm, 0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;

  cmd=ParseConfig(scfg);//всегда добавляется CMD_QUIT
  mode=STATUS_IDLE;
  AddKeybMsgHook((void*)my_keyhook);
  UnlockSched();
 }
 else
  ShowMSG(1, (int)"Command config not found!");
}
