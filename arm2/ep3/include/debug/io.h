

#ifndef __DEBUG_IO_H__
#define __DEBUG_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

void __memory_debug_write_log(FILE *when);
FILE *__open_stdout_file(const char *mode);
FILE *__open_stderr_file(const char *mode);



#ifdef __cplusplus
}
#endif


#endif
