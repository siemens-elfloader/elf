int Connect();
void Close();


#define SERVERADDR "login.icq.com"
#define PORT 5190

SOCKET sock;
sockaddr_in dest_addr;
HOSTENT    *hst;