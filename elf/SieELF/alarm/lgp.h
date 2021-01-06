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
const char on[]="开";
const char off[]="关";
const char alarm_name[]="闹钟";
const char change[]="更改";
const char save[]="保存";
const char ok[]="确定";
const char *wd[7]={"一","二","三","四","五","六","日"};
const char *wd2[7]={"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
const char msg_dir[]="directory %s not created!";
const char msg_no_alarm_ring_elf[]="alarm_ring.elf 不存在!";
const char msg_no_images[]="fon.%s 或 icon.%s 不存在!";
const char no_melody[]="音乐不存在!";
#endif

#endif
