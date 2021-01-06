// PlaySound.cpp: implementation of the PlaySound class.
//
//////////////////////////////////////////////////////////////////////

#include "include.h"
#include "PlaySound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PlaySouNd::~PlaySouNd()
{
	if(this->handle)
	{
		PlayMelody_StopPlayback(this->handle);
		this->handle=0;
	}
}

PlaySouNd::PlaySouNd()
{
	this->handle=0;
}

void PlaySouNd::PlayStart(PlaySouNd *ps, const char *filepath)
{
	if(!ps || !filepath)
		return;
	if(ps->handle)
	{
		ps->PlayStop();
	}
	PLAYFILE_OPT _sfo1;
	WSHDR *sndPath,sndPathn;
	WSHDR *sndFName,sndFNamen;
	unsigned short sndPathb[128];
	unsigned short sndFNameb[128];
	char s[128];
	const char *p;
	int snd_vol;
	CFile file;
	if(!file.IsFileExist(filepath)
		|| !CFG_ENA_SOUND
		|| !(snd_vol=GetProfileVolumeSetting(GetProfile(), VOLUME))
		)
	{
		return;
	}
	sndPath=CreateLocalWS(&sndPathn, sndPathb, 128);
	sndFName=CreateLocalWS(&sndFNamen, sndFNameb, 128);
	p=strrchr(filepath,'\\')+1;
	str_2ws(sndFName,p,128);
	strncpy(s,filepath,p-filepath);
	s[p-filepath]='\0';
	str_2ws(sndPath,s,128);
	zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
	_sfo1.repeat_num=1;
	_sfo1.time_between_play=0;
	_sfo1.play_first=0;
	_sfo1.volume=snd_vol;//
#ifdef NEWSGOLD
	_sfo1.unk6=1;
	_sfo1.unk7=1;
	_sfo1.unk9=2;
	ps->handle=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
	_sfo1.unk4=0x80000000;
	_sfo1.unk5=1;
	ps->handle=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
	_sfo1.unk5=1;
	ps->handle=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
}

void PlaySouNd::PlayStop()
{
	if(this->handle)
	{
		PlayMelody_StopPlayback(this->handle);
		this->handle=0;
	}
}

void PlaySouNd::PlayDone()
{
	this->handle=0;
}

int PlaySouNd::GetHandle()
{
	return this->handle;
}
