
#define __swi(x) __attribute__((swi(x)))

void loopback0()
__swi(0);

void loopback1()
__swi(1);

void loopback2()
__swi(2);

void loopback3()
__swi(3);

void loopback4()
__swi(4);

int GetAkku(int param1,int param2)
__swi(6);

long SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay)
__swi(8);

void SwitchPhoneOff()
__swi(0x9);

int _open(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber)
__swi(10);

int _read(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber)
__swi(11);

int _write(int FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber)
__swi(12);

int _close(int FileHandler, unsigned int *ErrorNumber)
__swi(13);

int _flush(int stream, unsigned int *ErrorNumber)
__swi(14);

unsigned int _lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2)
__swi(15);

int _mkdir(const char * cFileName, unsigned int *ErrorNumber)
__swi(16);

int GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber)
__swi(18);

int SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber)
__swi(19);

#ifdef __NO_LIBC
void *malloc(unsigned int size)
__swi(20);

void free(void * param1)
__swi(21);
#endif

void *malloc_adr(void)
__swi(0x8014);

void mfree(void * param1)
__swi(21);

void *mfree_adr(void)
__swi(0x8015);

#ifdef __NO_LIBC
int sprintf(char *buf, const char *str, ...)
__swi(22);

char * strcat (char * param1,const char * param2)
__swi(23);

char * strchr (const char * param1,int param2)
__swi(24);

int  strcmp (const char * param1,const char * param2)
__swi(25);

char * strcpy (char *dest,const char *source)
__swi(26);

unsigned int strlen(const char * param1)
__swi(27);
#endif

void  wsAppendChar(WSHDR *ws,int wchar)
__swi(28);

int wsInsertChar(WSHDR *ws,int wchar,int pos)
__swi(29);

IMGHDR *GetPITaddr(int num)
__swi(30);

void DrawMainScreen()
__swi(31);

void DrawScreenSaver ()
__swi(32);

int GetImgHeight(int picture)
__swi(33);

int GetImgWidth(int picture)
__swi(34);

void DrawImg(unsigned int x, unsigned int y, unsigned int picture)
__swi(35);

void DrawCanvas(void *data, int x1, int y1, int x2, int y2, int flag_one)
__swi(37);

void DrawImgBW(unsigned int x, unsigned int y, unsigned int picture, char *pen, char *brush)
__swi(38);

int EEFullGetBlockInfo(unsigned int block,int *size,char *version)
__swi(0x2C);

void PlaySound(long param1, long param2, long param3, long tone, long param5)
__swi(50);

void PlaySoundLoop(int _0x2F, int param2, int duration)
__swi(0x0034);

void AlarmClockRing()
__swi(0x0035);

int *GetEELiteBlockAddress(short blocknum)
__swi(42);

int setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber)
__swi(60);

int IsScreenSaver(void)
__swi(0x0042);

int GetVibraStatus (void)
__swi(0x40);

int IsUnlocked(void)
__swi(67);

void TempLightOn(int x, int y)
__swi(0x44);

#ifdef NEWSGOLD
int GetWavLen(char *filename)
#else
int GetWavLen(TWavLen *wl)
#endif
__swi(0x45);

int HasNewSMS(void)
__swi(0x0046);

int HasFlashSMS(void)
__swi(0x0047);

#ifdef X75
short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int zero, int CepId, int Msg, const PLAYFILE_OPT *sfo)
#else
short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int CepId, int Msg, const PLAYFILE_OPT *sfo)
#endif
__swi(0x4A);

int GetMissedCallsCount(void)
__swi(0x004C);

void GBS_StartTimerProc(void *htimer, long ms, void ptr(GBSTMR*))
__swi(77);

int MsgBoxError(int flag, int LgpId)
__swi(0x4E);

int MsgBoxYesNo(int flag, int LgpID, void CallBackProc(int))
__swi(0x4F);

int MsgBoxOkCancel(int flag, int LgpID, void CallBackProc(int))
__swi(0x50);

char *GetIlluminationDataTable()
#ifdef NEWSGOLD
__swi(0x8052);
#else
__swi(0x0052);
#endif

int StrToInt(char *s, char **endp)
__swi(0x0054);

void SetCpuClockLow(int const_2)
__swi(0x221);

void SetCpuClockTempHi(int const_2)
__swi(0x222);

unsigned char GetCPUClock()
__swi(92);

unsigned char GetCPULoad()
__swi(93);

unsigned int GetMMIMemUsed()
__swi(94);

int GetFreeRamAvail()
__swi(95);

SS_RAM *GetScreenSaverRAM(void)
__swi(0x68);

int  FindFirstFile (DIR_ENTRY *DIRENTRY,char *mask,unsigned int *ErrorNumber)
__swi(107);

int  FindNextFile (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber)
__swi(108);

int  FindClose (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber)
__swi(109);

int IsCalling(void)
__swi(0x06E);

void RefreshGPRSTraffic()
__swi(111);

int *GetGPRSTrafficPointer()
__swi(112);

int GetTypeOfCall()
__swi(0x0073);

void* GetFunctionPointer(char * _shortcut)
__swi(116);

unsigned int SetVibration(unsigned int power)
__swi(124);

int IsPlayerOn()
__swi(0x007F);

int ShowCallList(int list, int zero)
__swi(128);

int GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber)
__swi(132);

int strcmpi(const char *s1, const char *s2)
__swi(0x0085);

void EEFullReadBlock(int block, void *buf, int offset, int size, int cepid, int msg)
__swi(0x86);

void EEFullWriteBlock(int block, void *buf, int offset, int size, int cepid, int msg)
__swi(0x87);

int GetFreeFlexSpace(int DriveNum, unsigned int *ErrorNumber)
__swi(138);

int GetTotalFlexSpace(int DriveNum, unsigned int *ErrorNumber)
__swi(139);

void RegExplorerExt(REGEXPLEXT const * param1)
__swi(140);

int fmove(const char * SourceFileName, const char * DestFileName, unsigned int *ErrorNumber)
__swi(142);

int _rmdir(const char * cDirectory, unsigned int *ErrorNumber)
__swi(143);

int _truncate(int FileHandler, int length, int *errornumber)
__swi(144);

int isdir(const char * cDirectory, unsigned int *ErrorNumber)
__swi(145);

