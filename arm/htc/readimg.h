

/****************************************************************************************************************************
iphone_saver.elf (readimg.h)
(�)Mirrr (http://init.org.ua, mirrr@ukr.net)
(�)2008 

����������� �������������� � ������������ �� ������ ���������� ����� �������� �� ������,
��� ��������:
 - �� �������� ��������� � ����� �����, � ����� ������ ���������� �� �������� ����� ���������.
 - ��� ����������� ��������� �� �������� ������� ����� http://init.org.ua, ������������ ���� ��� ��� ������ ������� �����.

��� ��������� �������� �������� ����������������; �� ������ �������������� �� �������� � (���) ��������, 
�������� ������� ��������� ������������� ���������� GNU (GNU GPL), ��������������� ������ �������� ����������������� 
������������ �����������; ���� �������� 2 ����������, ���� (�� ���� ����������) ����� ��������, ���������� �����.
��� ��������� ���������������� � ������� �� ��, ��� ��� �������� ��������, �� ��� �����-���� ��������, 
������� ��������������� �������� �������� ���� ����������� ��� ������������ �����. 

����������� ���������� � �������� ������������ ���������� GNU.

������ � ���� ���������� ������ ���������������� ��������� ��������� ������������� ���������� GNU, ���� �� 
�����������, �������� �� ���� � ���� �������� ����������������� ������������ ����������� 
(Free Software Foundation, Inc.), 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA 
***************************************************************************************************************************/






#include "swilib.h"

IMGHDR *read_pngimg(const char *buf);

IMGHDR *CreateImgr(int width, int height);

IMGHDR *CreateImgr16(int width, int height);