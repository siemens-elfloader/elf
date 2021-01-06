#include "inc\mc.h"
#include "inc\lng.h"
#include "inc\mui.h"

const char mclg_deffile[]="default.mclg";
const char mclg_ext[]="mclg";

const MUI_STR mui[]={
	{id_no, sz_no},
	{id_yes, sz_yes},

	{id_byte, sz_byte},
	{id_kbyte, sz_kbyte},
	{id_mbyte, sz_mbyte},

	{id_reconfig, sz_reconfig},
	{id_lng, sz_lng},
	{id_lngname, sz_lngname},

	{id_dirmking, sz_dirmking},
	{id_copying, sz_copying},
	{id_moveing, sz_moveing},
	{id_deling, sz_deling},

	{id_mcmenu, sz_mcmenu},
	{id_select, sz_select},
	{id_back, sz_back},

	{id_open, sz_open},
	{id_file_m, sz_file_m},
	{id_chk, sz_chk},
	{id_chkall, sz_chkall},
	{id_invchk, sz_invchk},
	{id_unchall, sz_unchall},
	{id_oper_m, sz_oper_m},
	{id_past, sz_past},
	{id_cancel, sz_cancel},
	{id_copy, sz_copy},
	{id_move, sz_move},
	{id_del, sz_del},
	{id_rename, sz_rename},
	{id_newdir, sz_newdir},
	{id_prop, sz_prop},
	{id_drvinf, sz_drvinf},
	{id_view_m, sz_view_m},
	{id_sort_m, sz_sort_m},
	{id_sortn, sz_sortn},
	{id_sorte, sz_sorte},
	{id_sorts, sz_sorts},
	{id_sortd, sz_sortd},
	{id_sortr, sz_sortr},
	{id_filter, sz_filter},
	{id_refresh, sz_refresh},
	{id_newfile, sz_newfile},
	{id_bm_m, sz_bm_m},
	{id_bm, sz_bm},
	{id_add, sz_add},
	{id_bml, sz_bml},
	{id_misc_m, sz_misc_m},
	{id_settings, sz_settings},
	{id_about_m, sz_about_m},
	{id_exit, sz_exit},

	{id_name, sz_name},
	{id_fullname, sz_fullname},
	{id_size, sz_size},
	{id_global, sz_global},
	{id_folders, sz_folders},
	{id_files, sz_files},
	{id_date, sz_date},
	{id_attr, sz_attr},
	{id_readonly, sz_readonly},
	{id_hidden, sz_hidden},
	{id_system, sz_system},
	{id_arh, sz_arh},
	{id_subdirs, sz_subdirs},
	{id_ncsize, sz_ncsize},
	{id_csize, sz_csize},
	{id_cglobal, sz_cglobal},

	{id_pmt_del, sz_pmt_del},
	{id_pmt_copy, sz_pmt_copy},
	{id_pmt_move, sz_pmt_move},
	{id_pmt_stop, sz_pmt_stop},
	{id_pmt_cancel, sz_pmt_cancel},
	{id_pmt_exists, sz_pmt_exists},
	{id_pmt_exit, sz_pmt_exit},
	{id_pmt_impcs, sz_pmt_impcs},
	{id_pmt_implg, sz_pmt_implg},
	{id_pmt_rodel, sz_pmt_rodel},

	{id_err_attrset, sz_err_attrset},
	{id_err_makedir, sz_err_makedir},
	{id_err_rename, sz_err_rename},
	{id_err_delete, sz_err_delete},
	{id_err_badname_t, sz_err_badname_t},
	{id_err_baddrv_t, sz_err_baddrv_t},
	{id_err_resnok, sz_err_resnok},
	{id_err_nofiles, sz_err_nofiles},
	{id_err_badname, sz_err_badname},
	{id_err_badkey, sz_err_badkey},
	{id_err_badformat, sz_err_badformat},
	{id_err_nomemory, sz_err_nomemory},
	{id_err_makefile, sz_err_makefile},
	{id_err_ziperr, sz_err_ziperr},

	{id_msg_zreading, sz_msg_zreading},
	{id_msg_showhid_files, sz_msg_showhid_files},
	{id_msg_showsys_files, sz_msg_showsys_files},
	{id_msg_showhidsys_files, sz_msg_showhidsys_files},
	{id_msg_showhid_drv, sz_msg_showhid_drv},
};
#define MUI_COUNT		 (sizeof(mui)/sizeof(MUI_STR))
char* mui_ld[MUI_COUNT];

int getmuiind(int id)
{
	for(int cc=0; cc < MUI_COUNT; cc++)
		if (mui[cc].id == id) return cc;
	return -1;  
}