#ifdef __NO_LIBC
void *calloc(size_t nelem, size_t elsize)
__swi(146);
#endif

int ExecuteFile (WSHDR *filepath, WSHDR *mimetype, void *param)
__swi(148);

int UnRegExplorerExt(REGEXPLEXT const * param1)
__swi(149);

int PlayMelodyInMem(char Unk_0x11, void * MelAddr, int MelSize, int CepId, int Msg, int Unk_0)
__swi(0x99);

int ChangeVolume(unsigned char Volume)
__swi(154);

void CloseScreensaver ()
__swi(0x9C);

void ws_2str(WSHDR *ws, char *str, unsigned int size)
__swi(163);

void ResetGPRSTraffic()
__swi(166);

char *GetCurrentLocale()
__swi(170);

void loopback171()
__swi(171);

void GetDateTime(TDate * param1, TTime * param2)
__swi(180);

char GetWeek(TDate* param1)
__swi(181);

char GetProfile()
__swi(182);

char SetProfile(char param1)
__swi(183);

int sdiv(int denom,int number)
__swi(184);

char IsGPRSEnabled()
__swi(167);

char IsGPRSConnected()
__swi(168);

void KbdLock()
__swi(169);

void KbdUnlock()
__swi(185);

#ifdef __NO_LIBC
void *realloc(void *ptr, int size)
__swi(186);

void *memset(void *s, int c, int n)
__swi(187);
#endif

int udiv(unsigned int denom,unsigned int number)
__swi(188);

int DivBy10(int divident)
__swi(189);

void SpellTime()
__swi(0x00BF);

void *GetBuffer(int patch_id)
__swi(0x00C4);

char GetAkkuCapacity()
__swi(198);

char GetAccessoryType(void)
__swi(0x088);

char* RamAccPoint(void)
__swi(0x80D0);

void RebootPhone()
__swi(0x93);

unsigned short *RamCap()
__swi(0x80C8);

unsigned short *RamLS()
__swi(0x80C9);

RAMNET * RamNet()
__swi(0x80CA);

char * RamMissedCalls()
__swi(0x80CC);

char * RamMissedSMS()
__swi(0x80CD);

char * RamMissedMessage()
__swi(0x80D4);

char * RamMenuAnywhere()
__swi(0x80D8);

char *RamPressedKey()
__swi(0x80DF);

void * RamScreenBuffer()
__swi(0x80E0);

unsigned int *RamMPlayer_CtrlCode()
__swi(0x80E1);

void *FreeRAM()
__swi(0x80E4);

void *BuildCanvas(void)
__swi(0x80F1);

unsigned int AddrLibrary()
__swi(0x80FF);

char *RamLastStoreString(void)
__swi(0x838B);

void GBS_SendMessage(int cepid_to, int msg, ...)
__swi(0x0100);

int GBS_ReciveMessage(GBS_MSG * param1)
__swi(0x0101);

void GBS_AcceptMessage(void)
__swi(0x0102);

void GBS_ClearMessage(void)
__swi(0x0103);

void GBS_PendMessage(GBS_MSG * param1)
__swi(0x0104);

void CreateGBSproc(int cepid, const char *name, void (*onMsg)(void), int prio, int unk_zero)
__swi(0x0105);

CSMROOT *CSM_root()
__swi(0x8106);

int CreateCSM(const CSM_DESC* param1,void * param2,int param3)
__swi(0x0107);

CSM_RAM * FindCSMbyID (int id)
__swi(0x0108);

void DoIDLE(int param1)
__swi(0x0109);

void *GetConfig(unsigned int id)
__swi(0x010A);

void *GetMinAdrScan()
__swi(0x810B);

void *GetMaxAdrScan()
__swi(0x810C);

unsigned short *GetCI()
__swi(0x810D);

void Vibration(unsigned int power, unsigned int duration)
__swi(0x010E);

void freeUSSD()
__swi(0x010F);

char *wstrcopy(unsigned short *dst, const unsigned short *src)
__swi(0x0110);

char GetTypeUSSD()
__swi(0x0111);

unsigned int SetUSSD(StructUSSDStr * param1)
__swi(0x0112);

#ifdef __NO_LIBC
char * strpbrk (const char *s1, const char *s2)
__swi(0x0113);

int strcspn(const char *s1, const char *s2)
__swi(0x0113);

char * strncat (char *dest, const char *substr, size_t maxSubLen)
__swi(0x0114);

int  strncmp (const char *s1, const char *s2, size_t n)
__swi(0x0115);

int  strncpy (char *dest, const char *source, size_t maxlen)
__swi(0x0116);

char * strrchr (const char *s, unsigned int c)
__swi(0x0117);

char * strstr (const char *s1, const char *s2)
__swi(0x0118);

int  strtol (const char *nptr, char **endptr, int base)
__swi(0x0119);

int  strtoul (const char *nptr, char **endptr, int base)
__swi(0x011A);

int snprintf (char * param1, int n,const char *format,...)
__swi(0x011B);

int  memcmp (const void *m1, const void *m2, size_t n)
__swi(0x011C);
#endif

void  zeromem (void *dest, size_t n)
__swi(0x011D);

#ifdef __NO_LIBC
__swi(0x011E) void * memcpy (void *dest,const void *source, size_t cnt);
#endif

WSHDR * wstrcpy (WSHDR *wshdr_d,WSHDR *wshdr_s)
__swi(0x011F);

WSHDR * wstrncpy (WSHDR * param1,WSHDR * param2, size_t param3)
__swi(0x0120);

WSHDR * wstrcat (WSHDR *wshdr_d,WSHDR *wshdr_s)
__swi(0x0121);

WSHDR * wstrncat (WSHDR *wshdr_d,WSHDR *wshdr_s, size_t n)
__swi(0x0122);

int  wstrlen (WSHDR *wshdr)
__swi(0x0123);

int wsprintf (WSHDR * param1, const char *format,...)
__swi(0x0124);

WSHDR * AllocWS (int len)
__swi(0x0125);

void  CutWSTR (void *WSHDR,int len)
__swi(0x0126);

WSHDR * CreateLocalWS (WSHDR *wshdr,unsigned __int16 *wsbody,int len)
__swi(0x0127);

int  CreateWS (void *malloc,void *mfree,int len)
__swi(0x0128);

