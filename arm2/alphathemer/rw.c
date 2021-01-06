

char k;

struct{
	unsigned int sz;
	char *buf;
}ci;

struct{
	unsigned short w, h, bpn;
	char *buf;
}Dc;

int cps;

void dodat()
{
	state=W_WRT;
	IMGHDR* tmpimg;
	IMGHDR* C_IMG;
	char datnm[256], temp;
	int f, /* cps, */ tsz;
	unsigned int ul, lenfl, tc[2];
	unsigned short tcc[2];
	for(k=0; k<ccnt; k++)
	{
	 if(c[k].a)
	 {
		REDRAW();
		lenfl=strlen(c[k].fl);
	  if(((c[k].fl[lenfl-3]=='P')||(c[k].fl[lenfl-3]=='p'))&&
		((c[k].fl[lenfl-2]=='N')||(c[k].fl[lenfl-2]=='n'))&&
		((c[k].fl[lenfl-1]=='G')||(c[k].fl[lenfl-1]=='g')))
	  {
		tmpimg=CreateIMGHDRFromPngFile(c[k].fl, 0);
		zeromem(datnm, 256);
		if(c_dir[strlen(c_dir)-1]=='\\') sprintf(datnm, "%s%s.dat", c_dir, c[k].nm);
		else sprintf(datnm, "%s\\%s.dat", c_dir, c[k].nm);
		if ((f=fopen(datnm,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	    {
			#ifdef ELKA
				fwrite(f,&tmpimg->w,2,&ul);
				fwrite(f,&tmpimg->h,2,&ul);
			#else
				fwrite(f,&tmpimg->w,1,&ul);
				fwrite(f,&tmpimg->h,1,&ul);
			#endif
			if(!compr)
			{
				fwrite(f,&tmpimg->bpnum,1,&ul);
				fwrite(f,tmpimg->bitmap,tmpimg->w*tmpimg->h*4,&ul);

				C_IMG=GetIMGHDRFromThemeCache( c[k].nom );
				char* oldbitmap=C_IMG->bitmap;
				memcpy(C_IMG,tmpimg,sizeof(IMGHDR));
				tmpimg->bitmap=oldbitmap;
			}
			else
			{
				ci.sz=0;
				cps=0;//tmpimg->h*tmpimg->w;
				ci.buf=malloc(tmpimg->h*tmpimg->w*4);
				zeromem(ci.buf, tmpimg->h*tmpimg->w*4);
				while(cps<tmpimg->h*tmpimg->w)
				{
					tsz=0;
					memcpy(&tc[0], tmpimg->bitmap+cps*4, 4);
					memcpy(&tc[1], tmpimg->bitmap+cps*4+4, 4);
					if((tc[0]==tc[1]))
					{
						do
						{
							tsz++;
							memcpy(&tc[0], tmpimg->bitmap+(tsz+cps)*4, 4);
							memcpy(&tc[1], tmpimg->bitmap+(tsz+cps)*4+4, 4);
						}while((tc[0]==tc[1]) && (tsz<127) && ((tsz+cps)<tmpimg->h*tmpimg->w));
						//tsz--;
						ci.buf[ci.sz]=tsz;
						memcpy(ci.buf+ci.sz+1, tmpimg->bitmap+cps*4, 4);
						ci.sz+=5;
					}
					else
					{
						do
						{
							tsz++;
							memcpy(&tc[0], tmpimg->bitmap+(tsz+cps)*4, 4);
							memcpy(&tc[1], tmpimg->bitmap+(tsz+cps)*4+4, 4);
						}while((tc[0]!=tc[1]) && (tsz<127) && ((tsz+cps)<tmpimg->h*tmpimg->w));
						//tsz--;
						ci.buf[ci.sz]=0x100-tsz;
						memcpy(ci.buf+ci.sz+1, tmpimg->bitmap+cps*4, tsz*4);
						ci.sz+=tsz*4+1;
					}
					cps+=tsz;
				}
				temp=tmpimg->bpnum+0x80;
				fwrite(f,&temp,1,&ul);
				fwrite(f,ci.buf,ci.sz,&ul);

				C_IMG=GetIMGHDRFromThemeCache( c[k].nom );
				char* oldbitmap=C_IMG->bitmap;
				C_IMG->h=tmpimg->h;
				C_IMG->w=tmpimg->w;
				C_IMG->bpnum=tmpimg->bpnum+0x80;
				C_IMG->bitmap=malloc(ci.sz);
				memcpy(C_IMG->bitmap, ci.buf ,ci.sz);
				mfree(oldbitmap);
//				memcpy(C_IMG,tmpimg,sizeof(IMGHDR));
//				tmpimg->bitmap=oldbitmap;

				mfree(ci.buf);
			}
			fclose(f,&ul);
		}

		mfree(tmpimg->bitmap);
		mfree(tmpimg);
	  }
	 }
	 else
		if(compr)
		{
			REDRAW();
			zeromem(datnm, 256);
			if(c_dir[strlen(c_dir)-1]=='\\') sprintf(datnm, "%s%s.dat", c_dir, c[k].nm);
			else sprintf(datnm, "%s\\%s.dat", c_dir, c[k].nm);
			if ((f=fopen(datnm,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
		    {
				#ifdef ELKA
					fread(f,&Dc.w,2,&ul);
					fread(f,&Dc.h,2,&ul);
				#else
					fread(f,&Dc.w,1,&ul);
					fread(f,&Dc.h,1,&ul);
				#endif
					fread(f,&Dc.bpn,1,&ul);
					Dc.buf=malloc(Dc.h*Dc.w*2);
					zeromem(Dc.buf, Dc.h*Dc.w*2);
					fread(f,Dc.buf,Dc.w*Dc.h*2,&ul);
				if(Dc.bpn==8)
				{
					fclose(f,&ul);
					f=fopen(datnm,A_WriteOnly+A_Create+A_Truncate,P_WRITE,&ul);
					ci.sz=0;
					cps=0;//tmpimg->h*tmpimg->w;
					ci.buf=malloc(Dc.h*Dc.w*2);
					while(cps<Dc.h*Dc.w)
					{
						tsz=0;
						memcpy(&tcc[0], Dc.buf+cps*2, 2);
						memcpy(&tcc[1], Dc.buf+cps*2+2, 2);
						if((tcc[0]==tcc[1]))
						{
							do
							{
								tsz++;
								memcpy(&tcc[0], Dc.buf+(tsz+cps)*2, 2);
								memcpy(&tcc[1], Dc.buf+(tsz+cps)*2+2, 2);
							}while((tcc[0]==tcc[1]) && (tsz<127) && ((tsz+cps)<Dc.h*Dc.w));
							//tsz--;
							ci.buf[ci.sz]=tsz;
							memcpy(ci.buf+ci.sz+1, Dc.buf+cps*2, 2);
							ci.sz+=3;
						}
						else
						{
							do
							{
								tsz++;
								memcpy(&tcc[0], Dc.buf+(tsz+cps)*2, 2);
								memcpy(&tcc[1], Dc.buf+(tsz+cps)*2+2, 2);
							}while((tcc[0]!=tcc[1]) && (tsz<127) && ((tsz+cps)<Dc.h*Dc.w));
							//tsz--;
							ci.buf[ci.sz]=0x100-tsz;
							memcpy(ci.buf+ci.sz+1, Dc.buf+cps*2, tsz*2);
							ci.sz+=tsz*2+1;
						}
						cps+=tsz;
					}
				#ifdef ELKA
					fwrite(f,&Dc.w,2,&ul);
					fwrite(f,&Dc.h,2,&ul);
				#else
					fwrite(f,&Dc.w,1,&ul);
					fwrite(f,&Dc.h,1,&ul);
				#endif
					temp=Dc.bpn+0x80;
					fwrite(f,&temp,1,&ul);
					fwrite(f,ci.buf,ci.sz,&ul);

				C_IMG=GetIMGHDRFromThemeCache( c[k].nom );
				char* oldbitmap=C_IMG->bitmap;
				C_IMG->h=Dc.h;
				C_IMG->w=Dc.w;
				C_IMG->bpnum=Dc.bpn+0x80;
				C_IMG->bitmap=malloc(ci.sz);
				memcpy(C_IMG->bitmap, ci.buf ,ci.sz);
				mfree(oldbitmap);
//				memcpy(C_IMG,tmpimg,sizeof(IMGHDR));
//				tmpimg->bitmap=oldbitmap;

					mfree(ci.buf);
					mfree(Dc.buf);
				}
				fclose(f,&ul);
			}
		}
	}
	state=W_FIN;
	REDRAW();
}


int check24()
{
	IMGHDR *tmpimg;
	int s=OTH_ERR;
	unsigned int lenfl;
	for(k=0; k<ccnt; k++)
	{
		lenfl=strlen(c[k].fl);
	  if(((c[k].fl[lenfl-3]=='P')||(c[k].fl[lenfl-3]=='p'))&&
		((c[k].fl[lenfl-2]=='N')||(c[k].fl[lenfl-2]=='n'))&&
		((c[k].fl[lenfl-1]=='G')||(c[k].fl[lenfl-1]=='g')))
	  {
		tmpimg=CreateIMGHDRFromPngFile(c[k].fl, 0);
		if(tmpimg->bpnum==10) s=_OK;
		else s=NOT_24;
		mfree(tmpimg->bitmap);
		mfree(tmpimg);
	  }
	}
	return s;
}

int CheckText(char *text1, char *text2)
{
	if(strlen(text1)==strlen(text2))
	{
		for(int i=0; i<strlen(text2); i++) if(text2[i]!=text1[i]) return 0;
		return 1;
	}
	else return 0;
}

void initdatc()
{
	state=W_INIT;
	int f;
	unsigned int ul, pdsz, i, j, prov=0;
	char *pdbuf, fail=0, tmp[64];
	k=0;
	if ((f=fopen(PROF_PD,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		pdsz=lseek(f, 0, S_END, &ul, &ul);
		pdbuf=malloc(pdsz);
		lseek(f, 0, S_SET, &ul, &ul);
		fread(f,pdbuf,pdsz,&ul);
		fclose(f,&ul);

		while((k<ccnt)&&(!fail))
		{
			if(strlen(c[k].fl)) mfree(c[k].fl);

			i=0;
			prov=0;
			zeromem(tmp, 64);
			while(i<pdsz)
			{
			  if(i>=pdsz-strlen(c[k].pdnm))
			  {
				fail=1;
				i=pdsz;
			  }
			  else
			  {
				memcpy(tmp, pdbuf+i, strlen(c[k].pdnm));
				if(CheckText(tmp, c[k].pdnm))
				{
					i+=strlen(c[k].pdnm)+3;
					j=0;
					while((pdbuf[i+j]!=0x0D)/* &&(pdbuf[i+j+1]!=0x0A) */){ j++;}
					c[k].fl=malloc(j+1);
					zeromem(c[k].fl, j+1);
					memcpy(c[k].fl, pdbuf+i, j);
					prov=1;
					i=pdsz;
				}
				else i++;
			  }
			}
			REDRAW();
			if(!prov) fail=1;
			else k++;

		}
		//if(!fail) dodat();
		mfree(pdbuf);
		state=check24();
	}
	else
	{
		state=W_FAIL;
	}
	k=0;
	REDRAW();
}

