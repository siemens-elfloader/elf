#include "../inc/swilib.h"
#include "main.h"
#include "jabber.h"
#include "clist_util.h"
#include "jabber_util.h"
#include "string_util.h"
#include "groups_util.h"
#include "roster_icons.h"
#include "history.h"
#include "item_info.h"
#include "vCard.h"
#include "lang.h"
#include "..\inc\pnglist.h"
#include "smiles.h"
#include "color.h"

extern const unsigned int DEF_SKR;
CLIST* cltop = NULL;

char Display_Offline;         // Отображать ли оффлайн-пользователей

unsigned int NContacts = 0;       // Всего контактов (и ресурсов) в списке
unsigned int N_Disp_Contacts = 0; // Сколько из них должны отображаться

unsigned int Active_page = 1;     // Текущая активная страница списка
unsigned int N_cont_disp=0;       // Сколько контактов на странице
unsigned int CursorPos = 1;       // Текущая позиция курсора

TRESOURCE* ActiveContact = NULL;

extern char logmsg[512];
extern char My_Presence;
extern const char* PRESENCES[PRES_COUNT];
extern JABBER_STATE Jabber_state;
extern int CLIST_FONT;
/*
Единственная процедура, которая занимается отрисовкой контакт-листа
*/
void CList_RedrawCList()
{
  // Определяем, скока контактов поместится на странице списка
  int font_y = GetFontYSIZE(CLIST_FONT)+2; // ad: думаю что нужно сделать чтобы была 1 строка... пусть контакт вылетает за пределы экрана
  int scr_w=ScreenW();
#ifdef USE_PNG_EXT
  char path_to_pic[128];
#else
  int icon_num=0;
#endif
#ifdef ELKA
  N_cont_disp = sdiv(font_y,ScreenH()-CLIST_Y1-SCR_START)-2;
#else
  N_cont_disp = sdiv(font_y,ScreenH()-CLIST_Y1-SCR_START)-1;
#endif
  if(!cltop)return;

  LockSched();
  N_Disp_Contacts = Display_Offline? CList_GetNumberOfUsers_Visible() : CList_GetNumberOfOnlineUsers();
  // Определяем количество страниц списка контактов
  int pages_number = sdiv(N_cont_disp, N_Disp_Contacts);
  if(N_cont_disp*pages_number<N_Disp_Contacts){pages_number++;};

  CLIST* ClEx = cltop;
  WSHDR* out_ws = AllocWS(256);
  int i=1;
  int start_y;

  RGBA fcolor;
  TRESOURCE* resEx;

  char Alternation = 1;             // ad: состояние чередования
  char Is_Right_Vis_Mode = 0;       // Допустимо ли показывать с точки зрения свернутости групп

  WSHDR* ClEx_name = AllocWS(128);
  WSHDR* ResEx_name = AllocWS(128);

  while(ClEx)
  {
    if(ClEx->ResourceCount)
    {
      resEx = ClEx->res_list;
      while(resEx)
      {

        Is_Right_Vis_Mode = (resEx->entry_type!=T_GROUP && resEx->entry_type!=T_CONF_ROOT && ClEx->IsVisible==1) || (resEx->entry_type==T_CONF_ROOT || resEx->entry_type==T_GROUP) ;
        if((i>(Active_page-1)*N_cont_disp) && ((Display_Offline  |  resEx->status!=PRESENCE_OFFLINE | resEx->has_unread_msg) && Is_Right_Vis_Mode))
        {
          if(i==CursorPos)
          {
            lineColor=CURSOR;
            borderColor=CURSOR_BORDER; //бортик курсора
            ActiveContact = resEx;
          }
          else
          {
            borderColor=lineColor=(Alternation==1)? CONTACT_BG_0 : CONTACT_BG_1;
          }

          //ascii2ws(ClEx_name, ClEx->name);
          utf8_2ws(ClEx_name, ClEx->name, 128);

          if(resEx->name)
          {
            ascii2ws(ResEx_name,resEx->name);
            utf8_2ws(ResEx_name,resEx->name, 128);
            if(resEx->entry_type==T_CONF_NODE)
            {
              wsprintf(out_ws,"%w", ResEx_name); // это участник конференции
            }
            else wsprintf(out_ws,"%w/%w", ClEx_name, ResEx_name); //Это просто ресурс
          }
          else
          {
            wsprintf(out_ws,"%w", ClEx_name);  //другой вид, имхо удобнее
          }


          start_y = CLIST_Y1 + (i - (Active_page-1)*N_cont_disp)*font_y;

          if(resEx->has_unread_msg){fcolor=CLIST_F_COLOR_0;}
          else {fcolor=PRES_COLORS[resEx->status];}

          DrawRoundedFrame(0,start_y+1,scr_w-1,start_y+font_y,0,0,0,
                           color(borderColor),  //ad: ободок
                           color(lineColor));   //ad: рисуем с чередованием... для наглядности

          CutWSTR(out_ws, CHAR_ON_LINE);
          //DrawString(out_ws,16,start_y+2,scr_w-1,start_y+font_y,CLIST_FONT,0,color(fcolor),0); // Перенесено дальше иконки

#ifdef USE_PNG_EXT
          Roster_getIcon(path_to_pic, ClEx, resEx);
          Roster_DrawIcon(1, start_y+((font_y-Roster_getIconHeight(path_to_pic))>>1), (int)path_to_pic);
          DrawString(out_ws,Roster_getIconWidth(path_to_pic)+2,start_y+2,scr_w-1,start_y+font_y,CLIST_FONT,0,color(fcolor),0);
#else
          if (resEx->has_unread_msg)
            icon_num=Roster_getIconByStatus(50); //иконка сообщения
          else
            icon_num=Roster_getIcon(ClEx, resEx);

          Roster_DrawIcon(1, start_y, icon_num) ; //иконка сообщения
          DrawString(out_ws,Roster_getIconWidth(icon_num)+2,start_y+2,scr_w-1,start_y+font_y,CLIST_FONT,0,color(fcolor),0);
#endif

          Alternation=!Alternation; //ad: перещелкиваем чередование
        }
        if((Display_Offline  |  resEx->status!=PRESENCE_OFFLINE | resEx->has_unread_msg) && Is_Right_Vis_Mode) i++;
        resEx = resEx->next;
        if(i>Active_page*N_cont_disp)break;
      }
    }
    ClEx = ClEx->next;
    if(i>Active_page*N_cont_disp)break;
  }

  //  sprintf(logmsg, "P=%d;C=%d;N=%d;ND=%d",Active_page, CursorPos,N_Disp_Contacts,N_cont_disp);
  if(Jabber_state==JS_ONLINE)sprintf(logmsg, "Self=%s",PRESENCES[My_Presence]);
  //  sprintf(logmsg, "Jabber=%d",Jabber_state);
  UnlockSched();
  FreeWS(ClEx_name);
  FreeWS(ResEx_name);
  FreeWS(out_ws);
}


