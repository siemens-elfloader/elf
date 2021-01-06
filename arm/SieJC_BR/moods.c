#include "../inc/swilib.h"
#include "lang.h"
#include "string_util.h"
#include "rect_patcher.h"
#include "moods.h"
#include "main.h"
#include "jabber_util.h"

#define moods_items 62
extern char My_Mood_Presence;
extern const char PATH_TO_PIC[128];
char PATH_TO_MOODS[256];
int moodt_pos;
char *smood;

const char *moods_texts[moods_items] = 
{
  LG_M_EMPTY,
  LG_M_AFRAID,
  LG_M_AMAZED,
  LG_M_ANGRY,
  LG_M_ANNOYED,
  LG_M_ANXIOUS,
  LG_M_AROUSED,
  LG_M_ASHAMED,
  LG_M_BORED,
  LG_M_BRAVE,
  LG_M_CALM,
  LG_M_COLD,
  LG_M_CONFUSED,
  LG_M_CONTENTED,
  LG_M_CRANKY,
  LG_M_CURIOUS,
  LG_M_DEPRESSED,
  LG_M_DISAPPOINTED,
  LG_M_DISGUSTED,
  LG_M_DISTRACTED,
  LG_M_EMBARRASSED,
  LG_M_EXCITED,
  LG_M_FLIRTATIOUS,
  LG_M_FRUSTRATED,
  LG_M_GRUMPY,
  LG_M_GUILTY,
  LG_M_HAPPY,
  LG_M_HOT,
  LG_M_HUMBLED,
  LG_M_HUMILIATED,
  LG_M_HUNGRY,
  LG_M_HURT,
  LG_M_IMPRESSED,
  LG_M_IN_AWE,
  LG_M_IN_LOVE,
  LG_M_INDIGNANT,
  LG_M_INTERESTED,
  LG_M_INTOXICATED,
  LG_M_INVINCIBLE,
  LG_M_JEALOUS,
  LG_M_LONELY,
  LG_M_MEAN,
  LG_M_MOODY,
  LG_M_NERVOUS,
  LG_M_NEUTRAL,
  LG_M_OFFENDED,
  LG_M_PLAYFUL,
  LG_M_PROUD,
  LG_M_RELIEVED,
  LG_M_REMORSEFUL,
  LG_M_RESTLESS,
  LG_M_SAD,
  LG_M_SARCASTIC,
  LG_M_SERIOUS,
  LG_M_SHOCKED,
  LG_M_SHY,
  LG_M_SICK,
  LG_M_SLEEPY,
  LG_M_STRESSED,
  LG_M_SURPRISED,
  LG_M_THIRSTY,
  LG_M_WORRIED
};

char *moods[moods_items] = 
{
  "EMPTY",
  "afraid",
  "amazed",
  "angry",
  "annoyed",
  "anxious",
  "aroused",
  "ashamed",
  "bored",
  "brave",
  "calm",
  "cold",
  "confused",
  "contented",
  "cranky",
  "curious",
  "depressed",
  "disappointed",
  "disgusted",
  "distracted",
  "embarrassed",
  "excited",
  "flirtatious",
  "frustrated",
  "grumpy",
  "guilty",
  "happy",
  "hot",
  "humbled",
  "humiliated",
  "hungry",
  "hurt",
  "impressed",
  "in_awe",
  "in_love",
  "indignant",
  "interested",
  "intoxicated",
  "invincible",
  "jealous",
  "lonely",
  "mean",
  "moody",
  "nervous",
  "neutral",
  "offended",
  "playful",
  "proud",
  "relieved",
  "remorseful",
  "restless",
  "sad",
  "sarcastic",
  "serious",
  "shocked",
  "shy",
  "sick",
  "sleepy",
  "stressed",
  "surprised",
  "thirsty",
  "worried"
};

void moodt_locret(void) {};

