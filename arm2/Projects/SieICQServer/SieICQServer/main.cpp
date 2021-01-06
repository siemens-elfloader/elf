#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>

#pragma comment(lib, "WSock32.lib")
#pragma comment(lib, "ws2_32")
#pragma comment (lib, "mswsock.lib")

#include "connect.h"
#include "login.h"




int main()
{
if(Connect()==1)
   Login();

Close();
_getch();
return 0;
}