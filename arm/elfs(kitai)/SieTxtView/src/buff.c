/*
 * Copyright (c) 2007, MDVSC
 * All rights reserved.
 *
 * 文件名称：buff.c
 * 文件标识：无
 * 摘 要：实现对缓存的操作
 *
 * 当前版本：0.9
 * 作 者：H.Z.
 * 完成日期：2007年11月29日
 *
 */
#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\code.h"
#include "..\inc\buff.h"
#include "..\inc\file.h"
#include "..\inc\conf_loader.h"

/*
 buffed          - 是否准备好数据
 buffSize        - 缓存的数据长度
 readStartAdr    - 当前缓存中的数据在文件中的起始偏移
 readSize        - 实际有效读取的数据长度
 readOffset      - 偏移修正
 readBuffer      - 缓存
 visualOffset    - 转换后的数据起始偏移
 visualSize      - 转换后的有效数据长度
 visualRows      - 转换后的有效行数
 */
int buffed, buffSize;
int readStartAdr, readOffset, readOffset1, readSize;
int visualOffset, visualSize, visualRows, maxVisualSize;
char* readBuffer;

int initBuffer(void) {
	buffed = buffSize = 0;
	readStartAdr = readOffset1 = 0;
	readOffset = getStartOffset();
	visualOffset = visualSize = visualRows = maxVisualSize = 0;
	readSize = LOAD_SIZE - (LOAD_SIZE >> 3);
	return 1;
	//获取codetype
}

int getStartOffset(void) {
	readOffset = 0;
	if (charset)
		codetype = charset;
	else {
		switch (codetype) {
		case 2:
		case 3:
			readOffset += 2;
			break;
		case 4:
			readOffset += 3;
			break;
		}
	}
	return readOffset;
}

int setPrevBlock(void) {
	if (readStartAdr == 0)
		return 0;
	readSize = readStartAdr;
	readStartAdr -= LOAD_SIZE - (LOAD_SIZE >> 3);
	if (readStartAdr >= 0)
		readSize = LOAD_SIZE - (LOAD_SIZE >> 3);
	else
		readStartAdr = 0;
	visualOffset = 0;
	return 1;
}

int setNextBlock(void) {
	if (readStartAdr + readSize >= fileSize) return 0;
	readStartAdr += readSize;
	readSize = LOAD_SIZE - (LOAD_SIZE >> 3);
	return 1;
}

/*
 读出的数据全部转换成unicode编码的char*段。
 读出数据不能正常显示出来的情况：
 1.当原编码为gb2312的时候，内存页向上替换的时候，有可能不能正确获取到编码正确的开始地址，而出现乱码。
 2.当原编码为gb2312的时候，快速跳转到文件中的一个位置，如果该位置需要替换内存页，且该内存页不起始至文件开头，则有可能不能正确获取到编码的正确开始地址，而出现乱码。
 3.文件编码本身的错误导致出现乱码
 
 读取数据分两步：
 先读取一部分数据，再读取一段数据作为补充，将其转换为unicode编码保存在缓存中。
 做此两步操作的目的是，便于更换内存页的时候的无缝衔接。在用户翻页到补充数据段的时候，就应该转从文件中读取下一页数据了。
 */
int loadBlock(void) {
	int offset = readStartAdr + readOffset + readOffset1;
	if (lseek(fd, offset, S_SET, &err, &err) == offset) { //偏移位置有效
		//here we go
		buffed = 0;
		mfree(readBuffer);
		readBuffer = (char *)malloc(LOAD_SIZE);
		maxVisualSize = buffSize = visualSize = 0;
		char *tb= NULL;
		if ((readSize = fread(fd, readBuffer, readSize, &err)) > 0) {
			switch (codetype) {
			case 1: //gb2312
				tb = gb2unicode(readBuffer, readSize, &visualSize, &readSize);
				break;
			case 2: //unicode le，直接可以显示，因此不做任何改变
				visualSize = readSize;
				break;
			case 3: //unicode be
				tb = unicodeSwitch(readBuffer, readSize, &visualSize,
						&readSize);
				break;
			case 4: //utf8
				tb = utf82unicode(readBuffer, readSize, &visualSize,
						&readSize);
				break;
			default:
				return 0;
			}
			mfree(tb);
			tb = NULL;
			
			lseek(fd, offset, S_SET, &err, &err);
			buffSize = fread(fd, readBuffer, LOAD_SIZE, &err);
			switch (codetype) {
			case 1: //gb2312
				tb = gb2unicode(readBuffer, buffSize, &maxVisualSize,
						&buffSize);
				break;
			case 2: //unicode le，直接可以显示，因此不做任何改变
				maxVisualSize = buffSize;
				break;
			case 3: //unicode be
				tb = unicodeSwitch(readBuffer, buffSize, &maxVisualSize,
						&buffSize);
				break;
			case 4: //utf8
				tb = utf82unicode(readBuffer, buffSize, &maxVisualSize,
						&buffSize);
				break;
			default:
				return 0;
			}
			if (tb) {
				mfree(readBuffer);
				readBuffer = tb;
			}
		}
		buffed = 1;
		return 1;
	}
	return 0;
}

