//(c)Dimadze
//ext_work.h - Библиотека ф-ий для работы с фаилами карт SuDoKu 
//SMF - Sudoku Map File


typedef struct {  // Заголовок фаила карты SuDoKu
  char id[6];     // ID, т.е. "SUDOKU"
  char sversion;  // Cтаршая версия 
  char mversion;  // Младшая версия
  char level;     // Уровень сложности
}EXTHDR;

//Эти 2 структуры сделаны, чтобы не забыть структуры фаилов, практически не юзаются
typedef struct {      // Тело фаила карты SuDoKu версии 1.0       
  short unk_l_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char *name;         // Имя карты
  short unk_n_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad1[18];     // Ряд 9 цифр по 2 байта
  short unk_1_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad2[18];     // Ряд 9 цифр по 2 байта
  short unk_2_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad3[18];     // Ряд 9 цифр по 2 байта
  short unk_3_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad4[18];     // Ряд 9 цифр по 2 байта
  short unk_4_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad5[18];     // Ряд 9 цифр по 2 байта
  short unk_5_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad6[18];     // Ряд 9 цифр по 2 байта
  short unk_6_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad7[18];     // Ряд 9 цифр по 2 байта
  short unk_7_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad8[18];     // Ряд 9 цифр по 2 байта
  short unk_8_0x0D0A; // Перенос в "Блокноте" 0x0D0A
  char ryad9[18];     // Ряд 9 цифр по 2 байта
}EXTBODY_V10;

typedef struct {      // Тело фаила карты SuDoKu версии 2.0
  char *name;         // Имя карты
  char zero;          // Конец имени карты
  char body[9*9];     // Карта ячеек, одна ячейка - 1 байт: закрытые (0x01 - 0x09), открытые (0x21-0x29)
}EXTBODY_V20;


char extmapv10_2_cell(char c1,char c2) // Из двух байт (0x30-0x39) лепит один char, для фаилов SuDoKu 1.0 
 {
   int result;
   if (c1 == '0') for (int i=0x31;i<0x3A;i=i+0x01) if (c2 == i) result=i-0x30;
   if (c1 == '1') for (int i=0x31;i<0x3A;i=i+0x01) if (c2 == i) result=i-0x20;
   if (c1 == '2') for (int i=0x31;i<0x3A;i=i+0x01) if (c2 == i) result=i-0x10;
   return result;
}

SUDOKUMAP *gcell_2_rcell(SUDOKUMAP *sdm) // Конвертирует игровые ячеёки, должны быть верными, в проверочные. 
{
 for (int i=0;i<9;i++) for (int j=0;j<9;j++)
  {
    if (sdm->gcell[i][j]>=0x21 && sdm->gcell[i][j]<0x30) sdm->rcell[i][j] = (sdm->gcell[i][j]) - 0x20;
    if (sdm->gcell[i][j]>=0x11 && sdm->gcell[i][j]<0x20) sdm->rcell[i][j] = (sdm->gcell[i][j]) - 0x10;
    if (sdm->gcell[i][j]>=0x01 && sdm->gcell[i][j]<0x10) sdm->rcell[i][j] = (sdm->gcell[i][j]);
  }
 return sdm;
}

