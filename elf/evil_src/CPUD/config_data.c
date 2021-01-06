#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Show Welcome Message",0,2};
__root const int Welcome=1;

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Auto Mode Setup",1,0};
  __root const CFG_HDR cfghdr11_1={CFG_UINT,"Low akku (0 if off)",0,100};
  __root const unsigned int lowakku=0;
__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Smart Mode Setup",1,0};
  __root const CFG_HDR cfghdr21_1={CFG_UINT,"High Usage of CPU (%)",0,100};
  __root const unsigned int hiusg=80;

  __root const CFG_HDR cfghdr21_2={CFG_UINT,"Low Usage of CPU (%)",0,100};
  __root const unsigned int lousg=20;
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr2={CFG_CHECKBOX,"Use prof1 settings for all profs",0,2};
__root const int global=1;

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Profile1",1,0};
  __root const CFG_HDR cfghdr31_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode1 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox7[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox7[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Profile2",1,0};
  __root const CFG_HDR cfghdr41_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode2 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"Profile3",1,0};
  __root const CFG_HDR cfghdr51_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode3 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox1[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox1[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"Profile4",1,0};
  __root const CFG_HDR cfghdr61_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode4 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox2[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox2[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"Profile5",1,0};
  __root const CFG_HDR cfghdr71_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode5 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox3[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox3[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"Profile6",1,0};
  __root const CFG_HDR cfghdr81_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode6 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox4[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox4[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Profile7",1,0};
  __root const CFG_HDR cfghdr91_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode7 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox5[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox5[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"Profile8",1,0};
  __root const CFG_HDR cfghdr101_1 = {CFG_CBOX, "Mode", 0, 4};
__root const int Mode8 = 0;
#ifdef NEWSGOLD
__root const CFG_CBOX_ITEM cfgcbox6[4] = {"Auto", "52", "208", "Smart"};
#else
__root const CFG_CBOX_ITEM cfgcbox6[4] = {"Auto", "26", "104", "Smart"};
#endif
__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"",0,0};
