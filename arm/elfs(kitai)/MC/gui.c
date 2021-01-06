#include "inc\color.h"
#include "inc\mc.h"
#include "inc\gui.h"
#include "inc\lng.h"
#include "inc\mui.h"
#include "inc\ColorMap.h"
#include "inc\zslib.h"

GBSTMR sctm;
FILEINF* scfile=NULL;
int scind;
int sctpos;
int sctdir;
int scwait;

int scr_w;
int scr_h;
int txt_h;
int ico_hw;
int itm_ch;
int itms_max;
int itms_bs;

int NormalFont;
int BoldFont;

void InitScr()
{
	scr_w = ScreenW();
	scr_h = ScreenH();
	ico_hw = GetImgHeight(ext_dir.ico);
	txt_h = GetFontYSIZE(NormalFont); 
	if (!txt_h)
	{
		ShowMSG(1, (int)"Не уд. опред. выс. шрифта.\nGetFontYSIZE()=0");
		txt_h = 16; //!!!
	}
	int tmp = ico_hw - ITM_B * 2;
	itm_ch = tmp > txt_h ? tmp : txt_h;
	itms_max = ((FLS_H - ITM_S * 2) / ITM_FH)-1;
	itms_bs = FLS_Y + ( ( (FLS_H - ITM_S * 2)-((itms_max + 1) * ITM_FH) ) / 2 );
}

void DrwFile(int ind, FILEINF* file)
{ 
	if (ind > _CurIndex-_CurBase) ind++;
	int y = itms_bs + ind*ITM_FH;
	if (ind == _CurIndex-_CurBase) 
	{
		if (scfile != file)
		{  
			scfile = file;
			scind = ind;
			sctpos = 0;
			sctdir = 1;
			scwait = CONFIG_SCROLL_TEXT_WAIT;
		} 
		DrawRoundedFrame(ITM_X1,y,ITM_X2,y+ITM_FH*2-1,4,4,1,(char*)&Colors[clSelItemBD],(char*)&Colors[clSelItemBG]);

		int y2 = itms_bs+(ind+1)*ITM_FH;

		if (!(file->attr & FA_DIRECTORY))
		{
			if (file->ws_size) 
				DrawString(file->ws_size,TXT_X,y2+ITM_B+1,ITM_X2-ITM_B-2,y2+ITM_B+txt_h,NormalFont,TEXT_ALIGNLEFT,
					(char*)&Colors[clInfoTxt],0);

			if (file->ftype == TYPE_ZIP_FILE && file->ws_ratio)
			{
				// рисовать будем посередине + отступ на 1/2 символа
				int posX = (ITM_X2 - ITM_B - 2 - TXT_X) / 2 + TXT_X + txt_h / 2;
				DrawString(file->ws_ratio, posX ,y2+ITM_B+1,ITM_X2-ITM_B-2,y2+ITM_B+txt_h,NormalFont,TEXT_ALIGNLEFT,
					(char*)&Colors[clInfoTxt],0);
			}
		} 
		if (file->ws_attr)
			DrawString(file->ws_attr,TXT_X,y2+ITM_B+1,ITM_X2-ITM_B-2,y2+ITM_B+txt_h,NormalFont,TEXT_ALIGNRIGHT,
				(char*)&Colors[clInfoTxt],0);
	}
	EXTINF* ext = file->attr & FA_CHECK ? &ext_chk : file->ext;
	DrawImg(ICO_X, y+ICO_DY, ext->ico);

	int tc;
	if (file->attr & (FA_READONLY | FA_SYSTEM)) 
		tc=ind==_CurIndex-_CurBase?clSelFileReadOnly:clFileReadOnly;
	else if (file->attr & FA_HIDDEN)				
		tc=ind==_CurIndex-_CurBase?clSelFileHidden:clFileHidden;
	else
		tc=ind==_CurIndex-_CurBase?clSelFileNormal:clFileNormal;

	WSHDR* fn = (file->uccnt ? file->ws_short :
					(curtab == systab && file->ws_showname ? file->ws_showname : file->ws_name));
	if (fn)
		DrawString(fn,TXT_X,y+ITM_B+1,ITM_X2-ITM_B-2,y+ITM_B+txt_h,BoldFont,TEXT_ALIGNLEFT,
			(char*)&Colors[tc],0);
}

