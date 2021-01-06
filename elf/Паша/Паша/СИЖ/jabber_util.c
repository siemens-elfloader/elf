#include "../inc/swilib.h"
#include "history.h"
#include "main.h"
#include "clist_util.h"
#include "revision.h"
#include "jabber_util.h"
#include "string_util.h"
#include "xml_parser.h"
#include "item_info.h"
#include "vCard.h"
#include "jabber.h"
#include "bookmarks.h"
#include "serial_dbg.h"
#include "groups_util.h"
#include "adv_login.h"
#include "base64.h"
#include "lang.h"

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
extern const char percent_t[];

extern const char JABBER_SERVER[];
extern const char USERNAME[];
extern const char PASSWORD[];
extern const char RESOURCE[];
extern const char CMP_DATE[];
extern const char VERSION_NAME[];
extern const char VERSION_VERS[];
extern const char OS[];
extern const int USE_SASL;
extern const int USE_ZLIB;
extern const int DELIVERY_EVENTS;
extern const int DISPLAY_POPUPS;
extern char My_JID_full[];
extern char My_JID[];
extern char logmsg[];

extern GR_ITEM *GR_ROOT;
extern CLIST* cltop;
extern unsigned int NContacts;

MUC_ITEM *muctop = NULL;

TTime intimes; //��� idle
TDate indates;

extern JABBER_STATE Jabber_state;
const char* PRESENCES[PRES_COUNT] = {"online",
                                     "chat",
                                     "away",
                                     "xa",
                                     "dnd",
                                     "invisible",
                                     "unavailable",
                                     "error",
                                     "subscribe",
                                     "subscribed",
                                     "unsubscribe",
                                     "unsubscribed"};



#define AFFS_CNT 5
#define ROLS_CNT 4

const char* JABBER_AFFS[] = {"none", "outcast", "member", "admin", "owner"};
const char* JABBER_ROLS[] = {"none", "visitor", "participant", "moderator"};

ONLINEINFO OnlineInfo = {0,0,NULL};

/*
  ������� ������������ Jabber Iq
*/
//Context: HELPER
void SendIq(char* to, char* type, char* id, char* xmlns, char* payload)
{
  char* xmlq=malloc(1024);
  char *xmlq2=malloc(1024);
  char s_to[128];
  char s_id[40];
  if(id)
  {
    snprintf(s_id,40,"id='%s'", id);
  }
  else
  {
    strcpy(s_id, "");
  }
  char *_from = Mask_Special_Syms(My_JID_full);
  sprintf(xmlq, "<iq type='%s' %s from='%s'", type, s_id, _from);
  mfree(_from);
  if(to)
  {
    char *_to = Mask_Special_Syms(to);
    snprintf(s_to, 128, " to='%s'", _to);
    strcat(xmlq, s_to);
    mfree(_to);
  }
  if(payload)
  {
    strcat(xmlq, ">\r\n<query xmlns='%s'>\r\n%s\r\n</query>\r\n</iq>");
    sprintf(xmlq2, xmlq, xmlns, payload);
  }
  else
  {
    strcat(xmlq, ">\r\n<query xmlns='%s'/>\r\n</iq>");
    sprintf(xmlq2, xmlq, xmlns);
  }
  sprintf(xmlq2, xmlq, xmlns, payload);
  SendAnswer(xmlq2);
//  Log("IQ_OUT", xmlq2);
  mfree(xmlq2);
  mfree(xmlq);
}

/*
  ������� �����������, �� ���� ������ �������� �������� stream.
  ����� ����� ����� �������� � ��������
*/
// Context:HELPER
void Send_Welcome_Packet()
{

  void Send_Welcome_Packet_SASL();
  if(USE_SASL)
  {
    Send_Welcome_Packet_SASL();
    return;
  }
  char streamheader[]="<?xml version='1.0' encoding='UTF-8'?>\n"
    "<stream:stream to='%s' xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' xml:lang='en'>";
  char* buf=malloc(256);
  sprintf(buf,streamheader,JABBER_SERVER);
  SendAnswer(buf);
  mfree(buf);
  LockSched();
  strcpy(logmsg,"Send Welcome");
  UnlockSched();
#ifdef LOG_ALL
  Log("CONN",logmsg);
#endif
}
/*
  ������� ����������
*/
// Context:HELPER
void Send_Disconnect()
{
  char streamend[]="</stream:stream>";
  SendAnswer(streamend);
  strcpy(logmsg,"Send Disconnect");
#ifdef LOG_ALL
  Log("CONN",logmsg);
#endif
}

// ��������� Iq-��������
char auth_id[] = "SieJC_auth_req";
char rost_id[] = "SieJC_rost_req";
char vreq_id[] = "SieJC_vers_req";
char priv_id[] = "SieJC_priv_req";
char treq_id[] = "SieJC_time_req";
char vcreq_id[] = "SieJC_vcard_req";
char lastact_id[] = "SieJC_lastact_req";
/*
  ����������� �� Jabber-�������
  ����� �����, ��� ����������.
*/
//Context: HELPER
void Send_Auth()
{
  sprintf(My_JID, "%s@%s",USERNAME, JABBER_SERVER);
  sprintf(My_JID_full,"%s/%s",My_JID, RESOURCE);
  char* payload = malloc(256);
  sprintf(payload,"<username>%s</username>\n<password>%s</password>\n<resource>%s</resource>",USERNAME, PASSWORD, RESOURCE);
  SendIq(NULL, IQTYPE_SET, auth_id, IQ_AUTH, payload);
  mfree(payload);
  LockSched();
  strcpy(logmsg,"Send auth");
  UnlockSched();
}

//Context: HELPER
void _senddicoinforequest(char *dest_jid)
{
  char discoid[]="SieJC_discoinfo";
  char typ[]=IQTYPE_GET;
  char iqd[]=DISCO_INFO;
  SendIq(dest_jid, typ, discoid, iqd, NULL);
  mfree(dest_jid);
}


void Send_DiscoInfo_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_senddicoinforequest,to);
}

//Context: HELPER
void _sendversionrequest(char *dest_jid)
{
  char typ[]=IQTYPE_GET;
  char iq_v[]=IQ_VERSION;

  SendIq(dest_jid, typ, vreq_id, iq_v, NULL);
  mfree(dest_jid);
}

// ������� ������ � ������ ������������ � ��������� JID
void Send_Version_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendversionrequest,to);
}
//Context: HELPER

void _sendtimerequest(char *dest_jid)
{
  char typ[]=IQTYPE_GET;
  char iq_v[]=IQ_TIME;
  SendIq(dest_jid, typ, treq_id, iq_v, NULL);
  mfree(dest_jid);
}

// ������� ������ � ��������� ������� ������� ������������ � ��������� JID
void Send_Time_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendtimerequest,to);
}

void _sendvcardrequest(char *to)
{
  char* xmlq=malloc(1024);
  sprintf(xmlq, "<iq to='%s' type='get' id='%s'>\r\n<vCard xmlns='vcard-temp'/>\r\n</iq>", Mask_Special_Syms(to), vcreq_id);
  SendAnswer(xmlq);
  mfree(xmlq);
  mfree(to);
}

// ������� ������ � ������ vcard
void Send_Vcard_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendvcardrequest,to);
}

