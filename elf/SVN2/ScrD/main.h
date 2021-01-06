#define ELF_NAME "ScrD"

#define UpdateCSMname() wsprintf((WSHDR *)(&MAINCSM.maincsm_name),ELF_NAME)
#define exit() SUBPROC((void*)kill_data,__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
typedef int hProc;
void RegHandle(hProc pProc);
void DelHandle(hProc pProc);

void RedrawProc();

#pragma swi_number=0x80D8
__swi __arm char* RamMenuAnywhere();
