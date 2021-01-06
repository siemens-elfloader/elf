

typedef struct
{
	void *next;
	unsigned int id;
}SGUI_ID;



void pushGS(void *dlg_csm, unsigned int id);
void popGS(void *dlg_csm);
void freeAllGS(void *dlg_csm);
int IsGuiExist(CSM_RAM *csm, GUI *gui);