void _sendlastactivrequest(char *dest_jid)
{
  char typ[]=IQTYPE_GET;
  char iq_v[]=IQ_IDLE;
  SendIq(dest_jid, typ, lastact_id, iq_v, NULL);
  mfree(dest_jid);
}

void Send_LastActivity_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendlastactivrequest,to);
}

// ������������� ver= ������ �� ������� ������������ �������
// ������������ ������ ���������� �����������!
char *Generate_Caps()
{
  char caps_tpl[]="%s:%i:%d";
  char *q = malloc(64);
  zeromem(q,64);
  snprintf(q,127, caps_tpl, VERSION_VERS,__SVN_REVISION__,DELIVERY_EVENTS);
  char *Result_Resp;
  base64_encode(q, strlen(q),&Result_Resp);
  mfree(q);
  return Result_Resp;
}

/*
  ������� ��� ����������� (� ���������, ����� ����� �� ��� ������������
  ����������� ���������, � �� ���������� � �������� ������ ��������)

*/
// Context: HELPER
void Send_Presence(PRESENCE_INFO *pr_info)
{
  extern char My_Presence;
  My_Presence = pr_info->status;

  OnlineInfo.status = pr_info->status;
  OnlineInfo.priority = pr_info->priority;
  if(OnlineInfo.txt)mfree(OnlineInfo.txt);
  if(pr_info->message)
  {
    OnlineInfo.txt = malloc(strlen(pr_info->message)+1);
    strcpy(OnlineInfo.txt, pr_info->message);
  }else OnlineInfo.txt = NULL;

  //<c xmlns='http://jabber.org/protocol/caps' node='VERSION_NAME' ver='VERSION_VERS __SVN_REVISION__' />

  // ���������� ���� ������ �� ���������� ���
  char *caps = Generate_Caps();

  char* presence = malloc(1024);
  if(pr_info->status!=PRESENCE_INVISIBLE)
  {
    if(pr_info->message)
    {
      char presence_template[]="<presence><priority>%d</priority><show>%s</show><status>%s</status><c xmlns='http://jabber.org/protocol/caps' node='%s %s-r%d' ver='%s' /></presence>"; //�� ���� ��� �����/������� �� ���� ���������� ����
      snprintf(presence,1024,presence_template, pr_info->priority, PRESENCES[pr_info->status], pr_info->message, VERSION_NAME, VERSION_VERS, __SVN_REVISION__, caps);
    }
    else
    {
      char presence_template[]="<presence><priority>%d</priority><show>%s</show><c xmlns='http://jabber.org/protocol/caps' node='%s %s-r%d' ver='%s' /></presence>";//�� ���� ��� �����/������� �� ���� ���������� ����
      snprintf(presence,1024,presence_template, pr_info->priority, PRESENCES[pr_info->status], VERSION_NAME, VERSION_VERS, __SVN_REVISION__, caps);
    }
  }
  else
  {
      char presence_template[]="<presence type='invisible'/>";
      strcpy(presence,presence_template);
  }
  SendAnswer(presence);

// MUC support
  MUC_ITEM* m_ex = muctop;
  while(m_ex)
  {
    char *_to = Mask_Special_Syms(m_ex->conf_jid);
    char *_from = Mask_Special_Syms(My_JID_full);
    if(pr_info->message)
    {
      char presence_template[]="<presence from='%s' to='%s'><show>%s</show><status>%s</status><c xmlns='http://jabber.org/protocol/caps' node='%s %s-r%d' ver='%s' /></presence>";//�� ���� ��� �����/������� �� ���� ���������� ����
      snprintf(presence,1024,presence_template, _from, _to, PRESENCES[pr_info->status], pr_info->message, VERSION_NAME, VERSION_VERS, __SVN_REVISION__, caps);
    }
    else
    {
      char presence_template[]="<presence from='%s' to='%s'><show>%s</show><c xmlns='http://jabber.org/protocol/caps' node='%s %s-r%d' ver='%s' /></presence>";//�� ���� ��� �����/������� �� ���� ���������� ����
      snprintf(presence,1024,presence_template, _from, _to, PRESENCES[pr_info->status], VERSION_NAME, VERSION_VERS, __SVN_REVISION__, caps);
    }
    mfree(_to);
    mfree(_from);
    SendAnswer(presence);
    m_ex=m_ex->next;
  };
  mfree(caps);
  mfree(presence);
  if(pr_info->message)mfree(pr_info->message);
  mfree(pr_info);
  LockSched();
  strcpy(logmsg,"Send presence");
  UnlockSched();
}

void Send_ShortPresence(char *to,char type)
{
  char pr_templ[] = "<presence to='%s' type='%s'/>";
  char* pr=malloc(1024);
  sprintf(pr, pr_templ,Mask_Special_Syms(to),PRESENCES[type]);
  SendAnswer(pr);
  mfree(pr);
}

/*
  ������� ������ �������
*/
// Context: HELPER
void Send_Roster_Query()
{
  SendIq(NULL, IQTYPE_GET, rost_id, IQ_ROSTER, NULL);
  LockSched();
  strcpy(logmsg,"Send roster Q");
  UnlockSched();
}

unsigned int m_num=0;


// Context: HELPER
void SendMessage(char* jid, IPC_MESSAGE_S *mess)
{
/*
  <message to='romeo@montague.net' id='message22'>
      <body>Art thou not Romeo, and a Montague?</body>
      <x xmlns='jabber:x:event'>
        <offline/>
        <delivered/>
        <displayed/>
        <composing/>
      </x>
    </message>
*/
  char *_jid = Mask_Special_Syms(jid);
  char mes_template[]="<message to='%s' id='SieJC_%d' type='%s'><body>%s</body><x xmlns='jabber:x:event'></x></message>";
  char* msg_buf = malloc(MAX_MSG_LEN*2+200);
  if(mess->IsGroupChat)
  {
     sprintf(msg_buf, mes_template, _jid, m_num, MSGSTR_GCHAT, mess->body);
  }else sprintf(msg_buf, mes_template, _jid, m_num, MSGSTR_CHAT, mess->body);
  mfree(mess->body);
  mfree(mess);
  mfree(_jid);
#ifdef LOG_ALL
  LockSched();
  Log("MESS_OUT", msg_buf);
  UnlockSched();
#endif
  SendAnswer(msg_buf);
  mfree(msg_buf);
  m_num++;
  GetDateTime(&indates, &intimes);
}

extern const int COMPOSING_EVENTS;
 // Context: HELPER
void SendComposing(char* jid)
{
  if(!COMPOSING_EVENTS)return;
  char* _jid = Mask_Special_Syms(jid);
  const char mes_template[]="<message to='%s' id='SieJC_%d'><x xmlns='jabber:x:event'><composing/><id>SieJC_%d</id></x></message>";
  char* msg_buf = malloc(MAX_MSG_LEN*2+200);
  sprintf(msg_buf, mes_template, _jid, m_num, m_num);
  mfree(_jid);
  SendAnswer(msg_buf);
  mfree(msg_buf);
  m_num++;
}

 // Context: HELPER
void CancelComposing(char* jid)
{
  if(!COMPOSING_EVENTS)return;
  char* _jid= Mask_Special_Syms(jid);
  const char mes_template[]="<message to='%s' id='SieJC_%d'><x xmlns='jabber:x:event'><id>SieJC_%d</id></x></message>";
  char* msg_buf = malloc(MAX_MSG_LEN*2+200);
  sprintf(msg_buf, mes_template, _jid, m_num-1, m_num-1);
  mfree(_jid);
  SendAnswer(msg_buf);
  mfree(msg_buf);
  m_num++;
}