SUDOKUMAP *CreateSUDOKUMAPbyEXTFILE(char *path) // Создаёт SUDOKUMAP из фаила SuDoKu 1.0 и 2.0 версий
{
 FSTATS stat;
 SUDOKUMAP *sdm=malloc(sizeof(SUDOKUMAP));
 EXTHDR *exth=malloc(sizeof(EXTHDR));
 if (GetFileStats(path, &stat, 0)!=-1 && stat.size)
  {
    int ext=fopen(path,A_ReadOnly+A_BIN,P_READ,0);
    
    fread(ext,(void *)&exth->id[0], 1,0);
    fread(ext,(void *)&exth->id[1], 1,0);
    fread(ext,(void *)&exth->id[2], 1,0);
    fread(ext,(void *)&exth->id[3], 1,0);
    fread(ext,(void *)&exth->id[4], 1,0);
    fread(ext,(void *)&exth->id[5], 1,0);
    
    fread(ext,(void *)&exth->sversion, 1,0);
    fread(ext,(void *)&exth->mversion, 1,0);
    fread(ext,(void *)&exth->level, 1,0);
    
    sdm->warn = 0x00;
    if (exth->level != 'L' && exth->level != 'M' && exth->level != 'H') sdm->warn = sdm->warn + 0x01;
    
    sdm->preview = 0x00;
    sdm->x = 4; sdm->y = 4; 
    if (exth->id[0]=='S' && exth->id[1]=='U' && exth->id[2]=='D' && exth->id[3]=='O' && exth->id[4]=='K' && exth->id[5]=='U')
     {  
      switch ((exth->sversion-0x30)*10+(exth->mversion-0x30))
      {
       case 10:
        {
         int k=0;
         char *temp=malloc(stat.size-0x0B);
         lseek(ext, 0x0B, S_SET, 0, 0);
         fread(ext,temp, stat.size-0x0B,0);
         for (int i=0;temp[i]!=0x0A;i++) if (i<sizeof(sdm->name)) {sdm->name[i]=temp[i];k=i;}
         sdm->name[k]='\0';
         if (sdm->name[0] == '\0') sdm->warn = sdm->warn + 0x02;
         k=k+2;
         for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->gcell[i][j]=extmapv10_2_cell(temp[k+j*2+(i*18)+(i*2)],temp[k+j*2+(i*18)+(i*2)+1]);
         sdm = gcell_2_rcell(sdm);
         sdm->level=exth->level;
         sdm->sec=0;
         sdm->error = CheckSUDOKUMAP(sdm);
         mfree(temp);
         break;
        }
       case 20:
        {
         int k=0;
         char *temp=malloc(stat.size-9);
         lseek(ext, 0x09, S_SET, 0, 0);
         fread(ext,temp, stat.size-9,0);
         if (temp[0] == '\0') {sdm->warn = sdm->warn + 0x02; sdm->name[0]='\0';k=-1;} else for (int i=0;temp[i]!=0x00;i++) {sdm->name[i]=temp[i];k=i;}
         k=k+2;
         for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->gcell[i][j]=temp[k+j+i*9];
         sdm = gcell_2_rcell(sdm);
         sdm->level=exth->level;
         sdm->sec=0;
         sdm->error = CheckSUDOKUMAP(sdm);
         mfree(temp);
         break;
        }       
       default: sdm->error=0x03;
      }
     } else sdm->error=0x02;
    fclose(ext,0);
  }
 else sdm->error=0x01;
 
 mfree(exth);
 return sdm;
}



char CreateEXTFILEV20bySUDOKUMAP(SUDOKUMAP *sdm, char *path, char del) // Создаёт фаил карт SuDoKu 2.0 из SUDOKUMAP,  del == 1 заменяет фаил. Возвращает 0x00 - ошибка, 0x01 - фаил создан
{
 FSTATS stat;
 if ((GetFileStats(path, &stat, 0)==-1 || del==0x01) && sdm->error==0 && sdm->warn<0x02) // Если есть ошибки в структуре, то хер!
  {
    char temp[sizeof(EXTHDR) + sizeof(EXTBODY_V20) + sizeof(sdm->name)];
    
    if (sdm->warn == 0x01)   sdm->level = 0x3F;
   
    temp[0] = 'S';
    temp[1] = 'U';
    temp[2] = 'D';
    temp[3] = 'O';
    temp[4] = 'K';
    temp[5] = 'U';
    temp[6] = '2';
    temp[7] = '0';
    temp[8] = sdm->level;
    for (int i=0; i<strlen(sdm->name);i++) temp[9+i] = sdm->name[i];
    temp[9+strlen(sdm->name)]=0x00;
    for (int i=0;i<9;i++) for (int j=0;j<9;j++) temp[10 + strlen(sdm->name)+j+i*9] = sdm->gcell[i][j];
    temp[9+strlen(sdm->name)]=0x00;
    
    if (del==0x01) unlink(path,0);
    
    int ext = fopen (path,A_WriteOnly+A_Create+A_BIN,P_WRITE,0);
    fwrite(ext, temp, 6 + 1 + 1 + 1 + strlen(sdm->name) + 1 + 9*9, 0);
    fclose(ext, 0);
    return 0x01;
  }
  else return 0x00;
}


