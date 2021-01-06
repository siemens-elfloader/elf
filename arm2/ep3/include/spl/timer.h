

#ifndef __TIMER_H__
#define __TIMER_H__

#include "coreevent.h"




int timerStart(unsigned long time, void (*callback)(int, void *), void *userdata);
int timerPause(int timer);
int timerResume(int timer);
int timerStop(int timer);

#endif