// Context: HELPER
void Report_VersionInfo(char* id, char *to)
{
  char answer[200];
  char *ph_model = Get_Phone_Info(PI_MODEL);
  char *ph_sw = Get_Phone_Info(PI_SW_NUMBER);
  sprintf(answer, "<name>%s</name><version>%s-r%d (%s)</version><os>SIE-%s/%s %s</os>", VERSION_NAME, VERSION_VERS, __SVN_REVISION__, CMP_DATE, ph_model, ph_sw, OS);
  SendIq(to, IQTYPE_RES, id, IQ_VERSION, answer);

  mfree(id);
  mfree(to);
}

void Report_TimeInfo(char* id, char *to)
{
/*
  <utc>20070910T17:58:35</utc>
  <tz>MDT</tz>
  <display>Tue Sep 10 15:58:35 2007</display>");
*/
  char answer[200];
  TTime reqt;
  TDate reqd;
  const char *TimeZone[24]={"+00:00","+01:00","+02:00","+03:00","+04:00","+05:00","+06:00","+07:00","+08:00",
  "+09:00","+10:00","+11:00","+12:00","-01:00","-02:00","-03:00","-04:00","-05:00","-06:00","-07:00",
  "-08:00","-09:00","-10:00","-11:00"};
//  const signed int TimeZoneNum[24]={'0','1','2','3','4','5','6','7','8','9','10','11','12','-1','-2','-3','-4','-5','-6','-7','-8','-9','-10','-11'};
  extern const int MY_DEF_ZONE;
  char timzone[6];
  GetDateTime(&reqd, &reqt);
  strcpy(timzone, TimeZone[MY_DEF_ZONE]);
  sprintf(answer, "<utc>%04d%02d%02dT%02d:%02d:%02d</utc><tz>%s</tz><display>%02d-%02d-%04d %02d:%02d:%02d</display>",reqd.year,reqd.month,reqd.day,reqt.hour,reqt.min,reqt.sec, timzone,reqd.day,reqd.month,reqd.year,reqt.hour,reqt.min,reqt.sec);
  SendIq(to, IQTYPE_RES, id, IQ_TIME, answer);
  mfree(id);
  mfree(to);
};

void Report_IDLEInfo(char* id, char *to)
{
/*
   <iq from='' to='' id='' type=''>
    <query xmlns='jabber:iq:last' seconds=''/>
   </iq>
*/
  char* xmlql=malloc(1024);
  sprintf(xmlql, "<iq type='result' id='%s' from='%s' to='%s'>\r\n<query xmlns='jabber:iq:last' seconds='%d'/>\r\n</iq>", id, Mask_Special_Syms(My_JID_full), Mask_Special_Syms(to),GetIDLETime(intimes, indates));
  SendAnswer(xmlql);
  mfree(xmlql);
  mfree(to);
  mfree(id);
}

// Context: HELPER
void Report_DiscoInfo(char* id, char *to)
{
  char answer[400];
  sprintf(answer, "<identity category='client' type='mobile'/>"
                    "<feature var='%s'/>"
                    "<feature var='%s'/>"
                    "<feature var='%s'/>"
                    "<feature var='%s'/>"
                    "<feature var='%s'/>", DISCO_INFO, IQ_VERSION, XMLNS_MUC, IQ_TIME, IQ_IDLE);
  if(DELIVERY_EVENTS)
  {
    char xevents_feature[]="<feature var='"JABBER_X_EVENT"'/>";
    strcat(answer, xevents_feature);
  }
//  ShowMSG(0,(int)to);
  SendIq(to, IQTYPE_RES, id, DISCO_INFO, answer);

  mfree(id);
  mfree(to);
}

JABBER_SUBSCRIPTION GetSubscrType(char* subs)
{
  if(!subs)return SUB_NONE;
  if(!strcmp(subs,"none"))return SUB_NONE;
  if(!strcmp(subs,"both"))return SUB_BOTH;
  if(!strcmp(subs,"to"))return SUB_TO;
  if(!strcmp(subs,"from"))return SUB_FROM;

  return SUB_NONE;
}

char* Get_Resource_Name_By_FullJID(char* full_jid)
{
  char* pre_res = strstr(full_jid, "/");
  char* res_name = pre_res==NULL ? NULL : pre_res +1;
  return res_name;
}

//Context: HELPER
void Send_Initial_Presence_Helper()
{
//  OnlineInfo
//  char *message = ANSI2UTF8(ansi_msg, strlen(ansi_msg));
  PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
  pr_info->priority = OnlineInfo.priority;
  pr_info->status=OnlineInfo.status;
  /*if(OnlineInfo.txt)
  {
    pr_info->message = malloc(strlen(OnlineInfo.txt)+1);
    strcpy(pr_info->message,OnlineInfo.txt);
  }else pr_info->message = NULL;*/
  WSHDR *ws = AllocWS(256);
  char *msg = malloc(256);
  int len;
  extern const char DEFTEX_ONLINE[256];
  extern const char percent_t[];
  wsprintf(ws, percent_t, DEFTEX_ONLINE);
  ws_2utf8(ws, msg, &len, wstrlen(ws)*2+1);
  msg = realloc(msg, len+1);
  msg[len]='\0';
  pr_info->message=msg;
  Send_Presence(pr_info);
  Jabber_state = JS_ONLINE;
}

//Context: HELPER
void _enterconference(MUC_ENTER_PARAM *param)
{
  char *magic_ex = malloc(1024);
  strcpy(magic_ex, "<presence from='%s' to='%s/%s'><x xmlns='http://jabber.org/protocol/muc'><history maxstanzas='%d'/>");
  if(param->pass)
  {
    char *_room_pass = Mask_Special_Syms(param->pass);
    char *pass_str = malloc(128);
    sprintf(pass_str,"<password>%s</password>", _room_pass);
    strcat(magic_ex, pass_str);
    mfree(pass_str);
    mfree(_room_pass);
  }
  strcat(magic_ex, "</x><show>%s</show><status>%s</status></presence>");
  char* magic = malloc(1024);
  char *stext;
  extern char empty_str[];
  if(OnlineInfo.txt){stext= OnlineInfo.txt;}else{stext = empty_str;}
  char *_from = Mask_Special_Syms(My_JID_full);
  char *_room_name = Mask_Special_Syms(param->room_name);
  char *_room_nick = Mask_Special_Syms(param->room_nick);
  sprintf(magic,magic_ex, _from, _room_name,_room_nick, param->mess_num, PRESENCES[OnlineInfo.status], stext);
  mfree(_from);
  mfree(_room_name);
  mfree(_room_nick);
  mfree(magic_ex);
  SendAnswer(magic);
  mfree(magic);
  mfree(param->room_nick);
  mfree(param->room_name);
  if(param->pass)mfree(param->pass);
  mfree(param);
}


