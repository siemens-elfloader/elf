#include "../inc/swilib.h"
#include "main.h"
#include "clist_util.h"
#include "xml_parser.h"
#include "base64.h"
#include "siejc_ipc.h"
#include "history.h"
#include "lang.h"
#include "string_util.h"
#include "jabber_util.h"
#include "vCard.h"

#define N_VCARD_FIELDS 51

char *vcard_index[N_VCARD_FIELDS] =
{
  "JABBERID",
  "FN",
  
  "N/FAMILY",
  "N/GIVEN",
  "N/MIDDLE",
  "N/PREFIX",
  "N/SUFFIX",

  "NICKNAME",
  "BDAY",
  "GENDER",

  "ORG/ORGNAME",
  "ORG/ORGUNIT",
  "TITLE",
  "ROLE",

  "EMAIL/USERID",
  "EMAIL/HOME",
  "EMAIL/WORK",
  "EMAIL/INTERNET",
  "EMAIL/PREF",
  "EMAIL/X400",

  "TEL/HOME",
  "TEL/WORK",
  "TEL/VOICE",
  "TEL/FAX",
  "TEL/PAGER",
  "TEL/MSG",
  "TEL/CELL",
  "TEL/VIDEO",
  "TEL/BBS",
  "TEL/MODEM",
  "TEL/ISDN",
  "TEL/PCS",
  "TEL/PREF",
  "TEL/NUMBER",

  "ADR/HOME",
  "ADR/WORK",
  "ADR/POSTAL",
  "ADR/PARCEL",
  "ADR/DOM",
  "ADR/PREF",
  "ADR/POBOX",
  "ADR/EXTADD",
  "ADR/STREET",
  "ADR/LOCALITY",
  "ADR/REGION",
  "ADR/PCODE",
  "ADR/CTRY",
    
  "URL",

  "DESC",
  "TZ",

  "!PHOTO" // ���� �� ����� ���� � �������
};

char *vcard_names[N_VCARD_FIELDS] =
{
  LG_VCARD_JABBERID,
  LG_VCARD_FN,
  LG_VCARD_N_FAMILY,
  LG_VCARD_N_GIVEN,
  LG_VCARD_N_MIDDLE,
  LG_VCARD_N_PREFIX,
  LG_VCARD_N_SUFFIX,
  LG_VCARD_NICKNAME,
  LG_VCARD_BDAY,
  LG_VCARD_GENDER,

  LG_VCARD_ORGNAME,
  LG_VCARD_ORGUNIT,
  LG_VCARD_TITLE,
  LG_VCARD_ROLE,

  LG_VCARD_EMAIL,
  LG_VCARD_EMAIL_HOME,
  LG_VCARD_EMAIL_WORK,
  LG_VCARD_EMAIL_INTERNET,
  LG_VCARD_EMAIL_PREF,
  LG_VCARD_EMAIL_X400,
  
  LG_VCARD_TEL_HOME,
  LG_VCARD_TEL_WORK,
  LG_VCARD_TEL_VOICE,
  LG_VCARD_TEL_FAX,
  LG_VCARD_TEL_PAGER,
  LG_VCARD_TEL_MSG,
  LG_VCARD_TEL_CELL,
  LG_VCARD_TEL_VIDEO,
  LG_VCARD_TEL_BBS,
  LG_VCARD_TEL_MODEM,
  LG_VCARD_TEL_ISDN,
  LG_VCARD_TEL_PCS,
  LG_VCARD_TEL_PREF,
  LG_VCARD_TEL_NUMBER,

  LG_VCARD_ADR_HOME,
  LG_VCARD_ADR_WORK,
  LG_VCARD_ADR_POSTAL,
  LG_VCARD_ADR_PARCEL,
  LG_VCARD_ADR_DOM,
  LG_VCARD_ADR_PREF,
  LG_VCARD_ADR_POBOX,
  LG_VCARD_ADR_EXTADD,
  LG_VCARD_ADR_STREET,
  LG_VCARD_ADR_LOCALITY,
  LG_VCARD_ADR_REGION,
  LG_VCARD_ADR_PCODE,
  LG_VCARD_ADR_CTRY,

  LG_VCARD_URL,

  LG_VCARD_DESC,
  LG_VCARD_TZ,

  LG_VCARD_AVATAR
};

// ��������� �������, ��������� ��������� vCard
void Add_vCard_Value(VCARD dest, char *par_name, char *val)
{
  int field_id = 0;
  while (field_id<N_VCARD_FIELDS && strcmp(par_name, vcard_index[field_id]))
    field_id++;
  if (field_id<N_VCARD_FIELDS)
  {
    if (!dest[field_id])
      dest[field_id] = malloc(strlen(val)+1);
    strcpy(dest[field_id], val);
  }
}

