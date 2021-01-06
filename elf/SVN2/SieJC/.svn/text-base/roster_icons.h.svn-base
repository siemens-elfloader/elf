/*
    SieNatJabber Project
    Функции отрисовки иконок ростера
*/


// рисуем картинку с номером по заданным координатам
void Roster_DrawIcon(unsigned short x, unsigned short y, unsigned int img_num);
// Просто "обертки" к стандартным фунциям
int Roster_getIconWidth(char *path_to_pic);
int Roster_getIconHeight(char *path_to_pic);

// получаем номер картинки
#ifdef USE_PNG_EXT
void Roster_getIcon(char* path_to_pic, CLIST* ClEx, TRESOURCE* resEx);
#else
int Roster_getIcon(CLIST* ClEx, TRESOURCE* resEx);
#endif
 //заменяем картинки на png
  void Roster_fillIcons();

//вернет номер картинки по статусу
#ifdef USE_PNG_EXT
char* Roster_getIconByStatus(char* path_to_pic, char status);
#else
  int Roster_getIconByStatus(char status);
#endif
