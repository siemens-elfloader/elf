#include "../../inc/swilib.h"
#include "../plglib.h"


#define IPC_DT_NAME "_DeskTop"

#define IPC_NPLG	1


TDate date;
TTime time;

extern void kill_data(void *p, void (*func_p)(void *));
static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static const char *day[]={"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"},
	*month[]={"Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентября", "Октября", "Ноября", "Декабря"};


//===============================================================================================

	extern DT_ICON my_icon;
void dr_my_icon()
{
	
	WSHDR *ws=AllocWS(256);
	
	GetDateTime(&date, &time);
	
	wsprintf(ws, "%02d/%02d/%d", date.day,date.month,date.year);
	/* if((cur.x>=p.x)&&(cur.x<=p.x2)&&(cur.y>=p.y)&&(cur.y<=p.y2))
	{
		DrawString(ws,p.x,p.y+6,p.x2,p.y2,FONT_SMALL,2,red,NULL); */
	/* }
	else  */DrawString(ws,my_icon.p.x,my_icon.p.y+6,my_icon.p.x2,my_icon.p.y2,FONT_SMALL,2,white,NULL);
	
	FreeWS(ws);
}



void inf_clock_icon()
{
	sprintf(my_icon.inf, "%s\n%s\n%d %s\n%d%s", my_icon.nm, day[GetWeek(&date)], date.day, month[date.month-1], date.year, "г." );
}

int Enter_my_icon()
{
	return 0;
	//gui();
	//ShowWMSG(0, "проверка вывода сообщения", FONT_SMALL, GetPaletteAdrByColorIndex(3), GetPaletteAdrByColorIndex(7), 1);
}

static DT_ICON my_icon={
	NULL,
	{10,90,100,200},
	0,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_my_icon,
	Enter_my_icon,
	inf_clock_icon
};

static IPC_REQ gipc;
const char ipc_my_name[]="Plugin";
const char ipc_dt_name[]=IPC_DT_NAME;

int main(char *exename, char *fname)
{
	//PLG_P *TP=(PLG_P*)fname;
	//if((TP->sig[0]=='P')&&(TP->sig[1]=='L')&&(TP->sig[2]=='U')&&(TP->sig[3]=='G'))
	if((int)fname>=0xa0000000)
	{
	DT_ICON *TI=(DT_ICON*)fname;
	DT_ICON *TTI=(DT_ICON*)TI->next;
		my_icon.d=0;
		my_icon.next=TTI->next;
		my_icon.p=TTI->p;
		my_icon.nm=TTI->nm;
		my_icon.fl=TTI->fl;
		my_icon.img=TTI->img;
		// TI->p=tti->p;
		// TI->nm=tti->nm;
		// TI->fl=tti->fl;
		// TI->img=tti->img;
		//Dt.icon[ti->d]->inf=Dt.icon[Dt.icon_cnt]->inf;
		my_icon.inf=malloc(256);
		zeromem(my_icon.inf, 256);
		TI->next=&my_icon;
		REDRAW();
	}
	else
    SUBPROC((void *)Killer);
	// {
		// my_icon.d=0xFF;
		// gipc.name_to=ipc_dt_name;
		// gipc.name_from=ipc_my_name;
		// gipc.data=&my_icon;
		// GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_NPLG,&gipc);
	// }
  return 0;
}


