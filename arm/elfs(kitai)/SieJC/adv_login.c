#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "xml_parser.h"
#include "base64.h"
#include "md5.h"
#include "jabber.h"
#include "jabber_util.h"
#include "history.h"
#include "adv_login.h"

extern JABBER_STATE Jabber_state;
extern const char JABBER_SERVER[];
extern const char USERNAME[];
extern const char PASSWORD[];
extern const char RESOURCE[30];
extern char My_JID_full[];
extern char My_JID[];
extern char logmsg[];

SASL_AUTH_DATA SASL_Auth_data = {NULL, NULL, NULL, NULL};


void Send_Welcome_Packet_SASL()
{
  char streamheader[]="<?xml version='1.0' encoding='UTF-8'?>\n"
    "<stream:stream to='%s' xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' xml:lang='en' version='1.0'>";
  char* buf=malloc(256);
  sprintf(buf,streamheader,JABBER_SERVER);
  SendAnswer(buf);
  mfree(buf);
  LockSched();
  strcat(logmsg,"\nSend Extended Welcome");
  UnlockSched();
#ifdef LOG_ALL
  Log("CONN",logmsg);
#endif
}

void Destroy_SASL_Ctx()
{
  if(SASL_Auth_data.nonce)mfree(SASL_Auth_data.nonce);
  if(SASL_Auth_data.cnonce)mfree(SASL_Auth_data.cnonce);
  if(SASL_Auth_data.qop)mfree(SASL_Auth_data.qop);
  if(SASL_Auth_data.rsp_auth)mfree(SASL_Auth_data.rsp_auth);
  zeromem(&SASL_Auth_data, sizeof(SASL_AUTH_DATA));
}

// �������� ������� �� ������������� �������������� MD5-DIGEST
//Context:HELPER
void Use_Md5_Auth_Report()
{
  char s[]="<auth xmlns='urn:ietf:params:xml:ns:xmpp-sasl' mechanism='DIGEST-MD5'/>";
  Jabber_state = JS_SASL_NEGOTIATION;
  SendAnswer(s);
}

// �������� ������� �� ������������� �������������� PLAIN
//Context:HELPER
void Use_Plain_Auth_Report()
{
// �� ������� e:\CPP_Proj\Miranda_IM\miranda\protocols\JabberG\jabber_secur.cpp

  char s[]="<auth xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\" mechanism=\"PLAIN\">%s</auth>";
  char patt[]="%s@%s%c%s%c%s";
  unsigned short patlen = strlen(USERNAME)*2 + strlen(JABBER_SERVER) + strlen(PASSWORD) + 3;
  char *authdata = malloc(patlen+1);
  zeromem(authdata, patlen+1);
  snprintf(authdata, patlen+1, patt, USERNAME, JABBER_SERVER, 0, USERNAME, 0, PASSWORD);
  char *Data_To_Send;
  base64_encode(authdata, patlen,&Data_To_Send);
  char *fin = malloc(strlen(Data_To_Send) + strlen(s) + 1 - 2); // ��� %s ��� �� ���� �������
  sprintf(fin, s, Data_To_Send);
  Jabber_state = JS_SASL_AUTH_ACK;  // ����� - ���������� ��������� ������ ;)
  SendAnswer(fin);
  mfree(Data_To_Send);
  mfree(authdata);
  mfree(fin);
}

// ��������� ����� ����� � ������� �� ��������� �����������
void SASL_Open_New_Stream()
{
  Jabber_state = JS_SASL_NEW_STREAM_ACK;
  SUBPROC((void*)Send_Welcome_Packet_SASL);
}

// ��������� Resource Binding
void SASL_Bind_Resource()
{
  sprintf(My_JID, "%s@%s",USERNAME, JABBER_SERVER);
  sprintf(My_JID_full,"%s/%s",My_JID, RESOURCE);

  sprintf(logmsg, "Resource binding");
  REDRAW();
  char *bind_tpl = malloc(256);
  sprintf(bind_tpl, "<iq type='set' id='SieJC_bind_req'>"
                  "<bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'>"
                  "<resource>%s</resource>"
                  "</bind>"
                  "</iq>", RESOURCE);
  Jabber_state = JS_SASL_RESBIND_ACK;
  SUBPROC((void*)_sendandfree, bind_tpl);
}

// ������������� ������
void SASL_Init_Session()
{
  sprintf(logmsg, "Session Init");
  REDRAW();

static char sess_init_tpl[]="<iq type='set' id='SieJC_sess_req'>"
                  "<session xmlns='urn:ietf:params:xml:ns:xmpp-session'/>"
                  "</iq>";

  Jabber_state = JS_SASL_SESS_INIT_ACK;
  SUBPROC((void*)SendAnswer, sess_init_tpl);
}

void Decode_Challenge(char *challenge)
{
  char *decoded_challenge = malloc(1024);
  base64_decode(challenge, decoded_challenge);
  SASL_Auth_data.nonce = Get_Param_Value(decoded_challenge, "nonce",1);
  SASL_Auth_data.qop   = Get_Param_Value(decoded_challenge, "qop",1);

//SASL_Auth_data.nonce = malloc(128);strcpy(SASL_Auth_data.nonce,"455564019");
//SASL_Auth_data.qop = malloc(128);strcpy(SASL_Auth_data.qop,"auth");

  mfree(decoded_challenge);
  char *cnonce= malloc(60);
  strcpy(cnonce, "7425da72aliuf242765");
  SASL_Auth_data.cnonce = cnonce;
}

void mkhex(md5_byte_t digest[16], char *hex_output)
{
  for (int di = 0; di < 16; ++di)sprintf(hex_output + di * 2, "%02x", digest[di]);
}

char ans[]="<response xmlns='urn:ietf:params:xml:ns:xmpp-sasl'/>";

