
#define CASESENSITIVITY (0)
#define MAX_PATH_INZIP  (256)
#define WRITEBUFFERSIZE (8192)

int ExtractCurrentFile(unzFile uf, char* filePathInZip, char* extractDir, int usePaths, char* password);

// Common functions
void FreeZipInfo(ZIPINF* pzi);
int ReadZipInfo(ZIPINF* pzi);
int OpenZip(ZIPINF* pzi, char* zipFileName);
void CloseZip(ZIPINF* pzi);
int ExtractFile(ZIPINF* pzi, char* fname, char* extractDir, int usePaths);
int ExtractFileByID(ZIPINF* pzi, int id, char* extractDir, int usePaths);
int ExtractDir(ZIPINF* pzi, char* dname, char* extractDir, int usePaths);

// Tab functions
int IsZipOpened(int tab);
int IsInZip();
int OpenTabZip(int tab, char* zipFileName);
void CloseTabZip(int tab);
int FillZipFiles(int tab, char* subdname);

// Buffer functions
void ZipBufferExtractBegin();
int ZipBufferExtract(FN_ITM* pi, char* extractDir);
void ZipBufferExtractEnd();
