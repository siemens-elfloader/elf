/*
 * Copyright (c) 2007, MDVSC
 * All rights reserved.
 *
 * 文件名称：code.c
 * 文件标识：无
 * 摘 要：实现数据的编码转换
 *
 * 当前版本：0.9
 * 作 者：HanikLZ
 * 完成日期：2007年11月29日
 *
 */
#include "..\..\inc\swilib.h"
#include "..\inc\main.h"

#define MAP_SIZE 32768
char gb2312map[MAP_SIZE];
int maplen = 0, maplen1 = 0;
int codetype;

int getCodeType(char* str) {
	if (!str) return 0;
	int result = 1; //ansi
	if (str[0] == 0xff && str[1] == 0xfe) {
		result = 2; //unicode le
	} else if (str[0] == 0xfe && str[1] == 0xff) {
		result = 3; //unicode be
	} else if (str[0] == 0xef && str[1] == 0xbb && str[2] == 0xbf) {
		result = 4; //utf8
	}
	return result;
}

void loadGB2UnicodeMap(void) {
	int fd1 = 0;
	unsigned int ul1 = 0;
	maplen = maplen1 = 0;
	char *t = malloc(128);
	strcpy(t, apppath);
	strcat(t, "map\\gb2uc.map");
	if ((fd1 = fopen(t, A_ReadOnly + A_BIN, P_READ, &ul1)) != -1) {
		maplen = fread(fd1, gb2312map, MAP_SIZE, &ul1);
		fclose(fd1, &ul1);
	}
	mfree(t);
}

void loadUnicode2GBMap(void) {
	int fd1 = 0;
	unsigned int ul1 = 0;
	maplen = maplen1 = 0;
	char *t = malloc(128);
	strcpy(t, apppath);
	strcat(t, "map\\uc2gb.map");
	if ((fd1 = fopen(t, A_ReadOnly + A_BIN, P_READ, &ul1)) != -1) {
		maplen1 = fread(fd1, gb2312map, MAP_SIZE, &ul1);
		fclose(fd1, &ul1);
	}
	mfree(t);
}

void str2ws_unicode(WSHDR* ws, char* str, int len) {
	int i = 0;
	char *p;
	int wsmax;
	if(!ws || !str) return;
	wsmax=ws->maxlen;
	p = str;
	while (((p - str) < (len - 1)) && (i<wsmax)) {
		ws->wsbody[++i] = (*(p + 1) << 8) + *p;
		p += 2;
	}
	ws->wsbody[0] = i;
}

void ws2str_unicode(char* str, WSHDR* ws, int *len) { //注意范围
	for (int i = 0; i < ws->wsbody[0]; i++) {
		*(str + (i << 1)) = ws->wsbody[i + 1] & 0xFF;
		*(str + (i << 1) + 1) = ws->wsbody[i + 1] >> 8;
	}
	*len = ws->wsbody[0] << 1;
}

char* unicodeSwitch(char *str, int len, int *rlen, int *llen) {
	if (!str)
		return NULL;
	int i = 0, l = len >> 1 << 1;
	char *p = malloc(l);
	while (i < l) {
		*(p + i) = *(str + i + 1);
		*(p + i + 1) = *(str + i);
		i += 2;
	}
	*rlen = *llen = l;
	return p;
}

/*
 str     - 原始编码串
 len     - 需要转换的原始串的字节数
 rlen    - 转换成功后目标串的字节数
 llen    - 实际转换的原始串的字节数
 返回    - 目标编码串
 */
char* gb2unicode(char *str, int len, int *rlen, int *llen) {

	if (!str)
		return NULL;
	if (!maplen)
		loadGB2UnicodeMap(); //读取map文件
	if (maplen) {
		int ad = 0, i = 0, j = 0, l = len, bl = len << 1;
		char *s = malloc(bl);
		*llen = *rlen = 0;
		bl -= 3;
		while (i < l) {
			if (str[i] < 0xa1) { //单字节编码
				s[j++] = str[i++];
				s[j++] = 0x0;
				(*llen)++;
				(*rlen) += 2;
			} else {
				if (i > l - 2)
					break;
				ad = str[i] - 0xa1;
				if (str[i++] > 0xa9)
					ad -= 0x6;
				ad = (((ad << 8) | str[i++]) - ad * 0xa2 - 0xa1) << 1;
				if (ad < maplen - 1) {
					s[j++] = gb2312map[ad];
					s[j++] = gb2312map[ad + 1];
				}
				(*llen) += 2;
				(*rlen) += 2;
			}
		}
		if (*rlen < (l << 1)) {
			char *r = malloc(*rlen);
			memcpy(r, s, *rlen);
			mfree(s);
			s = r;
		}
		return s;
	} else {
		ShowMSG(1, (int) "打开MAP失败!");
		return NULL;
	}
}

