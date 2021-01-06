#include "crashprotect.h"
#include "..\inc\swilib.h"

char* CrashProtect::ElfName="unk";
char CrashProtect::ZBinDrive='0';
char CrashProtect::flagfile[128]="_:\\Zbin\\crashprotect";
int CrashProtect::crashed=-1;

void CrashProtect::CheckForCrash()
{
if(crashed>=0)return;
flagfile[0]=ZBinDrive;
unsigned int u;
if(!isdir(flagfile,&u)) mkdir(flagfile,&u);
strcat(flagfile,"\\");
strcat(flagfile,ElfName);

int hFile = fopen(flagfile, A_ReadOnly + A_BIN, P_READ, &u);
if(hFile!=-1)
  {
    fclose(hFile, &u);
    crashed=1;
    
    char bu[256];
    sprintf(bu,"%s possibly crashed and had disabled by CRASHPROTECT.",ElfName);
    ShowMSG(2,(int)bu);
    //unlink(flagfile,&u);
  }
else
  crashed=0;
};


void CrashProtect::CorrectlyTerminate()
  {
  CheckForCrash();  
  unsigned int u;  
  unlink(flagfile,&u);
  };

void CrashProtect::Start()
  {
  CheckForCrash();   
  unsigned int u;  
  int hFile = fopen(flagfile, A_ReadWrite+ A_Create + A_BIN, P_READ + P_WRITE, &u);
  if(hFile!=-1) fclose(hFile, &u);
  };
