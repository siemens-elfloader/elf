#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"ͼƬ����",0,4};
__root const int PIC_QUALITY=2;
__root const CFG_CBOX_ITEM cfgcbox0[]={"��","����","������","������"};

__root const CFG_HDR cfghdr1={CFG_UINT,"��ʷ��¼��Ŀ",0,128};
__root const int HISTORY_DEPTH=20;

__root const CFG_HDR cfghdr2={CFG_UINT,"Java��ջֵ(kb)",0,16384};
#ifdef NEWSGOLD
#ifdef ELKA
__root const int JAVA_HEAP_SIZE=3072;
#else
__root const int JAVA_HEAP_SIZE=3072;
#endif
#else
__root const int JAVA_HEAP_SIZE=768;
#endif

__root const CFG_HDR cfghdr3={CFG_LEVEL,"������",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CBOX, "IPѡ��", 0, 4};
__root const int IP_CHOOSE= 0;
__root const CFG_CBOX_ITEM cfgcbox1[4]={"IP1","IP2","IP3","IP4"};

__root const CFG_HDR cfghdr3_1={CFG_STR_GB,"����1",0,31};
__root const char OM_POST_HOST1[32]="80.232.117.10";

__root const CFG_HDR cfghdr3_2={CFG_UINT,"�˿�1",0,65535};
__root const unsigned int OM_POST_PORT1=80;

__root const CFG_HDR cfghdr3_3={CFG_STR_GB,"����2",0,31};
__root const char OM_POST_HOST2[32]="203.81.19.12";

__root const CFG_HDR cfghdr3_4={CFG_UINT,"�˿�2",0,65535};
__root const unsigned int OM_POST_PORT2=80;

__root const CFG_HDR cfghdr3_5={CFG_STR_GB,"����3",0,31};
__root const char OM_POST_HOST3[32]="";

__root const CFG_HDR cfghdr3_6={CFG_UINT,"�˿�3",0,65535};
__root const unsigned int OM_POST_PORT3=80;

__root const CFG_HDR cfghdr3_7={CFG_STR_GB,"����4",0,31};
__root const char OM_POST_HOST4[32]="";

__root const CFG_HDR cfghdr3_8={CFG_UINT,"�˿�4",0,65535};
__root const unsigned int OM_POST_PORT4=80;

__root const CFG_HDR cfghdr3_end={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"Ĭ����������",0,127};
__root const char DEFAULT_PARAM[128]="bookmarks";

__root const CFG_HDR cfghdr5={CFG_UINT,"�������ݳ���",128,1024};
__root const int length=128;

