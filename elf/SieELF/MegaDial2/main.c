#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "extern.h"
#include "MegaDial.h"
#include "math.h"

#define TMR_SECOND (1300/6)
#define SMS_MAX_LEN  760
#define cfg_item_gaps 2
#define color(x) (x<24)?GetPaletteAdrByColorIndex(x):(char *)(&(x))  

//字体控制
#ifdef ELKA
#define font_size big_font?4:8
#else
#define font_size big_font?3:7
#endif

volatile int numx;
int sumx;
int cs_adr=0;
int iReadFile=0;
int gLen=0;
int count_page;
int need_ip=0;
int smsdata=0;
int smscount=0;
int input=0;
int nxc=0;

WSHDR *gwsName;
WSHDR *gwsTemp;
WSHDR *numTemp;
WSHDR *smstemp;
char smsnum[46];
char fn[10]="0:\\amr\\";
char pszNum3[25];
char pszNum4[30];

#ifdef ELKA
#define MAX_ESTR_LEN 9
#else
#define MAX_ESTR_LEN 13
#endif

#ifdef NEWSGOLD
#define MAX_RECORDS 5000
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else 
#ifdef SK65
#define LEVEL1_RN	(0x2D)
#else
#define LEVEL1_RN	(0x20)
#endif
#define MAX_RECORDS 1024
#endif

#define NUMBERS_MAX 5
#define wslen(ARG) (ARG->wsbody[0])

#ifdef NEWSGOLD
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define COMPANY_NAME 0x29
#define POST_NAME 0x6F
#define DISPLAY_NAME 0x60
#define PICTURE 0x33
#define E_MAIL 0x2E
#else
#define NICKNAME 0x12
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define STREET 0x25
#define POSTCODE 0x26
#define CITY 0x27
#define COUNTRY 0x28
#define COMPANY_NAME 0x29
#define PHONE_OFFICE 0x2A
#define PHONE_FAX 0x2B
#define PHONE_MOBILE 0x2C
#define PHONE_NUMBER 0x2D
#define E_MAIL 0x2E
#define URL 0x2F
#define PICTURE 0x33
#define E_MAIL2 0x5D
#define PHONE_FAX2 0x5E
#define WALKY_TALKY_ID 0x6D
#endif

volatile int is_pos_changed=0;

CSM_DESC icsmd;
CSM_DESC* old_icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

int (*old_ed_onkey)(GUI *gui, GUI_MSG *msg);
void (*old_ed_ghook)(GUI *gui, int cmd);
void (*old_ed_redraw)(void *data);

//0 - looking appearance dialogue
//1 - to dialogue appeared, hooked, waiting for positive onRedraw 
//2 - cable onRedraw, idle- regime 
//3 - query search 
//4 - you requested 
//5 - searched 
volatile int hook_state=0;

volatile WSHDR *e_ws;

volatile int curpos; //The position of the cursor in the list 

typedef struct
{
  void *next;
  WSHDR *name;
  WSHDR *num[NUMBERS_MAX];
  WSHDR *icons;
  WSHDR *pic;
}CLIST;

volatile CLIST *cltop; //Start

char dstr[NUMBERS_MAX][40];
char dstr2[40];
char dstr3[40];
int dstr_index[NUMBERS_MAX+1];

int menu_icons[NUMBERS_MAX];
int utf_symbs[NUMBERS_MAX];

#ifdef NEWSGOLD
#define USR_WIRE 0xE106
#define USR_MOBILE 0xE107
#define WORK_WIRE 0xE108
#define WORK_FAX 0xE109
#define USR_FAX 0xE10A
#define WORK_MOBILE 0xE10E

void InitIcons(void)
{
  menu_icons[0]=GetPicNByUnicodeSymbol(utf_symbs[0]=USR_WIRE); //12345
  menu_icons[1]=GetPicNByUnicodeSymbol(utf_symbs[1]=WORK_WIRE); //093
  menu_icons[2]=GetPicNByUnicodeSymbol(utf_symbs[2]=USR_MOBILE); //651
  menu_icons[3]=GetPicNByUnicodeSymbol(utf_symbs[3]=WORK_MOBILE); //884
  menu_icons[4]=GetPicNByUnicodeSymbol(utf_symbs[4]=USR_FAX);
}

#else
#define USR_WIRE 0xE100
#define WORK_WIRE 0xE102
#define USR_MOBILE 0xE101
#define USR_FAX1 0xE103
#define USR_FAX2 0xE104

void InitIcons(void)
{
  menu_icons[0]=GetPicNByUnicodeSymbol(utf_symbs[0]=USR_WIRE); 
  menu_icons[1]=GetPicNByUnicodeSymbol(utf_symbs[1]=WORK_WIRE); 
  menu_icons[2]=GetPicNByUnicodeSymbol(utf_symbs[2]=USR_MOBILE); 
  menu_icons[3]=GetPicNByUnicodeSymbol(utf_symbs[3]=USR_FAX1);
  menu_icons[4]=GetPicNByUnicodeSymbol(utf_symbs[4]=USR_FAX2);
}
#endif

