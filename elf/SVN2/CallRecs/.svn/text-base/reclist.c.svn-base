#include "reclist.h"
#include "..\inc\swilib.h"

 typedef  struct {
  dates datetime;
  WSHDR  *Number;
  WSHDR  *Name;  
  unsigned int duration;
  unsigned char type; //битовое поле флагов
  unsigned int recId;  //ид записи, мож пригодится
  char cnt;  //если группа то число субитемов -1
  char isGroup;  //признак группы
}CContactL;


short GetNumberByRecId( int rec, char *num){
  char recname[128];
            #ifdef NEWSGOLD
	    //Запись есть в битмапе
            unsigned int rl1;
	    unsigned int rl2;
	    unsigned int rl3;
	    rl1=rec/LEVEL1_RN;
	    rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
	    rl3=rec%LEVEL2_RN;
    	    snprintf(recname,128,"0:\\System\\apo\\" APO_EN "\\data\\%02d\\%02d\\%02d",rl1,rl2,rl3);
            
            #else
	    unsigned int rl1=rec/LEVEL1_RN;
	    unsigned int r12=rec%LEVEL1_RN;
	    snprintf(recname,128,"0:\\System\\apo\\" APO_EN "\\%02x\\%02x",rl1,r12);            
            #endif             

  
int fin;
unsigned short type=0;
unsigned int ul,fsz;  
if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	    {
              AB_UNPRES ur;
              void *buffer;                
	      zeromem(&ur,sizeof(AB_UNPRES));
              fsz=lseek(fin,0,S_END,&ul,&ul);
//              buffer=malloc(fsz);              
              buffer=malloc(((fsz<<4)>>4));

              lseek(fin,0,S_SET,&ul,&ul);
  	      fread(fin,buffer,fsz,&ul);
	      fclose(fin,&ul);
              #ifdef NEWSGOLD
	      UnpackABentry(&ur,((char *)buffer+8),fsz,APO_TYPE);
              #else
              UnpackABentry(&ur,((char *)buffer+4),fsz-4,APO_TYPE);
              #endif
	      int i=0;
              
              while(i<ur.number_of_records)
	      {
                
		AB_UNPRES_ITEM *r=ur.record_list+i;
		if (r->no_data!=1)
		{

		  if (GetTypeOfAB_UNPRES_ITEM(r->item_type)==1)
                   {        //номер          
                      PKT_NUM *p=(PKT_NUM*)r->data;
                      if (p){
                        memcpy(num,p->data,8);

                        
                      }
                   }else
		  if (GetTypeOfAB_UNPRES_ITEM(r->item_type)==0)
                   {        //флаги
                     
                      if (r->item_type==0x55)  type|=0x4000*(*((short*)r->data)); //if 1 -incomig call
                      if (r->item_type==0x56)  type|=0x8000*(*((short*)r->data));  //not answered 
                   };
                                          
                     
                      
                }
		i++; //next record
	      }
              //all readed
	      FreeUnpackABentry(&ur,mfree_adr());
              mfree (buffer);
            }else
              return 0;
  if ((type&0xc000)==0xc000)type=RECORD_TYPE_MISS;
    else
      if ((type&0x4000)==0x4000)type=RECORD_TYPE_RECV;else
        type=RECORD_TYPE_DIAL;
  return type;
}

void ZeroContact(CContact *loc){
  WSHDR*w1=loc->Name; 
  WSHDR*w2=loc->Number;                 
  loc->recId=-1;
  zeromem(loc,sizeof(CContact));
  loc->Name=w1;
  loc->Number=w2;
}

