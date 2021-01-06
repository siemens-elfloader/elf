#ifndef _DAEMONCSM_H_
#define _DAEMONCSM_H_

#include "..\..\INC\swilib.h"	// Added by ClassView
#define DLGCSM_ID_MAX 32
#define DAEMON_NAME_LEN 32

#define ICONBAR
typedef struct _ICONBAR_H
{
  char check_name[8];
  int addr;
}ICONBAR_H;

class DaemonCSM
{
  typedef struct _DAEMON_CSM_DESC
  {
    CSM_DESC csm_desc;
    WSHDR csm_name;
#ifdef ICONBAR
    ICONBAR_H iconbar_handler;
#endif
  }DAEMON_CSM_DESC;
  typedef struct _DAEMON_CSM
  {
    CSM_RAM csm_ram;
    DaemonCSM *daemon;
  }DAEMON_CSM;
public:
//	static const CSM_DESC csm_desc_tpl;
	static void StartDialog(int submess, void *data);
	SendList * sndlst;
  DaemonCSM();
  ~DaemonCSM();
  void CreateDaemonCSM(void);
  static CSM_RAM * GetTopCSM(void);
private:
#ifdef ICONBAR
  static void AddIconBar(short* num);
#endif
  DAEMON_CSM_DESC daemon_csm_desc;
  int DLGCSM_IDS[DLGCSM_ID_MAX];
  unsigned short csm_name_body[DAEMON_NAME_LEN];
  GBSTMR chktmr;
  int temp_tmr_index;
  int is_new_proc;
//  int PLAY_ID;
  PlaySouNd *playsound;
  Vibra *vibra;
  //ShortVibra *shortvibra;
  int AddDlgCsmID(int id);
  void AddDlgCsmID_Forced0(int id);
  void DelDlgCsmID(int id);
  void CloseAllDlgCSM(void);
  int IsOnTopMyCSM(void);
  static void OnCreate(CSM_RAM *data);
  static int OnMessage(CSM_RAM *data, GBS_MSG *msg);
  static void OnClose(CSM_RAM *data);
  static void DoNewProc(void);
  static void UpdateNProc(void);
};

#endif