WSHDR* getOffsetWS(int start, int offset, int wslen) {
	WSHDR *ws = AllocWS(wslen);
	if (lseek(fd, start, S_SET, &err, &err) == start) { //偏移位置有效
		char *tb0 = (char *)malloc(LOAD_SIZE);
		char *tb = NULL;
		int size = fread(fd, tb0, LOAD_SIZE, &err);
		int size2;
		switch (codetype) {
		case 1: //gb2312
			tb = gb2unicode(tb0, size, &size, &size2);
			break;
		case 2: //unicode le，直接可以显示，因此不做任何改变
			size2 = size;
			break;
		case 3: //unicode be
			tb = unicodeSwitch(tb0, size, &size, &size2);
			break;
		case 4: //utf8
			tb = utf82unicode(tb0, size, &size, &size2);
			break;
		default:
			wsprintf(ws, "invaid bookmark!");
			mfree(tb0);
			return ws;
		}
		if (tb) {
			mfree(tb0);
			tb0 = tb;
		}
		//WriteLog(tb0, size);
		if (offset > size - 1) wsprintf(ws, "invaid bookmark!");
		else {
			wslen = wslen << 1;
			if (offset + wslen > size - 1) wslen = size - offset - 1;
			str2ws_unicode(ws, tb0 + offset, wslen);
		}
		mfree(tb0);
	}
	else wsprintf(ws, "invaid bookmark!");
	return ws;
}

int saveBlock(void) {
	fclose(fd, &err);
	fd = -1;
	char temp[128];
	strcpy(temp, procfile);
	strcat(temp, ".temp");
	unlink(temp, &err);
	int sfd = fopen(procfile, A_ReadOnly, P_READ, &err);
	int dfd = fopen(temp, A_ReadWrite + A_Create + A_Truncate,
			P_READ + P_WRITE, &err);
	char *tbuff = malloc(LOAD_SIZE);
	//写入当前块之前的所有数据
	int maxlen = readStartAdr;
	int len = 0;
	while (maxlen > 0) {
		if ((len = fread(sfd, tbuff, maxlen > LOAD_SIZE ? LOAD_SIZE : maxlen,
				&err)) <= 0)
			break;
		fwrite(dfd, tbuff, len, &err);
		maxlen -= len;
	}
	//当前编辑块

	maxlen = maxVisualSize;
	mfree(tbuff);
	switch (codetype) {
	case 1: //ansi
		tbuff = unicode2gb(readBuffer, &maxlen);
		break;
	case 2: //unicode le
		tbuff = malloc(maxlen);
		memcpy(readBuffer, tbuff, maxlen);
		break;
	case 3: //unicode be
		tbuff = unicodeSwitch(readBuffer, maxlen, &maxlen, &maxlen);
		break;
	case 4: //utf8
		tbuff = unicode2utf8(readBuffer, &maxlen);
		break;
	default:
		tbuff = unicode2gb(readBuffer, &maxlen);
		break;
	}
	//WriteLog(tb, maxlen);
	fwrite(dfd, tbuff, maxlen, &err);
	mfree(tbuff);

	maxlen = readStartAdr + buffSize;
	if (lseek(sfd, maxlen, S_SET, &err, &err) == maxlen) {
		maxlen = fileSize - maxlen;
		tbuff = malloc(LOAD_SIZE);
		while (maxlen > 0) {
			if ((len = fread(sfd, tbuff, maxlen > LOAD_SIZE ? LOAD_SIZE
					: maxlen, &err)) <= 0)
				break;
			fwrite(dfd, tbuff, len, &err);
			maxlen -= LOAD_SIZE;
		}
		mfree(tbuff);
	}
	fclose(dfd, &err);
	fclose(sfd, &err);
	unlink(procfile, &err);
	fmove(temp, procfile, &err);
	fd = fopen(procfile, A_ReadOnly + A_BIN, P_READ, &err);
	return 1;
}

