object AboutBox: TAboutBox
  Left = 349
  Top = 222
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Hakk'#305'nda'
  ClientHeight = 170
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = OnShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 281
    Height = 129
    BevelInner = bvRaised
    BevelOuter = bvLowered
    ParentColor = True
    TabOrder = 0
    object ProductName: TLabel
      Left = 40
      Top = 8
      Width = 203
      Height = 18
      Alignment = taCenter
      Caption = 'Bilgisayar Proje 1 Dersi'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clNavy
      Font.Height = -16
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentFont = False
      IsControl = True
    end
    object Label1: TLabel
      Left = 96
      Top = 104
      Width = 99
      Height = 17
      Alignment = taCenter
      Caption = 'Murat BALCI'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 88
      Top = 88
      Width = 117
      Height = 17
      Alignment = taCenter
      Caption = 'Mehmet CAMBAZ'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clNavy
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 80
      Top = 56
      Width = 127
      Height = 16
      Alignment = taCenter
      Caption = '2. Proje - Grup 19'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object OKButton: TButton
    Left = 111
    Top = 140
    Width = 75
    Height = 25
    Caption = 'Tamam'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = OKButtonClick
  end
end
