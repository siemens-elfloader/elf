// KeyHook.h: interface for the KeyHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYHOOK_H__957A15D9_9398_4520_BC5B_663FD8DE7652__INCLUDED_)
#define AFX_KEYHOOK_H__957A15D9_9398_4520_BC5B_663FD8DE7652__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KeyHook  
{
public:
	static void Remove();
	static int HookProc(int submsg, int msg);
	static void Create();

private:
	static int mode;
	static int IsIdle();
	static int IsSS();

};

#endif // !defined(AFX_KEYHOOK_H__957A15D9_9398_4520_BC5B_663FD8DE7652__INCLUDED_)
