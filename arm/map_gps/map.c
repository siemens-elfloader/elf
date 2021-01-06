#include "..\inc\swilib.h"



//zoom 0-19
//sizex,sizey 512x512
void CreateReq(char *req,char *maptype,char *LAT,char*LON,int zoom,int sizex,int sizey)
 {
   sprintf(req,"http://maps.google.com/staticmap?maptype=%s&center=%s,%s&zoom=%d&size=%dx%d",
   maptype,LON,LAT,zoom,sizex,sizey);
 }

