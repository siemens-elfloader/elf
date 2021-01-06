#include "inc\mc.h"
#include "inc\mui.h"

HEADER_DESC disk_prop_hdr={0,0,0,0,NULL,0,LGP_NULL};
INPUTDIA_DESC disk_prop_desc=
{
	1,
	empty_onkey,
	empty_ghook,
	(void *)empty_locret,
	0,
	&empty_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};

void DoDrvInf()
{
	disk_prop_hdr.lgp_id = (int) muitxt(ind_prop);

	EDITCONTROL ec;
	void *ma=malloc_adr();
	void *eq=AllocEQueue(ma, mfree_adr());
	PrepareEditControl(&ec);

	WSHDR *buff = AllocWS(64);

	unsigned int iTotal, iFree;
	float fFree;
	char szTotal[32];
	char szFree[32];
	char szPFree[8];

	for(int ii=0; ii<4; ii++)
	{
		iTotal = GetTotalFlexSpace(Drives[ii].num, &err);
		if (iTotal)
		{
			iFree = GetFreeFlexSpace(Drives[ii].num, &err);
			fFree = (float)iFree * 100 / (float)iTotal;
			sz2s(iTotal, szTotal);
			sz2s(iFree,  szFree );
			sprintf(szPFree, "%.1f%%", fFree);

			wsprintf(buff, _tc, Drives[ii].name);
			ConstructEditControl(&ec, ECT_HEADER,ECF_APPEND_EOL, buff, 64);
			prep_hd(&ec);
			AddEditControlToEditQend(eq,&ec,ma);

			wsprintf(buff, "%t/%t\n%t" , szFree, szTotal, szPFree);
			ConstructEditControl(&ec, ECT_READ_ONLY,ECF_APPEND_EOL, buff, 64);
			ec.ed_options.bitmask = 2;
			ec.ed_options.font = 1;
			AddEditControlToEditQend(eq,&ec,ma);
		} 
	}
	CreateInputTextDialog(&disk_prop_desc,&disk_prop_hdr,eq,1,0);

	FreeWS(buff);
}
