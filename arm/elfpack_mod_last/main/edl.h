

extern long elfload(char *filename, void *param1, void *param2, void *param3);
extern int get_file_size(const char * fname);
extern unsigned int DEFAULT_DISK_N;

//BCFG - Max Library Size
extern unsigned int edl_sys_size;
#define EDL_MAXSIZE edl_sys_size

//Void Element  for EDL System
#define EDL_VOID 0xD00DD00D

//IDs for EDL file lib
#define EDL_ID1  0xDDDDEEEE
#define EDL_ID2  0x33212133
#define EDL_ID3  0xEEEEDDDD

//Small phone list
#define EDL_PHONE_NONE        "NONE"  // �� ����� (Not important)

#define EDL_PHONE_SGX65_C65   "C65"   // C65
#define EDL_PHONE_SGX65_SL65  "SL65"  // SL65
#define EDL_PHONE_SGX65_M65   "M65"   // M65
#define EDL_PHONE_SGX65_CX65  "CX65"  // CX65
#define EDL_PHONE_SGX65_CX70  "CX70"  // CX70
#define EDL_PHONE_SGX65_SK65  "SK65"  // SK65
#define EDL_PHONE_SGX65_S65   "S65"   // S65

#define EDL_PHONE_SGX75_C72   "C72"   // C72
#define EDL_PHONE_SGX75_CF75  "CF75"  // CF75
#define EDL_PHONE_SGX75_ME75  "ME75"  // ME75
#define EDL_PHONE_SGX75_C75   "C75"   // C75
#define EDL_PHONE_SGX75_M75   "M75"   // M75
#define EDL_PHONE_SGX75_CX75  "CX75"  // CX75

#define EDL_PHONE_NSG_S68     "S68"   // S68
#define EDL_PHONE_NSG_C81     "C81"   // C81
#define EDL_PHONE_NSG_M81     "M81"   // M81
#define EDL_PHONE_NSG_SL75    "SL75"  // SL75
#define EDL_PHONE_NSG_S75     "S75"   // S75

#define EDL_PHONE_ELKA_EL71   "EL71"  // EL71
#define EDL_PHONE_ELKA_E71    "E71"   // E71

//Platform list
#define EDL_PLATFORM_NONE     0x00    // �� ����� (Not important)
#define EDL_PLATFORM_SGX65    0x01    // SGold X65
#define EDL_PLATFORM_SGX75    0x02    // SGold X75
#define EDL_PLATFORM_NSG      0x04    // NewSGold
#define EDL_PLATFORM_ELKA     0x08    // NewSGold E/EL71 (ELKA)
//M���� �� �����������, ��� �������: EDL_PLATFORM_NSG   + EDL_PLATFORM_ELKA
//                                   EDL_PLATFORM_SGX65 + EDL_PLATFORM_SGX75 + EDL_PLATFORM_NSG

//Firmware
#define EDL_FIRMWARE_NONE     0x00    // �� ����� (not important)


//EDL Struct - Lib Header
typedef struct {
  // IDs
  int   id1;                          // ID1
  int   id2;                          // ID2
  int   id3;                          // ID3
  // ��������, ������ (Name, version)
  char  name[32];                     // ��� ���������� (Library Name)
  char  authors[64];                  // ��������� ((C)opy(R)ights)
  short version;                      // ������ ���������� (Library version)
  short count;                        // ���-�� �-�� � ���������� (Count Functions in Library)
  //������������� (Support)
  char  platform;                     // ��������� (Phone Platform), EDL_PLATFORM_NONE - �� ����� (not important)
  char  phone[9];                     // M����� �������� (Phone Model), EDL_PHONE_NONE - �� ����� (not important)
  short sw;                           // �������� (FirmWare), EDL_FIRMWARE_NONE - �� ����� (not important)
  //������ �-�� (Functions call addresses)
  void (*killproc)();                 // ����� �-�� �������� ���������� �� RAM (Address function for kill current Library)
}EDL_HEADER;

typedef struct { 
  void *func_first;                   // ������ ������ � ����������� �-�� �� ����������
  /*                                  // Addresses first and next functions from current library
  void *func_second;
  void *func_third;
  ...
  void *func_last;
  */
}EDL_POINTERS;

typedef struct {
  EDL_HEADER edl_head;
  EDL_POINTERS edl_pnt;
}EDL_STRUCT;
  


// EDL System Init
// 0 - EDL ������� ��� �������� (EDL System is launched)
// 1 - EDL ������� ������� (EDL System is created)
__arm int EDL_system_init();

// EDL System Kill
// 0 - EDL ������� �� �������� ��� �� �������� (EDL System don't load or don't work)
// 1 - EDL ������� ����� (EDL System is killed)
__arm int EDL_system_kill();

// EDL System ReInit
__arm int EDL_system_reinit();

//-1 - �� �������! (No find)
//-2 - EDL ������� �� �������� ��� �� �������� (EDL System don't load or don't work)
//+i - �������� ������� ��������� ���������� (Place find lib)
__arm int isEDL_exist_ep(char *name, short version);

//0 - ���������� �� �������������� (Current Library don't support)
//1 - ���������� �������������� (Current Library support)
__arm int isEDL_support_ep(char platform, char *phone, short sw);

// -100  - ��� ����� (File is not find)
// -101  - ���� �� �����������/�� �������� (File don't open / don't read)
// -102  - ������������ ������ (Is not memory)
// -103  - C�������� EDL_HEADER �� ���������� (EDL_HEADER struct is not detect)
// -104  - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
// -105  - ������ ���������� ��� ���������� (Library is exist)
// -106  - � ���������� ��� �� ����� �-�� (In library zero count functions)
// -107  - ���������� �� �������������� (Library is not support)

// -1 .. -13 - ������ ������� 'ELF' (Errors of ELF format)

// +i    - ���������� ���������! i - �������� ���-�� �-�� (Library is loaded, i is count functions of library)
__arm int EDL_load_ep(char *fname);

//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ���������� ��������� (Library unload from RAM)
__arm int EDL_unload_ep(char *name, short version);

//  0 - ���������� ��� ���������� (Library is exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ��������� (Library added in base)
__arm int EDL_addlib_ep(EDL_STRUCT *edl_struct);

//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ���������� ������ �� ������� (�� ��� ����� � RAM) / Library is removed, but she in RAM
__arm int EDL_remove_ep(EDL_STRUCT *edl_struct);

//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ������ �-�� ��������� (Addresses functions filled) 
__arm int EDL_use_ep(char *name, short version, void *func_struct);

// ���������� ��������� �� ���� ���������� (Return pointer on Library)
__arm void *getEDL_baseAddr_ep();

// ���������� ������� ���-�� ����������� ��������� (Return �urrent count libs)
__arm int getEDL_curLibs_ep();

// ���������� ������������ ���-�� ����������� ��������� (Return max count libs)
__arm int getEDL_maxLibs_ep();