void DrwName()
{
	if (!Busy && scfile && IsGuiOnTop(MAINGUI_ID))
	{
		WSHDR* ws = (curtab == systab && scfile->ws_showname ? scfile->ws_showname : scfile->ws_name);
		if (ws && scfile->uccnt)
		{
			int gend=FALSE;
			int sc = getLVC(&ws->wsbody[sctpos+1],
				ws->wsbody[0]-sctpos,
				BoldFont);
			if (!sc)
			{
				sc=ws->wsbody[0]-sctpos;
				gend = sctdir>0;	  
			}  

			WSHDR* txt = AllocWS(sc+1);
			txt->wsbody[0]=sc;
			//	 txt->wsbody[sc+1]=0;
			for(int ii=1;ii<sc+1;ii++)
				txt->wsbody[ii]=ws->wsbody[ii+sctpos];

			if (scwait<=0)
			{
				if (gend)
				{
					sctdir=-1;
					scwait=CONFIG_SCROLL_TEXT_WAIT-1;
				} else
					sctpos=sctpos+sctdir;
				if (sctpos<=0)
				{
					sctdir=1;
					scwait=CONFIG_SCROLL_TEXT_WAIT;
				}
			}
			else
				scwait--;

			int y = itms_bs+scind*ITM_FH;
			int tc;
			if (scfile->attr & (FA_READONLY | FA_SYSTEM)) 
				tc=clSelFileReadOnly;
			else if (scfile->attr & FA_HIDDEN )				
				tc=clSelFileHidden;
			else
				tc=clSelFileNormal;

			DrawRoundedFrame(TXT_X,y+ITM_B+1,ITM_X2-ITM_B-2,y+ITM_B+txt_h,0,0,1,0,(char*)&Colors[clSelItemBG]);
			DrawString(txt,TXT_X,y+ITM_B+1,ITM_X2-ITM_B-2,y+ITM_B+txt_h,BoldFont,TEXT_ALIGNLEFT,
				(char*)&Colors[tc],0);
			FreeWS(txt);
		}  
	} 
	GBS_StartTimerProc(&sctm,CONFIG_SCROLL_TEXT_SPEED,DrwName);
}

void DrwDrvBg(int ind)
{
	int x = DRV_X+DRV_O*ind;
	DrawRoundedFrame(x,TOP_Y,x+DRV_W-1,TOP_Y+TOP_H-1,4,4,0,
		(char*)&Colors[clUSTabBD],(char*)&Colors[clUSTabBG]);
}

void DrwDrvAc(int ind)
{
	char* name;
	int x;
	if (curtab < MAX_TABS)
	{
		x = DRV_X + DRV_O*ind;
		if (IsInZip())
			name = (char*)psz_zipvol;
		else
			name = (char*)&Drives[ind].name;
	}
	else if (curtab == systab)
	{
		x = DRV_X;
		name = psz_mcvol;
	}
	wsprintf(guibuf, _t, name);
	DrawRoundedFrame(x,TOP_Y,x+DRV_W-1,TOP_Y+TOP_H-1,4,4,1,(char*)&Colors[clSlTabBD],(char*)&Colors[clSlTabBG]);
	DrawString(guibuf,x+1,TOP_Y+TOP_B,x+DRV_W-2,TOP_Y+TOP_B+TOP_H-1,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
		(char*)&Colors[clTabTxt],(char*)&Colors[clTabTxtBD]);
}

void DrwCurTab()
{
	DrawRoundedFrame(TAB_X,TOP_Y,TAB_X+TAB_W-1,TOP_Y+TOP_H-1,4,4,1,(char*)&Colors[clSlTabBD],(char*)&Colors[clSlTabBG]);
	wsprintf(guibuf, _d, curtab+1);
	DrawString(guibuf,TAB_X,TOP_Y+TOP_B,TAB_X+TAB_W-2,TOP_Y+TOP_B+TOP_H-1,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
		(char*)&Colors[clTabTxt],(char*)&Colors[clTabTxtBD]);
}

const char stn[]={'n','e','s','d','?'};

void DrwSort()
{
	int i = _CurTab->sort & STV_MASK;
	if (i > ST_DATE) i = 4;

	char s = stn[i];
	if (_CurTab->sort & STD_MASK) s -= 'a' - 'A';

	wsprintf(guibuf, "%c", s);
	DrawString(guibuf,SRT_X,TOP_Y+TOP_B,IND_X1,TOP_Y+TOP_B+TOP_H-1,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
		(char*)&Colors[clIndexTxt],(char*)&Colors[clIndexTxtBD]);
}

void DrwIndex()
{
	int chkcnt = EnumChk(NULL,0);
	if (chkcnt)
		wsprintf(guibuf,"%d(%d)", chkcnt, _CurCount);
	else
		wsprintf(guibuf,"%d/%d", _CurIndex+1, _CurCount);
	DrawString(guibuf,IND_X1,TOP_Y+TOP_B,IND_X2-2,TOP_Y+TOP_B+TOP_H-1,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
		(char*)&Colors[clIndexTxt],(char*)&Colors[clIndexTxtBD]);
}

