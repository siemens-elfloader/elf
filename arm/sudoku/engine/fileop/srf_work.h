//(c)Dimadze
//srf_work.h - Библиотека ф-ий для работы с srf - фаилами
//Эта структура сделана, чтобы не забыть структуру фаилов srf и она не отражает прямого сходства с ними (только участками памяти отдельных элементов, распределённых в фаиле)
typedef struct {           // Структура srf - Фаила 
  char id[3];              // ID фаила, т.е. "SRF" (SuDoKu Record File)
  char recs;               // Кол-во сохранений
  char timedate[3][16];    // Время и дата 3 рекордов (14:16 17.01.2010)
  char level[3];           // Уровни сложности 3 рекордов
  int  sec[3];             // Секунды проведенных 3 рекордных игр до момента завершения
  int  points[3];          // Игровые очки 3 рекордных игр
}SRF;


char int_2_fourchar_srf(int src, char n) // Разбивает 8-значное число на 4 char'a, например, 12345678 => 12 = 0x0C и 34 = 0x22 и 56 = 0x38 и 78 = 0x4E
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


SUDOKUREC *CreateSUDOKURECbySUDOKUMAP(SUDOKUMAP *sdm) //Создаёт SUDOKUREC из SUDOKUMAP
{
  SUDOKUREC *sdr=malloc(sizeof(SUDOKUREC));
  

}



char CreateSRFFILEbySUDOKUREC(SUDOKUREC *sdr, char *path) // Создаёт srf - Фаил из SUDOKUREC
{
 FSTATS stat;
 if (GetFileStats(path, &stat, 0)==-1 && sdr->error==0) // Если есть ошибки в структуре, то хер!
  {
    char temp[sizeof(SRF)];
    
    temp[0] = 'S';
    temp[1] = 'R';
    temp[2] = 'F';
    temp[3] = sdr->recs;
       
    for (int k=0;k<3;k++) for (int i=0;i<16;i++) temp[4+i+k*16]=sdr->timedate[k][i];
    
    temp[5+3*16]=sdr->level[0];
    temp[6+3*16]=sdr->level[1];
    temp[7+3*16]=sdr->level[2];
    
    for (int k=0;k<3;k++) for (int i=0;i<4;i++)  temp[8+3*16+i+k*4] = int_2_fourchar_srf(sdr->sec[k], i);
    for (int k=0;k<3;k++) for (int i=0;i<4;i++)  temp[9+3*4+3*16+i+k*4] = int_2_fourchar_srf(sdr->points[k], i);

    unlink(path,0);
    
    int ext = fopen (path,A_WriteOnly+A_Create+A_BIN,P_WRITE,0);
    fwrite(ext, temp, 3 + 1 + 3*16 + 1*3 + 4*3 + 4*3, 0);
    fclose(ext, 0);
    return 0x01;
  }
  else return 0x00;
}
