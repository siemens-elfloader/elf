#ifndef _FILE_WORKS_H_
#define _FILE_WORKS_H_

// ������������� ����
void getSymbolicPath(char * path, const char * cFileName);
// ��������� url ���� �� ����������
int Is_URL_File(const char *s);
// ���������� ������� �����
int get_file_size(const char * fname);
// ���������, ���������� �� ���� �� ���������� ����
int is_file_exists(const char * fname);
// ������� �����, ���� ��� �� ����������
int make_dir(const char * dir_fname);

#endif