int GetSBY(int i, int c)
{
	return (c<=1)?0:((SB_H-SB_VS+1)*i/(c-1));
}

void DrwSB()
{
	int sby = FLS_Y+1+GetSBY(_CurIndex, _CurCount);
	DrawLine(SB_X+SB_HS/2, FLS_Y+1+SB_B, SB_X+SB_HS/2, FLS_Y+SB_H-1, 0,(char*)&Colors[clScBar]);
	DrawRectangle(SB_X,sby,SB_X+SB_HS-1,sby+SB_VS-1,0,0,(char*)&Colors[clScBarBG]);
}

void ShowFiles()
{
	if (!guibuf) return;
	DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,(char*)&Colors[clBD],(char*)&Colors[clBG]);

	if (curtab < MAX_TABS) DrwCurTab();
	for(int ii=0; ii<_CurDrv; ii++) DrwDrvBg(ii);

	DrwDrvAc(_CurDrv);

	DrawRoundedFrame(FLS_B,FLS_Y,scr_w-FLS_B-1,FLS_Y+FLS_H-1,
		0,0,0,(char*)&Colors[clListBD],(char*)&Colors[clListBG]);

	int ibase, icount;
	if (_CurCount<=itms_max)
	{
		icount=_CurCount;
		ibase=0;
	}
	else
	{
		icount=itms_max;
		ibase=_CurBase;

		int idist = _CurIndex - _CurBase;

		if (idist >= itms_max-1) ibase += idist - itms_max + 2;
		else if (_CurIndex <= _CurBase) ibase += idist - 1;

		if (ibase < 0) ibase = 0;
		else if (ibase > _CurCount - itms_max) ibase = _CurCount - itms_max;
	}
	_CurBase = ibase;

	FILEINF *file = FileListBase[curtab];
	//skip
	for(int ii=0; ii<ibase; ii++) file=file->next;

	for(int ii=0; ii<icount; ii++)
	{
		file = file->next;
		FillFileInfo(file);
		DrwFile(ii, file);
	}

	DrwSB();
	DrwSort();
	DrwIndex();
}

void ShowProgr()
{
	if (!guibuf) return;
	DrawRoundedFrame(PRGB_X1,PRGB_Y,PRGB_X2,PRGB_Y+PRGB_H-1,0,0,0,(char*)&Colors[clProgrBoxBD],(char*)&Colors[clProgrBoxBG]);

	int p = progr_cur * 100 / progr_max;

	if (progr_act)
	{
		wsprintf(guibuf, _tc, muitxt(progr_act));
		DrawString(guibuf,PRGB_X1+2,PRG_AT_Y,PRGB_X2-2,PRG_AT_Y+txt_h,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
			(char*)&Colors[clProgrTxt],(char*)&Colors[clProgrTxtBD]);
	} 

	wsprintf(guibuf,"%d%% %d/%d",p,progr_cur,progr_max);
	DrawString(guibuf,PRGB_X1+2,PRG_PT_Y,PRGB_X2-2,PRG_PT_Y+txt_h,BoldFont,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,
		(char*)&Colors[clProgrTxt],(char*)&Colors[clProgrTxtBD]);

	p = progr_cur * (PRGP_X2-PRGP_X1-2) / progr_max;

	DrawRoundedFrame(PRGP_X1,PRG_B1_Y,PRGP_X2,PRG_B1_Y+PRGP_H,0,0,0,(char*)&Colors[clProgrBD],(char*)&Colors[clProgrBG]);
	DrawRoundedFrame(PRGP_X1+1,PRG_B1_Y+1,PRGP_X1+p+1,PRG_B1_Y-1+PRGP_H,0,0,0,0,(char*)&Colors[clCurProgrBG]);

	if (progrsp_start)
	{
		DrawRoundedFrame(PRGP_X1,PRG_B2_Y,PRGP_X2,PRG_B2_Y+PRGP_H,0,0,0,(char*)&Colors[clProgrBD],(char*)&Colors[clProgrBG]);
		if (progrsp_max)
		{
			int p = progrsp_cur * (PRGP_X2-PRGP_X1-2) / progrsp_max;
			DrawRoundedFrame(PRGP_X1+1,PRG_B2_Y+1,PRGP_X1+p+1,PRG_B2_Y-1+PRGP_H,0,0,0,0,(char*)&Colors[clCurProgrBG]);
		} 
	} 
}