TRESOURCE* CList_GetActiveContact()
{
  return ActiveContact;
}

unsigned int CList_GetNumberOfOnlineUsers()
{
  unsigned int Online=0;
  CLIST* ClEx;
  TRESOURCE* ResEx;
  if(!(ClEx = cltop))return 0;
  while(ClEx)
  {
    ResEx = ClEx->res_list;
    while(ResEx)
    {
      if((ResEx->status!=PRESENCE_OFFLINE || ResEx->has_unread_msg) && (ClEx->IsVisible==1 || ResEx->entry_type==T_GROUP || ResEx->entry_type==T_CONF_ROOT))
        Online++;
      ResEx=ResEx->next;
    }
    ClEx = ClEx->next;
  }
  return Online;
}

unsigned int CList_GetNumberOfUsers() //количество контактов
{
  return NContacts;
}

unsigned int CList_GetNumberOfUsers_Visible()
{
  unsigned int N_Cont = 0;
  CLIST* ClEx;
  TRESOURCE* ResEx;
  if(!(ClEx = cltop)) return 0;

  while(ClEx)
  {
    while(ClEx && (CList_isGroup(ClEx) || CList_isMUC(ClEx)) && ClEx->IsVisible == NULL) //Перескакиваем через свернутые группы и конференции, иначе промахнемся
    {
      char c_group = ClEx->group;
      if (c_group & 0x80) // Пропускаем конференции
        ClEx = ClEx->next;
      else
        while(ClEx && ClEx->group == c_group) // Пропускаем группы
          ClEx = ClEx->next;
      N_Cont++;
    }

    if (!ClEx) return N_Cont;
    
    ResEx = ClEx->res_list;
    while(ResEx)
    {
      N_Cont++;
      ResEx=ResEx->next;
    }
    ClEx = ClEx->next;
  }
  return N_Cont;
}

