/*
    SieNatJabber Project
    SASL-авторизация

    Организация SASL-авторизации с возможным запросом ZLib-компрессии
    Обработка связанных с этим ошибок
*/

#ifndef _ADV_LOGIN_H_
  #define _ADV_LOGIN_H_

#include "xml_parser.h"

typedef struct
{
  char *nonce;
  char *cnonce;
  char *qop;
  char *rsp_auth;
}SASL_AUTH_DATA;

void Send_Welcome_Packet_SASL();

void SASL_Init_Session();
void Send_Login_Packet();
void Use_Md5_Auth_Report();
void Use_Plain_Auth_Report();
void Process_Auth_Answer(char *challenge);
void SASL_Open_New_Stream();
void SASL_Bind_Resource();
void Decode_Challenge(char *challenge);
void Destroy_SASL_Ctx();
void SASL_Process_Error(XMLNode *nodeEx);
////
void Compression_Ask();
void Compression_Init_Stream();

#endif
