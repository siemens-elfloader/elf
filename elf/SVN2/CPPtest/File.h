#ifndef _FILE_H_
#define _FILE_H_

//#include "..\inc\swilib.h"

class CFile
{
private:
  unsigned int ferr;
public:  
  int hFile;
  int retval;
  char fname[128];
  
  void SetFileName(const char* path);
  void Close();
  int Open(unsigned int iFileFlags);
  int Read(void *cBuffer, int iByteCount);
  char* ReadBuf(int iByteCount);
  int Write(void const * cBuffer, int iByteCount);
  int Size();
  int Seek(unsigned int offset, unsigned int origin);
  
  //-----------
  
  int FOpen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode);
  int FRead(int FileHandler, void *cBuffer, int iByteCount);
  int FWrite(int FileHandler, void const * cBuffer, int iByteCount);
  void FClose(int FileHandler);
  int LSeek(int FileHandler, unsigned int offset, unsigned int origin);
  int MkDir(const char * cFileName);
  int IsDir(const char * cDirectory);
  int FindFirstFile(DIR_ENTRY *DIRENTRY,char *mask);
  int FindNextFile(DIR_ENTRY *DIRENTRY);
  int FindClose(DIR_ENTRY *DIRENTRY);
  int IsFileExist(const char *filename);
  int GetSize(const char *filepath);
  int FDelete(const char * cFileName);
  int FMove(const char * SourceFileName, const char * DestFileName);
  
  CFile(char *fname = NULL);
  ~CFile();
  
};
#endif

