



static DrwImage(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

IMGHDR *test,bg,zb;
char path[]="4:\\test";
int main()
{
	char s[128];
	sprintf(s,"%s\\test1.png",path);
	test=CreateIMGHDRFromPngFile(s, 2);   	
	
	sprintf(s,"%s\\bg1.png",path);
	bg=CreateIMGHDRFromPngFile(s, 2);   	
	
	sprintf(s,"%s\\zb1.png",path);
	zb=CreateIMGHDRFromPngFile(s, 2);   	
	
	DrwImage(test,0,0,0,0);
}