
void ElfFolderOperations(char *elfpath)
{
 
 //��������� ����� ���������
 int elfn = strlen(elfpath)-strlen((strrchr(elfpath,(int)'\\')+1));
 for (int i=0;i<=256;i++) elffolder[i]=elfpath[i];
 elffolder[elfn]='\0';
 
 sprintf(imgfolder,"%s%dx%d\\",elffolder, SCRW,SCRH);
 sprintf(cfgfolder,"%s%s",elffolder,"cfg\\");
 sprintf(smffolder,"%s%s",elffolder,"smf\\");
 
 //�������� ��� �������� ���������
 if (isdir(imgfolder, 0)!=1) mkdir(imgfolder, 0);
 if (isdir(cfgfolder, 0)!=1) mkdir(cfgfolder, 0);
 if (isdir(smffolder, 0)!=1) mkdir(smffolder, 0);
 
 //��������� ����� �������������� ������
 
 //�����
 for (int i = 0; i<10;i++) sprintf(dig[i],"%s%d.png", imgfolder, i);
 for (int i = 10;i<19;i++) sprintf(dig[i],"%s%ds.png",imgfolder, i -  9);
 for (int i = 19;i<28;i++) sprintf(dig[i],"%s%da.png",imgfolder, i - 18);
 
 sprintf(sudoku,"%ssudoku.png",imgfolder);
 sprintf(bgm,"%sbgm.png",imgfolder);
 sprintf(bgg,"%sbgg.png",imgfolder);
 
 //SSF - �����
 for (int i = 0; i<5;i++) sprintf(ssffile[i],"%ssudoku_%02d.ssf", cfgfolder,i+1);
 
 //HLP - ����
 sprintf(hlpfile,"%ssudoku.hlp",cfgfolder);
 
 //���� - �������� ������ ���� SuDoKu
 sprintf(seditor,"%ssmfeditor.elf",elffolder);
 
 //BCFG - ����
 sprintf(cfgfile,"%ssudoku.bcfg",cfgfolder);
 
}

ERRORSTRUCT *ElfFolderCheckFiles(SUDOKUMAP *sdm, char *filepath)
{
 FSTATS stat;
 ERRORSTRUCT *errs=malloc(sizeof(ERRORSTRUCT));
 
 //�������� ������� 0.png - 9.png � 1s.png - 9s.png � 1a.png - 9a.png
 errs->png_file = 0;
 for (int i=0;i<28;i++) if (GetFileStats(dig[i], &stat, 0)==-1 && stat.size) errs->png_file++;

 //�������� ������� sudoku.png (���� ������ ������ ������ 130), bgm.png, bgg.png
 if (GetFileStats(sudoku, &stat, 0)==-1 && stat.size && SCRH > SCRHM) errs->png_file++;
 if (GetFileStats(bgm, &stat, 0)==-1 && stat.size)    errs->png_file++;
 if (GetFileStats(bgg, &stat, 0)==-1 && stat.size)    errs->png_file++;
 
 //�������� ������� sudoku.hlp � smfeditor.elf
 errs->hlp_file   = 0;
 errs->sedit_file = 0;
 if (GetFileStats(hlpfile, &stat, 0)==-1 && stat.size) errs->hlp_file   = 1;
 if (GetFileStats(seditor, &stat, 0)==-1 && stat.size) errs->sedit_file = 1;
 
 //�������� ����� ����
 if (filepath[1]==':') errs->ext_file = sdm->error; else errs->ext_file = 0x64; 
 
 //���� ���� ������, �� �������� ��������� ������ � �������
 if (errs->png_file > 0)
  {
   char path[256];
   sprintf(path,"%spng_help.txt",elffolder);
   fileext(path, png_help_txt, 1246);
  }
 
  if (errs->hlp_file == 1 || errs->sedit_file == 1)
  {
   char path[256];
   sprintf(path,"%setc_help.txt",elffolder);
   fileext(path, etc_help_txt, 228);
  }
 
 return errs;
}
 
