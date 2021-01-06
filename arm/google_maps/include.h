#include "..\inc\swilib.h"
#include <math.h>

#ifdef ELKA
#define FONT 9
#define cub 80
#define W 240
#define H 320
#else
#define W 132
#define H 176
#define FONT 7
#define cub 44
#endif


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define BOTTOM 0

#define MAP_X W/cub
#define MAP_Y H/cub

#define BUFFSIZE 2048
//connect
extern int sock,connect_state;
extern char *buf;
extern int pbuf;

extern char filename[128];
void save_image_in_cache(int n);
void DrwImg(IMGHDR *img, int x, int y);

extern GBSTMR tmr;
extern int cur_x,cur_y;

extern void send_req(void),get_answer(void),end_socket(void), CreateRequest();

extern const char fname[128],name[2];
extern const int frmt,map_type;
extern  int zoom;
extern const int Zoom;
extern int mode;
char *valuetag(char *src,char *dst, int maxlen);
char * findtag(char *src, char *tag);

extern double latitude,longitude;
double str_to_double(const char *str);
double LToX(double x);
double LToY(double y);
double XToL(double x);
double YToL(double x);

extern char *tag;
extern IMGHDR *map[MAP_X][MAP_Y];
extern int size_image;
extern int mapi,mapj;

extern RAMNET *ramnet;

extern int Type;
extern char req_buf[512];
extern char *maptype[5];

extern char *format[3];
extern char *type[3];
void free_imghdr(IMGHDR *i);
extern double my_latitude,my_longitude;

void c();
extern int all_traf;
void create_connect();
extern int timer;
extern const char HOST[128];
extern const unsigned int PORT;
extern FSTATS fs;
extern void LoadCache();
extern int istate;
#define NO_TILE 1
#define LOAD_TILE 0
#define LANG 2
extern char *resource[3];
void lgpInitLangPack(void);
void search_cache(void);
extern char elf_path[128];