// ������ � �����������
// ��� ����� � UTF-8 :)
void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages)
{

  // �������, ���� �� ����� ����� � ������ �����������
  // ���� ����, ����� �� ������ ������ �������� ��� � ���
  char IsAlreadyInList = 0;
  MUC_ITEM* m_ex = muctop;
  if(muctop)
  {
    while(m_ex)
    {
      if(stristr(m_ex->conf_jid, room)==m_ex->conf_jid)
      {
        IsAlreadyInList=1;
        break;
      }
      m_ex=m_ex->next;
    };
  }

  if(!IsAlreadyInList)
  {
    // ��������� ������� ����������� � ������
    CLIST* Conference = CList_FindContactByJID(room);
    if(!Conference)
    {
      CList_AddContact(room,room, SUB_BOTH, 0, 129);
    }
//    else  // ����� ����� �������� �� ����������� �����/������
//    {
//      Conference->res_list->status=PRESENCE_ONLINE;
//    }
  }
  // ������� ��������� ��� �������� � HELPER
  MUC_ENTER_PARAM* par = malloc(sizeof(MUC_ENTER_PARAM));
//  par->room_nick =ANSI2UTF8(roomnick, strlen(roomnick)*2);
//  par->room_name = ANSI2UTF8(room, strlen(room)*2);

  par->room_nick =malloc(strlen(roomnick)*2);
  par->room_name = malloc(strlen(room)*2);
  strcpy(par->room_nick, roomnick);
  strcpy(par->room_name, room);
  if(roompass)
  {
    par->pass = malloc(strlen(roompass)*2);
    strcpy(par->pass, roompass);
  }
  else par->pass = NULL;
  
  if(!IsAlreadyInList)
  {
    par->mess_num=N_messages;
  }
  else par->mess_num=0;   // ��� ��� ��� ����������� �������
  SUBPROC((void*)_enterconference, par);

  if(!IsAlreadyInList)
  {
    // ������������ ����������� � ������ �����������
    MUC_ITEM* mi = malloc(sizeof(MUC_ITEM));
    mi->conf_jid = malloc(strlen(par->room_name)*2+strlen(par->room_nick)*2+2);
    sprintf(mi->conf_jid, "%s/%s", par->room_name, par->room_nick);
    mi->muctema=NULL;
    mi->next=NULL;
    m_ex = muctop;
    if(muctop)
    {
      while(m_ex->next){m_ex=m_ex->next;};
      m_ex->next = mi;
    }
    else
    {
      muctop = mi;
    }
  }
  else
  {
    // m_ex - ������� �������
    int len = strlen(par->room_name)+strlen(par->room_nick)+2;
    m_ex->conf_jid = realloc(m_ex->conf_jid, len);
    snprintf(m_ex->conf_jid, len, "%s/%s", par->room_name, par->room_nick);
  }
}


//Context: HELPER
void _leaveconference(char *conf_jid)
{
  extern const char DEFTEX_MUCOFFLINE[];
  if(strlen(DEFTEX_MUCOFFLINE))
  {
  char pr_templ[] = "<presence from='%s' to='%s' type='unavailable'><status>%s</status></presence>";
  char* pr=malloc(1024);
  char *msg = malloc(256);
  WSHDR *ws = AllocWS(256);
  int len;
  wsprintf(ws, percent_t, DEFTEX_MUCOFFLINE);
  ws_2utf8(ws, msg, &len, wstrlen(ws)*2+1);
  msg=realloc(msg, len+1);
  msg[len]='\0';
  sprintf(pr, pr_templ, Mask_Special_Syms(My_JID_full), Mask_Special_Syms(conf_jid), Mask_Special_Syms(msg));
  SendAnswer(pr);
  FreeWS(ws);
  mfree(msg);
  mfree(pr);
  } else Send_ShortPresence(conf_jid,PRESENCE_OFFLINE);
  mfree(conf_jid);
}

// ������� �� �����������
void Send_Leave_Conference(char* room)
{
      char* cj = malloc(strlen(room)*2+1);
      strcpy(cj, room);
      SUBPROC((void*)_leaveconference, cj);
}

void Leave_Conference(char* room)
{
  // ���� ��������� �������� � ������ ��� �����������
  MUC_ITEM* m_ex = CList_FindMUCByJID(room);

  MUC_ITEM* m_ex2 = muctop;
  if(muctop==m_ex && muctop!=NULL)
  {
    mfree(m_ex->conf_jid);
    if(m_ex->muctema)mfree(m_ex->muctema);
    muctop=m_ex->next;
    mfree(m_ex);
  }
  while(m_ex2)
  {
    if(m_ex2->next==m_ex)
    {
      m_ex2->next = m_ex->next;   // �������� �� �������
      mfree(m_ex->conf_jid);
      mfree(m_ex);
      break;
    }
    m_ex2 = m_ex2->next;
  }
  ShowMSG(1,(int)LG_MUCEXITDONE);
}


// ���������� ������ ������
void MUCList_Destroy()
{
  LockSched();
  MUC_ITEM* cl=muctop;
  muctop=NULL;
  while(cl)
  {
    MUC_ITEM *p;
    mfree(cl->conf_jid);
    if(cl->muctema)mfree(cl->muctema);
    p=cl;
    cl=(MUC_ITEM*)(cl->next);
    mfree(p);
    p=NULL;
  }
  UnlockSched();
}



// ��� ������ ��������
void Send_Presence_MMIStub()
{
  SUBPROC((void*)Send_Initial_Presence_Helper);
}


// �������� ��� �������� � �������
void ChangeRoster(XMLNode* items)
{
  XMLNode* rostEx = items;
  CLIST* Cont_Ex;
  char *name;
  char* w_subscr;
  char aname[]="jid";  // ��������� Tool Internal Error
  char asub[]="subscribe";
  char aask[]="ask";
  char* jid;
  int gr_id;
  char w_subscr_flag;
  while(rostEx)
  {
    jid = XML_Get_Attr_Value(aname,rostEx->attr);
    JABBER_SUBSCRIPTION r_subscr=GetSubscrType(XML_Get_Attr_Value("subscription",rostEx->attr));
    name = XML_Get_Attr_Value("name",rostEx->attr);
    w_subscr = XML_Get_Attr_Value(aask,rostEx->attr);
    if(w_subscr)
    {
      w_subscr_flag = !strcmp(w_subscr, asub) ? 1: 0;
    }
    else
    {
      w_subscr_flag = 0;
    }
    XMLNode *group = XML_Get_Child_Node_By_Name(rostEx, "group");
    if(group)
    {
      if(!(gr_id = GetGroupID(group->value)))
      {
        gr_id = AddGroup(group->value);
      }
    }
    else gr_id = 0;
    Cont_Ex = CList_FindContactByJID(jid);
    if(Cont_Ex)
    {
      CList_ChangeContactParams(Cont_Ex,name,r_subscr, w_subscr_flag,gr_id);
    }
    else
    { //���� �������� ���� ���� �������� ��� � �����������.
     CList_AddContact(jid, name,r_subscr, w_subscr_flag, gr_id);
    }
    rostEx=rostEx->next;
  }
}