void GetRecordInfo2Cache(unsigned int rec, CContact *loc)//собсветнно чтени АПО  
// ВНИМАНИЕ ЧТЕНИЕ НАПИСАНО ПОД ЕЛКУ и наверно НСГ, и идет с последней записи а не с первой, на СГОЛД надо чето придумать
{
  unsigned int orr=rec;
  rec=rec&0x1FF;




  unsigned int ul;

  int fin;
  

  
  

//    unsigned int rec=0;

  int fsz;
  char recname[128];  
  
  AB_UNPRES ur;
  void *buffer;

//start parsing  
  if ((buffer=malloc(512)))
  {


      {
	  {
            
            #ifdef NEWSGOLD
	    //Запись есть в битмапе
            unsigned int rl1;
	    unsigned int rl2;
	    unsigned int rl3;
	    rl1=rec/LEVEL1_RN;
	    rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
	    rl3=rec%LEVEL2_RN;
    	    snprintf(recname,128,"0:\\System\\apo\\" APO_EN "\\data\\%02d\\%02d\\%02d",rl1,rl2,rl3);
            
            #else
	    unsigned int rl1=rec/LEVEL1_RN;
	    unsigned int r12=rec%LEVEL1_RN;
	    snprintf(recname,128,"0:\\System\\apo\\" APO_EN "\\%02x\\%02x",rl1,r12);            
            #endif             
            if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	    {
	      zeromem(&ur,sizeof(AB_UNPRES));
              fsz=lseek(fin,0,S_END,&ul,&ul);
              lseek(fin,0,S_SET,&ul,&ul);
  	      fread(fin,buffer,fsz,&ul);
	      fclose(fin,&ul);
              #ifdef NEWSGOLD
	      UnpackABentry(&ur,((char *)buffer+8),fsz,APO_TYPE);
              #else
              UnpackABentry(&ur,((char *)buffer+4),fsz-4,APO_TYPE);
              #endif
	      int i=0;

               ZeroContact(loc)                 ;
          //    
              loc->recId=orr;
              while(i<ur.number_of_records)
	      {
                
		AB_UNPRES_ITEM *r=ur.record_list+i;
		if (r->no_data!=1)
		{


                  switch (GetTypeOfAB_UNPRES_ITEM(r->item_type))
                  {
                    case 6: //дата
                      memcpy(&loc->datetime,r->data,sizeof(dates));
                      break;
                    case 5: //имя
                        wstrcpy(loc->Name,r->data);
                      break;    
                      
                    case 1:  {        //номер          
                      PKT_NUM *p=(PKT_NUM*)r->data;
                      if (p){
                        unsigned int c;
                        unsigned int c1;
                        int m,j;
                        j=0;
                        m=0;

                        wsprintf(loc->Number,"")      ;
                        //wsAppendChar(contact.icons,utf_symbs[n]);
                        if (p->format==0x91) wsAppendChar(loc->Number,'+');                        
                        
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
//                            loc->number[m++]=c1;
                            wsAppendChar(loc->Number,c1);

			    m++;
			  }


                      }
                      }
                      break;
                    case 3://unsigned short / timne in secs?
                      if (r->item_type==0x52)
                      {
                        loc->duration=*((short*)r->data);
                      }
                      break;
                    case 0://unsigned int/ boolean ?
                      if (r->item_type==0x54)  loc->type|=0x01*(*((short*)r->data));  //kto polozil trubku (1 -sam)
                      if (r->item_type==0x55)  loc->type|=0x02*(*((short*)r->data)); //if 1 -incomig call
                      if (r->item_type==0x56)  loc->type|=0x04*(*((short*)r->data));  //not answered 
                      if (r->item_type==0x57)  loc->type|=0x08*(*((short*)r->data));  //conected by service  suzh as mts and wrong number 
                      if (r->item_type==0x58)  loc->type|=0x10*(*((short*)r->data));  // ??? rejected
                      if (r->item_type==0x59)  loc->type|=0x20*(*((short*)r->data));  //all side connected
                      if (r->item_type==0x5a)  loc->type|=0x40*(*((short*)r->data));
                                                                                                        //06 -07 missed calls
                      break;
                    
                  };
                }
		i++; //next record
	      }
              //all readed
	      FreeUnpackABentry(&ur,mfree_adr());
            }
	
	  }
       
//          rec++;
        
     mfree(buffer) ;
    }
}
///end of parsing

};

inline int FindNumber (char *num, unsigned short mask){
  
  for (int i=0;i<rcCnt;i++)
    if ((((rc[i].recId)&mask)==mask)&&(!memcmp(rc[i].Number,num,8))){
      return i;
    }
  return -1;
}

void PutRecord(int id,char *num){
  
  int ex=FindNumber(num,id&0xFE00);
  int j=rcCnt;
  if (ex!=-1){
    //get last rec

    for ( j=ex+1;j<MAX_RECORDS&&(rc[j].ids.oxFF==-1);j++){
      
    };
    //j new index;
    // shift array for new record;
//    rc[ex].cnt++;
    
    rc[ex].recId|=RECORD_IS_GROUP;
    memmove(&rc[j+1],&rc[j],MAX_RECORDS-j-1);
    rc[j].recId=id|RECORD_IN_GROUP;    
//    memcpy(rc[j].Number,num,8);        
    rc[j].ids.oxFF=-1;
    rc[j].ids.idParentItem=ex;

  }else{
    
    //write new record
  
    rc[j].recId=id;    
    memcpy(rc[j].Number,num,8);        
}

  rcCnt++;
}


