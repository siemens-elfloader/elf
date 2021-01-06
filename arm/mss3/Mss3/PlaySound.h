// PlaySound.h: interface for the PlaySound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYSOUND_H__5F2AACD0_B81A_4C08_855B_E0D39048B50F__INCLUDED_)
#define AFX_PLAYSOUND_H__5F2AACD0_B81A_4C08_855B_E0D39048B50F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PlaySouNd  
{
public:
	int GetHandle();
	void PlayDone();
	void PlayStop();
	static void PlayStart(PlaySouNd *ps, const char *filepath);
	PlaySouNd();
	~PlaySouNd();
private:
	int handle;
};

#endif // !defined(AFX_PLAYSOUND_H__5F2AACD0_B81A_4C08_855B_E0D39048B50F__INCLUDED_)
