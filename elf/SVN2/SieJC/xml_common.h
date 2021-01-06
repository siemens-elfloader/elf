#ifndef _XML_COMMON_
#define _XML_COMMON_

typedef struct{
  void *next;
  char *name;
  char *param;
}XMLAttr;


typedef struct{
  void *next;
  void *subnode;
  char *name;
  XMLAttr *attr;
  char *value;
} XMLNode;

#endif