void FillRoster(XMLNode* items)
{
  XMLNode* rostEx = items;
  int i=0;
  char* name;
  char* w_subscr;
  char w_subscr_flag;
  while(rostEx)
  {
    JABBER_SUBSCRIPTION r_subscr=GetSubscrType(XML_Get_Attr_Value("subscription",rostEx->attr));
    name = XML_Get_Attr_Value("name",rostEx->attr);
    w_subscr = XML_Get_Attr_Value("ask",rostEx->attr);
    if(w_subscr)
    {
      w_subscr_flag = !strcmp(w_subscr, "subscribe") ? 1: 0;
    }
    else
    {
      w_subscr_flag = 0;
    }
    // �������� ������ ��������, ������� � ������ �����
    XMLNode *group = XML_Get_Child_Node_By_Name(rostEx, "group");
    int gr_id;
    if(group)
    {
      if(!(gr_id = GetGroupID(group->value)))
      {
        gr_id = AddGroup(group->value);
      }
    }
    else gr_id = 0;

    CList_AddContact(XML_Get_Attr_Value("jid",rostEx->attr),
                          name,
                          r_subscr,
                          w_subscr_flag,
                          gr_id
                          );
   //if(name)mfree(name);

   rostEx=rostEx->next;
   i++;
  }

  // ��������� ������� ���������. ��������� ������
  GR_ITEM *tmp_gpointer=GR_ROOT;
  CLIST *tmp_cpointer=cltop;
  int cur_gid=-1, this_grid;   // ������� �������������� GID


  // ���� �� ���� ���������
  while(tmp_cpointer->next)
  {
    this_grid = ((CLIST*)tmp_cpointer->next)->group;
    // �������� ������� ������
    if(cur_gid!=this_grid)
    {
      tmp_gpointer = GetGroupByID(this_grid);
      cur_gid = this_grid;
      // ������ �������������, ��������� ���
      CLIST *gr_pscontact = malloc(sizeof(CLIST));
      gr_pscontact->name = malloc(strlen(tmp_gpointer->name)+1);
      gr_pscontact->JID = malloc(strlen(tmp_gpointer->name)+2+(strlen(My_JID_full)));
      strcpy(gr_pscontact->name, tmp_gpointer->name);
      strcpy(gr_pscontact->JID, tmp_gpointer->name);
      strcat(gr_pscontact->JID, "@"); //�������� ������ �������������� JID, ���� �� ������� � �����.
      strcat(gr_pscontact->JID, My_JID_full);//�� ������ � ������� ������ ���������
      gr_pscontact->subscription = SUB_BOTH;
      gr_pscontact->wants_subscription = 0;
      gr_pscontact->group = cur_gid;
      gr_pscontact->IsVisible = 1;
      gr_pscontact->ResourceCount=1;
      gr_pscontact->next=tmp_cpointer->next;  // ��������� ����� ������� � ���������
      gr_pscontact->vcard=NULL; //� ������ ��� vCard. � ������� �� �����.
      tmp_cpointer->next = gr_pscontact;

      // C����� ��� � ������������
      TRESOURCE* ResEx = malloc(sizeof(TRESOURCE));
      ResEx->vcard = NULL;
      ResEx->log=NULL;
      ResEx->next=NULL;
      ResEx->status_msg=NULL;
      ResEx->muc_privs.real_jid=NULL;
      ResEx->status = PRESENCE_ONLINE;
      ResEx->has_unread_msg=0;
      ResEx->total_msg_count=0;
      ResEx->entry_type=T_GROUP;
      ResEx->name = NULL;
      ResEx->full_name = malloc(strlen(tmp_gpointer->name)+2+(strlen(My_JID_full)));
      strcpy(ResEx->full_name, tmp_gpointer->name);
      strcat(ResEx->full_name, "@");
      strcat(ResEx->full_name, My_JID_full);
      // ��������� ������ � ������
      gr_pscontact->res_list = ResEx;
      NContacts++;
      tmp_cpointer = tmp_cpointer->next;
    }
    tmp_cpointer = tmp_cpointer->next;
  }

}

/*
<iq from='siepatchdb@conference.jabber.ru/Adder' to='kibab612@jabber.ru/SieJC' id='stoat_173' type='get'>
  <query xmlns='jabber:iq:time'/>
</iq>
*/

/*
  <iq to='sender' type='error'>
  <error type='cancel'>
    <feature-not-implemented xmlns='urn:ietf:params:xml:ns:xmpp-stanzas'/>
  </error>
  </iq>
*/


void Send_Feature_Not_Implemented(char *to, char *id)
{
  if(!to || !id)return;
  char err_tpl[]="<iq to='%s' id='%s' type='error'>"
                 "<error type='cancel'>"
                    "<feature-not-implemented xmlns='urn:ietf:params:xml:ns:xmpp-stanzas'/>"
                  "</error>"
                 "</iq>";
  char *m=malloc(1024);
  zeromem(m,1024);
  snprintf(m,1023,err_tpl,to,id);
  SUBPROC((void*)_sendandfree,m);
}

/*
 ��������� �������� Iq-��������
*/
void Process_Iq_Request(XMLNode* nodeEx)
{
  char* iqtype = NULL;
  char* id = NULL;
  char *from = NULL;
  char gget[]=IQTYPE_GET;
  char gres[]=IQTYPE_RES;
  char gerr[]=IQTYPE_ERR;
  char gset[]=IQTYPE_SET;
  const char iq_version[]=IQ_VERSION;
  const char disco_info[]=DISCO_INFO;

  iqtype = XML_Get_Attr_Value("type",nodeEx->attr);
  from = XML_Get_Attr_Value("from",nodeEx->attr);
  id = XML_Get_Attr_Value("id",nodeEx->attr);

// ��������� ������� ������������ ���������
if(!iqtype) return;

if(!strcmp(gget,iqtype)) // Iq type = get
{
  XMLNode* query;
  if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
  char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
  if(!q_type)return;
  // ��� �� ����� XMLNS ������������ �������
  if(!strcmp(q_type,iq_version))
  {
    // jabber:iq:version
    if(from)
    {
        // ������� ����������, ����� � ��� �������� ������
        // � ��������� ���������� � HELPER

      char* loc_id = NULL;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_VersionInfo,loc_id, loc_from);
        return;
    }
  } //end version

  if(!strcmp(q_type,IQ_TIME))
  {
    // jabber:iq:time
    if(from)
    {
        // ������� ����������, ����� � ��� �������� ������
        // � ��������� ���������� � HELPER

      char* loc_id = NULL;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_TimeInfo,loc_id, loc_from);
        return;
    }
  }

  if(!strcmp(q_type,IQ_IDLE))    // jabber:iq:last
  {
    if(from)
    {
      char* loc_id = NULL;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_IDLEInfo, loc_id, loc_from);
        return;
    }
  } //end jabber:iq:last

  //entity caps
  if(!strcmp(q_type,disco_info))
  {
    // http://jabber.org/protocol/disco#info
    if(from)
    {
        // ������� ����������, ����� � ��� �������� ������
        // � ��������� ���������� � HELPER

      char* loc_id = NULL;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_DiscoInfo,loc_id, loc_from);
        return;
    }
  }

  // �� ���� ���������� �� �������, ���������� ������.
  Send_Feature_Not_Implemented(from, id);
}


