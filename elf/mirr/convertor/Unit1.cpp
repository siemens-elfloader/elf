//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <alloc.h>
#include <fcntl.h>
#include <sys\stat.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int __fastcall savefile(char *fname, char *buf,int len)
{
 int handle;
 int i;
 if ((handle = open(fname, O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD)) == -1)
   {
      char s[128];
      sprintf(s,"Error Opening File %s",fname);

      Application->NormalizeTopMosts();
      Application->MessageBox(s, "Ошибка!", MB_OK);
      Application->RestoreTopMosts();

      exit(1);
   }

   if ((i=write(handle, buf, len)) == -1)
   {
      Application->NormalizeTopMosts();
      Application->MessageBox("Не могу сохранить файл! :(", "Ошибка!", MB_OK);
      Application->RestoreTopMosts();
      exit(1);
   }
   else
   {
     Application->NormalizeTopMosts();
     Application->MessageBox("Файл сохранен",/* IntToStr(i).c_str()*/"ok =)", MB_OK);
     Application->RestoreTopMosts();
   }
  close(handle);
  return i;
}

int flen = 0;
char* __fastcall loadfile(char *fname)
{
 int handle;
 int i;
// void *mybuf = malloc(1024*100);
 char mybuf[1024*100];
 if ((handle = open(fname, O_RDONLY | O_BINARY, S_IREAD)) == -1)
   {
      char s[128];
      sprintf(s,"Error Opening File %s",fname);
      ShowMessage(s);
      exit(1);
   }

   if ((i=read(handle, mybuf, 1024*100)) == -1)
   {
      Application->NormalizeTopMosts();
      Application->MessageBox("Не могу прочитать файл! :(", "Ошибка!", MB_OK);
      Application->RestoreTopMosts();
      free(mybuf);
      exit(1);
   }
   else
   {
     flen = i;
     Application->NormalizeTopMosts();
     Application->MessageBox("Файл загружен",/* IntToStr(i).c_str()*/"ok =)", MB_OK);
     Application->RestoreTopMosts();
   }
  close(handle);
  return (char*)mybuf;
}

//------------------------------------------------------------------------------

char* __fastcall hex(char r)
{
  char *temp="  ";
  int y;
  y=r;
  if (y==0) return "00";
  temp[0]= '0';
  if (y>15){temp[0]= '1'; y-=16;}
  if (y>15){temp[0]= '2'; y-=16;}
  if (y>15){temp[0]= '3'; y-=16;}
  if (y>15){temp[0]= '4'; y-=16;}
  if (y>15){temp[0]= '5'; y-=16;}
  if (y>15){temp[0]= '6'; y-=16;}
  if (y>15){temp[0]= '7'; y-=16;}
  if (y>15){temp[0]= '8'; y-=16;}
  if (y>15){temp[0]= '9'; y-=16;}
  if (y>15){temp[0]= 'a'; y-=16;}
  if (y>15){temp[0]= 'b'; y-=16;}
  if (y>15){temp[0]= 'c'; y-=16;}
  if (y>15){temp[0]= 'd'; y-=16;}
  if (y>15){temp[0]= 'e'; y-=16;}
  if (y>15){temp[0]= 'f'; y-=16;}

  temp[1] = '0';
  if (y==1){temp[1]= '1';}
  if (y==2){temp[1]= '2';}
  if (y==3){temp[1]= '3';}
  if (y==4){temp[1]= '4';}
  if (y==5){temp[1]= '5';}
  if (y==6){temp[1]= '6';}
  if (y==7){temp[1]= '7';}
  if (y==8){temp[1]= '8';}
  if (y==9){temp[1]= '9';}
  if (y==10){temp[1]= 'a';}
  if (y==11){temp[1]= 'b';}
  if (y==12){temp[1]= 'c';}
  if (y==13){temp[1]= 'd';}
  if (y==14){temp[1]= 'e';}
  if (y==15){temp[1]= 'f';}
return temp;    
}
void __fastcall hexer(char *dir,char *fname,char buf[],int len)
{
  char *out;
  out = (char*)malloc((len*4)+strlen(fname)+21);
//  zeromem(out,sizeof(out));
  char name[64];
  unsigned long i;
  i = StrToInt(fname[0]);

  if(i>=0 && i<=9)
     sprintf(name,"char _%s_png[] = \x22",fname);
  else
     sprintf(name,"char %s_png[] = \x22",fname);

  strcpy(out,name);
  for (int i=0; i<=len; i++)
  {
/*    char a[3];
    sprintf(a, "\\%02x", buf[i]);
    out[3*i] = a[0];
    out[3*i+1] = a[1];
    out[3*i+2] = a[2];*/
    sprintf(out+strlen(out),"\\x%s",/*out+strlen(out),*/ hex((char)buf[i]));
  }

  sprintf(out+strlen(out),"%s\x22\x3b ",out+strlen(out));
  sprintf(out+strlen(out),"%s  \x0D\x0A",out+strlen(out));

  char s[128];
  sprintf(s,"%s\\%s_png.c",dir,fname);
//  ShowMessage(s);
  char *p = out;
  len=0;
  while(*p++) len++;
//  len += /*strlen(out) +*/ strlen(name)+strlen("\x22\x3b ")+strlen("  \x0D\x0A")+15;
  Form1->Caption = "Saving....";
  savefile(s, out,len);
  Form1->Caption = "All done....";
  if(out) free(out);
}

void __fastcall LoadImage(AnsiString fname, AnsiString dir)
{
  char name[128];
  char *n;
  strcpy(name,fname.c_str());
  n = strrchr(name,'\\')+1;
  for(int i=strlen(n); i>0 && n[i]!='.';i--) n[i]=0;
  if(n) n[strlen(n)-1]=0;//убираем точку
//  ShowMessage(n);
  Form1->Caption = "Processing....";
  char *buf = loadfile(fname.c_str());
  hexer(dir.c_str(),n,buf,flen);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1DblClick(TObject *Sender)
{
  LoadImage(FileListBox1->FileName,FileListBox1->Directory);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Form1->Caption = "Converter *.png to *.c =)";        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
   if(CheckBox1->Checked)
     FileListBox1->Mask = "*.png;*.c";
   else
     FileListBox1->Mask = "*.png";
    FileListBox1->Refresh();
}
//---------------------------------------------------------------------------