//-------------------------------------
//读取设置
//-------------------------------------
void RereadSettings()
{
	int fin;
	unsigned int ul;
	InitConfig();
	if(iReadFile && !cs_adr)
        mfree((void*)cs_adr);
	if(cfg_cs_adrs != 9||(cfg_cs_adrs==0&&cfg_cs_adr > 0xA0000000))
	{
          switch(cfg_cs_adrs)
          {
          case 0://自输
            cs_adr=cfg_cs_adr;
            break;
            
          case 1://S65/CX65
            cs_adr=0xA0CC0000;
            break;
            
          case 2://SK65
            cs_adr=0xA0E30000;
            break;
            
          case 3://C65/SL65
            cs_adr=0xA0F60000;
            break;
            
          case 4://CX70
            cs_adr=0xA0E55A00;
            break;
            
          case 5://M65
            cs_adr=0xA0C61220;
            break;
            
          case 6://C7C
            cs_adr=0xA0E70B60;
            break;            
            
          case 7://CX7A
            cs_adr=0xA0F294B0;
            break;
            
          case 8://E71/EL71/M81/S68/SL75/S75
            cs_adr=0xA1580000;
            break;
          }  
	   iReadFile = 0;
	}
	else
	{
	iReadFile = 1;
	if(cs_adr=(int)malloc(240*1024))
	if ((fin=fopen("4:\\zbin\\codeshow.bin",A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		if (fread(fin,(void*)cs_adr,240*1024,&ul)!=240*1024)
		{
			mfree((void*)cs_adr);
		}
		fclose(fin,&ul);
		}
		else
		{
		if ((fin=fopen("0:\\zbin\\codeshow.bin",A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
		if (fread(fin,(void*)cs_adr,240*1024,&ul)!=240*1024)
		{
			mfree((void*)cs_adr);
		}
		fclose(fin,&ul);
		}
	else mfree((void*)cs_adr);
	}
}
//-------------------------------------
//区号秀
//-------------------------------------
void ShowInputCodeShow(WSHDR* pwsNum,int y1)
{
	WSHDR* pwsCodeshow;
	pwsCodeshow=AllocWS(20);
	char pszNum[20];
	int len;

	if(cltop) goto sub_end;

	if(!cfg_cs_enable) goto sub_end;
	ws_2str(pwsNum,pszNum,20);
	len=strlen(pszNum);

        if(cfg_disable_one_number)
        if(len <= 1) goto sub_end;

	if(len)
	{
		if(*pszNum == '0' && len < 3)
			goto sub_end;	//Locale table number is not enough
		else
			if(*pszNum == '1' && len < 7)
				goto sub_end;	//mobile number is not enough
			else
				if(*pszNum == '+' && len < 10)
					goto sub_end;	//+86XXXXXXXXX number is not enough
                        
                        	     else if(len > 20)
					    goto sub_end;   //Too long
				else
				{
					GetProvAndCity(pwsCodeshow->wsbody,pszNum);
					DrawString(pwsCodeshow,
						0,
						y1,
						ScreenW()-6,
						y1+GetFontYSIZE(font_size),
						font_size,
						4,
						color(cfg_cs_font_color),
						GetPaletteAdrByColorIndex(23));
				}
	}
sub_end:
	FreeWS(pwsCodeshow);
}

void ShowSelectedCodeShow(WSHDR* pwsNum,int y1)
{
	WSHDR* pwsCodeshow;
	pwsCodeshow=AllocWS(20);
	char pszNum[20];
	if((!cfg_cs_enable)||(cfg_cs_part)) goto sub_end;
	ws_2str(pwsNum,pszNum,20);
	GetProvAndCity(pwsCodeshow->wsbody,pszNum);
	DrawString(pwsCodeshow,
		2,
		y1,
		ScreenW()-6,
		y1+GetFontYSIZE(font_size),
		font_size,
		4,
                color(cfg_cs_font_color),
                color(CS_NUMBER_BG));
sub_end:
	FreeWS(pwsCodeshow);
}

//-------------------------------------------
//Destroy list 
void FreeCLIST(void)
{
  LockSched();
  CLIST *cl=(CLIST*)cltop;
  cltop=0;
  UnlockSched();
  while(cl)
  {
    CLIST *p;
    FreeWS(cl->name);
    for(int i=0;i<NUMBERS_MAX;i++) FreeWS(cl->num[i]);
    FreeWS(cl->icons);
    FreeWS(cl->pic);
    p=cl;
    cl=(CLIST*)(cl->next);
    mfree(p);
  }
}

int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;  //big_yo
    else if (c==4) c=2;  //big_ye
    else if (c==6) c=10; //big_i
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16; //small_yo
    else if (c==0x54) c=18; //small_ye
    else if (c==0x56) c=11; //small_i
    else if (c==0x57) c=23; //small_yi
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

//-----------------------------------------------------
//Search pieces in the line using T9 
//-----------------------------------------------------
unsigned int us_reverse(unsigned int v)
{
  return((v>>8)|((v&0xFF)<<8));
}

int CompareStrT9(WSHDR *ws, WSHDR *ss, int need_insert_color)
{
  int spos=1;
  int wpos=1;
  int c,c1=ws->wsbody[1],c2=ss->wsbody[1];
  int first_pos=-1;
  unsigned short temp;
  
  //Table keys for text search
  static const char key[256]=
    "11111111111111111111111111111111"   
      "10001**0***0000*012345678900***0"
	"0222333444555666777788899991*110"
	  "122233344455566677778889999111*1"
	    "11111111111111111111111111111111"
	      "11111111311111111111111131111111"
		"22223333444455566677778888899999"
		  "22223333444455566677778888899999";

  if (!wslen(ss)) return(1); //Empty string always line;) 
  if (!wslen(ws)) return(0); //A blank background is not shooting;) 

  do
  {
	c=ws->wsbody[wpos];
	if ((wpos==1)&&(c=='+')&&(c2!='+')&&(wslen(ws)>3))
	{
		wpos=4; //first pass'+' 
                continue;
	}
	else if((spos==1)&&(c1!='+')&&(c2=='+')&&(wslen(ss)>3))
	{
		spos=4;
		continue;
	}
	else if((c1=='+')&&(c2=='+')&&(wpos==1)&&(spos==1)&&(wslen(ws)>3)&&(wslen(ss)>3))
	{
		wpos=2;
		spos=2;
		continue;
	}
    if (!spos)
    {
      //We are looking for a gap 
      if (c==' ') spos=1; //Starting anew 
    }
    else
    {
       //Preobrazuem code buttons 
	temp=(c >= 0x4E00 && c <= 0x9FA8 )?PinYinTable[(c  >> 2) - 4992]:0xFFFF;
	temp=(temp >> ((c&0x03) << 2))&0x0F;
	if (c>255&&(temp!=0xF)) c=temp+'0';
	else 
	{
            c=char16to8(c);
	    c&=0xFF;
	    c=key[c];
	}
      if (c==ss->wsbody[spos])
      {
	if (first_pos<0) first_pos=wpos;
	spos++;
	if (spos>wslen(ss))
	{
	  if (need_insert_color&&(first_pos>0))
	  {
	    wsInsertChar(ws,us_reverse(((unsigned short *)COLOR_SEARCH_UNMARK)[1]),wpos+1);
	    wsInsertChar(ws,us_reverse(((unsigned short *)COLOR_SEARCH_UNMARK)[0]),wpos+1);
	    wsInsertChar(ws,0xE006,wpos+1);
	    wsInsertChar(ws,us_reverse(((unsigned short *)COLOR_SEARCH_MARK)[1]),first_pos);
	    wsInsertChar(ws,us_reverse(((unsigned short *)COLOR_SEARCH_MARK)[0]),first_pos);
	    wsInsertChar(ws,0xE006,first_pos);
	  }
	  return(1); //All coincided 
        }
      }
      else 
      {
	first_pos=-1;
	spos=0; //We are looking for a new word 
      }
    }
    wpos++;
  }
  while(wpos<=wslen(ws));
  return(0);
}

//than long lines 
int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  while((pos<=l1)&&(pos<=l2))
  {
    cs=char16to8(ws1->wsbody[pos]);
    if (cs&0x40) cs&=0xDF;
    ds=char16to8(ws2->wsbody[pos]);
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return(l1-l2);
}

//=====================================================
// Constructor list  
//=====================================================
void ConstructList(void)
{
  int fin;
  unsigned int ul;
  char recname[128];
  char szRoot[100];//通信录地址

  AB_UNPRES ur;
  void *buffer;
  
#pragma pack(1)
  struct {
#ifdef NEWSGOLD
    long dummy1;
    short dummy2;
    char bitmap[MAX_RECORDS/8];
#else
    long dummy1;
    char bitmap[MAX_RECORDS/8];
#endif
  } ABmain;
#pragma pack()

  unsigned int rec=0;
  int fsz;
  CLIST contact;

  //通信录地址处理
  strcpy(szRoot, root_dir);
  fin = strlen(szRoot);
  if(fin > 0 && szRoot[fin-1] == '\\')
  szRoot[fin-1] = 0;
        
  WSHDR *sws=AllocWS(50);

  FreeCLIST(); //Unichtozhaem before. list 
  LockSched();
  if (e_ws) wstrcpy(sws,(WSHDR *)e_ws);
  if (hook_state==4) hook_state=5;
  UnlockSched();
  zeromem(&contact,sizeof(contact));
  if ((buffer=malloc(65536)))
  {
    zeromem(&ABmain,sizeof(ABmain));
    
    snprintf(recname,128,"%s\\main",szRoot);
//   if ((fin=fopen("0:\\System\\apo\\addr\\main",A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
    if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
    {
#ifdef ELKA
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
      {
	fclose(fin,&ul);
	do
	{
          #ifdef NEWSGOLD
	  if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
          #else
          if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
          #endif   
	  {
            #ifdef NEWSGOLD
	    //record is in class
            unsigned int rl1;
	    unsigned int rl2;
	    unsigned int rl3;
	    rl1=rec/LEVEL1_RN;
	    rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
	    rl3=rec%LEVEL2_RN;
//	     snprintf(recname,128,"0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d",rl1,rl2,rl3);
	    snprintf(recname,128,"%s\\data\\%02d\\%02d\\%02d",szRoot,rl1,rl2,rl3);
            #else
	    unsigned int rl1=rec/LEVEL1_RN;
	    unsigned int r12=rec%LEVEL1_RN;
//	     snprintf(recname,128,"0:\\System\\apo\\addr\\%02x\\%02x",rl1,r12);            
	    snprintf(recname,128,"%s\\%02x\\%02x",szRoot,rl1,r12);              
           #endif             
	    if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	    {
	      zeromem(&ur,sizeof(AB_UNPRES));
              fsz=lseek(fin,0,S_END,&ul,&ul);
              lseek(fin,0,S_SET,&ul,&ul);
  	      fread(fin,buffer,fsz,&ul);
	      fclose(fin,&ul);
              #ifdef NEWSGOLD
	      UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
              #else
              UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
              #endif
	      int i=0;
	      zeromem(&contact,sizeof(contact));
	      contact.icons=AllocWS(NUMBERS_MAX);
	      while(i<ur.number_of_records)
	      {
		AB_UNPRES_ITEM *r=ur.record_list+i;
		if (r->no_data!=1)
		{
		  switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
		  {
		  case 0x05:
                    #ifdef NEWSGOLD
//                    if (r->item_type==0x81)
                    if (
			r->item_type==LAST_NAME||
			r->item_type==FIRST_NAME||
			r->item_type==COMPANY_NAME||
			r->item_type==POST_NAME||
			r->item_type==DISPLAY_NAME
			  )
                    #else
                    if (
                        r->item_type==LAST_NAME||
                        r->item_type==FIRST_NAME||
                        r->item_type==COMPANY_NAME
                         )
                    #endif   
		    {
                      if (r->data)
		      {
                        if (!contact.name)
                        {
			 wstrcpy(contact.name=AllocWS(150),(WSHDR *)(r->data));
			 *((int *)(&contact.next))|=CompareStrT9(contact.name,sws,0);
                        }
                        else
                        {
                         wsAppendChar(contact.name,',');
                         wsAppendChar(contact.name,' ');
                         wstrcat(contact.name,(WSHDR *)(r->data));
                         *((int *)(&contact.next))|=CompareStrT9(contact.name,sws,0);
                        }
		      }
		    }
                    if (r->item_type==PICTURE)
                    {
                        if (r->data)
                            if (!contact.pic)
                            wstrcpy(contact.pic=AllocWS(150),(WSHDR *)(r->data)); 
                    }                    
                    break;

		  case 0x01:
		    {
		      PKT_NUM *p=(PKT_NUM*)r->data;
		      unsigned int n=r->item_type;
		      int j;
		      unsigned int c;
		      WSHDR *ws;
                      #ifdef NEWSGOLD
		      if (n!=106)
			n-=0x62;
		      else
			n=4;
                      if (n<5)
                      #else
                      switch(r->item_type)
                      {
                      case PHONE_NUMBER:
                        n=0;    break;      
                      case PHONE_OFFICE:
                        n=1;    break;
                      case PHONE_MOBILE:
                        n=2;    break;
                      case PHONE_FAX:
                        n=3;    break;
                      case PHONE_FAX2:
                        n=4;    break;
                      default:
                        continue;
                      }
                      #endif 
		      {
			if (p)
			{
                          unsigned int c1;
                          int m;
			  ws=contact.num[n]=AllocWS(50);
			  //Add icons phones
                            
			  wsAppendChar(contact.icons,utf_symbs[n]);
			  j=0;
                          m=0;
			  if (p->format==0x91) wsAppendChar(ws,'+');
			  while(j<p->data_size)
			  {
                            if (m&1) {c1=c>>4; j++;}
                            else c1=(c=p->data[j])&0x0F;
			    if (c1==0x0F) break;
                            
                            if (c1==0xA) c1='*';
                            else if (c1==0xB) c1='#';
                            else if (c1==0xC) c1='+';
                            else if (c1==0xD) c1='?';
                            else c1+='0';
                            wsAppendChar(ws,c1);
			    m++;
			  }
			  *((int *)(&contact.next))|=CompareStrT9(ws,sws,0);
			}
		      }
		      break;
		    }
		  }
		}
		i++;
	      }
	      if (!contact.next)
	      {
		FreeWS(contact.name);
		for(int i=0;i<NUMBERS_MAX;i++) FreeWS(contact.num[i]);
		FreeWS(contact.icons);
                FreeWS(contact.pic);
	      }
	      FreeUnpackABentry(&ur,mfree_adr());
	      if (hook_state!=5) goto L_STOP;
	      LockSched();
	      if ((hook_state==5)&&(contact.next))
	      {
		//Add to the list 
		int n=0;
		CLIST *p=malloc(sizeof(contact));
		CLIST *t;
		CLIST *b=(CLIST *)(&cltop);
		contact.next=0;
		memcpy(p,&contact,sizeof(contact));
		for(;;)
		{
		  if (t=b->next)
		  {
		    //We have the following 
		    if (wstrcmp_nocase(contact.name,t->name)<0)
		    {
		      //The following are inserted, vtykaem Here 
		      p->next=t;
		      b->next=p;
                      if (is_pos_changed&&n<=curpos) curpos++;  // Otsaemsya at selected positions 
		      break;
		    }
		    b=t; //next
		    n++; //The number added to the calculation, I want REDRAW 
		  }
		  else
		  {
		    //End of anyone 
		    b->next=p;
		    break;
		  }
		}
		if (curpos<2)
		{
		  if (n<count_page) REDRAW();
		}
		else
		{
		  if ((unsigned int)(n-(curpos-2))<count_page) REDRAW();
		}
	      }
	      UnlockSched();
	    }
	  }
	  rec++;
	}
	while(rec<MAX_RECORDS);
      }
      else
      {
	fclose(fin,&ul);
      }
    }
  L_STOP:
    mfree(buffer);
  }
  if (contact.next)
  {
    FreeWS(contact.name);
    for(int i=0;i<NUMBERS_MAX;i++) FreeWS(contact.num[i]);
    FreeWS(contact.icons);
    FreeWS(contact.pic);
  }
  LockSched();
  if (hook_state==5) hook_state=2; else FreeCLIST();
  UnlockSched();
  REDRAW();
  FreeWS(sws);
}


void Play(const char *fpath, const char *fname)
{  
  WSHDR* sndPath=AllocWS(128);
  WSHDR* sndFName=AllocWS(128);

  wsprintf(sndPath, fpath);
  wsprintf(sndFName, fname);
  
    PLAYFILE_OPT _sfo1;
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=volume;
#ifdef NEWSGOLD
    _sfo1.unk6=1;
    _sfo1.unk7=1;
    _sfo1.unk9=2;
    PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
    _sfo1.unk4=0x80000000;
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif 

  FreeWS(sndPath);
  FreeWS(sndFName);

}

IMGHDR *my_pic=0;

//#define PI 3.1415926535
#define CTYPE1 0
#define CTYPE2 1

typedef struct {
  int x;
  int y;
}POINT;

typedef struct {
  char R;
  char G;
  char B;
  char A;
}color;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int sqr(int x)
{
  return x*x;
}

int abs(int x)
{
  return x < 0 ? x*(-1) : x;
}

int max(int x, int y)
{
  return x > y ? x : y;
}

int min(int x, int y)
{
  return x < y ? x : y;
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

color RGBA(char R, char G, char B, char A)
{
  color t={R,G,B,A};
  return t;
}


color getcolor(IMGHDR *img, int x, int y)
{
  color *bm=(color*)img->bitmap;
  if(x < img->w && x>=0 && y < img->h && y>=0) 
    return *(bm + x + y*img->w);
  else
    return (color){0,0,0,0};
}

void setcolor(IMGHDR *img, int x, int y, color clr)
{
  color *bm=(color*)img->bitmap;
  if(x < img->w && x>=0 && y < img->h && y>=0)
    *(bm + x + y*img->w)=clr;
}

void bmfree(IMGHDR *img)
{
  int x, y;
  for(y=0; y<img->h; y++)
    for(x=0; x<img->w; x++)
      setcolor(img, x, y, (color){0,0,0,0});
}

IMGHDR *createIMGHDR(int w, int h, int type)
{
  IMGHDR *img=malloc(sizeof(IMGHDR));
  img->w=w; 
  img->h=h; 
  img->bpnum=type;
  img->bitmap=malloc(h*w*sizeof(color));
  bmfree(img);
  return img;
}

void deleteIMGHDR(IMGHDR *img)
{
  mfree(img->bitmap);
  mfree(img); 
}

IMGHDR *rotate(IMGHDR *img, float angle, int del)
{
  double ang = -angle*acos(0)/90;
  int newWidth, newHeight;
  int nWidth = img->w;
  int nHeight= img->h;
  double cos_angle = cos(ang);
  double sin_angle = sin(ang);
  
  POINT p1={0,0};
  POINT p2={nWidth,0};
  POINT p3={0,nHeight};
  POINT p4={nWidth-1,nHeight};
  POINT newP1,newP2,newP3,newP4, leftTop, rightTop, leftBottom, rightBottom;
  
  newP1.x = p1.x;
  newP1.y = p1.y;
  newP2.x = (long)(p2.x*cos_angle - p2.y*sin_angle);
  newP2.y = (long)(p2.x*sin_angle + p2.y*cos_angle);
  newP3.x = (long)(p3.x*cos_angle - p3.y*sin_angle);
  newP3.y = (long)(p3.x*sin_angle + p3.y*cos_angle);
  newP4.x = (long)(p4.x*cos_angle - p4.y*sin_angle);
  newP4.y = (long)(p4.x*sin_angle + p4.y*cos_angle);
  
  leftTop.x = min(min(newP1.x,newP2.x),min(newP3.x,newP4.x));
  leftTop.y = min(min(newP1.y,newP2.y),min(newP3.y,newP4.y));
  rightBottom.x = max(max(newP1.x,newP2.x),max(newP3.x,newP4.x));
  rightBottom.y = max(max(newP1.y,newP2.y),max(newP3.y,newP4.y));
  leftBottom.x = leftTop.x;
  leftBottom.y = rightBottom.y;
  rightTop.x = rightBottom.x;
  rightTop.y = leftTop.y;
  
  newWidth = rightTop.x - leftTop.x;
  newHeight= leftBottom.y - leftTop.y;
  IMGHDR *img2=createIMGHDR(newWidth, newHeight, CTYPE1);
  
  int x,y,newX,newY,oldX,oldY;
  for (y = leftTop.y, newY = 0; y<=leftBottom.y; y++,newY++){
    for (x = leftTop.x, newX = 0; x<=rightTop.x; x++,newX++){
      oldX = (long)(x*cos_angle + y*sin_angle /*- 0.5*/);
      oldY = (long)(y*cos_angle - x*sin_angle /*- 0.5*/);
      setcolor(img2,newX,newY,getcolor(img,oldX,oldY));
    }
  }
  if(del)
    deleteIMGHDR(img);
  return img2;
}

IMGHDR *alpha(IMGHDR *img, char a, int nw, int del)
{
  int i;
  color *r=(color*)img->bitmap;
  for(i=0;i<img->h*img->w; i++, r++)
    if(r->A>a)
      r->A-=a;
    else
      r->A=0;
    return img;
}


IMGHDR *resample(IMGHDR *img, int px, int py, int fast, int del)
{
  if (px==100 && py==100) return img;

  long newx = (img->w*px)/100,
  newy = (img->h*py)/100;
  
  float xScale, yScale, fX, fY;
  xScale = (float)img->w  / (float)newx;
  yScale = (float)img->h / (float)newy;
  
  IMGHDR *img2=createIMGHDR(newx,newy,CTYPE1);
  if (fast) 
  {
    for(long y=0; y<newy; y++)
    {
      fY = y * yScale;
      for(long x=0; x<newx; x++)
      {
        fX = x * xScale;
        setcolor(img2,  x,  y, getcolor(img, (long)fX,(long)fY));
      }
    }
  }
  else 
  {
    long ifX, ifY, ifX1, ifY1, xmax, ymax;
    float ir1, ir2, ig1, ig2, ib1, ib2, ia1, ia2, dx, dy;
    char r,g,b,a;
    color rgb1, rgb2, rgb3, rgb4;
    xmax = img->w-1;
    ymax = img->h-1;
    for(long y=0; y<newy; y++)
    {
      fY = y * yScale;
      ifY = (int)fY;
      ifY1 = min(ymax, ifY+1);
      dy = fY - ifY;
      for(long x=0; x<newx; x++)
      {
        fX = x * xScale;
        ifX = (int)fX;
        ifX1 = min(xmax, ifX+1);
        dx = fX - ifX;
        rgb1= getcolor(img, ifX,ifY);
        rgb2= getcolor(img, ifX1,ifY);
        rgb3= getcolor(img, ifX,ifY1);
        rgb4= getcolor(img, ifX1,ifY1);
        
        ir1 = rgb1.R   * (1 - dy) + rgb3.R   * dy;
        ig1 = rgb1.G * (1 - dy) + rgb3.G * dy;
        ib1 = rgb1.B  * (1 - dy) + rgb3.B  * dy;
        ia1 = rgb1.A  * (1 - dy) + rgb3.A  * dy;
        ir2 = rgb2.R   * (1 - dy) + rgb4.R   * dy;
        ig2 = rgb2.G * (1 - dy) + rgb4.G * dy;
        ib2 = rgb2.B  * (1 - dy) + rgb4.B  * dy;
        ia2 = rgb2.A  * (1 - dy) + rgb4.A  * dy;
        
        r = (char)(ir1 * (1 - dx) + ir2 * dx);
        g = (char)(ig1 * (1 - dx) + ig2 * dx);
        b = (char)(ib1 * (1 - dx) + ib2 * dx);
        a = (char)(ia1 * (1 - dx) + ia2 * dx);
        
        setcolor(img2, x,y,RGBA(r,g,b,a));
      }
    }
  }
  if(del)
    deleteIMGHDR(img);
  return img2;
  
}

void DrwPic(int x,int y,const char *pic_path,int pic_size)
{
  //unsigned int pic_op = 50;
  if(my_pic) deleteIMGHDR(my_pic);
  my_pic=0;
  if(strlen(pic_path))
  {
    FSTATS fstats;
    unsigned int err;     
    if (GetFileStats(pic_path,&fstats,&err)!=-1)
    {
      #ifdef NEWSGOLD
      if(my_pic=CreateIMGHDRFromPngFile(pic_path, CTYPE2)) 
      {                                                    
        my_pic=resample(my_pic, pic_size, pic_size, 0, 1); 
        //if(ROT)
        //my_pic=rotate(my_pic, ROT*-1, 1);
        //my_pic=alpha(my_pic, 255-255*pic_op/100, 0, 0);    
      }
      
      #else
      #ifdef X75
      if(my_pic=CreateIMGHDRFromPngFile(pic_path, CTYPE2)) 
      {                                                    
        my_pic=resample(my_pic, pic_size, pic_size, 0, 1); 
        //if(ROT)
        //my_pic=rotate(my_pic, ROT*-1, 1);
        //my_pic=alpha(my_pic, 255-255*pic_op/100, 0, 0);       
      }
      #else
      my_pic=CreateIMGHDRFromPngFile(pic_path,CTYPE2);
      #endif
      #endif
      
      DrwImg(my_pic,x,y,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1)); 
    }
    else my_pic=0;
  }
}

GBSTMR tmr_scroll;
volatile int scroll_disp;
volatile int max_scroll_disp;

void scroll_timer_proc(void)
{
  int i=max_scroll_disp;
  if (i)
  {
    if (scroll_disp>=i)
    {
      scroll_disp=0;
      GBS_StartTimerProc(&tmr_scroll,TMR_SECOND,scroll_timer_proc);
    }
    else
    {
      scroll_disp++;
      GBS_StartTimerProc(&tmr_scroll,scroll_disp!=i?TMR_SECOND>>3:TMR_SECOND,scroll_timer_proc);
    }
    REDRAW();
  }
}

void DisableScroll(void)
{
  GBS_DelTimer(&tmr_scroll);
  max_scroll_disp=0;
  scroll_disp=0;
}

void my_ed_redraw(void *data)
{
  sumx=0;
  char pszNum2[100];
  int z;
  int gfont_size = GetFontYSIZE(font_size)+1;
  
  int i=curpos-2;
  int cp;
  int total_n;
  int right_border, down_border;
  CLIST *p=(CLIST *)cltop;
  CLIST *cl;
  old_ed_redraw(data);
  
  WSHDR *prws=AllocWS(128);
  
  int startfix4;
    if(startfix>100)
      startfix4=100-startfix;
    else
      startfix4=startfix;
  
#ifdef ELKA
  (big_font)?(count_page=6):(count_page=8);
  int csh=startY+startfix4+44;
  if(big_font)
      z=startY+startfix4+46;
  else
      z=startY+startfix4+42;
#else
  #ifdef S68
  (big_font)?(count_page=6):(count_page=7);
  int csh=startY+startfix4+22;
  if(big_font)
      z=startY+startfix4+19;
  else
      z=startY+startfix4+22;
  #else
  (big_font)?(count_page=7):(count_page=9);
  int csh=startY+startfix4+22;
  if(big_font)
      z=startY+startfix4+24;
  else
      z=startY+startfix4+20;
  #endif
#endif
  
  
  //区号秀平时输出
  if(e_ws&&!p)
  {
      ShowInputCodeShow((WSHDR*)e_ws,csh);
  }

  if (p && e_ws && e_ws->wsbody[0]<MAX_ESTR_LEN) //Its length <MAX_ESTR_LEN 
  {
    int startfix3;
    if(startfix2>100)
      startfix3=100-startfix2;
    else
      startfix3=startfix2;
  #ifdef S68
    int y=ScreenH()-25-gfont_size*count_page+startfix3;
  #else
    int y=ScreenH()-SoftkeyH()-gfont_size*count_page+startfix3;
  #endif
    down_border=ScreenH()-SoftkeyH()+5;
    DrawRectangle(1,z,ScreenW()-2,down_border,0,color(COLOR_MENU_BRD),color(COLOR_MENU_BK));
    
    if (i<0) cp=curpos; else cp=2;
    cl=p;
    total_n=0;
    while(p)
    {
      if (total_n==i) cl=p;
      p=(CLIST *)(p->next);
      total_n++;
    }
    i=0;
    if (total_n>count_page && color(COLOR_SCROLLBAR))  //Prorisuem skrollbar 
    {
      int start_y, y_width;
      right_border=ScreenW()-6;
      start_y=(y+2)+curpos*((down_border-2)-(y+2))/total_n;
      y_width=((down_border-2)-(y+2))/total_n;
      DrawLine(right_border+2,y+2,right_border+2,down_border-2,0,color(COLOR_SCROLLBAR_BG));
      DrawRectangle(right_border+1,start_y,right_border+3,start_y+y_width+1,0,color(COLOR_SCROLLBAR),color(COLOR_SCROLLBAR));
    } 
    else right_border=ScreenW()-3;
    
    int   list_num2=0;
    do
    {
      int dy=i*gfont_size+y;
      if (!cl) break;
      if(i==0&&list_num==0)
        list_num2=1;
      else
        list_num2=list_num;
      if (i!=cp)
      {
	wstrcpy(prws,cl->name);
	if (e_ws) CompareStrT9(prws,(WSHDR *)e_ws,1);
	DrawString(prws,3,dy+4,right_border-1,dy+cfg_item_gaps+gfont_size,font_size,0x80,color(COLOR_NOTSELECTED),GetPaletteAdrByColorIndex(23));  
      }
      else if(i=cp+1+list_num2)
      {
	int icons_size=Get_WS_width(cl->icons,font_size);
	DrawRectangle(2,dy+3,right_border,dy+2*(cfg_item_gaps+gfont_size)-2+list_num2*gfont_size,0,color(COLOR_SELECTED_BRD),color(COLOR_SELECTED_BG));
	DrawString(cl->name,3,dy+4,right_border-2-icons_size,dy+(cfg_item_gaps+gfont_size),font_size,0x80,color(COLOR_SELECTED),GetPaletteAdrByColorIndex(23));

        //号码输出
         int c=0,n=0,bc=0,cn=0;
         int box[5];
          do
          {
            if (cl->num[c])
           {
             ws_2str(cl->num[c],dstr[n],39);
             box[n]=c;
             
             wstrcpy(gwsTemp,cl->num[c]);
             if(CompareStrT9(gwsTemp,(WSHDR *)e_ws,0))
               {
                  strncpy(dstr3,dstr[0],39);
                  strncpy(dstr[0],dstr[n],39);
                  strncpy(dstr[n],dstr3,39);
                  bc=box[0];
                  box[0]=box[n];
                  box[n]=bc;
                  cn=1;
               }
             
             if(c==priority&&dstr[0]&&cn==0)
             {
                  strncpy(dstr3,dstr[0],39);
                  strncpy(dstr[0],dstr[n],39);
                  strncpy(dstr[n],dstr3,39);
                  bc=box[0];
                  box[0]=box[n];
                  box[n]=bc;
             }
             ++n;
           }
            c++;
          }
         while(c<NUMBERS_MAX);
         sumx=n;

         if(n==0)
         gb2ws(prws,no_num,64);
         else
         str_2ws(prws,dstr[numx],39);

          int dyx,dyy;
          if(i==cp+1)
             {
                    dyx=dy;
                    dyy=dy;
             }    
          else
             {
                    dyx=dy+3*(gfont_size+cfg_item_gaps)-7;
                    dyy=dy+(gfont_size+cfg_item_gaps)-3;
             }


          if(n!=0)
          {
          //图标
          int l=GetImgWidth(menu_icons[0]);
          DrawString(cl->icons,right_border-1-icons_size,dy+cfg_item_gaps,right_border-2,dy+cfg_item_gaps+gfont_size,font_size,0x80,color(COLOR_SELECTED),GetPaletteAdrByColorIndex(23));
          
	  int i=Get_WS_width(prws,font_size);
	  i-=(ScreenW()-10-l);
	  if (i<0)
	  {
	    DisableScroll();
	  }
	  else
	  {
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SECOND,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
          
          DrawScrollString(prws,3+l,dy+(gfont_size+cfg_item_gaps)+2,ScreenW()-7,dy+2*(gfont_size+cfg_item_gaps),scroll_disp+1,font_size,0x80,color(COLOR_NUMBER),GetPaletteAdrByColorIndex(23));
          DrawImg(3,dy+(gfont_size+cfg_item_gaps),menu_icons[box[numx]]);
          
          //区号秀
          if(!cfg_cs_part)
          ShowSelectedCodeShow(prws,dyx-(gfont_size+cfg_item_gaps)+6);
          }
                  //大头贴
                  if(show_pic&&wstrlen(cl->pic)>5)
                  {
                  ws_2str(cl->pic,pszNum2,100);
                  int x0=ScreenW()-4-GetImgWidth((int)pszNum2);
                   unsigned int pic_size=100;
                   if(x0<gfont_size*3)
                   {
                   x0=gfont_size*3;
                   if(resampled)
                   {
                    #ifdef NEWSGOLD
                    pic_size=100-(gfont_size*3-x0)*100/(ScreenW()-x0);
                    #endif  
                    #ifdef X75
                    pic_size=100-(gfont_size*3-x0)*100/(ScreenW()-x0);
                     #endif
                    }
                   }
                     
                   if(resampled)
                   DrwPic(x0,dyy+2*(gfont_size+cfg_item_gaps)-1,pszNum2, pic_size);
                   else
                   DrawImg(x0,dyy+2*(gfont_size+cfg_item_gaps)-1,(unsigned int)pszNum2); 
                 
                  }
          
          //界面音效
          if(voice)
          {
          int len=0;
          ws_2str(cl->name,pszNum3,25);
          sprintf(pszNum4,"%s.amr",pszNum3);
          len=strlen(pszNum4);
          if(len>4)
          {
          Play(fn, pszNum4);
          }      
          }
      }
      cl=(CLIST *)cl->next;
      i++;
    }
      while(i<count_page);
  }
  FreeWS(prws);
}

//屏幕参数控制
void ChangeRC(GUI *gui)
{
#ifdef ELKA
  static RECT rc={6,56,234,140};
#else
  #ifdef S68
  static RECT rc={6,38,126,100};
  #else
  static RECT rc={6,18,126,100};
  #endif
#endif
  rc.x = startX;
  rc.y = startY;
  
  if (e_ws)
  {
    if (wslen(e_ws)>=MAX_ESTR_LEN) return;
  }
  if (!gui) return;
  char *p=(char *)gui;
  p+=DISPLACE_OF_EDGUI;
  gui=*((GUI **)p);
  if (!gui) return;
  void **m=GetDataOfItemByID(gui,4);
  if (gui->canvas) memcpy(gui->canvas,&rc,sizeof(rc));
  if (!m) return;
  if (m[0]) memcpy(m[0],&rc,sizeof(rc));
}

//-------------------------------------
//短信发送菜单
//-------------------------------------
int mode;


char* Opendata(char *recname)
{
  char *buf;
  int f;
  unsigned int fsize;  
  unsigned int err;
  f=fopen(recname,A_ReadOnly+A_BIN,P_READ,&err);
  fsize=lseek(f,0,S_END,&err,&err);
  if (fsize<=0)
  {
    fclose(f,&err);
  }
  lseek(f,0,S_SET,&err,&err);
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  buf[fsize]=0;
  fclose(f,&err);
  return (buf);
}


static void sendsms(void)
{
  if((smscount > 0) || (mode == 1))
  {
  smsdata=0;
  nxc=0;
  smscount=0;
  SendSMS(smstemp, smsnum, MMI_CEPID, MSG_SMS_RX-1, mode);
  GeneralFuncF1(1);
  }
  else
  ShowMSG(1,(int)"空短信!");
}

static void mm_settings(GUI *gui)
{
   mode=6;
   sendsms();
}


#ifndef NEWSGOLD
static void sm_settings(GUI *gui)
{
   mode=1;
   sendsms();
}

static void sms_settings(GUI *gui)
{
    typedef void (*voidfunc)();
    voidfunc pp=(voidfunc)GetFunctionPointer("MESG_SMSSETUPOM");
    if(pp!=0) pp();
}
#endif

unsigned int err;

static void bcfgsetting()
{
  WSHDR *ws = AllocWS(150);
  int fd1;
  if ((fd1 = fopen("4:\\ZBin\\etc\\MegaDial2.bcfg", A_ReadOnly + A_BIN, P_READ, &err)) != -1)
    str_2ws(ws, "4:\\ZBin\\etc\\MegaDial2.bcfg", 128);
  else
    str_2ws(ws, "0:\\ZBin\\etc\\MegaDial2.bcfg", 128);
  fclose(fd1, &err);
  ExecuteFile(ws, 0, 0);
  FreeWS(ws);
}

static void md_setting(GUI *gui) 
{
  bcfgsetting();
}

static const int mmenusoftkeys[]={0,1,2};

static const SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)"选择"},
  {0x0001,0x0000,(int)"返回"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

static HEADER_DESC mmenu_hdr={0,0,0,0,NULL,(int)"选项",LGP_NULL};

#ifdef NEWSGOLD
#define MAIN_MENU_ITEMS_N 2
static MENUITEM_DESC mmenu_ITEMS[MAIN_MENU_ITEMS_N]=
{
  {NULL,(int)"发送短信", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"MD设置", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}
};

static const MENUPROCS_DESC mmenu_HNDLS[MAIN_MENU_ITEMS_N]=
{
  mm_settings,
  md_setting,
};
#else
#define MAIN_MENU_ITEMS_N 4
static MENUITEM_DESC mmenu_ITEMS[MAIN_MENU_ITEMS_N]=
{
  {NULL,(int)"发送短信", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"默认菜单", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"短信菜单", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"MD设置", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}
};

static const MENUPROCS_DESC mmenu_HNDLS[MAIN_MENU_ITEMS_N]=
{
  mm_settings,
  sm_settings,
  sms_settings,
  md_setting,
};
#endif


void VoiceOrSMS(const char *num);

static int mmenu_keyhook(void *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
      case RIGHT_SOFT : 
        smsdata=1; 
        if(nxc==1)
        {
        VoiceOrSMS(smsnum);
        }  
        else
        {
        VoiceOrSMS(dstr[numx]);
        }
        break;
    }
  }
  return (0);
}

static void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}


static const MENU_DESC mmenu=
{
  8,mmenu_keyhook,mmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x10,//MENU_FLAG,
  NULL,
  mmenu_ITEMS,//menuitems,
  mmenu_HNDLS,//menuprocs,
  MAIN_MENU_ITEMS_N
};

int ShowMainMenu()
{
  patch_header(&mmenu_hdr);
  return CreateMenu(0,0,&mmenu,&mmenu_hdr,0,MAIN_MENU_ITEMS_N,0,0);
}

//-------------------------------------
//短信功能菜单
//-------------------------------------
const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)""},
  {0x0001,0x0000,(int)""},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