// ���������  Iq type = result
if(!strcmp(gres,iqtype))
{
  char bind_id[]="SieJC_bind_req";
  char sess_id[]="SieJC_sess_req";
  char disco_id[]="SieJC_discoinfo";

  if(!strcmp(id, bind_id))
  {
    Jabber_state = JS_SASL_SESS_INIT_ACK;
    SASL_Init_Session();
    return;
  }

  if(!strcmp(id,auth_id) || !strcmp(id, sess_id))   // ����������� ���� ����� ������������� ������
  {
    Jabber_state = JS_AUTH_OK;
    if(!cltop)
    {
      CList_AddContact(My_JID, "(Me)", SUB_BOTH,0,0);
      SUBPROC((void*)Send_Roster_Query);
    }
    else Send_Presence_MMIStub();
    return;
  }

  if(!strcmp(id,rost_id))   // ������ �������
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_ROSTER))
    {
      // jabber:iq:roster
      FillRoster(query->subnode);
        // ����� ������� �������� ��������
      extern GBSTMR TMR_Send_Presence;
      GBS_StartTimerProc(&TMR_Send_Presence, TMR_SECOND*1, Send_Presence_MMIStub);
      return;
    }
  }

  if(!strcmp(id,vreq_id))   // ������ ������ (�����)
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_VERSION))
    {
      char no_os[]="(no data)";
      char* vers_os_str;
      XMLNode *cl_name=XML_Get_Child_Node_By_Name(query, "name");
      XMLNode *cl_version=XML_Get_Child_Node_By_Name(query, "version");
      XMLNode *cl_os=XML_Get_Child_Node_By_Name(query, "os");
      if(cl_os)
      {
        vers_os_str = cl_os->value;
      }
      else
      {
        vers_os_str=no_os;
      }
      //��������� ���������
      char *reply=malloc(512);
      snprintf(reply, 512,LG_VERINFO,cl_name->value, cl_version->value, vers_os_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      ShowMSG(0,(int)reply);
      mfree(reply);
      return;
    }
  }

    if(!strcmp(id,lastact_id))   // ������ IDLE (�����)
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_IDLE))
    {
      char *cl_sec=XML_Get_Attr_Value("seconds", query->attr);
      //��������� ���������
      char *reply=malloc(512);
      unsigned int nsec, nmin, nhr, nd;
      nsec = strtoul(cl_sec, &cl_sec, 10);
      nmin = udiv(60, nsec);
      nsec -= nmin*60;
      nhr = udiv(60, nmin);
      nmin -= nhr*60;
      nd = udiv(24, nhr);
      nhr -= nd*24;
      snprintf(reply, 512,LG_LASTACTIVMSG, nd, nhr, nmin, nsec);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      ShowMSG(0,(int)reply);
      mfree(reply);
      return;
    }
  }//end lastactiv

    if(!strcmp(id,treq_id))   // ������ TIME (�����)
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_TIME))
    {
      char no_display[]="(no data)";
      char* display_str;
      char* tz_str;
      XMLNode *cl_utc=XML_Get_Child_Node_By_Name(query, "utc");
      XMLNode *cl_tz=XML_Get_Child_Node_By_Name(query, "tz");
      XMLNode *cl_display=XML_Get_Child_Node_By_Name(query, "display");
      if(cl_display)
      {
        display_str = cl_display->value;
      }
      else
      {
        display_str=no_display;
      }
      if(cl_tz)
      {
        tz_str = cl_tz->value;
      }
      else
      {
        tz_str=no_display;
      }
      //��������� ���������
      char *reply=malloc(512);
      snprintf(reply, 512,LG_TIMEINFO,cl_utc->value, tz_str, display_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      ShowMSG(0,(int)reply);
      mfree(reply);
      return;
    }
  }
  if(!strcmp(id,vcreq_id))   // ������ vcard (�����)
  {
    XMLNode* vcard;
    if(!(vcard = XML_Get_Child_Node_By_Name(nodeEx, "vCard")))return;
    char* v_type = XML_Get_Attr_Value("xmlns", vcard->attr);
    if(!v_type)return;
    if(!strcmp(v_type,"vcard-temp"))Process_vCard(from, vcard);
  }
/////////////////
  if(!strcmp(id,disco_id))   // ������ ����� (�����)
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,DISCO_INFO))
    {
      Disp_From_Disco(from, query);
    }
  }
/////////////////
  if(!strcmp(id,priv_id))
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_PRIVATE))
    {
      XMLNode *bm = XML_Get_Child_Node_By_Name(query, "storage");
      if(!bm)return;
      char *xmlns = XML_Get_Attr_Value("xmlns", bm->attr);
      if(!xmlns)return;
      if(!strcmp(xmlns, XMLNS_BOOKMARKS))Process_Bookmarks_Storage(bm);
      return;
    }
  }
}
// ���������  Iq type = set
if(!strcmp(gset,iqtype))
{
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;

    if(!strcmp(q_type,IQ_ROSTER))
    {
      // jabber:iq:roster
      ChangeRoster(query->subnode);
      return;
    }
}

if(!strcmp(gerr,iqtype)) // Iq type = error
{

  // ����������� ������
  XMLNode* error = XML_Get_Child_Node_By_Name(nodeEx, "error");
  if(!error)return;
  char* errcode = XML_Get_Attr_Value("code", error->attr);
//  Jabber_state = JS_ERROR;
  if(errcode)sprintf(logmsg,"ERR:%s",errcode);
  MsgBoxError(1,(int)logmsg);
  if(!strcmp(id,auth_id))
  {
    Jabber_state = JS_AUTH_ERROR;
    strcat(logmsg,"\nAuth error!");
    extern void end_socket(void);
    SUBPROC((void*)end_socket);
  }
}
}
/*
�������� :)
*/
void Process_Presence_Change(XMLNode* node)
 {
  // ��� ������
char loc_actor[]="actor";
char loc_jid[]="jid";
char loc_reason[]="reason";
char loc_xmlns[]="xmlns";
char loc_x[]="x";
short priority = 0;

  CONF_DATA priv;
  char Req_Set_Role=0;
  char *real_jid = NULL;
  char* from = XML_Get_Attr_Value("from",node->attr);
  if(!from)return;

  char status;
  char* msg=NULL;
  char* pr_type = XML_Get_Attr_Value("type",node->attr);
  if(pr_type)
  {
    status = GetPresenceIndex(pr_type);
  }
  else
  {
    XMLNode* status_node = XML_Get_Child_Node_By_Name(node,"show");
    if(!status_node)
    {
      status = PRESENCE_ONLINE;
      extern const char sndOnline[64];
      //Play(sndOnline);
      SUBPROC((void *)Play, sndOnline);
    }
    else
    {
      status = GetPresenceIndex(status_node->value);
    }

    XMLNode* statusmsg_node = XML_Get_Child_Node_By_Name(node,"status");
    if(statusmsg_node)msg = statusmsg_node->value;

    XMLNode* prio_node = XML_Get_Child_Node_By_Name(node,"priority");
    extern long  strtol (const char *nptr,char **endptr,int base);
    if(prio_node)priority = strtol (prio_node->value,0,10);
  }

   // ��������������� ������, ��� ������� ��� ���-�� �� �����������. ��� �����.
   XMLNode *x_node;

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, XMLNS_MUC)) // ������� �� �����������
    {
      CLIST* Conference = CList_FindContactByJID(from);
      // �������� �������� ���� error (��� �������� �� ��������� ������ ������)
      XMLNode* err_node = XML_Get_Child_Node_By_Name(node,"error");
      if(err_node)  // ���� ������!
      {
        // ���� ����� ������
        XMLNode* err_desc = XML_Get_Child_Node_By_Name(err_node,"text");
        if(err_desc)
        {
          if(err_desc->value)msg = err_desc->value;
          MsgBoxError(1,(int)err_desc->value);
          CList_AddSystemMessage(Conference->JID,PRESENCE_OFFLINE, err_desc->value);
        }
        else
        {
          char q[40];
          char *code = XML_Get_Attr_Value("code",err_node->attr);
          sprintf(q,"ERR %d",code);
          MsgBoxError(1,(int)q);
        }
      }
    }