void CList_ToggleOfflineDisplay()
{
  Display_Offline = !Display_Offline;
  if (CursorPos>CList_GetNumberOfOnlineUsers())
  CursorPos=CList_GetNumberOfOnlineUsers();
  REDRAW();
}

// Убить список сообщений
void KillMsgList(LOG_MESSAGE* messtop)
{
  LOG_MESSAGE* cl=messtop;
  messtop=NULL;
  while(cl)
  {
    LOG_MESSAGE *p;
    mfree(cl->mess);
    if(cl->muc_author)mfree(cl->muc_author);
    p=cl;
    cl=cl->next;
    mfree(p);
  }
}


// Убить список ресурсов
void KillResourceList(TRESOURCE* res_list)
{
  TRESOURCE* cl=res_list;
  while(cl)
  {
    TRESOURCE *p;
    if(cl->name)mfree(cl->name);
    mfree(cl->full_name);
    if(cl->status_msg)mfree(cl->status_msg);
    if(cl->log)KillMsgList(cl->log);
    if(cl->muc_privs.real_jid)mfree(cl->muc_privs.real_jid);
    Free_vCard(cl->vcard);
    p=cl;
    cl=cl->next;
    mfree(p);
    p=NULL;
  }
}

// Получить дескриптор контакта по FullJID (JID вместе с ресурсом)
CLIST* CList_FindContactByJID(char* jid)
{
  LockSched();
  // Преобразуем жид в нижний регистр
  //  char lc_jid[128];
  //  strcpy(lc_jid, jid);
  //  str2lower(lc_jid);
  CLIST* ClEx = cltop;
  while(ClEx)
  {
    //    if(strstr(lc_jid,ClEx->JID)==lc_jid)
    if(stristr(jid,ClEx->JID)==jid && ClEx->res_list->entry_type!=T_GROUP)
    {
      UnlockSched();
      return ClEx;
    }
    ClEx = ClEx->next;
  }
  UnlockSched();
  return NULL;
}
//поиск конфы
MUC_ITEM* CList_FindMUCByJID(char* jid)
{
  LockSched();
  extern MUC_ITEM* muctop;
  MUC_ITEM* McEx = muctop;
  if(McEx)
  while(McEx)
  {
    if(stristr(McEx->conf_jid,jid)==McEx->conf_jid)
    {
      UnlockSched();
      return McEx;
    }
    McEx = McEx->next;
  }
  UnlockSched();
  return NULL;
}

// Добавляет в список контактов системное сообщение
// Полезно, когда происходят действия с подпиской
void CList_AddSystemMessage(char* jid, char status, char* status_msg)
{
  if(status<=PRESENCE_ERROR)
  {
    if(!status_msg)return;
    CList_AddMessage(jid, MSG_STATUS, status_msg);
    return;
  }
  char *sws = malloc(128);
  switch (status)
  {
  case PRESENCE_SUBSCRIBE:   strcpy(sws,LG_AUTHORCAME); break;
  case PRESENCE_SUBSCRIBED:  strcpy(sws,LG_AUTHORGRANTED); break;
  case PRESENCE_UNSUBSCRIBE: strcpy(sws,LG_AUTHORREM); break;
  case PRESENCE_UNSUBSCRIBED:strcpy(sws,LG_AUTHORDECLINE); break;
  }
  WSHDR *wsaut = AllocWS(256);
  wsprintf(wsaut, "%t", sws);
  mfree(sws);
  int len;
  char *saut=malloc(256);
  ws_2utf8(wsaut, saut, &len, 256);
  saut = realloc(saut, len + 1);
  saut[len] = '\0';
  CList_AddMessage(jid, MSG_SYSTEM, saut);
  mfree(saut);
  FreeWS(wsaut);
}

void CList_AddSystemMessageA(char* jid, char status, char* ansi_status_msg)
{
  char *utf8_msg=ANSI2UTF8(ansi_status_msg, 512);
  CList_AddSystemMessage(jid, status, utf8_msg);
  mfree(utf8_msg);
}

