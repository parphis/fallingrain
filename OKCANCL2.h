//----------------------------------------------------------------------------
#ifndef OkCancl2H
#define OkCancl2H
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
//----------------------------------------------------------------------------
class TOKRightDlg : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TEdit *edtProxyPwd;
private:
public:
	virtual __fastcall TOKRightDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKRightDlg *OKRightDlg;
//----------------------------------------------------------------------------
#endif    
