#ifndef _FILE_H_
#define _FILE_H_
class CFile
{
private:
  unsigned int ferr;
public:
	int GetFileCountOfDir(const char *dirpath);
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
  int FDelete(const char * cFileName);
  int FMove(const char * SourceFileName, const char * DestFileName);
};
#endif