void  FreeWS (WSHDR *wshdr)
__swi(0x0129);

void  DrawObject (DRWOBJ * param1)
__swi(0x012A);

void  AddKeybMsgHook (void *proc)
__swi(0x012B);

int  AddKeybMsgHook_end (void *proc)
__swi(0x012C);

void  RemoveKeybMsgHook (void *proc)
__swi(0x012D);

char *GetPaletteAdrByColorIndex (int ColorIndex)
__swi(0x012E);

void  getRGBcolor (int ColorIndex,void *dest)
__swi(0x012F);

void  getRGBbyPaletteAdr (int *paletteAdr,void *dest)
__swi(0x0130);

void  setColor (int a,int r,int g,int b,void *dest)
__swi(0x0131);

#ifdef __NO_LIBC
void *memmove(void *dest,const void *source,int cnt)
__swi(0x0132);
#endif

void  StoreXYWHtoRECT (void *RECT,int x,int y,int w,int h)
__swi(0x0133);

void  StoreXYXYtoRECT (void *RECT,int x,int y,int x2,int y2)
__swi(0x0134);

int  IsGuiOnTop (int id)
__swi(0x0135);

int  CreateGUI_ID (void *gui,int id)
__swi(0x0136);

int  CreateGUI (void *gui)
__swi(0x0137);

int  CreateGUI_30or2 (void *gui)
__swi(0x0138);

int  CreateGUIWithDummyCSM (void *gui,int flag)
__swi(0x0139);

int  CreateGUIWithDummyCSM_30or2 (void *gui,int flag)
__swi(0x013A);

void  GeneralFuncF1 (int cmd)
__swi(0x013B);

void  GeneralFuncF0 (int cmd)
__swi(0x013C);

void  GeneralFunc_flag1 (int id,int cmd)
__swi(0x013D);

void  GeneralFunc_flag0 (int id,int cmd)
__swi(0x013E);

void DirectRedrawGUI (void)
__swi(0x013F);

void  DirectRedrawGUI_ID (int id)
__swi(0x0140);

void PendedRedrawGUI (void)
__swi(0x0141);

CSM_RAM * FindCSM (void *csm_q,int id)
__swi(0x0142);

void  GBS_StartTimer (GBSTMR *tmr,int time,int msg,int unk,int cepid)
__swi(0x0143);

void  GBS_StopTimer (GBSTMR *tmr)
__swi(0x0144);

short GBS_GetCurCepid (void)
__swi(0x0145);

void LockSched(void)
__swi(0x0146);

void UnlockSched(void)
__swi(0x0147);

extern int ShowMSG(int flag, int lgp_id)
__swi(0x0148);

void SetPropTo_Obj1(DRWOBJ *drwobj,void *rect,int rect_flag,WSHDR *wshdr,int font,int text_flag)
__swi(0x0149);

void FreeDrawObject_subobj(DRWOBJ *drwobj)
__swi(0x014A);

void SetColor(DRWOBJ *drwobj, const char *color1, const char *color2)
__swi(0x014B);

void DrawString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int font,int text_attribute,const char *Pen,const char *Brush)
__swi(0x014C);

GUI *GetTopGUI(void)
__swi(0x014D);

void *FindItemByID(GUI *gui,int id)
__swi(0x014E);

void *GetDataOfItemByID(GUI *gui,int id)
__swi(0x014F);

void DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush)
__swi(0x0150);

void SetPropTo_Obj5(DRWOBJ * param1, RECT * param2, int zero, IMGHDR *Image)
__swi(0x0151);

int CreateMenu(int is_small,int zero1,const MENU_DESC *menu, const HEADER_DESC *hdr,int start_item,int n_items,void *user_pointer,int *to_remove)
__swi(0x0152);

int GBS_RecActDstMessage(GBS_MSG * param1)
__swi(0x0153);

void KillGBSproc(int cepid)
__swi(0x0154);

#ifdef __SWILIB_PNG__
png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
__swi(0x0155);

png_infop png_create_info_struct(png_structp png_ptr)
__swi(0x0156);

void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
__swi(0x0157);

void png_set_sig_bytes(png_structp png_ptr,int num_bytes)
__swi(0x0158);

void png_read_info(png_structp png_ptr, png_infop info_ptr)
__swi(0x0159);

png_uint_32 png_get_IHDR(png_structp png_ptr,png_infop info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)
__swi(0x015A);

png_voidp png_malloc(png_structp png_ptr, png_uint_32 size)
__swi(0x015B);

void png_read_image(png_structp png_ptr, png_bytepp image)
__swi(0x015C);

void png_read_end(png_structp png_ptr, png_infop info_ptr)
__swi(0x015D);

png_voidp png_get_io_ptr(png_structp png_ptr)
__swi(0x015E);

png_uint_32 png_get_rowbytes(png_structp png_ptr,png_infop info_ptr)
__swi(0x015F);

void png_read_row(png_structp png_ptr,png_bytep row,png_bytep dsp_row)
__swi(0x0160);

void png_init_io(png_structp png_ptr, int fp)
__swi(0x0161);
#endif

#ifdef __NO_LIBC
int setjmp(jmp_buf jmpbuf)
__swi(0x0162);
#endif

EDITQ *AllocEQueue(void *malloc_a, void *mfree_a)
__swi(0x0163);

EDITCONTROL *PrepareEditControl(EDITCONTROL * param1)
__swi(0x0164);

void ConstructEditControl(EDITCONTROL *EditControl,int type,int flag,WSHDR *ws,int maxlen)
__swi(0x0165);

int AddEditControlToEditQend(void *EditQ,EDITCONTROL *EditControl,void *malloc_a)
__swi(0x0166);

int CreateInputTextDialog(const INPUTDIA_DESC *input_desc, const HEADER_DESC *header_desc,void *editq,int do_mfree,void *user_pointer)
__swi(0x0167);

void SetSoftKey(void *gui,const SOFTKEY_DESC * param2,int n)
__swi(0x0168);

int ExtractEditControl(void *guidata,int n,EDITCONTROL * param3)
__swi(0x0169);

int StoreEditControl(void *guidata,int n,EDITCONTROL * param3)
__swi(0x016A);

int _unlink(const char *cFileName,unsigned int *errornumber)
__swi(0x016B);

int str_2ws(WSHDR *ws,const char *str,unsigned int size)
__swi(0x016C);

