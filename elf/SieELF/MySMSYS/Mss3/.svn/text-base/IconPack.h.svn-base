#ifndef _ICONPACK_H_
#define _ICONPACK_H_


typedef struct _ICONPACK
{
  //main menu
  int mm_crtsms; //create
  int mm_smsnew; //new in sms
  int mm_inbox; //inbox
  int mm_sent;
  int mm_draft;
  int mm_allsms;
  int mm_others;

  //sms type
  int sms_innew;
  int sms_inread;
  int sms_sent;
  int sms_draft;
  //ems
  int ems_innew;
  int ems_inread;
  int ems_sent;
  int ems_draft;
  //headr icon
  //hdr menu
  int hdr_mmenu;
  int hdr_smsnew; //new in list
  int hdr_inbox;
  int hdr_sent;
  int hdr_draft;
  int hdr_allsms;
  int hdr_filter;
  //hdr edit_gui
  int hdr_ed_view;
  int hdr_ed_edit;
  int hdr_ed_adrbk; //addressbook

  //pop-up window icon
  int pp_incoming;
  int pp_showmsg;

  //display
  int dis_smsnew;

  int icon_mysmsys;
}ICONPACK;

class IconPack : public CFile
{
public:
  IconPack();
  ~IconPack();
  ICONPACK ip;
private:
  void LoadIconPack(void);
  void FreeIconPack(void);
  void InitIconPack(void);
  void LoadDefaultIP(void);
  void ZeroIconPack(void);
};

extern IconPack *IP;
#endif
