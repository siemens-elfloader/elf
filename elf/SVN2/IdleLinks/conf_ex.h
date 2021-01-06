#ifndef _CONF_EX_H_
  #define _CONF_EX_H_

void FreeBcfgs();
void LoadBcfgs();
int CreatePathToBcfgs();
void OpenBcfgFromMenu(char *linkname);
void CreateNewBcfg(char *linkname);
void RenameBcfg(char *first, char *last);
void DeleteBcfg(char* linkpath);

#endif