int UnpackABentry(AB_UNPRES * param1,void *abentry,int filesz,int flag)
__swi(0x016D);

int FreeUnpackABentry(AB_UNPRES * param1, void *mfree_adr)
__swi(0x016E);

int GetTypeOfAB_UNPRES_ITEM(int param1)
__swi(0x016F);

int MakeVoiceCall(const char *number,int _0x10, int _0x20C0)
__swi(0x0170);

void SUBPROC(void * param1,...)
__swi(0x0171);

void REDRAW(void)
__swi(0x0172);

int socket(int af,int type,int protocol)
__swi(0x0173);

int connect(int sock,SOCK_ADDR * param2,int name_length)
__swi(0x0174);

int bind(int sock,SOCK_ADDR * param2,int name_length)
__swi(0x0175);

int closesocket(int socket)
__swi(0x0176);

int shutdown(int socket,int how)
__swi(0x0177);

int recv(int socket,void *buf,int len,int flag)
__swi(0x0178);

int send(int socket,const void *buf,int len,int flag)
__swi(0x0179);

unsigned __int16 htons(unsigned __int16)
__swi(0x017A);

unsigned int htonl(unsigned int)
__swi(0x017B);

int *socklasterr(void)
__swi(0x817C);

void SetIDLETMR(int time_ms,int msg)
__swi(0x017D);

void RestartIDLETMR(void)
__swi(0x017E);

void DisableIDLETMR(void)
__swi(0x017F);

int EDIT_GetItemNumInFocusedComboBox(void *gui)
__swi(0x0180);

void EDIT_SetTextToFocused(void *gui,WSHDR *ws)
__swi(0x0181);

int EDIT_GetFocus(void *gui)
__swi(0x0182);

int EDIT_GetUnFocus(void *gui)
__swi(0x0183);

void ConstructComboBox(EDITCONTROL *EditControl,int type,int attr,WSHDR* param4,int maxlen,int unk_zero,int num_of_items,int start_item)
__swi(0x0184);

int GBS_WaitForMsg(const int *msg_list, int msgs_num, GBS_MSG* param3, int timeout)
__swi(0x0185);

int RegisterCepidForSocketWork(REGSOCKCEPID_DATA * param1)
__swi(0x0186);

int RequestLMANConnect(LMAN_DATA * param1)
__swi(0x0187);

int ScreenW(void)
__swi(0x8188);

int ScreenH(void)
__swi(0x8189);

int HeaderH(void)
__swi(0x818A);

int SoftkeyH(void)
__swi(0x818B);

void GBS_DelTimer(GBSTMR * param1)
__swi(0x018C);

int available0(int sock)
__swi(0x018D);

void GPRS_OnOff(int on, int _1)
__swi(0x018E);

int GetCurMenuItem(void *gui)
__swi(0x018F);

void MutexCreate(MUTEX *mtx)
__swi(0x0190);

void MutexDestroy(MUTEX *mtx)
__swi(0x0191);

void MutexLock(MUTEX *mtx)
__swi(0x0192);

void MutexLockEx(MUTEX *mtx, int flag)
__swi(0x0193);

void MutexUnlock(MUTEX *mtx)
__swi(0x0194);

void SetMenuItemIcon(void *gui,int item_n,int icon_n)
__swi(0x0195);

void RefreshGUI(void)
__swi(0x0196);

void *AllocMenuItem(void *gui)
__swi(0x0197);

WSHDR *AllocMenuWS(void *gui, int len)
__swi(0x0198);

void SetMenuItemIconArray(void *gui,void *item,const int *icons)
__swi(0x0199);

void SetMenuItemText(void *gui,void *item,WSHDR *text,int item_n)
__swi(0x019A);

void EDIT_SetFocus(void *gui, int item)
__swi(0x019B);

void SEQKILLER(void *data, void(*next_in_seq)(void *), void *data_to_kill)
__swi(0x019C);

void *SEQKILLER_ADR()
__swi(0x819C);

long long getCpuUsedTime_if_ena(void)
__swi(0x019D);

void StartCpuUsageCount(void)
__swi(0x019E);

int inflateInit2_ (z_streamp strm, int windowBits,const char *version, int stream_size)
__swi(0x019F);

int inflate (z_streamp strm, int flush)
__swi(0x01A0);

int inflateEnd (z_streamp strm)
__swi(0x01A1);

int ActivateDialUpProfile(unsigned int cep_id,int profile_num)
__swi(0x01A2);

int GetCurrentGPRSProfile(void)
__swi(0x01A3);

int GetDisconnectTime(void)
__swi(0x01A4);

void RegisterCepIdForCurProfile(unsigned int cep_id,int profile_num,unsigned int csd_or_gprs)
__swi(0x01A5);

int IsTimerProc(GBSTMR * param1)
__swi(0x01A6);

char* Get_CC_NC()
__swi(0x1A7);

#ifdef __SWILIB_PNG__
png_structp png_create_read_struct_2(png_const_charp user_png_ver, png_voidp error_ptr,
                                                 png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
                                                 png_malloc_ptr malloc_fn, png_free_ptr free_fn)
__swi(0x1A8);

