//---------------------------------------------------------------------------

#include "winsock2.h"
#include "stdio.h"
#include "time.h"
#include "md5.h"

#pragma hdrstop

#define mfree free

extern const char USERNAME[];
extern const char PASSWORD[];

SOCKET sock;
WSAEVENT we;
struct sockaddr_in hadr;
struct hostent * he;
/*char hostname[256];
char filename[256];
char diskfilename[256];
char newurl[1024];


DWORD timeout;

FILE *f;*/


//------------------------------------------------
//Used on Submit
char *password=NULL;
char *sessionkey=NULL;
char *submiturl=NULL;
char *songlist=NULL;
char *posturl=NULL;
char *submhost=NULL;
int songnum=0;
//-------------------------------------------------
char BS[4096];

int sck;

int fmstate;
//---------------------------------------------------------------------------
char *i2a(int value, int base)
{
	enum { kMaxDigits = 35 };
	char *buf=malloc(kMaxDigits);
  int i=0;
  int j;
	int quotient;
  memset(buf,0,kMaxDigits);
	if (base < 2 || base > 16) return buf;
	if ( value < 0 && base == 10)
  {
   buf[i++]= '-';
   value=-value;
  }
  j=i;
	quotient = value;
	do
  {
		buf[i++] = "0123456789abcdef"[ quotient % base ];
		quotient /= base;
	} while ( quotient );
  while(j<i)
  {
    int c=buf[j];
    buf[j++]=buf[--i];
    buf[i]=c;
  }
	return buf;
}

char *globalstr(const char *s)
{
  char *r=malloc(strlen(s)+1);
  strcpy(r,s);
  return r;
}

char *urlescape(const unsigned char *source)
{
	const char * h = "0123456789abcdef";
	char *out=malloc(strlen(source)*3+1);
	int c;
  int i=0;
	while((c =*source++)!=0)
  {
		if ('a' <= c && c <= 'z'
		|| 'A' <= c && c <= 'Z'
		|| '0' <= c && c <= '9'
		|| c == '-' || c == '_' || c == '.')
			out[i++]= c;
//		else if( c == ' ' )
//			out[i++]= '+';
		else {
			out[i++]= '%';
			out[i++]= h[c >> 4];
			out[i++]= h[c & 0x0f];
		}
	}
  out[i]=0;
	return out;
}

char *genSessionKey(const char *challenge)
{
  md5_state_t md5state;
	unsigned char md5pword[16];
	char *clear=malloc(strlen(password)+strlen(challenge)+1);
	char *key=malloc(33);
  int j;
  strcpy(clear,password);
  strcat(clear,challenge);
	md5_init(&md5state);
	md5_append(&md5state, (unsigned const char *)clear, (int)strlen(clear));
	md5_finish(&md5state, md5pword);
  memset(key,0,33);
	for (j = 0;j < 16;j++) {
		char a[3];
		sprintf(a, "%02x", md5pword[j]);
		key[2*j] = a[0];
		key[2*j+1] = a[1];
	}
  mfree(clear);
  return key;
}

char *setPassword(const char *pass, const char *challenge)
{
  char *tmp;
  int j;
	md5_state_t md5state;
	unsigned char md5pword[16];
	md5_init(&md5state);
	md5_append(&md5state, (unsigned const char *)pass, (int)strlen(pass));
	md5_finish(&md5state, md5pword);
	if (!strlen(pass)) return NULL;
	tmp=malloc(33);
  memset(tmp,0,33);
	for (j = 0;j < 16;j++)
  {
		char a[3];
		sprintf(a, "%02x", md5pword[j]);
		tmp[2*j] = a[0];
		tmp[2*j+1] = a[1];
	}
	password = tmp;
	return genSessionKey(challenge);
}

/*int sockputs(char *s, char echof)
{
 if (echof) printf(s);
 if (send(sck,s,strlen(s),0)==SOCKET_ERROR)
 {
  printf(" send error %d\n",WSAGetLastError());
  return(1);
 }
 return(0);
}*/

void sendHandShake(void)
{
 char *hst=BS;
 char *s;
 char *authdata;
 char *timstmp;
 int i;
 time_t now;
 time(&now);
 timstmp=i2a(now,10);
 authdata=setPassword(PASSWORD,timstmp);
 hst[0]=0;
 strcat(hst,"GET /?hs=true&p=1.2&c=lmd&v=1.1&u=");
 s=urlescape(USERNAME);
 strcat(hst,s);
 mfree(s);
 strcat(hst,"&t=");
 strcat(hst,timstmp);
 strcat(hst,"&a=");
 strcat(hst,authdata);
 strcat(hst,"\r\nHost: post.audioscrobbler.com\r\n\r\n");
 send(sck,hst,strlen(hst),0);
 mfree(authdata);
 mfree(timstmp);
}