#define MAX_STATUS_LEN 512
static char r[MAX_STATUS_LEN];       // ������, ����� �� ����� � ��� ���������� ���������

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, XMLNS_MUC_USER)) // ������� �� ����������� � ������������
    {

      // ������� ��������� �����, � ������� �� ����������
      CLIST* Conference = CList_FindContactByJID(from);
      if(!Conference)
      {
        return;
      }
      char* nick = Get_Resource_Name_By_FullJID(from);

      // ��� ����� ������������ ������� �����/������ � �����
      // ��� ����������, ��� ����� (����� ��, �����...)
      XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
      if(status!=PRESENCE_OFFLINE) // ���� � ����� ��������
      {
        TRESOURCE* ResEx = CList_IsResourceInList(from);
        char* affiliation = XML_Get_Attr_Value("affiliation", item->attr);
        char* role =  XML_Get_Attr_Value("role", item->attr);
        real_jid = XML_Get_Attr_Value(loc_jid, item->attr);
        priv.aff = (JABBER_GC_AFFILIATION)GetAffRoleIndex(affiliation);
        priv.role = (JABBER_GC_ROLE)GetAffRoleIndex(role);

        if(ResEx)
        {

        if(ResEx->status!=PRESENCE_OFFLINE)
        {
          if(!(ResEx->muc_privs.aff==priv.aff && ResEx->muc_privs.role==priv.role))
          {
            sprintf(r, "%s is now %s and %s [%d->%d, %d->%d]", nick, affiliation, role, ResEx->muc_privs.aff, priv.aff, ResEx->muc_privs.role, priv.role);
            Req_Set_Role = 1;
          }
          else
          {
            if(msg)
            {
              snprintf(r, MAX_STATUS_LEN, "%s changed status to %s (%s)", nick, PRESENCES[status], msg);
            }
            else
            {
              sprintf(r, "%s changed status to %s", nick, PRESENCES[status]);
            }
          }
        }
        else if(real_jid)  //���� ����� �������� jid, ������� ���
        {
          sprintf(r, "%s (%s) joined as %s and %s", nick, real_jid, affiliation, role);
          Req_Set_Role = 1;
        }
        else
          sprintf(r, "%s joined as %s and %s", nick, affiliation, role);
          Req_Set_Role = 1;

        }
        else 
        {
          if(real_jid)
        {
          sprintf(r, "%s (%s) joined as %s and %s", nick, real_jid, affiliation, role);
          Req_Set_Role = 1;
        }
        else
        {
          sprintf(r, "%s joined as %s and %s", nick, affiliation, role);
          Req_Set_Role = 1;
        }
        };

        char* my_nick = Get_Resource_Name_By_FullJID(CList_FindMUCByJID(Conference->JID)->conf_jid);
        if ((!strcmp(nick,my_nick))&&(Conference->res_list->status==PRESENCE_OFFLINE)) //���� ��� ��, ������ � ���.
        {
          Conference->res_list->status=PRESENCE_ONLINE;
          ShowMSG(1,(int)LG_MUCCROK);
        };
        CList_AddSystemMessage(Conference->JID,PRESENCE_ONLINE, r);
      }


      if(status==PRESENCE_OFFLINE) // �����
      {
        XMLNode* statusmsg_node = XML_Get_Child_Node_By_Name(node,"status");
        if (!statusmsg_node)
          sprintf(r, "%s left us", nick);
        else 
        {
         if(statusmsg_node->value) sprintf(r, "%s left us (%s)", nick, statusmsg_node->value);
         else sprintf(r, "%s left us", nick);
        }

        char* my_nick = Get_Resource_Name_By_FullJID(CList_FindMUCByJID(Conference->JID)->conf_jid);
        if (!strcmp(nick,my_nick)) //���� ��� ��, ������� �����.
        {
          Leave_Conference(Conference->JID);
          CList_MakeAllResourcesOFFLINE(Conference);
        };
        extern const char sndOffline[64];
        //Play(sndOffline);
        SUBPROC((void *)Play, sndOffline);
        CList_AddSystemMessage(Conference->JID,PRESENCE_OFFLINE, r);
        priv.role = ROLE_NONE;
        priv.aff  = AFFILIATION_NONE;
        Req_Set_Role = 1;
      }


      // �������� �������� ���� �������
      XMLNode* sstatus = XML_Get_Child_Node_By_Name(x_node,"status");
      if(sstatus)  // ���� ������!
      {
        // �������� ��� �������
        char* st_code=XML_Get_Attr_Value("code", sstatus->attr);
        sprintf(r,"%s - [Unknown action]",nick);
        // ������ ���� �������� - ������ �������:)
        if(!strcmp(st_code, MUCST_KICKED)) sprintf(r, MUCST_R_KICK,nick); // ��������� � ����
        if(!strcmp(st_code, MUCST_BANNED)) sprintf(r, MUCST_R_BAN, nick); // ��������� � ����
        if(!strcmp(st_code, MUCST_KICKED_MEMB_ONLY)) sprintf(r, MUCST_R_KICK_MEMB_ONLY, nick); // ��������� � ���� �� ������-���� ����
        if(!strcmp(st_code, MUCST_CHNICK)) sprintf(r, MUCST_R_CHNICK, nick,  XML_Get_Attr_Value("nick", item->attr)); // ��������� � ����� ����
        //sprintf(r,r,nick);

        XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
        if(item)
        {
          XMLNode* actor = XML_Get_Child_Node_By_Name(item,loc_actor); // ����� ������ ��� ��������� �������, ��� �������� �����������
          if(actor)strcat(r, XML_Get_Attr_Value(loc_jid, actor->attr));

          XMLNode* reason = XML_Get_Child_Node_By_Name(item,loc_reason); // � ����� ��� ���� �������, �� ���?
          if(reason)
          {
            strcat(r, "; Reason: ");
            int l = strlen(r);
            if(MAX_STATUS_LEN-l-1>0)strncat(r, reason->value, MAX_STATUS_LEN-l-1);
          }


        }
        char *ansi_r = convUTF8_to_ANSI_STR(r);
        MsgBoxError(1,(int)ansi_r);
        mfree(ansi_r);
        CList_AddSystemMessage(Conference->JID,status, r);
        msg = r;
      }

    }

  TRESOURCE *ResEx = CList_AddResourceWithPresence(from, status, msg, priority);
  if(Req_Set_Role) CList_MUC_SetRole(from, priv);
  if(real_jid)
  {
    ResEx->muc_privs.real_jid = malloc(strlen(real_jid)+1);
    strcpy(ResEx->muc_privs.real_jid, real_jid);
  }
}

MESS_TYPE Get_Message_Type(char* mess_type_str)
{
  char m_chat[]=MSGSTR_CHAT;
  char m_gchat[]=MSGSTR_GCHAT;
  if(!mess_type_str)return MSG_NORMAL;
  if(!strcmp(mess_type_str,m_chat ))return MSG_CHAT;
  if(!strcmp(mess_type_str,m_gchat ))return MSG_GCHAT;
  return MSG_NORMAL;
}

