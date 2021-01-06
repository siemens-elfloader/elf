#ifndef _GET_CONFIG_H_
#define _GET_CONFIG_H_

#include "master.h"


extern PTC_CONFIG * volatile ptcfgtop;

int readConfig(int type, char *tp);
void fuckThemAll(void);
PTC_CONFIG *getPatchConfigItem(int n);
int getAllPatchData(void);
int getMaxCBoxItem(DATA_CBOX *cbox);
CBOX_ITEM *getInitCBoxItem(DATA_CBOX *cbox, int *cur);
CBOX_ITEM *getCurCBoxItem(DATA_CBOX *cbox, int cur);
void reloadThisPatch(PTC_CONFIG *ptcfg);
void setPatchOnOff(PTC_CONFIG *ptcfg, int n);
int getPatchOnOff(PTC_CONFIG *ptcfg, int n);
int isPatchExistedByID(char *patchID);
#endif


