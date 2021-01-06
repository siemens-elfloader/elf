
#include "main.h"

SieGetDaemon *daemon;

int main(char *exename, char *fname){
  daemon = new SieGetDaemon();
  daemon->Create();
  return 0;
}
