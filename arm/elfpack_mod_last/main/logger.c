#include "..\..\inc\swilib.h"

extern int get_file_size(const char * fname);
extern unsigned int DEFAULT_DISK_N;

#define LOGPATH "X:\\Zbin\\etc\\ep_log.log"
#define LOGSIZE 50

#define PLAYTONE(A) PlaySound(1,0, 0, A, 0)


__arm void logger(char *log_string, void *address)
{
  TDate date; TTime time;
  
  char log_path[128] = LOGPATH;
  log_path[0] = DEFAULT_DISK_N + '0';
  
  if (get_file_size(log_path) > LOGSIZE*1024) unlink(log_path, 0);
  
  int log = fopen(log_path,A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  
  char *log_data=malloc(1024);
  short cepid = GBS_GetCurCepid();
  GetDateTime(&date,&time);
  
  
  sprintf(log_data,"[%02d:%02d:%02d %02d-%02d-%04d], CepID: 0x%04X, Addr: 0x%08X Str: \"%s\"\r\n",
                     time.hour, time.min, time.sec, date.day, date.month, date.year, cepid, (unsigned int)address, log_string);

  lseek(log, 0x0, S_END, 0, 0);
  fwrite(log, log_data, strlen(log_data), 0);
 
  zeromem(log_data, 1024);
  mfree(log_data);
  fclose(log, 0);
  
  extern int log_sound;
  if (log_sound == 1) PLAYTONE(1);
}
