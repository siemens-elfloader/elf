//tbase.h - Работа с базой трансляции для применения виртуальных патчей
//(C)Dimadze
//v1.2

extern void EnableINT(int fi);
extern int  DisableINT();
extern void CleanCache(void *vaddress);
extern void CleanTLB();
extern int *GetTBaseAddr();
extern void UnLockAccess();


//Получение значения байта из адреса
char GetByteFromAddress(void *addr);
//Виртуальная запись байта по адресу (Применение патча)
int  ApplyPatch(void *addr, char new_byte);
//Виртуальная запись байта по адресу (Отмена патча)
int  UndoPatch(void *addr, char old_byte);

/* При отмене всех патчей было решено */
/* Разбивку секций оставить */
/* Хотя для очистки flash страниц есть все данные */
/* Участки RAM, которые отводится под flash страницы */
/* Не имеют доступа для записи, только чтение */
/* Чтобы в них писать надо разблокировывать доступ */

