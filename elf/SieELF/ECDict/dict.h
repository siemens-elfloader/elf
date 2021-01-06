
#ifndef _DICT_H_
#define _DICT_H_

void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode);

void LoadDictIndex();
void UnloadDictIndex();

void OpenDict();
void CloseDict();

int lookup(char* word);
void construct_entry_text(WSHDR* word_entry_text, char* word, int show_word, int show_phonetic, int show_meaning);


#endif
