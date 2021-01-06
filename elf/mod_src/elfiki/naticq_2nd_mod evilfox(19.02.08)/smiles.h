#pragma pack(1)
typedef struct
{
  void *next;
  unsigned int key; //Для быстрой проверки
  unsigned int mask;
  char text[1];
}STXT_SMILES;
#pragma pack()

typedef struct
{
  void *next;
  unsigned int uni_smile;
  STXT_SMILES *lines; //Список строк
  STXT_SMILES *botlines;
}S_SMILES;

void FreeSmiles(void);
void InitSmiles(void);
void ProcessNextSmile(void);

void FreeXStatusesImg(void);
void InitXStatusesImg(void);
void ProcessNextXStatImg(void);

S_SMILES *FindSmileById(int n);
S_SMILES *FindSmileByUni(int wchar);