int is_sms_need=0;
WSHDR *ews;
//WSHDR *dbg_ws;

void edsms_locret(void){}

//字数计算
int get_word_count(GUI *data)
{
  int i,k=0;
  int l,len=0;
  EDITCONTROL ec;
  WSHDR *wsTemp=AllocWS(SMS_MAX_LEN);
  WSHDR *wsTemp2=AllocWS(15);
  ExtractEditControl(data, 2, &ec);
  len = wstrlen(ec.pWS);
  
  for(i=1;i<=ec.pWS->wsbody[0];i++)
  {
    if(ec.pWS->wsbody[i]>128)k=1;
  }
  
  if(k) 
  {
   l=330;
   if(len>70)
   k=(len+65)/66;
   else
   k=(len+69)/70;
  }
  else 
  {
   l=760;
   if(len>160)
   k=(len+151)/152;  
   else
   k=(len+159)/160;
  }
  if(k<=5)
  wsprintf(gwsTemp, "%t: %d - %d   (%d)","字数", k, len,l-len);
  else
  {
  wsprintf(gwsTemp, "%t: %t(%d/%d)","字数","超出长度",len,l);
  }
  ExtractEditControl(data, 1, &ec);
  wstrncpy(wsTemp, ec.pWS, gLen);
  wstrcat(wsTemp, gwsTemp); 
  wstrcpy(ec.pWS, wsTemp);
//REDRAW();
  ExtractEditControl(data, 2, &ec);
  FreeWS(wsTemp);
  FreeWS(wsTemp2);  
  return k;
}

