#ifndef _UPLOAD_H_
#define _UPLOAD_H_

typedef void (*func)(void* data, char* fullname, char* name);
void PrepareFileForUpload(void* data, char* fullname, char* name);
unsigned int GetFileDataLen(REFCACHE* ref);
unsigned int FillFileData(REFCACHE* ref, char* buf);

#endif /* _UPLOAD_H_ */
