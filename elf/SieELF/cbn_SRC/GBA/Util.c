// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 1999-2003 Forgotten
// Copyright (C) 2004 Forgotten and the VBA development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <zlib.h>

//extern "C" {
//#include <png.h>
//}

#include "System.h"
#include "NLS.h"
#include "Util.h"
#include "Flash.h"
#include "GBA.h"
#include "Globals.h"
#include "RTC.h"
#include "Port.h"

#define ERR -1
#define STREAM int
#define ffopen fopen
#define ffclose fclose
#define ffread fread
#define ffwrite fwrite
#define llseek lseek


extern "C" {
//#include "memgzio.h"
}

#ifndef _MSC_VER
#define _stricmp strcasecmp
#endif // ! _MSC_VER

static int (*utilGzWriteFunc)(gzFile, const voidp, unsigned int) = NULL;
static int (*utilGzReadFunc)(gzFile, voidp, unsigned int) = NULL;
static int (*utilGzCloseFunc)(gzFile) = NULL;

bool utilWritePNGFile(const char *fileName, int w, int h, u8 *pix)
{ return 0;
/*
  u8 writeBuffer[512 * 3];
  
  FILE *fp = fopen(fileName,"wb");

  if(!fp) {
    systemMessage(MSG_ERROR_CREATING_FILE, N_("Error creating file %s"), fileName);
    return false;
  }
  
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                                NULL,
                                                NULL,
                                                NULL);
  if(!png_ptr) {
    fclose(fp);
    return false;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    png_destroy_write_struct(&png_ptr,NULL);
    fclose(fp);
    return false;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    png_destroy_write_struct(&png_ptr,NULL);
    fclose(fp);
    return false;
  }

  png_init_io(png_ptr,fp);

  png_set_IHDR(png_ptr,
               info_ptr,
               w,
               h,
               8,
               PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  png_write_info(png_ptr,info_ptr);

  u8 *b = writeBuffer;

  int sizeX = w;
  int sizeY = h;

  switch(systemColorDepth) {
  case 16:
    {
      u16 *p = (u16 *)(pix+(w+2)*2); // skip first black line
      for(int y = 0; y < sizeY; y++) {
         for(int x = 0; x < sizeX; x++) {
          u16 v = *p++;
          
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G 
          *b++ = ((v >> systemBlueShift) & 0x01f) << 3; // B
        }
        p++; // skip black pixel for filters
        p++; // skip black pixel for filters
        png_write_row(png_ptr,writeBuffer);
        
        b = writeBuffer;
      }
    }
    break;
  case 24:
    {
      u8 *pixU8 = (u8 *)pix;
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          if(systemRedShift < systemBlueShift) {
            *b++ = *pixU8++; // R
            *b++ = *pixU8++; // G
            *b++ = *pixU8++; // B
          } else {
            int blue = *pixU8++;
            int green = *pixU8++;
            int red = *pixU8++;
            
            *b++ = red;
            *b++ = green;
            *b++ = blue;
          }
        }
        png_write_row(png_ptr,writeBuffer);
        
        b = writeBuffer;
      }
    }
    break;
  case 32:
    {
      u32 *pixU32 = (u32 *)(pix+4*(w+1));
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          u32 v = *pixU32++;
          
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G
          *b++ = ((v >> systemBlueShift) & 0x001f) << 3; // B
        }
        pixU32++;
        
        png_write_row(png_ptr,writeBuffer);
        
        b = writeBuffer;
      }
    }
    break;
  }
  
  png_write_end(png_ptr, info_ptr);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);

  return true;  
  */
}

void utilPutDword(u8 *p, u32 value)
{
  *p++ = value & 255;
  *p++ = (value >> 8) & 255;
  *p++ = (value >> 16) & 255;
  *p = (value >> 24) & 255;
}

void utilPutWord(u8 *p, u16 value)
{
  *p++ = value & 255;
  *p = (value >> 8) & 255;
}