void recvHandShake(void)
{
 char *s=BS;
 const char seps[] = " \n\r";
 char *response;
 int i;
 memset(s,0,4096);
 i=recv(sck,s,4096,0);
 closesocket(sck);
 printf("recv result: %d\n%s",i,s);
 if (i<=0)
 {
   fmstate=0;
   return;
 }
 response=strtok(s, seps);
 if (stricmp("OK",response)!=0)
 {
   printf("Error: %s",response);
   fmstate=0;
   return;
 }
 sessionkey=globalstr(strtok(NULL,seps));
 strtok(NULL,seps); //NP url
 submiturl=globalstr(strtok(NULL,seps));
}

void addSong(
  const char *artist,
  const char *track,
  time_t splay_time,
  char source,
  char rating,
  int length,
  const char *album
  )
{
  char *s;
//  char sc[]=" ";
  char *num=i2a(songnum,10);
  int i;
//	struct tm *today = gmtime(&splay_time);
	char ti[20];
  if (!songlist)
  {
    songlist=malloc(1024);
    songlist[0]=0;
  }
  else
    songlist=realloc(songlist,strlen(songlist)+1024);
  s=urlescape(artist);
  strcat(songlist,"&a[");strcat(songlist,num);strcat(songlist,"]=");strcat(songlist,s);mfree(s);
  s=urlescape(album);
  strcat(songlist,"&b[");strcat(songlist,num);strcat(songlist,"]=");strcat(songlist,s);mfree(s);
  s=urlescape(track);
  strcat(songlist,"&t[");strcat(songlist,num);strcat(songlist,"]=");strcat(songlist,s);mfree(s);
  //
  //	strftime(ti, sizeof(ti), "%Y-%m-%d %H:%M:%S", today);
  sprintf(ti,"%u",splay_time);
  s=urlescape(ti);
  strcat(songlist,"&i[");strcat(songlist,num);strcat(songlist,"]=");strcat(songlist,s);mfree(s);
  s=i2a(length,10);
  strcat(songlist,"&o[");strcat(songlist,num);strcat(songlist,"]=P");
  strcat(songlist,"&r[");strcat(songlist,num);strcat(songlist,"]=");
  strcat(songlist,"&l[");strcat(songlist,num);strcat(songlist,"]=");strcat(songlist,s);mfree(s);
  strcat(songlist,"&n[");strcat(songlist,num);strcat(songlist,"]=");
  strcat(songlist,"&m[");strcat(songlist,num);strcat(songlist,"]=");
  mfree(num);
  songnum++;
}

void sendSubmit(void)
{
  char *ss;
  char *s;
  char *s2;
  if (!songnum)
  {
    fmstate=0;
    closesocket(sck);
    return;
  }
//  setPassword(PASSWORD);
  ss=malloc(256);ss[0]=0;
//  s=urlescape(USERNAME);
//  strcat(ss,"u=");
//  strcat(ss,s);mfree(s);
  strcat(ss,"s=");
  strcat(ss,sessionkey);
  ss=realloc(ss,strlen(ss)+strlen(songlist)+1);
  strcat(ss,songlist);
  s=malloc(strlen(ss)+strlen(posturl)+1024);
  strcpy(s,"POST /");
  strcat(s,posturl);
  strcat(s," HTTP/1.1\r\nHost: ");
  strcat(s,submhost);
  strcat(s,"\r\nContent-Length: ");
  s2=i2a(strlen(ss),10);
  strcat(s,s2);mfree(s2);
  strcat(s,"\r\nUser-Agent: lmd v1.1");
  strcat(s,"\r\nContent-type: application/x-www-form-urlencoded\r\nAccept: */*\r\nConnection: Close\r\n\r\n");
  strcat(s,ss);
  printf("Submit:\n%s",s);
  send(sck,s,strlen(s),0);
}

void recvSubmit(void)
{
 char *s=BS;
 char *response;
 int i;
 memset(s,0,4096);
 i=recv(sck,s,4096,0);
 closesocket(sck);
 printf("recv result: %d\n%s",i,s);
}