char *Get_VCard_Value(VCARD src, char *par_name)
{
  int field_id = 0;
  while (field_id<N_VCARD_FIELDS && strcmp(par_name, vcard_index[field_id]))
    field_id++;
  if (field_id<N_VCARD_FIELDS)
  {
    return src[field_id];
  }
  return NULL;
}

VCARD Create_vCard()
{
  VCARD tmp = malloc(4*N_VCARD_FIELDS);
  zeromem(tmp, 4*N_VCARD_FIELDS);
  return tmp;
}

void Free_vCard(VCARD vcard)
{
  if (!vcard)
    return;
  for (int i=0; i<N_VCARD_FIELDS; i++)
    if (vcard[i])
      mfree(vcard[i]);
  mfree(vcard);
}


//==============================   AVATAR   ================================

extern const char DEFAULT_DISC[128];
extern const char ipc_my_name[32];
extern const char PATH_TO_AVATARS[128];
const char _slash[2] = "\\";

void Get_Avatar_Path(char *path, char *jid)
{
  strcpy(path, PATH_TO_AVATARS);
  TRESOURCE *ResEx = CList_IsResourceInList(jid);
  CLIST *ClEx = CList_FindContactByJID(jid);
  unsigned int err;
  if (ResEx)
  {
    if (ResEx->entry_type==T_CONF_NODE)
    {
      char *s1, *s2;
      s1 = utf82filename(ClEx->JID);
      strcat(path, s1);
      if (!isdir(path, &err))
        mkdir(path, &err);
      strcat(path, _slash);
      s2 = utf82filename(ResEx->name);
      strcat(path, s2);
      mfree(s1);
      mfree(s2);
    }
    else
    {
      char *s1;
      s1 = utf82filename(ClEx->JID);
      strcat(path, ClEx->JID);
      mfree(s1);
    }
  }
}

void vCard_Photo_Display(char *path)
{
  WSHDR *fp = AllocWS(128);
  str_2ws(fp,path,128);
  ExecuteFile(fp, NULL, NULL);
  FreeWS(fp);
}

//Context:HELPER
void DecodePhoto(char *path, void *data)
{
  char *buf = malloc(strlen(data));
  int binlen = base64_decode(data, buf);
  unsigned int ec = 0;
  unlink(path, &ec);
  ec=0;   // ������, ��� ���������� ��������.
  volatile int f = fopen(path, A_ReadWrite +A_Create+ A_Append + A_BIN, P_READ+ P_WRITE, &ec);
  if(!ec)
  {
    fwrite(f, buf, binlen, &ec);
    fclose(f, &ec);
  }
  else
  {
    LockSched();
    MsgBoxError(1,(int)path);
    UnlockSched();
  }

  /* // ������ ������ �� �������
  // Display
  if(Saved_OK)
  {
    //WSHDR *fp = AllocWS(128);
    //str_2ws(fp,full_path,128);
    //ExecuteFile(fp, NULL, NULL);
    //FreeWS(fp);
    char *fp = malloc(128);
    strcpy(fp, path);

    vcard_ipc.name_to=ipc_my_name;
    vcard_ipc.name_from=ipc_my_name;
    vcard_ipc.data=fp;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_AVATAR_DECODE_OK,&vcard_ipc);
  }
  */

  // Cleanup
  mfree(buf);
  mfree(data);
  mfree(path);
}

// ���������� ����������
void SavePhoto(VCARD vcard, char *jid, XMLNode *photonode)
{
  // Prepare path
  char ph_path[128];
  Get_Avatar_Path(ph_path, jid);
  char extension[]=".jpg";
  XMLNode *ph_node = XML_Get_Child_Node_By_Name(photonode, "TYPE");
  if(ph_node)
  {
    char *ph_node_val = ph_node->value;
    if(!strcmp(ph_node_val, "image/jpeg"))
    {
      strcpy(extension,".jpg");
    }
    else if(!strcmp(ph_node_val, "image/png"))
    {
      strcpy(extension,".png");
    }
    else if(!strcmp(ph_node_val, "image/gif"))
    {
      strcpy(extension,".gif");
    }
  }
  char *full_path = malloc(128);
  strcpy(full_path, ph_path);
  strcat(full_path, extension);
  Add_vCard_Value(vcard, "!PHOTO", full_path);

  // Decode & write
  XMLNode *binval = XML_Get_Child_Node_By_Name(photonode, "BINVAL");
  int ln = strlen(binval->value);
  char *buf = malloc(ln);
  memcpy(buf, binval->value, ln);
  SUBPROC((void*)DecodePhoto, full_path, buf);
}