void mmenuitem(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,"%t","换输入法");
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      input=1;
      break;
    }
  }
}

//按键控制
int edsms_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
 // const char *snum=EDIT_GetUserPointer(data);
  int key=msg->gbsmsg->submess;
  int m=msg->gbsmsg->msg;
  
     if(input==1)
     {
     GBS_SendMessage(MMI_CEPID,LONG_PRESS,0x23);
     input=0;
     return (-1);
     }
  
  
  if (m==KEY_DOWN)
   {  
  switch(key)
     {
  #ifdef NEWSGOLD
    case LEFT_SOFT:
  #else
    case RIGHT_SOFT:
  #endif
       {
      if(EDIT_IsMarkModeActive(data))
        return(-1);
      
      if(EDIT_IsBusy(data))
        return(0);     
      
      if((get_word_count(data)<=5))
      {
      ExtractEditControl(data,2,&ec);
      smstemp=AllocWS(ec.pWS->wsbody[0]);
      wstrcpy(smstemp,ec.pWS);
      smscount=(int)ec.pWS->wsbody[0];
      ws_2str(numTemp,smsnum,wstrlen(numTemp));
      if(sms_list)
      ShowMainMenu();
      else
      {
      mode=6;
      sendsms(); 
      }
      }
      else
      {
       ShowMSG(1,(int)"短信太长了!");
       return (-1);
      }
      
      break;
      }
      
     case ENTER_BUTTON:
      {
        if(EDIT_IsBusy(data))
        return(0);  
        else 
        {
        EDIT_OpenOptionMenuWithUserItems(data,mmenuitem,data,1);
        return (-1);
        }
      }
 
     case RED_BUTTON:
     {
      //ExtractEditControl(data,2,&ec);
      //smstemp=AllocWS(ec.pWS->wsbody[0]);
      //wstrcpy(smstemp,ec.pWS);
      smsdata=0;
      nxc=0;
      break;
     }
     
     case GREEN_BUTTON:
     {
      if(!sms_list)
      { 
      GeneralFuncF1(1);
      MakeVoiceCall(smsnum,0x10,0x2FFF);
      }
      break;
     }
     
  
     }
        
    }
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}


