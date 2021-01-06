//Процесс "HIGH_PROC" наивысшего приоритета
#include "..\..\inc\swilib.h"


#define HPROC_ID   0x4409
#define HPROC_NAME "HIGH_PROC"
#define HPROC_PRIO 0x00

#define HPROC_MSG   0x0001 // HIGHPROC
#define HPROC_KILL  0x0002 // Kill HIGHPROC


//Создание GBS Процесса "HIGH_PROC"
void Create_HPROC();
//Уничтожение GBS Процесса "HIGH_PROC"
void Kill_HPROC();
//Уничтожение GBS Процесса "HIGH_PROC"
void Kill_HPROC_MSG(void *killproc);
//Вызов ф-ии в процессе с повышенным приоритетом
void HIGHPROC(void *f,  void *p1, int p2);



