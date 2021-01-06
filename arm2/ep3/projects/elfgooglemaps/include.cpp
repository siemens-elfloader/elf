#include "include.h"


//connect
int mode=0,
    sock=-1,
    connect_state=0,
    pbuf=0,
    zoom=0,
    cur_x=cub*2,
    cur_y=cub*3,
    all_traf=0,
    timer=50,
    mapi=0,
    mapj=0,
    Type=DOWN;//что грузить


char *buf=0;
IMGHDR *map[MAP_X][MAP_Y] = {0};
int size_image=0;
GBSTMR tmr;
char filename[128];
RAMNET *ramnet;
double latitude=0,longitude=0;//широта/долгота
char req_buf[512];

char *maptype[5]={"roadmap","mobile","satellite", "terrain", "hybrid"};
char *clr[3]={"red","green","blue"};
char *format[3]={"png","jpg","gif"};
char *type[3]={"text","image","partimage"};

double my_latitude=0,my_longitude=0;//моя позиция

int istate=0;
char *resource[3]={"img\\loading_tile.png","img\\blank_tile.png","language\\language.lng"};
char elf_path[128];
char *tag=0;
const char fname[128] = "4:\\Maps\\";
const char HOST[128] = "213.138.73.90";
const unsigned int PORT = 80;
const int Zoom = 13;
const int map_type = 1;