void utilWriteBMP(char *buf, int w, int h, u8 *pix)
{
  u8 *b = (u8 *)buf;

  int sizeX = w;
  int sizeY = h;

  switch(systemColorDepth) {
  case 16:
    {
      u16 *p = (u16 *)(pix+(w+2)*(h)*2); // skip first black line
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          u16 v = *p++;

          *b++ = ((v >> systemBlueShift) & 0x01f) << 3; // B      
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G 
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
        }
        p++; // skip black pixel for filters
        p++; // skip black pixel for filters
        p -= 2*(w+2);
      }
    }
    break;
  case 24:
    {
      u8 *pixU8 = (u8 *)pix+3*w*(h-1);
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          if(systemRedShift > systemBlueShift) {
            *b++ = *pixU8++; // B
            *b++ = *pixU8++; // G
            *b++ = *pixU8++; // R           
          } else {
            int red = *pixU8++;
            int green = *pixU8++;
            int blue = *pixU8++;
            
            *b++ = blue;
            *b++ = green;
            *b++ = red;
          }
        }
        pixU8 -= 2*3*w;
      }
    }
    break;
  case 32:
    {
      u32 *pixU32 = (u32 *)(pix+4*(w+1)*(h));
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          u32 v = *pixU32++;

          *b++ = ((v >> systemBlueShift) & 0x001f) << 3; // B     
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
        }
        pixU32++;
        pixU32 -= 2*(w+1);
      }
    }
    break;
  }  
}

bool utilWriteBMPFile(const char *fileName, int w, int h, u8 *pix)
{
  u8 writeBuffer[512 * 3];
  
  STREAM fp = fopen(fileName,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err);

  if(fp==ERR) {
    systemMessage(MSG_ERROR_CREATING_FILE, N_("Error creating file %s"), fileName);
    return false;
  }

  struct {
    u8 ident[2];
    u8 filesize[4];
    u8 reserved[4];
    u8 dataoffset[4];
    u8 headersize[4];
    u8 width[4];
    u8 height[4];
    u8 planes[2];
    u8 bitsperpixel[2];
    u8 compression[4];
    u8 datasize[4];
    u8 hres[4];
    u8 vres[4];
    u8 colors[4];
    u8 importantcolors[4];
    //    u8 pad[2];
  } bmpheader;
  memset(&bmpheader, 0, sizeof(bmpheader));

  bmpheader.ident[0] = 'B';
  bmpheader.ident[1] = 'M';

  u32 fsz = sizeof(bmpheader) + w*h*3;
  utilPutDword(bmpheader.filesize, fsz);
  utilPutDword(bmpheader.dataoffset, 0x36);
  utilPutDword(bmpheader.headersize, 0x28);
  utilPutDword(bmpheader.width, w);
  utilPutDword(bmpheader.height, h);
  utilPutDword(bmpheader.planes, 1);
  utilPutDword(bmpheader.bitsperpixel, 24);
  utilPutDword(bmpheader.datasize, 3*w*h);

  ffwrite(fp,&bmpheader, sizeof(bmpheader), &err);

  u8 *b = writeBuffer;

  int sizeX = w;
  int sizeY = h;

  switch(systemColorDepth) {
  case 16:
    {
      u16 *p = (u16 *)(pix+(w+2)*(h)*2); // skip first black line
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          u16 v = *p++;

          *b++ = ((v >> systemBlueShift) & 0x01f) << 3; // B      
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G 
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
        }
        p++; // skip black pixel for filters
        p++; // skip black pixel for filters
        p -= 2*(w+2);
        ffwrite(fp,writeBuffer, 3*w, &err);
        
        b = writeBuffer;
      }
    }
    break;
  case 24:
    {
      u8 *pixU8 = (u8 *)pix+3*w*(h-1);
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          if(systemRedShift > systemBlueShift) {
            *b++ = *pixU8++; // B
            *b++ = *pixU8++; // G
            *b++ = *pixU8++; // R           
          } else {
            int red = *pixU8++;
            int green = *pixU8++;
            int blue = *pixU8++;
            
            *b++ = blue;
            *b++ = green;
            *b++ = red;
          }
        }
        pixU8 -= 2*3*w;
        ffwrite(fp,writeBuffer, 3*w, &err);
        
        b = writeBuffer;
      }
    }
    break;
  case 32:
    {
      u32 *pixU32 = (u32 *)(pix+4*(w+1)*(h));
      for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
          u32 v = *pixU32++;

          *b++ = ((v >> systemBlueShift) & 0x001f) << 3; // B     
          *b++ = ((v >> systemGreenShift) & 0x001f) << 3; // G
          *b++ = ((v >> systemRedShift) & 0x001f) << 3; // R
        }
        pixU32++;
        pixU32 -= 2*(w+1);
        
        ffwrite(fp,writeBuffer, 3*w, &err);
        
        b = writeBuffer;
      }
    }
    break;
  }

  ffclose(fp,&err);

  return true;
}

