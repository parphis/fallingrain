//----------------------------------------------------------------------------
#ifndef OptionsUH
#define OptionsUH
//----------------------------------------------------------------------------
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ComCtrls.hpp>
//----------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TEdit *edtTMPURL;
	TEdit *edtPCPURL;
	TLabel *lblTMPURL;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtCLCURL;
	TGroupBox *grpbChartURLs;
	TGroupBox *grpbProxy;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edtUserName;
	TEdit *edtp;
	TEdit *edtProxyURL;
	TEdit *edtProxyPort;
	TGroupBox *grpbOpacity;
	TTrackBar *trbOpacity;
	TLabel *lblFRURL;
	void __fastcall lblFRURLClick(TObject *Sender);
private:
public:
	virtual __fastcall TfrmOptions(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//----------------------------------------------------------------------------
#endif    
