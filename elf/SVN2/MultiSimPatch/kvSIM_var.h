#ifndef __KV_SIM_VAR_H__
#define __KV_SIM_VAR_H__

//#include ".\..\inc\swilib.h"
#include "multisim_ipc.h"

#define KI_BYTE_LEN         	16
#define SRES_BYTE_LEN       	4
#define KC_BYTE_LEN         	8
#define SIM_RSP_LEN         	(SRES_BYTE_LEN + KC_BYTE_LEN)
#define IMSI_DATA_BYTE_LEN  	9  
#define LOCI_DATA_BYTE_LEN      11
#define FPLMN_DATA_BYTE_LEN      12
#define BCCH_DATA_BYTE_LEN      16
#define KC_DATA_BYTE_LEN        9

#define SPN_DATA_BYTE_LEN       16
#define SMSP_DATA_BYTE_LEN      16

#define CONST_Response_FALSE			0x00
#define CONST_Select_IMSI_File			0x07
#define CONST_Select_SMS_Param_File		0x42
#define CONST_Select_LOCI_File			0x7E
#define CONST_Select_BCCH_File			0x74
#define CONST_Select_KC_File			0x20
#define CONST_Select_FPLMN_File			0x7B

#define CONST_Select_Elementary_File		0x6F
#define CONST_Select_File_14			0x14
#define CONST_Select_SPN_File			0x46
#define CONST_Response_OK			0x92

#define CONST_Get_LOCI_File			0x7D
#define CONST_Put_LOCI_File			0x7F

typedef struct _KV_SIM_CTRL_BLOCK
{
	int SIM_number;
	unsigned char A38_Data_buffer[KI_BYTE_LEN];
	int Response_State;
	int SIM_State;
	long long RamTimer1;
	GBSTMR RamTimer2;

	unsigned char REAL_SIM_IMSI[IMSI_DATA_BYTE_LEN];
	unsigned char REAL_SIM_SPN [SPN_DATA_BYTE_LEN];
	unsigned char REAL_SIM_F14 [SPN_DATA_BYTE_LEN];
	unsigned char REAL_SIM_LOCI[LOCI_DATA_BYTE_LEN];
	unsigned char REAL_SIM_BCCH[BCCH_DATA_BYTE_LEN];
	unsigned char REAL_SIM_KC[KC_DATA_BYTE_LEN];
        
        unsigned char *RAM_IMSI_Ptr;
        unsigned char *RAM_SPN_Ptr;
        unsigned char *RAM_F14_Ptr;
        unsigned char *RAM_LOCI_Ptr;
        unsigned char *RAM_BCCH_Ptr;
        unsigned char *RAM_KC_Ptr;
        unsigned char *RAM_FPLMN_Ptr;        
        unsigned char *ReciveBuffer;
        int ReciveBufferLen;

        int NeedAnswer;        

        unsigned char SendBuf2[48];

        BLOCK5401 Block5401[MAX_SIM_CNT];
      //  unsigned char Block5400[1024];
        BLOCK5403 Block5403;
//        unsigned char Block5402[0x50];

	unsigned int simCnt;        

        CSM_DESC icsmd;
        int (*onmsg)(CSM_RAM*,GBS_MSG*);        
        IPC_REQ gipc;       
}KV_SIM_CTRL_BLOCK;

#define CONST_Run_GSM_A38		0x88
#define CONST_Get_Response		0xC0
#define CONST_Select_File		0xA4
#define CONST_Read_Binary		0xB0
#define CONST_Update_Binary		0xD6
#define CONST_Read_Record		0xB2
#define SIM_OP_STATUS			0xF2

#endif
