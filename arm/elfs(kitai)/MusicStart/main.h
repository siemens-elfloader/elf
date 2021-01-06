
#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct
{
  char *p_name;
  int id;
}LIST_SONG_NAME;

void control(int type);
void exit(void);
void start_auto_exit(void);
void stop_auto_exit(void);

#endif

