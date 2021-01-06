#include "..\inc\swilib.h"
#include "filelist.h"
#include "main.h"

extern int scroll_pos; // ��������������ʾ����ʼλ��
extern int scroll_wait;
extern const char g_path[128];
extern char procfile[128];
extern int playhandle;
extern char *list_text;
extern LIST_SONG_NAME *name_list;
//extern char **pp_list; //��ָ��ָ���ָ��洢ÿ�׸��λ��
char list_path[128];
int list_size=0;
char *p_list; //��ָ��ָ��ǰ���ڲ��ŵĸ���
//int some_num_in_list;
int SONG_NUM_NOW=0;
int SONG_ALL=0; //�б��������


void get_song_point(void)
{
  char *pp;
  pp=list_text;
  int i=0;
	while(*(pp+2))
  {
    if((*(pp+1)==':')&&(*(pp+2)=='\\'))//��":\"Ϊ���
    {
      (name_list+i)->id=i;
    	(name_list+i)->p_name=pp;
    	i++;
    }
    pp++;
  }
  SONG_ALL=i-1;
}
  

void check_song_now(void)
{
	int i=0;
	for(;i<SONG_ALL;i++)
	{
		if((name_list+i)->p_name==p_list)
			break;
	}
	SONG_NUM_NOW=i;
}

void get_currect_song_name(void)
{
  char *p;
  p=p_list;
  int c;
  int i=0;
  char ss[128];
  int is_1st_utf8=0;
  while(*p)
  {
    if((*(p+1)==':')&&(*(p+2)=='\\'))//��":\"Ϊ���
      break;
    p++;
  }
  p_list=p;
  check_song_now();
  while((*p!=0)&&(*p!='\n'))
  {
    c=*p;
    if(c>=' ')
    {
      if((is_1st_utf8==0)&&(c>0x80))//��һ��UTF8����ʶ����ʱ����0x80ΪASCII���ֽ��ַ����ֵ
      {
        ss[i]=0x1F;
        i++;
        is_1st_utf8=1;
      }
      if (i<(sizeof(ss)-1)) ss[i]=c;
      i++;
    }
    p++;
  }
  ss[i]='\0';
  strcpy(procfile,ss);
  scroll_pos = 0;
}

void top2end(void)
{
  char *p;
  p=strrchr(list_text,':'); //���������һ��':'�ַ�
  p_list=p-1;
  get_currect_song_name();
}

void end2top(void)
{
  p_list=list_text;
  get_currect_song_name();
}

void get_next_song(void)
{
  char *p;
  p=p_list;
  while(*p!='\n')
  {
    p++;
  }
  while((*p=='\n')||(*p==' '))//�ų��м������з����ո��Լ�����ĩβ
  {
    p++;
    if(*p=='\0')
    {
      end2top();
      return;
    }
  }
  p_list=p;
  get_currect_song_name();
}

void get_prev_song(void)
{
  char *p;
  p=p_list;
  while(*p)
  {
    p--;
    if((*(p+1)==':')&&(*(p+2)=='\\')) //��":\"Ϊ���������һ��
      break;
  }
  if(*p==0)
  {
    top2end();
    return;
  }
  p_list=p;
  get_currect_song_name();
}

void load_list(int type) //0: load his fail, 1:load his succ... 2:reload
{
  unsigned int err;
  if(type==0)
  {
    strncpy(list_path,g_path,strlen(g_path));
    strcat(list_path,"PlayList\\mylist.lst\0");
  }
  int f=fopen(list_path,A_ReadOnly+A_BIN,P_READ,&err);
  if(f!=-1)
  {
    list_size=fread(f,list_text,32767,&err);
    fclose(f,&err);
  }
  if (list_size>=0)
    list_text[list_size]=0;

  get_song_point();

  if(type==0||type==2) //load his fail or reload
  {
    p_list=list_text; //��ʼ��һ��
    get_currect_song_name();
  }
  else
  {
    char *p=strstr(list_text,procfile); //ת���б��е�λ��
    if(*p)
      p_list=p;
    check_song_now();
  }
  

}


void select_list_gui(void)
{
  open_select_file_gui(1,1);
}


/*============================play mode============================*/

void play_next(void) //˳��ѭ��
{
	get_next_song();
	control(0);
}

void play_prev(void) //����ѭ��
{
	get_prev_song();
	control(0);
}

/***************************************************************
����Ϊ����㷨��by binghelingxi(bingk)
ԭ���Ȼ�ȡ���ڲ��Ÿ�����handle���Ȿ�����һ�����������
Ȼ��������3�����õ�������0��1��2���ֱ�λ���б������������
�ٽ�ԭ���õ���handle����0x18(��ԼΪһ�׸�·���ĳ���)
ѭ����ȥhandle/3��ֱ����������������λ���б�ķ�Χ�ڵ�Ϊֹ
Ȼ��Ѹ������б��е�λ��ָ�붨λ�������
����get_currect_song_name��������Ϳ��Եõ�׼ȷ�ĸ�����
****************************************************************/

void play_shuff(void)
{
  if(playhandle)
  {
    int y;
    int x=playhandle;
    int c=x%3;
    switch(c)
    {
      case 0:
        y=x*0x18;
        while(y>=list_size/3)
        {
          y-=list_size/3;
        }
        break;
      case 1:
        y=list_size/3+x*0x18;
        while(y>=list_size/3*2)
        {
          y-=list_size/3;
        }
        break;
      case 2:
        y=list_size/3*2+x*0x18;
        while(y>=list_size)
        {
          y-=list_size/3;
        }
        break;
    }
    p_list=list_text;
    p_list+=y;
    get_currect_song_name();
    control(0);
  }
}

/****************************************************

****************************************************/

