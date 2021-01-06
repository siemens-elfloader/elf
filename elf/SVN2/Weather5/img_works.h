#include "..\inc\pnglist.h"

typedef struct
{
  DYNPNGICONLIST dpl;
  char *fname;
  int uni_n;
}DYNPNGILIST_MY;

int AddPicIfNotExist(DYNPNGILIST_MY **top, char *fname);