void edsms_ghook(GUI *data, int cmd)
{
   if(cmd != 2)
  {
    get_word_count(data);
  }
}

HEADER_DESC edsms_hdr={0,0,0,0,NULL,(int)"短信",LGP_NULL};

INPUTDIA_DESC edsms_desc=
{
  1,
  edsms_onkey,
  edsms_ghook,
  (void *)edsms_locret,
  0,
  &menu_skt,
  {0,0,0,0},
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
  0x40000000 // Change field coaching buttons 
};



//-------------------------------------
//ip电话菜单
//-------------------------------------

int cfg_ip_number3;

static void ip1(GUI *gui)
{
   cfg_ip_number3=cfg_ip_number1;
   need_ip=1;
   VoiceOrSMS(dstr2);
   numx=0;
}

static void ip2(GUI *gui)
{
   cfg_ip_number3=cfg_ip_number2;
   need_ip=1;
   VoiceOrSMS(dstr2);
   numx=0;
}

#define MAIN_MENU_ITEMS_2 2
static HEADER_DESC amenu_hdr={0,0,0,0,NULL,(int)"IP选项",LGP_NULL};

static MENUITEM_DESC amenu_ITEMS[MAIN_MENU_ITEMS_2]=
{
  {NULL,(int)"本地IP",LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"漫游和国际IP",LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}
};

