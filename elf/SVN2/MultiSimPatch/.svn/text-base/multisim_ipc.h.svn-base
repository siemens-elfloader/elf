#ifndef _MULTISIM_IPC_H_
#define _MULTISIM_IPC_H_
typedef  unsigned char byte;
typedef  unsigned short word;
typedef  unsigned int dword;

  #define MAX_SIM_CNT (19+1)
  #define BL_SZ_5401  (0x30*MAX_SIM_CNT)
  #define BL_SZ_5402  (0x50*MAX_SIM_CNT)
  #define BL_SZ_5403  0x50
#pragma pack(1)
typedef struct   {
  byte LOCI[16];//0x00
  byte BCCH[16];//0x10
  byte KC[10];  //0x20
  byte FLAGSR[4];//0x2A    
  byte pad;      //0x2E
  byte simnum;   //0x2F     
  byte SMSC[16]; //0x30   
  byte FLAGS[12]; //040     
  byte num2sw;//0x4c
  byte time2sw;  
  byte sms_profile;    
  byte inet_profile;      
}BLOCK5403;
;
typedef struct {
  byte IMSI[16];
  byte KI[16];
  union {
  byte SPN[16]; 
  struct{
    byte SPNsub;
    byte SPNname[15];
  };
  };
}BLOCK5401;
#pragma pack()
//ipc send 2 patch
  #define IPC_MSIM_NAME "MultiSim"
  #define ELF_MSIM_NAME "MultiSimElf"
  #define IPC_MSIM_SWITCH 1
//  #define IPC_MSIM_5400_READ 1
//  #define IPC_MSIM_5400_WRITE 2 
/*  #define IPC_MSIM_GET_RAM5400 3
  #define IPC_MSIM_EEPROM_BACKDOOR 4
  #define IPC_MSIM_EEPROM_BACKDOOR_READ 4
  #define IPC_MSIM_EEPROM_BACKDOOR_WRITE 5
  #define IPC_MSIM_EEPROM_BACKDOOR_VERS */

  #define IPC_MSIM_EEPROM_AUTOSEARCH 7
/*
//const for replies from patch
  #define PRC_MSIM_RAM5400 0x00  
  #define PRC_MSIM_READBLOCK 0x10  
  #define PRC_MSIM_READBLOCK2FILE 0x11
  #define PRC_MSIM_WRITEBLOCK 0x20
  #define PRC_MSIM_WRITEBLOCK4FILE 0x21
*/
//ipc replies from patch
/*
#define IPC_MSIM_PROCESSED 0x100

  #define IPC_MSIM_PROCESSED_READBLOCK (IPC_MSIM_PROCESSED+PRC_MSIM_READBLOCK)
  #define IPC_MSIM_PROCESSED_WRITEBLOCK (IPC_MSIM_PROCESSED+PRC_MSIM_WRITEBLOCK)

  #define IPC_MSIM_PROCESSED_READBLOCK2FILE (IPC_MSIM_PROCESSED+PRC_MSIM_READBLOCK2FILE)
  #define IPC_MSIM_PROCESSED_WRITEBLOCK4FILE (IPC_MSIM_PROCESSED+PRC_MSIM_WRITEBLOCK4FILE)
*/
  #define IPC_MSIM_SWITCHED 10  
/*
typedef struct
{
	char msg_version;   // Версия структуры обмена
	char type;	
	int block;
	void *buf;
	int offset;
	int size;
}MSIM_IPC_MSG_EEPROM;


typedef struct
{
  int  SimCnt;
  int  CurSim;
  char SimNames[20][16];
  char SimFlags[20][4];//maybe add simnum  
}MSIM_ELF_RESP;
*/
#endif

