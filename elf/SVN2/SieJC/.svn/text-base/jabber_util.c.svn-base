/* -*- coding: windows-1251-dos -*- */
#include "../inc/swilib.h"
#include "history.h"
#include "main.h"
#include "clist_util.h"
#include "revision.h"
#include "jabber_util.h"
#include "string_util.h"
#include "xml_parser.h"
#include "xml_gen.h"
#include "item_info.h"
#include "vCard.h"
#include "jabber.h"
#include "bookmarks.h"
#include "serial_dbg.h"
#include "groups_util.h"
#include "adv_login.h"
#include "lang.h"

extern const char JABBER_SERVER[];
extern const char USERNAME[];
extern const char PASSWORD[];
extern const char RESOURCE[];
extern const char CMP_DATE[];
extern const char VERSION_NAME[];
extern const char VERSION_VERS[];
extern const char OS[];
extern const char OS_postfix[];
extern const int USE_SASL;
extern const int DELIVERY_EVENTS;
extern const int COMPOSING_EVENTS;
extern const int USE_ATTENTION;
extern const int DISPLAY_POPUPS;
extern char My_JID_full[];
extern char My_JID[];
extern char logmsg[];

extern GR_ITEM *GR_ROOT;
extern CLIST* cltop;
extern unsigned int NContacts;

extern const int EXT_VERSION_INFO;

MUC_ITEM *muctop = NULL;

TTime intimes; //для idle
TDate indates;

unsigned int m_num=0; // ид сообщения, любого!

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

/**
  * Функция для отправки настроения
 **/
// Context: HELPER
void Send_Mood(char *mood, char *text)
{
  char *reply = malloc(1024);
  char *_from = Mask_Special_Syms(My_JID_full);
  
  char mod0_t[]="<iq type='set' from='%s' id='SieJC_p%d'>"
    "<pubsub xmlns='http://jabber.org/protocol/pubsub'>"
      "<publish node='http://jabber.org/protocol/mood'>"
        "<item><mood xmlns='http://jabber.org/protocol/mood'><%s/>";
  char mod2_t[]="</mood></item></publish></pubsub></iq>";
  
  char modn_t[]="<iq type='set' from='%s' id='SieJC_p%d'>"
    "<pubsub xmlns='http://jabber.org/protocol/pubsub'>"
      "<publish node='http://jabber.org/protocol/mood'>"
        "<item><mood xmlns='http://jabber.org/protocol/mood'/>"
          "</item></publish></pubsub></iq>";  
  if (mood) 
   {
     sprintf(reply, mod0_t, _from, m_num, mood);
     if (strlen(text)>0) 
     {
       char s_t[256];
       snprintf(s_t,256,"<text>%s</text>", text);
       strcat(reply, s_t);
     }
     strcat(reply, mod2_t);
   }
  else sprintf(reply, modn_t,_from ,m_num);
  SUBPROC((void*)_sendandfree, reply);
  m_num++;
  mfree(_from);
  if (text) mfree(text);
}

/*
  Посылка стандартного Jabber Iq
*/
void SendIq(char* to, char* type, char* id, char* xmlns, XMLNode* payload)
{
  XMLNode *iq, *query;
  char *xml;
  char xmlns_t[]="xmlns";
  char query_t[]="query";
  char iq_t[]="iq";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  iq = XML_CreateNode(iq_t, NULL);
  if (id)
    XML_Set_Attr_Value(iq, id_t, id);
  if (type)
    XML_Set_Attr_Value(iq, type_t, type);
  if (to)
    XML_Set_Attr_Value(iq, to_t, to);

  if(xmlns)
  {
    query = XML_CreateNode(query_t, NULL);  
    XML_Set_Attr_Value(query, xmlns_t, xmlns);
    query->subnode = payload;
    iq->subnode = query;
  } else iq->subnode = payload;
  xml = XML_Get_Node_As_Text(iq);
  _sendandfree(xml);
  DestroyTree(iq);
}

/*
  Посылка стандартного Jabber message
*/
void Send_Message(char* to, char* type, char* id, XMLNode* payload)
{
  XMLNode *message;
  char *xml;
  char message_t[]="message";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  message = XML_CreateNode(message_t, NULL);
  if (id)
    XML_Set_Attr_Value(message, id_t, id);
  if (type)
    XML_Set_Attr_Value(message, type_t, type);
  if (to)
    XML_Set_Attr_Value(message, to_t, to);

  message->subnode = payload;
  xml = XML_Get_Node_As_Text(message);
#ifdef LOG_ALL
  LockSched();
  Log("MESS_OUT", xml);
  UnlockSched();
#endif
  _sendandfree(xml);
  DestroyTree(message);
}

/*
  Посылка стандартного Jabber presence
*/
void SendPresence(char* to, char* type, char* id, XMLNode* payload)
{
  XMLNode *presence;
  char *xml;
  char presence_t[]="presence";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  presence = XML_CreateNode(presence_t, NULL);
  if (id)
    XML_Set_Attr_Value(presence, id_t, id);
  if (type)
    XML_Set_Attr_Value(presence, type_t, type);
  if (to)
    XML_Set_Attr_Value(presence, to_t, to);

  presence->subnode = payload;
  xml = XML_Get_Node_As_Text(presence);
  _sendandfree(xml);
  DestroyTree(presence);
}
/*
  Послать приветствие, на него сервер высылает ответный stream.
  После этого можно общаться с сервером
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
    "<stream:stream to='%s' xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' xml:lang='%s'>";
  char* buf=malloc(256);
  sprintf(buf,streamheader,JABBER_SERVER, LG_XML_LANG);
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
  Послать дисконнект
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

// Константы Iq-запросов
char auth_id[] = "SieJC_auth_req";
char rost_id[] = "SieJC_rost_req";
char vreq_id[] = "SieJC_vers_req";
char priv_id[] = "SieJC_priv_req";
char treq_id[] = "SieJC_time_req";
char vcreq_id[] = "SieJC_vcard_req";
char lastact_id[] = "SieJC_lastact_req";
/*
  Авторизация на Jabber-сервере
  Самая тупая, без извращений.
*/
//Context: HELPER
void Send_Auth()
{
  sprintf(My_JID, "%s@%s",USERNAME, JABBER_SERVER);
  sprintf(My_JID_full,"%s/%s",My_JID, RESOURCE);
  char* tmpstr = malloc(256);
  XMLNode *xml, *xml_out;
  strcpy(tmpstr, USERNAME);
  char username_t[]="username";
  char password_t[]="password";
  char resource_t[]="resource";
  strcpy(tmpstr, USERNAME);
  xml = XML_CreateNode(username_t, tmpstr);

  strcpy(tmpstr, PASSWORD);
  xml->next = XML_CreateNode(password_t, tmpstr);

  strcpy(tmpstr, RESOURCE);  
  xml_out = XML_CreateNode(resource_t, tmpstr);
  xml_out->next = xml;
  
  SendIq(NULL, IQTYPE_SET, auth_id, IQ_AUTH, xml_out);
  mfree(tmpstr);
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

// Послать запрос о версии пользователю с указанным JID
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

// Послать запрос о локальном времени клиента пользователю с указанным JID
void Send_Time_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendtimerequest,to);
}