// Узнать, есть ли уже такой ресурс у контакта, по FullJID
TRESOURCE* CList_IsResourceInList(char* jid)
{
  CLIST* ClEx = CList_FindContactByJID(jid);
  if(!ClEx)return NULL;
  LockSched();
  TRESOURCE* ResEx = ClEx->res_list;
  while(ResEx)
  {
    if(!stricmp(ResEx->full_name, jid))
    {
      UnlockSched();
      return ResEx;
    }
    ResEx = ResEx->next;
  }
  UnlockSched();
  return NULL;
}


// Поменять статус у контакта
void CList_Ch_Status(TRESOURCE* resource,
                     char status,
                     char* status_msg,
                     short priority
                       )
{
  LockSched();
  if(resource->status_msg)
  {
    mfree(resource->status_msg);
    resource->status_msg = NULL;
  }
  if(status_msg)
  {
    resource->status_msg = malloc(strlen(status_msg)+1);
    strcpy(resource->status_msg, status_msg);
  }
  resource->status = status;
  resource->priority = priority;
  if (status>PRESENCE_INVISIBLE) resource->compos = 0; //сброс компосинга если остался
  UnlockSched();
  CList_AddSystemMessage(resource->full_name, status, status_msg);
}


// Делаем оффлайнами все ресурсы заданного контакта. Useful для конференций.
void CList_MakeAllResourcesOFFLINE(CLIST* ClEx)
{
  if(!ClEx)return;
  TRESOURCE* ResEx = ClEx->res_list;

  while(ResEx)
  {
    CList_Ch_Status(ResEx,
                    PRESENCE_OFFLINE,
                    NULL, 0
                      );
    ResEx = ResEx->next;
  }
}

// Делаем оффлайнами все контакты. Useful для реконнекта *Ы*
void CList_MakeAllContactsOFFLINE()
{
  CLIST *ClEx;
  if(!(ClEx=cltop))return;
  while(ClEx)
  {
    TRESOURCE* ResEx = ClEx->res_list;
    while(ResEx)
    {
      if(ResEx->entry_type!=T_GROUP)
        CList_Ch_Status(ResEx,
                      PRESENCE_OFFLINE,
                       NULL,0
                       );
      ResEx = ResEx->next;
    }
    ClEx = ClEx->next;
  }
}

void CList_ToggleVisibilityForGroup(int GID)
{
  CLIST* ClEx = cltop;
  ClEx = ClEx->next;  //skip (me)
  while(ClEx)
  {
    if(ClEx->group==GID)
    {
      ClEx->IsVisible = !ClEx->IsVisible;
    }
    ClEx = ClEx->next;
  }
}

int CList_GetVisibilityForGroup(int GID)
{
  CLIST* ClEx = cltop;
  while(ClEx)
  {
    if(ClEx->group==GID&&(CList_isGroup(ClEx)))
    {
      return ClEx->IsVisible;
    }
    ClEx = ClEx->next;
  }
  return 1; //Такая группа не найдена. Такого вообще-то не должно быть, но для конференций это именно так.
}

