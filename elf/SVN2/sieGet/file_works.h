#ifndef _FILE_WORKS_H_
#define _FILE_WORKS_H_

// ������������� ����
char * getSymbolicPath(const char * cFileName);
// ���������� ���������� ����� � ��������� � ���������
int is_file(const char * fname, const char * mask);
// ���������� ������� �����
int get_file_size(const char * fname);
// ���������, ���������� �� ���� �� ���������� ����
int is_file_exists(const char * fname);
// ������� �����, ���� ��� �� ����������
int make_dirs(const char * path);

#endif
