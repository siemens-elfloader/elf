#include "..\..\inc\swilib.h"
#include "..\inc\search.h"
#include "..\inc\code.h"
#include "..\inc\buff.h"
#include "..\inc\main.h"

char* searchstr = NULL;
int* next = NULL;
int searchstrlen = 0;

int kmp_init(const char *patn, int len, int *next) {
	int i, j;

	if (!patn || len <= 0 || !next) return 0;
	next[0] = 0;
	for (i = 1, j = 0; i < len; i ++) {
		while (j > 0 && patn[j] != patn[i])
			j = next[j - 1];
		if (patn[j] == patn[i])
			j ++;
		next[i] = j;
	}
	return 1;
}

char* kmp_find(char *text, int text_len, char *patn, int patn_len,
		int *next) {
	int i, j;

	if (!text || text_len <= 0 || !patn || patn_len <= 0 || !next) return NULL;
	for (i = 0, j = 0; i < text_len; i ++) {
		while (j > 0 && text[i] != patn[j])
			j = next[j - 1];
		if (text[i] == patn[j])
			j ++;
		if (j == patn_len)
			return text + i + 1 - patn_len;
	}
	return NULL;
}

void searchForward(void) {
	if (!buffed) return;
	/*
	if (searchresulthead[0].offset + 1 > 0 && 
			searchresulthead[0].offset + 1 < searchresulthead[0].address) {
		searchresulthead[0].offset++;
		curvisrow = searchresulthead[searchresulthead[0].offset].offset;
		if (readStartAdr != bl->address) {
			initBuffer();
			readStartAdr = searchresulthead[searchresulthead[0].offset].address;
			loadBlock();
			createRowIndex();
		}
		for (int i = 0; i < visualRows; i++) {
			if (rowindex[i].end > curvisrow) {
				curvisrow = i;
				break;
			}
		}
	}
	else { //从当前块开始搜索
		int readStartAdr_old = readStartAdr;
		int curvisrow_old = curvisrow;
		int readOffset_old = readOffset;
		int readOffset1_old = readOffset1;
		int visualOffset_old = visualOffset;
		
		char* src = readBuff + rowindex[i].start;
		char* result = strstr(src, searchstr);
		if (!result) {
			setNextBlock();
			loadBlock();
			result = strstr(src, readBuff);
		}
		else {
			
		}
	}*/
	int readStartAdr_old = readStartAdr;
	int curvisrow_old = curvisrow;
	int readOffset_old = readOffset;
	int readOffset1_old = readOffset1;
	int visualOffset_old = visualOffset;
	
	char* src = readBuffer + rowindex[curvisrow].end;
	int len = maxVisualSize - rowindex[curvisrow].end;
	
	char* result = kmp_find(src, len, searchstr, searchstrlen, next);
	//char* result = kmp_find(src, len, searchstr, searchstrlen, next);
	
	while (!result && setNextBlock()) {
		loadBlock();
		result = kmp_find(readBuffer, maxVisualSize, searchstr, searchstrlen, next);
	}
	if (result) {
		curvisrow = result - readBuffer;
		if (readStartAdr != readStartAdr_old) createRowIndex();
		for (int i = 0; i < visualRows; i++) {
			if (rowindex[i].end > curvisrow) {
				curvisrow = i;
				break;
			}
		}
	}
	else {
		readStartAdr = readStartAdr_old;
		curvisrow = curvisrow_old;
		readOffset = readOffset_old;
		readOffset1 = readOffset1_old;
		visualOffset = visualOffset_old;
		loadBlock();
		createRowIndex();
	}
}

void searchBackward(void) {
	/*
	if (!buffed) return;
		int readStartAdr_old = readStartAdr;
		int curvisrow_old = curvisrow;
		int readOffset_old = readOffset;
		int readOffset1_old = readOffset1;
		int visualOffset_old = visualOffset;
		
		int len = rowindex[curvisrow].start;
		
		char* result = kmp_find(readBuffer, len, searchstr, searchstrlen, next);
		while (!result && setPrevBlock()) {
			loadBlock();
			result = kmp_find(readBuffer, maxVisualSize, searchstr, searchstrlen, next);
		}
		if (result) {
			curvisrow = result - readBuffer;
			if (readStartAdr != readStartAdr_old) createRowIndex();
			for (int i = 0; i < visualRows; i++) {
				if (rowindex[i].end > curvisrow) {
					curvisrow = i;
					break;
				}
			}
		}
		else {
			readStartAdr = readStartAdr_old;
			curvisrow = curvisrow_old;
			readOffset = readOffset_old;
			readOffset1 = readOffset1_old;
			visualOffset = visualOffset_old;
			loadBlock();
			createRowIndex();
		}*/
}

void freeSearchStr(void) {
	mfree(searchstr);
	mfree(next);
}

void procSearchResult(WSHDR* ws) {
	freeSearchStr();
	searchstrlen = ws->wsbody[0];
	searchstr = malloc((searchstrlen << 1) + 1);
	ws2str_unicode(searchstr, ws, &searchstrlen);
	next = malloc(searchstrlen * sizeof (int));
	kmp_init(searchstr, searchstrlen, next);
	searchForward();
}