static int utilReadInt2(STREAM f)
{
  unsigned char cc, c;
  if(ffread(f,&cc,1,&err)!=1) return -1;
  if(ffread(f,&c,1,&err)!=1) return -1;
  return c + (cc<<8);
}

static int utilReadInt3(STREAM f)
{
  unsigned char ccc, cc, c;
  if(ffread(f,&ccc,1,&err)!=1) return -1;
  if(ffread(f,&cc,1,&err)!=1) return -1;
  if(ffread(f,&c,1,&err)!=1) return -1;
  return c + (cc<<8) +(ccc<<16);
}

char fgetc(int f){ return 0;} //fake

void utilApplyIPS(const char *ips, u8 **r, int *s)
{
  // from the IPS spec at http://zerosoft.zophar.net/ips.htm
  STREAM f = fopen(ips, A_ReadOnly+A_BIN,P_READ,&err);
  if(f==ERR)
    return;
  u8 *rom = *r;
  int size = *s;
  if(fgetc(f) == 'P' &&
     fgetc(f) == 'A' &&
     fgetc(f) == 'T' &&
     fgetc(f) == 'C' &&
     fgetc(f) == 'H') {
    int b;
    int offset;
    int len;
    for(;;) {
      // read offset
      offset = utilReadInt3(f);
      // if offset == EOF, end of patch
      if(offset == 0x454f46)
        break;
      // read length
      len = utilReadInt2(f);
      if(!len) {
        // len == 0, RLE block
        len = utilReadInt2(f);
        // byte to fill
        int c = fgetc(f);
        if(c == -1)
          break;
        b = (u8)c;
      } else
        b= -1;
      // check if we need to reallocate our ROM
      if((offset + len) >= size) {
        size *= 2;
        rom = (u8 *)realloc(rom, size);
        *r = rom;
        *s = size;
      }      
      if(b == -1) {
        // normal block, just read the data
        if(ffread(f,&rom[offset], len, &err) != (size_t)len)
          break;
      } else {
        // fill the region with the given byte
        while(len--) {
          rom[offset++] = b;
        }
      }
    }
  }
  // close the file
  ffclose(f,&err);
}

extern bool cpuIsMultiBoot;

bool utilIsGBAImage(const char * file)
{
  cpuIsMultiBoot = false;
  if(strlen(file) > 4) {
    char * p = strrchr(file,'.');

    if(p != NULL) {
      if(stricmp(p, ".gba") == 0)
        return true;
      if(stricmp(p, ".agb") == 0)
        return true;
      if(stricmp(p, ".bin") == 0)
        return true;
      if(stricmp(p, ".elf") == 0)
        return true;
      if(stricmp(p, ".mb") == 0) {
        cpuIsMultiBoot = true;
        return true;
      }
    }
  }

  return false;
}

bool utilIsGBImage(const char * file)
{
  if(strlen(file) > 4) {
    char * p = strrchr(file,'.');

    if(p != NULL) {
      if(stricmp(p, ".gb") == 0)
        return true;
      if(stricmp(p, ".gbc") == 0)
        return true;
      if(stricmp(p, ".cgb") == 0)
        return true;
      if(stricmp(p, ".sgb") == 0)
        return true;      
    }
  }

  return false;
}

