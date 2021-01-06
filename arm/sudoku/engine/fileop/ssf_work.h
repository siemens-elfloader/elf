//(c)Dimadze
//ssf_work.h - Библиотека ф-ий для работы с ssf - фаилами
//SSF - Sudoku Save File

//Эта структура сделана, чтобы не забыть структуру фаилов ssf и она не отражает прямого сходства с ними (только участками памяти отдельных элементов, распределённых в фаиле)
typedef struct {      // Структура ssf - Фаила
  char id[3];         // ID фаила, т.е. "SSF" (SuDoKu Save File)
  char preview;       // Кол-во "подсматриваний" до момента сохранения
  char x;             // Координата X курсора
  char y;             // Координата Y курсора
  char hour;          // Час сохранения
  char minute;        // Минута сохранения
  char day;           // День сохранения
  char month;         // Месяц сохранения
  short year;         // Год сохранения
  int sec;            // Секунды проведенной игры до момента сохранения
  char level;         // Уровень сложности
  char *name;         // Имя карты SuDoKu
  char zero;          // Конец имени карты SuDoKu
  char gcell[9*9];    // Карта игровых ячеек (ввиде одного сплошноного массива)
  char rcell[9*9];    // Карта проверочных ячеек (ввиде одного сплошноного массива)
}SSF;
  
typedef struct {      // Некоторые доп. данные из ssf - фаила для некоторых меню
  char name[32];      // Имя SUFOKUMAP
  char time[32];      // Время и Дата сохранения (20.48 16.01.2010)
  char error;         // Ошибки: 0x00 - Без ошибок, 0x01 - Нет фаила!
}SSF_NT;


char int_2_twochar(int src, char n)  // Разбивает 4-значное число на 2 char'a, например, 2010 => 20 = 0x14 и 10 = 0x0A
{
  char srcs[5];
  sprintf(srcs,"%04d",src);
  if (n==0) return ((srcs[0] - 0x30)*10 + (srcs[1] - 0x30));
      else  return ((srcs[2] - 0x30)*10 + (srcs[3] - 0x30));
}

char int_2_fourchar(int src, char n) // Разбивает 8-значное число на 4 char'a, например, 12345678 => 12 = 0x0C и 34 = 0x22 и 56 = 0x38 и 78 = 0x4E
{
  char res = 0;
  char srcs[10];
  sprintf(srcs,"%08d",src);
  if (n==0) res = (srcs[0] - 0x30)*10 + (srcs[1] - 0x30);
  if (n==1) res = (srcs[2] - 0x30)*10 + (srcs[3] - 0x30);
  if (n==2) res = (srcs[4] - 0x30)*10 + (srcs[5] - 0x30);
  if (n==3) res = (srcs[6] - 0x30)*10 + (srcs[7] - 0x30);
  return res;
}


SUDOKUMAP *CreateSUDOKUMAPbySSFFILE(char *path) // Создаёт SUDOKUMAP из ssf - фаила
{
 FSTATS stat;
 SUDOKUMAP *sdm=malloc(sizeof(SUDOKUMAP));
 
 if (GetFileStats(path, &stat, 0)!=-1 && stat.size)
  {
    char id[3], pv, x, y, sec[4];
    int ext=fopen(path,A_ReadOnly+A_BIN,P_READ,0);
    
    fread(ext,(void *)&id[0],  1,0);
    fread(ext,(void *)&id[1],  1,0);
    fread(ext,(void *)&id[2],  1,0);
    fread(ext,(void *)&pv,     1,0);
    fread(ext,(void *)&x,      1,0);
    fread(ext,(void *)&y,      1,0);
    lseek(ext, 0x0C, S_SET,    0,0);
    fread(ext,(void *)&sec[0], 1,0);
    fread(ext,(void *)&sec[1], 1,0);
    fread(ext,(void *)&sec[2], 1,0);
    fread(ext,(void *)&sec[3], 1,0);
    fread(ext,(void *)&sdm->level, 1,0);

    sdm->warn = 0x00;
    if (sdm->level != 'L' && sdm->level != 'M' && sdm->level != 'H') sdm->warn = sdm->warn + 0x01;
    
    if (id[0]=='S' && id[1]=='S' && id[2]=='F')
     {  
       int k=0;
       char *temp=malloc(stat.size - 0x10);
       lseek(ext, 0x11, S_SET, 0, 0);
       fread(ext, temp, stat.size - 0x10,0);
          
       if (temp[0] == '\0') {sdm->warn = sdm->warn + 0x02; sdm->name[0]='\0';k=-1;} else for (int i=0;temp[i]!=0x00;i++) {sdm->name[i]=temp[i];k=i;}
       k=k+2;
       for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->gcell[i][j]=temp[k+j+i*9]; k+=81;
       for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->rcell[i][j]=temp[k+j+i*9];
       
       sdm->error = CheckSUDOKUMAP(sdm);
       for (int i=0;i<9;i++) for (int j=0;j<9;j++) if(sdm->gcell[i][j] > 0x39 || sdm->gcell[i][j] == 0x00 ||
                                                     (sdm->gcell[i][j] > 0x09 && sdm->gcell[i][j] < 0x11) ||
                                                     (sdm->gcell[i][j] > 0x19 && sdm->gcell[i][j] < 0x21) ||
                                                     (sdm->gcell[i][j] > 0x29 && sdm->gcell[i][j] < 0x31)) sdm->error = 0x04;
   
       //  0x10101010
       //  10*1000000 + 10*10000 + 10*100 + 10
       //  10000000 + 100000 + 1000 + 10
       //  10101010
       
       if (pv <= MAXPREVIEW)          sdm->preview = pv; else sdm->error=0x04;
       if (x <= MAXXC && y <= MAXYC) {sdm->x = x; sdm->y = y;} else sdm->error=0x04;
       
       sdm->sec = sec[0]*1000000 + sec[1]*10000 + sec[2]*100 + sec[3];
       mfree(temp);   
     } else sdm->error=0x02;
    
    fclose(ext,0);
  }
 else sdm->error=0x01;
 
 return sdm;
}


