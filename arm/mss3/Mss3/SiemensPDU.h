#ifndef _SIEMENSPDU_H_
#define _SIEMENSPDU_H_

class SiememPDU
{
public:
  static int PduDecodeTxt(SDLIST *sd, char *data);
  static int PduDecodeAll(SDLIST *sd, char *data);
  static void DoSmsReport(SDLIST *sd, char *data, WSHDR *ws);
private:
  static void Add2WS(char *data, WSHDR *ws, int len);
  static void Hex2Num(char *hex, char *num, int len);
  static void Bit7Decode(WSHDR *ws, char *pdata, int skip, int len);
};

#endif