char* utf82unicode(char *str, int len, int *rlen, int *llen) {
	if (!str)
		return NULL;

	/*
	 char *ms = malloc (50);
	 sprintf(ms, "%d, %d", j, l);
	 ShowMSG(1, (int) ms);
	 mfree(ms);*/

	int i = 0, j = 0, l = len, bl = len << 1;
	char* s = malloc(bl);
	char c;
	*rlen = *llen = 0;
	bl -= 3;
	for (i = 0; i < l; i++) {
		c = str[i];
		if ((c >> 7) == 0x0) { //单字节编码
			s[j++] = c;
			s[j++] = 0x0;
			(*llen)++;
		} else if ((c >> 5) == 0x6 && i < l - 1) { //双字节编码
			s[++j] = ((c & 0x1f) >> 2);
			s[j - 1] = c << 6;
			c = str[++i];
			s[j - 1] = s[j - 1] | (c & 0x3f);
			j++;
			(*llen) += 2;
		} else if ((c >> 4) == 0xe && i < l - 2) { //三字节编码
			s[++j] = c << 4;
			c = str[++i];
			s[j] = s[j] | ((c >> 2) & 0xf);
			s[j - 1] = c << 6;
			c = str[++i];
			s[j - 1] = s[j - 1] | (c & 0x3f);
			j++;
			(*llen) += 3;

		} else
			break;
		(*rlen) += 2;
	}

	if (*rlen < (l << 1)) {
		char *r = malloc(*rlen);
		memcpy(r, s, *rlen);
		mfree(s);
		s = r;
	}
	return s;
}

char* unicode2gb(char *str, int *len) {

	if (!str)
		return NULL;
	if (!maplen1)
		loadUnicode2GBMap();
	if (maplen1) {
		int aj[256];
		int i = 0;
		for (int k = 0; i < 256; k += 2) {
			aj[i++] = ((gb2312map[k] & 0xff) << 8) | (gb2312map[k + 1] & 0xff);
		}
		char *abyte0 = malloc(*len);
		int l = 0;
		for (int i1 = 0; i1 < (*len) - 1; i1 += 2) {
			char c1 = str[i1 + 1]; //高位
			char byte0 = str[i1]; //低位
			if (c1 == 0 && (byte0 & 0x80) == 0) { //小于 0x0080 */
				/*
				 if(byte0 == 10)
				 abyte0[l++] = 13;*/

				abyte0[l++] = byte0;
			} else {
				int c2 = aj[c1];
				if (c2 > maplen1)
					return NULL;
				int j1 = gb2312map[c2] & 0xff;
				int k1 = j1 * 3 + 1; //长度
				int l1 = 1;
				do {
					if (l1 >= k1)
						break;
					if (gb2312map[c2 + l1] == byte0) {
						abyte0[l++] = gb2312map[++l1 + c2];
						abyte0[l++] = gb2312map[++l1 + c2];
						break;
					}
					l1 += 3;
				} while (1);
			}
		}
		char *abyte1 = malloc(l);
		memcpy(abyte1, abyte0, l);
		*len = l;
		mfree(abyte0);
		return abyte1;
	} else {
		ShowMSG(1, (int) "打开MAP失败!");
		return NULL;
	}
	/*
	 int ag = 0;
	 unsigned int ul1 = 0;
	 int aj[256];
	 char ai[768];
	 if ((ag = fopen(MAP1, A_ReadOnly + A_BIN, P_READ, &ul1)) != -1) {
	 fread(ag, ai, 512, &ul1);
	 int i = 0;
	 for(int k = 0; i < 256; k += 2) {
	 aj[i++] = ((ai[k] & 0xff) << 8) | (ai[k + 1] & 0xff);
	 }
	 }
	 else {
	 ShowMSG(1, (int) "open map file Error!");
	 return NULL;
	 }
	 
	 char *abyte0 = malloc(*len);
	 int l = 0;

	 for(int i1 = 0; i1 < (*len) - 1; i1 += 2) {
	 char c1 = str[i1 + 1];			//高位
	 char byte0 = str[i1];		//低位
	 if(c1 == 0 && (byte0 & 0x80) == 0) {			//小于 0x0080 */
	/*
	 if(byte0 == 10)
	 abyte0[l++] = 13;*/
	/*
	 abyte0[l++] = byte0;
	 }
	 else {
	 int c2 = aj[c1];
	 if (!lseek(ag, c2, S_SET, &ul1, &ul1)) {
	 mfree(abyte0);
	 fclose(ag, &ul1);
	 return NULL;
	 }
	 fread(ag, ai, 768, &ul1);
	 int j1 = ai[0] & 0xff;
	 int k1 = j1 * 3 + 1;				//长度
	 int l1 = 1;
	 do {
	 if(l1 >= k1) break;
	 if(ai[l1] == byte0) {
	 abyte0[l++] = ai[++l1];
	 abyte0[l++] = ai[++l1];
	 break;
	 }
	 l1 += 3;
	 } while(1);
	 }
	 }
	 
	 char *abyte1 = malloc(l);
	 memcpy(abyte1, abyte0, l);
	 *len = l;
	 mfree(abyte0);
	 fclose(ag, &ul1);
	 return abyte1;*/
}

char* unicode2utf8(char *str, int *len) {
	if (!str)
		return NULL;

	int i = 0, j = 0;
	char* s = malloc((*len) << 1);

	int c;
	for (i = 0; i < (*len) - 1; i += 2) {
		c = (str[i + 1] << 8) | str[i];
		if (c < 0x80) { //单字节编码
			s[j++] = (char) c;
		} else if (c > 0x7f && c < 0x800) { //双字节编码
			s[j++] = (c >> 6) | 0xc0;
			s[j++] = c & 0x3f | 0x80;
		} else if (c > 0x7ff && c < 0x10000) { //三字节编码
			s[j++] = (c >> 12) | 0xe0;
			s[j++] = (c >> 6) & 0x3f | 0x80;
			s[j++] = c & 0x3f | 0x80;
		}
	}
	*len = j;
	return s;
}