static const MENUPROCS_DESC amenu_HNDLS[MAIN_MENU_ITEMS_N]=
{
  ip1,
  ip2,
};

static int amenu_keyhook(void *data, GUI_MSG *msg)
{
  return (0);
}

static void amenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const MENU_DESC amenu=
{
  8,amenu_keyhook,amenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x10,//MENU_FLAG,
  NULL,
  amenu_ITEMS,//menuitems,
  amenu_HNDLS,//menuprocs,
  MAIN_MENU_ITEMS_2
};

int ShowMainMenu2()
{
  patch_header(&amenu_hdr);
  return CreateMenu(0,0,&amenu,&amenu_hdr,0,MAIN_MENU_ITEMS_2,0,0);
}


//---------------------------------
//拨号短信控制
//---------------------------------
void VoiceOrSMS(const char *num)
{
  if (!is_sms_need)
  {
    	char buf[50];
	if(need_ip)
	{
		if(*num != '+')
                {
                        sprintf(buf,"%d",cfg_ip_number3);
			strcat(buf,num);
                }
		else if(*(num+1)== '8'&&*(num+2)== '6')
                {
                        sprintf(buf,"%d",cfg_ip_number3);
			strcat(buf,num+3);
                }
                else
                {
                  if(ip00)
                        sprintf(buf,"%d00",cfg_ip_number3);
                  else
                        sprintf(buf,"%d",cfg_ip_number3);
			strcat(buf,num+1);
                }

		need_ip = 0;
		MakeVoiceCall(buf,0x10,0x2FFF);
	}
	else
	{
		MakeVoiceCall(num,0x10,0x2FFF);
	}
  }
  
  else
  {
    void *ma=malloc_adr();
    void *eq;
    EDITCONTROL ec;
    PrepareEditControl(&ec);
    eq=AllocEQueue(ma,mfree_adr());
    char szTemp[46];

     wstrcpy(ews,gwsName);//名字

     if(smsn)
     {
     wsAppendChar(ews, '\n');  
     wsprintf(gwsTemp,"%s",num);
     wstrcpy(numTemp,gwsTemp);
     wstrcat(ews,gwsTemp);
     //wsAppendChar(gwsTemp,'\n');
     }

     if(smsc)
     {
     CutWSTR(gwsTemp, 0);
     strcpy(szTemp,num);
     GetProvAndCity(gwsTemp->wsbody,szTemp);//区号秀地址
     wsAppendChar(ews,'\n'); 
     wstrcat(ews, gwsTemp);
     }
     wsAppendChar(ews,'\n'); 
     
     gLen = wstrlen(ews);  //字数输出

    ConstructEditControl(&ec,1,0x40,ews,150);
    AddEditControlToEditQend(eq,&ec,ma);
    //wsprintf(ews,percent_t,"");
    CutWSTR(ews,0);
    if(smsdata==0)
    ConstructEditControl(&ec,4,0x40,ews,SMS_MAX_LEN);
    else
    ConstructEditControl(&ec,4,0x40,smstemp,SMS_MAX_LEN);//短信输入
    AddEditControlToEditQend(eq,&ec,ma);
    patch_header(&edsms_hdr);
    patch_input(&edsms_desc);
    CreateInputTextDialog(&edsms_desc,&edsms_hdr,eq,1,(void *)num);
  }
}


