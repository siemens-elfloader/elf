char per_d[]="%d";
int len=0;

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

char *dec2boh(int dec,int sys)//dec->bin,oct,hex:) ; sys-2,8 
{
  int i=0;
  int j=0;
  char *tmp=malloc(32);
  char *s=malloc(32);
  while(dec>0)
  {
    i=0;
    i=dec%sys;
    dec=dec/sys;
    sprintf(s,per_d,i);
    *(tmp+j)=*s;
    j++;
    if(dec==1)
     {
      sprintf(s,per_d,1);
      *(tmp+j)=*s;
      break;
     }
  }
  j++;
  *(tmp+j)=0;
  for(i=strlen(tmp)-1;i>=0;i--)
  {
    s[strlen(tmp)-i]=tmp[i];
  }
  len=strlen(tmp);
return s;
}

int boh2dec(char *boh,int sys)//bin,oct,hex->dec ; sys-2,8,16 //Преобразуем в десятичное число
{
  int i=0;
  int rez=0;
  int j=0;
  for(i=strlen(boh),j=0;i>=0;j++,i--)
   {
     if(boh[i]=='1' && sys==2)//на 0 нет смысла умножать(для двоичной системы):)
      rez+=pow(sys,j-1);
    else
      rez+=pow(sys,j-1);
   }
return rez;
}


/*
char *dec2bin(int dec)
{
  int i=0;
  int j=0;
  char *tmp=malloc(32);
  char *s=malloc(32);
  while(dec>0)
  {
    i=0;
    i=dec%2;
    dec=dec/2;
    sprintf(s,per_d,i);
    *(tmp+j)=*s;
    j++;
    if(dec==1)
     {
      sprintf(s,per_d,1);
      *(tmp+j)=*s;
      break;
     }
  }
  j++;
  *(tmp+j)=0;
  for(i=strlen(tmp)-1;i>=0;i--)
  {
    s[strlen(tmp)-i]=tmp[i];
  }
  len=strlen(tmp);
return s;
}

int bin2dec(char *bin)
{
  int i=0;
  int rez=0;
  int j=0;
  for(i=strlen(bin),j=0;i>=0;j++,i--)
   {
     if(bin[i]=='1')//на 0 нет смысла умножать:)
      rez+=pow(2,j-1);
   }
return rez;
}

//-------------------------------//

char *dec2oct(int dec)
{
 int i=0;
 int j=0;
 char *s=malloc(32);
 char *tmp=malloc(32);
 while(dec>0)
  {
   i=0;
   i=dec%8;
   dec=dec/8;
   sprintf(s,per_d,i);
   *(tmp+j)=*s;
   j++;
   if(dec==1)
    {
      sprintf(s,per_d,1);
      *(tmp+j)=*s;
     break;
    }
  }
  j++;
  *(tmp+j)=0;
  for(i=strlen(tmp)-1;i>=0;i--)
  {
    s[strlen(tmp)-i]=tmp[i];
  }
  len=strlen(tmp);
return s;
}

const char per_c[]="%c";
int oct2dec(char *bin)
{
  long rez=0;
  long c=0;
  char d[1];
  int i;
  int j=0;
  for(i=strlen(bin),j=0;i>=0;j++,i--)
   {
    sprintf(d,per_c,bin[i]);
    c=strtoul(d,0,10);
    rez+=pow(8,j-1)*c;
   }
return rez;
}

int hex2dec(char *bin)
{
  long rez=0;
  long c=0;
  char d[1];
  int i;
  int j=0;
  for(i=strlen(bin),j=0;i>=0;j++,i--)
   {
    sprintf(d,per_c,bin[i]);
    c=strtoul(d,0,16);
    rez+=pow(16,j-1)*c;
   }
return rez;
}*/
//--------------------------------Редактор--------------------------------//

HEADER_DESC disk_prop_hdr={0,0,131,21,NULL,0,LGP_NULL};
int id_create;
enum editcontrols
{
  ec_dec=2,
  ec_bin=4,
  ec_oct=6,
  ec_hex=8,
};

enum sys
{
  dec=10,
  bin=2,
  oct=8,
  hex=16,
};

int id_ed2;
extern int menu_id;
int empty_onkey(GUI *data, GUI_MSG *msg)
{
//  void *edgui=FindGUIbyId(id_create,NULL);
  
 if(msg->keys==LEFT_SOFT || msg->keys==RED_BUTTON)
 {
  GeneralFunc_flag1(menu_id,1);
  GeneralFunc_flag1(id_ed,1);
  GeneralFunc_flag1(id_ed2,1); 
 }
 return(0);
}

SOFTKEY_DESC sk[];
SOFTKEYSTAB skt={ sk,0 };