void _sendvcardrequest(char *to)
{
  char vcard_t[]="vCard";
  char xmlns_t[]="xmlns";
  char typ[]=IQTYPE_GET;
  XMLNode *vcard_xml;
  vcard_xml = XML_CreateNode(vcard_t, NULL);
  XML_Set_Attr_Value(vcard_xml, xmlns_t, JABBER_VCARD_TEMP);
  SendIq(to, typ, vcreq_id, NULL, vcard_xml);
  mfree(to);
}

// Послать запрос о версии vcard
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

// Сгенерировать ver= исходя из текущих возможностей клиента
// Возвращаемую строку необходимо освобождать!
char *Generate_Caps()
{
  char answer[400];
  sprintf(answer, "client/mobile//SieJC %s:%i"
    "<%s"
    "<%s"
    "<%s"
    "<%s"
    "<%s"
    "<%s", VERSION_VERS, __SVN_REVISION__, DISCO_INFO, XMLNS_MUC, IQ_IDLE, IQ_TIME, IQ_VERSION, JABBER_URN_PING);
      
  if(DELIVERY_EVENTS)
  {
    char xevents_feature[]="<"JABBER_XMPP_RECEIPTS;
    strcat(answer, xevents_feature);
  }

  if(COMPOSING_EVENTS)
  {
    char xevents_feature[]="<"XMLNS_CHATSTATES;
    strcat(answer, xevents_feature);
  }

  if(USE_ATTENTION)
  {
    char xevents_feature[]="<"JABBER_URN_ATTENTION;
    strcat(answer, xevents_feature);
  }
      
  SHA_CTX ctx;
  char *hash2 = malloc(256);
  zeromem(hash2,256);
  SHA1_Init(&ctx);
  SHA1_Update(&ctx, answer, strlen(answer));
  SHA1_Final(hash2,&ctx);
  char *Result_Resp = malloc(256);
  zeromem(Result_Resp, 256);
  Base64Encode(hash2, strlen(hash2),Result_Resp, 256);
  mfree(hash2);
  return Result_Resp;
}

/*
  Послать своё присутствие (в частности, после этого на нас вываливаются
  присутствия остальных, а мы появляемся в ресурсах своего контакта)

*/
// Context: HELPER
void Send_Presence(PRESENCE_INFO *pr_info)
{
  extern char My_Presence;
  extern const char percent_d[];
  My_Presence = pr_info->status;
  //<c xmlns='http://jabber.org/protocol/caps' node='VERSION_NAME' ver='VERSION_VERS __SVN_REVISION__' />
  // Генерируем капс исходя из включённых фич
  char *caps_str = Generate_Caps();
  char *tmp_str = malloc(256);
  char* presence = malloc(1024);
  XMLNode *priority=NULL, *show=NULL, *status=NULL, *caps=NULL, *payload=NULL;
  char *type = NULL;
  char status_t[]="status";
  char show_t[]="show";
  char c_t[]="c";
  char xmlns_t[]="xmlns";
  char node_t[]="node";
  char ver_t[]="ver";
  char hash_t[]="hash";
  char priority_t[]="priority";
  
  if(pr_info->status!=PRESENCE_OFFLINE)
  {
  //обновляем онлайнинфо только если не выбран офлайн статус, чтоб при выходе в конфиг записать
  OnlineInfo.status = pr_info->status;
  OnlineInfo.priority = pr_info->priority;
  if(OnlineInfo.txt)mfree(OnlineInfo.txt);
  if(pr_info->message)
  {
    OnlineInfo.txt = malloc(strlen(pr_info->message)+1);
    strcpy(OnlineInfo.txt, pr_info->message);
  }else OnlineInfo.txt = NULL;

  if(pr_info->message)
    if(strlen(pr_info->message)>0)status =XML_CreateNode(status_t, pr_info->message);
  if(pr_info->status!=PRESENCE_INVISIBLE)
  {
    sprintf(tmp_str, percent_d, pr_info->priority);
    priority = XML_CreateNode(priority_t, tmp_str);
    show = XML_CreateNode(show_t, (char*)PRESENCES[pr_info->status]);
    caps = XML_CreateNode(c_t, NULL);
    XML_Set_Attr_Value(caps, xmlns_t, XMLNS_CAPS);
    sprintf(tmp_str, "%s %s-r%d", VERSION_NAME, VERSION_VERS, __SVN_REVISION__);
    XML_Set_Attr_Value(caps, node_t, tmp_str);
    XML_Set_Attr_Value(caps, ver_t, caps_str);
    XML_Set_Attr_Value(caps, hash_t, "sha-1");
    show->next = caps;
    priority->next = show;
    if(status) status->next = priority;
      else status=priority;
    type = NULL;
    payload = status;
  }
  else type = (char*)PRESENCES[PRESENCE_INVISIBLE];
  }
  else
  {
    type=(char*)PRESENCES[PRESENCE_OFFLINE];
    if(status) payload = status;
  }
  SendPresence(NULL, type, NULL, payload);

// MUC support
  MUC_ITEM* m_ex = muctop;
  while(m_ex)
  {
    show = XML_CreateNode(show_t, (char*)PRESENCES[pr_info->status]);    
    if(pr_info->message) 
      if(strlen(pr_info->message)>0)
    {
      status =XML_CreateNode(status_t, pr_info->message);
      show->next = status;
    }
    caps = XML_CreateNode(c_t, NULL);
    XML_Set_Attr_Value(caps, xmlns_t, XMLNS_CAPS);
    sprintf(tmp_str, "%s %s-r%d", VERSION_NAME, VERSION_VERS, __SVN_REVISION__);
    XML_Set_Attr_Value(caps, node_t, tmp_str);
    XML_Set_Attr_Value(caps, ver_t, caps_str);
    XML_Set_Attr_Value(caps, hash_t, "sha-1");
    caps->next = show;

    SendPresence(m_ex->conf_jid, NULL, NULL, caps);
    m_ex=m_ex->next;
  };
  mfree(caps_str);
  mfree(presence);
  mfree(tmp_str);
  if(pr_info->message)mfree(pr_info->message);
  if(pr_info->status==PRESENCE_OFFLINE)
  {
    Send_Disconnect();
  }
  mfree(pr_info);
  LockSched();
  strcpy(logmsg,"Send presence");
  UnlockSched();
}

void Send_ShortPresence(char *to,char type)
{
  SendPresence(to, (char*)PRESENCES[type], NULL, NULL);
}

/*
  Послать запрос ростера
*/
// Context: HELPER
void Send_Roster_Query()
{
  SendIq(NULL, IQTYPE_GET, rost_id, IQ_ROSTER, NULL);
  LockSched();
  strcpy(logmsg,"Send roster Q");
  UnlockSched();
}

