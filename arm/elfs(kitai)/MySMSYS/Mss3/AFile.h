// AFile.h: interface for the AFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AFILE_H__90A5084B_019F_4F9E_82E3_56DD9922030F__INCLUDED_)
#define AFX_AFILE_H__90A5084B_019F_4F9E_82E3_56DD9922030F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFile  
{
public:
	int LSeek(unsigned int offset, unsigned int origin);
	int FWrite(void const * cBuffer, int iByteCount);
	int FRead(void *cBuffer, int iByteCount);
	int FOpen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode);
	AFile(const char *cFileName, unsigned int iFileFlags, unsigned int iFileMode);
	void FClose();
	AFile();
	~AFile();
private:
	unsigned int ferr;
	int fin;
};

#endif // !defined(AFX_AFILE_H__90A5084B_019F_4F9E_82E3_56DD9922030F__INCLUDED_)
