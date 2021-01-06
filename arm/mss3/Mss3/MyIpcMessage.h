#ifndef _MYIPCMESSAGE_H_
#define _MYIPCMESSAGE_H_

#define MY_SMSYS_IPC_START	0 //启动,data=IPC_DATA_DAEMON


#define SMSYS_IPC_MAIN		1 //打开主菜单, data=NULL
#define SMSYS_IPC_NEWSMS	2 //新建短信, data=NULL
#define SMSYS_IPC_IN_NEW	3 //打开未读短信列表, data=NULL
#define SMSYS_IPC_IN_RD		4 //打开已读短信列表, data=NULL
#define SMSYS_IPC_OUT			5 //打开已发送短信列表, data=NULL
#define SMSYS_IPC_DRAFT		6 //打开草稿列表, data=NULL
#define SMSYS_IPC_ALL			7 //打开所有信息列表, data=NULL
#define SMSYS_IPC_TLAST		8 //查看最新一条短信, data=NULL
#define SMSYS_IPC_IN_ALL  9 //打开所有来短信列表, data=NULL

#define SMSYS_IPC_ARCHIVE 0x40 //打开信息档案柜,data=NULL

#define SMSYS_IPC_NEW_IN_WIN 0x81 //弹出新信息窗口,data=NULL,来自补丁
#define SMSYS_IPC_NEWSMS_NUM 0x82 //根据号码新建短信,data=Number,Number使用malloc申请内存,完成后将在MySMSYS中被释放,可用于通讯录/通话记录中信建短信
#define SMSYS_IPC_SEND_UTF8 0x83 //基于UTF8文本新建短信,data=UTF8_text,UTF8_text使用malloc申请内存,UTF8编码,,完成后将在MySMSYS中被释放,可用于以文本格式发送重要记事/任务/便笺

#define SMSYS_IPC_VIEW_OPMSG 0x84 //view,基于opmsg_id查看短信,data=opmsg_id,可用于多功能收件箱
#define SMSYS_IPC_REPLY_OPMSG 0x85 //reply,基于opmsg_id回复短信,data=opmsg_id,可用于多功能收件箱
#define SMSYS_IPC_QR_OPMSG 0x86 //quote to reply,基于opmsg_id引用原信息回复短信,data=opmsg_id,可用于多功能收件箱
#define SMSYS_IPC_QN_OPMSG 0x87 //quote to new,基于opmsg_id引用原信息新建短信,data=opmsg_id,可用于多功能收件箱

#define SMSYS_IPC_SEND_WS 0x88 //基于ws新建短信,data=ws
#define SMSYS_IPC_NEW_IN_ME 0x89 //弹出新信息窗口,data=dat_index,来自自身

#define SMSYS_IPC_FVIEW 0x90 //直接查看文件,data=filename,filename使用malloc申请内存,完成后将在MySMSYS中被释放,
#define SMSYS_IPC_READ_NEW 0x91 //新短信在timer之后发送,开始读取预存的dat_index
#define SMSYS_IPC_READ_SMS 0x92 //普通短信,检查之后发现要重新读取

#define SMSYS_IPC_CREATE_DLG	0xFF //创建图形界面,(未使用)
#define SMSYS_IPC_UPDATE_CLIST	0x100 //更新通讯录,data=NULL
#define SMSYS_IPC_SMS_DATA_UPDATE 0x101 //更新短信数据链表,data=NULL
//#define SMSYS_IPC_READ_NEW_SECC 0x102 //data=NULL
//#define SMSYS_IPC_NAB_CREATE 0x104 //data=csm_id
#define SMSYS_IPC_ADD_CSMID 0x104 //data=csm_id

//vibra play
#define SMSYS_IPC_VIBRA_START 0x120 //data=NULL
#define SMSYS_IPC_VIBRA_STOP 0x121 //data=NULL
#define SMSYS_IPC_VIBRA_NEXT 0x122 //data=NULL

#define SMSYS_IPC_SOUND_PLAY 0x130 //data=filepath
#define SMSYS_IPC_SOUND_STOP 0x131 //data=NULL

//send list
#define SMSYS_IPC_SEND_LIST 0x140 //data= SNDLST

void SendMyIpc(int submess);
void SendMyIpc(int submess, void *data);

#endif