// Context: HELPER
void SendMessage(char* jid, IPC_MESSAGE_S *mess)
{
/*
  <attention xmlns='urn:xmpp:attention:0'/>
  <message to='romeo@montague.net' id='message22'>
      <body>Art thou not Romeo, and a Montague?</body>
      <request xmlns='urn:xmpp:receipts'/>
  </message>
*/
  extern const char percent_d[];
  char* mnum_str = malloc(256);
  XMLNode *body=NULL, *request=NULL, *active=NULL, *attention=NULL;
  char body_t[]="body";
  char request_t[]="request";
  char xmlns_t[]="xmlns";
  char active_t[]="active";
  char attention_t[]="attention";
  char *type ;
  body = XML_CreateNode(body_t, mess->body);
  if(mess->IsGroupChat)
  {
    type = MSGSTR_GCHAT;
  }else type = MSGSTR_CHAT;
  if (DELIVERY_EVENTS && !mess->IsGroupChat)
  {
    request=XML_CreateNode(request_t, NULL);
    XML_Set_Attr_Value(request, xmlns_t, JABBER_XMPP_RECEIPTS);
  }
  if (COMPOSING_EVENTS && !mess->IsGroupChat)
  {
    active=XML_CreateNode(active_t, NULL);
    XML_Set_Attr_Value(active, xmlns_t, XMLNS_CHATSTATES);
  }
  if(request)
  {
    request->next = active;
  }
  else request = active;

  if (request)  body->next = request;

  if (USE_ATTENTION && mess->IsAttention && !mess->IsGroupChat)
  {
    attention=XML_CreateNode(attention_t, NULL);
    XML_Set_Attr_Value(attention, xmlns_t, JABBER_URN_ATTENTION);
    attention->next = body;
  } else attention = body;

  sprintf(mnum_str, percent_d, m_num);
  Send_Message(jid, type, mnum_str, attention);
  mfree(mnum_str);
  mfree(mess->body);
  mfree(mess);
  m_num++;
  GetDateTime(&indates, &intimes);
}

 // Context: HELPER
void SendComposing(char* jid, IPC_MESSAGE_S *mess)
{
  /*
  <message 
    from='bernardo@shakespeare.lit/pda'
    to='francisco@shakespeare.lit/elsinore'
    type='chat'>
  <composing xmlns='http://jabber.org/protocol/chatstates'/>
</message>
*/
  extern const int COMPOSING_EVENTS;
  if(!COMPOSING_EVENTS)return;
  char *type;
  if(mess->IsGroupChat)
  {
     type = MSGSTR_GCHAT;
  }else type = MSGSTR_CHAT;

  XMLNode *composing;
  char composing_t[]="composing";
  char xmlns_t[]="xmlns";
  char *str=malloc(256);
  extern const char percent_d[];
  
  composing = XML_CreateNode(composing_t, NULL);
  XML_Set_Attr_Value(composing, xmlns_t, XMLNS_CHATSTATES);
  sprintf(str, percent_d, m_num);
  Send_Message(jid, type, str, composing);

  mfree(str);
  mfree(mess);
  m_num++;
}

 // Context: HELPER
void CancelComposing(char* jid, IPC_MESSAGE_S *mess)
{
  /*
  <message 
    from='juliet@capulet.com/balcony'
    to='romeo@shakespeare.lit/orchard'
    type='chat'>
  <thread>act2scene2chat1</thread>
  <active xmlns='http://jabber.org/protocol/chatstates'/>
</message>
  */
  extern const int COMPOSING_EVENTS;
  if(!COMPOSING_EVENTS)return;
  char *type;
  if(mess->IsGroupChat)
  {
     type = MSGSTR_GCHAT;
  }else type = MSGSTR_CHAT;
  XMLNode *active;
  char active_t[]="active";
  char xmlns_t[]="xmlns";
  char *str=malloc(256);
  extern const char percent_d[];
  active = XML_CreateNode(active_t, NULL);
  XML_Set_Attr_Value(active, xmlns_t, XMLNS_CHATSTATES);
  sprintf(str, percent_d, m_num);
  Send_Message(jid, type, str, active);

  mfree(str);
  mfree(mess);
  m_num++;
}

// Context: HELPER
void Report_VersionInfo(char* id, char *to)
{
  char answer[200];
  char *ph_model = Get_Phone_Info(PI_MODEL);
  char *ph_sw = Get_Phone_Info(PI_SW_NUMBER);
  XMLNode *xml_name=NULL, *xml_version, *xml_os;
  char name_t[]="name";
  char version_t[]="version";
  char os_t[]="os";
  
  strcpy(answer, VERSION_NAME);
  xml_name = XML_CreateNode(name_t, answer);
  
  sprintf(answer, "%s-r%d (%s)", VERSION_VERS, __SVN_REVISION__, CMP_DATE);
  xml_version = XML_CreateNode(version_t, answer);
  
  // Не будем издеваться над Костиным сервером)
  #pragma swi_number=0x41
  __swi __arm char GetProvider(WSHDR* name, int unk_1);

  #pragma swi_number=0x2C2
  __swi __arm int GetSubprovider(WSHDR* ws);
  
  // Аццкий процент не экранируется
  #define percent "%"
  
  if(EXT_VERSION_INFO)
  {
    WSHDR* prov = AllocWS(128);
#ifdef NEWSGOLD
    GetSubprovider(prov);
    if(!prov->wsbody[0]) GetProvider(prov, 1);
#else
    GetProvider(prov, 1);
#endif
    char provider[128];
    ws_2str(prov, provider, 128);
    FreeWS(prov);
    RAMNET *net_data = RamNet();
    sprintf(answer, "SIE-%s/%s %s (%s:%ddB BAT:%d%s RAM:%dKb)", ph_model, ph_sw, OS, provider, net_data->power, *RamCap(), percent, GetFreeRamAvail()/1000);
  }
  else sprintf(answer, "SIE-%s/%s %s%s", ph_model, ph_sw, OS, OS_postfix);
  
  
  xml_os = XML_CreateNode(os_t, answer);
  xml_version->next = xml_os;
  xml_name->next = xml_version;
  SendIq(to, IQTYPE_RES, id, IQ_VERSION, xml_name);

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
  GetDateTime(&reqd, &reqt);
  int total=GetTimeZoneShift(&reqd, &reqt, RamDateTimeSettings()->timeZone);
  int hour=0;
  char znak[]="+";
  if (total<0)
  {
    total=total*(-1);
    znak[0]='-';
  };
  while(total>59)
  {
    total=total-60;
    hour++;
  };

  XMLNode *xml_utc=NULL, *xml_tz, *xml_display;
  char utc_t[]="utc";
  char tz_t[]="tz";
  char display_t[]="display";
  
  sprintf(answer, "%04d%02d%02dT%02d:%02d:%02d", reqd.year,reqd.month,reqd.day,reqt.hour,reqt.min,reqt.sec);
  xml_utc = XML_CreateNode(utc_t, answer);
  
  sprintf(answer, "%s%02d:%02d",znak, hour, total);
  xml_tz = XML_CreateNode(tz_t, answer);

  sprintf(answer, "%02d-%02d-%04d %02d:%02d:%02d",reqd.day,reqd.month,reqd.year,reqt.hour,reqt.min,reqt.sec);
  xml_display = XML_CreateNode(display_t, answer);
  
  xml_utc->next = xml_display;
  xml_tz->next = xml_utc;
  SendIq(to, IQTYPE_RES, id, IQ_TIME, xml_tz);  
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
  extern const char percent_d[];
  XMLNode *query;
  char xmlns_t[]="xmlns";
  char query_t[]="query";
  char seconds_t[]="seconds";

  query = XML_CreateNode(query_t, NULL);  
  XML_Set_Attr_Value(query, xmlns_t, IQ_IDLE);
  char* timestr=malloc(512);
  sprintf(timestr, percent_d, GetIDLETime(intimes, indates));

  XML_Set_Attr_Value(query, seconds_t, timestr);
  mfree(timestr);
  SendIq(to, IQTYPE_RES, id, NULL, query);

  mfree(to);
  mfree(id);
}