void prepareSubmit(void)
{
 int err;
 unsigned char ip1,ip2,ip3,ip4;
 char *s=globalstr(submiturl);
 char *port;

 if (strncmp(s,"http://",7)==0) s+=7;
 submhost=globalstr(strtok(s,":"));
 port=strtok(NULL,"/");
 posturl=strtok(NULL,""); //Without slash
 he=gethostbyname(submhost);
 if (he==NULL)
 {
  printf("Can't resolve host information!\n");
  fmstate=0;
  return;
 }
 printf("-------- Host information ---------\n");
 printf("Official name of host: %s\n",he->h_name);
 ip1=he->h_addr_list[0][0];
 ip2=he->h_addr_list[0][1];
 ip3=he->h_addr_list[0][2];
 ip4=he->h_addr_list[0][3];
 printf("IP address: %d.%d.%d.%d\n",ip1,ip2,ip3,ip4);
 printf("------------------------------------\n");
 printf("Try to create socket... ");
 if ((sck=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
 {
  printf("socket error %d\n",WSAGetLastError());
  fmstate=0;
  return;
 }
 printf("Ok\n");
 hadr.sin_family=AF_INET;
 hadr.sin_port=htons(strtoul(port,NULL,10));
 hadr.sin_addr.S_un.S_un_b.s_b1=ip1;
 hadr.sin_addr.S_un.S_un_b.s_b2=ip2;
 hadr.sin_addr.S_un.S_un_b.s_b3=ip3;
 hadr.sin_addr.S_un.S_un_b.s_b4=ip4;
 printf("Try to connect... ");
 if (connect(sck,(const struct sockaddr FAR*)&hadr,sizeof(hadr)))
 {
  printf("connect error %d\n",WSAGetLastError());
  fmstate=0;
  return;
 }
 printf("Ok\n");
}

#pragma argsused
int main(int argc, char* argv[])
{
 int err;
 unsigned char ip1,ip2,ip3,ip4;
 WORD wVersionRequested;
 WSADATA wsaData;
 wVersionRequested = MAKEWORD( 1, 0 );
 err = WSAStartup( wVersionRequested, &wsaData );
 if ( err != 0 ) return(0);
 he=gethostbyname("post.audioscrobbler.com");
 if (he==NULL)
 {
  printf("Can't resolve host information!\n");
  return 0;
 }
 printf("-------- Host information ---------\n");
 printf("Official name of host: %s\n",he->h_name);
 ip1=he->h_addr_list[0][0];
 ip2=he->h_addr_list[0][1];
 ip3=he->h_addr_list[0][2];
 ip4=he->h_addr_list[0][3];
 printf("IP address: %d.%d.%d.%d\n",ip1,ip2,ip3,ip4);
 printf("------------------------------------\n");
 printf("Try to create socket... ");
 if ((sck=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
 {
  printf("socket error %d\n",WSAGetLastError());
  return 0;
 }
 printf("Ok\n");
 hadr.sin_family=AF_INET;
 hadr.sin_port=0x5000;
 hadr.sin_addr.S_un.S_un_b.s_b1=ip1;
 hadr.sin_addr.S_un.S_un_b.s_b2=ip2;
 hadr.sin_addr.S_un.S_un_b.s_b3=ip3;
 hadr.sin_addr.S_un.S_un_b.s_b4=ip4;
 printf("Try to connect... ");
 if (connect(sck,(const struct sockaddr FAR*)&hadr,sizeof(hadr)))
 {
  printf("connect error %d\n",WSAGetLastError());
  return 0;
 }
 printf("Ok\n");
 fmstate=3;
 sendHandShake();
 fmstate=4;
 recvHandShake();
 if (!fmstate) return 0;
 fmstate=5;
 {
  time_t now;
  time(&now);
  now-=300;
  addSong(
//  "Raznye ludy",
   "Р Р°Р·РЅС‹Рµ Р»СЋРґРё",
//  "Разные люди",
//  "Rabochij rock-n-roll",
   "Р Р°Р±РѕС‡РёР№ СЂРѕРє-РЅ-СЂРѕР»Р»",
//  "Рабочий рок-н-ролл",
   now,
   'P',
   'L',
   4*60+56,
//   "Akustika"
   "РђРєСѓСЃС‚РёРєР°"
//  "Акустика"
   );
 }
 prepareSubmit();
 if (!fmstate) return 0;
 fmstate=6;
 sendSubmit();
 if (!fmstate) return 0;
 recvSubmit();
 return 0;
}
//---------------------------------------------------------------------------
