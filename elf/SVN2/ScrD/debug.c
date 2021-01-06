#include "../inc/swilib.h"
#include "debug.h"
int dFile=-1;
int rSize;
//-----------------------------------------------------------------
void dopen(const char* dname)
{
  UINT err;
  dFile=fopen(dname,A_Create|A_WriteOnly|A_Truncate,P_WRITE,&err);
  if(dFile==-1)
    ShowMSG(1,(int)"Can't create debug file");
  rSize=GetFreeRamAvail();
}
//-----------------------------------------------------------------
void dwint(const char* vName,int iNum,int opt)
{
  char* pBuf;
  UINT err;
  pBuf=(char*)malloc(MAX_LINE);
  if(opt==I_HEX)
    sprintf(pBuf,"%s=0x%X\n",vName,iNum);
  else
    sprintf(pBuf,"%s=%d\n",vName,iNum);
  fwrite(dFile,pBuf,strlen(pBuf),&err);
  mfree(pBuf);
}
//------------------------------------------------------------------
void dwstr(const char* vName,const char* pStr)
{
  char* pBuf;
  UINT err;
  pBuf=(char*)malloc(strlen(pStr)+20);
  sprintf(pBuf,"%s=\"%s\"\n",vName,pStr);
  fwrite(dFile,pBuf,strlen(pBuf),&err);
  mfree(pBuf);
}
//-------------------------------------------------------------------
void dramav()
{
  char*pBuf;
  UINT err;
  pBuf=(char*)malloc(MAX_LINE);
  sprintf(pBuf,"RamAvaiable: %dkb\n",GetFreeRamAvail()>>10);
  fwrite(dFile,pBuf,strlen(pBuf),&err);
  mfree(pBuf);
}
//---------------------------------------------------------------------
void dclose()
{
  UINT err;
  char* pBuf;
  rSize=rSize-GetFreeRamAvail();
  pBuf=(char*)malloc(MAX_LINE);
  sprintf(pBuf,"Lost memory %d kb\n",rSize>>10);
  fwrite(dFile,pBuf,strlen(pBuf),&err);
  mfree(pBuf);
  fclose(dFile,&err);
}