// Context: HELPER
void Report_DiscoInfo(char* id, char *to)
{
  XMLNode *tmp, *out, *cur;
  char feature_t[]="feature";
  char var_t[]="var";
  char identity_t[]="identity";
  char category_t[]="category";
  char type_t[]="type";
  char phone_t[]="phone";
  char client_t[]="client";
  cur = XML_CreateNode(identity_t, NULL);
  XML_Set_Attr_Value(cur, category_t, client_t);
  XML_Set_Attr_Value(cur, type_t, phone_t);
  out = cur;

  char *FeaturesList[9]={
  DISCO_INFO,
  IQ_VERSION,
  XMLNS_MUC,
  IQ_TIME,
  IQ_IDLE,
  JABBER_URN_PING,
  JABBER_XMPP_RECEIPTS,
  JABBER_URN_ATTENTION,
  XMLNS_CHATSTATES};
  
  int featurescount;
  for(featurescount=0; featurescount<10; featurescount++)
  {
  if ((featurescount<6)||(featurescount==6 && DELIVERY_EVENTS)
  ||(featurescount==7 && USE_ATTENTION)||(featurescount==8 && COMPOSING_EVENTS))
   {
    cur = XML_CreateNode(feature_t, NULL);
    XML_Set_Attr_Value(cur, var_t, FeaturesList[featurescount]);
      tmp=out;
      if(tmp)
        while(tmp->next)tmp = tmp->next;
      if(tmp)
      {
        tmp->next = cur;
      }
      else out = cur;
   }
  }
  SendIq(to, IQTYPE_RES, id, DISCO_INFO, out);
  mfree(id);
  mfree(to);
}

void Report_PING(char* id, char *to)
{
/*
  <iq from='juliet@capulet.lit/balcony' to='capulet.lit' id='s2c1' type='result'/>
*/
  SendIq(to, IQTYPE_RES, id, NULL, NULL);
  mfree(to);
  mfree(id);
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
  PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
  pr_info->priority = OnlineInfo.priority;
  pr_info->status=OnlineInfo.status;
  int len;
  if(OnlineInfo.txt)
  {
  if(len = strlen(OnlineInfo.txt))
  {
  char *msg = malloc(len+1);
  strcpy(msg, OnlineInfo.txt);
  msg[len]='\0';
  pr_info->message =msg;
    //mfree(msg);
  }
  }else
  pr_info->message = NULL;
  Send_Presence(pr_info);

  Jabber_state = JS_ONLINE;
}

//Context: HELPER
void _enterconference(MUC_ENTER_PARAM *param)
{
  char *tmp_str = malloc(256);
  XMLNode *history, *xml_x, *password, *show, *status;
  char history_t[]="history";
  char show_t[]="show";
  char status_t[]="status";
  char password_t[]="password";
  char x_t[]="x";
  char xmlns_t[]="xmlns";
  char maxstanzas_t[]="maxstanzas";
  extern const char percent_d[];
  char slash_t[]="/";
  history = XML_CreateNode(history_t, NULL);
  sprintf(tmp_str, percent_d, param->mess_num);
  XML_Set_Attr_Value(history, maxstanzas_t, tmp_str);
  if(param->pass)
  {
    password=XML_CreateNode(password_t, param->pass);
    history->next=password;
  }
  xml_x = XML_CreateNode(x_t, NULL);
  XML_Set_Attr_Value(xml_x, xmlns_t, XMLNS_MUC);
  xml_x->subnode=history;

  char *stext;
  extern char empty_str[];
  if(OnlineInfo.txt){stext= OnlineInfo.txt;}else{stext = empty_str;}
  show = XML_CreateNode(show_t, (char*)PRESENCES[OnlineInfo.status]);
  if (stext)
    if(strlen(stext)>0)
    {
      status = XML_CreateNode(status_t, stext);
      xml_x->next = status;
    }
  show->next = xml_x;
  strcpy(tmp_str, param->room_name);
  strcat(tmp_str, slash_t);
  strcat(tmp_str, param->room_nick);
  SendPresence(tmp_str, NULL, NULL, show);
  mfree(tmp_str);
  mfree(param->room_nick);
  mfree(param->room_name);
  if(param->pass)mfree(param->pass);
  mfree(param);
}


// Входит в конференцию
// Все имена в UTF-8 :)
void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages)
{

  // Смотрим, есть ли такая конфа в списке конференций
  // Если есть, тогда мы должны просто поменять ник в ней
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

  CLIST* Conference = CList_FindContactByJID(room);
  if(!IsAlreadyInList)
  {
    // Добавляем контакт конференции в ростер
    if(!Conference)
    {
      CList_AddContact(room,room, SUB_BOTH, 0, 129);
    }
//    else  // Конфа могла остаться от предыдущего входа/выхода
//    {
//      Conference->res_list->status=PRESENCE_ONLINE;
//    }
  }
  if((Conference)&&(m_ex))
    if(Conference->res_list)
      if((Conference->res_list->status==PRESENCE_ONLINE)&&(!strcmp(Get_Resource_Name_By_FullJID(m_ex->conf_jid),roomnick))) return; //Уже там, и нечего перезаходить

  // Готовим структуру для передачи в HELPER
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
  else par->mess_num=0;   // Нах еще раз запрашивать историю
  SUBPROC((void*)_enterconference, par);

  if(!IsAlreadyInList)
  {
    // Регистрируем конференцию в списке конференций
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
    // m_ex - текущий элемент
    int len = strlen(par->room_name)+strlen(par->room_nick)+2;
    m_ex->conf_jid = realloc(m_ex->conf_jid, len);
    snprintf(m_ex->conf_jid, len, "%s/%s", par->room_name, par->room_nick);
  }
}

struct muc_hlp_data {
  char *conf_jid;
  char *aux0;
};