// ���������� vCard
void Process_vCard(char *from, XMLNode *vCard)
{
  int Use_Resource = 0;
  TRESOURCE *ResEx = CList_IsResourceInList(from);
  if (ResEx->entry_type==T_CONF_NODE) // ���� ����������� - ���������� ������
    Use_Resource = 1;
  CLIST *ClEx = CList_FindContactByJID(from);

  VCARD vcard;
  if (Use_Resource)
    vcard = ResEx->vcard;
  else
    vcard = ClEx->vcard;
  if (!vcard)
    vcard = Create_vCard();

  // ������� ��� ���������� ���� vCard
  char field_name[256];
  XMLNode *vCard_Node = vCard->subnode;
  XMLNode *vCard_NodeL2;
  while(vCard_Node)
  {
    //if(vCard_Node->name && vCard_Node->value) // ���� �� �������� Photo, � ����� ����
    //  Add_vCard_Value(vcard, vCard_Node->name, vCard_Node->value);
    if (vCard_Node->name)
    {
      if (vCard_Node->value)
        Add_vCard_Value(vcard, vCard_Node->name, vCard_Node->value);
      if (strcmp(vCard_Node->name, "PHOTO") && strcmp(vCard_Node->name, "PHOTO")) // �� ��� ��� ��� ������� � �������...
      {
        vCard_NodeL2 = vCard_Node->subnode;
        while (vCard_NodeL2) // ������������ ���� ������ �����������
        {
          if (vCard_NodeL2->name && vCard_NodeL2->value)
          {
            sprintf(field_name, "%s/%s", vCard_Node->name, vCard_NodeL2->name);
            Add_vCard_Value(vcard, field_name, vCard_NodeL2->value);
          }

          vCard_NodeL2 = vCard_NodeL2->next;
        }
      }
    }

    vCard_Node = vCard_Node->next;
  }

  // Save photo :))
  XMLNode *photo = XML_Get_Child_Node_By_Name(vCard,"PHOTO");
  if(photo)
    if(photo->subnode)SavePhoto(vcard, from, photo);

  // ���������� vCard

  if (Use_Resource)
    ResEx->vcard = vcard;
  else
    ClEx->vcard = vcard;

  Show_vCard(from);
}

int Show_vCard2(char *jid)
{
  CLIST *ClEx = CList_FindContactByJID(jid);
  if (!ClEx)
    return 0;
  VCARD vcard = ClEx->vcard;
  if (!vcard) // ���� �� ����� - ���� � ������� (��� �����������)
  {
    TRESOURCE *ResEx = CList_IsResourceInList(jid);
    if (ResEx)
      vcard = ResEx->vcard;
  }
  if (vcard)
  {
    char *result = malloc(1024);
    int result_len = 1024;
    strcpy(result, "VCard:\n");
    char *param_pair = malloc(2048);
    for (int i=0; i<N_VCARD_FIELDS; i++)
      if (vcard[i])
      {
        char *parname = ANSI2UTF8(vcard_names[i], 1024);
        snprintf(param_pair, 2048, "%s: %s\n", parname+1 /* +1 - ��� ����� ���, �� �������� */, vcard[i]);
        mfree(parname);
        unsigned int real_result_len, parpair_len;
        real_result_len = strlen(result);
        parpair_len = strlen(param_pair);
        while(real_result_len+parpair_len>result_len)
        {
          result_len += 1024;
          result = realloc(result, result_len);
        }
        strcat(result,param_pair);
      }
    CList_AddMessage(jid, MSG_SYSTEM, result);
    mfree(param_pair);
    mfree(result);
    return 1;
  }
  return 0;
}

//====================   GUI   ========================

typedef struct
{
  char *jid;
  int update_pos;
  int photo_show_pos;
} VCARD_VIEW_DESC;

int vcinfo_onkey(GUI *gui, GUI_MSG *msg)
{
  VCARD_VIEW_DESC *desc = EDIT_GetUserPointer(gui);
  if (desc)
  {
    if (msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON && EDIT_GetFocus(gui)==desc->update_pos)
    {
      CLIST *ClEx = CList_FindContactByJID(desc->jid);
      if (ClEx)
      {
        if (ClEx->vcard)
        {
          Free_vCard(ClEx->vcard);
          ClEx->vcard = NULL;
          Send_Vcard_Request(desc->jid);
        }
        else // ���� �� ����� - ���� � ������� (��� �����������)
        {
          TRESOURCE *ResEx = CList_IsResourceInList(desc->jid);
          if (ResEx)
            if (ResEx->vcard)
            {
              Free_vCard(ResEx->vcard);
              ResEx->vcard = NULL;
              Send_Vcard_Request(desc->jid);
            }
        }
      }
      return (1); //Exit
    }
    if (msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON && EDIT_GetFocus(gui)==desc->photo_show_pos)
    {
      CLIST *ClEx = CList_FindContactByJID(desc->jid);
      if (!ClEx)
        return 0;
      VCARD vcard = ClEx->vcard;
      if (!vcard) // ���� �� ����� - ���� � ������� (��� �����������)
      {
        TRESOURCE *ResEx = CList_IsResourceInList(desc->jid);
        if (ResEx)
          vcard = ResEx->vcard;
      }
      vCard_Photo_Display(Get_VCard_Value(vcard, "!PHOTO"));
    }
  }
  return(0); //Do standart keys
}

