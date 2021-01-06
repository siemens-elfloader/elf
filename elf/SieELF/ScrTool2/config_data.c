#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include "scrtool.h"

__root const CFG_HDR cfghdr0={CFG_CHECKBOX, "快捷菜单", 0,1}; 
__root const uint TASK_ENA= 1;
//显示自定义文本
__root const CFG_HDR SCR11={CFG_LEVEL,"自定文本",1,0};
__root const CFG_HDR SCR1_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint TEXT_ENA=1;
__root const CFG_HDR SCR1_3={CFG_STR_GB,"文字",0,LEN-1};
__root const char TEXT_CP[LEN]="玫瑰工作室";
__root const CFG_HDR SCR1_2={CFG_COORDINATES,"位置",0,0};
__root const uint TEXT_X=0;
__root const uint TEXT_Y=60;
__root const CFG_HDR SCR1_4={CFG_COLOR,"颜色",0,0};
__root const char TEXT_CS[4]={255,255,255,100};
__root const CFG_HDR SCR1_5={CFG_COLOR,"边色",0,0};
__root const char TEXT_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR1_6={CFG_UINT,"对齐",0,3};
__root const uint TEXT_T=2;
__root const CFG_HDR SCR1_7={CFG_UINT,"字体",0,16};
__root const uint TEXT_FT=0;
#else
__root const CFG_HDR SCR1_6={CFG_CBOX,"对齐",0,4};
__root const uint TEXT_T=2;
__root const CFG_CBOX_ITEM BOX14[4]={AgainCN};
__root const CFG_HDR SCR1_7={CFG_CBOX,"字体",0,17};
__root const uint TEXT_FT=0;
__root const CFG_CBOX_ITEM BOX15[17]={FontCN};
#endif
__root const CFG_HDR SCR10={CFG_LEVEL,"",0,0};
//菜单配置信息//开始按键配置
__root const CFG_HDR mBAR1={CFG_LEVEL,"全局参数",1,0};
__root const CFG_HDR BAR_0={CFG_CHECKBOX, "菜单描述", 0,2}; 
__root const uint DEST_ENA=1;
__root const CFG_HDR SCR={CFG_CBOX, "启用屏显", 0,4}; 
__root const uint INFO_ENA= 2;
__root const CFG_CBOX_ITEM BOX01[4] = {ScrMode};
__root const CFG_HDR BAR_3={CFG_CBOX,"关闭菜单",0,7};
__root const uint CALL_BTN=6;
__root const CFG_CBOX_ITEM BOX02[7] = {KeyName};
__root const CFG_HDR BAR_1={CFG_UINT,"刷屏(秒)",0,50};
__root const uint REFRESH=5;
__root const CFG_HDR BAR_2={CFG_UINT,"自关(秒)",0,20};
__root const uint AUTO_CLOSE=3;
__root const CFG_HDR BAR_5={CFG_CBOX,"调用模式",0,3};
__root const uint MODE_KBD=0;
__root const CFG_CBOX_ITEM BOX03[3]={"短按","弹起","长按"};
__root const CFG_HDR BAR_7={CFG_UINT, "垂直偏移",0,400};
__root const uint OFFSET=0;
__root const CFG_HDR PSize={CFG_UINT, "图标尺寸",0,33};
__root const uint PicSize=30;
__root const CFG_HDR BAR_8={CFG_COLOR,"文本颜色",0,0};
__root const char ATEXT_CS[4]={255,255,255,100};
#ifdef SCR_LITE
__root const CFG_HDR BAR_9={CFG_UINT, "文本字号",0,16};
__root const uint ATEXT_FT=8;
#else
__root const CFG_HDR BAR_9={CFG_CBOX, "文本字体",0,17};
__root const uint ATEXT_FT=8;
__root const CFG_CBOX_ITEM BOX04[17]={FontCN};
#endif
__root const CFG_HDR BAR_A={CFG_COLOR,"边框颜色",0,0};
__root const char PBDCol[4]={255,255,255,100};
__root const CFG_HDR BAR_B={CFG_COLOR,"背景颜色",0,0};
__root const char PBGCol[4]={0,0,0,100};
__root const CFG_HDR BAR_C={CFG_COLOR,"图标边色",0,0};
__root const char BBDCol[4]={255,255,255,100};
__root const CFG_HDR BAR_J={CFG_CHECKBOX, "显示扩展名", 0,2}; 
__root const uint SHOW_EXT= 0;
__root const CFG_HDR mBAR0={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mMENU1={CFG_LEVEL,"菜单图标",1,0};
__root const CFG_HDR BAR_I={CFG_STR_UTF8,"关机",0,SLEN-1};
__root const char AITO[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\to.png";
__root const CFG_HDR BAR_H={CFG_STR_UTF8,"重启",0,SLEN-1};
__root const char AIRT[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\rt.png";
__root const CFG_HDR BAR_G={CFG_STR_UTF8,"锁键",0,SLEN-1};
__root const char AILK[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\lk.png";
__root const CFG_HDR BAR_E={CFG_STR_UTF8,"设置",0,SLEN-1};
__root const char AIST[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\st.png";
__root const CFG_HDR BAR_F={CFG_STR_UTF8,"空白",3,SLEN-1};
__root const char AINO[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\no.png";
__root const CFG_HDR mMENU0={CFG_LEVEL,"",0,0};
//---------------------------------------
//程序设置
__root const CFG_HDR mAPP1={CFG_LEVEL,"菜单列表",1,0};
//-------------------------------------------------
__root const CFG_HDR mA041={CFG_LEVEL,"菜单01",1,0};
__root const CFG_HDR A04_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT04=3; 
__root const CFG_CBOX_ITEM BOX05[ELEN]={ETycn};
__root const CFG_HDR A04_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN04[LEN]="其它配置";
__root const CFG_HDR A04_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI04[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\bc.png";
__root const CFG_HDR A04_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF04[SLEN]=DEFAULT_DISK ":\\ZBin\\ETC\\*.bcfg";
__root const CFG_HDR mA040={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA051={CFG_LEVEL,"菜单02",1,0};
__root const CFG_HDR A05_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT05=3; 
__root const CFG_CBOX_ITEM BOX06[ELEN]={ETycn};
__root const CFG_HDR A05_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN05[LEN]="应用软件";
__root const CFG_HDR A05_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI05[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\elf.png";
__root const CFG_HDR A05_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF05[SLEN]=DEFAULT_DISK ":\\ZBin\\APP\\*.elf";
__root const CFG_HDR mA050={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA061={CFG_LEVEL,"菜单03",1,0};
__root const CFG_HDR A06_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT06=0; 
__root const CFG_CBOX_ITEM BOX07[ELEN]={ETycn};
__root const CFG_HDR A06_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN06[LEN]=NoName;
__root const CFG_HDR A06_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI06[SLEN]="";
__root const CFG_HDR A06_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF06[SLEN]="";
__root const CFG_HDR mA060={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA071={CFG_LEVEL,"菜单04",1,0};
__root const CFG_HDR A07_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT07=0; 
__root const CFG_CBOX_ITEM BOX08[ELEN]={ETycn};
__root const CFG_HDR A07_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN07[LEN]=NoName;
__root const CFG_HDR A07_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI07[SLEN]="";
__root const CFG_HDR A07_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF07[SLEN]="";
__root const CFG_HDR mA070={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA081={CFG_LEVEL,"菜单05",1,0};
__root const CFG_HDR A08_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT08=0; 
__root const CFG_CBOX_ITEM BOXA08[ELEN]={ETycn};
__root const CFG_HDR A08_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN08[LEN]=NoName;
__root const CFG_HDR A08_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI08[SLEN]="";
__root const CFG_HDR A08_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF08[SLEN]="";
__root const CFG_HDR mA080={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA091={CFG_LEVEL,"菜单06",1,0};
__root const CFG_HDR A09_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT09=0; 
__root const CFG_CBOX_ITEM BOX09[ELEN]={ETycn};
__root const CFG_HDR A09_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN09[LEN]=NoName;
__root const CFG_HDR A09_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI09[SLEN]="";
__root const CFG_HDR A09_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF09[SLEN]="";
__root const CFG_HDR mA090={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA101={CFG_LEVEL,"菜单07",1,0};
__root const CFG_HDR A10_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT10=0; 
__root const CFG_CBOX_ITEM BOX10[ELEN]={ETycn};
__root const CFG_HDR A10_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN10[LEN]=NoName;
__root const CFG_HDR A10_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI10[SLEN]="";
__root const CFG_HDR A10_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF10[SLEN]="";
__root const CFG_HDR mA100={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA111={CFG_LEVEL,"菜单08",1,0};
__root const CFG_HDR A11_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT11=0; 
__root const CFG_CBOX_ITEM BOX11[ELEN]={ETycn};
__root const CFG_HDR A11_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN11[LEN]=NoName;
__root const CFG_HDR A11_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI11[SLEN]="";
__root const CFG_HDR A11_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF11[SLEN]="";
__root const CFG_HDR mA110={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA121={CFG_LEVEL,"菜单09",1,0};
__root const CFG_HDR A12_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT12=0; 
__root const CFG_CBOX_ITEM BOX12[ELEN]={ETycn};
__root const CFG_HDR A12_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN12[LEN]=NoName;
__root const CFG_HDR A12_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI12[SLEN]="";
__root const CFG_HDR A12_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF12[SLEN]="";
__root const CFG_HDR mA120={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR mA131={CFG_LEVEL,"菜单10",1,0};
__root const CFG_HDR A13_4 ={CFG_CBOX,"类型", 0,ELEN}; 
__root const uint AT13=0; 
__root const CFG_CBOX_ITEM BOX13[ELEN]={ETycn};
__root const CFG_HDR A13_1={CFG_STR_GB,"描述",0,LEN-1};
__root const char AN13[LEN]=NoName;
__root const CFG_HDR A13_2={CFG_STR_UTF8,"图标",0,SLEN-1};
__root const char AI13[SLEN]="";
__root const CFG_HDR A13_3={CFG_STR_UTF8,"调用",0,SLEN-1};
__root const char AF13[SLEN]="";
__root const CFG_HDR mA130={CFG_LEVEL,"",0,0};
__root const CFG_HDR mAPP0={CFG_LEVEL,"",0,0};
//TextInfo begin
__root const CFG_HDR SCR1={CFG_LEVEL,"系统屏显",1,0};

//显示温度
__root const CFG_HDR SCR21={CFG_LEVEL,"温度探测",1,0};
__root const CFG_HDR SCR2_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint TEMP_ENA=1;
__root const CFG_HDR SCR2_2={CFG_COORDINATES,"位置",0,0};
__root const uint TEMP_X=3;
__root const uint TEMP_Y=25;
__root const CFG_HDR SCR2_3={CFG_COLOR,"颜色",0,0};
__root const char TEMP_CS[4]={255,255,255,100};
__root const CFG_HDR SCR2_4={CFG_COLOR,"边色",0,0};
__root const char TEMP_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR2_5={CFG_UINT,"对齐",0,3};
__root const uint TEMP_T=1;
__root const CFG_HDR SCR2_6={CFG_UINT,"字体",0,16};
__root const uint TEMP_FT=8;
#else
__root const CFG_HDR SCR2_5={CFG_CBOX,"对齐",0,4};
__root const uint TEMP_T=1;
__root const CFG_CBOX_ITEM BOX22[4]={AgainCN};
__root const CFG_HDR SCR2_6={CFG_CBOX,"字体",0,17};
__root const uint TEMP_FT=8;
__root const CFG_CBOX_ITEM BOX21[17]={FontCN};
#endif
__root const CFG_HDR SCR20={CFG_LEVEL,"",0,0};
//显示电压
__root const CFG_HDR SCR31={CFG_LEVEL,"电池电量",1,0};
__root const CFG_HDR SCR3_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint VOLT_ENA=1;
__root const CFG_HDR SCR3_2={CFG_CBOX, "样式", 0, 2};
__root const uint VOLT_M=1;
__root const CFG_CBOX_ITEM BOX33[2]={"电压值","百分比"};
__root const CFG_HDR SCR3_3={CFG_COORDINATES,"位置",0,0};
__root const uint VOLT_X=175;
__root const uint VOLT_Y=25;
__root const CFG_HDR SCR3_4={CFG_COLOR,"颜色",0,0};
__root const char VOLT_CS[4]={255,255,255,100};
__root const CFG_HDR SCR3_5={CFG_COLOR,"边色",0,0};
__root const char VOLT_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR3_6={CFG_UINT,"对齐",0,3};
__root const uint VOLT_T=3;
__root const CFG_HDR SCR3_7={CFG_UINT,"字体",0,16};
__root const uint VOLT_FT=8;
#else
__root const CFG_HDR SCR3_6={CFG_CBOX,"对齐",0,4};
__root const uint VOLT_T=3;
__root const CFG_CBOX_ITEM BOX32[4]={AgainCN};
__root const CFG_HDR SCR3_7={CFG_CBOX,"字体",0,17};
__root const uint VOLT_FT=8;
__root const CFG_CBOX_ITEM BOX31[17]={FontCN};
#endif
__root const CFG_HDR SCR30={CFG_LEVEL,"",0,0};
//显示内存
__root const CFG_HDR SCR41={CFG_LEVEL,"可用内存",1,0};
__root const CFG_HDR SCR4_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint RAMT_ENA=1;
__root const CFG_HDR SCR4_2={CFG_COORDINATES,"位置",0,0};
__root const uint RAMT_X=0;
__root const uint RAMT_Y=295;
__root const CFG_HDR SCR4_3={CFG_COLOR,"颜色",0,0};
__root const char RAMT_CS[4]={255,255,255,100};
__root const CFG_HDR SCR4_4={CFG_COLOR,"边色",0,0};
__root const char RAMT_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR4_5={CFG_UINT,"对齐",0,3};
__root const uint RAMT_T=1;
__root const CFG_HDR SCR4_6={CFG_UINT,"字体",0,16};
__root const uint RAMT_FT=8;
#else
__root const CFG_HDR SCR4_5={CFG_CBOX,"对齐",0,4};
__root const uint RAMT_T=1;
__root const CFG_CBOX_ITEM BOX42[4]={AgainCN};
__root const CFG_HDR SCR4_6={CFG_CBOX,"字体",0,17};
__root const uint RAMT_FT=8;
__root const CFG_CBOX_ITEM BOX41[17]={FontCN};
#endif
__root const CFG_HDR SCR40={CFG_LEVEL,"",0,0};
//NET begin
__root const CFG_HDR SCR51={CFG_LEVEL,"信号强度",1,0};
__root const CFG_HDR SCR5_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint NETI_ENA=0;
__root const CFG_HDR SCR5_2={CFG_COORDINATES,"位置",0,0};
__root const uint NETI_X=0;
__root const uint NETI_Y=50;
__root const CFG_HDR SCR5_3={CFG_COLOR,"颜色",0,0};
__root const char NETI_CS[4]={255,255,255,100};
__root const CFG_HDR SCR5_4={CFG_COLOR,"边色",0,0};
__root const char NETI_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR5_5={CFG_UINT,"对齐",0,3};
__root const uint NETI_T=0;
__root const CFG_HDR SCR5_6={CFG_UINT,"字体",0,16};
__root const uint NETI_FT=8;
#else
__root const CFG_HDR SCR5_5={CFG_CBOX,"对齐",0,4};
__root const uint NETI_T=0;
__root const CFG_CBOX_ITEM BOXA2[4]={AgainCN};
__root const CFG_HDR SCR5_6={CFG_CBOX,"字体",0,17};
__root const uint NETI_FT=8;
__root const CFG_CBOX_ITEM BOXA1[17]={FontCN};
#endif
__root const CFG_HDR SCR50={CFG_LEVEL,"",0,0};
//-----------------------------------
__root const CFG_HDR SCR61={CFG_LEVEL,"基站号码",1,0};
__root const CFG_HDR SCR6_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint MGPS_ENA=0;
__root const CFG_HDR SCR6_2={CFG_COORDINATES,"位置",0,0};
__root const uint MGPS_X=0;
__root const uint MGPS_Y=100;
__root const CFG_HDR SCR6_3={CFG_COLOR,"颜色",0,0};
__root const char MGPS_CS[4]={255,255,255,100};
__root const CFG_HDR SCR6_4={CFG_COLOR,"边色",0,0};
__root const char MGPS_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR6_5={CFG_UINT,"对齐",0,3};
__root const uint MGPS_T=2;
__root const CFG_HDR SCR6_6={CFG_UINT,"字体",0,16};
__root const uint MGPS_FT=8;
#else
__root const CFG_HDR SCR6_5={CFG_CBOX,"对齐",0,4};
__root const uint MGPS_T=2;
__root const CFG_CBOX_ITEM BOXTGPS2[4]={AgainCN};
__root const CFG_HDR SCR6_6={CFG_CBOX,"字体",0,17};
__root const uint MGPS_FT=8;
__root const CFG_CBOX_ITEM BOXTGPS1[17]={FontCN};
#endif
__root const CFG_HDR SCR60={CFG_LEVEL,"",0,0};
//NET end
//GPRS begin
__root const CFG_HDR SCR71={CFG_LEVEL,"网络流量",1,0};
__root const CFG_HDR SCR7_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint GPRS_ENA=0;
__root const CFG_HDR SCR7_2={CFG_COORDINATES,"位置",0,0};
__root const uint GPRS_X=0;
__root const uint GPRS_Y=210;
__root const CFG_HDR SCR7_3={CFG_COLOR,"颜色",0,0};
__root const char GPRS_CS[4]={255,255,255,100};
__root const CFG_HDR SCR7_4={CFG_COLOR,"边色",0,0};
__root const char GPRS_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR7_5={CFG_UINT,"对齐",0,3};
__root const uint GPRS_T=0;
__root const CFG_HDR SCR7_6={CFG_UINT,"字体",0,16};
__root const uint GPRS_FT=8;
#else
__root const CFG_HDR SCR7_5={CFG_CBOX,"对齐",0,4};
__root const uint GPRS_T=0;
__root const CFG_CBOX_ITEM BOXC2[4]={AgainCN};
__root const CFG_HDR SCR7_6={CFG_CBOX,"字体",0,17};
__root const uint GPRS_FT=8;
__root const CFG_CBOX_ITEM BOXC1[17]={FontCN};
#endif
__root const CFG_HDR SCR70={CFG_LEVEL,"",0,0};
//GPRS end
//CPULoad begin
__root const CFG_HDR SCR81={CFG_LEVEL,"内核状态",1,0};
__root const CFG_HDR SCR8_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CPUI_ENA=0;
__root const CFG_HDR SCR8_2={CFG_COORDINATES,"位置",0,0};
__root const uint CPUI_X=90;
__root const uint CPUI_Y=293;
__root const CFG_HDR SCR8_3={CFG_COLOR,"颜色",0,0};
__root const char CPUI_CS[4]={255,255,255,100};
__root const CFG_HDR SCR8_6={CFG_COLOR,"边色",0,0};
__root const char CPUI_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR SCR8_7={CFG_UINT,"对齐",0,3};
__root const uint CPUI_T=0;
__root const CFG_HDR SCR8_4={CFG_UINT,"字体",0,16};
__root const uint CPUI_FT=8;
#else
__root const CFG_HDR SCR8_7={CFG_CBOX,"对齐",0,4};
__root const uint CPUI_T=0;
__root const CFG_CBOX_ITEM BOXD2[4]={AgainCN};
__root const CFG_HDR SCR8_4={CFG_CBOX,"字体",0,17};
__root const uint CPUI_FT=8;
__root const CFG_CBOX_ITEM BOXD1[17]={FontCN};
#endif
__root const CFG_HDR SCR80={CFG_LEVEL,"",0,0};
//CPULoad end
__root const CFG_HDR SCR0={CFG_LEVEL,"",0,0};
//TextInfo end
//开始阳历屏显
__root const CFG_HDR NEW1={CFG_LEVEL,"日历屏显",1,0};
//显示星期
__root const CFG_HDR SCRB1={CFG_LEVEL,"公历星期",1,0};
__root const CFG_HDR SCRB_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint WEEK_ENA=1;
__root const CFG_HDR SCRB_2={CFG_COORDINATES,"位置",0,0};
__root const uint WEEK_X=90;
__root const uint WEEK_Y=25;
__root const CFG_HDR SCRB_3={CFG_COLOR,"颜色",0,0};
__root const char WEEK_CS[4]={255,255,255,100};
__root const CFG_HDR SCRB_6={CFG_COLOR,"边色",0,0};
__root const char WEEK_CB[4]={144,144,144,48};
__root const CFG_HDR SCRB_5={CFG_CBOX,"格式",0,6};
__root const int WEEK_FMT=4;
__root const CFG_CBOX_ITEM BOX52[6]={WeekFmt};
#ifdef SCR_LITE
__root const CFG_HDR SCRB_7={CFG_UINT,"对齐",0,3};
__root const uint WEEK_T=2;
__root const CFG_HDR SCRB_4={CFG_UINT,"字体",0,16};
__root const uint WEEK_FT=8;
#else
__root const CFG_HDR SCRB_7={CFG_CBOX,"对齐",0,4};
__root const uint WEEK_T=2;
__root const CFG_CBOX_ITEM BOX53[4]={AgainCN};
__root const CFG_HDR SCRB_4={CFG_CBOX,"字体",0,17};
__root const uint WEEK_FT=8;
__root const CFG_CBOX_ITEM BOX51[17]={FontCN};
#endif
__root const CFG_HDR SCRB0={CFG_LEVEL,"",0,0};
//显示时间
__root const CFG_HDR SCRC1={CFG_LEVEL,"公历时间",1,0};
__root const CFG_HDR SCRC_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint TIME_ENA=1;
__root const CFG_HDR SCRC_2={CFG_COORDINATES,"位置",0,0};
__root const uint TIME_X=0;
__root const uint TIME_Y=130;
__root const CFG_HDR SCRC_3={CFG_COLOR,"颜色",0,0};
__root const char TIME_CS[4]={255,255,255,100};
__root const CFG_HDR SCRC_6={CFG_COLOR,"边色",0,0};
__root const char TIME_CB[4]={144,144,144,48};
__root const CFG_HDR SCRC_5={CFG_CBOX,"格式",0,6};
__root const int TIME_FMT=1;
__root const CFG_CBOX_ITEM BOX72[6]={TimeFmt};
#ifdef SCR_LITE
__root const CFG_HDR SCRC_7={CFG_UINT,"对齐",0,3};
__root const uint TIME_T=2;
__root const CFG_HDR SCRC_4={CFG_UINT,"字体",0,16};
__root const uint TIME_FT=3;
#else
__root const CFG_HDR SCRC_7={CFG_CBOX,"对齐",0,4};
__root const uint TIME_T=2;
__root const CFG_CBOX_ITEM BOX73[4]={AgainCN};
__root const CFG_HDR SCRC_4={CFG_CBOX,"字体",0,17};
__root const uint TIME_FT=3;
__root const CFG_CBOX_ITEM BOX71[17]={FontCN};
#endif
__root const CFG_HDR SCRC0={CFG_LEVEL,"",0,0};
//显示日期
__root const CFG_HDR SCRD1={CFG_LEVEL,"公历日期",1,0};
__root const CFG_HDR SCRD_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint DATE_ENA=1;
__root const CFG_HDR SCRD_2={CFG_COORDINATES,"位置",0,0};
__root const uint DATE_X=85;
__root const uint DATE_Y=295;
__root const CFG_HDR SCRD_3={CFG_COLOR,"颜色",0,0};
__root const char DATE_CS[4]={255,255,255,100};
__root const CFG_HDR SCRD_6={CFG_COLOR,"边色",0,0};
__root const char DATE_CB[4]={144,144,144,48};
__root const CFG_HDR SCRD_5={CFG_CBOX,"格式",0,10};
__root const int DATE_FMT=7;
__root const CFG_CBOX_ITEM BOX62[10]={DateFmt};
#ifdef SCR_LITE
__root const CFG_HDR SCRD_7={CFG_UINT,"对齐",0,3};
__root const uint DATE_T=0;
__root const CFG_HDR SCRD_4={CFG_UINT,"字体",0,16};
__root const uint DATE_FT=8;
#else
__root const CFG_HDR SCRD_7={CFG_CBOX,"对齐",0,4};
__root const uint DATE_T=0;
__root const CFG_CBOX_ITEM BOX63[4]={AgainCN};
__root const CFG_HDR SCRD_4={CFG_CBOX,"字体",0,17};
__root const uint DATE_FT=8;
__root const CFG_CBOX_ITEM BOX61[17]={FontCN};
#endif
__root const CFG_HDR SCRD0={CFG_LEVEL,"",0,0};
//显示农历年份
__root const CFG_HDR SCRA1={CFG_LEVEL,"阴历年柱",1,0};
__root const CFG_HDR SCRA_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CHSY_ENA=1;
__root const CFG_HDR SCRA_2={CFG_COORDINATES,"位置",0,0};
__root const uint CHSY_X=0;
__root const uint CHSY_Y=270;
/*__root const CFG_HDR SCRA_3={CFG_COLOR,"颜色",0,0};
__root const char CHSY_CS[4]={0,0,255,75};
__root const CFG_HDR SCRA_4={CFG_COLOR,"边色",0,0};
__root const char CHSY_CB[4]={255,255,255,100};*/
#ifdef SCR_LITE
__root const CFG_HDR SCRA_7={CFG_UINT,"对齐",0,3};
__root const uint CHSY_T=3;
//__root const CFG_HDR SCRA_5={CFG_UINT,"字体",0,16};
//__root const uint CHSY_FT=8;
#else
__root const CFG_HDR SCRA_7={CFG_CBOX,"对齐",0,4};
__root const uint CHSY_T=3;
__root const CFG_CBOX_ITEM BOX82[4]={AgainCN};
//__root const CFG_HDR SCRA_5={CFG_CBOX,"字体",0,17};
//__root const uint CHSY_FT=8;
//__root const CFG_CBOX_ITEM BOX81[17]={FontCN};
#endif
__root const CFG_HDR SCRA0={CFG_LEVEL,"",0,0};
//显示农历月柱
__root const CFG_HDR SCRM1={CFG_LEVEL,"阴历月柱",1,0};
__root const CFG_HDR SCRM_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CHSM_ENA=1;
__root const CFG_HDR SCRM_2={CFG_COORDINATES,"位置",0,0};
__root const uint CHSM_X=0;
__root const uint CHSM_Y=245;
/*__root const CFG_HDR SCRM_3={CFG_COLOR,"颜色",0,0};
__root const char CHSM_CS[4]={0,0,255,75};
__root const CFG_HDR SCRM_4={CFG_COLOR,"边色",0,0};
__root const char CHSM_CB[4]={255,255,255,100};*/
#ifdef SCR_LITE
__root const CFG_HDR SCRM_7={CFG_UINT,"对齐",0,3};
__root const uint CHSM_T=3;
//__root const CFG_HDR SCRM_5={CFG_UINT,"字体",0,16};
//__root const uint CHSM_FT=8;
#else
__root const CFG_HDR SCRM_7={CFG_CBOX,"对齐",0,4};
__root const uint CHSM_T=3;
__root const CFG_CBOX_ITEM BOX83[4]={AgainCN};
//__root const CFG_HDR SCRM_5={CFG_CBOX,"字体",0,17};
//__root const uint CHSM_FT=8;
//__root const CFG_CBOX_ITEM BOX84[17]={FontCN};
#endif
__root const CFG_HDR SCRM0={CFG_LEVEL,"",0,0};
//显示农历农历年月日节气
__root const CFG_HDR SCR91={CFG_LEVEL,"阴历日柱",1,0};
__root const CFG_HDR SCR9_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CHSD_ENA=1;
__root const CFG_HDR SCR9_2={CFG_COORDINATES,"位置",0,0};
__root const uint CHSD_X=0;
__root const uint CHSD_Y=270;
/*__root const CFG_HDR SCR9_3={CFG_COLOR,"颜色",0,0};
__root const char CHSD_CS[4]={0,0,255,75};
__root const CFG_HDR SCR9_4={CFG_COLOR,"边色",0,0};
__root const char CHSD_CB[4]={255,255,255,100};*/
#ifdef SCR_LITE
__root const CFG_HDR SCR9_7={CFG_UINT,"对齐",0,3};
__root const uint CHSD_T=1;
//__root const CFG_HDR SCR9_5={CFG_UINT,"字体",0,16};
//__root const uint CHSD_FT=8;
#else
__root const CFG_HDR SCR9_7={CFG_CBOX,"对齐",0,4};
__root const uint CHSD_T=1;
__root const CFG_CBOX_ITEM BOX92[4]={AgainCN};
//__root const CFG_HDR SCR9_5={CFG_CBOX,"字体",0,17};
//__root const uint CHSD_FT=8;
//__root const CFG_CBOX_ITEM BOX91[17]={FontCN};
#endif
__root const CFG_HDR SCR90={CFG_LEVEL,"",0,0};
//显示农历时辰
__root const CFG_HDR CHSH1={CFG_LEVEL,"阴历时柱",1,0};
__root const CFG_HDR CHSH_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CHSH_ENA=1;
__root const CFG_HDR CHSH_2={CFG_COORDINATES,"位置",0,0};
__root const uint CHSH_X=0;
__root const uint CHSH_Y=245;
/*__root const CFG_HDR CHSH_3={CFG_COLOR,"颜色",0,0};
__root const char CHSH_CS[4]={0,0,255,75};
__root const CFG_HDR CHSH_4={CFG_COLOR,"边色",0,0};
__root const char CHSH_CB[4]={255,255,255,100};*/
#ifdef SCR_LITE
__root const CFG_HDR CHSH_7={CFG_UINT,"对齐",0,3};
__root const uint CHSH_T=1;
//__root const CFG_HDR CHSH_5={CFG_UINT,"字体",0,16};
//__root const uint CHSH_FT=8;
#else
__root const CFG_HDR CHSH_7={CFG_CBOX,"对齐",0,4};
__root const uint CHSH_T=1;
__root const CFG_CBOX_ITEM BOXTH92[4]={AgainCN};
//__root const CFG_HDR CHSH_5={CFG_CBOX,"字体",0,17};
//__root const uint CHSH_FT=8;
//__root const CFG_CBOX_ITEM BOXTH91[17]={FontCN};
#endif
__root const CFG_HDR CHSH0={CFG_LEVEL,"",0,0};
//显示农历日期
__root const CFG_HDR SCMD1={CFG_LEVEL,"阴历日期",1,0};
__root const CFG_HDR SCMD_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint CHMD_ENA=1;
__root const CFG_HDR SCMD_2={CFG_COORDINATES,"位置",0,0};
__root const uint CHMD_X=0;
__root const uint CHMD_Y=295;
/*__root const CFG_HDR SCMD_3={CFG_COLOR,"颜色",0,0};
__root const char CHMD_CS[4]={0,0,255,75};
__root const CFG_HDR SCMD_4={CFG_COLOR,"边色",0,0};
__root const char CHMD_CB[4]={255,255,255,100};*/
#ifdef SCR_LITE
__root const CFG_HDR SCMD_7={CFG_UINT,"对齐",0,3};
__root const uint CHMD_T=3;
//__root const CFG_HDR SCMD_5={CFG_UINT,"字体",0,16};
//__root const uint CHMD_FT=8;
#else
__root const CFG_HDR SCMD_7={CFG_CBOX,"对齐",0,4};
__root const uint CHMD_T=3;
__root const CFG_CBOX_ITEM BOX85[4]={AgainCN};
//__root const CFG_HDR SCMD_5={CFG_CBOX,"字体",0,17};
//__root const uint CHMD_FT=8;
//__root const CFG_CBOX_ITEM BOX86[17]={FontCN};
#endif
__root const CFG_HDR SCMD0={CFG_LEVEL,"",0,0};

__root const CFG_HDR SCRA_3={CFG_COLOR,"阴历颜色",0,0};
__root const char CHSY_CS[4]={255,255,255,100};
__root const CFG_HDR SCRA_4={CFG_COLOR,"阴历边色",0,0};
__root const char CHSY_CB[4]={144,144,144,48};
#ifdef SCR_LITE
__root const CFG_HDR CHSH_5={CFG_UINT,"阴历字体",0,16};
__root const uint CHSY_FT=8;
#else
__root const CFG_HDR CHSH_5={CFG_CBOX,"阴历字体",0,17};
__root const uint CHSY_FT=8;
__root const CFG_CBOX_ITEM BOXTH91[17]={FontCN};
#endif
//结束日历屏显
__root const CFG_HDR NEW0={CFG_LEVEL,"",0,0};
//阳历节日选项设置
__root const CFG_HDR BIR1={CFG_LEVEL,"节日屏显",1,0};
__root const CFG_HDR NBIR1={CFG_LEVEL,"公历节日",1,0};
__root const CFG_HDR NBIR_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint NBIR_ENA=1;
__root const CFG_HDR NBIR_2={CFG_COORDINATES,"位置",0,0};
__root const uint NBIR_X=0;
__root const uint NBIR_Y=180;
__root const CFG_HDR NBIR_3={CFG_COLOR,"颜色",0,0};
__root const char NBIR_CS[4]={255,0,0,100};
__root const CFG_HDR NBIR_4={CFG_COLOR,"边色",0,0};
__root const char NBIR_CB[4]={255,255,255,100};
#ifdef SCR_LITE
__root const CFG_HDR NBIR_7={CFG_UINT,"对齐",0,3};
__root const uint NBIR_T=2;
__root const CFG_HDR NBIR_5={CFG_UINT,"字体",0,16};
__root const uint NBIR_FT=8;
#else
__root const CFG_HDR NBIR_7={CFG_CBOX,"对齐",0,4};
__root const uint NBIR_T=2;
__root const CFG_CBOX_ITEM BOXNBIR2[4]={AgainCN};
__root const CFG_HDR NBIR_5={CFG_CBOX,"字体",0,17};
__root const uint NBIR_FT=8;
__root const CFG_CBOX_ITEM BOXNBIR1[17]={FontCN};
#endif
__root const CFG_HDR NBIR0={CFG_LEVEL,"",0,0};
//阴历节日选项设置
__root const CFG_HDR OBIR1={CFG_LEVEL,"阴历节日",1,0};
__root const CFG_HDR OBIR_1={CFG_CHECKBOX, "屏显", 0, 1};
__root const uint OBIR_ENA=1;
__root const CFG_HDR OBIR_2={CFG_COORDINATES,"位置",0,0};
__root const uint OBIR_X=0;
__root const uint OBIR_Y=210;
__root const CFG_HDR OBIR_3={CFG_COLOR,"颜色",0,0};
__root const char OBIR_CS[4]={0,255,0,100};
__root const CFG_HDR OBIR_4={CFG_COLOR,"边色",0,0};
__root const char OBIR_CB[4]={255,255,255,100};
#ifdef SCR_LITE
__root const CFG_HDR OBIR_7={CFG_UINT,"对齐",0,3};
__root const uint OBIR_T=2;
__root const CFG_HDR OBIR_5={CFG_UINT,"字体",0,16};
__root const uint OBIR_FT=8;
#else
__root const CFG_HDR OBIR_7={CFG_CBOX,"对齐",0,4};
__root const uint OBIR_T=2;
__root const CFG_CBOX_ITEM BOXOBIR2[4]={AgainCN};
__root const CFG_HDR OBIR_5={CFG_CBOX,"字体",0,17};
__root const uint OBIR_FT=8;
__root const CFG_CBOX_ITEM BOXOBIR1[17]={FontCN};
#endif
__root const CFG_HDR mOBIR0={CFG_LEVEL,"",0,0};
__root const CFG_HDR BIRFILE={CFG_STR_UTF8,"节日文件",0,SLEN-1};
__root const char BIRS_FILE[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\DAY.TXT";
__root const CFG_HDR BIR0={CFG_LEVEL,"",0,0};
//铃声设置
__root const CFG_HDR ALRM1={CFG_LEVEL,"闹钟设置",1,0};
__root const CFG_HDR ALRM_1={CFG_CHECKBOX, "启用", 0, 1};
__root const uint ALRM_ENA=1;
__root const CFG_HDR ALRM_2={CFG_CHECKBOX, "振动", 0, 1};
__root const uint ALRV_ENA=0;
__root const CFG_HDR ALRM_3={CFG_CHECKBOX, "闪屏", 0, 1};
__root const uint ALIU_ENA=1;
__root const CFG_HDR ALRM_4={CFG_COLOR,"背景",0,0};
__root const char ALRM_CBK[4]={255,255,255,100};
__root const CFG_HDR ALRM_5={CFG_COLOR,"字色",0,0};
__root const char ALRM_CTX[4]={0,0,255,75};
#ifdef SCR_LITE
__root const CFG_HDR ALRM_6={CFG_UINT,"字体",0,16};
__root const uint ALRM_FT=8;
#else
__root const CFG_HDR ALRM_6={CFG_CBOX,"字体",0,17};
__root const uint ALRM_FT=8;
__root const CFG_CBOX_ITEM BOXALRMFONT[17]={FontCN};
#endif
__root const CFG_HDR ALRM_7={CFG_UINT,"重复[0-8]",0,9};
__root const uint ALRM_NUM=3;
__root const CFG_HDR ALRM_8={CFG_UINT,"音量[0-6]",0,7};
__root const uint ALRM_VOL=6;
__root const CFG_HDR ALRM_9={CFG_UINT,"振度[1-50]",0,51};
__root const uint ALRM_VIB=30;
__root const CFG_HDR ALRM_A={CFG_UINT,"图数[1-10]",0,11};
__root const uint ALRM_COT=4;
__root const CFG_HDR RINFILE={CFG_STR_UTF8,"铃声",0,SLEN-1};
__root const char ALRM_FILE[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\ALM.MP3";
__root const CFG_HDR RINPIC={CFG_STR_UTF8,"图片",0,SLEN-1};
__root const char ALRM_PIC[SLEN]=DEFAULT_DISK ":\\ZBin\\ScrTool\\AL%d.PNG";
__root const CFG_HDR ALRM0={CFG_LEVEL,"",0,0};
//自动关机
__root const CFG_HDR SHUT1={CFG_LEVEL,"自动关机",1,0};
__root const CFG_HDR SHUT_1={CFG_CHECKBOX, "启用", 0, 2};
__root const uint SHUT_ENA=0;
__root const CFG_HDR SHUT_2={CFG_TIME, "时间", 0, 0};
__root const TTime SHUT_TIME={2,0,0,0};
__root const CFG_HDR SHUT0={CFG_LEVEL,"",0,0};
//自动关机
__root const CFG_HDR ROOT1={CFG_LEVEL,"自动重启",1,0};
__root const CFG_HDR ROOT_1={CFG_CHECKBOX, "启用", 0, 2};
__root const uint ROOT_ENA=1;
__root const CFG_HDR ROOT_2={CFG_TIME, "时间", 0, 0};
__root const TTime ROOT_TIME={6,0,0,0};
__root const CFG_HDR ROOT0={CFG_LEVEL,"",0,0};