//Context: HELPER
void _leaveconference(struct muc_hlp_data *ld)
{
  extern const char DEFTEX_MUCOFFLINE[];
//  char pr_templ[] = "<presence from='%s' to='%s' type='unavailable'><status>%s</status></presence>";
  char *msg=NULL;
  unsigned int l;
  if (!ld->aux0) {
    int len;
    if(len = strlen(DEFTEX_MUCOFFLINE))
      {
	msg = malloc(len+1);
	strcpy(msg, DEFTEX_MUCOFFLINE);
	msg[len]='\0';
      } else Send_ShortPresence(ld->conf_jid, PRESENCE_OFFLINE);
  } else {
    l = strlen(ld->aux0);
    msg = malloc(l*2 + 1);
    strcpy(msg, ld->aux0);
    mfree(ld->aux0);
  }

  if (msg) {
    char status_t[]="status";
    XMLNode *status = XML_CreateNode(status_t, msg);
    SendPresence(ld->conf_jid, (char*)PRESENCES[PRESENCE_OFFLINE], NULL, status);
    mfree(msg);
  }

  mfree(ld->conf_jid);
  mfree(ld);
}

/*
 * Функция для подготовки служебных структур перед отправкой в HELPER
 */
void Muc_Ctl(char *room, char *str, void(proc)(struct muc_hlp_data*))
{
  struct muc_hlp_data *ld;
  unsigned int l;

  if (!room || !proc) return; /* Sanity checking */

  ld = malloc(sizeof(struct muc_hlp_data));
  ld->conf_jid = malloc(strlen(room)*2+1);
  strcpy(ld->conf_jid, room);

  if (str && (l = strlen(str))) {
    ld->aux0 = malloc(l*2+1);
    strcpy(ld->aux0, str);
  } else ld->aux0 = NULL;
  
  SUBPROC((void*)proc, ld);

  return;
}

//Context: HELPER
void _setconferencetopic(struct muc_hlp_data *ld)
{
  XMLNode *subject;
  char subject_t[]="subject";
  extern const char percent_d[];
  char *type = MSGSTR_GCHAT;

  if (!ld->aux0 || !(strlen(ld->aux0)))
    goto _free;
  
  subject = XML_CreateNode(subject_t, ld->aux0);
  Send_Message(ld->conf_jid, type, NULL, subject);

 _free:
  mfree(ld->conf_jid);
  mfree(ld);
}

// Выходит из конференции
void Send_Leave_Conference(char* room, char *reason)
{

  Muc_Ctl(room, reason, _leaveconference);
}

// Задаёт тему базара
void Set_Conference_Topic(char *room, char* topic)
{

  Muc_Ctl(room, topic, _setconferencetopic);
}

void Leave_Conference(char* room)
{
  // Ищем экземпляр контакта в списке для конференций
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
      m_ex2->next = m_ex->next;   // Выбиваем из цепочки
      mfree(m_ex->conf_jid);
      mfree(m_ex);
      break;
    }
    m_ex2 = m_ex2->next;
  }
  ShowMSG(1,(int)LG_MUCEXITDONE);
}


// Уничтожить список комнат
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



// Для вызова таймером
void Send_Presence_MMIStub()
{
  SUBPROC((void*)Send_Initial_Presence_Helper);
}