void empty_locret(void){}

void empty_ghook(GUI *gui, int cmd)
{ 
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Convert"};
  
  if(cmd==0xA)
  {
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
  
  if(cmd==0x03)     // onDestroy
  {
  }
  
  if (cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);
  }
}

INPUTDIA_DESC edit_desc=//Редактирование
{
  1,
  empty_onkey,
  empty_ghook,
  (void *)empty_locret,
  0,
  &skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};
 
//--------------------------------------------------------//

int ed_create(int i,char *s)
{     
  EDITCONTROL ec;
  PrepareEditControl(&ec);

  char *ss=malloc(32);
  void *ma=malloc_adr();
  void *eq=AllocEQueue(ma, mfree_adr());
  WSHDR *ws=AllocWS(256);
  WSHDR *ws_dec=AllocWS(256);
  WSHDR *ws_bin=AllocWS(256);
  WSHDR *ws_oct=AllocWS(256);
  WSHDR *ws_hex=AllocWS(256);
  /*
  switch(i)
  {
   case 0: //DEC
     wsprintf(ws_dec,per_s,s);
     ss=dec2bin(strtoul(s,0,10));

     CutWSTR(ws_bin,0);
     for(i=0;i<=len;i++)
        wsInsertChar(ws_bin,ss[i],i);
       
      ss=dec2oct(strtoul(s,0,10));
      CutWSTR(ws_oct,0);
      for(i=0;i<=len;i++)
        wsInsertChar(ws_oct,ss[i],i);
      
      CutWSTR(ws_hex,0);
      wsprintf(ws_hex,"%X",strtoul(s,0,10));     
     break;
     
     case 1: //BIN
      wsprintf(ws_bin,per_s,s); 
      wsprintf(ws_dec,per_d,bin2dec(s));//bin->dec

      ws_2str(ws_dec,s,wstrlen(ws_dec));
      ss=dec2oct(strtoul(s,0,10));//dec->oct
      CutWSTR(ws_oct,0);
      for(i=0;i<=len;i++)
        wsInsertChar(ws_oct,ss[i],i);
      
      CutWSTR(ws_hex,0);
      wsprintf(ws_hex,"%X",strtoul(s,0,10));//dec->hex
       break;       
       
     case 2: //OCT
       wsprintf(ws_oct,per_s,s);//oct
       wsprintf(ws_dec,per_d,oct2dec(s));//oct->dec
       
       ws_2str(ws_dec,s,wstrlen(ws_dec));
       ss=dec2bin(strtoul(s,0,10));//dec->bin
       CutWSTR(ws_bin,0);
       for(i=0;i<=len;i++)
         wsInsertChar(ws_bin,ss[i],i);
       
       CutWSTR(ws_hex,0);
       wsprintf(ws_hex,"%X",strtoul(s,0,10));//dec->hex      
      break;
      
     case 3:  //HEX
       wsprintf(ws_hex,per_s,s);//hex
       wsprintf(ws_dec,per_d,hex2dec(s));//hex->dec
       
       ws_2str(ws_dec,s,wstrlen(ws_dec));
       ss=dec2bin(strtoul(s,0,10));//dec->bin
       CutWSTR(ws_bin,0);
       for(i=0;i<=len;i++)
         wsInsertChar(ws_bin,ss[i],i);
       
      ss=dec2oct(strtoul(s,0,10));//dec->oct
      CutWSTR(ws_oct,0);
      for(i=0;i<=len;i++)
        wsInsertChar(ws_oct,ss[i],i);
       break;
  }*/
  
  int j=0;
  switch(i)
  {
   case 0: //DEC
     wsprintf(ws_dec,per_s,s);
     ss=dec2boh(strtoul(s,0,10),bin);//dec->bin

     CutWSTR(ws_bin,0);
     for(i=0;i<=len;i++)
     {
       if(j<4)
       {
        wsInsertChar(ws_bin,ss[i],i);
        j++;
       }
       else 
       {
         wsInsertChar(ws_bin,' ',i);//Вставляем пробел чтобы разбить по 4 цифры...
         j=0;
       }
     }       
     ss=dec2boh(strtoul(s,0,10),oct);//dec->oct
     CutWSTR(ws_oct,0);
     j=0;
     for(i=0;i<=len;i++)
      {
       if(j<4)
        {
         wsInsertChar(ws_oct,ss[i],i);
         j++;
        }
        else 
        {
         wsInsertChar(ws_oct,' ',i);//Вставляем пробел чтобы разбить по 4 цифры...
         j=0;
        }
      }      
      CutWSTR(ws_hex,0);
      wsprintf(ws_hex,"%X",strtoul(s,0,10));//dec->hex
     break;
     
     case 1: //BIN
      wsprintf(ws_bin,per_s,s); 
      wsprintf(ws_dec,per_d,boh2dec(s,dec));//bin->dec

      ws_2str(ws_dec,s,wstrlen(ws_dec));
      ss=dec2boh(strtoul(s,0,10),oct);//dec->oct
      CutWSTR(ws_oct,0);
      for(i=0;i<=len;i++)
        wsInsertChar(ws_oct,ss[i],i);
      
      CutWSTR(ws_hex,0);
      wsprintf(ws_hex,"%X",strtoul(s,0,10));//dec->hex
       break;       
       
     case 2: //OCT
       wsprintf(ws_oct,per_s,s);//oct
       wsprintf(ws_dec,per_d,boh2dec(s,dec),dec);//oct->dec
       
       ws_2str(ws_dec,s,wstrlen(ws_dec));
       ss=dec2boh(strtoul(s,0,10),bin);//dec->bin
       CutWSTR(ws_bin,0);
       for(i=0;i<=len;i++)
         wsInsertChar(ws_bin,ss[i],i);
       
       CutWSTR(ws_hex,0);
       wsprintf(ws_hex,"%X",strtoul(s,0,10));//dec->hex      
      break;
      
     case 3:  //HEX
       wsprintf(ws_hex,per_s,s);//hex
       wsprintf(ws_dec,per_d,boh2dec(s,hex));//hex->dec
       
       ws_2str(ws_dec,s,wstrlen(ws_dec));
       ss=dec2boh(strtoul(s,0,10),bin);//dec->bin
       CutWSTR(ws_bin,0);
       for(i=0;i<=len;i++)
         wsInsertChar(ws_bin,ss[i],i);
       
      ss=dec2boh(strtoul(s,0,10),oct);//dec->oct
      CutWSTR(ws_oct,0);
      for(i=0;i<=len;i++)
        wsInsertChar(ws_oct,ss[i],i);
       break;
  }

  wsprintf(ws,per_t,"DEC:\n");
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws,10);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ws_dec,32);
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(ws,per_t,"BIN:");
  ConstructEditControl(&ec,ECT_HEADER,ECF_SET_CURSOR_END,ws,10);
  AddEditControlToEditQend(eq,&ec,ma);

  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ws_bin,32);
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ws,per_t,"OCT:\n");
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws,11);
  AddEditControlToEditQend(eq,&ec,ma);

  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ws_oct,32);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  wsprintf(ws,per_t,"HEX:\n");
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws,11);
  AddEditControlToEditQend(eq,&ec,ma);

  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_hex,32);
  AddEditControlToEditQend(eq,&ec,ma);  

  disk_prop_hdr.lgp_id = (int)"ConvertorSS";        
  patch_header(&disk_prop_hdr);
  patch_input(&edit_desc);      

  FreeWS(ws);
  return id_create=CreateInputTextDialog(&edit_desc,&disk_prop_hdr,eq,1,0);
}

