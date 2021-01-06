#include "..\..\inc\swilib.h"
#include "../draw/image.h"
#include "../include.h"
#include "map.h"

int mktree(char* path)
{
	if (isdir(path, 0)) return 1;
	int len = strlen(path);
	char c;
	char buf[256];

	for(int ii=0;ii<len;ii++)
	{
		c = path[ii];
		if (c=='\\')
		{
			buf[ii]=0;
			mkdir(buf, 0);
		}  
		buf[ii]=c;
	}
	return mkdir(path, 0);
}



void save_image_in_cache(int n)
{
   int size_image=0;
    int f=0;
   if(n==1)goto a;

   if(tag=findtag(buf,"Content-Lat:"))
  {
    valuetag(tag, filename, sizeof(filename)-1);
    latitude=str_to_double(filename);
  }

  if(tag=findtag(buf,"Content-Lon:"))
  {
    valuetag(tag, filename, sizeof(filename)-1);
    longitude=str_to_double(filename);  
  }

  if(tag=findtag(buf,"Content-Length:"))
  {
    valuetag(tag, filename, sizeof(filename)-1);
    size_image=(int)str_to_double(filename);
  }

  sprintf(filename,"%scache%f_%f\\",elf_path,longitude,latitude);

  mktree(filename);

  sprintf(filename,"%smap_%d_%d_%d_%d.png",filename,mapi,mapj,zoom,map_type);

  f = fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);

  fwrite(f,buf+(pbuf-size_image),size_image,0);

  fclose(f,0);



  if(buf)mfree(buf);

  buf=0;

  pbuf=0;
  
a:
  if(my_latitude==0)my_latitude=latitude;
  if(my_longitude==0)my_longitude=longitude;
  FreeImg(map[mapi][mapj]);
  sprintf(filename,"%scache%f_%f\\map_%d_%d_%d_%d.png",elf_path,longitude,latitude,mapi,mapj,zoom,map_type);
  map[mapi][mapj]=CreateIMGHDRFromPng(filename);
  
  if(mapi==MAP_X-1&&mapj==MAP_Y-1)goto end;
  
  switch(Type)
 {
case RIGHT:
   if(mapj==MAP_Y-1)
 {
   if(mapi<MAP_X-1)mapi++;
   else goto end;
   mapj=0;
 }
 else mapj++;   
break;
         
case LEFT:
  if(mapj==MAP_Y-1)goto end;
  else mapj++;
break;
  
case UP:case DOWN:
    if(mapi>=MAP_X-1)
    {
      goto end;
    }
    else mapi++;
break;
}

  FreeImg(map[mapi][mapj]);

  sprintf(filename,"%s%s",elf_path,resource[LOAD_TILE]);
 
  map[mapi][mapj]=CreateIMGHDRFromPng(filename);

  c();
  return;
end:
  mapi=0;
  mapj=0;
  mode=0;
}

//ported from .java


double round(double num)
{
         double flr = (int)num;

	if(num - flr >= 0.5)
		return ceil(num);
	else
		return flr;
}
double LToX(double x)
{
	return round(offset + radius * x * PI / 180);
}
 
double LToY(double y)
{
	return round(
		offset - radius * 
		log(
			
			(1 + sin(y * PI / 180))
			/
			(1 - sin(y * PI / 180))
			
		) / 2);
} 
 
double XToL(double x)
{
	return ((round(x) - offset) / radius) * 180 / PI;
}
 
double YToL(double y)
{
	return (PI / 2 - 2 * atan(exp((round(y)-offset)/radius))) * 180 / PI;
}
