#include <swilib.h>
#include <conf_loader.h>
#include <cfg_items.h>

/** ��������� ������� ��� ���
 * (�) Z.Vova
 */

__CFG_BEGIN(0)

__root const CFG_HDR cfghdr0={CFG_UINT, "�����������", 100, 50000};
__root const unsigned int bufferizing = 500;


__root const CFG_HDR cfghdr1={CFG_UINT, "���������", 0, 0xFF};
__root const unsigned int task_priority = 120;

__root const CFG_HDR cfghdr2={CFG_UINT, "��������� ���������", 0,
#ifdef NEWSGOLD
15};
__root const unsigned int cfg_volume = 13;
#else
5};
__root const unsigned int cfg_volume = 5;
#endif

__root const CFG_HDR cfghdr3={CFG_UINT, "������� ������������ (��)", 1, 300};
__root const unsigned int bufferized_size = 30;

__root const CFG_HDR cfghdr4={CFG_UTF8_STRING, "Url", 1, 255};
__root const char internet_radio[256] = "http://urg.adamant.net:8080/radio-stilnoe48k";


__CFG_END(0)



/** ������ ������ �� config_data.c
  * Properties -> Advanced -> Use custom command to build this file
  * ������ �������
  * ��������� ���� $compiler $options -xc $includes -c $file -o $object -O0
*/