void Destructor(void)
{
  //GBS_DelTimer(&hours_tmr);
  //SaveCash();
  //EndUSSDtimer();
//  FreeWS(dbg_ws);
  FreeWS(gwsName);
  FreeWS(gwsTemp);
  FreeWS(numTemp);
  FreeWS(smstemp);
  FreeWS(ews);
}

void ElfKiller(void)
{      
	extern void *ELF_BEGIN;
       // extern void kill_data(void *p, void (*func_p)(void *));
  
        FreeCLIST();
        
	LockSched();
	CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
	memcpy(&icsmd,icsm->constr,sizeof(icsmd));
	icsmd.onMessage=old_icsm_onMessage;
	icsmd.onClose=old_icsm_onClose;
	icsm->constr=old_icsmd;
	UnlockSched();
        
        if(iReadFile && !cs_adr)
	  mfree((void*)cs_adr);
        if(my_pic) deleteIMGHDR(my_pic);
        //Destructor();

       // kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
       ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
        
}

//-------------------------------------
//屏幕主控
//-------------------------------------
int my_ed_onkey(GUI *gui, GUI_MSG *msg)   //按键功能
{
  int key=msg->gbsmsg->submess;
  int m=msg->gbsmsg->msg;
  int r=0;
  int i=0;
  int n,d,dn;
  
  CLIST *cl=(CLIST *)cltop;
  is_sms_need=0;
  
  
  if (sumx>1&&((key==LEFT_BUTTON)||(key==RIGHT_BUTTON)))
   {
    msg->keys=0;
   if ((m==KEY_DOWN)||(m==LONG_PRESS))
   {
    if(key==RIGHT_BUTTON)
    {
           numx++;   
        if((numx-sumx+1)>0)
          numx=0;
    }
    if(key==LEFT_BUTTON)
    {
           numx--;
         if(numx<0)
           numx=sumx-1;
    }
   }
   return(-1); 
  }
  
  if(key==RED_BUTTON)
  {
    numx=0;
    //smsdata=0;
  }
  
  if(e_ws && key==ENTER_BUTTON) // "##Enter" to exit
	{
		if(e_ws->wsbody[0]==2&&e_ws->wsbody[1]=='1'&&e_ws->wsbody[2]=='1')
		{
			ShowMSG(1,(int)"Megadial退出!");
			SUBPROC((void *)ElfKiller);
			return 1;
		}
		if(e_ws->wsbody[0]==2&&e_ws->wsbody[1]=='2'&&e_ws->wsbody[2]=='1')
		{
                        bcfgsetting();
			return 1;
		}
	}
  
  if ((key==ENTER_BUTTON)&&(m==KEY_DOWN))
   {
    EDITCONTROL ec;
    ExtractEditControl(gui,1,&ec);
    if (ec.pWS->wsbody[0]==EDIT_GetCursorPos(gui)-1)
    {
//    ShowMSG(1,(int)"Try to write SMS!");
      is_sms_need=1;
    }
   }
  
#ifdef ELKA
          if(key==ACTIVE_KEY||key==GREEN_BUTTON||is_sms_need)
#else
#ifdef NEWSGOLD
          if(key==ACTIVE_KEY||key==GREEN_BUTTON||is_sms_need)
#else
          if(key==ACTIVE_KEY||key==GREEN_BUTTON||is_sms_need)
#endif
#endif
  {
    DisableScroll();
    if (!cl) 
    {
      if(is_sms_need && e_ws&& (e_ws->wsbody[0] > 1))
      {
        char nx[40];
        WSHDR *sws=AllocWS(50);
        wstrcpy(sws,(WSHDR *)e_ws);
        ws_2str((WSHDR *)sws,nx,sws->wsbody[0]);
        gb2ws(gwsName,nx,sws->wsbody[0]);
        FreeWS(sws);
#ifndef NEWSGOLD
        if(dewin&&is_sms_need)
        {
        SendSMS(smstemp,nx, MMI_CEPID, MSG_SMS_RX-1, 1);
        }
        else
#endif
        {
        VoiceOrSMS(nx);
        nxc=1;
        }
        return(1);
      }
      else
      goto L_OLDKEY;
    }
    else
    {
    
    while(i!=curpos)
    {
      i++;
      cl=(CLIST *)cl->next;
      if (!cl) goto L_OLDKEY;
    }
    //Now cl indicates input 
    d=0;
    n=0;
    dn=0;
    do
    {
      if (cl->num[d])
      {
        //if (d==2) numx=n;
        ws_2str(cl->num[d],dstr[n],39);
              wstrcpy(gwsTemp,cl->num[d]);
             if(CompareStrT9(gwsTemp,(WSHDR *)e_ws,0))
             {
                  strncpy(dstr3,dstr[0],39);
                  strncpy(dstr[0],dstr[n],39);
                  strncpy(dstr[n],dstr3,39);
                  dn=1;
             }

             if(d==priority&&dstr[0]&&dn==0)
             {
                  strncpy(dstr3,dstr[0],39);
                  strncpy(dstr[0],dstr[n],39);
                  strncpy(dstr[n],dstr3,39);
             }
        ++n;
      }
      d++;
    }
    while(d<NUMBERS_MAX);
    wstrcpy(gwsName, cl->name);

    if (n==0) goto L_OLDKEY; //No phones altogether 

    if(n>0)
    {
#ifdef ELKA
          if(key==ACTIVE_KEY)
#else
#ifdef NEWSGOLD
          if(key==ACTIVE_KEY)
#else
          if(key==ACTIVE_KEY)
#endif
#endif
      {   
      if(ipx2)
      {
      strcpy(dstr2,dstr[numx]); 
      ShowMainMenu2();
      }
      else
      {
      cfg_ip_number3=cfg_ip_number1;
      need_ip=1;
      VoiceOrSMS(dstr[numx]);
      numx=0;
      }
      }
      else
      {
#ifndef NEWSGOLD
      if(dewin&&is_sms_need)  
      SendSMS(smstemp,dstr[numx], MMI_CEPID, MSG_SMS_RX-1, 1);  
      else
#endif
      VoiceOrSMS(dstr[numx]);
      numx=0;
      }
      return(1); //Close tries 
    }
    return(0);
    }
  }
  
  if ((key==UP_BUTTON)||(key==DOWN_BUTTON))
  {
    //Do not treat editor of up / down
    msg->keys=0;
    if ((m==KEY_DOWN)||(m==LONG_PRESS))
    {
      DisableScroll();
      is_pos_changed=1;
      if (key==UP_BUTTON)
      {
		if (curpos)
			curpos--;
		else if(cl)
		{
			cl=(CLIST *)cltop;
			while(cl->next)
			{
				curpos++;
				cl=(CLIST *)cl->next;
			}
		}
                 numx=0;
      }
      if (key==DOWN_BUTTON)
      {
		if (cl)
		{
			do
			{
			cl=(CLIST *)cl->next;
			if (!cl) break;
			i++;
			}
			while(i<=curpos);
		}
		if(cl)curpos=i;
		else curpos=0;
                numx=0;
      }
    }
    r=-1; //Redraw 
  }
  else
  {
    #ifdef NEWSGOLD
    if ((key>='0'&&key<='9')||(key=='*')||(key=='#')||(key==RIGHT_SOFT))
    #else
    if ((key>='0'&&key<='9')||(key=='*')||(key=='#')||(key==LEFT_SOFT))
    #endif
    {
      if (m==KEY_DOWN)
      {
	DisableScroll();
        is_pos_changed=0;
	if (hook_state>=2)  //Changes to the line input is required search 
        {
	  hook_state=3;
	}
      }
    }
  L_OLDKEY:
    r=old_ed_onkey(gui,msg);
  }
  ChangeRC(gui);
  return(r);
}