// Изменяет имя контакта в ростере
void ChangeRoster(XMLNode* items)
{
  XMLNode* rostEx = items;
  CLIST* Cont_Ex;
  char *name;
  char* w_subscr;
  char aname[]="jid";  // Затрахали Tool Internal Error
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
    { //если контакта нету надо добавить его в контактлист.
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
    // Получаем группу контакта, заносим в список групп
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

  // Получение ростера закончено. Размечаем группы
  GR_ITEM *tmp_gpointer=GR_ROOT;
  CLIST *tmp_cpointer=cltop;
  int cur_gid=-1, this_grid;   // Текущий обрабатываемый GID


  // Цикл по всем контактам
  while(tmp_cpointer->next)
  {
    this_grid = ((CLIST*)tmp_cpointer->next)->group;
    // Получаем текущую группу
    if(cur_gid!=this_grid)
    {
      tmp_gpointer = GetGroupByID(this_grid);
      cur_gid = this_grid;
      // Создаём псевдоконтакт, вставляем его
      CLIST *gr_pscontact = malloc(sizeof(CLIST));
      gr_pscontact->name = malloc(strlen(tmp_gpointer->name)+1);
      gr_pscontact->JID = malloc(strlen(tmp_gpointer->name)+2+(strlen(My_JID_full)));
      strcpy(gr_pscontact->name, tmp_gpointer->name);
      strcpy(gr_pscontact->JID, tmp_gpointer->name);
      strcat(gr_pscontact->JID, "@"); //присвоим группе несущемтвуюший JID, чтоб не сбивала с толку.
      strcat(gr_pscontact->JID, My_JID_full);//но ресурс и контакт должны совпадать
      gr_pscontact->subscription = SUB_BOTH;
      gr_pscontact->wants_subscription = 0;
      gr_pscontact->group = cur_gid;
      gr_pscontact->IsVisible = 1;
      gr_pscontact->ResourceCount=1;
      gr_pscontact->next=tmp_cpointer->next;  // Вставляем между текущим и следующим
      gr_pscontact->vcard=NULL; //У группы нет vCard. И никогда не будет.
      tmp_cpointer->next = gr_pscontact;

      // Cоздаём ещё и псевдоресурс
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
      // Коннектим ресурс к группе
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
  XMLNode *error, *feature;
  char error_t[]="error";
  char type_t[]="type";
  char cancel_t[]="cancel";
  char featureni_t[]="feature-not-implemented";
  char xmlns_t[]="xmlns";
  char urnietf_t[]="urn:ietf:params:xml:ns:xmpp-stanzas";
  
  feature = XML_CreateNode(featureni_t, NULL);
  XML_Set_Attr_Value(feature, xmlns_t, urnietf_t);
  error = XML_CreateNode(error_t, NULL);
  XML_Set_Attr_Value(error, type_t, cancel_t);
  error->subnode = feature;
  SendIq(to, IQTYPE_ERR, id, NULL, error);
}

void Send_Service_Unavailable(char *to, char *id)
{
  if(!to || !id)return;
  XMLNode *error, *feature;
  char error_t[]="error";
  char type_t[]="type";
  char cancel_t[]="cancel";
  char serviceun_t[]="service-unavailable";
  char xmlns_t[]="xmlns";
  char urnietf_t[]="urn:ietf:params:xml:ns:xmpp-stanzas";
  
  feature = XML_CreateNode(serviceun_t, NULL);
  XML_Set_Attr_Value(feature, xmlns_t, urnietf_t);
  error = XML_CreateNode(error_t, NULL);
  XML_Set_Attr_Value(error, type_t, cancel_t);
  error->subnode = feature;
  SendIq(to, IQTYPE_ERR, id, NULL, error);
}

/*
 Обработка входящих Iq-запросов
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

// Проверяем наличие обязательных атрибутов
if(!iqtype) return;

if(!strcmp(gget,iqtype)) // Iq type = get
{
  XMLNode* query;
  char* q_type;
  if(query = XML_Get_Child_Node_By_Name(nodeEx, "query"))
  if(q_type = XML_Get_Attr_Value("xmlns", query->attr))
  {
  // Тут мы знаем XMLNS поступившего запроса
  if(!strcmp(q_type,iq_version))
  {
    // jabber:iq:version
    if(from)
    {
        // Создаем переменные, чтобы в них записать данные
        // и безопасно уничтожить в HELPER

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
        // Создаем переменные, чтобы в них записать данные
        // и безопасно уничтожить в HELPER

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
        // Создаем переменные, чтобы в них записать данные
        // и безопасно уничтожить в HELPER

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
 } //end "query" 
 
   if(query = XML_Get_Child_Node_By_Name(nodeEx, "ping"))
    if (q_type = XML_Get_Attr_Value("xmlns", query->attr))
  if(!strcmp(q_type,JABBER_URN_PING))    // urn:xmpp:ping
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
        SUBPROC((void*)Report_PING, loc_id, loc_from);
        return;
    }
  } //end ping

  // Ни один обработчик не подошёл, отправляем ошибку.
  Send_Feature_Not_Implemented(from, id);
}


// Обработка  Iq type = result
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

  if(!strcmp(id,auth_id) || !strcmp(id, sess_id))   // Авторизация либо конец инициализации сессии
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

  if(!strcmp(id,rost_id))   // Запрос ростера
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_ROSTER))
    {
      // jabber:iq:roster
      FillRoster(query->subnode);
        // Через секунду запросим презенсы
      extern GBSTMR TMR_Send_Presence;
      GBS_StartTimerProc(&TMR_Send_Presence, TMR_SECOND*1, Send_Presence_MMIStub);
      return;
    }
  }

  if(!strcmp(id,vreq_id))   // Запрос версии (ответ)
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
      //Формируем сообщение
      char *reply=malloc(512);
      snprintf(reply, 512,LG_VERINFO,cl_name->value, cl_version->value, vers_os_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }

    if(!strcmp(id,lastact_id))   // Запрос IDLE (ответ)
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,IQ_IDLE))
    {
      char *cl_sec=XML_Get_Attr_Value("seconds", query->attr);
      //Формируем сообщение
      char *reply=malloc(512);
      unsigned int nsec, nmin, nhr, nd;
      extern const char percent_d[];
      sscanf(cl_sec, percent_d, &nsec);
      nmin = udiv(60, nsec);
      nsec -= nmin*60;
      nhr = udiv(60, nmin);
      nmin -= nhr*60;
      nd = udiv(24, nhr);
      nhr -= nd*24;
      snprintf(reply, 512,LG_LASTACTIVMSG, nd, nhr, nmin, nsec);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }//end lastactiv

    if(!strcmp(id,treq_id))   // Запрос TIME (ответ)
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
      //Формируем сообщение
      char *reply=malloc(512);
      snprintf(reply, 512,LG_TIMEINFO,cl_utc->value, tz_str, display_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }
  if(!strcmp(id,vcreq_id))   // Запрос vcard (ответ)
  {
    XMLNode* vcard;
    if(!(vcard = XML_Get_Child_Node_By_Name(nodeEx, "vCard")))return;
    char* v_type = XML_Get_Attr_Value("xmlns", vcard->attr);
    if(!v_type)return;
    if(!strcmp(v_type,JABBER_VCARD_TEMP))Process_vCard(from, vcard);
  }
/////////////////
  if(!strcmp(id,disco_id))   // Запрос диско (ответ)
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
// Обработка  Iq type = set
if(!strcmp(gset,iqtype))
{
    XMLNode* query;
    if(query = XML_Get_Child_Node_By_Name(nodeEx, "query"))
    {
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;

    if(!strcmp(q_type,IQ_ROSTER))
    {
      // jabber:iq:roster
      ChangeRoster(query->subnode);
      return;
    }
    }
    Send_Service_Unavailable(from, id);
}

if(!strcmp(gerr,iqtype)) // Iq type = error
{

  // Анализируем ошибку
  XMLNode* error = XML_Get_Child_Node_By_Name(nodeEx, "error");
  if(!error)return;
  char* errcode = XML_Get_Attr_Value("code", error->attr);
//  Jabber_state = JS_ERROR;
  if(errcode)
  {
    int errcode_n=0;
    extern const char percent_d[];
    sscanf(errcode,percent_d,&errcode_n);
    {
    switch (errcode_n)
      {
      case JABBER_ERROR_REDIRECT: sprintf(logmsg,LG_JABBER_ERROR_REDIRECT); break;
      case JABBER_ERROR_BAD_REQUEST: sprintf(logmsg,LG_JABBER_ERROR_BAD_REQUEST); break;
      case JABBER_ERROR_UNAUTHORIZED: sprintf(logmsg,LG_JABBER_ERROR_UNAUTHORIZED); break;
      case JABBER_ERROR_PAYMENT_REQUIRED: sprintf(logmsg,LG_JABBER_ERROR_PAYMENT_REQUIRED); break;
      case JABBER_ERROR_FORBIDDEN: sprintf(logmsg,LG_JABBER_ERROR_FORBIDDEN); break;
      case JABBER_ERROR_NOT_FOUND: sprintf(logmsg,LG_JABBER_ERROR_NOT_FOUND); break;
      case JABBER_ERROR_NOT_ALLOWED: sprintf(logmsg,LG_JABBER_ERROR_NOT_ALLOWED); break;
      case JABBER_ERROR_NOT_ACCEPTABLE: sprintf(logmsg,LG_JABBER_ERROR_NOT_ACCEPTABLE); break;
      case JABBER_ERROR_REGISTRATION_REQUIRED: sprintf(logmsg,LG_JABBER_ERROR_REGISTRATION_REQUIRED); break;
      case JABBER_ERROR_REQUEST_TIMEOUT: sprintf(logmsg,LG_JABBER_ERROR_REQUEST_TIMEOUT); break;
      case JABBER_ERROR_CONFLICT: sprintf(logmsg,LG_JABBER_ERROR_CONFLICT); break;
      case JABBER_ERROR_INTERNAL_SERVER_ERROR: sprintf(logmsg,LG_JABBER_ERROR_INTERNAL_SERVER_ERROR); break;
      case JABBER_ERROR_NOT_IMPLEMENTED: sprintf(logmsg,LG_JABBER_ERROR_NOT_IMPLEMENTED); break;
      case JABBER_ERROR_REMOTE_SERVER_ERROR: sprintf(logmsg,LG_JABBER_ERROR_REMOTE_SERVER_ERROR); break;
      case JABBER_ERROR_SERVICE_UNAVAILABLE: sprintf(logmsg,LG_JABBER_ERROR_SERVICE_UNAVAILABLE); break;
      case JABBER_ERROR_REMOTE_SERVER_TIMEOUT: sprintf(logmsg,LG_JABBER_ERROR_REMOTE_SERVER_TIMEOUT); break;
      default:sprintf(logmsg,"ERR:%s",errcode);
      }
      MsgBoxError(1,(int)logmsg);
    }
  }
  
  if(!strcmp(id,auth_id))
  {
    Jabber_state = JS_AUTH_ERROR;
    strcat(logmsg,"\nAuth error!");
    MsgBoxError(1,(int)logmsg);
    extern void end_socket(void);
    SUBPROC((void*)end_socket);
  }
}
}
/*
Презенсы :)
*/
void Process_Presence_Change(XMLNode* node)
 {
  // Иар заебал
   extern const char percent_d[];
   extern const int SHOWSTAT_MUCINOUT;
   extern const int SHOWSTAT_MUCCHANGESTAT;
   
char loc_actor[]="actor";
char loc_jid[]="jid";
char loc_reason[]="reason";
char loc_xmlns[]="xmlns";
char loc_x[]="x";
int priority = 0;

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
    if(prio_node)
     sscanf(prio_node->value,percent_d,&priority);
  }

   // Предусматриваем случай, что послано нам что-то от конференции. Это важно.
   XMLNode *x_node;

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, XMLNS_MUC)) // Послано от конференции
    {
      CLIST* Conference = CList_FindContactByJID(from);
      // Получаем дочерний узел error (ибо нацелены на обработку именно ошибок)
      XMLNode* err_node = XML_Get_Child_Node_By_Name(node,"error");
      if(err_node)  // Есть ошибка!
      {
        // Хочу текст ошибки
        XMLNode* err_desc = XML_Get_Child_Node_By_Name(err_node,"text");
        if(err_desc)
        {
          if(err_desc->value)msg = err_desc->value;
          if (DISPLAY_POPUPS)
          {
            char *ansi_r = convUTF8_to_ANSI_STR(err_desc->value);
            MsgBoxError(1,(int)ansi_r);
            mfree(ansi_r);
          }
          CList_AddSystemMessage(Conference->JID,PRESENCE_OFFLINE, err_desc->value);
        }
        else
        {
          char q[40];
          char *code = XML_Get_Attr_Value("code",err_node->attr);
          sprintf(q,"ERR %s",code);
          MsgBoxError(1,(int)q);
        }
      }
    }


#define MAX_STATUS_LEN 512
static char r[MAX_STATUS_LEN];       // Статик, чтобы не убило её при завершении процедуры

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, XMLNS_MUC_USER)) // Послано от конференции в пользователя
    {

      // Получим экземпляр конфы, в которой всё происходит
      CLIST* Conference = CList_FindContactByJID(from);
      if(!Conference)
      {
        return;
      }
      MUC_ITEM *MucClist = CList_FindMUCByJID(Conference->JID);
      if (!MucClist) return; //нету такой конференции, значит мы ёё несоздавали
      char* nick = Get_Resource_Name_By_FullJID(from);

      // Тут можно обрабатывать события входа/выхода в конфу
      // Ибо сообщается, кто вошёл (модер ли, админ...)
      XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
      if(status!=PRESENCE_OFFLINE) // Вход с любым статусом
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
        else if(real_jid)  //если знаем реальный jid, выводим его
        {
          sprintf(r, "%s (%s) joined as %s and %s", nick, real_jid, affiliation, role);
          Req_Set_Role = 1;
        }
        else
        {
          sprintf(r, "%s joined as %s and %s", nick, affiliation, role);
          Req_Set_Role = 1;
        }

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

        char* my_nick = Get_Resource_Name_By_FullJID(MucClist->conf_jid);
        if ((!strcmp(nick,my_nick))&&(Conference->res_list->status==PRESENCE_OFFLINE)) //если ето мы, входим в нее.
        {
          Conference->res_list->status=PRESENCE_ONLINE;
          ShowMSG(1,(int)LG_MUCCROK);
        };
        if((SHOWSTAT_MUCINOUT&&Req_Set_Role)||(SHOWSTAT_MUCCHANGESTAT&&!Req_Set_Role))
         CList_AddSystemMessage(Conference->JID,PRESENCE_ONLINE, r);
      }


      if(status==PRESENCE_OFFLINE) // Выход
      {
        XMLNode* statusmsg_node = XML_Get_Child_Node_By_Name(node,"status");
        if (!statusmsg_node)
          sprintf(r, "%s left us", nick);
        else 
        {
         if(statusmsg_node->value) sprintf(r, "%s left us (%s)", nick, statusmsg_node->value);
           else sprintf(r, "%s left us", nick);
        }

        char* my_nick = Get_Resource_Name_By_FullJID(MucClist->conf_jid);
        if (!strcmp(nick,my_nick)) //если ето мы, удаляем конфу.
        {
          Leave_Conference(Conference->JID);
          CList_MakeAllResourcesOFFLINE(Conference);
        };
        extern const char sndOffline[64];
        //Play(sndOffline);
        SUBPROC((void *)Play, sndOffline);
        if(SHOWSTAT_MUCINOUT)
          CList_AddSystemMessage(Conference->JID,PRESENCE_OFFLINE, r);
        priv.role = ROLE_NONE;
        priv.aff  = AFFILIATION_NONE;
        Req_Set_Role = 1;
      }

      // Получаем дочерний узел статуса
      XMLNode* sstatus = XML_Get_Child_Node_By_Name(x_node,"status");
      if(sstatus)  // Есть статус!
      {
        // Получаем код статуса
        char* st_code=XML_Get_Attr_Value("code", sstatus->attr);
        int errcode_n=0;
        extern const char percent_d[];
        sscanf(st_code,percent_d,&errcode_n);
        // Разные коды статусов - разное варенье:)
        switch (errcode_n)
        {
         case MUCST_KICKED:  sprintf(r, LG_MUCST_R_KICK,nick); break; // Сообщение о кике
         case MUCST_BANNED: sprintf(r, LG_MUCST_R_BAN, nick); break;// Сообщение о бане
         case MUCST_KICKED_MEMB_ONLY: sprintf(r, LG_MUCST_R_KICK_MEMB_ONLY, nick); break; // Сообщение о кике из мембер-онли румы
         case MUCST_CHNICK: sprintf(r, LG_MUCST_R_CHNICK, nick,  XML_Get_Attr_Value("nick", item->attr)); break; // Сообщение о смене ника
         case MUCST_MUCCREATED: sprintf(r, LG_MUCST_MUCCREATED, nick); break; // Сообщение о бане
         default: sprintf(r,"%s - [unknow action(%s)]",nick, st_code);
        }
        XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
        if(item)
        {
          XMLNode* actor = XML_Get_Child_Node_By_Name(item,loc_actor); // Вдруг сервис был настолько любезен, что соообщил исполнителя
          if(actor)strcat(r, XML_Get_Attr_Value(loc_jid, actor->attr));

          XMLNode* reason = XML_Get_Child_Node_By_Name(item,loc_reason); // А вдруг нам даже сказали, за что?
          if(reason)
          {
            strcat(r, "; Reason: ");
            int l = strlen(r);
            if(MAX_STATUS_LEN-l-1>0)strncat(r, reason->value, MAX_STATUS_LEN-l-1);
          }
        }
        if(DISPLAY_POPUPS)
        {
          char *ansi_r = convUTF8_to_ANSI_STR(r);
          MsgBoxError(1,(int)ansi_r);
          mfree(ansi_r);
        }
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
  char m_error[]=MSGSTR_ERROR;
  if(!mess_type_str)return MSG_NORMAL;
  if(!strcmp(mess_type_str,m_chat ))return MSG_CHAT;
  if(!strcmp(mess_type_str,m_gchat ))return MSG_GCHAT;
  if(!strcmp(mess_type_str,m_error ))return MSG_STATUS;
  return MSG_NORMAL;
}

