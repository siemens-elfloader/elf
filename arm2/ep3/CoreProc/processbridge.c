
#include <swilib.h>
#include <nu_swilib.h>
#include <spl/processbridge.h>
#include <spl/process.h>

void MopiBridgeMessenger();


void bridgeInit()
{
    KillGBSproc(BridgeMOPI_ID);
    CreateGBSproc(BridgeMOPI_ID, "NU2MOPI_IOBRIDGE", MopiBridgeMessenger, 0x24, 0);
}


void bridgeFini()
{
    KillGBSproc(BridgeMOPI_ID);
}



/* arguments manipulation code */

void * pack_args(int argc, ...)
{
    void **data = (void **)malloc((argc+3) * sizeof(void *));
    data[0] = (void*)argc;

    va_list va;
    va_start(va, argc);

    argc++;
    for(int i=1; i < argc; ++i)
    {
        data[i] = va_arg(va, void *);
    }

    return data;
}


uint32_t unpack_args(void *_data, void ***_args)
{
    uint32_t *data = _data;
    unsigned int cnt = *data;

    if(!cnt) {
        *_args = 0;
        return 0;
    }

    ++data;
    *_args = (void*)data;
    return cnt;
}




/* Bridge of mopi and nucleus */
void MopiBridgeMessenger()
{
    GBS_MSG msg;
    if (GBS_RecActDstMessage(&msg))
    {
        if (msg.msg == MOPI_THREAD_PROC)
        {
            if(msg.submess)
            {
                ThreadInfo *inf = (ThreadInfo *)msg.data0;

                uint32_t pcnt;
                void **args, *pret = 0, *arg_ptr = msg.data1;
                void *(*ptr_func)(void *, ...) = (void *(*)(void *, ...))msg.submess;

                /* нету параметров */
                if(!arg_ptr)  {
                    ptr_func(0);
                    pcnt = 0;

                } else
                    pcnt = unpack_args(arg_ptr, &args);

                switch(pcnt)
                {
                    case 0:
                        pret = ptr_func(0);
                        break;

                    case 1:
                        pret = ptr_func(args[0]);
                        break;

                    case 2:
                        pret = ptr_func(args[0], args[1]);
                        break;

                    case 3:
                        pret = ptr_func(args[0], args[1], args[2]);
                        break;

                    case 4:
                        pret = ptr_func(args[0], args[1], args[2], args[3]);
                        break;

                    case 5:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4]);
                        break;

                    case 6:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5]);
                        break;

                    case 7:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6]);
                        break;

                    case 8:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6]);
                        break;

                    case 9:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6]);
                        break;

                    case 10:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6], args[7], args[8], args[9]);
                        break;

                    case 11:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6], args[7], args[8], args[9], args[10]);
                        break;

                    case 12:
                        pret = ptr_func(args[0], args[1], args[2], args[3], args[4], args[5],
                                        args[6], args[7], args[8], args[9], args[10], args[11]);
                        break;

                    default:
                        ShowMSG(1, (int)"Bridge invalid param!");
                        break;
                }

                if(inf->sync) {
                    inf->ret = pret;
                    inf->loked = 0;
                    NU_Release_Semaphore(&inf->loker);
                }
                else {
                    free(arg_ptr);
                    free(inf);
                }
            }
        }
        else
        {
            GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,msg.pid_from,msg.msg,msg.submess);
        }
    }
}



void *BridgeMessageSend(void *func_ptr, int type, void *packed_args)
{
    ThreadInfo *i = (ThreadInfo*) malloc(sizeof(ThreadInfo));
    i->sync = (type == NU_SYNCHRONIZED_PROC);
    i->loked = 1;
    i->ret = 0;


    if(i->sync && NU_Create_Semaphore(&i->loker, "mopi", 0, NU_PRIORITY) != NU_SUCCESS) {
        ShowMSG(1, (int)"ProcB: Semaphore init failed");
        free(i);
        return 0;
    }

    GBS_SendMessage(BridgeMOPI_ID, MOPI_THREAD_PROC, func_ptr, i, packed_args);

    switch(type)
    {
        case NU_SYNCHRONIZED_PROC:
            NU_Obtain_Semaphore(&i->loker, NU_SUSPEND);
            break;

        case NU_ASYNC_PROC:
            /* in async mode return not support */
            return 0;
    }

    if(i->sync)
        NU_Delete_Semaphore(&i->loker);

    /* возвращаемое значение */
    void *ret = i->ret;

    /* больше не нужно оно */
    free(i);

    /* чистим стек аргументов */
    free(packed_args);

    /* возвращаем результат выполнения */
    return ret;
}

#if 0
    if(GBS_GetCurCepid() != 0xFFFF) {
        return (ret_type)func(__VA_ARGS__);
    }
#endif