void png_set_read_fn(png_structp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
__swi(0x1A9);

void png_read_update_info(png_structp png_ptr,void *info_ptr)
__swi(0x1AA);

void png_set_palette_to_rgb(png_structp png_ptr)
__swi(0x1AB);

png_uint_32 png_get_valid(png_structp png_ptr,png_infop info_ptr, png_uint_32 flag)
__swi(0x1AC);

void png_set_tRNS_to_alpha(png_structp png_ptr)
__swi(0x1AD);

void png_set_filler(png_structp png_ptr,png_uint_32 filler, int flags)
__swi(0x1AE);

void png_set_strip_16(png_structp png_ptr)
__swi(0x1AF);

void png_set_packing(png_structp png_ptr)
__swi(0x1B0);

void png_set_gray_to_rgb(png_structp png_ptr)
__swi(0x1B1);

int png_check_sig(png_bytep sig, int num)
__swi(0x1B2);
#endif

void DrawLine(int x,int y,int x2,int y2,int type,const char *pen)
__swi(0x1B3);

void DrawRectangle(int x,int y,int x2,int y2,int flags,const char *pen,const char *brush)
__swi(0x1B4);

int isnewSGold(void)
__swi(0x81B5);

int async_gethostbyname(const char *host_name,int ****DNR_RES,int *DNR_ID)
__swi(0x1B6);

unsigned int str2ip(const char * param1)
__swi(0x1B7);

void *EXT_TOP(void)
__swi(0x81B8);

void *PNG_TOP(void)
__swi(0x81B9);

void *LIB_TOP(void)
__swi(0x81BA);

//FIXME
//SFN_DATA *DATA_N_SFB(void)
//__swi(0x81BB);

void SHA1_Init(SHA_CTX *c)
__swi(0x1BC);

void SHA1_Update(SHA_CTX *c, const void *data, unsigned long len)
__swi(0x1BD);

void SHA1_Final(char *md, SHA_CTX *c)
__swi(0x1BE);

RSA * RSA_new_method(RSA_METHOD *method)
__swi(0x1BF);

void RSA_free (RSA *r)
__swi(0x1C0);

int RSA_sign(int type, char *m, unsigned int m_len, char *sigret, unsigned int *siglen, RSA *rsa)
__swi(0x1C1);

BIGNUM *BN_bin2bn(const char *s,int len,BIGNUM *ret)
__swi(0x1C2);

void SetMenuItemCount(void *gui,int n)
__swi(0x1C3);

void SetCursorToMenuItem(void *gui,int n)
__swi(0x1C4);

int GetFontYSIZE(int font)
__swi(0x1C5);

void EDIT_ExtractFocusedControl(void *gui,EDITCONTROL *ec)
__swi(0x1C6);

int EDIT_StoreControlToFocused(void *gui,EDITCONTROL *ec)
__swi(0x1C7);

EDITC_OPTIONS *PrepareEditCOptions(EDITC_OPTIONS *ec_options)
__swi(0x1C8);

void SetInvertToEditCOptions(EDITC_OPTIONS *ec_options, int invert)
__swi(0x1C9);

void SetFontToEditCOptions(EDITC_OPTIONS *ec_options, int font)
__swi(0x1CA);

void SetAlignToEditCOptions(EDITC_OPTIONS *ec_options, int align)
__swi(0x1CB);

void SetPenColorToEditCOptions(EDITC_OPTIONS *ec_options, int pen)
__swi(0x1CC);

void SetBrushColorToEditCOptions(EDITC_OPTIONS *ec_options, int brush)
__swi(0x1CD);

void CopyOptionsToEditControl(EDITCONTROL *ec,EDITC_OPTIONS *ec_options)
__swi(0x1CE);


#ifdef NEWSGOLD
  #define TREGEXPLEXT REGEXPLEXT
#else
  #define TREGEXPLEXT REGEXPLEXT_ARM_NEW
#endif

TREGEXPLEXT *get_regextpnt_by_uid(int uid)
__swi(0x1CF);

int GetExtUid_ws(WSHDR * ext)
__swi(0x1D0);

void EDIT_RemoveEditControl(void *gui,int n)
__swi(0x1D1);

void EDIT_InsertEditControl(void *gui,int n,EDITCONTROL * param3)
__swi(0x1D2);

int EDIT_GetCursorPos(void *gui)
__swi(0x1D3);

void EDIT_SetCursorPos(void *gui, int pos)
__swi(0x1D4);

char *Get_Phone_Info(int InfoIndex)
__swi(0x1D5);

void png_set_gray_1_2_4_to_8(png_structp png_ptr)
__swi(0x1D6);

void png_set_invert_mono(png_structp png_ptr)
__swi(0x1D7);

int EDIT_IsMarkModeActive(void *gui)
__swi(0x1D8);

int EDIT_GetMarkedText(void *gui,WSHDR *dest)
__swi(0x1D9);

int SendSMS(WSHDR *ws,const char *num, int cepid,int msg,int flag)
__swi(0x1DA);

PDU *IncommingPDU(void)
__swi(0x81DB);

short wstrchr(WSHDR *ws,unsigned int start_pos,unsigned int wchar)
__swi(0x1DC);

short wstrrchr(WSHDR *ws,unsigned int max_pos,unsigned int wchar)
__swi(0x1DD);

int EDIT_SetTextToEditControl(void *gui,int n,WSHDR *ws)
__swi(0x1DE);

void *EDIT_GetUserPointer(void *gui)
__swi(0x1DF);

void *MenuGetUserPointer(void *gui)
__swi(0x1E0);

int GetSymbolWidth(int wchar,int font)
__swi(0x1E1);

int ws_2utf8( WSHDR *from, char *to , int *result_length, int max_len)
__swi(0x1E2);

int utf8_2ws(WSHDR *ws,const char *utf8_str, unsigned int maxLen)
__swi(0x1E3);

int GetPicNByUnicodeSymbol(int wchar)
__swi(0x1E4);

int EDIT_OpenOptionMenuWithUserItems(void *gui, void (*itemhandler)(USR_MENU_ITEM *item), void *user_pointer, int to_add)
__swi(0x1E5);

void Menu_SetItemCountDyn(void *gui, int n)
__swi(0x1E6);

char *GetLastJavaApplication()
__swi(0x1E7);

int IsNoJava()
__swi(0x1E8);

IMGHDR *CreateIMGHDRFromPngFile(const char *fname, int type)
__swi(0x1E9);

int GetMaxDynIcon(void)
__swi(0x1EA);

char *RAM_IMSI(void)
__swi(0x81EB);

void FreeDynIcon(int picture)
__swi(0x1EC);

int IsDynIconBusy(int picture)
__swi(0x1ED);

void SetDynIcon(int picture,IMGHDR *img,char *bitmap)
__swi(0x1EF);

unsigned int GetSessionAge(void)
__swi(0x1F3);

#ifdef __NO_LIBC
int sscanf(const char * param1, const char * param2, ...)
__swi(0x1F5);
#endif

IMGHDR* GetPitAdrBy0xE200Symbol(int uni_symbol)
__swi(0x1F6);

int GetPlayStatus(void)
__swi(0x1F8);

char *RamMediaIsPlaying()
__swi(0x81FB);

void CloseCSM(int id)
__swi(0x1FC);

void SetProp2ImageOrCanvas(DRWOBJ * param1, RECT * param2, int zero, IMGHDR *Image, int bleed_x, int bleed_y)
__swi(0x201);

void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int flag, char *pen, char *brush)
__swi(0x202);

