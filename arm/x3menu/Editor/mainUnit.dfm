object MainForm: TMainForm
  Left = 191
  Top = 141
  BorderStyle = bsDialog
  Caption = 'MenuEditor'
  ClientHeight = 389
  ClientWidth = 512
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 512
    Height = 41
    Align = alTop
    TabOrder = 0
    object Button1: TButton
      Left = 88
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Open'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 168
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'New'
      TabOrder = 2
      OnClick = Button3Click
    end
  end
  object ListBox1: TListBox
    Left = 0
    Top = 41
    Width = 153
    Height = 348
    Align = alLeft
    ItemHeight = 13
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object Panel2: TPanel
    Left = 153
    Top = 41
    Width = 359
    Height = 348
    Align = alClient
    TabOrder = 2
    object LabeledEdit1: TLabeledEdit
      Left = 16
      Top = 24
      Width = 326
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Name'
      TabOrder = 0
    end
    object LabeledEdit2: TLabeledEdit
      Left = 16
      Top = 64
      Width = 326
      Height = 21
      EditLabel.Width = 53
      EditLabel.Height = 13
      EditLabel.Caption = 'Description'
      TabOrder = 1
    end
    object LabeledEdit3: TLabeledEdit
      Left = 16
      Top = 104
      Width = 326
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'LargeImage'
      TabOrder = 2
    end
    object LabeledEdit4: TLabeledEdit
      Left = 16
      Top = 144
      Width = 326
      Height = 21
      EditLabel.Width = 54
      EditLabel.Height = 13
      EditLabel.Caption = 'SmallImage'
      TabOrder = 3
    end
    object LabeledEdit5: TLabeledEdit
      Left = 16
      Top = 184
      Width = 326
      Height = 21
      EditLabel.Width = 39
      EditLabel.Height = 13
      EditLabel.Caption = 'Execute'
      TabOrder = 4
    end
    object Button4: TButton
      Left = 16
      Top = 216
      Width = 75
      Height = 25
      Caption = 'Add'
      TabOrder = 5
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 96
      Top = 216
      Width = 75
      Height = 25
      Caption = 'Apply'
      TabOrder = 6
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 176
      Top = 216
      Width = 75
      Height = 25
      Caption = 'Delete'
      TabOrder = 7
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 256
      Top = 216
      Width = 33
      Height = 25
      Caption = '/\'
      TabOrder = 8
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 296
      Top = 216
      Width = 33
      Height = 25
      Caption = '\/'
      TabOrder = 9
      OnClick = Button8Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 304
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    Left = 336
    Top = 16
  end
end