#define SafeProcessRun(func, ret_type, run_type, args_cnt, ...)         \
    if(GBS_GetCurCepid() != (unsigned short)-1) {                                   \
        return (ret_type)func(__VA_ARGS__);                             \
    }                                                                   \
    void *args = pack_args(args_cnt, ##__VA_ARGS__);                      \
    void *retrn = BridgeMessageSend((void *)func, run_type, args);      \
    return (ret_type)retrn;

#ifndef UNUSED
#define UNUSED(x) ((void)x)
#endif

void my_test() {
    char d[64];
    sprintf(d, "CepID: %X\n", GBS_GetCurCepid());
    ShowMSG(1, (int)d);
}

void sync_test()
{
    SafeProcessRun(my_test, void, NU_SYNCHRONIZED_PROC, 0, 0);
}


int _ShowMSG(int type, int lang) {
    return ShowMSG(type, lang);
}

void _sync_ShowMSG(int type, int lang)
{
    SafeProcessRun(_ShowMSG, void, NU_SYNCHRONIZED_PROC, 2, type, lang);
}



void _async_ShowMSG(int type, int lang)
{
    SafeProcessRun(_ShowMSG, void, NU_ASYNC_PROC, 2, type, lang);
}


/* Files std */

int sync_open(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber)
{
    int __open(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber) {
        return _open(cFileName, iFileFlags, iFileMode, ErrorNumber);
    }
    SafeProcessRun(__open, int, NU_SYNCHRONIZED_PROC, 4, cFileName, iFileFlags, iFileMode, ErrorNumber);
}


int sync_read(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber)
{
    int __read(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber) {
        return _read(FileHandler, cBuffer, iByteCount, ErrorNumber);
    }

    SafeProcessRun(__read, int, NU_SYNCHRONIZED_PROC, 4, FileHandler, cBuffer, iByteCount, ErrorNumber);
}


int sync_write(int FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber)
{
    int __write(int FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber) {
        return _write(FileHandler, cBuffer, iByteCount, ErrorNumber);
    }

    SafeProcessRun(__write, int, NU_SYNCHRONIZED_PROC, 4, FileHandler, cBuffer, iByteCount, ErrorNumber);
}


int sync_close(int FileHandler, unsigned int *ErrorNumber)
{
    int __close(int FileHandler, unsigned int *ErrorNumber) {
        return _close(FileHandler, ErrorNumber);
    }
    SafeProcessRun(__close, int, NU_SYNCHRONIZED_PROC, 2, FileHandler, ErrorNumber);
}


int sync_flush(int FileHandler, unsigned int *ErrorNumber)
{
    int __flush(int f, unsigned int *ErrorNumber) { return _flush(f, ErrorNumber); }
    SafeProcessRun(__flush, int, NU_SYNCHRONIZED_PROC, 2, FileHandler, ErrorNumber);
}


int sync_truncate(int FileHandler, int length, unsigned int *errornumber)
{
    int __truncate(int FileHandler, int length, unsigned int *errornumber) {
        return _truncate(FileHandler, length, errornumber);
    }
    SafeProcessRun(__truncate, int, NU_SYNCHRONIZED_PROC, 3, FileHandler, length, errornumber);
}


int sync_unlink(const char *cFileName, unsigned int *errornumber)
{
    int __unlink() {
        return _unlink(cFileName, errornumber);
    }
    SafeProcessRun(_unlink, int, NU_SYNCHRONIZED_PROC, 2, cFileName, errornumber);
}


int sync_lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2)
{
    int __lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2) {
        return _lseek(FileHandler, offset, origin, ErrorNumber, ErrorNumber2);
    }
    SafeProcessRun(__lseek, int, NU_SYNCHRONIZED_PROC, 5, FileHandler, offset, origin, ErrorNumber, ErrorNumber2);
}


/* Dirs */

int sync_mkdir(const char * cDirectory, unsigned int *ErrorNumber)
{
    int __mkdir(const char * cDirectory, unsigned int *ErrorNumber) {
        return _mkdir(cDirectory, ErrorNumber);
    }
    SafeProcessRun(__mkdir, int, NU_SYNCHRONIZED_PROC, 2, cDirectory, ErrorNumber);
}


int sync_rmdir(const char * cDirectory, unsigned int *ErrorNumber)
{
    int __rmdir(const char * cDirectory, unsigned int *ErrorNumber) {
        return _rmdir(cDirectory, ErrorNumber);
    }
    SafeProcessRun(__rmdir, int, NU_SYNCHRONIZED_PROC, 2, cDirectory, ErrorNumber);
}


int sync_isdir(const char * cDirectory, unsigned int *ErrorNumber)
{
    int _isdir(const char * cDirectory, unsigned int *ErrorNumber) {
        return isdir(cDirectory, ErrorNumber);
    }

    SafeProcessRun(_isdir, int, NU_SYNCHRONIZED_PROC, 2, cDirectory, ErrorNumber);
}


/* Find files */

int sync_FindFirstFile(DIR_ENTRY *dentry, const char *mask, unsigned int *ErrorNumber)
{
    int _FindFirstFile(DIR_ENTRY *dentry, const char *mask, unsigned int *ErrorNumber) {
        return FindFirstFile(dentry, mask, ErrorNumber);
    }

    SafeProcessRun(_FindFirstFile, int, NU_SYNCHRONIZED_PROC, 3, dentry, mask, ErrorNumber);
}