bool utilIsZipFile(const char *file)
{
  if(strlen(file) > 4) {
    char * p = strrchr(file,'.');

    if(p != NULL) {
      if(stricmp(p, ".zip") == 0)
        return true;
    }
  }

  return false;  
}

#if 0
bool utilIsRarFile(const char *file)
{
  if(strlen(file) > 4) {
    char * p = strrchr(file,'.');

    if(p != NULL) {
      if(stricmp(p, ".rar") == 0)
        return true;
    }
  }

  return false;  
}
#endif

bool utilIsGzipFile(const char *file)
{
  if(strlen(file) > 3) {
    char * p = strrchr(file,'.');

    if(p != NULL) {
      if(stricmp(p, ".gz") == 0)
        return true;
      if(stricmp(p, ".z") == 0)
        return true;
    }
  }

  return false;  
}

void utilGetBaseName(const char *file, char *buffer)
{
  strcpy(buffer, file);

  if(utilIsGzipFile(file)) {
    char *p = strrchr(buffer, '.');

    if(p)
      *p = 0;
  }
}

int utilFindType(const char *file)
{
//  char buffer[2048];
/*  
  if(utilIsZipFile(file)) {
    unzFile unz = unzOpen(file);
    
    if(unz == NULL) {
      systemMessage(MSG_CANNOT_OPEN_FILE, N_("Cannot open file %s"), file);
      return IMAGE_UNKNOWN;
    }
    
    int r = unzGoToFirstFile(unz);
    
    if(r != UNZ_OK) {
      unzClose(unz);
      systemMessage(MSG_BAD_ZIP_FILE, N_("Bad ZIP file %s"), file);
      return IMAGE_UNKNOWN;
    }
    
    IMAGE_TYPE found = IMAGE_UNKNOWN;
    
    unz_file_info info;
    
    while(true) {
      r = unzGetCurrentFileInfo(unz,
                                &info,
                                buffer,
                                sizeof(buffer),
                                NULL,
                                0,
                                NULL,
                                0);
      
      if(r != UNZ_OK) {
        unzClose(unz);
        systemMessage(MSG_BAD_ZIP_FILE, N_("Bad ZIP file %s"), file);
        return IMAGE_UNKNOWN;
      }
      
      if(utilIsGBAImage(buffer)) {
        found = IMAGE_GBA;
        break;
      }

      if(utilIsGBImage(buffer)) {
        found = IMAGE_GB;
        break;
      }
        
      r = unzGoToNextFile(unz);
      
      if(r != UNZ_OK)
        break;
    }
    unzClose(unz);
    
    if(found == IMAGE_UNKNOWN) {
      systemMessage(MSG_NO_IMAGE_ON_ZIP,
                    N_("No image found on ZIP file %s"), file);
      return found;
    }
    return found;
#if 0
  } else 
	  if(utilIsRarFile(file)) {
    IMAGE_TYPE found = IMAGE_UNKNOWN;
    
    ArchiveList_struct *rarList = NULL;
    if(urarlib_list((void *)file, (ArchiveList_struct *)&rarList)) {
      ArchiveList_struct *p = rarList;

      while(p) {
        if(utilIsGBAImage(p->item.Name)) {
          found = IMAGE_GBA;
          break;
        }

        if(utilIsGBImage(p->item.Name)) {
          found = IMAGE_GB;
          break;
        }
        p = p->next;
      }
      
      urarlib_freelist(rarList);
    }
    return found;
#endif
  } else {
  
    if(utilIsGzipFile(file))
      utilGetBaseName(file, buffer);
    else
      strcpy(buffer, file);
    
    if(utilIsGBAImage(buffer))
      return IMAGE_GBA;
    if(utilIsGBImage(buffer))
      return IMAGE_GB;
//  }
  return IMAGE_UNKNOWN;  
  */
return IMAGE_GBA;
}

static int utilGetSize(int size)
{
  int res = 1;
  while(res < size)
    res <<= 1;
  return res;
}

