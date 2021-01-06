#include "..\inc\swilib.h"
#include "decode_xml.h"

#pragma inline
int IsSpace (int c){
	return	c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

#pragma inline
int IsLit (int c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

#pragma inline
int IsNum (int c){
	return (c >= '0' && c <= '9');
}

int IsName (int c){
  return (IsLit(c) || IsNum(c) || c == '_' || c == '-' || c == ':');
}

void FreeAttrQueue(XMLAttr *ta)
{
  while (ta)
  {
    XMLAttr *p=ta->next;
    mfree(ta->name);
    mfree(ta->param);
    mfree(ta);
    ta=p;
  }
}

void DestroyTree(XMLNode *tmpp)
{
  XMLNode * tmpp2;
  while(tmpp)
  {
    FreeAttrQueue(tmpp->attr);
    if (tmpp->subnode)
    {
      DestroyTree(tmpp->subnode);
    }
    tmpp2=tmpp->next;
    mfree(tmpp->name);
    mfree(tmpp->value);
    mfree(tmpp);
    tmpp=tmpp2;
  }
}

void AddTextToNode(XMLNode *node, const char *s, int len)
{
  char *d;
  int l;
  if (node->value)
  {
    d=node->value=realloc(node->value, (l=strlen(node->value))+len+2);
    d[l]=' ';
    strncpy(d+l+1, s, len);
    d[l+len+1]=0;    
  }
  else
  {
    d=node->value=malloc(len+1);
    strncpy(d, s, len);
    d[len]=0;    
  }
}


XMLNode *EndTag(char *name, int name_len, XMLAttr *xattr)
{
  XMLNode *tmp=malloc(sizeof(XMLNode));
  zeromem(tmp,sizeof(XMLNode));
  tmp->name=malloc(name_len+1);
  strncpy(tmp->name, name, name_len);
  tmp->name[name_len]=0;
  tmp->attr=xattr;
  return tmp;
}


XMLAttr *EndAttr(char *name, int name_len, char *value, int value_len)
{
  XMLAttr *xattr=malloc(sizeof(XMLAttr));
  zeromem(xattr,sizeof(XMLAttr));
  xattr->name=malloc(name_len+1);
  strncpy(xattr->name,name,name_len);
  xattr->name[name_len]=0;
  if(value_len>0)
  {
    xattr->param=malloc(value_len+1); 
    strncpy(xattr->param,value, value_len);
    xattr->param[value_len]=0;
  }
  return xattr;
}

XMLNode *XMLDecode(char *buf, int size)
{
  char *TagName;
  int TagLen;
  char *AttrName;
  int AttrNameLen;
  char *AttrValue;
  int AttrValueLen;
  char *Text;
  int TextLen;

  XMLNode *TreeBranchs[128];

  XMLAttr *root_attr=0;
  XMLAttr *bot_attr=0;
  XMLNode *root_node=0;
  XMLNode *bot_node=0;
  
  int is_closed=0;
  int stack_pos=0;
  
  int MSState = MS_BEGIN;
  int TagState = TS_INDEFINITE;

  int i = 0;
  while (i<size)
  {
    int c = buf[i];   
    switch (MSState)
    {
    case MS_BEGIN:
      if (c == '<') {
        MSState = MS_BEGINTAG;
      } else if (!IsSpace (c)) {
        goto L_ERR;
      }
      break;
      
    case MS_BEGINTAG:
      if (IsLit (c)) {
        MSState = MS_TAGNAME;
        TagState = TS_NORMAL;
        TagName = buf+i;
        TagLen=1;
      } else if (IsSpace(c)) {
        MSState = MS_MIDDLETAG;
        TagState = TS_NORMAL;
      } else if (c == '?') {
        MSState = MS_MIDDLETAG;
        TagState = TS_DECLARATION;
      } else if (c == '/') {
        MSState = MS_MIDDLETAG;
        TagState = TS_CLOSE;
      } else if (c == '!') {
        MSState = MS_CHECK_DECL;
      } else {
        goto L_ERR;
      }
      break;
      
    case MS_MIDDLETAG:
      if (IsLit (c)) {
        MSState = MS_TAGNAME;
        TagName = buf+i;
        TagLen=1;
      } else if (!IsSpace (c)) {
        goto L_ERR;
      }
      break;
      
    case MS_TAGNAME:
      if (IsName (c)) {
        TagLen++;
      } else if (IsSpace(c)) {
        MSState = MS_ENDTAGNAME;
      } else if (c == '/') {
        TextLen=0;
        MSState = MS_ENDTAG;
        TagState = TS_EMPTY;
      } else if (c == '>') {
        MSState = MS_TEXT;
        Text=buf+i+1;
        TextLen=0;
        goto L_ADD_TAG;
      } else {
        goto L_ERR;
      }
      break;
      
    case MS_ENDTAGNAME:
      if (IsLit (c)){
        MSState = MS_ATTRIBNAME;
        AttrName=buf+i;
        AttrNameLen=1;
      } else if (c == '/'){
        MSState = MS_ENDTAG;
        TagState = TS_EMPTY;
      } else if (c == '>'){
        MSState = MS_TEXT;
        Text=buf+i+1;
        TextLen=0;
        goto L_ADD_TAG;
      } else if (!IsSpace(c) && (c != '?' && TagState != TS_DECLARATION)) {
        goto L_ERR;
      }
      break;
      
    case MS_ATTRIBNAME:
      if (IsName(c)) {
        AttrNameLen++;
      } else if (c == '=') {
        MSState = MS_ENDEQUALLY;
      } else if (IsSpace(c)) {
        MSState = MS_ENDATTRIBNAME;
      } else {
        goto L_ERR;
      }
      break;
      
    case MS_ENDATTRIBNAME:
      if (c == '=') {
        MSState = MS_ENDEQUALLY;
      } else if (!IsSpace(c)) {
        goto L_ERR;
      }
      break;
      
    case MS_ENDEQUALLY:
      if ((c == '\"')||(c == '\'')) {
        MSState = MS_ATTRIBVALUE;
        AttrValue=buf+i+1;
        AttrValueLen=0;
      } else if (!IsSpace(c)) {
        goto L_ERR;
      }
      break;
      
    case MS_ATTRIBVALUE:
      if ((c == '\"')||(c == '\'')) {
        XMLAttr *xatr=EndAttr(AttrName, AttrNameLen, AttrValue, AttrValueLen);
        MSState = MS_ENDTAGNAME;
        if (!root_attr)
        {
          bot_attr=root_attr=xatr;
        }
        else
        {
          bot_attr->next=xatr;
          bot_attr=xatr;
        }
      } else {
        AttrValueLen++;
      }
      break;
      
    case MS_ENDTAG:
      if (c == '>') {
        MSState = MS_TEXT;
        Text=buf+i+1;
        TextLen=0;
      L_ADD_TAG:
        {
          if((TagState == TS_NORMAL)||(TagState == TS_EMPTY))
          {
             XMLNode *tmp=EndTag(TagName,TagLen,root_attr);
             if (!root_node){
               root_node=tmp;
             }else{
               if(!is_closed)
                 bot_node->next=tmp;
               else bot_node->subnode=tmp;
             }
             TreeBranchs[stack_pos++]=tmp;
             bot_node=tmp;
             root_attr=0;
             is_closed=1;
          }
          if((TagState == TS_EMPTY)||(TagState == TS_CLOSE))
          {
            if(stack_pos>0){
              bot_node=TreeBranchs[--stack_pos];
            }
            is_closed=0;
          }
          if (root_attr)  // удаляем мусор
          {
            FreeAttrQueue(root_attr);
            root_attr=NULL;            
          }
        }   
      } else {
        goto L_ERR;
      }
      break;
      
    case MS_TEXT:
      if (c == '<')
      {
        if(TextLen>0)
        {
          if (bot_node)
          {
            AddTextToNode(bot_node, Text, TextLen);
          }
        }
        TextLen=0;
        MSState = MS_BEGINTAG;
        TagState = TS_INDEFINITE;
      }
      else
      {
        if (TagState == TS_NORMAL) TextLen++;
      }
      break;
      
    case MS_CHECK_DECL:
      if (!strncmp(buf+i, "[CDATA[", 7)) {
        i+=6;
        Text=buf+i+1;
        TextLen=0;
        MSState = MS_CDATA_SECTION;
        TagState = TS_NORMAL;
      } else if (buf[i]=='-' && buf[i+1]=='-') {
        i++;
        Text=buf+i+1;
        MSState = MS_COMMENT;
      } else {
        goto L_ERR;
      }
      break;
      
    case MS_CDATA_SECTION:
      if (buf[i]==']' && buf[i+1] ==']' && buf[i+2] =='>') {
        if(TextLen>0)
        {
          if (bot_node)
          {
            AddTextToNode(bot_node, Text, TextLen);
          }
        }
        TextLen=0;
        MSState = MS_BEGIN;
        TagState = TS_INDEFINITE;
        i+=2;
      } else {
        TextLen++;
      }
      break;
      
    case MS_COMMENT:
      if (buf[i]=='-' && buf[i+1] =='-' && buf[i+2] =='>') {
        TextLen=0;
        MSState = MS_BEGIN;
        TagState = TS_INDEFINITE;
        i+=2;
      } else {
        TextLen++;
      }
      break;
    }
    i++;
  }
L_ERR:
  FreeAttrQueue(root_attr);
  return root_node;//
}
