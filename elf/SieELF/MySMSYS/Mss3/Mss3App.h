// Mss3App.h: interface for the Mss3App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSS3APP_H__328ADB32_1D39_42C7_B160_317CDD3DFD8F__INCLUDED_)
#define AFX_MSS3APP_H__328ADB32_1D39_42C7_B160_317CDD3DFD8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Mss3App  
{
public:
	static int IsAlreadyRuning();
	static void Killer();
	static void InitDatPath();
	static void InitSetting();
	static int Start(char *exename, char *fname);

};

#endif // !defined(AFX_MSS3APP_H__328ADB32_1D39_42C7_B160_317CDD3DFD8F__INCLUDED_)
