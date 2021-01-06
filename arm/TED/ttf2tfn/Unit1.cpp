//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  int n = 0;
  for (int i = 0; i < Screen->Fonts->Count; i++)
  {
    ComboBox1->Items->Add(Screen->Fonts->Strings[i]);
    if(Screen->Fonts->Strings[i] == "MS Sans Serif") n = i;
 }
 ComboBox1->ItemIndex = n;
 ComboBox2->Items->Add("Normal");
 ComboBox2->Items->Add("Bold");
 ComboBox2->Items->Add("Italic");
 ComboBox2->Items->Add("Bold Italic");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  int height = Edit1->Text.ToInt();
  Image1->Canvas->Font->Name = ComboBox1->Text;
  Image1->Canvas->Font->Height = height;

  switch(ComboBox2->ItemIndex)
  {
    case 0:
      Image1->Canvas->Font->Style = TFontStyles();
      break;
    case 1:
      Image1->Canvas->Font->Style = TFontStyles()<<fsBold;
      break;
    case 2:
      Image1->Canvas->Font->Style = TFontStyles()<<fsItalic;
      break;
    case 3:
      Image1->Canvas->Font->Style = TFontStyles()<<fsBold<<fsItalic;
      break;
  }

  Image1->Canvas->Brush->Style = bsSolid;

  DeleteFile(ComboBox1->Text+".tfn");
  int f = FileCreate(ComboBox1->Text+".tfn");
  char font_name[256];
  strcpy(font_name, Edit2->Text.c_str());
  font_name[15] = 0;

  unsigned char buf[65536];
  unsigned char widths[256];

  for(int i = 0; i < 65536; buf[i++] = 0);

  int ww = 0, cw, w, h;
  char c[2];

  for(int i = 32; i < 128; i++)
  {
    c[0] = i;
    c[1] = 0;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
    Image1->Canvas->Pen->Color = clBlack;

    h = height;
    cw = 0;
    w = Image1->Canvas->TextWidth(c);
    Image1->Canvas->TextOutA(0,0,c);
    for(int y = 0; y < h; y++)
      for(int x = 0; x < w; x++)
        if(Image1->Canvas->Pixels[x][y]<clGray)
          cw = x>cw?x:cw;
    if(i == 32)
      cw = w-1;
    widths[i] = cw+1;
    if(ww < cw) ww = cw;

  }
  for(int i = 0xC0; i < 0x100; i++)
  {
    c[0] = i;
    c[1] = 0;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
    Image1->Canvas->Pen->Color = clBlack;

    h = height;
    cw = 0;
    w = Image1->Canvas->TextWidth(c);
    Image1->Canvas->TextOutA(0,0,c);
    for(int y = 0; y < h; y++)
      for(int x = 0; x < w; x++)
        if(Image1->Canvas->Pixels[x][y]<clGray)
          cw = x>cw?x:cw;
    widths[i] = cw+1;
    if(ww < cw) ww = cw;

  }
  Image1->Canvas->Pen->Color = clWhite;
  Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
  Image1->Canvas->Pen->Color = clBlack;

  h = height;
  cw = 0;
  w = Image1->Canvas->TextWidth("¨");
  Image1->Canvas->TextOutA(0,0,"¨");
  for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
      if(Image1->Canvas->Pixels[x][y]<clGray)
        cw = x>cw?x:cw;
  widths[0xA8] = cw+1;
  if(ww < cw) ww = cw;

  Image1->Canvas->Pen->Color = clWhite;
  Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
  Image1->Canvas->Pen->Color = clBlack;

  h = height;
  cw = 0;
  w = Image1->Canvas->TextWidth("¸");
  Image1->Canvas->TextOutA(0,0,"¸");
  for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
      if(Image1->Canvas->Pixels[x][y]<clGray)
        cw = x>cw?x:cw;
  widths[0xB8] = cw+1;
  if(ww < cw) ww = cw;

  int bw = (ww>>3)+((ww&7)?1:0);

  for(int i = 0; i < 0x100*(height*bw+1); buf[i] = widths[32], i += (height*bw+1));

  for(int i = 32; i < 128; i++)
  {
    c[0] = i;
    c[1] = 0;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
    Image1->Canvas->Pen->Color = clBlack;

    h = height;
    w = Image1->Canvas->TextWidth(c);
    Image1->Canvas->TextOutA(0,0,c);
    buf[i*(height*bw+1)] = widths[i];
    for(int y = 0, dy = i*(height*bw+1) + 1; y < h; y++)
    {
      unsigned char l = 0;
      for(int x = 0, bx = 0; x < (bw<<3); x++, bx++)
      {
        l<<=1;
        int b = (Image1->Canvas->Pixels[x][y]>clGray)?0:1;
        l |= b;
        if(bx == 7)
        {
          bx = -1;
          buf[dy++] = l;
          l = 0;
       }
      }
    }
  }
  for(int i = 0xC0; i < 0xF0; i++)
  {
    c[0] = i;
    c[1] = 0;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
    Image1->Canvas->Pen->Color = clBlack;

    h = height;
    w = Image1->Canvas->TextWidth(c);
    Image1->Canvas->TextOutA(0,0,c);
    buf[(i-0x40)*(height*bw+1)] = widths[i];
    for(int y = 0, dy = (i-0x40)*(height*bw+1)+1; y < h; y++)
    {
      unsigned char l = 0;
      for(int x = 0, bx = 0; x < (bw<<3); x++, bx++)
      {
        l<<=1;
        int b = (Image1->Canvas->Pixels[x][y]>clGray)?0:1;
        l |= b;
        if(bx == 7)
        {
          bx = -1;
          buf[dy++] = l;
          l = 0;
       }
      }
    }
  }
  for(int i = 0xF0; i < 0x100; i++)
  {
    c[0] = i;
    c[1] = 0;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
    Image1->Canvas->Pen->Color = clBlack;

    h = height;
    w = Image1->Canvas->TextWidth(c);
    Image1->Canvas->TextOutA(0,0,c);
    buf[(i-0x10)*(height*bw+1)] = widths[i];
    for(int y = 0, dy = (i-0x10)*(height*bw+1)+1; y < h; y++)
    {
      int l = 0;
      for(int x = 0, bx = 0; x < (bw<<3); x++, bx++)
      {
        l<<=1;
        int b = (Image1->Canvas->Pixels[x][y]>clGray)?0:1;
        l |= b;
        if(bx == 7)
        {
          bx = -1;
          buf[dy++] = l;
          l = 0;
       }
      }
    }
  }

  Image1->Canvas->Pen->Color = clWhite;
  Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
  Image1->Canvas->Pen->Color = clBlack;

  h = height;
  w = Image1->Canvas->TextWidth("¨");
  Image1->Canvas->TextOutA(0,0,"¨");
  buf[0xF0*(height*bw+1)] = widths[0xA8];
  for(int y = 0, dy = 0xF0*(height*bw+1)+1; y < h; y++)
  {
    int l = 0;
    for(int x = 0, bx = 0; x < (bw<<3); x++, bx++)
    {
      l<<=1;
      int b = (Image1->Canvas->Pixels[x][y]>clGray)?0:1;
      l |= b;
      if(bx == 7)
      {
        bx = -1;
        buf[dy++] = l;
        l = 0;
     }
    }
  }

  Image1->Canvas->Pen->Color = clWhite;
  Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
  Image1->Canvas->Pen->Color = clBlack;

  h = height;
  w = Image1->Canvas->TextWidth("¸");
  Image1->Canvas->TextOutA(0,0,"¸");
  buf[0xF1*(height*bw+1)] = widths[0xB8];
  for(int y = 0, dy = 0xF1*(height*bw+1)+1; y < h; y++)
  {
    int l = 0;
    for(int x = 0, bx = 0; x < (bw<<3); x++, bx++)
    {
      l<<=1;
      int b = (Image1->Canvas->Pixels[x][y]>clGray)?0:1;
      l |= b;
      if(bx == 7)
      {
        bx = -1;
        buf[dy++] = l;
        l = 0;
     }
    }
  }

  FileWrite(f, &bw, 1);
  FileWrite(f, &height, 1);
  FileWrite(f, &font_name, 16);

  FileWrite(f, buf, 0x100*(height*bw+1));
  FileClose(f);

  char FH, FW, fname[16];
  int fh, fw;
  unsigned char l, cc;
  int xp = 0, yp = 0;
  f = FileOpen(ComboBox1->Items->Strings[ComboBox1->ItemIndex]+".tfn", fmOpenRead);

  FileRead(f, &FW, 1);
  FileRead(f, &FH, 1);
  fh = FH; fw = FW;
  FileRead(f, &fname, 16);

  unsigned char *font = new unsigned char[(fw*fh+1) * 256];
  FileRead(f, font, (fw*fh+1) * 256);
  FileClose(f);

  Form1->Image1->Canvas->Brush->Color = clWhite;
  Form1->Image1->Canvas->FillRect(Rect(0,0,Form1->Image1->Width,Form1->Image1->Height));

  for(int i = 0, row = 0; i < 256; i++, row++)
  {
    cc = i;
    w = font[(fw*fh+1) * cc];

    xp += (w + 1);
    if(row == 16) {xp = w+1; yp += fh + 1; row = 0;}
    for(int y = 0; y < fh; y++)
    {
      for(int x = 0, dx = 0; x < fw; x++)
      {
        l = font[(fw*fh+1) * cc + y*fw + x + 1];
        for(int bx = 0; dx < w && bx < 8 ; dx++, bx++)
        {
          Image1->Canvas->Pixels[xp - w - 1 + dx][y + yp] = (l&0x80)?clBlack:clWhite;
          l <<= 1;
        }
      }
    }

  }

  delete []font;
  Image1->Canvas->Pen->Color = clLtGray;
  Image1->Canvas->Brush->Style = bsClear;
  Image1->Canvas->Rectangle(0,0,240,320);
  Image1->Canvas->Rectangle(0,0,132,176);
  Image1->Canvas->Rectangle(0,0,132,132);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
  char font_name[512];
  strcpy(font_name, ComboBox1->Text.c_str());
  font_name[15] = 0;
  Edit2->Text = font_name;
}
//---------------------------------------------------------------------------