//Context: HELPER
void _mucadmincmd(char* room, XMLNode* iq_payload)
{
  char admin_iqid[]="SieJC_adm";
  char iqtypeset[]=IQTYPE_SET;
  SendIq(room, iqtypeset, admin_iqid, XMLNS_MUC_ADMIN, iq_payload);
  mfree(room);
}

// Исполнение административных команд
void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason)
{
  char *_room_name=malloc(strlen(room_name)+1);
  strcpy(_room_name,room_name);
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
  
  XMLNode *xml_item, *xml_reason;
  char item_t[]="item";
  char nick_t[]="nick";
  char reason_t[]="reason";

  xml_item = XML_CreateNode(item_t, NULL);
  xml_reason = XML_CreateNode(reason_t, reason);
  XML_Set_Attr_Value(xml_item, it, val);
  XML_Set_Attr_Value(xml_item, nick_t, room_jid);
  xml_item->subnode = xml_reason;
  SUBPROC((void*)_mucadmincmd, _room_name, xml_item);
}

static void Report_Delivery(char *mess_id, char *to)
{
/*
RECV:
  <message
    from='kingrichard@royalty.england.lit/throne'
    id='richard2-4.1.247'
    to='northumberland@shakespeare.lit/westminster'>
  <received xmlns='urn:xmpp:receipts'/>
</message>
*/
  XMLNode *received;
  char received_t[]="received";
  char xmlns_t[]="xmlns";  
  received = XML_CreateNode(received_t, NULL);
  XML_Set_Attr_Value(received, xmlns_t, JABBER_XMPP_RECEIPTS);
  Send_Message(to, NULL, mess_id, received);
}

