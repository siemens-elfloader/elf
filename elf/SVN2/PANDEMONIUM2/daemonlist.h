#ifndef __DL
#define __DL

#include "include.h" 

#define MODE_ENABLED_NEW  1
#define MODE_ENABLED_OLD  2
#define MODE_UPDATEABLE   4

typedef struct
{
  char name[128];
  unsigned short mode;
  int size;
}TDaemon;

class TDaemonList
{
private:
  char daemon_path[128];
  void qsort_daemons(TDaemon *,int);
public:
  int count;
  int total_size;  
  
  int reboot_required;
  
  TDaemon * daemons;
  int enabled_size();
  
  TDaemonList();
  ~TDaemonList();
  
  void Load();  
  void Save(int update);
};


#endif
