#include "../include.h"
#include <sys/socket.h>

#include "internet.h"
#include "../language/language.h"
#include "utils.h"
#include "../map/map.h"


void create_connect()
{
    SOCK_ADDR sa;
    connect_state=0;
    sock = _socket(AF_UNIX,SOCK_STREAM,0);
    if (sock!=-1)
    {
        sa.family=AF_UNIX;
        sa.port=htons(PORT);
        sa.ip=gethostname(HOST);
        if(_connect(sock,&sa,sizeof(sa))!=-1)
        {
            if(istate==1)istate=2;
            connect_state=1;
        }
        else
        {
            closesocket(sock);
            sock=-1;
        }
    }




}


void send_req()
{
    if(!buf)buf = new char(BUFFSIZE);
    mode=1;
    create_request();

    all_traf+=_send(sock,req_buf,strlen(req_buf),0);
    connect_state=2;

}

void end_socket()
{
    if (sock>=0)
    {
        //shutdown(sock,2);
        closesocket(sock);
        connect_state=0;
        SUBPROC((void *)create_connect);
    }
}





void get_answer()
{

    int j=0;
    int header_size=0,image_size=0;
    pbuf=0;
    while((j=_recv(sock,buf+pbuf,BUFFSIZE,0))>0)//получаем весь ответ
    {
        all_traf+=j;
        pbuf+=j;
        buf[pbuf] = 0;
        buf=(char*)realloc(buf,pbuf+BUFFSIZE);
    }

        /*while( (j = read(sock, buf+pbuf, BUFFSIZE)) > 0)
    {
        pbuf+=j;
        buf[pbuf] = 0;
        buf=(char*)realloc(buf,pbuf+BUFFSIZE);

    }*/
    buf[pbuf]=0;

    if(header_size==0||image_size==0)
    {
        if(strstr(buf,"\r\n\r\n"))
        {
            if(header_size==0)header_size=get_headersize(buf);
            if(image_size==0&&(tag=findtag(buf,"Content-Length:")))
            {

                valuetag(tag, filename, sizeof(filename)-1);
                image_size=(int)str_to_double(filename);
            }
        }
    }

    if(pbuf>=(image_size+header_size))
    {
        buf[pbuf]=0;
        save_image_in_cache(0);

    }
}


void create_request()
{

    if(!latitude||!longitude)
    {
        ramnet=RamNet();
        char *p=((char*)ramnet)-11;
        char cc1=*p;
        char cc2=*(p+1);
        char nc=*(p+2);
        sprintf(req_buf,"GET /maps/index.php?cell=%d&op=%d&cc=%d&lac=%d",ramnet[0].ci,(nc&0x0F)*10+(nc>>4),(cc1&0x0F)*100+(cc1>>4)*10+(cc2&0x0F),ramnet[0].lac);

    }
    else sprintf(req_buf ,"GET /maps/index.php?lat=%f&lon=%f",latitude,longitude);

    if(my_latitude&&my_longitude)sprintf(req_buf ,"%s&my_latitude=%f&my_longitude=%f",req_buf,my_latitude,my_longitude);

    sprintf(req_buf ,"%s&zoom=%d&t=%s&frmt=%s&szx=%d&szy=%d&q=%s&imgx=%d&imgy=%d&cub=%d&color=blue&hl=%s"
            " HTTP/1.1\r\nHost: gps.st-hunter.ru\r\n\r\n", req_buf, zoom, maptype[map_type],
                                                           format[0], ScreenW(), ScreenH(),
                                                           type[2], mapi, mapj, cub, lgpData[LGP_LangCode].c_str());
}

void c()
{
    if(connect_state==0)
    {
        SUBPROC((void *)create_connect);
        return;
    }
    mode=1;
    sprintf(filename,"%scache%f_%f\\map_%d_%d_%d_%d.png",elf_path,longitude,latitude,mapi,mapj,zoom,map_type);
    if(is_file_exists(filename))save_image_in_cache(1);//SUBPROC((void*)save_image_in_cache,1);
    else

        SUBPROC((void*)send_req);
}