static u8 *utilLoadFromZip(const char *file,
                           bool (*accept)(const char *),
                           u8 *data,
                           int *size)
{  //deleted
	return 0;
}

static u8 *utilLoadGzipFile(const char *file,
                            bool (*accept)(const char *),
                            u8 *data,
                            int *size)
{
  STREAM f = fopen(file, A_ReadOnly+A_BIN,P_READ,&err);

  if(f == ERR) {
    systemMessage(MSG_ERROR_OPENING_IMAGE, N_("Error opening image %s"), file);
    return NULL;
  }

  llseek(f, -4, S_END,&err,&err);
  int fileSize = fgetc(f) | (fgetc(f) << 8) | (fgetc(f) << 16) | (fgetc(f) << 24);
  ffclose(f,&err);
  if(*size == 0)
    *size = fileSize;

  gzFile gz = fopen(file,A_ReadOnly+A_BIN,P_READ,&err);

  if(gz == ERR) {
    // should not happen, but who knows?
    systemMessage(MSG_ERROR_OPENING_IMAGE, N_("Error opening image %s"), file);
    return NULL;
  }

  u8 *image = data;

  if(image == NULL) {
    image = (u8 *)malloc(utilGetSize(*size));
    if(image == NULL) {
      systemMessage(MSG_OUT_OF_MEMORY, N_("Failed to allocate memory for %s"),
                    "data");
      ffclose(f,&err);
      return NULL;
    }
    *size = fileSize;
  }
  int read = fileSize <= *size ? fileSize : *size;
  int r = ffread(gz, image, read,&err);
  ffclose(gz,&err);

  if(r != (int)read) {
    systemMessage(MSG_ERROR_READING_IMAGE,
                  N_("Error reading image %s"), file);
    if(data == NULL)
      mfree(image);
    return NULL;
  }  
  
  *size = fileSize;

  return image;  
}

#if 0
static u8 *utilLoadRarFile(const char *file,
                           bool (*accept)(const char *),
                           u8 *data,
                           int &size)
{
  char buffer[2048];

  ArchiveList_struct *rarList = NULL;
  if(urarlib_list((void *)file, (ArchiveList_struct *)&rarList)) {
    ArchiveList_struct *p = rarList;
    
    bool found = false;
    while(p) {
      if(accept(p->item.Name)) {
        strcpy(buffer, p->item.Name);
        found = true;
        break;
      }
      p = p->next;
    }
    if(found) {
      void *memory = NULL;
      unsigned long lsize = 0;
      size = p->item.UnpSize;
      int r = urarlib_get((void *)&memory, &lsize, buffer, (void *)file, "");
      if(!r) {
        systemMessage(MSG_ERROR_READING_IMAGE,
                      N_("Error reading image %s"), buffer);
        urarlib_freelist(rarList);
        return NULL;
      }
      u8 *image = (u8 *)memory;
      if(data != NULL) {
        memcpy(image, data, size);
      }
      urarlib_freelist(rarList);
      return image;
    }
    systemMessage(MSG_NO_IMAGE_ON_ZIP,
                  N_("No image found on RAR file %s"), file);
    urarlib_freelist(rarList);
    return NULL;
  }
  // nothing found
  return NULL;
}
#endif