//--------------------------------INPUT----------------------------------//
char hdr[64];
HEADER_DESC pos_hdr={0,0,131,21,NULL,(int)hdr,LGP_NULL};
int conv=0;
int pos_onkey(GUI *data, GUI_MSG *msg)
{
  WSHDR *ws=AllocWS(64);
  char num[32];
  if (msg->keys==0x0018)//0xFFF
  {
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);	
    ws=ec.pWS;
    ws_2str(ws,num,ec.maxlen);
    ed_create(conv,num);
  }
return(0);
}

void pos_ghook(GUI *gui, int cmd)
{ 
  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Convert"};
  if (cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);
  }
  if(cmd==0xA)
  {
    DisableIDLETMR(); // Отключаем таймер выхода по таймауту
  }
  if (cmd==0x0C)
  {
  }
  if(cmd==0x03){}
}

void pos_locret(void){}

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

INPUTDIA_DESC pos_desc=
{
  1,
  pos_onkey,
  pos_ghook,
  (void *)pos_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  0x00000000,
  0x40000000
};

char *cc[]={"DEC","BIN","OCT","HEX"};
void input(int i)
{
   conv=i;
   EDITCONTROL ec;
   sprintf(hdr,"%s %s","Input",cc[i]);
   void *ma=malloc_adr();
   void *eq=AllocEQueue(ma, mfree_adr());

   PrepareEditControl(&ec);
   if(i!=3)
    ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ec.pWS,32);
   else
     ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ec.pWS,32);
   AddEditControlToEditQend(eq,&ec,ma);

   patch_header(&pos_hdr);
   patch_input(&pos_desc);      
 
   id_ed2=CreateInputTextDialog(&pos_desc,&pos_hdr,eq,1,0);//создаем диалоговое окно
}