void SetPixel(int x,int y,char *color)
__swi(0x203);

void drawArc(int x1,int y1,int x2,int y2,int a1,int a2,int flag,char *pen,char *brush)
__swi(0x204);


#ifdef __NO_LIBC
void srand(unsigned int seed)
__swi(0x206);
#endif

void DrawScrollString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int xdisp,int font,int text_attribute,const char *Pen,const char *Brush)
__swi(0x207);

int Get_WS_width(WSHDR *ws, int font)
__swi(0x208);

void *FindGUIbyId(int id, CSM_RAM **csm)
__swi(0x209);

void EDIT_SetDate(void *gui,int n,TDate *dd)
__swi(0x20A);

void EDIT_SetTime(void *gui,int n,TTime *tt)
__swi(0x20B);

void EDIT_GetDate(void *gui,int n,TDate *dd)
__swi(0x20C);

void EDIT_GetTime(void *gui,int n,TTime *tt)
__swi(0x20D);

int ConstructEditTime(EDITCONTROL *EditControl,TTime *time)
__swi(0x20E);

int ConstructEditDate(EDITCONTROL *EditControl,TDate *date)
__swi(0x20F);

int CardExplGetCurItem(void *csm)
__swi(0x212);

void CardExplGetFName(void *csm, int cur_item, WSHDR *dest)
__swi(0x213);

void wstrcpybypos(WSHDR *dest,WSHDR *src,int from,int len)
__swi(0x214);

void wsRemoveChars(WSHDR *ws,int from,int to)
__swi(0x215);

void wstrcatprintf(WSHDR * param1,const char *format,...)
__swi(0x216);

int CreateMultiLinesMenu(int dummy,int dummy2,const ML_MENU_DESC * param3,const HEADER_DESC * param4,int to_item,int n)
__swi(0x217);

void SetMLMenuItemText(void *data,void *item,WSHDR *ws1,WSHDR *ws2,int n)
__swi(0x218);

void *AllocMLMenuItem(void *data)
__swi(0x219);

int EDIT_SetTextInvert(void *gui,int cursor_pos,int len)
__swi(0x21A);

void EDIT_RemoveTextInvert(void *gui)
__swi(0x21B);

int EDIT_IsBusy(void *gui)
__swi(0x21C);

int GSMTXT_Decode(WSHDR *dest,void *pkt,int len,int encoding_type, void *(*malloc_adr)(int), void (*mfree_adr)(void))
__swi(0x21D);

void FocusGUI(int id)
__swi(0x21E);

void UnfocusGUI(void)
__swi(0x21F);

void SetCpuClockLow(int flag)
__swi(0x221);

void SetCpuClockHi(int flag)
__swi(0x222);

int PlayMelody_ChangeVolume(int handle,int volume)
__swi(0x225);

int PlayMelody_StopPlayback(int handle)
__swi(0x226);

int PlayMelody_PausePlayback(int handle)
__swi(0x227);

int PlayMelody_ResumePlayBack(int handle)
__swi(0x228);

#ifdef __NO_LIBC
void longjmp(jmp_buf param1, int param2)
__swi(0x229);
#endif

void FreeGSMTXTpkt(void *pkt)
__swi(0x22A);

int GetLunarDate(TDate* pdate, TDate* pLdate)
__swi(0x234);

int GetLunarYearID(int year)
__swi(0x235);

int GetLunarAnimal(int year)
__swi(0x236);

char *RamIconBar()
__swi(0x8237);

TDateTimeSettings *RamDateTimeSettings(void)
__swi(0x822F);

int GetTimeZoneShift(TDate * param1, TTime * param2, int timeZone)
__swi(0x230);

#ifdef __NO_LIBC
int rand(void)
__swi(0x7E);
#endif

void SendAutoUSSDack(void)
__swi(0x238);

int EEFullDeleteBlock(unsigned int block,int cepid,int msg)
__swi(0x239);

int EEFullCreateBlock(unsigned int block,int size,int version,int cepid,int msg)
__swi(0x23A);

void DisableIconBar(int disable)
__swi(0x23B);

void AddIconToIconBar(int pic, short* num)
__swi(0x27);

int SetCurrentGPRSProfile(int profile)
__swi(0x23C);

void SetDateTime(TDate * param1, TTime * param2)
__swi(0x241);

void gb2ws(WSHDR *ws, const char *s, int len)
__swi(0x242);

void ws2gb(WSHDR *ws, char *s, int len)
__swi(0x243);

int Base64Encode(void *inbuf, int insize, void *outbuf, int outsize)
__swi(0x244);

int Base64Decode(char *inbuf, int insize, void *outbuf, int outsize, char *_null, int *unk5)
__swi(0x245);

int GetFileProp(FILE_PROP *wl,WSHDR *file,WSHDR *folder)
__swi(0x246);

void SetMenuSearchCallBack(void *gui, MenuSearchCallBack proc)
__swi(0x24B);

int  GetPeripheryState (int device, int check_state)
__swi(0x24C);

int PlayMelody_SetPosition(int handle, int pos_ms)
__swi(0x24D);

void* GetPlayObjById(int handle)
__swi(0x24E);

int GetPlayObjPosition(void *playobj_3D0, int *pos_ms)
__swi(0x24F);

int GetPlayObjDuration(void *playobj_3D0, int *pos_ms)
__swi(0x250);

int StartNativeExplorer(NativeExplorerData* data)
__swi(0x254);

void MenuSetUserPointer(void *gui,void *user_pointer)
__swi(0x255);

int CalcBitmapSize(short w,short h, char typy)
__swi(0x258);

HObj Obs_CreateObject(int uid_in, int uid_out, int prio, int msg_callback, int emb4, int sync,unsigned int *ErrorNumber)
__swi(0x259);

int Obs_DestroyObject(HObj hObj)
__swi(0x25A);

int Obs_SetInput_File (HObj hObj, int unk_zero, WSHDR *path)
__swi(0x25B);

int Obs_GetInputImageSize (HObj hObj, short *w, short *h)
__swi(0x25C);

int Obs_SetOutputImageSize (HObj hObj, short w, short h)
__swi(0x25D);

int Obs_Start(HObj hObj)
__swi(0x25E);

int Obs_Output_GetPictstruct(HObj hObj, IMGHDR **img)
__swi(0x25F);

