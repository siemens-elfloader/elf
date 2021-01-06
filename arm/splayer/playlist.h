#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

#define TClines 512
#define TCPL 5             // Количество пл   AAA

// Оказалось его перед закрытием еще и останавливать надо... А то такое начинается! :D  AAA
void DisableScroll(void);

// Поднимаем громкость
void VolumeUp();

// Опускаем громкость
void VolumeDown();

// Громкость на ноль
void ToggleVolume();

// Случайный трек
void RandTrack();

//Повторяющийся трек  AAA
void RepeatTrack();

// Для plamode==1  AAA
void NextTrackX();

// Следующий трек пл  AAA
void NextTrack();

// Предыдущий трек пл  AAA
void PreviousTrack();

// Остановить перемотку :) - Vedan
void StopRewind();

// Перемотка - Vedan   // Оптимизировал   AAA
void StartRewind();

// Пауза/Воспроизведение
void TogglePlayback();

// Останавливаем проигрывание
void StopAllPlayback();

// Постановка в очередь   AAA
void SetNextPlayed();

// Воспроизведение поставленного в очередь   AAA
void PlaySetTrack();

// Сходим с ума по гламуру :)   AAA
void OpenAnim(void);

// Переключаем пл   AAA
void MovePL();

// Потребовалось для исправления глюка AAA
void CTtoFirst();

// Сделал в две для удобства AAA
void PTtoFirst();

//Пробуем листание вниз AAA
void CTDown();

//Пробуем листание вверх AAA
void CTUp();

// Быстрое листание AAA
void CTSpeed(void);

//Листание шопестец вниз AAA
void CTDownSix();

//Листание шопестец вверх AAA
void CTUpSix();

//Воспроизвести AAA
void PlayTrackUnderC();

// Выдаем текущий статус
char GetPlayingStatus();

// Устанавливаем статус
void SetPlayingStatus(char PS);

// Громкость
unsigned short GetVolLevel();

// Установим указатель на проигрываемую мелодию...
void SetPHandle(short ph);

// Возвращает кол-во треков в загруженном пл
int GetTC();

// Выделим память   AAA
void Memory();

// Сохраняем пл!   AAA
void SavePlaylist(char *fn);

// Добавляем строку в пл   AAA
void PastLine(WSHDR *p, unsigned short i);

// Копируем строку в пл   AAA
void CopyLine(WSHDR *p);

// Удаляем строку из пл   AAA
void DeleteLine();

// Перемещаем строку в пл вверх   AAA
void MoveLineUp();

// Перемещаем строку в пл вниз   AAA
void MoveLineDown();

// Перемещаем строку в следующий пл   AAA
void MoveLineRight();

// Перемещаем строку в предыдущий пл   AAA
void MoveLineLeft();

// Возвращает имя файла по полному пути...
void FullpathToFilename(WSHDR * fnamews, WSHDR * wsFName);

// Убираем странный символ (всвязи с переходом на WSHDR)   AAA
void fix(char* p);

// Возвращется трек по номеру в пл
WSHDR * GetCurrentTrack();

// Возвращется играющий трек по номеру в пл
WSHDR * GetPlayedTrack();

// Чистим массив   AAA
//void NULLchar(char* p, unsigned int imax);

// Перерисовка
void PL_Redraw(WSHDR** mass, int* CurLine, int* MarkLine, int* MarkLines, unsigned int* AllLines, int CurList, int MarkList);

// Полоса прокрутки   AAA
void BandRoll(int CurLine, int AllLines);

// Загружаем пл!
int LoadPlaylist(const char * fn);

// Для загрузки пл из главного модуля
void LoadingPlaylist(const char * fn);

// Для еще одной фичи   AAA
void LoadPlaylists(const char* path);

// Чистим пл   AAA
void CleanPlaylist();

// Эта зверюга замочит что угодно!   AAA
void Disable_An(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4, unsigned short i5, unsigned short i6/*, unsigned short i7*/);

// Утечка памяти в самом деле достала...   AAA
void MemoryFree();

//void ascii2ws(char *s, WSHDR *ws);
#endif
