void KillViewUrl(void);
char *globalstr(const char *s);
int ReadUrlFile(char *url_file);

typedef struct
{
  CSM_RAM csm;
  int view_id;
  int Text_out_Editor;
  int sel_bmk;
  int main_menu_id;
}MAIN_CSM;

enum I_INPUTMODE {MODE_FILE, MODE_URL};

void FreeRawText(VIEWDATA *vd);

