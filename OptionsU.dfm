object frmOptions: TfrmOptions
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 375
  ClientWidth = 563
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object CancelBtn: TButton
    Left = 479
    Top = 343
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
  object grpbChartURLs: TGroupBox
    Left = 8
    Top = 8
    Width = 547
    Height = 170
    Caption = 'Chart URLs'
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 67
      Width = 159
      Height = 13
      Caption = 'URL to Get the Precipiation Chart'
    end
    object Label2: TLabel
      Left = 16
      Top = 113
      Width = 159
      Height = 13
      Caption = 'URL to Get the Cloud Level Chart'
    end
    object lblTMPURL: TLabel
      Left = 16
      Top = 21
      Width = 166
      Height = 13
      Caption = 'URL to Get the Temperature Chart'
    end
    object lblFRURL: TLabel
      Left = 334
      Top = 11
      Width = 211
      Height = 13
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Find your region and copy the image URLs'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHighlight
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      GlowSize = 10
      ParentFont = False
      Transparent = False
      OnClick = lblFRURLClick
    end
    object edtCLCURL: TEdit
      Left = 16
      Top = 132
      Width = 511
      Height = 21
      TabOrder = 0
      Text = 
        'http://wx.fallingrain.com/wx.cgi?lat=47.3932&long=18.4604&name-C' +
        'sakvar&what=CLD'
    end
    object edtPCPURL: TEdit
      Left = 16
      Top = 86
      Width = 511
      Height = 21
      TabOrder = 1
      Text = 
        'http://wx.fallingrain.com/wx.cgi?lat=47.3932&long=18.4604&name-C' +
        'sakvar&what=PCP'
    end
    object edtTMPURL: TEdit
      Left = 16
      Top = 40
      Width = 511
      Height = 21
      TabOrder = 2
      Text = 
        'http://wx.fallingrain.com/wx.cgi?lat=47.3932&long=18.4604&name-C' +
        'sakvar&what=TMP'
    end
  end
  object OKBtn: TButton
    Left = 398
    Top = 343
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object grpbProxy: TGroupBox
    Left = 8
    Top = 184
    Width = 547
    Height = 89
    Caption = 'Proxy Settings'
    TabOrder = 3
    object Label3: TLabel
      Left = 16
      Top = 24
      Width = 50
      Height = 13
      Caption = 'Proxy URL'
    end
    object Label4: TLabel
      Left = 16
      Top = 51
      Width = 51
      Height = 13
      Caption = 'Proxy Port'
    end
    object Label5: TLabel
      Left = 185
      Top = 24
      Width = 52
      Height = 13
      Caption = 'User Name'
    end
    object Label6: TLabel
      Left = 185
      Top = 51
      Width = 46
      Height = 13
      Caption = 'Password'
    end
    object edtUserName: TEdit
      Left = 256
      Top = 24
      Width = 271
      Height = 21
      TabOrder = 0
    end
    object edtp: TEdit
      Left = 256
      Top = 51
      Width = 271
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object edtProxyURL: TEdit
      Left = 72
      Top = 21
      Width = 81
      Height = 21
      TabOrder = 2
    end
    object edtProxyPort: TEdit
      Left = 73
      Top = 48
      Width = 32
      Height = 21
      TabOrder = 3
    end
  end
  object grpbOpacity: TGroupBox
    Left = 8
    Top = 279
    Width = 547
    Height = 58
    Caption = 'Opacity'
    TabOrder = 4
    object trbOpacity: TTrackBar
      Left = 16
      Top = 12
      Width = 511
      Height = 42
      Max = 255
      Min = 10
      PageSize = 1
      Position = 10
      PositionToolTip = ptTop
      TabOrder = 0
      ThumbLength = 15
      TickMarks = tmBoth
    end
  end
end
