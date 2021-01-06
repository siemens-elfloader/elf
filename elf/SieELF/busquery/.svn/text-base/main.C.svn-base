#include "..\inc\swilib.h"
#include "conf_loader.h"
extern const char name[128];

char pt[]="%t";
const int minus11=-11;

char *buf=0;
char *s=0;
int fsize=0;
int num=0;
int len=0;


char cr[600][600]; 
char( *p)[600]=&cr[600];
char cr2[40]; 
char *p2;
char cr3[40][40]; 
char( *p3)[40]=&cr3[40];
char cz[122];


const SOFTKEY_DESC menu_sk[]=
{
    {0x0018,0x0000,(int)"Select"},
    {0x0001,0x0000,(int)"Close"},
    {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
    menu_sk,0
};

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ErrorMsg(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void Loaddata()
{ 
  int f;
  unsigned int err;
  char fname[128];
  
  if (buf != 0)
   mfree(buf);
  
  snprintf(fname,128,"%s",name);
  if ((f=fopen(fname, A_ReadOnly+A_BIN, 0, &err))==-1)
  {
         ErrorMsg("Can't open data!");
         return;    
  }
  fsize=lseek(f,0,S_END,&err,&err);
  lseek(f,0,S_SET,&err,&err);
  if (fsize<=0)
  {
    ErrorMsg("Zero lenght of data!");
    fclose(f,&err);
  } 
  else if ((buf=malloc(fsize))==0)
  {
     ErrorMsg("Can't malloc!");
  }  
  else if (fread(f,buf,fsize,&err)!=fsize)
  {
        ErrorMsg("Can't read data!");
      fclose(f, &err);
      mfree(buf);
      buf=0;
  }
  fclose(f,&err);
  
}


void ed1_locret(void){}

void ed1_ghook(GUI *data, int cmd){}

void doit(GUI *data)
{
  EDITCONTROL ec, ec2,ec3;
  {
    char word[40];
    char word2[40];
    ExtractEditControl(data,1,&ec);
    ExtractEditControl(data,2,&ec2);
    ExtractEditControl(data,3,&ec3);
    int utf8conv_res_len;
    ws_2utf8(ec.pWS,word,&utf8conv_res_len,40);
    ws_2utf8(ec2.pWS,word2,&utf8conv_res_len,40);
  
    
  int i=0;  
  char *pos=buf;
  int c;
  int find=0;
  int i2=0;
  int k;
  int l;
  int k1;
  p2=cr2;
  int cc=0;
  
  while((c=*pos))
  {
    pos++;
    switch(c)
    {
    case '\r':
        if(*pos++=='\n')
        {
        s=(p+i)[600];
        i++;
        while(*pos!='\r'&&*pos!='\n'&&*pos)
        {
          *s++=*pos++;
        }
        *s=0;
        }
        break;
        
     default:
      break;
    }
  }

 
  
  if(strlen(word)!=0&&strlen(word2)==0)
  for(k=0;k<=i;k++)
  {
       if(cc!=num+1)
       {
         
       if(strstr((p+k)[600],word))
         {
          utf8_2ws(ec3.pWS,(p+k)[600],600);
          StoreEditControl(data ,3, &ec3); 
          cc++;
         }      
       }
  }
  
  if(strlen(word)==0&&strlen(word2)!=0)
  for(k=0;k<=i;k++)
  {
       if(cc!=num+1)
       {
         
       if(strstr((p+k)[600],word2))
         {
          utf8_2ws(ec3.pWS,(p+k)[600],600);
          StoreEditControl(data ,3, &ec3); 
          cc++;
         }
       }
  }
  
  if(strlen(word2)!=0&&strlen(word)!=0)
    for(k=0;k<=i;k++)
     { 
     if(cc!=num+1)
       {
       if(strstr((p+k)[600],word)&&strstr((p+k)[600],word2))
         {
          utf8_2ws(ec3.pWS,(p+k)[600],600);
          StoreEditControl(data ,3, &ec3); 
          find=1;
          cc++; 
         }       
       }
    }
  
  
  if(strlen(word2)!=0&&strlen(word)!=0&&find==0)
  {
   for(l=0;l<=i;l++)
     {   
     for(k=0;k<=i;k++)
       {
        if(cc!=num+1)
          {         
          if(strstr((p+k)[600],word)&&strstr((p+l)[600],word2))
            {
                char *pos2=(p+k)[600];
                    s=p2;
                    while((c=*pos2++)!='*')
                    {
                       *s++=c;
                    }
                    *s=0;
                                   
               
                char *pos3=(p+l)[600];
                    s=p3[40];
                    while((c=*pos3++)!='*')
                    {
                       *s++=c;
                    }
                    *s=0;
               while((c=*pos3))
               {
                 pos3++;
                 switch(c)
                 {
                   case '*':
                     i2++;
                     s=(p3+i2)[40];
                     while(*pos3!='*'&&*pos3)
                     {
                       *s++=*pos3++;
                     }
                     *s=0;
                     break;
        
                    case '@':
                    break;
              
                    default:
                    break;
                  }
                }    
               int q=0;
               for(k1=1;k1<=i2;k1++)
               {
                 
               if(strstr((p+k)[600],(p3+k1)[40]))
               {
                 q=1;
                 break;
               }
                 
               }   
               if(q==1)
               {
                 strncpy(cz,p2,40);
                 strcat(cz," ");
                 strncat(cz,(p3+k1)[40],40);
                 strcat(cz," ");
                 strncat(cz,p3[40],40);             
                 utf8_2ws(ec3.pWS,cz,122);
                 StoreEditControl(data ,3, &ec3);           
                 cc++;
               }
            }
          }         
            
     }
  }
  }
  
     if(cc==0)
          {
           wsprintf(ec3.pWS, pt, "No bus!");
            StoreEditControl(data ,3, &ec3); 
          }

  }
}


int onkey(GUI *data, unsigned char keycode, int pressed)
{
  if(pressed==KEY_DOWN)
  {
    switch(keycode)
    {
    case ENTER_BUTTON: num=0;doit(data); return -1;
    case GREEN_BUTTON: if(num>0) num--;doit(data); return -1;
    case RED_BUTTON: num++;doit(data); return -1;   
    }
  }
  return 0;
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  //return(0); //Do standart keys
  //1: close
    return onkey(data, msg->gbsmsg->submess, msg->gbsmsg->msg);
}

//HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"busquery",0x7FFFFFFF};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0, 5, 132, 160},
  4,
  100,
  101,
  0,

//  0x00000001 - Align Right 
//  0x00000002 - Align Center 
//  0x00000004 - inversion characters
//  0x00000008 - UnderLine
//  0x00000020 - not carry the word 
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Not moving the cursor 
//  0x40000000 - Change field coaching buttons 
  0
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ews;
  EDITCONTROL ec;

  ews=AllocWS(1024);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,"%t","");
  ConstructEditControl(&ec,4,0x40,ews,40); 
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"%t","");
  ConstructEditControl(&ec,4,0x40,ews,40); 
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ews,"%t","Bus number!");
  ConstructEditControl(&ec,1,0x40,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(ews);
  
  return CreateInputTextDialog(&ed1_desc,0,eq,1,0);
}


void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  csm->gui_id=create_ed();
  Loaddata();
}

void maincsm_onclose(CSM_RAM *csm)
{
  if (buf) mfree(buf);  
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      {
	csm->csm.state=-3;
      }
    }
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"busquery");
}


int main()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  InitConfig();
  return 0;
}