void Process_Auth_Answer(char *challenge)
{
  char *decoded_challenge = malloc(256);
  base64_decode(challenge, decoded_challenge);
  SASL_Auth_data.rsp_auth   = Get_Param_Value(decoded_challenge, "rspauth",0);
  mfree(decoded_challenge);
  Jabber_state = JS_SASL_AUTH_ACK;
  SUBPROC((void*)SendAnswer,ans);
}


void Send_Login_Packet()
{
  md5_state_t state;
  md5_byte_t digest[16];
  md5_byte_t  A1[16], A2[16], Response[16];
  char colon_t[]=":";
  char _00000001[]="00000001";
  char hex_output[16*2 + 1];
  char A1_HEX[16*2 + 1];
  char A2_HEX[16*2 + 1];
  char R_HEX[16*2 + 1];

  char *digest_uri = malloc(128);
  char realm[]="";
  char *User_Realm_Pass = malloc(256);
  zeromem(digest_uri, 128);
  snprintf(digest_uri, 127, "AUTHENTICATE:xmpp/%s", JABBER_SERVER);

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)USERNAME, strlen(USERNAME));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)realm, strlen(realm));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)PASSWORD, strlen(PASSWORD));
  md5_finish(&state, digest);
  mkhex(digest, hex_output);

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)digest, 16);      // (MD5(user:realm:pass)
  md5_append(&state, (const md5_byte_t *)colon_t,1);            // :
  md5_append(&state, (const md5_byte_t *)SASL_Auth_data.nonce,strlen(SASL_Auth_data.nonce));
  md5_append(&state, (const md5_byte_t *)colon_t,1);            // :
  md5_append(&state, (const md5_byte_t *)SASL_Auth_data.cnonce,strlen(SASL_Auth_data.cnonce));
  md5_finish(&state, A1);
  mkhex(A1, A1_HEX);

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)digest_uri, strlen(digest_uri));
  md5_finish(&state, A2);
  mkhex(A2, A2_HEX);

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)A1_HEX, strlen(A1_HEX));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)SASL_Auth_data.nonce,strlen(SASL_Auth_data.nonce));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)_00000001, strlen(_00000001));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)SASL_Auth_data.cnonce,strlen(SASL_Auth_data.cnonce));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)SASL_Auth_data.qop,strlen(SASL_Auth_data.qop));
  md5_append(&state, (const md5_byte_t *)colon_t,1);
  md5_append(&state, (const md5_byte_t *)A2_HEX, strlen(A2_HEX));
  md5_finish(&state, Response);
  mkhex(Response, R_HEX);

  char *Response_STR = malloc(1024);
  zeromem(Response_STR, 1024);
  char Res_tpl[]=
    "username=\"%s\",realm=\"%s\",nonce=\"%s\",nc=00000001,cnonce=\"%s\","
                "qop=auth,digest-uri=\"xmpp/%s\",response=\"%s\",charset=utf-8";
  snprintf(Response_STR, 1024, Res_tpl,
           USERNAME,
           realm,
           SASL_Auth_data.nonce,
           SASL_Auth_data.cnonce,
           JABBER_SERVER,
           R_HEX
           );
  char *Result_Resp;
  base64_encode(Response_STR, strlen(Response_STR),&Result_Resp);
  char resp_full_tpl[]="<response xmlns='urn:ietf:params:xml:ns:xmpp-sasl'>%s</response>";
  char *resp_full = malloc(1024);
  zeromem(resp_full, 1024);
  snprintf(resp_full, 1023, resp_full_tpl, Result_Resp);
  Jabber_state=JS_SASL_NEG_ANS_WAIT;
  SUBPROC((void*)_sendandfree, resp_full);
  mfree(Result_Resp);
  mfree(Response_STR);
  mfree(digest_uri);
  mfree(User_Realm_Pass);
}

// ��������� ������ SASL
void SASL_Process_Error(XMLNode *nodeEx)
{
  Jabber_state=JS_ERROR;
  XMLNode *err = nodeEx->subnode;
  if(err)
  {
    strcpy(logmsg, "SASL error!\n");
    strcat(logmsg, err->name);  // �� ����-�������
    if(!strcmp(err->name, SASLERR_NOTAUTH))strcat(logmsg, "\nBad password");
  }
}
////////////////////////////////////////////////////////////////////////////////

// ������ ���������� � �������
void Compression_Ask()
{
static  char zlib_ask[]="<compress xmlns='http://jabber.org/protocol/compress'>"
                  "<method>zlib</method>"
                  "</compress>";
  Jabber_state = JS_ZLIB_INIT_ACK;
  SUBPROC((void*)SendAnswer,zlib_ask);
  strcat(logmsg, "\nUsing ZLib ack");
}

//Context:HELPER
void Compression_Send_Header()
{
  char cMethod = 8;
  char cInfo = 3;
  char cm = (char) (cMethod | (cInfo << 4));
  extern int sock;
  send(sock,&cm,1,0);
  char flags = 0;// bez dictu a fastest
  if ((cm * 256 + flags) % 31 != 0)
  {
    flags += 31 - ((cm * 256 + flags) % 31);
  }
  send(sock,&flags,1,0);
}


//Context:HELPER
void Send_New_stream()
{
  Jabber_state = JS_ZLIB_STREAM_INIT_ACK;
  Compression_Send_Header();
  Send_Welcome_Packet_SASL();
}

//GBSTMR Newstream;
// ������������� ������ ������ (��� �������)
void Compression_Init_Stream()
{
  strcat(logmsg, "\nOK, ZLib enable...");
  extern char Is_Compression_Enabled;
  Is_Compression_Enabled = 1;
  SUBPROC((void*)Send_New_stream);
}

//EOL,EOF
