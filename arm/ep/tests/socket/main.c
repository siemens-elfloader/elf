
#include <swilib.h>
#include <usart.h>
#include <arpa/inet.h>
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/waitcondition.h>
#include <spl/processbridge.h>
#include <fcntl.h>
#include <stdio.h>
#include <spl/thread.h>
#include <spl/socket.h>
#include <spl/fs.h>

FILE *debug_fd = 0;
#undef printf
#define printf(fmt, ...) fprintf(debug_fd, fmt, ##__VA_ARGS__)


int stream(void *d)
{
    int sock;

    struct in_addr adr;
    adr.s_addr = gethostbyname("team-sc.ru");
    if(adr.s_addr == (unsigned int)-1) {
        printf("Can`t resolve ip\n");
        return 0;
    }

    printf("Connecting to team-sc.ru(%s)\n", inet_ntoa(adr));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("Can`t create socket\n");
        return 0;
    }

    printf("socket: %d\n", sock);

    struct sockaddr_in sa;

    sa.sin_family = AF_INET;
    sa.sin_addr = adr;
    sa.sin_port = htons(80);

    printf("Connecting...\n");
    if( connect(sock, (struct sockaddr*)&sa, sizeof sa) ){
        printf("Can`t connect\n");
        return 0;
    }

    printf("Connected\n");


    char data[1024*8] = "GET /files/gcc_462_swi_call_siemens2patch_129.zip HTTP/1.0\r\n"
                          "Host: team-sc.ru\r\n"
                          "User-Agent: Ololo\r\n"
                          "Connection: close\r\n\r\n";

    if( write(sock, data, strlen(data)) < 1 ) {
        printf("Write failed\n");
        goto err;
    }


    int fd = open((char*)d, O_CREAT | O_WRONLY | O_TRUNC);
    int sz, first = 0;
    while( (sz = read(sock, data, 2*1024)) > 0)
    {
        data[sz] = 0;
        printf("%d: Readed: %d\n", sock, sz);

        if(!first) {

            const char *d = strstr(data, "\r\n\r\n");
            if(d){
                d += 4;
                const char *end = data+sz;
                if(d < end)
                {
                    write(fd, d, end-d);
                }

                first = 1;
            }


            continue;
        }

        if(fd != -1)
            write(fd, data, sz);
    }

    close(fd);

err:
    printf("\n");
    if( close(sock) ){
        printf("Can`t close socket\n");
    }

    return 0;
}



int main()
{
    //initUsart();
    debug_fd = fopen("4:\\elf\\coretest\\debug.txt", "w+");
    setvbuf(debug_fd, 0, _IOFBF, 56);

    printf(" [+] main: pid: %d\n", getpid());
    int tids[15];
    char names[15][128];


    for(int i=0; i<5; ++i) {
        sprintf(names[i], "4:\\elf\\coretest\\patch_129_s%d.zip", i);
        tids[i] = createThread(95, stream, names[i], 1);
    }


    for(int i=0; i<5; ++i) {
        waitForThreadFinished(tids[i], 0);
    }


    printf("Ram: %d\n", GetFreeRamAvail());

    SetVibration(40);
    NU_Sleep(40);
    SetVibration(0);

    fclose(debug_fd);
    return 0;
}