//Context: HELPER
void _mucadmincmd(char* room, char* iq_payload)
{
  //char* to, char* type, char* id, char* xmlns, char* payload
  char admin_iqid[]="SieJC_adm";
  char iqtypeset[]=IQTYPE_SET;
  SendIq(room, iqtypeset, admin_iqid, XMLNS_MUC_ADMIN, iq_payload);
  mfree(iq_payload);
  mfree(room);
}

// ���������� ���������������� ������
void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason)
{
  char* payload = malloc(1024);
  char *_room_name = Mask_Special_Syms(room_name);
  char payload_tpl[]="<item nick='%s' %s='%s'><reason>%s</reason></item>";
  char it[20];
  char val[20];
  char aff[]="affiliation";
  char role[]="role";
  switch(cmd)
  {
  case ADM_KICK:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_NONE]);
      break;
    }
  case ADM_VOICE_REMOVE:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_VISITOR]);
      break;
    }
  case ADM_VOICE_GRANT:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_PARTICIPANT]);
      break;
    }

  case ADM_PARTICIPANT:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_NONE]);
      break;
    }

  case ADM_MEMBER:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_MEMBER]);
      break;
    }

  case ADM_MODERATOR:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_MODERATOR]);
      break;
    }
 case ADM_MODERATOR_REMOVE:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_PARTICIPANT]);
      break;
    }

  case ADM_ADMIN:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_ADMIN]);
      break;
    }

  case ADM_OWNER:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_OWNER]);
      break;
    }

  case ADM_BAN:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_OUTCAST]);
      break;
    }

  }

  char *_room_jid = Mask_Special_Syms(room_jid);
  snprintf(payload, 1023, payload_tpl, _room_jid, it, val, reason);
  mfree(_room_jid);
  SUBPROC((void*)_mucadmincmd, _room_name, payload);
}

static void Report_Delivery(char *mess_id, char *to)
{
/*
RECV: <message
          from='romeo@montague.net/orchard'
          to='juliet@capulet.com/balcony'>
      <x xmlns='jabber:x:event'>
        <delivered/>
        <id>message22</id>
      </x>
    </message>
*/
  char notif_tpl[]="<message to='%s'><x xmlns='jabber:x:event'><id>%s</id><delivered/></x></message>";
  char *ans = malloc(256);
  snprintf(ans,256,notif_tpl, Mask_Special_Syms(to), mess_id);
  SUBPROC((void*)_sendandfree,ans);
}

/*
�������� ���������
*/
void Process_Incoming_Message(XMLNode* nodeEx)
{
  char Is_subj=0;
  char from[]="from";
  char c_xmlns[]="xmlns";
  char c_id[]="id";

  // ���� �������� ������������ �������� � ���������...
  {
    XMLNode* xnode = XML_Get_Child_Node_By_Name(nodeEx,"x");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      {
      if(!strcmp(xmlns,JABBER_X_EVENT))
      {
        // �������� <x xmlns='jabber:x:event'>
        // ��������� <delivered/>, ��� �� ����� ������ ������
        TRESOURCE* Res_ex = CList_IsResourceInList(XML_Get_Attr_Value(from,nodeEx->attr));
        XMLNode *delivery = XML_Get_Child_Node_By_Name(xnode,"delivered");
        if((delivery)&&(DELIVERY_EVENTS)) //��������
        {
          // �������� ID ���������
          char *id = XML_Get_Attr_Value(c_id, nodeEx->attr);
          if(id)Report_Delivery(id, XML_Get_Attr_Value(from,nodeEx->attr));
        }
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE)) //composing
        {
        delivery = XML_Get_Child_Node_By_Name(xnode,"composing");
        if(delivery) CList_ChangeComposingStatus(Res_ex, 1);
        else CList_ChangeComposingStatus(Res_ex, 0);
        }
      }

      if(!strcmp(xmlns,XMLNS_MUC_USER)) //��������� invite
      {
       XMLNode *invite =  XML_Get_Child_Node_By_Name(xnode,"invite");
       if(invite)
       {
        MUC_ITEM* muct = CList_FindMUCByJID(XML_Get_Attr_Value(from,nodeEx->attr)); 
        if(!muct) //���� ��� ����� ����� ����� �� ������� � ������ muctop, � ����� ������
        {
          
          CList_AddContact(XML_Get_Attr_Value(from,nodeEx->attr),XML_Get_Attr_Value(from,nodeEx->attr), SUB_BOTH, 0, 129);
          
        }
       }
      }
      }
    }
  }

  XMLNode* msgnode = XML_Get_Child_Node_By_Name(nodeEx,"body");
  XMLNode* msgnodes = XML_Get_Child_Node_By_Name(nodeEx,"subject");  
  if(!msgnode)
  {
    msgnode = msgnodes;
    Is_subj = 1;
  }
  if(msgnodes) //���� ���� ����, ����������...
  {
    MUC_ITEM* TmpMUC = CList_FindMUCByJID(CList_FindContactByJID(XML_Get_Attr_Value(from,nodeEx->attr))->JID);
      if(TmpMUC)
      {
       if(TmpMUC->muctema) mfree(TmpMUC->muctema);
       TmpMUC->muctema = malloc(strlen(msgnodes->value)*2+1);
       strcpy(TmpMUC->muctema ,msgnodes->value);
      }
  }
  if(msgnode)
  if(msgnode->value)
  {
    MESS_TYPE msgtype = Get_Message_Type(XML_Get_Attr_Value("type",nodeEx->attr));

    // �� ���������� ������ ��� ��������, ��� ������ ������� ���
    if(msgtype!=MSG_GCHAT)
    {
      if(DISPLAY_POPUPS)
      {
        char* m = malloc(128+5+strlen(msgnode->value));
        sprintf(m,"%s: %s", XML_Get_Attr_Value(from,nodeEx->attr), msgnode->value);
        //char *ansi_m=convUTF8_to_ANSI_STR(m);
        char *ansi_m = m;
        utf82win(ansi_m, ansi_m);
        ShowMSG(1,(int)ansi_m);
        mfree(m);
        //mfree(ansi_m);
      }
      extern const char sndPM[];
      SUBPROC((void *)Play,sndPM);
    }
      else
        {
          extern const char sndConf[];
          SUBPROC((void *)Play,sndConf);
        }
    if(Is_subj)
    {
      msgtype = MSG_SUBJECT;
    }
    CList_AddMessage(XML_Get_Attr_Value(from,nodeEx->attr), msgtype, msgnode->value);

    extern volatile int vibra_count;
    Vibrate(1);
  }
}

/*
�������� ���������� ����� ������� ���� ����������� �� ������ � �����������
*/
unsigned short GetPresenceIndex(char* presence_str)
{
  if(!presence_str)return 0;
  for(int i=0;i<PRES_COUNT;i++)
  {
    if(!strcmp(presence_str, PRESENCES[i]))return i;
  }
  return 0;
}

/*
�������� ���������� ����� ������� ���� ����/���������� �� ������ � �����������
*/
unsigned short GetAffRoleIndex(char* str)
{
  if(!str)return 0;
  int i;
  for(i=0;i<AFFS_CNT;i++)
  {
    if(!strcmp(str, JABBER_AFFS[i]))return i;
  }
  for(i=0;i<ROLS_CNT;i++)
  {
    if(!strcmp(str, JABBER_ROLS[i]))return i;
  }

  return 0;
}


//Context:HELPER
void _sendandfree(char *str)
{
  SendAnswer(str);
  mfree(str);
}
// EOL,EOF