TRESOURCE* CList_AddResourceWithPresence(char* jid, char status, char* status_msg, short priority)
{
  TRESOURCE* qq = CList_IsResourceInList(jid);

  // Если такой ресурс уже есть, его не добавляем.
  // Нужно ему статус поменять.
  if(qq)
  {
    CList_Ch_Status(qq, status, status_msg, priority);
    return qq;
  }
  CLIST* ClEx = cltop;
  LockSched();
  while(ClEx)
  {

    if(stristr(jid,ClEx->JID)==jid && ClEx->res_list->entry_type!=T_GROUP) // Ага, именно так, ибо это соответствует началу строки!
    {
      TRESOURCE* ResEx=malloc(sizeof(TRESOURCE));//ClEx->res_list;
      char *resname_ptr=Get_Resource_Name_By_FullJID(jid);
      if(resname_ptr)
      {
        ResEx->name = malloc(strlen(resname_ptr)+1);
        strcpy(ResEx->name, resname_ptr);
      }
      else
      {
        ResEx->name = NULL;
      }
      ResEx->full_name = malloc(strlen(jid)+1);
      strcpy(ResEx->full_name, jid);

      if(status_msg)
      {
        ResEx->status_msg = malloc(strlen(status_msg)+1);
        strcpy(ResEx->status_msg, status_msg);
      }
      else
      {
        ResEx->status_msg = NULL;
      }

      ResEx->status = status;
      ResEx->priority = priority;
      ResEx->compos = 0;
      ResEx->muc_privs.aff = AFFILIATION_NONE;
      ResEx->muc_privs.role=  ROLE_NONE;
      ResEx->muc_privs.real_jid =  NULL;
      ResEx->vcard = NULL;
      if(!CList_isMUC(ClEx))
         ResEx->entry_type = T_NORMAL;
      else
        ResEx->entry_type = T_CONF_NODE;
      ResEx->has_unread_msg=0;
      ResEx->total_msg_count=0;
      ResEx->log = NULL;

      // Удаляем псевдоресурс, если он есть
      if(ClEx->res_list->entry_type==T_VIRTUAL && ClEx->res_list->has_unread_msg==0)
      {
        KillResourceList(ClEx->res_list);
        ClEx->ResourceCount=0;
        NContacts--;
        ClEx->res_list=NULL;
      }

      TRESOURCE* existing_res=ClEx->res_list;

      if(!existing_res)
      {
        ClEx->res_list = ResEx;
        ClEx->ResourceCount=1;
      }
      else
      {
        while(existing_res->next){existing_res=existing_res->next;}
        existing_res->next = ResEx;
        ClEx->ResourceCount++;
      }
      NContacts++;
      ResEx->next=NULL;
      //CursorPos = 1;
      Active_page=1;
      UnlockSched();
      CList_AddSystemMessage(ResEx->full_name, status, ResEx->status_msg);
      return ResEx;
    }
    ClEx = ClEx->next;
  }
  //CursorPos = 1;
  Active_page=1;
  UnlockSched();
  return NULL;
}

void CList_ChangeContactParams(CLIST* Cont_Ex,
                               char* name,
                               JABBER_SUBSCRIPTION subscription,
                               char wants_subscription,
                               char group)
{

  if(!Cont_Ex)return;
  if(Cont_Ex->name)mfree(Cont_Ex->name);
  // Имя может быть не заполнено
  if(name)
  {
    Cont_Ex->name = malloc(strlen(name)+1);
    strcpy(Cont_Ex->name, name);
  }
  else
  {
    Cont_Ex->name = malloc(strlen(Cont_Ex->JID)+1);
    strcpy(Cont_Ex->name, Cont_Ex->JID);
  }
  Cont_Ex->subscription = subscription;
  Cont_Ex->wants_subscription = wants_subscription;
  Cont_Ex->group = group;
  Cont_Ex->IsVisible = CList_GetVisibilityForGroup(group);
}

void CList_ChangeComposingStatus(TRESOURCE* Res_Ex, char composing)
{
  if(!Res_Ex)return;
  Res_Ex->compos = composing;
}

// Пишет роли контакта в конфе в структуру
void CList_MUC_SetRole(char* jid, CONF_DATA priv)
{
  TRESOURCE* ResEx = CList_IsResourceInList(jid);
  if(!ResEx)
  {
    return;
  }
  if(ResEx->entry_type!=T_CONF_NODE)return;
  ResEx->muc_privs.aff=priv.aff;
  ResEx->muc_privs.role=priv.role;
}