int ReadRecord(int lastrecord)//собсветнно чтени АПО  
{
  int delv=0;
  unsigned int ul;
  int fin;
   int rec;    
  char num[8];  
  void *buffer;
//start parsing  
  if ((buffer=malloc(512)))
  {
    zeromem(&ABmain,sizeof(ABmain));

    if ((fin=fopen("0:\\System\\apo\\" APO_EN "\\main",A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
    {
  
#ifdef ELKA
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=69)
#else
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
      {
#ifdef NEWSGOLD   

        rec=ABmain.len-1;  //-1 потому как это адресс следующей
#else
        rec=MAX_RECORDS-1;//чит
#endif         
        fclose(fin,&ul);
	do
	{
          int tp=GetNumberByRecId(rec,num);
    

          if (tp){
            PutRecord((rec|tp|RECORD_TYPE_ALL),num);
            delv++;
          }
          
          rec--;          //читы

        }  
	while(rec>lastrecord);        //читы
        
      }
      else
      {
	fclose(fin,&ul);
      }
      mfree(buffer) ;
    }
  }
///end of parsing

#ifdef DEMON
  ShowMSG(1,(int)"Call Records read.");
#endif
  return rec;
  

}
void InitContacts(void){
  zeromem(cache,sizeof(cache));
  for (int j=0;j<CONTACT_CACHE_SIZE;j++)  {
    cache[j].Name=AllocWS(64);
    cache[j].Number=AllocWS(16);    
    cache[j].recId=-1;
    
  }
    
}

void ClearContacts(){
  for (int j=0;j<CONTACT_CACHE_SIZE;j++) 
  {
    FreeWS(cache[j].Name);
    FreeWS(cache[j].Number);    
  }
    
}

int GetCacheRecordById(int id){

  for (int j=0;j<CONTACT_CACHE_SIZE;j++)  
    if (((cache[j].recId)&0x1ff)==(id&0x1ff)){
      unsigned short msk=id&0xFE00;
        cache[j].recId|=msk;
      
      return j;
    }   else{
    }
      
  // add to cache
  //clear top
  WSHDR *w1=cache[CONTACT_CACHE_SIZE-1].Name;
  WSHDR *w2=cache[CONTACT_CACHE_SIZE-1].Number;  
  
  //memmove(&cache[1],&cache[0],sizeof(CContact)*(CONTACT_CACHE_SIZE-1) ); //dst,src
  for (int l=(CONTACT_CACHE_SIZE-1);l>=1;l--){
    memcpy(&cache[l],&cache[l-1],sizeof(CContact));
  }
  cache[0].Name=w1;
  cache[0].Number=w2;  
  GetRecordInfo2Cache(id,&cache[0]);
//  unsigned short msk=id&0xFE00;
//  cache[0].recId|=msk;
  return 0;
};
void PostProcessRecords(void){//group
}
 short  GetNextIdMask(int curId,int mask){
  for (int j=curId;j<MAX_RECORDS;j++){    
    if ((rc[j].recId&mask)==mask)return j;
  }    
  return -1;
}
 short  GetNextId(int curId,int mask){
  
  for (int j=curId;j<MAX_RECORDS;j++){    
    if ((rc[j].recId&mask)!=mask)continue;
    
    if ((rc[j].recId&RECORD_IS_GROUP_EXPND)==RECORD_IS_GROUP)   { //group colapsed
      int m;
      for (m=j+1;(m<MAX_RECORDS)&&(rc[m].ids.oxFF==-1)/*&&((rc[j].recId&mask)==mask)*/;m++);      

        return GetNextIdMask(m,mask);
        
    }else
    if ((rc[j].recId&RECORD_GROUP_EXPAND)==RECORD_GROUP_EXPAND)   { //group expand
        return GetNextIdMask(j+1,mask);
      
    }else
    if ((rc[j].recId&RECORD_IN_GROUP)==RECORD_IN_GROUP)   { //in group element
        return GetNextIdMask(j+1,mask);
    }else
  
  {
    //simple record
        return GetNextIdMask(j+1,mask);
    }
  }
  return -1;
}
int FindRecordIdByMenuId(int num, int mask){

  short ct=GetNextIdMask(0,mask);
  for (int j=0;(ct!=-1)&&(j<num);j++){
    ct=GetNextId(ct,mask);
  }
  return rc[ct].recId;
};

int FindIdByMenuId(int num, int mask){

  short ct=GetNextIdMask(0,mask);
  for (int j=0;(ct!=-1)&&(j<num);j++){
    ct=GetNextId(ct,mask);
  }
  return ct;
};


int CountRecord(void ){
    short ct=GetNextIdMask(0,mask);;
    int j=0;
    
  for ( j=0;(ct!=-1)&&(j<MAX_RECORDS);j++){

    ct=GetNextId(ct,mask);

  }

  return j;

};
int FindContactByContact(CContact *req){
    short ct=GetNextIdMask(0,mask);;
    int j=0;
  for ( j=0;(ct!=-1)&&(j<MAX_RECORDS)&&(rc[ct].recId&0x1ff)!=(req->recId&0x1ff);j++){
    ct=GetNextId(ct,mask);
  }
  return j;
  
}

CContact *GetContactByItem(int i){
  int id=FindRecordIdByMenuId(i,mask);
  char tmp[8];
  if (GetNumberByRecId(id&0x1ff,tmp)){
    return &cache[GetCacheRecordById(id)];
  }
  return NULL;
  
}
int FindIndexByRecId(int rid){
//   short ct=GetNextIdMask(0,mask);;
   int j=0;
  for ( j=0;(j<MAX_RECORDS)&&(rc[j].recId&0x1ff)!=(rid&0x1ff);j++);

  return j;
 
}
int GetCallsCount(int gid){
  short ct= FindIndexByRecId(gid);
  if (ct!=-1){
    int m;
   for ( m=ct+1;(m<MAX_RECORDS)&&(rc[m].ids.oxFF==-1)/*&&((rc[j].recId&mask)==mask)*/;m++);      
    return m-ct;
  }
  return 0;

};
