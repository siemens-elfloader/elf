#ifndef _INFO_H_
#define _INFO_H_

class Info
{
public:
  enum InfoMode
  {
    DownloadInfo,
    TrafficInfo
  };
  void Show(Download * _download, InfoMode _mode);

  int onKey(GUI *gui, GUI_MSG *msg);
  void gHook(GUI *gui, int cmd);
  
private:
  void wsprintf_bytes(WSHDR * ws, int bytes);
  void wsprintf_bytes(WSHDR * ws, int bytes1, int bytes2);
  
  InfoMode mode;
  int gui_id;
  int url_pos;
  int path_pos;
  int open_file_pos;
  Download * download;
};

#endif