u8 *utilLoad(const char *file,
             bool (*accept)(const char *),
             u8 *data,
             int *size)
{
  if(utilIsZipFile(file)) {
    return utilLoadFromZip(file, accept, data, size);
  }
  if(utilIsGzipFile(file)) {
    return utilLoadGzipFile(file, accept, data, size);
  }
#if 0
  if(utilIsRarFile(file)) {
    return utilLoadRarFile(file, accept, data, size);
  }
#endif
  
  u8 *image = data;

  STREAM f = ffopen(file, A_ReadOnly+A_BIN,P_READ,&err);

  if(f==ERR) {
    systemMessage(MSG_ERROR_OPENING_IMAGE, N_("Error opening image %s"), file);
    return NULL;
  }

  int fileSize = llseek(f,0,S_END,&err,&err);
  llseek(f,0,S_SET,&err,&err);
  if(*size == 0)
    *size = fileSize;

  if(image == NULL) {
    image = (u8 *)malloc(utilGetSize(*size));
    if(image == NULL) {
      systemMessage(MSG_OUT_OF_MEMORY, N_("Failed to allocate memory for %s"),
                    "data");
      ffclose(f,&err);
      return NULL;
    }
    *size = fileSize;
  }
  int read = fileSize <= *size ? fileSize : *size;
  int r = ffread(f,image, read, &err);
  ffclose(f,&err);

  if(r != (int)read) {
    systemMessage(MSG_ERROR_READING_IMAGE,
                  N_("Error reading image %s"), file);
    if(data == NULL)
      mfree(image);
    return NULL;
  }  

  *size = fileSize;
  
  return image;
}

void utilWriteInt(gzFile gzFile1, int i)
{
  utilGzWrite(gzFile1, &i, sizeof(int));
}

int utilReadInt(gzFile gzFile1)
{
  int i = 0;
  utilGzRead(gzFile1, &i, sizeof(int));
  return i;
}

void utilReadData(gzFile gzFile1, variable_desc* data)
{
  while(data->address) {
    utilGzRead(gzFile1, data->address, data->size);
    data++;
  }
}

void utilWriteData(gzFile gzFile1, variable_desc *data)
{
  while(data->address) {
    utilGzWrite(gzFile1, data->address, data->size);
    data++;
  }
}

gzFile utilGzOpen(const char *file, const char *mode)
{
//  utilGzWriteFunc = (int (*)(void *,void * const, unsigned int))gzwrite;
//  utilGzReadFunc = gzread;
//  utilGzCloseFunc = gzclose;

//  return gzopen(file, mode);
	return 0;
}

gzFile utilMemGzOpen(char *memory, int available, char *mode)
{
//  utilGzWriteFunc = memgzwrite;
//  utilGzReadFunc = memgzread;
//  utilGzCloseFunc = memgzclose;

  return 0;//memgzopen(memory, available, mode);  
}

int utilGzWrite(gzFile file, const voidp buffer, unsigned int len)
{
  return utilGzWriteFunc(file, buffer, len);
}

int utilGzRead(gzFile file, voidp buffer, unsigned int len)
{
  return utilGzReadFunc(file, buffer, len);
}

int utilGzClose(gzFile file)
{
  return utilGzCloseFunc(file);
}

long utilGzMemTell(gzFile file)
{
//  return memtell(file);
	return 0;
}

void utilGBAFindSave(const u8 *data, const int size)
{
  u32 *p = (u32 *)data;
  u32 *end = (u32 *)(data + size);
  int saveType = 0;
  int flashSize = 0x10000;
  bool rtcFound = false;

  while(p  < end) {
    u32 d = READ32LE(p);
    
    if(d == 0x52504545) {
      if(memcmp(p, (char*)"EEPROM_", 7) == 0) {
        if(saveType == 0)
          saveType = 1;
      }
    } else if (d == 0x4D415253) {
      if(memcmp(p, (char*)"SRAM_", 5) == 0) {
        if(saveType == 0)
          saveType = 2;
      }
    } else if (d == 0x53414C46) {
      if(memcmp(p, (char*)"FLASH1M_", 8) == 0) {
        if(saveType == 0) {
          saveType = 3;
          flashSize = 0x20000;
        }
      } else if(memcmp(p, (char*)"FLASH", 5) == 0) {
        if(saveType == 0) {
          saveType = 3;
          flashSize = 0x10000;
        }
      }
    } else if (d == 0x52494953) {
      if(memcmp(p, (char*)"SIIRTC_V", 8) == 0)
        rtcFound = true;
    }
    p++;
  } 
  // if no matches found, then set it to NONE
  if(saveType == 0) {
    saveType = 5;
  }
  rtcEnable(rtcFound);
  cpuSaveType = saveType;
  flashSetSize(flashSize);
}