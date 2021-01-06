	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN

	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1
        PUBLIC  seqkill
seqkill
        BX      R3

;
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM
/*
A10A67B8    ; int GetOpmsgId(void *unk) //
A10A6548    ; void *GetOpmsgData(int opmsg_id)
A10A650C    ; void RefreshOpmsgData(void *data)

A0E8E7C8 //int DeleteSMS(int index, int _1); ?? better
A0E8E81E //int DeleteSMS(int index);
*/
/*
typedef struct
{
	const int group_id;
	const char *grp_name;
	short unk0; //5
	short unk1; //0x200
	int unk2; //1
}PROC_GROUP;
typedef struct
{
	const PROC_GROUP *proc_group; //A042A198 ?
	const int cepid;
	const char *name;
	const int unk_0; //0
	const void *procs[];
}PROC_DESC;

	defadr DeleteSMS_NEW,0xA0E8E81F //int DeleteSMS_NEW(int index);
	defadr DeltetSmsNew,0xA0B0EE3D //int DeltetSmsNew(int index, short *del_cnt);
	defadr GetOpmsgData,0xA00B0731 //void *GetOpmsgData(int opmsg_id)
	defadr RefreshOpmsgData,0xA00B0351 //void RefreshOpmsgData(void *data)
	defadr PrepareSmsStatus,0xA00C31E5 //void PrepareSmsStatus(int opmsg_id, int index, int _1);
	defadr CreateProc,0xA009899C //void CreateProc(const PROC_DESC *)
	defadr GetNoteViewGui,0xA09AE59F //void *GetNoteViewGui(void *malloc_adr, void *mfree_adr)
	 
	defadr OpenNativeAddressbook,0xA05EA1FC //unsigned int OpenNativeAddressbook(int type, int unk1, int unk2, void *data);
	defadr FreeNativeAbData,0xA055E2AC //int FreeNativeAbData(NativeAbData *nab_data);
	defadr AllocNativeAbData,0xA055E19C //NativeAbData *AllocNativeAbData(void);
	defadr GetNativeAbDataType,0xA055E534 //int GetAbDataType(NativeAbData *nab, int unk0); //0
	defadr GetNumFromNativeAbData,0xA055EBEC //WSHDR *GetNumFromNativeAbData(NativeAbData *nab, int type, int unk0); //0
//	defadr IsAbDataFilled,0xA055EFD0 //int IsAbDataFilled(NativeAbData *nab);
	defadr GetNativeAbDataStatus,0xA055E554 //int GetNativeAbDataStatus(NativeAbData *nab, int _0) //9,not filled, 1, filled
	defadr SetNumToNativeAbData,0xA055EE48 //int SetNumToNativeAbData(NativeAbData *abd, int unk, WSHDR *num); //unk=0x1D, maxlen ?
	*/
	//A8B88320 //ABDATA ?
//ROM:A02D79B6 0E 99                       LDR     R1, [SP,#0x38]
//ROM:A02D79B8 4C F1 6E EA                 BLX     sub_A0423E98
//	defadr EDIT_SetHeaderInputIcon,0xA0A3A719 //void EDIT_SetHeaderInputIcon(void *header_pointer, const int *icons, void *malloc_adr, void *mfree_adr)
//	defadr SetHeaderIcon,0xA0A3A6B3 //void SetHeaderIcon(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr)
//	defadr GetScreenSaverRAM,0xA030866D //SS_RAM *GetScreenSaverRam();

	defadr GetTabGUI,0xA0A374BB//	; void *GetTabGUI(void *malloc_adr, void *mfree_adr)
	defadr SetGUIDefinition,0xA0A34585//	; void SetGUIDefinition(void *gui, const void *definition)
	//defadr A0A345EA+1	; void SetBViewRect(void *gui, int x, int y, int x2, int y2)
	defadr SetGUIToTabGUI,0xA0A3796F//	; int SetGUIToTabGUI(void *tabgui, int n, int icons[4], void *gui)
	defadr SetCursorTab,0xA0A37A8B//	; int SetCursorTab(void *tab_gui, int n)
	defadr UpdateTab1stItem,0xA0A37BED//	; int UpdateTab1stItem(void *tab_gui, int unk_0)
	defadr GetCursorTab,0xA0A37AA9//	; int GetCursorTab(void *tab_gui)
	defadr GetGuiByTab,0xA0A37525//	; void *GetGuiByTab(void *tab_gui, int n)
	END
	