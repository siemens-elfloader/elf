#ifndef lgp_H
#define lgp_H

#ifdef EN
const char on[]="on";
const char off[]="off";
const char alarm_name[]="Alarm";
const char change[]="change";
const char save[]="save";
const char ok[]="ok";
const char *wd[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};
const char *wd2[7]={"Monday","Tuesday","Wednesday","Thesday","Friday","Saturday","Sunday"};
const char msg_dir[]="directory %s not created!";
const char msg_no_alarm_ring_elf[]="alarm_ring.elf not found!";
const char msg_no_images[]="fon.%s or icon.%s not found!";
const char no_melody[]="melody not found!";
#else
const char on[]="���.";
const char off[]="����.";
const char alarm_name[]="���������";
const char change[]="�����.";
const char save[]="����.";
const char ok[]="��";
const char *wd[7]={"��","��","��","��","��","��","��"};
const char *wd2[7]={"�����������","�������","�����","�������","�������","�������","�����������"};
const char msg_dir[]="���������� %s �� �������!";
const char msg_no_alarm_ring_elf[]="alarm_ring.elf �� ������!";
const char msg_no_images[]="fon.%s ��� icon.%s �� �������!";
const char no_melody[]="������� �� �������!";
#endif

#endif
