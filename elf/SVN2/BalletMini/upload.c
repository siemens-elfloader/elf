#include "../inc/swilib.h"
#include "view.h"
#include "string_works.h"
#include "display_utils.h"
#include "upload.h"

#pragma swi_number=0x244
__swi __arm int Base64Encode(void *inbuf, int insize, void *outbuf, int outsize);

const char* file_data_signature = "file=";
int filesize=0;

#define CALCLEN(a,b) ((a*4)/3+2+b+1)

void PrepareFileForUpload(void* data, char* fullname, char* name)
{ 
  REFCACHE *ref = data;
  
  ref->upload_file_data_not_present = 0;
  if ((int)ref->full_filename != 0xFFFFFFFF)
    mfree(ref->full_filename);
  ref->full_filename = (char*)malloc(strlen(fullname)+1);
  strcpy(ref->full_filename, fullname);
   
  FreeWS(((WSHDR *)ref->data));
  ref->data=(void *)AllocWS(strlen(name));
  str_2ws(((WSHDR *)ref->data), name, strlen(name));
}

unsigned int GetFileDataLen(REFCACHE* ref)
{
  FSTATS stat;
  unsigned int err;
  if (GetFileStats(ref->full_filename,&stat,&err)!=-1)
    if ((filesize=stat.size) > 0)
    {
      unsigned int maxlen = CALCLEN(filesize, strlen(file_data_signature));
      int mem_avail = GetFreeRamAvail() - maxlen;
      if (mem_avail < 204800)
      {
        filesize = 0;
        return 0;
      }
      else
        return maxlen;
    } 
  return 0;
}

unsigned int FillFileData(REFCACHE* ref, char* buf)
{
#define BUFSIZE 15000
  int f;
  unsigned int ul;
  char* filebuf;
  unsigned int filelen, outlen, maxlen, len, ret;
  unsigned int filepos = 0;
  
  
  if (filesize && ((f=fopen(ref->full_filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1))
  {
    filebuf = (char*)malloc(BUFSIZE+1);
    maxlen = CALCLEN(filesize, strlen(file_data_signature));
    strcpy(buf,file_data_signature);
    len = strlen(file_data_signature);
    do
    {
      filelen=fread(f,filebuf,BUFSIZE,&ul);
      filebuf[filelen] = 0;
    
      outlen = Base64Encode(filebuf, filelen, buf+len, maxlen);
      len += outlen;
      filepos+=filelen;
    }
    while (filelen == BUFSIZE);
    mfree(filebuf);
    fclose(f, &ul);
    ret = len;
  }
  else
    ret = 0;
  mfree(ref->full_filename);
  ref->full_filename = (char*)0xFFFFFFFF;
  return ret;
  
}
