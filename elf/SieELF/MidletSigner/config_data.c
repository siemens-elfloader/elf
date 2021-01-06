#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define DEFAULT_JAVA_FOLDER "0:\\Applications\\";  
#else
#define DEFAULT_DISK "0"
#define DEFAULT_JAVA_FOLDER "0:\\Java\\jam\\";  
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"程序文件夹",0,63};
__root const char WORKFOLDER[64]=DEFAULT_DISK":\\Zbin\\utilities\\MidletSigner\\";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"*.der文件",0,31};
__root const char DER_FILE[32]="cert.der";

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"*.key文件",0,31};
__root const char KEY_FILE[32]="cert.key";

__root const CFG_HDR cfghdr13={CFG_STR_UTF8,"JAVA目录",0,128};
__root const char folder[129]=DEFAULT_JAVA_FOLDER;

__root const CFG_HDR cfghdr3={CFG_STR_UTF8,"文件夹图标",0,63};
__root const char FOLDER_ICON[64]=DEFAULT_DISK":\\Zbin\\utilities\\MidletSigner\\folder.png";

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"jar图标",0,63};
__root const char JAR_ICON[64]=DEFAULT_DISK":\\Zbin\\utilities\\MidletSigner\\jar.png";

__root const CFG_HDR cfghdr5={CFG_CBOX,"授权:\n数据读取",0,3};
__root const int FREAD=1;
__root const CFG_CBOX_ITEM cfgcbox3[3]={"否","是_x65","是_x75"};

__root const CFG_HDR cfghdr6={CFG_CBOX,"数据写入",0,3};
__root const int FWRITE=1;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"否","是_x65","是_x75"};

__root const CFG_HDR cfghdr7={CFG_CBOX,"网络",0,2};
__root const int INTERNET=1;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"否","是"};

__root const CFG_HDR cfghdr8={CFG_CBOX,"COM端口",0,2};
__root const int COMM=1;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"否","是"};

__root const CFG_HDR cfghdr9={CFG_CBOX,"蓝牙",0,2};
__root const int BLUETOOTH=1;
__root const CFG_CBOX_ITEM cfgcbox7[2]={"否","是"};

__root const CFG_HDR cfghdr10={CFG_CBOX,"短信",0,2};
__root const int SMS=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"否","是"};

__root const CFG_HDR cfghdr11={CFG_CBOX,"彩信",0,2};
__root const int MMS=1;
__root const CFG_CBOX_ITEM cfgcbox9[2]={"否","是_x65"};

__root const CFG_HDR cfghdr12={CFG_CBOX,"多媒体",0,3};
__root const int MEDIA=1;
__root const CFG_CBOX_ITEM cfgcbox10[3]={"否","是_x65","是_x75"};
