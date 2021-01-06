#define MY_SMSYS_IPC_NAME "MySMSYS"
#define MY_SMSYS_IPC_START	0 //����,data=IPC_DATA_DAEMON

#define SMSYS_IPC_MSG_MAX	9 //����submsg���ֵ

#define SMSYS_IPC_MAIN		1 //�����˵�, data=NULL
#define SMSYS_IPC_NEWSMS	2 //�½�����, data=NULL
#define SMSYS_IPC_IN_NEW	3 //��δ�������б�, data=NULL
#define SMSYS_IPC_IN_RD		4 //���Ѷ������б�, data=NULL
#define SMSYS_IPC_OUT			5 //���ѷ��Ͷ����б�, data=NULL
#define SMSYS_IPC_DRAFT		6 //�򿪲ݸ��б�, data=NULL
#define SMSYS_IPC_ALL			7 //��������Ϣ�б�, data=NULL
#define SMSYS_IPC_TLAST		8 //�鿴����һ������, data=NULL
#define SMSYS_IPC_IN_ALL  9 //�������������б�, data=NULL

#define SMSYS_IPC_ARCHIVE 0x40 //����Ϣ������,data=NULL

//#define SMSYS_IPC_INBOX_VIEW 0x80
#define SMSYS_IPC_NEW_IN_WIN 0x81 //��������Ϣ����,data=NULL
#define SMSYS_IPC_NEWSMS_NUM 0x82 //���ݺ����½�����,data=Number,Numberʹ��malloc�����ڴ�,��ɺ���MySMSYS�б��ͷ�,������ͨѶ¼/ͨ����¼���Ž�����
#define SMSYS_IPC_SEND_UTF8 0x83 //����UTF8�ı��½�����,data=UTF8_text,UTF8_textʹ��malloc�����ڴ�,UTF8����,,��ɺ���MySMSYS�б��ͷ�,���������ı���ʽ������Ҫ����/����/���

#define SMSYS_IPC_VIEW_OPMSG 0x84 //view,����opmsg_id�鿴����,data=opmsg_id,�����ڶ๦���ռ���
#define SMSYS_IPC_REPLY_OPMSG 0x85 //reply,����opmsg_id�ظ�����,data=opmsg_id,�����ڶ๦���ռ���
#define SMSYS_IPC_QR_OPMSG 0x86 //quote to reply,����opmsg_id����ԭ��Ϣ�ظ�����,data=opmsg_id,�����ڶ๦���ռ���
#define SMSYS_IPC_QN_OPMSG 0x87 //quote to new,����opmsg_id����ԭ��Ϣ�½�����,data=opmsg_id,�����ڶ๦���ռ���

#define SMSYS_IPC_SEND_WS 0x88 //����ws�½�����,data=ws

#define SMSYS_IPC_FVIEW 0x90 //ֱ�Ӳ鿴�ļ�,data=filename,filenameʹ��malloc�����ڴ�,��ɺ���MySMSYS�б��ͷ�,

#define SMSYS_IPC_CREATE_DLG	0xFF //����ͼ�ν���,(δʹ��)
#define SMSYS_IPC_UPDATE_CLIST	0x100 //����ͨѶ¼,data=NULL
#define SMSYS_IPC_SMS_DATA_UPDATE 0x101 //���¶�����������,data=NULL
//----------------
#define MY_SMSYS_CREATE	0
#define MY_SMSYS_CLOSE	1
#define MY_SMSYS_FVIEW	2
//----------------



