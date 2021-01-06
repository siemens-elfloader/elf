#ifndef _HISTORY_H_
#define _HISTORY_H_

void AddURLToHistory(const char *url);
void CheckHistory(const char *url);
char **GetHistory(int *cnt);

#endif /* _HISTORY_H_ */
