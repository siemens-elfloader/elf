
#ifndef __CORE_EVENT_H__
#define __CORE_EVENT_H__


enum {

    CORE_EVENT_PROCESS = 0x01,
    TIMER_EVENT,
    CSM_EVENT,
    GUI_EVENT
};


typedef struct {
    int id;
    int type;
    void (*dispatcher)(void *);
}CoreEvent;


void processEvents();
void initUsart();


#ifndef printf
extern void print(int, const char *);
#define printf(fmt, ...) { extern char _debug_data[]; extern void printLock(); extern void printUnLock(); \
 printLock(); int __sz__ = sprintf(_debug_data, fmt, ##__VA_ARGS__); print(__sz__, _debug_data); printUnLock(); }
#endif

#ifndef printf_nlock
#define printf_nlock(fmt, ...) { extern char _debug_data[];  \
int __sz__ = sprintf(_debug_data, fmt, ##__VA_ARGS__); print(__sz__, _debug_data); }
#endif

#endif