int sync_FindNextFile(DIR_ENTRY *dentry, unsigned int *ErrorNumber)
{
    int _FindNextFile(DIR_ENTRY *dentry, unsigned int *ErrorNumber) {
        return FindNextFile(dentry, ErrorNumber);
    }
    SafeProcessRun(_FindNextFile, int, NU_SYNCHRONIZED_PROC, 2, dentry, ErrorNumber);
}

int sync_FindClose(DIR_ENTRY *dentry, unsigned int *ErrorNumber)
{
    int _FindClose(DIR_ENTRY *dentry, unsigned int *ErrorNumber) {
        return FindClose(dentry, ErrorNumber);
    }
    SafeProcessRun(_FindClose, int, NU_SYNCHRONIZED_PROC, 2, dentry, ErrorNumber);
}



/* File Stats && attributes */

int sync_GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber)
{
    int _GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber) {
        return GetFileStats(cFileName, StatBuffer, errornumber);
    }
    SafeProcessRun(_GetFileStats, int, NU_SYNCHRONIZED_PROC, 3, cFileName, StatBuffer, errornumber);
}


int sync_GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber)
{
    int _GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber) {
        return GetFileAttrib(cFileName, cAttribute, ErrorNumber);
    }

    SafeProcessRun(_GetFileAttrib, int, NU_SYNCHRONIZED_PROC, 3, cFileName, cAttribute, ErrorNumber);
}


int sync_SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber)
{
    int _SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber) {
        return SetFileAttrib(cFileName, cAttribute, ErrorNumber);
    }
    SafeProcessRun(_SetFileAttrib, int, NU_SYNCHRONIZED_PROC, 3, cFileName, cAttribute, ErrorNumber);
}





IMGHDR *sync_CreateIMGHDRFromPngFile(const char *file, int type)
{
    IMGHDR *crtimgfrompng(const char *file, int type) {
        return CreateIMGHDRFromPngFile(file, type);
    }
    SafeProcessRun(crtimgfrompng, IMGHDR *, NU_SYNCHRONIZED_PROC, 2, file, type);
}


int sync_setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber)
{
    int _setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber) {
        return setfilesize(FileHandler, iNewFileSize, ErrorNumber);
    }

    SafeProcessRun(_setfilesize, int, NU_SYNCHRONIZED_PROC, 3, FileHandler, iNewFileSize, ErrorNumber);
}


int sync_fmove(const char * SourceFileName, const char * DestFileName, unsigned int *ErrorNumber)
{
    int _fmove(const char * SourceFileName, const char * DestFileName, unsigned int *ErrorNumber) {
        return fmove(SourceFileName, DestFileName, ErrorNumber);
    }
    SafeProcessRun(_fmove, int, NU_SYNCHRONIZED_PROC, 3, SourceFileName, DestFileName, ErrorNumber);
}


Elf32_Exec *sync_elfopen(const char* filename)
{
    Elf32_Exec *_elfopen(const char* filename) {
        return elfopen(filename);
    }

    SafeProcessRun(_elfopen, Elf32_Exec *, NU_SYNCHRONIZED_PROC, 1, filename);
}


int sync_ExecuteFile(WSHDR *file, WSHDR *mime, void *d)
{
    int _ExecuteFile(WSHDR *file, WSHDR *mime, void *d) {
        return ExecuteFile(file, mime, d);
    }
    SafeProcessRun(_ExecuteFile, int, NU_SYNCHRONIZED_PROC, 3, file, mime, d);
}


int sync_PlayMelodyInMem(char Unk_0x11, void * MelAddr, int MelSize, int CepId, int Msg, int Unk_0)
{
    SafeProcessRun(PlayMelodyInMem, int, NU_SYNCHRONIZED_PROC, 6, Unk_0x11, MelAddr, MelSize, CepId, Msg, Unk_0);
}


int sync_PlayMelody_StopPlayback(int player_id)
{
    SafeProcessRun(PlayMelody_StopPlayback, int, NU_SYNCHRONIZED_PROC, 1, player_id);
}


int sync_Obs_CreateObject(int uid_in, int uid_out, int prio, int msg_callback, int emb4, int sync,unsigned int *ErrorNumber)
{
    SafeProcessRun(Obs_CreateObject, int, NU_SYNCHRONIZED_PROC, 7, uid_in, uid_out, prio, msg_callback, emb4, sync, ErrorNumber);
}


int sync_Obs_DestroyObject(HObj hObj)
{
    SafeProcessRun(Obs_DestroyObject, int, NU_SYNCHRONIZED_PROC, 1, hObj);
}


int sync_Obs_SetInput_File(HObj hObj, int unk_zero, WSHDR *path)
{
    SafeProcessRun(Obs_SetInput_File, int, NU_SYNCHRONIZED_PROC, 3, hObj, unk_zero, path);
}


int sync_Obs_Stop(HObj hObj)
{
    SafeProcessRun(Obs_Stop, int, NU_SYNCHRONIZED_PROC, 1, hObj);
}

