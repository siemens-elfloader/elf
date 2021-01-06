#ifndef _DECODE_XML_H_
  #define _DECODE_XML_H_


typedef struct XMLAttr_type XMLAttr;

typedef struct XMLAttr_type {
  XMLAttr *next;
  char *name;
  char *param;
} _XMLAttr;

typedef struct XMLNode_type XMLNode;

typedef struct XMLNode_type {
  XMLNode *next;
  XMLNode *subnode;
  char *name;
  XMLAttr *attr;
  char *value;
} _XMLNode;


// ������������ �����
XMLNode *XMLDecode(char *buf, int size);

// ���������� ������
void DestroyTree(XMLNode *tmpp);

enum XML_MAINSTATE{
  MS_BEGIN=1,                 //< ������ ��������
  MS_BEGINTAG,                //< ������� ���
  MS_MIDDLETAG,               //< �������� ����, �� ��� �� �����
  MS_TAGNAME,                 //< ������ ��� ����
  MS_ENDTAGNAME,              //< ��������� ������� ��� ����
  MS_ATTRIBNAME,              //< ������ ��� ���������
  MS_ENDATTRIBNAME,           //< ��������� ��� ���������
  MS_ENDEQUALLY,              //< ������ ���� = ����� ������ ��������� � ���������
  MS_ATTRIBVALUE,             //< ������ �������� ��������� (����� ")
  MS_ENDTAG,                  //< ����� ���� (��� ������������������ ����� /)
  MS_TEXT,                    //< �����
  MS_CHECK_DECL,
  MS_CDATA_SECTION,
  MS_COMMENT
};

enum XML_TAGSTATE{
  TS_INDEFINITE=1,            //< ��������������, �.�. ��� ������ ������ ������� (���� ������)
  TS_NORMAL,                  //< ������� (��)�������������. ����� �� ����������
  TS_CLOSE,                   //< �������������
  TS_EMPTY,                   //< ��� � �����������
  TS_DECLARATION              //< ����������, ��� ��� XML. ������ ��������� ����������
};

#endif