/*
Входящие сообщения
*/
void Process_Incoming_Message(XMLNode* nodeEx)
{
  char Is_subj=0;
  char from[]="from";
  char c_xmlns[]="xmlns";
  char c_id[]="id";
  extern const int BOLD_NICK_INMUC;
  // Если включено обслуживание запросов о получении...
  char *chr_from = XML_Get_Attr_Value(from,nodeEx->attr);
    XMLNode* xnode = XML_Get_Child_Node_By_Name(nodeEx,"x");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      {
      if(!strcmp(xmlns,XMLNS_MUC_USER)) //обработка invite
      {
       XMLNode *invite =  XML_Get_Child_Node_By_Name(xnode,"invite");
       if(invite)
       {
        MUC_ITEM* muct = CList_FindMUCByJID(chr_from); 
        if(!muct) //если еще нетты такой конфы то добавим в список muctop, а вдруг зайдем
        {
          CList_AddContact(chr_from,chr_from, SUB_BOTH, 0, 129);
        }
       }
      } //end invite

     }
    }

  //обработка attention xep-0224
   XMLNode *attention =  XML_Get_Child_Node_By_Name(nodeEx,"attention");
   if(attention && USE_ATTENTION)
   {
     char *xmlnsa = XML_Get_Attr_Value(c_xmlns,attention->attr);
     if (xmlnsa)
       if(!strcmp(xmlnsa,JABBER_URN_ATTENTION)) 
       {
         //ShowMSG(1,(int)"Agtung!");
         Vibrate(2);
       }
   } //end attention

    // delivery
    if(DELIVERY_EVENTS)
    {
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"request");
    if(xnode)
      {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
       {
       if(!strcmp(xmlns,JABBER_XMPP_RECEIPTS))
        {
          char *id = XML_Get_Attr_Value(c_id, nodeEx->attr);
          if(id)Report_Delivery(id, chr_from);
        }
       }
      }
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"received");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,JABBER_XMPP_RECEIPTS))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        {
          //Пришло уведомление что наше сообщение получено, и как ето отобразить?
          // ShowMSG(1,(int)Res_ex->name);
        }
      }
    }
    }
    // composing
    if(COMPOSING_EVENTS)
    {
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"composing");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,XMLNS_CHATSTATES))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        CList_ChangeComposingStatus(Res_ex, 1);
      }
    }
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"active");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,XMLNS_CHATSTATES))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        CList_ChangeComposingStatus(Res_ex, 0);
      }
    }
    }

  XMLNode* msgnode = XML_Get_Child_Node_By_Name(nodeEx,"body");
  XMLNode* msgsubject = XML_Get_Child_Node_By_Name(nodeEx,"subject");
  XMLNode* msgerror = XML_Get_Child_Node_By_Name(nodeEx,"error");
  if(!msgnode)
  {
    msgnode = msgsubject;
    Is_subj = 1;
  }
  if(msgsubject && !msgerror) //если есть тема, обработаем...
  {
    MUC_ITEM* TmpMUC = CList_FindMUCByJID(CList_FindContactByJID(chr_from)->JID);
      if(TmpMUC)
      {
       if(TmpMUC->muctema) mfree(TmpMUC->muctema);
       TmpMUC->muctema = malloc(strlen(msgsubject->value)*2+1);
       strcpy(TmpMUC->muctema ,msgsubject->value);
      }
  }
  if(msgerror)
  {
   XMLNode* texterror = XML_Get_Child_Node_By_Name(msgerror,"text");
    if(texterror)
      if(texterror->value)
        if(strlen(texterror->value))
          msgnode = texterror;
  }
  
  if(msgnode)
  if(msgnode->value)
  {
    MESS_TYPE msgtype = Get_Message_Type(XML_Get_Attr_Value("type",nodeEx->attr));

    // Не показываем попапы для групчата, ибо достаёт трындец как
    if((msgtype!=MSG_GCHAT)&&(msgtype!=MSG_NICKGCHAT))
    {
      if(DISPLAY_POPUPS)
      {
        char* m = malloc(128+5+strlen(msgnode->value));
        sprintf(m,"%s: %s", chr_from, msgnode->value);
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
          if(BOLD_NICK_INMUC)
          if(msgtype==MSG_GCHAT)
          {
          CLIST* clMuc = CList_FindContactByJID(chr_from);
          if(clMuc)
          {
            MUC_ITEM* TmpMUC = CList_FindMUCByJID(clMuc->JID);
            if (TmpMUC)
            {
              char* my_nick = Get_Resource_Name_By_FullJID(TmpMUC->conf_jid);
              if (strstr(msgnode->value, my_nick))
              {
                if(strcmp(Get_Resource_Name_By_FullJID(chr_from), my_nick)) 
                  msgtype=MSG_NICKGCHAT;
              }
            }
          }
          }
          extern const char sndConf[];
          SUBPROC((void *)Play,sndConf);
        }
    if(Is_subj)
    {
      msgtype = MSG_SUBJECT;
    }
    
    if (!msgerror)
    CList_AddMessage(chr_from, msgtype, msgnode->value);
    else
    {
      char r[MAX_STATUS_LEN];
      sprintf(r, "Error: %s", msgnode->value);
      CList_AddSystemMessage(chr_from, PRESENCE_ERROR, r);
    }
    extern volatile int vibra_count;
    Vibrate(1);
  }
}

/*
Получить внутренний номер данного типа присутствия по строке с присутсвием
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
Получить внутренний номер данного типа роли/полномочий по строке с присутсвием
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
