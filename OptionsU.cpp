//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OptionsU.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmOptions *frmOptions;
//--------------------------------------------------------------------- 
__fastcall TfrmOptions::TfrmOptions(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TfrmOptions::lblFRURLClick(TObject *Sender)
{
	ShellExecute(this->Handle, NULL,
		L"http://www.fallingrain.com/world/",
		NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

