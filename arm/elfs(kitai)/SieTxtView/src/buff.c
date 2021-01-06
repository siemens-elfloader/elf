/*
 * Copyright (c) 2007, MDVSC
 * All rights reserved.
 *
 * �ļ����ƣ�buff.c
 * �ļ���ʶ����
 * ժ Ҫ��ʵ�ֶԻ���Ĳ���
 *
 * ��ǰ�汾��0.9
 * �� �ߣ�H.Z.
 * ������ڣ�2007��11��29��
 *
 */
#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\code.h"
#include "..\inc\buff.h"
#include "..\inc\file.h"
#include "..\inc\conf_loader.h"

/*
 buffed          - �Ƿ�׼��������
 buffSize        - ��������ݳ���
 readStartAdr    - ��ǰ�����е��������ļ��е���ʼƫ��
 readSize        - ʵ����Ч��ȡ�����ݳ���
 readOffset      - ƫ������
 readBuffer      - ����
 visualOffset    - ת�����������ʼƫ��
 visualSize      - ת�������Ч���ݳ���
 visualRows      - ת�������Ч����
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
	//��ȡcodetype
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
 ����������ȫ��ת����unicode�����char*�Ρ�
 �������ݲ���������ʾ�����������
 1.��ԭ����Ϊgb2312��ʱ���ڴ�ҳ�����滻��ʱ���п��ܲ�����ȷ��ȡ��������ȷ�Ŀ�ʼ��ַ�����������롣
 2.��ԭ����Ϊgb2312��ʱ�򣬿�����ת���ļ��е�һ��λ�ã������λ����Ҫ�滻�ڴ�ҳ���Ҹ��ڴ�ҳ����ʼ���ļ���ͷ�����п��ܲ�����ȷ��ȡ���������ȷ��ʼ��ַ�����������롣
 3.�ļ����뱾��Ĵ����³�������
 
 ��ȡ���ݷ�������
 �ȶ�ȡһ�������ݣ��ٶ�ȡһ��������Ϊ���䣬����ת��Ϊunicode���뱣���ڻ����С�
 ��������������Ŀ���ǣ����ڸ����ڴ�ҳ��ʱ����޷��νӡ����û���ҳ���������ݶε�ʱ�򣬾�Ӧ��ת���ļ��ж�ȡ��һҳ�����ˡ�
 */
int loadBlock(void) {
	int offset = readStartAdr + readOffset + readOffset1;
	if (lseek(fd, offset, S_SET, &err, &err) == offset) { //ƫ��λ����Ч
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
			case 2: //unicode le��ֱ�ӿ�����ʾ����˲����κθı�
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
			case 2: //unicode le��ֱ�ӿ�����ʾ����˲����κθı�
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
	if (lseek(fd, start, S_SET, &err, &err) == start) { //ƫ��λ����Ч
		char *tb0 = (char *)malloc(LOAD_SIZE);
		char *tb = NULL;
		int size = fread(fd, tb0, LOAD_SIZE, &err);
		int size2;
		switch (codetype) {
		case 1: //gb2312
			tb = gb2unicode(tb0, size, &size, &size2);
			break;
		case 2: //unicode le��ֱ�ӿ�����ʾ����˲����κθı�
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
	//д�뵱ǰ��֮ǰ����������
	int maxlen = readStartAdr;
	int len = 0;
	while (maxlen > 0) {
		if ((len = fread(sfd, tbuff, maxlen > LOAD_SIZE ? LOAD_SIZE : maxlen,
				&err)) <= 0)
			break;
		fwrite(dfd, tbuff, len, &err);
		maxlen -= len;
	}
	//��ǰ�༭��

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

