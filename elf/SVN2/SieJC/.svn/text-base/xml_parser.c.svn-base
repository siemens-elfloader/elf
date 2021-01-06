#include "..\inc\swilib.h"
#include "main.h"
#include "string_util.h"
#include "xml_parser.h"

int IsSpace (char c){
	return	c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

int IsLit (char c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int IsNum (char c){
	return (c >= '0' && c <= '9');
}

int InName (char c){
  return IsLit(c) || IsNum(c) || c == '_' || c == '-' || c == ':';
}


 XMLNode *XMLTree=0;
 XMLAttr *curattr=0;
 int *TreeBranchs;
 int BranchPos=0;
 XMLNode *current = 0;
 XMLNode *tmp=0;
 XMLAttr *attribs=0;
 int isClosed=0;
 char *TagName;					
 char *AttrName;				
 char *AttrValue;				
 char *Text;
 int TagState;
 int MSState;

 int f;
 unsigned int ul;

 char _crlf[2] = {0xd,0xa};
 char tabul[100];
 char bbuf[256];
 char bbf[256];

 
void SaveBranch(XMLNode *tmpp){
 while(tmpp){
   strcpy(bbuf,tabul);
   sprintf(bbf,"name: %s = ",tmpp->name);
   strcat(bbuf,bbf);
   if(tmpp->value){
     sprintf(bbf,"%s",tmpp->value);
     strcat(bbuf,bbf);
   }
   strcat(bbuf,_crlf);
   fwrite(f,bbuf,strlen(bbuf),&ul);
   if(tmpp->attr){
     XMLAttr *ta=tmpp->attr;
     strcpy(bbuf,tabul);
     strcat(bbuf,"attributes: ");
     strcat(bbuf,_crlf);
     fwrite(f,bbuf,strlen(bbuf),&ul);
     while(ta){
       strcpy(bbuf,tabul);
       sprintf(bbf,"%s - ",ta->name);
       strcat(bbuf,bbf);
       if(ta->param){
         sprintf(bbf,"%s",ta->param);
         strcat(bbuf,bbf);
       }
       strcat(bbuf,_crlf);
       fwrite(f,bbuf,strlen(bbuf),&ul);
       ta=ta->next;
     }
   }
   fwrite(f,_crlf,2,&ul);
   if(tmpp->subnode){
     strcat(tabul,"  ");
     SaveBranch(tmpp->subnode);
     *(tabul+strlen(tabul)-2)=0;
   }
   tmpp=tmpp->next;
 }
}

void SaveTree(XMLNode *tree){
  //strcpy(tabul,"");
  zeromem(tabul,64);
#ifdef NEWSGOLD
  const char savepath[]="4:\\xml_packet.txt";
#else
  const char savepath[]="0:\\xml_packet.txt";
#endif
  f=fopen(savepath, A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  SaveBranch(XMLTree);
  fclose(f,&ul);
}
 
void EndTag(void){
  if((TagState == TS_NORMAL)||(TagState == TS_EMPTY)){
    tmp=malloc(sizeof(XMLNode));
    zeromem(tmp,sizeof(XMLNode));
    if (!XMLTree){
      XMLTree=tmp;
    }else{
      if(!isClosed)current->next=tmp;
      else current->subnode=tmp;
    }
    tmp->name=malloc(strlen(TagName)+1);
    if(attribs)tmp->attr=attribs;
    attribs=0;
    strcpy(tmp->name,TagName);
    *(TreeBranchs+BranchPos)=(int)tmp;
    BranchPos++;
    current=tmp;
    curattr=0;
    isClosed=1;
  }
  if((TagState == TS_EMPTY)||(TagState == TS_CLOSE)){
    if(BranchPos>0){
      BranchPos--;
      current=(void*)(*(TreeBranchs+BranchPos));
    }
    isClosed=0;
  }
}

void EndAttr(void){
  XMLAttr *tmp2=malloc(sizeof(XMLAttr));
  zeromem(tmp2,sizeof(XMLAttr));
  tmp2->name=malloc(strlen(AttrName)+1);
  strcpy(tmp2->name,AttrName);
  if(strlen(AttrValue)>0){
    char *newattrval = Replace_Special_Syms(AttrValue);
   tmp2->param=malloc(strlen(newattrval)+1);
   strcpy(tmp2->param,newattrval);
   mfree(newattrval);
  }
  if(!curattr){
    attribs=tmp2;
  }else{
    curattr->next=tmp2;
  }
  curattr=tmp2;
}

void DestroyTree(XMLNode *tmpp){
 while(tmpp){
   XMLAttr *ta=tmpp->attr;
   while(ta){
       tmpp->attr=ta->next;
       if(ta->name)mfree(ta->name);
       if(ta->param)mfree(ta->param);
       mfree(ta);
       ta=tmpp->attr;
   }
   if(tmpp->subnode){
     DestroyTree(tmpp->subnode);
   }
   XMLNode *tmpp2=tmpp->next;
   if(tmpp->name)mfree(tmpp->name);
   if(tmpp->value)mfree(tmpp->value);
   mfree(tmpp);
   tmpp=tmpp2;
 }
 
 XMLTree=0;
 curattr=0;
 BranchPos=0;
 current = 0;
 tmp=0;
 attribs=0;
 isClosed=0; 
}

void Finish(void){
 mfree(TagName);
 mfree(AttrName);
 mfree(AttrValue);
 mfree(Text);
 mfree(TreeBranchs);
}

void *XMLDecode(char *buf, int size){

 
 TagName=malloc(size);					
 AttrName=malloc(size);				
 AttrValue=malloc(size);				
 Text=malloc(size);
 TreeBranchs=malloc(1024);

 zeromem(TagName,size);
 zeromem(AttrName,size);
 zeromem(AttrValue,size);
 zeromem(Text,size);
 MSState = MS_BEGIN;
 TagState = TS_INDEFINITE;
 char sh_str[2]=".\0";
 int i = 0;

	while ((i<size)){
            char c = *(buf+i);
            sh_str[0]=c;
            
	    switch (MSState){
		case MS_BEGIN:
			if (c == '<'){
				MSState = MS_BEGINTAG;
			}else if (!IsSpace (c)){
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_BEGINTAG:
                        strcpy(AttrName,"");
			if (IsLit (c)){
				MSState = MS_TAGNAME;
				TagState = TS_NORMAL;
                                strcpy(TagName,sh_str);

			}else if (IsSpace(c)){
				MSState = MS_MIDDLETAG;
				TagState = TS_NORMAL;
			}else if (c == '?'){
				TagState = TS_DECLARATION;
				MSState = MS_MIDDLETAG;
			}else if (c == '/'){
				TagState = TS_CLOSE;
				MSState = MS_MIDDLETAG;
			}else{
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_MIDDLETAG:
			if (IsLit (c)){
				MSState = MS_TAGNAME;
				strcpy(TagName,sh_str);
			}else if (!IsSpace (c)){
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_TAGNAME:
			if (InName (c)){
				strcat(TagName,sh_str);
			}else if (IsSpace(c)){
				MSState = MS_ENDTAGNAME;
			}else if (c == '/'){
				MSState = MS_ENDTAG;
				TagState = TS_EMPTY;
			}else if (c == '>'){
				MSState = MS_TEXT;
				EndTag();
			}else{
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_ENDTAGNAME:
			if (IsLit (c)){
				MSState = MS_ATTRIBNAME;
				strcpy(AttrName,sh_str);
			}else if (c == '/'){
				MSState = MS_ENDTAG;
				TagState = TS_EMPTY;
			}else if (c == '>'){
				MSState = MS_TEXT;
				EndTag();
			}else if (!IsSpace(c) && (c != '?' && TagState != TS_DECLARATION)){
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_ATTRIBNAME:
			if (InName(c)){
				strcat(AttrName,sh_str);
			}else if (c == '='){
				MSState = MS_ENDEQUALLY;
			}else if (IsSpace(c)){
				MSState = MS_ENDATTRIBNAME;
			}else{
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

                case MS_ENDATTRIBNAME:
			if (c == '='){
				MSState = MS_ENDEQUALLY;
			}else if (!IsSpace(c)){
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_ENDEQUALLY:
			if ((c == '\"')||(c == '\'')){
				MSState = MS_ATTRIBVALUE;
				strcpy(AttrValue,"");
			}else if (!IsSpace(c)){
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_ATTRIBVALUE:
			if ((c == '\"')||(c == '\'')){
				MSState = MS_ENDTAGNAME;
				EndAttr();
			}else{
				strcat(AttrValue,sh_str);
			}
			break;

		case MS_ENDTAG:
			if (c == '>'){
				MSState = MS_TEXT;
				EndTag();
			}else{
				Finish();
				return XMLTree;//0;
                                //EndParse = 1;
			}
			break;

		case MS_TEXT:

			if (c == '<'){
                          if(strlen(Text)>0){
                            //tmp->value=malloc(strlen(Text)+1);
                            //strcpy(tmp->value,Text);
                            tmp->value = Replace_Special_Syms(Text);
                          }
                          strcpy(Text,"");
                          MSState = MS_BEGINTAG;
                          TagState = TS_INDEFINITE;
			}else{
                          if((TagState == TS_NORMAL)) strcat(Text,sh_str);
                        }
			break;
		}
            i++;
	}

	//if (!EndParse) return 1;
        //{
//		Success();
//	}

	Finish();
        return XMLTree;//
}


/*
  Получить значение атрибута по его имени
IN: char* req_attr_name - название атрибута
    XMLAttr* attr_list  - список атрибутов тега
OUT: значение атрибута или NULL
*/
char* XML_Get_Attr_Value(char* req_attr_name, XMLAttr* attr_list)
{
  XMLAttr* attr_Ex = attr_list;
  while(attr_Ex)
  {
    if(attr_Ex->name)
      if(!strcmp(req_attr_name, attr_Ex->name)) return attr_Ex->param;
    attr_Ex = attr_Ex->next;
  }
  return NULL;
}

/*
  Получить дочерний узел из списка дочерних узлов по его имени
IN: XMLNode* node         - родительский узел
    char* req_node_name   - имя требуемого узла
OUT: дочерний узел или NULL
*/
XMLNode* XML_Get_Child_Node_By_Name(XMLNode* node, char* req_node_name)
{
  XMLNode* nodeEx = node->subnode;
  while(nodeEx)
  {
    if(nodeEx->name)
      if(!strcmp(req_node_name, nodeEx->name)) return nodeEx;
    nodeEx = nodeEx->next;
  }
  return NULL;
}

/*
  Получить дочерний узел из списка дочерних узлов по его имени,
  при условии, что существует заданный атрибут с заданным значением
IN: XMLNode* node         - родительский узел
    char* req_node_name   - имя требуемого узла
    char* req_attr_name   - имя атрибута
    char* req_attr_velue  - значение атрибута
OUT: дочерний узел или NULL
*/
XMLNode* XML_Get_Child_Node_By_Name_And_Attr(XMLNode* node, char* req_node_name, char* req_attr_name, char* req_attr_velue)
{
  XMLNode* nodeEx = node->subnode;
  while(nodeEx)
  {
    if(nodeEx->name)
      if(!strcmp(req_node_name, nodeEx->name))    // Если найден нод с нужным именем
      {
        char *attr_val = XML_Get_Attr_Value(req_attr_name, nodeEx->attr);
        if(attr_val)    // Если есть требуемый атрибут
        {
          if(!strcmp(attr_val, req_attr_velue))return nodeEx;          
        }
      }
    nodeEx = nodeEx->next;
  }
  return NULL;
}
//EOL,EOF
