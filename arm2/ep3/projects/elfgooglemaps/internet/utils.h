#ifndef UTILS_H
#define UTILS_H
//internet
unsigned int gethostname(const char *name);
int get_headersize(char *buf);
//files
int is_file_exists(const char *file);
unsigned int get_file_size(const char *file);
#endif