int moodt_onkey(GUI *gui, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg == KEY_DOWN)
  {
    if ((msg->gbsmsg->submess == GREEN_BUTTON) || (msg->keys == 0x0018))
    {
      EDITCONTROL ec;
      char *s = malloc(256);
      int len;
      ExtractEditControl(gui, moodt_pos, &ec);
      ws_2utf8(ec.pWS, s, &len, 256);
      SUBPROC((void *)Send_Mood, smood, s);
      return 1;
    }
  }
  return 0;
}

void moodt_ghook(GUI *gui, int cmd)
{
  if (cmd == TI_CMD_REDRAW)
  {
    static SOFTKEY_DESC sk = {0x0018, 0x0000, (int)LG_OK};
#ifdef NEWSGOLD
    SetSoftKey(gui, &sk, 0);
#else
    SetSoftKey(gui, &sk, 1);
#endif
  }
}

SOFTKEY_DESC moodt_sk[]=
{
  {0x0018,0x0000,(int)LG_OK},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB moodt_skt=
{
  moodt_sk,0
};

HEADER_DESC moodt_hdr={0,0,0,0,NULL,(int)LG_MOOD_TEXT,LGP_NULL};

INPUTDIA_DESC moodt_desc=
{
  1,
  moodt_onkey,
  moodt_ghook,
  (void *)moodt_locret,
  0,
  &moodt_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void ShowMoodTextDialog(char *mood)
{
  if (mood=="EMPTY")
  {
    smood=NULL;
    SUBPROC((void *)Send_Mood, NULL, NULL);
    return;
  } else smood = mood;
  
  WSHDR *ws = AllocWS(256);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq=AllocEQueue(ma,mfree_adr());
  
  extern const char empty_t[];

  wsprintf(ws, empty_t);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 256);
  moodt_pos = AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(ws);
  patch_header(&moodt_hdr);
  patch_input(&moodt_desc);
  CreateInputTextDialog(&moodt_desc,&moodt_hdr,eq,1,NULL);
}

static int moodsmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    My_Mood_Presence = GetCurMenuItem(data);
    ShowMoodTextDialog(moods[My_Mood_Presence]);
    return 1;
  }
  return 0;
}

int moods_icons[moods_items];

void moodsmenu_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_CREATE)
  {
    SetCursorToMenuItem(data,My_Mood_Presence);
  }
  if (cmd==TI_CMD_DESTROY)
  {
  for (int i = 0; i < moods_items; i++)
   {
    mfree((void*)moods_icons[i]);
   }
  }
}

int moodsmenusoftkeys[]={0,1,2};

static const SOFTKEY_DESC moodsmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB moodsmenu_skt=
{
  moodsmenu_sk,0
};

void moodsmenuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(moods_texts[curitem]));
  ascii2ws(ws, moods_texts[curitem]);
  SetMenuItemIconArray(data, item, moods_icons + curitem);
  SetMenuItemText(data, item, ws, curitem);
}

static const MENU_DESC moods_menu=
{
  8,
  moodsmenu_keyhook,
  moodsmenu_ghook,
  NULL,
  moodsmenusoftkeys,
  &moodsmenu_skt,
  0x11,
  moodsmenuitemhandler,
  NULL,
  NULL,
  moods_items
};

HEADER_DESC moods_menuhdr={0,0,131,21,NULL,(int)LG_MOODS,LGP_NULL};

void Show_Moods_Menu()
{
  sprintf(PATH_TO_MOODS, "%smoods\\", PATH_TO_PIC);
  for (int i = 0; i < moods_items; i++)
  {
    char *text = malloc(256);
    sprintf(text, "%s%s.png", PATH_TO_MOODS, moods[i]);
    moods_icons[i] = (int)text;
  }
  patch_header(&moods_menuhdr);
  moods_menuhdr.icon = &moods_icons[My_Mood_Presence];
  CreateMenu(0,0,&moods_menu,&moods_menuhdr,0,moods_items,0,0);
}
// EOL,EOF
