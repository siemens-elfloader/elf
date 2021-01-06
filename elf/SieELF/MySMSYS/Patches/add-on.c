#include "..\..\inc\swilib.h"
#include "..\MySMSYS_ipc.h"

#define RAM_SMS_dat_FileHandler 0xA8DADE14
#define RAM_WB_dat_FileHandler 0xA8DADE16
#define RAM_EMS_Admin_dat_FileHandler 0xA8DEEA20

const char my_ipc_name[]=MY_SMSYS_IPC_NAME;
const IPC_REQ my_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};

__arm void send_ipc(int ipc_msg)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,ipc_msg,&my_ipc);
}

typedef struct
{
	char header[8];
	int version;
	char time[32];
	char number[32];
}MSS_FILE_P1;

#define TYPE_UNK	0
#define TYPE_OUT	1
#define TYPE_IN_R	2 //readed
#define TYPE_IN_N 	3 //new
#define TYPE_DRAFT	4
#define TYPE_IN_ALL 	5


const char FLDR_IN[]="In\\";
const char FLDR_OUT[]="Out\\";
const char FLDR_DRAFT[]="Draft\\";
const char FLDR_MAIN[]="0:\\ZBin\\MySMSYS\\";

__thumb int getFileCount(int type, int count_old, SMS_DATA_ROOT *sdr)
{
  unsigned int err;
  char dir[128];
  int n=0;
  DIR_ENTRY de;
  strcpy(dir, FLDR_MAIN);
  switch(type)
  {
  case TYPE_DRAFT:
    if(!count_old) n+=sdr->cnt_sms_draft;
    strcat(dir, FLDR_DRAFT);
    break;
  case TYPE_OUT:
    if(!count_old) n+=sdr->cnt_sms_sent;
    strcat(dir, FLDR_OUT);
    break;
  case TYPE_IN_ALL:
    if(!count_old)
    {
      n+=sdr->cnt_msg_in_read;
      n+=sdr->cnt_in_new_sms_dat;
      n+=sdr->cnt_in_new_opwv;
    }
    strcat(dir, FLDR_IN);
    break;
  }
  if(!isdir(dir, &err))
  {
    dir[0]='4';
    if(!isdir(dir, &err))
      return n;
  }
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir, &err))
  {
    do
    {
      if(de.file_size>=(sizeof(MSS_FILE_P1)))
	n++;
    }
    while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  return n;
}

void CreateSmsWithNum(char *num)
{
   IPC_REQ my_ipc3=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  char *data;
  LockSched();
  data=malloc(strlen(num)+2);
  strcpy(data, num);
  my_ipc3.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,&my_ipc3);
  UnlockSched();
}

void CreateSmsWithNum_2(char *num)
{

  IPC_REQ *my_ipc3;
  char *data;
  my_ipc3=malloc(sizeof(IPC_REQ));
  data=malloc(strlen(num)+2);
  my_ipc3->name_to=my_ipc_name;
  my_ipc3->name_from=my_ipc_name;
  strcpy(data, num);
  my_ipc3->data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,my_ipc3);
}

void CreateSmsWithNum_3(char *num)
{

  IPC_REQ *my_ipc3;
  char *data;
  LockSched();
  my_ipc3=malloc(sizeof(IPC_REQ));
  data=malloc(strlen(num)+2);
  my_ipc3->name_to=my_ipc_name;
  my_ipc3->name_from=my_ipc_name;
  strcpy(data, num);
  my_ipc3->data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,my_ipc3);
  UnlockSched();
}

void OrgSendText(char *text) //utf8
{
   IPC_REQ my_ipc4=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  char *data;
  data=malloc(strlen(text)+2);
  strcpy(data, text);
  my_ipc4.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SEND_UTF8,&my_ipc4);
}

void OpmsgIDSend(int submsg, int opmsg_id)
{
   IPC_REQ my_ipc5=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  my_ipc5.data=(void *)opmsg_id;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submsg,&my_ipc5);
}

