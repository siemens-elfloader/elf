#include "..\..\inc\swilib.h"
//#include "..\inc\swilib.h"

#define MSG_FILE  "2:\\security.msg"
#define IMSI_FILE "2:\\IMSI.dat"

#define BRIGHT 50
#define TIMES  10

#define TICK 216
#define IN_TICKS(sec) (sec * TICK)

// 1/10 sec
#define PERIOD 5

int count;
GBSTMR mytmr;


__thumb void LightOff(void);


//SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay);
//0 - дисплей, 1 - клавиатура, 2 - динамический свет (x65)
__thumb void LightOn()
{
	SetIllumination(0, 1, BRIGHT, 0);
	SetIllumination(1, 1, BRIGHT, 0);   
	SetIllumination(4, 1, BRIGHT, 0);

	GBS_StartTimerProc(&mytmr, IN_TICKS(PERIOD) / 20, LightOff);
}

__thumb void LightOff()
{
	SetIllumination(0, 1, 0, 0);
	SetIllumination(1, 1, 0, 0);   
	SetIllumination(4, 1, 0, 0);

	if (--count)
		GBS_StartTimerProc(&mytmr, IN_TICKS(PERIOD) / 20, LightOn);
}

__thumb char *BCD2Str(const char *BCDStr, char nbytes)
{
	char *res;
	if (!BCDStr)
		return (NULL);
	res = malloc(2 * nbytes + 1);
	res[2 * nbytes] = 0;
	for(int i = 0; i < nbytes; i++)
	{
		res[2 * i] = ((BCDStr[i] >> 4) & 0xF) + 0x30;
		res[2 * i + 1] = (BCDStr[i] & 0xF) + 0x30;
	}
	return (res);
}


#define MAX_TEXT 256

__thumb char *GetStrFromFile(char *FName)
{
	char *out;
	unsigned int ierr;
	int isize;
	int hfile = fopen(FName, A_NoShare | A_Exclusive | A_BIN, P_READ, &ierr);
	if (hfile == -1)
		return (NULL);
	out = malloc(MAX_TEXT);
	isize = fread(hfile, out, MAX_TEXT, &ierr);
	fclose(hfile, &ierr);
	if (isize >= 0)
	{
		out[isize] = 0;
		return (out);
	}
	return (NULL);
}

#pragma inline
void Alert(void)
{
	char *Msg;
	count = TIMES;
	LightOn();
	Msg = GetStrFromFile(MSG_FILE);
	if (Msg != NULL)
	{
		ShowMSG(1, (int)Msg);
		mfree(Msg);
	}
}

void patch(void)
{
	char *ValidIMSIs = GetStrFromFile(IMSI_FILE);
	char *CurrIMSI = BCD2Str(RAM_IMSI(), 9);
	int IsValidIMSI = (ValidIMSIs && CurrIMSI) ? (int)strstr(ValidIMSIs, CurrIMSI) : 0L;
	if (*RamPressedKey()== '*')
	{
		ShowMSG(1, (int)"«*» pressed. Security disabled!");
		return;
	}
	if (IsValidIMSI)
	{
		ShowMSG(1, (int)"IMSI is valid. Security disabled!");
		return;
	}
	Alert();
}

