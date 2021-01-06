#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct
{
  char *p_name;
  int id;
}LIST_SONG_NAME;

void start_auto_exit(void);
void stop_auto_exit(void);
void Control(int type);
void Exit(void);

#endif