void my_ed_ghook(GUI *gui, int cmd)
{
  int a=0;
  int bcalling;
  static void *methods[16];
  void **m=GetDataOfItemByID(gui,4);
  if ((hook_state==1)/*&&(cmd==7)*/)
  {
    //Tseplyaem method onRedraw 
    if (m)
    {
      if (m[1])
      {
	memcpy(methods,m[1],sizeof(methods));
	old_ed_redraw=(void (*)(void *))(methods[0]);
	methods[0]=(void *)my_ed_redraw;
	m[1]=methods;
	hook_state=3; //Query Search 
      }
    }
  }
  old_ed_ghook(gui, cmd);
  if (cmd==7)
  {
#ifdef ELKA
#else
          if(cltop)
          {
             static SOFTKEY_DESC skIP={0x0018,0x0000,(int)"IP电话"};
#ifdef NEWSGOLD
             if(ACTIVE_KEY==LEFT_SOFT)
             SetSoftKey(gui,&skIP,0);
#else
             if(ACTIVE_KEY==RIGHT_SOFT)
             SetSoftKey(gui,&skIP,1);
#endif
          }
#endif
    EDITCONTROL ec;
    ExtractEditControl(gui,1,&ec);
    //New Line Search 
   if(disable_when_calling)//disable when calling
   {
     bcalling = IsCalling();
     if(bcalling)
	return;
   }
    if ((e_ws=ec.pWS)->wsbody[0]<MAX_ESTR_LEN&&(cfg_disable_one_number?((e_ws=ec.pWS)->wsbody[0]>1):1)) //Its length? <MAX_ESTR_LEN 
    {
      if (hook_state==3)
      {
	curpos=0;
	hook_state=4;
	SUBPROC((void *)ConstructList);
      }
    }
     if(cfg_disable_one_number&&((e_ws=ec.pWS)->wsbody[0]==1))   
     {
       a=1;
       FreeCLIST();
     }
     else
       a=0;
  }
  if(!a)
  ChangeRC(gui);
}

void DoSplices(GUI *gui)
{
  static INPUTDIA_DESC my_ed;
  memcpy(&my_ed,gui->definition,sizeof(INPUTDIA_DESC));
  old_ed_onkey=my_ed.onKey;
  old_ed_ghook=my_ed.global_hook_proc;
  my_ed.onKey=my_ed_onkey;
  my_ed.global_hook_proc=my_ed_ghook;
  gui->definition=&my_ed;
  is_pos_changed=0;
}

static GBSTMR vibra_tmr;

static void vibra_tmr_proc(void)
{
  SetVibration(0);
}   
/*
const char white[4]={0xFF,0xFF,0xFF,0x64};
const char transparent[4]={0,0,0,0};
static void DrawMyProgress(int y, int n)
{
  int start_y, end_y, font_size,scr_w,fill, cur, max;
  WSHDR *ws=AllocWS(32);
  scr_w=ScreenW();
  cur=CurrentCASH[n];
  max=MaxCASH[n];
  fill=((long long)cur)*(scr_w-5)/max;
  font_size=GetFontYSIZE(TEXT_FONTSZ)+1;
  start_y=y+n*font_size;
  end_y=y+(n+1)*font_size-1;
  
  DrawCanvas(BuildCanvas(), 1, start_y, scr_w-2, end_y, 1);
  DrawRectangle(1,start_y,scr_w-2,end_y,0,white,transparent);
  DrawRectangle(2,start_y+1,fill+2,end_y-1,0,progress_colors[n],progress_colors[n]);
  wsprintf(ws,"%u.%02u/%u.%02u",cur/100,cur%100,max/100,max%100);
  DrawString(ws,3,start_y+1,scr_w-4,end_y-1,TEXT_FONTSZ,TEXT_ALIGNMIDDLE,COLOR_TEXTPB,transparent);
  FreeWS(ws);
}
 
static void HoursTimerProc(void)
{
  SendCashReq();
}

void StartHoursTimer(void)
{
  if (CHECK_HOURS)
  {
    TTime t; int sc;
    GetDateTime(0, &t);
    sc = 3600*CHECK_HOURS - 60*t.min - t.sec;
    GBS_StartTimerProc(&hours_tmr, sc*1300/6, HoursTimerProc);
  }
}

static volatile int is_voice_connected=0;
*/

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
#define edialgui_id (((int *)data)[DISPLACE_OF_EDGUI_ID/4])
  int csm_result;
  /*
  {
    char *imsi=RAM_IMSI();
    if (memcmp(imsi,cur_imsi,IMSI_DATA_BYTE_LEN))
    {
      SaveCash();
      memcpy(cur_imsi,imsi,IMSI_DATA_BYTE_LEN);
      InitConfig();
      LoadCash();
      StartHoursTimer();
    }
  }
  if (msg->msg==MSG_USSD_RX || msg->msg==MSG_AUTOUSSD_RX)
  {
    if (ProcessUSSD(data,(GBS_USSD_MSG *)msg)) return 0; //Obrabotanno 
  }
  
  if (msg->msg==MSG_END_CALL)
  {
    if (ENA_CASHTRACE) 
    {
      if (is_voice_connected)
      {
	GBS_DelTimer(&hours_tmr);
	SendCashReq();
      }
    }
    is_voice_connected=0;
  }
  */
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==edialgui_id)
    {
      hook_state=0;
      e_ws=0;
      FreeCLIST();
      DisableScroll();
    }
  }
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MegaDial设置更新完成!");
      RereadSettings();
    }
  }
  static volatile int is_incoming_call=0;
  if (msg->msg==MSG_INCOMMING_CALL)
   is_incoming_call=1;
  #ifdef NEWSGOLD
  if ((msg->msg==MSG_STATE_OF_CALL||msg->msg==MSG_END_CALL)&&(msg->submess==1)&&((int)msg->data0==2))
  #else
  if ((msg->msg==MSG_STATE_OF_CALL||msg->msg==MSG_END_CALL)&&(msg->submess==1)&&((int)msg->data0==0))
  #endif   
  {
    //is_voice_connected=1;
    if (ENA_VIBRA)
    {
    if (ENA_VIBRA==3 || is_incoming_call+ENA_VIBRA==2)
    {
      SetVibration(vibraPower);
      GBS_StartTimerProc(&vibra_tmr, vibraDuration*TMR_SECOND/1000, vibra_tmr_proc);
    }
    is_incoming_call=0;
    }
  }
  
  csm_result=old_icsm_onMessage(data,msg); //call old handler events  
  
  /*
    if (cfgShowIn != 1 - IsUnlocked())
  {
    if (IsGuiOnTop(idlegui_id)) //If IdleGui at the top 
    {
      GUI *igui = GetTopGUI();
      if (igui) //And it is 
      {
        extern int CASH_SIZE;               //by BoBa 4.07.07

        int n=0; //Number    
        while(n<CASH_SIZE)
        {
          DrawMyProgress(IDLE_Y,n);
          n++;
        }
      }
    }
  }
  */
    if (IsGuiOnTop(edialgui_id)) //If IdleGui at the top 
    {
    GUI *igui=GetTopGUI();
    if (igui) //And it is (not in the draft;)) 
    {
      if (!hook_state)
      {
	//There was no dialogue
        DoSplices(igui);
	hook_state=1;
      }
    }
  }
  return(csm_result);
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  if(my_pic) deleteIMGHDR(my_pic);
  if(iReadFile && !cs_adr)
    mfree((void*)cs_adr);
  Destructor();
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}




int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onClose=MyIDLECSM_onClose;
  icsmd.onMessage=MyIDLECSM_onMessage;
  old_icsmd=icsm->constr;
  icsm->constr=&icsmd;
  UnlockSched();
  ews=AllocWS(SMS_MAX_LEN);
//dbg_ws=AllocWS(256);
  gwsTemp=AllocWS(240);
  numTemp=AllocWS(40);
  gwsName=AllocWS(40);
  InitIcons();
  RereadSettings();
  return 0;
}

