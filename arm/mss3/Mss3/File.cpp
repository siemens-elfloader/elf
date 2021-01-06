#include "include.h"
#include "File.h"

int CFile::FOpen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode)
{
  return (fopen(cFileName, iFileFlags, iFileMode, &ferr));
}

int CFile::FRead(int FileHandler, void *cBuffer, int iByteCount)
{
  return (fread(FileHandler, cBuffer, iByteCount, &ferr));
}

int CFile::FWrite(int FileHandler, void const * cBuffer, int iByteCount)
{
  return (fwrite(FileHandler, cBuffer, iByteCount, &ferr));
}

void CFile::FClose(int FileHandler)
{
  fclose(FileHandler, &ferr);
}

int CFile::LSeek(int FileHandler, unsigned int offset, unsigned int origin)
{
  return (lseek(FileHandler, offset, origin, &ferr, &ferr));
}

int CFile::MkDir(const char * cFileName)
{
  return (mkdir(cFileName, &ferr));
}

int CFile::IsDir(const char * cDirectory)
{
  return (isdir(cDirectory, &ferr));
}

int CFile::FindFirstFile(DIR_ENTRY *DIRENTRY,char *mask)
{
  return (::FindFirstFile(DIRENTRY, mask, &ferr));
}

int CFile::FindNextFile(DIR_ENTRY *DIRENTRY)
{
  return (::FindNextFile(DIRENTRY, &ferr));
}

int CFile::FindClose(DIR_ENTRY *DIRENTRY)
{
  return (::FindClose(DIRENTRY, &ferr));
}

int CFile::IsFileExist(const char *filepath)
{
  FSTATS fst;
  if(GetFileStats(filepath, &fst, &ferr)==-1)
    return 0;
  else
    return 1;
}

int CFile::FDelete(const char * cFileName)
{
  return (unlink(cFileName, &ferr));
}

int CFile::FMove(const char * SourceFileName, const char * DestFileName)
{
  return (fmove(SourceFileName, DestFileName, &ferr));
}


#define MAX_CNT 40
// -1:err, -2: >MAX_CNT
int CFile::GetFileCountOfDir(const char *dirpath)
{
  char folder[128];
  DIR_ENTRY de;
  int len;
  int c;
  int cnt=0;
  if(!dirpath
    || !IsDir(dirpath)
    )
    return -1;
  strcpy(folder, dirpath);
  if((len=strlen(folder))<3)
    return -1;
  c=folder[len-1];
  if(c!='\\'
    && c!='/'
    )
  {
    folder[len++]='\\';
    folder[len]='\0';
  }
  strcat(folder, "*.*");
  if(FindFirstFile(&de, folder))
  {
    do
    {
      if(cnt>=MAX_CNT)
      {
	cnt=-2;
	break;
      }
      cnt++;
    }while(FindNextFile(&de));
  }
  FindClose(&de);
  return cnt;
}


