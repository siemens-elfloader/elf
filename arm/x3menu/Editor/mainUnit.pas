unit mainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;


type
  TMenuPoint=record
    Name:array [1..32] of char;
    Description:array [1..128] of char;
    LargeImage:array [1..128] of char;
    SmallImage:array [1..128] of char;
    Execute:array [1..128] of char;
    end;


  TMainForm = class(TForm)
    Panel1: TPanel;
    ListBox1: TListBox;
    Panel2: TPanel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    LabeledEdit1: TLabeledEdit;
    LabeledEdit2: TLabeledEdit;
    LabeledEdit3: TLabeledEdit;
    LabeledEdit4: TLabeledEdit;
    LabeledEdit5: TLabeledEdit;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    Button7: TButton;
    Button8: TButton;
    procedure Button4Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    Menu:array of TMenuPoint;
    Procedure RefreshList;
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

Procedure TMainForm.RefreshList;
var i:integer;
str:string;
begin
ListBox1.Clear;
for i:=0 to Length(Menu)-1 do
 Begin
   SetLength(str,32);
   Move(Menu[i].Name[1],str[1],32);
   ListBox1.Items.Add(str);
 end;

end;



procedure TMainForm.Button4Click(Sender: TObject);
var n:integer;
begin
 SetLength(Menu,Length(Menu)+1);
 ZeroMemory(@Menu[Length(Menu)-1].Name,32);
 if Length(LabeledEdit1.Text)>32 then n:=32 else n:=Length(LabeledEdit1.Text);
 Move(LabeledEdit1.Text[1],Menu[Length(Menu)-1].Name[1],n);
 ZeroMemory(@Menu[Length(Menu)-1].Description,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit2.Text);
 Move(LabeledEdit2.Text[1],Menu[Length(Menu)-1].Description[1],n);
 ZeroMemory(@Menu[Length(Menu)-1].LargeImage,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit3.Text);
 Move(LabeledEdit3.Text[1],Menu[Length(Menu)-1].LargeImage[1],n);
 ZeroMemory(@Menu[Length(Menu)-1].SmallImage,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit4.Text);
 Move(LabeledEdit4.Text[1],Menu[Length(Menu)-1].SmallImage[1],n);
 ZeroMemory(@Menu[Length(Menu)-1].Execute,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit5.Text);
 Move(LabeledEdit5.Text[1],Menu[Length(Menu)-1].Execute[1],n);

RefreshList;
end;

procedure TMainForm.Button2Click(Sender: TObject);
var i:integer;
    f:file of TMenuPoint;
begin
 if not SaveDialog1.Execute then exit;
   AssignFile(f,SaveDialog1.FileName);
   Rewrite(f);
    for i:=0 to Length(Menu)-1 do
     write(f,Menu[i]);
   CloseFile(f);


end;

procedure TMainForm.ListBox1Click(Sender: TObject);
var str:string;
begin
if ListBox1.ItemIndex=-1 then exit;
   SetLength(str,32);
   Move(Menu[ListBox1.ItemIndex].Name[1],str[1],32);
   LabeledEdit1.Text:=str;
   SetLength(str,128);
   Move(Menu[ListBox1.ItemIndex].Description[1],str[1],128);
   LabeledEdit2.Text:=str;
   SetLength(str,128);
   Move(Menu[ListBox1.ItemIndex].LargeImage[1],str[1],128);
   LabeledEdit3.Text:=str;
   SetLength(str,128);
   Move(Menu[ListBox1.ItemIndex].SmallImage[1],str[1],128);
   LabeledEdit4.Text:=str;
   SetLength(str,128);
   Move(Menu[ListBox1.ItemIndex].Execute[1],str[1],128);
   LabeledEdit5.Text:=str;
end;

procedure TMainForm.Button1Click(Sender: TObject);
var i:integer;
    f:file of TMenuPoint;
begin
 if not OpenDialog1.Execute then exit;
SetLength(Menu,0);
   AssignFile(f,OpenDialog1.FileName);
   Reset(f);
   while not Eof(f) do
   begin
    SetLength(Menu,Length(Menu)+1);
    Read(f,Menu[Length(Menu)-1]);
   end;
   CloseFile(f);
RefreshList;
end;

procedure TMainForm.Button3Click(Sender: TObject);
begin
SetLength(Menu,0);
RefreshList;
end;

procedure TMainForm.Button5Click(Sender: TObject);
var n:integer;
begin
if ListBox1.ItemIndex=-1 then exit;

 ZeroMemory(@Menu[ListBox1.ItemIndex].Name,32);
 if Length(LabeledEdit1.Text)>32 then n:=32 else n:=Length(LabeledEdit1.Text);
 Move(LabeledEdit1.Text[1],Menu[ListBox1.ItemIndex].Name[1],n);
 ZeroMemory(@Menu[ListBox1.ItemIndex].Description,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit2.Text);
 Move(LabeledEdit2.Text[1],Menu[ListBox1.ItemIndex].Description[1],n);
 ZeroMemory(@Menu[ListBox1.ItemIndex].LargeImage,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit3.Text);
 Move(LabeledEdit3.Text[1],Menu[ListBox1.ItemIndex].LargeImage[1],n);
 ZeroMemory(@Menu[ListBox1.ItemIndex].SmallImage,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit4.Text);
 Move(LabeledEdit4.Text[1],Menu[ListBox1.ItemIndex].SmallImage[1],n);
 ZeroMemory(@Menu[ListBox1.ItemIndex].Execute,128);
 if Length(LabeledEdit2.Text)>128 then n:=128 else n:=Length(LabeledEdit5.Text);
 Move(LabeledEdit5.Text[1],Menu[ListBox1.ItemIndex].Execute[1],n);

RefreshList;
end;


procedure TMainForm.Button6Click(Sender: TObject);
var i:integer;
begin
if ListBox1.ItemIndex=-1 then exit;
for i:=ListBox1.ItemIndex to Length(Menu)-1 do
 Menu[ListBox1.ItemIndex]:=Menu[ListBox1.ItemIndex+1];
SetLength(Menu,Length(Menu)-1);

RefreshList;
end;

procedure TMainForm.Button7Click(Sender: TObject);
var tmp:TMenuPoint;
begin
if ListBox1.ItemIndex<1 then exit;
tmp:=Menu[ListBox1.ItemIndex-1];
Menu[ListBox1.ItemIndex-1]:=Menu[ListBox1.ItemIndex];
Menu[ListBox1.ItemIndex]:=tmp;
RefreshList;
end;

procedure TMainForm.Button8Click(Sender: TObject);
var tmp:TMenuPoint;
begin
if ListBox1.ItemIndex>=Length(Menu)-1 then exit;
tmp:=Menu[ListBox1.ItemIndex+1];
Menu[ListBox1.ItemIndex+1]:=Menu[ListBox1.ItemIndex];
Menu[ListBox1.ItemIndex]:=tmp;
RefreshList;
end;

end.
