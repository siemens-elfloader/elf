#ifndef _URLSTACK_H_
#define _URLSTACK_H_

#define PageSTACK_SIZE (32)

char *PushPageToStack(void);
char *PopPageFromStack(void);
char *ForwardPageFromStack(void);
void FreePageStack(void);
void UpPageStack(void);

#endif /* _URLSTACK_H_ */