int Obs_Graphics_SetClipping(HObj hObj, short x, short y, short w, short h)
__swi(0x260);

int Obs_SetRotation(HObj hObj, int angle)
__swi(0x261);

int Obs_GetInfo (HObj hObj, int unk_0or1)
__swi(0x262);

int Obs_SetScaling (HObj hObj, int unk5)
__swi(0x263);

int Obs_TranslateMessageGBS (GBS_MSG *msg, OBSevent *event_handler)
__swi(0x264);

int Obs_Pause (HObj hObj)
__swi(0x265);

int Obs_Resume (HObj hObj)
__swi(0x266);

int Obs_Stop (HObj hObj)
__swi(0x267);

int Obs_Prepare (HObj hObj)
__swi(0x268);

int Obs_SetRenderOffset (HObj hObj,short x,short y)
__swi(0x269);

int Obs_SetPosition (HObj hObj,int ms)
__swi(0x26A);

int Obs_Mam_SetPurpose (HObj hObj,char purpose)
__swi(0x26B);

int Obs_Sound_SetVolumeEx (HObj hObj, char vol, char delta)
__swi(0x26C);

int Obs_Sound_GetVolume (HObj hObj, char *vol)
__swi(0x26D);

int Obs_Sound_SetPurpose (HObj hObj,int purpose)
__swi(0x26E);

int runMidletLinkablely(const char *midlet_name, WSHDR *filename)
__swi(0x283);

#ifdef NEWSGOLD
void getProfileNameByN(WSHDR *ws, int n, int _0)
#else
void getProfileNameByN(int n, WSHDR *ws, int _0)
#endif
__swi(0x296);

void UpdateMenuCursorItem(void *gui, int n)
__swi(0x2A3);

void *GetMenuGUI(void *malloc_adr, void *mfree_adr)
__swi(0x2A4);

void *GetMultiLinesMenuGUI(void *malloc_adr, void *mfree_adr)
__swi(0x2A5);

void SetHeaderToMenu(void *gui, const HEADER_DESC *hdr, void *malloc_adr)
__swi(0x2A6);

void SetMenuToGUI(void *gui, const void *menu_desc)
__swi(0x2A7);

int GetMenuItemCount(void *gui)
__swi(0x2A8);

int CreatePopupGUI(int flag, void *user_pointer, const POPUP_DESC * param3, int lgp_msg)
__swi(0x2A9);

int CreatePopupGUI_ws(int flag, void *user_pointer, const POPUP_DESC * param3, WSHDR *msg)
__swi(0x2AA);

void *GetPopupUserPointer(void *gui)
__swi(0x2AB);

int DeleteSMS(int index, short *del_cnt)
__swi(0x2AC);

int SetSmsStatus(int index, int type)
__swi(0x2AD);

void *GetHeaderPointer(void *gui)
__swi(0x2AE);

void SetHeaderText(void *hdr_pointer, WSHDR *txt, void *malloc_adr, void *mfree_adr)
__swi(0x2AF);

void SetMenuSoftKey(void *gui, const SOFTKEY_DESC * param2,int n)
__swi(0x2B0);

SMS_DATA_ROOT *SmsDataRoot()
__swi(0x82B1);

int GetSmsPosIndex(SMS_POS_INDEX_DATA *buf, int data_id)
__swi(0x2B2);

NativeAbData *AllocNativeAbData(void)
__swi(0x2B3);

int FreeNativeAbData(NativeAbData *ab_data)
__swi(0x2B4);

int GetNativeAbDataType(NativeAbData *nab, int n)
__swi(0x2B5);

WSHDR *GetNumFromNativeAbData(NativeAbData *nab, int type, int unk0)
__swi(0x2B6);

int GetNativeAbDataStatus(NativeAbData *nab, int n)
__swi(0x2B7);

int SetNumToNativeAbData(NativeAbData *abd, int unk, WSHDR *num)
__swi(0x2B8);

unsigned int OpenNativeAddressbook(int type, int unk1, int unk2, void *data)
__swi(0x2B9);

void SetHeaderIcon(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr)
__swi(0x2BA);

void *GetTabGUI(void *malloc_adr, void *mfree_adr)
__swi(0x2BB);

void SetGUIDefinition(void *gui, const void *definition)
__swi(0x2BC);

int SetGUIToTabGUI(void *tabgui, int n, const int *tabicons, void *gui)
__swi(0x2BD);

int SetCursorTab(void *tab_gui, int n)
__swi(0x2BE);

int UpdateTab1stItem(void *tab_gui, int unk_0)
__swi(0x2BF);

int GetCursorTab(void *tab_gui)
__swi(0x2C0);

void *GetGuiByTab(void *tab_gui, int n)
__swi(0x2C1);

int GetSubprovider(WSHDR* ws)
__swi(0x2C2);

int GetRoamingState()
__swi(0x2C3);

int GetProfileVolumeSetting(int profile, int type)
__swi(0x2C4);

RAM_EMS_ADMIN *RAM_EMS_Admin()
__swi(0x82C5);

int GetSecondsFromDateTime(int *result, TDate *t_date, TTime *time, TDate *s_date)
__swi(0x2C6);

int GetSecondsFromDateTimeSince1997(int *result, TDate *date, TTime *time)
__swi(0x2C7);

int GetSecondsFromTime(TTime *time)
__swi(0x2C8);

int GetDateTimeFromSeconds(int *seconds, TDate *t_date, TTime *time, TDate *s_date)
__swi(0x2C9);

int GetDateTimeFromSecondsSince1997(int *seconds, TDate *date, TTime *time)
__swi(0x2CA);

void GetTimeFromSeconds(TTime *time, int seconds)
__swi(0x2CB);

void InitDate(TDate *date, unsigned long year, unsigned char month, unsigned char day)
__swi(0x2CC);

void InitTime(TTime *time, unsigned char hour, unsigned char min, unsigned char sec, unsigned long millisec)
__swi(0x2CD);

int CmpDates(TDate *date1, TDate *date2)
__swi(0x2CE);

int CmpTimes(TTime *time1, TTime *time2)
__swi(0x2CF);

int GetDaysFromMonth(TDate *date)
__swi(0x2D0);

int IsLeapYear(TDate *date)
__swi(0x2D1);