// Добавить к листу контакт. Возвращает структуру созданного контакта.
CLIST* CList_AddContact(char* jid,
                        char* name,
                        JABBER_SUBSCRIPTION subscription,
                        char wants_subscription,
                        char group)
{

  str2lower(jid);
  CLIST* Cont_Ex = malloc(sizeof(CLIST));

  // Имя может быть не заполнено
  if(name)
  {
    Cont_Ex->name = malloc(strlen(name)+1);
    strcpy(Cont_Ex->name, name);
  }
  else
  {
    Cont_Ex->name = malloc(strlen(jid)+1);
    strcpy(Cont_Ex->name, jid);
  }

  Cont_Ex->JID = malloc(strlen(jid)+1);
  strcpy(Cont_Ex->JID, jid);
  Cont_Ex->subscription = subscription;
  Cont_Ex->wants_subscription = wants_subscription;
  Cont_Ex->group = group;
  Cont_Ex->IsVisible = CList_GetVisibilityForGroup(group);
  Cont_Ex->next = NULL;
  Cont_Ex->vcard = NULL; // Не запросили еще

  TRESOURCE* ResEx = malloc(sizeof(TRESOURCE));
  ResEx->vcard = NULL;
  ResEx->log=NULL;
  ResEx->next=NULL;
  ResEx->status_msg=NULL;
  ResEx->priority=0;
  ResEx->muc_privs.real_jid =  NULL;
  ResEx->has_unread_msg=0;
  ResEx->total_msg_count=0;
  ResEx->compos=0;
  if(group & 0x80)
  {
    ResEx->entry_type=T_CONF_ROOT; // Корень конференции
  }
  else
  {
    ResEx->entry_type=T_VIRTUAL; // По этому признаку потом его убъём
    if(!strchr(jid, '@'))
    {
      ResEx->entry_type=T_TRANSPORT; // Транспортный агент
    }
  }
  ResEx->status=PRESENCE_OFFLINE;
  
  ResEx->name = NULL;
  ResEx->full_name = malloc(strlen(jid)+1);
  strcpy(ResEx->full_name, jid);
  //  strcat(ResEx->full_name, "/");
  //  strcat(ResEx->full_name, ResEx->name);
  Cont_Ex->res_list=ResEx;
  Cont_Ex->ResourceCount=1;

  LockSched();
  if(!cltop)
  {
    cltop = Cont_Ex;
  }
  else
  {
    CLIST* tmp=cltop; // А на самом деле наверху списка у нас селф-контакт ;)
    while(tmp->next)
    {
      tmp=tmp->next;
      if(tmp->group==group)break;
    }
    CLIST *after_tmp = tmp->next;
    tmp->next=Cont_Ex;
    Cont_Ex->next =after_tmp;
  }

  NContacts++;
  UnlockSched();
  //CursorPos = 1;
  Active_page=1;
  return Cont_Ex;
}