void vcinfo_ghook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_CREATE)
  {
    //Called after onCreate
  }

  if (cmd==TI_CMD_DESTROY)
  {
    // onDestroy
    VCARD_VIEW_DESC *desc = EDIT_GetUserPointer(gui);
    if (desc)
    {
      if (desc->jid)
        mfree(desc->jid);
      mfree(desc);
    }
  }

  if(cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();   // ��������� ������ ������ �� ��������
  }

  if (cmd==TI_CMD_SUBFOCUS_CHANGE)
  {
    if (EDIT_GetFocus(gui)>EDIT_GetUnFocus(gui)) // ���� ���� ������ ����
      EDIT_SetCursorPos(gui, 1); // �� ������ ������ � ������
  }
}

extern void inp_locret(void);

SOFTKEY_DESC vcinfo_sk[]=
{
  {0x0018,0x0000,(int)LG_UPDATE},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB vcinfo_skt=
{
  vcinfo_sk,0
};

INPUTDIA_DESC vcinfo_desc=
{
  1,
  vcinfo_onkey,
  vcinfo_ghook,
  (void *)inp_locret,
  0,
  &vcinfo_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// �������� ����-������
};

HEADER_DESC vcinfo_hdr={0,0,0,0,NULL,(int)"vCard",LGP_NULL};

extern const char percent_t[];
extern const char percent_s[];

int Show_vCard(char *jid)
{
#define MAX_VCARD_LINE_LEN 1024
  CLIST *ClEx = CList_FindContactByJID(jid);
  if (!ClEx)
    return 0;
  VCARD vcard = ClEx->vcard;
  if (!vcard) // ���� �� ����� - ���� � ������� (��� �����������)
  {
    TRESOURCE *ResEx = CList_IsResourceInList(jid);
    if (ResEx)
      vcard = ResEx->vcard;
  }
  if (vcard)
  {
    WSHDR* ws_info = AllocWS(MAX_VCARD_LINE_LEN);

    VCARD_VIEW_DESC *view_desc = malloc(sizeof(VCARD_VIEW_DESC));
    view_desc->jid = malloc(strlen(jid)+1);
    strcpy(view_desc->jid, jid);

    EDITCONTROL ec;
    void *ma=malloc_adr();
    void *eq;
    PrepareEditControl(&ec);
    eq=AllocEQueue(ma,mfree_adr());

    for (int i=0; i<N_VCARD_FIELDS; i++)
    {
      if (vcard[i])
      {
        wsprintf(ws_info, percent_t, vcard_names[i]);
        ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws_info, MAX_VCARD_LINE_LEN);
        AddEditControlToEditQend(eq,&ec,ma);
        utf8_2ws(ws_info, vcard[i], MAX_VCARD_LINE_LEN);
        ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws_info, MAX_VCARD_LINE_LEN);
        AddEditControlToEditQend(eq,&ec,ma);
      }
    }

    wsprintf(ws_info, percent_t, LG_UPDATE);
    ConstructEditControl(&ec, ECT_LINK, ECF_APPEND_EOL, ws_info, MAX_VCARD_LINE_LEN);
    view_desc->update_pos = AddEditControlToEditQend(eq,&ec,ma);

    if (Get_VCard_Value(vcard, "!PHOTO"))
    {
      wsprintf(ws_info, percent_t, LG_SHOW_AVATAR);
      ConstructEditControl(&ec, ECT_LINK, ECF_APPEND_EOL, ws_info, MAX_VCARD_LINE_LEN);
      view_desc->photo_show_pos = AddEditControlToEditQend(eq,&ec,ma);
    }
    else
    {
      view_desc->photo_show_pos = 0;
    }

    patch_header(&vcinfo_hdr);
    patch_input(&vcinfo_desc);
    CreateInputTextDialog(&vcinfo_desc,&vcinfo_hdr,eq,1,view_desc);

    FreeWS(ws_info);
    return 1;
  }
  return 0;
}

//EOL,EOF