char CreateSSFFILEbySUDOKUMAP(SUDOKUMAP *sdm, char *path) // Создаёт ssf - Фаил из SUDOKUMAP. Возвращает 0x00 - ошибка, 0x01 - фаил создан (перезаписан)
{
 if (sdm->error == 0x00) // Если есть ошибки в структуре, то хер!
  {
    char temp[sizeof(SSF) + sizeof(sdm->name)];
    
    if (sdm->warn == 0x01)   sdm->level = 0x3F;
    if (sdm->warn == 0x02)   sdm->name[0] = 0x00;
    if (sdm->warn == 0x03)   {sdm->level = 0x3F; sdm->name[0] = 0x00;}
    
    TDate date; TTime time; 
    GetDateTime(&date,&time);
    
    temp[0]  = 'S';
    temp[1]  = 'S';
    temp[2]  = 'F';
    temp[3]  = sdm->preview;
    temp[4]  = sdm->x;
    temp[5]  = sdm->y;
    temp[6]  = time.hour;
    temp[7]  = time.min;
    temp[8]  = date.day;
    temp[9]  = date.month;
    temp[10] = int_2_twochar(date.year, 0);
    temp[11] = int_2_twochar(date.year, 1);
    temp[12] = int_2_fourchar(sdm->sec, 0);
    temp[13] = int_2_fourchar(sdm->sec, 1);
    temp[14] = int_2_fourchar(sdm->sec, 2);
    temp[15] = int_2_fourchar(sdm->sec, 3);
    temp[16] = sdm->level;
    for (int i=0; i<strlen(sdm->name);i++) temp[17+i] = sdm->name[i];
    temp[17+strlen(sdm->name)]=0x00;

    for (int i=0;i<9;i++) for (int j=0;j<9;j++) temp[18 + strlen(sdm->name)+j+i*9] = sdm->gcell[i][j];
    for (int i=0;i<9;i++) for (int j=0;j<9;j++) temp[18 + 9*9 + strlen(sdm->name)+j+i*9] = sdm->rcell[i][j];
  
    unlink(path,0);
    
    int ext = fopen (path,A_WriteOnly+A_Create+A_BIN,P_WRITE,0);
    fwrite(ext, temp, 3 + 1 + 2 + 1 + 1 + 1 + 1 + 2 + 4 + 1 + strlen(sdm->name) + 1 + 9*9 + 9*9, 0);
    fclose(ext, 0);
    return 0x01;
  }
 else return 0x00;
}

SSF_NT *GetNAMETIMEbySSFFILE(char *path, char *und_text) // Возвращает SSF_NT из ssf - фаила. Осторожно! Ф-ия не проверяет целостность фаила.
{
 FSTATS stat;
 SSF_NT *ssf = malloc(sizeof(SSF_NT));
 if (GetFileStats(path, &stat, 0)!=-1 && stat.size)
  {
    int ext=fopen(path,A_ReadOnly+A_BIN,P_READ,0);
    
    char *temp_time = malloc(32);
    lseek(ext, 0x04, S_SET, 0, 0);
    fread(ext, temp_time, 6,0);
    sprintf(ssf->time, "%02d:%02d %02d.%02d.%04d", temp_time[0], temp_time[1],
                                                   temp_time[2], temp_time[3],
                                                   temp_time[4]*100+temp_time[5]);
    mfree(temp_time);
    
    char *temp_name = malloc(stat.size - 14);
    lseek(ext, 15, S_SET, 0, 0);
    int k=0;
    fread(ext, temp_name, stat.size - 14,0);
    for (int i=0;temp_name[i]!=0x00;i++) { k=i; ssf->name[i]=temp_name[i]; }
    ssf->name[k+1] = 0x00;
    if (k == 0) sprintf(ssf->name, und_text);
    fclose(ext, 0);
    mfree(temp_name);
    ssf->error = 0;
  } else ssf->error = 0x01;
 return ssf;
}


void Create(char *path, char *path2)
{

    char *temp=malloc(1024);
    
    sprintf(temp,"%s %s", GetNAMETIMEbySSFFILE(path2, "XEP")->time, GetNAMETIMEbySSFFILE(path2, "XEP")->name);
  
    unlink(path,0);
    
    int ext = fopen (path,A_WriteOnly+A_Create+A_BIN,P_WRITE,0);
    fwrite(ext, temp,  strlen(temp), 0);
    fclose(ext, 0);


}




void MemFreeOfSSF_NT(SSF_NT *ssf) // Очистка памяти от SSF_NT
{
 mfree(ssf);
}