void StartNativeBrowserCore()
__swi(0x2D2);

int GetFilledNAbDataCount(NativeAbData *nab)
__swi(0x2D3);

void *GetDataFromNAbData(NativeAbData *nab, int n)
__swi(0x2D4);

void UnpackNumPkt(PKT_NUM *pkt, char *buf, int maxlen)
__swi(0x2D5);

void *TViewGetGUI(void *malloc_adr, void *mfree_adr)
__swi(0x2D6);

void TViewSetDefinition(void *gui, const TVIEW_DESC * param2)
__swi(0x2D7);

void TViewSetText(void *gui, WSHDR *text, void *malloc_adr, void *mfree_adr)
__swi(0x2D8);

void TViewSetUserPointer(void *gui,void *user_pointer)
__swi(0x2D9);

void *TViewGetUserPointer(void *gui)
__swi(0x2DA);

void *GetTabGUI(void *malloc_adr, void *mfree_adr)
__swi(0x2BB);

void SetGUIDefinition(void *gui, const void *definition)
__swi(0x2BC);

int SetGUIToTabGUI(void *tabgui, int n, const int *tabicons, void *gui)
__swi(0x2BD);

int SetCursorTab(void *tab_gui, int n)
__swi(0x2BE);

int UpdateTab1stItem(void *tab_gui, int unk_0)
__swi(0x2BF);

int GetCursorTab(void *tab_gui)
__swi(0x2C0);

void *GetGuiByTab(void *tab_gui, int n)
__swi(0x2C1);

int Registry_GetHMIKeyID(char *Keyword)
__swi(0x038);

void Registry_SetResourcePath(int HMIKeyID, int Prio, WSHDR *Path)
__swi(0x039);

void Registry_DeleteResourcePath(int HMIKeyID, int Prio)
__swi(0x03A);

void Registry_GetResourcePathFromLevel(int HMIKeyID1, int Prio, int *HMIKeyID2, WSHDR *Path)
__swi(0x03E);

void StartMidlet(char* param1)
__swi(0x004B);

void SaveMaxIllumination(int level)
__swi(0x2DC);

void SetIlluminationoffTimeout(int time_sec)
__swi(0x2DD);

void IllumTimeRequest(int TimeMode, int Counter)
__swi(0x2DE);

void IllumTimeRelease(int TimeMode, int Counter)
__swi(0x2DF);

void MediaSendCSM_Open(WSHDR *file, WSHDR *path)
__swi(0x2DB);

char *RamRingtoneStatus()
__swi(0x80CB);

int RefreshAlarmClock()
__swi(0x291);

IMGHDR *GetIMGHDRFromThemeCache(int index)
__swi(0x2E0);

char *RamDisplayLanguage()
__swi(0x829D);

int GetExtUidByFileName_ws(WSHDR * fn)
__swi(0x2E1);

int wstrcmp(WSHDR*ws1,WSHDR*ws2)
__swi(0x2E2);

int fexists(WSHDR* FileName)
__swi(0x2E3);

int SettingsAE_Update_ws(WSHDR * param1,int set,char * entry,char *keyword)
__swi(0x2E4);

int SettingsAE_Read_ws(WSHDR * param1,int set,char * entry,char *keyword)
__swi(0x2E5);

int SettingsAE_SetFlag(int val,int set,char * entry,char *keyword)
__swi(0x2E6);

int SettingsAE_GetFlag(int *res,int set,char * entry,char *keyword)
__swi(0x2E7);

int SettingsAE_Update(int val,int set,char * entry,char *keyword)
__swi(0x2E8);

int SettingsAE_Read(int *res,int set,char * entry,char *keyword)
__swi(0x2E9);

void* SettingsAE_GetEntryList(int set)
__swi(0x2EA);

int SettingsAE_RemoveEntry(int set,char *entry,int flag)
__swi(0x2EB);

int i2c_transfer(I2C_MSG *msg)
__swi(0x2EC);

int i2c_receive(I2C_MSG *msg)
__swi(0x2ED);

char *RamExtendedCameraState()
__swi(0x8299);

char *RamInputLanguage()
__swi(0x829C);

#ifndef __LOADER_BUILD
int elfclose(void* ex)
__swi(0x2EE);

int _dlopen(const char *name)
__swi(0x2EF);

void *_dlsym(int handle, const char *name)
__swi(0x2F0);

int _dlclose(int handle)
__swi(0x2F1);

const char * _dlerror()
__swi(0x2F7);

#ifdef __NO_LIBC
int setenv(const char *name, const char *value, int replace)
__swi(0x2F2);

int unsetenv(const char *name)
__swi(0x2F3);

char * getenv(const char *var)
__swi(0x2F4);

int clearenv(void)
__swi(0x2F5);

char ** getBaseEnviron()
__swi(0x2F6);

const char * dlerror()
__swi(0x2F7);
#endif

int dlclean_cache()
__swi(0x2F8);

void * SHARED_TOP()
__swi(0x2F9);
#endif


WSHDR *GetClipBoard(void)
__swi(0x380);

int CopyTextToClipboard(WSHDR *src, int pos, int len)
__swi(0x381);

void ClearClipboard(char _0x12)
__swi(0x382);

int PushDRWOBJOnLAYER(DRWOBJ *obj, LCDLAYER *layer)
__swi(0x383);

int LCDRedrawLAYER(LCDLAYER *layer)
__swi(0x384);

GBSPROC *GetGBSProcAddress(short cepid)
__swi(0x385);

void SetPropTo_obj0x17(DRWOBJ *obj, RECT *rect, int zero0, EIMGHDR *eimg, int zero1, int zero2)
__swi(0x386);

LCDLAYER *GetLCDLAYERByCurCepID()
__swi(0x387);

void SetDepthBuffer(char depth)
__swi(0x388);

void SetDepthBufferOnLCDLAYER(LCDLAYER *layer, char depth)
__swi(0x389);

LCDLAYER *RamMainLCDLayer(void)
__swi(0x80F5);

LCDLAYER **RamMMILCDLayer(void)
__swi(0x80F6);

void SetProp2Square_v2(DRWOBJ *drwobj, RECT *rc, int _unk_0x20)
__swi( 0x1FD);

void SetProp2Square_v1(DRWOBJ *drwobj, RECT *rc, int zero0, int unk0, int unk1)
__swi( 0x205);

