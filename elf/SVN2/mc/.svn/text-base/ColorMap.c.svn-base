
#include "inc\color.h"
#include "inc\mc.h"
#include "inc\ColorMap.h"

//Colors
#define ITM_C_BG	clWhite
#define ITM_C_BD	(clBlue+clDark)
#define ITM_C_BGS	(clBlue+clLight)
#define ITM_C_BDS	clWhite

#define TC_NORMAL	clBlack
#define TC_HIDDEN	clGrey
#define TC_HIDDENS	clDarkGrey
#define TC_READONLY	(clRed+clDark)

#define DRV_C_BG	(clBlue+clDark)
#define DRV_C_BD	clWhite
#define DRV_C_BGS	(clBlue+clLight)
#define DRV_C_BDS	clWhite

#define PRG_C_BD	clWhite
#define PRG_C_BG	(clBlue+clDark)
#define PRGP_C_BG	clRed

const char mccs_deffile[]="default.mccs";
const char mccs_ext[]="mccs";

int Colors[clMAX+1];
const int ColorIndex[clMAX+1] = {
	clWhite, clBlack, ITM_C_BG, ITM_C_BD, ITM_C_BGS, ITM_C_BDS, 
	TC_NORMAL, TC_NORMAL, TC_HIDDEN, TC_HIDDENS, TC_READONLY, TC_READONLY, clWhite, 
	clWhite, clBlue+clDark,
	clWhite, clBlue+clDark, DRV_C_BGS, DRV_C_BDS, DRV_C_BG, DRV_C_BD, 
	clWhite, clBlue+clDark, PRG_C_BG, PRG_C_BD, PRG_C_BG, PRG_C_BD, PRGP_C_BG,
	clLightGrey, clDarkGrey
};

void InitCS()
{
	for(int ii=0;ii<=clMAX;ii++)
		nricp(GetPaletteAdrByColorIndex(ColorIndex[ii]), (char*)&Colors[ii]);
	if (CONFIG_LOAD_CS)LoadCS(NULL);
}

void SaveCS(char* filename)
{
	char* fn = filename?filename:MCFilePath(mccs_deffile);

	int f;
	if (fn && (f=fopen(fn,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1)
	{
		MCCS_hdr hdr;
		hdr.sig=mccs_sig;
		hdr.ver=mccs_ver;
		hdr.size=mccs_size;
		hdr.offset=mccs_offset;

		fwrite(f,&hdr,sizeof(hdr),&err);
		fwrite(f,&Colors,sizeof(Colors),&err);
		fclose(f,&err);
	}
}

int LoadCS(char* filename)
{
	int res = 0;
	char* fn = filename?filename:MCFilePath(mccs_deffile);

	int f;
	if (fn && (f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
	{
		MCCS_hdr hdr;
		if (fread(f, &hdr, sizeof(hdr), &err)==sizeof(hdr))
		{
			if ((hdr.sig==mccs_sig) && (hdr.size>=mccs_size))
			{
				lseek(f,hdr.offset,S_SET,&err,&err);
				res = fread(f, &Colors, sizeof(Colors), &err)==sizeof(Colors);
			}
		}
		fclose(f, &err);
	}
	if (res && GUIStarted) REDRAW();
	return res;
}