// Добавить сообщение в список сообщений контакта
void CList_AddMessage(char* jid, MESS_TYPE mtype, char* mtext)
{
  TTime now_time;
  TDate now_date;
  GetDateTime(&now_date,&now_time);
  char datestr[200];

  char IsMe = strstr(mtext,"/me ")==mtext ? 1 : 0; // Флаг наличия /me
  if(mtype==MSG_ME)
  {
    extern char My_JID[128];
    sprintf(datestr, "%s: %02d:%02d %02d-%02d\r\n",My_JID,now_time.hour,now_time.min,now_date.day,now_date.month);
  }
  else
  {
    sprintf(datestr, "%s: %02d:%02d %02d-%02d\r\n",jid,now_time.hour,now_time.min,now_date.day,now_date.month);
  }


  CLIST* contEx = CList_FindContactByJID(jid);
  if(!contEx)
  {
    // Фикс - добавляем контакт в ростер, временно
    unsigned short jidlen = ((int)strchr(jid, '/') - (int)jid);
    char *qjid = malloc(jidlen+1);
    strncpy(qjid, jid, jidlen);
    qjid[jidlen]=0x0;
    ShowMSG(1,(int)qjid);
    contEx = CList_AddContact(qjid, qjid, SUB_NONE, 0, 0);
    mfree(qjid);
    CList_AddResourceWithPresence(jid, PRESENCE_OFFLINE, NULL,0);
  }
  TRESOURCE* cont = (contEx->group & 0x80 && (mtype==MSG_GCHAT || mtype==MSG_SUBJECT)) ? contEx->res_list : CList_IsResourceInList(jid);
  if(!cont)
  {
    // У контакта нет ресурсов или такого ресурса нет. Добавляем на первый же.
    // Такая ситуация, скорее всего, возникает, если у контакта ресурсов не
    // бывает в принципе (MRIM)
    cont=contEx->res_list;
  }

  if(!cont->total_msg_count && mtype==MSG_STATUS && cont->entry_type!=T_CONF_ROOT)return;  // Не записываем статусные сообщения, если нет беседы

  if(mtype!=MSG_ME && mtype!=MSG_STATUS)cont->has_unread_msg++;
  LOG_MESSAGE* mess = malloc(sizeof(LOG_MESSAGE));
  char timestamp[]="[%02d:%02d] ";
  snprintf(timestamp, 12, timestamp, now_time.hour, now_time.min);
  switch(mtype)
  {
  case MSG_GCHAT:
    {
      char* conf_nickname = Get_Resource_Name_By_FullJID(jid);
      if(!conf_nickname)
      {
        extern const char empty_t[];
        conf_nickname=(char*)&empty_t;
      }
      mess->mess = malloc(strlen(mtext)+strlen(conf_nickname)+strlen(timestamp)+2+1);
      mess->muc_author = malloc(strlen(conf_nickname)+1);
      strcpy(mess->muc_author, conf_nickname);
      strcpy(mess->mess, timestamp);
      if(IsMe)
      {
        strcat(mess->mess, "*");
        strcat(mess->mess, conf_nickname);
        strcat(mess->mess, mtext+3);  // пропуск /me
      }
      else
      {
        strcat(mess->mess, conf_nickname);
        strcat(mess->mess, ": ");
        strcat(mess->mess, mtext);
      }
      break;
    }
  case MSG_SUBJECT:
    {
      char* conf_nickname = Get_Resource_Name_By_FullJID(jid);
      char subj_set_to[] = " has set the subject: ";
      mess->mess = malloc(strlen(mtext)+strlen(conf_nickname)+strlen(timestamp)+strlen(subj_set_to)+1);
      mess->muc_author = malloc(strlen(conf_nickname)+1);
      strcpy(mess->muc_author, conf_nickname);
      strcpy(mess->mess, timestamp);
      strcat(mess->mess, conf_nickname);
      strcat(mess->mess, subj_set_to);
      strcat(mess->mess, mtext);
      break;
    }
  default:
    {
      mess->mess = malloc(strlen(mtext)+strlen(timestamp)+1);
      strcpy(mess->mess, timestamp);
      strcat(mess->mess, mtext);
      mess->muc_author = NULL;
    }
  }
  mess->mtype=mtype;
  LockSched();
  if(!cont->log)
  {
    cont->log = mess;
  }
  else
  {
    LOG_MESSAGE* tmp=cont->log;
    while(tmp->next){tmp=tmp->next;}
    tmp->next=mess;
  }
  cont->total_msg_count++;
  mess->next=NULL;
  UnlockSched();

  extern const int WRITE_HISTORY, WRITE_MUC_HISTORY;


  if((WRITE_HISTORY && !(cont->entry_type==T_CONF_ROOT)) || (WRITE_MUC_HISTORY && (cont->entry_type==T_CONF_ROOT)))
  {
    Add2History(CList_FindContactByJID(jid), datestr,mtext);
  }
}
// Уничтожить список контактов
void CList_Destroy()
{
  LockSched();
  CLIST* cl=cltop;
  cltop=NULL;
  while(cl)
  {
    CLIST *p;
    if(cl->res_list) KillResourceList(cl->res_list);
    cl->ResourceCount=0;
    Free_vCard(cl->vcard);
    mfree(cl->JID);
    mfree(cl->name);
    p=cl;
    cl=(CLIST*)(cl->next);
    mfree(p);
    p=NULL;
  }
  UnlockSched();
}


// Отображение всякого спама про контакт
void CList_Display_Popup_Info(TRESOURCE* ResEx)
{
  if(!ResEx)return;
  Disp_Info(ResEx);
}


char qqq[100];

// бегаем по контактам с сообщениями
void nextUnread()
{
  if (CList_GetUnreadMessages()==0) return; //выйдем если нет непрочитанных
  CLIST* ClEx;
  TRESOURCE* ResEx;
  if(!(ClEx = cltop))return;
  LockSched();
  while(ClEx) //идем по списку контактов
  {
    ResEx = ClEx->res_list;
    while(ResEx) //идем по списку ресурсов
    {
      if(ResEx->has_unread_msg) //если есть непрочитанное
      {
        if (CList_GetActiveContact()!=ResEx)//если мы не стоим на этом контакте
        {
          if (!CList_isMUC(ClEx))
          {
            if (!CList_GetVisibilityForGroup(ClEx->group)) //если группа контакта свернута, надо ее развернуть, иначе плохо будет
              CList_ToggleVisibilityForGroup(ClEx->group);
          }
          else
          {
            if (!ClEx->IsVisible) // Разворачиваем конференцию
              ClEx->IsVisible = 1;
          }
          MoveCursorTo(ResEx);
          break;
        }
      }
      ResEx=ResEx->next; //следующий ресурс
    }
    ClEx = ClEx->next; //следующий контакт
  }
  UnlockSched();
}