char* muitxt(int ind)
{
	if (ind < 0 || ind >= MUI_COUNT) return NULL;
	return mui_ld[ind] ? mui_ld[ind] : mui[ind].df_str;
}
/*
char* muistr(int id)
{
int ind = getmuiind(id);
if (ind<0)return NULL;
return mui_ld[ind]?mui_ld[ind]:mui[ind].df_str;
}
*/
void SaveMUI(char* filename)
{
	char* fn = filename?filename:MCFilePath(mclg_deffile);

	int f;
	if (fn && (f=fopen(fn,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1)
	{
		MCLG_hdr hdr;
		hdr.sig=mclg_sig;
		hdr.ver=mclg_ver;
		//	hdr.size=mclg_size;
		hdr.offset=mclg_offset;

		int bufsz=0;
		for(int cc=0;cc<MUI_COUNT;cc++)
			bufsz+=strlen(muitxt(cc))+1;
		char* buff;
		char* lp;
		lp=buff=malloc(bufsz);

		hdr.size=mclg_size | (bufsz<<16);

		MC_LG* lgtbl;
		MC_LG* lg;
		lg=lgtbl=malloc(MUI_COUNT*sizeof(MC_LG));
		for(int cc=0;cc<MUI_COUNT;cc++)
		{
			lg->id=mui[cc].id;
			lg->ofs=(int)lp-(int)buff;
			strcpy(lp, muitxt(cc));
			lp+=strlen(muitxt(cc))+1;
			lg=(MC_LG*)((int)lg+sizeof(MC_LG));
		} 

		fwrite(f,&hdr,sizeof(hdr),&err);
		fwrite(f,lgtbl,MUI_COUNT*sizeof(MC_LG),&err);
		fwrite(f,buff,bufsz,&err);
		mfree(lgtbl);
		mfree(buff);
		fclose(f,&err);
	}
}

#ifdef DUMP_MUI
void SaveMUI2(char* filename)
{
	char* fn = filename?filename:MCFilePath(mclg_deffile);

	int f;
	if (fn && (f=fopen(fn,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1)
	{
		char* buf = malloc(256);
		if (buf)
		{
			for(int cc=0;cc<MUI_COUNT;cc++) 
			{
				strncpy(buf, mui_ld[cc]?mui_ld[cc]:mui[cc].df_str,255);
				for(int ii=0;buf[ii];ii++)
					if (buf[ii]=='\n')buf[ii]='^';

				sprintf(pathbuf, "%.4d=%s\n", mui[cc].id, buf);
				fwrite(f,pathbuf,strlen(pathbuf),&err);
			}
			mfree(buf);
		} 
		fclose(f,&err);
	}
}
#endif

char* muibuff;
int muibuffsz;

int LoadMUI(char* filename)
{
	int res = 0;
	int v1=0;
	char* fn = filename?filename:MCFilePath(mclg_deffile);

	int f;
	if (fn && (f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
	{
		MCLG_hdr hdr;
		if (fread(f, &hdr, sizeof(hdr), &err)==sizeof(hdr))
		{
			if (hdr.sig==mclg_sig)
			{
				lseek(f,hdr.offset,S_SET,&err,&err);
				int tblcn=(hdr.size & 0xffff);
				int tblsz=tblcn*sizeof(MC_LG);
				int bufsz=hdr.size>>16;
				FreeMUI();
				muibuff=malloc(bufsz);
				muibuffsz=bufsz;
				MC_LG* tbl;
				MC_LG* lg;
				lg=tbl=malloc(tblsz);
				res = 
					(fread(f, tbl, tblsz, &err)==tblsz) &&
					(fread(f, muibuff, bufsz, &err)==bufsz);
				if (res)
				{
					LockSched();
					for(int cc=0;cc<tblcn;cc++)
					{
						int ind=getmuiind(lg->id);
						mui_ld[ind]=(char*)((int)muibuff + lg->ofs);
						lg=(MC_LG*)((int)lg+sizeof(MC_LG));
					} 
					UnlockSched();
				}
				else
					mfree(muibuff);
				mfree(tbl);
			}
			else v1=1;
		}
		fclose(f, &err);
	}
	int LoadMUIold(char* fname);
	if (v1)res=LoadMUIold(filename);
	else InitMUI();
	return res;
}

void freeb(char* buf)
{
	if (buf)
		if ((int)buf<(int)muibuff || (int)buf>=(int)muibuff+muibuffsz)
			mfree(buf);
}

void FreeMUI()
{
	for(int cc=0;cc<MUI_COUNT;cc++)
		if (mui_ld[cc])
		{
			freeb(mui_ld[cc]);
			mui_ld[cc]=NULL;
		}
		if (muibuff) 
		{
			mfree(muibuff);
			muibuff=0;
		} 
}

void MUIProc(char *name, char *value)
{
	int id=strtol(name,0,10);
	int ind=getmuiind(id);
	if (ind<0)return;

	LockSched();
	freeb(mui_ld[ind]);
	char* buf = malloc(strlen(value)+1);
	strcpy(buf, value);
	for(int cc=0;buf[cc];cc++)
		if (buf[cc]=='^')buf[cc]='\n';
	mui_ld[ind] = buf;
	UnlockSched();
}

int LoadMUIold(char* fname)
{
	int l;
	char* fn;
	if (fname)
	{
		l=0;
		fn=fname;
	}
	else
	{
		l=1;
		fn=(char*)&mclg_deffile;
	}
	int res = EnumIni(l, fn, MUIProc);
	InitMUI();
	return res;
}

void InitMUI()
{

	yesno[0] = muitxt(ind_no);
	yesno[1] = muitxt(ind_yes);

	tmenuhdr.lgp_id = (int)muitxt(ind_mcmenu);
	
//#define MENU_ZH
#ifndef MENU_ZH
	int i = 0;

	menu_sk[0].lgp_id = (int)muitxt(ind_select);
	menu_sk[1].lgp_id = (int)muitxt(ind_back);
	
	opt_menuitems[0].lgp_id_small = (int)muitxt(ind_open);
	opt_menuitems[1].lgp_id_small = (int)muitxt(ind_file_m);
	opt_menuitems[2].lgp_id_small = (int)muitxt(ind_oper_m);
	opt_menuitems[3].lgp_id_small = (int)muitxt(ind_prop);
	opt_menuitems[4].lgp_id_small = (int)muitxt(ind_view_m);
	opt_menuitems[5].lgp_id_small = (int)muitxt(ind_misc_m);
	opt_menuitems[6].lgp_id_small = (int)muitxt(ind_exit);
	i = 0;
	//zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_open);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_file_m);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_oper_m);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_prop);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_view_m);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_misc_m);
	zip_opt_menuitems[i++].lgp_id_small = (int)muitxt(ind_exit);

	op_menuitems[0].lgp_id_small = (int)muitxt(ind_past);
	op_menuitems[1].lgp_id_small = (int)muitxt(ind_cancel);
	op_menuitems[2].lgp_id_small = (int)muitxt(ind_copy);
	op_menuitems[3].lgp_id_small = (int)muitxt(ind_move);
	op_menuitems[4].lgp_id_small = (int)muitxt(ind_del);
	op_menuitems[5].lgp_id_small = (int)muitxt(ind_rename);
	op_menuitems[6].lgp_id_small = (int)muitxt(ind_newdir);
	op_menuitems[7].lgp_id_small = (int)muitxt(ind_newfile);

	i = 0;
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_past);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_cancel);
	zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_copy);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_move);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_del);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_rename);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_newdir);
	//zip_op_menuitems[i++].lgp_id_small = (int)muitxt(ind_newfile);

	mis_menuitems[0].lgp_id_small = (int)muitxt(ind_bm_m);
	mis_menuitems[1].lgp_id_small = (int)muitxt(ind_drvinf);
	mis_menuitems[2].lgp_id_small = (int)muitxt(ind_settings);
	mis_menuitems[3].lgp_id_small = (int)muitxt(ind_about_m);

	fl_menuitems[0].lgp_id_small = (int)muitxt(ind_chk);
	fl_menuitems[1].lgp_id_small = (int)muitxt(ind_chkall);
	fl_menuitems[2].lgp_id_small = (int)muitxt(ind_unchall);
	fl_menuitems[3].lgp_id_small = (int)muitxt(ind_invchk);

	vw_menuitems[0].lgp_id_small = (int)muitxt(ind_sort_m);
	vw_menuitems[1].lgp_id_small = (int)muitxt(ind_filter);
	vw_menuitems[2].lgp_id_small = (int)muitxt(ind_refresh);

	st_menuitems[0].lgp_id_small = (int)muitxt(ind_sortn);
	st_menuitems[1].lgp_id_small = (int)muitxt(ind_sorte);
	st_menuitems[2].lgp_id_small = (int)muitxt(ind_sorts);
	st_menuitems[3].lgp_id_small = (int)muitxt(ind_sortd);
	st_menuitems[4].lgp_id_small = (int)muitxt(ind_sortr);

	bm_menuitems[0].lgp_id_small = (int)muitxt(ind_add);
	bm_menuitems[1].lgp_id_small = (int)muitxt(ind_bml);
#endif
}