unsigned int CList_GetUnreadMessages() //количество непрочитанных сообщений
{
  unsigned int unread=0;
  CLIST* ClEx;
  TRESOURCE* ResEx;
  if(!(ClEx = cltop))return 0;
  while(ClEx)
  {
    ResEx = ClEx->res_list;
    while(ResEx)
    {
      if(ResEx->has_unread_msg)
        unread+=ResEx->has_unread_msg;
      ResEx=ResEx->next;
    }
    ClEx = ClEx->next;
  }
  return unread;
};

// Ставим курсор на нужный ресурс
void MoveCursorTo(TRESOURCE* NewResEx)
{
  if(!NewResEx)return;

  CLIST* ClEx;
  TRESOURCE* ResEx;
  if(!(ClEx = cltop))return;

  int pos=0;
  while(ClEx)
  {
    while((CList_isGroup(ClEx) || CList_isMUC(ClEx)) && ClEx->IsVisible == NULL) //Перескакиваем через свернутые группы и конференции, иначе промахнемся
    {
      char c_group = ClEx->group;
      if (c_group & 0x80) // Пропускаем конференции
      {
        if (!ClEx->next) return;
        ClEx = ClEx->next;
      }
      else
      {
        while(ClEx->group == c_group) // Пропускаем группы
        {
          if (!ClEx->next) return;
          ClEx = ClEx->next;
        }
      }
      pos ++;
    }

    ResEx = ClEx->res_list;
    while(ResEx)
    {
      if(ResEx==NewResEx)
      {
        //ставим курсор на клиента
        CursorPos=pos+1;
        //тут надо бы еще проверит на какой мы странице.. а то вдруг не там и курсор проебется :-D
        // сначала считаем на какой странице должен быть курсор
        if (CursorPos>N_cont_disp)
          Active_page = sdiv(N_cont_disp, CursorPos)+1;
        else
          Active_page=1;
        REDRAW();
        break;
      }
      if (Display_Offline || ResEx->status!=PRESENCE_OFFLINE)
        pos++;
      ResEx=ResEx->next;
    }
    ClEx = ClEx->next;
  }
};


// Управление курсором
void CList_MoveCursorUp(int flagi)
{
  if(!N_Disp_Contacts)return;
  if(CursorPos<=1)
  {
    CursorPos=N_Disp_Contacts;
    if (N_cont_disp==N_Disp_Contacts)
      Active_page = 1;
    else
      Active_page = sdiv(N_cont_disp, N_Disp_Contacts)+1;
  }
  else
  {
    if (flagi)
      CursorPos=CursorPos-DEF_SKR;
    else
      CursorPos--;
    
    if (CursorPos<=(Active_page-1)*N_cont_disp)
      Active_page--;
  }
  REDRAW();
};


void CList_MoveCursorDown(int flagi)
{
  if (!N_Disp_Contacts)
    return;
  if(flagi==1)
  {
    if (CursorPos==(N_Disp_Contacts+1))
    {
      CursorPos=1;
      Active_page=1;
    }
    else
    {
      CursorPos=CursorPos+DEF_SKR;
      if(CursorPos>(N_Disp_Contacts+1))
      {
        CursorPos=(N_Disp_Contacts+1);
        Active_page = sdiv(N_cont_disp, N_Disp_Contacts)+1;
      }
    }
  }
  if(flagi==0)
  {
    CursorPos++;
    if(CursorPos>N_Disp_Contacts/*+1*/)
    {
      CursorPos=1;
      Active_page=1;
    }
  }
  if(Active_page*N_cont_disp<CursorPos){Active_page++;}
  REDRAW();
}
void CList_MoveCursorHome()
{
  if(!N_Disp_Contacts)return;
  CursorPos =1;
  Active_page = 1;
  REDRAW();
}

void CList_MoveCursorEnd()
{
  if(!N_Disp_Contacts)return;
  CursorPos = N_Disp_Contacts;
  Active_page = sdiv(N_cont_disp, N_Disp_Contacts)+1;
  REDRAW();
}

int CList_isGroup(CLIST *cont)
{
  if(cont->ResourceCount==0) return 0;
  if(cont->res_list->entry_type==T_GROUP) return 1;
  return 0;
}

int CList_isMUC(CLIST *cont)
{
  if(cont->ResourceCount==0) return 0;
  if(cont->res_list->entry_type==T_CONF_ROOT) return 1;
  return 0;
}
//EOL,EOF
