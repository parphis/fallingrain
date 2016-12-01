//---------------------------------------------------------------------------

#ifndef mainUH
#define mainUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

#include "IdAuthenticationNTLM.hpp"
#include "IdAuthenticationDigest.hpp"
#include "Logger.h"
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <fstream.h>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdAuthentication.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TIdHTTP *FR_HTTP;
	TImage *TEMP;
	TImage *PCP;
	TTrayIcon *tyIcon;
	TPopupMenu *popmMain;
	TMenuItem *Show1;
	TMenuItem *Hide1;
	TMenuItem *Exit1;
	TMenuItem *N1;
	TTimer *tRefreshImages;
	TMenuItem *Options1;
	TImage *CLC;
	void __fastcall FR_HTTPProxyAuthorization(TObject *Sender, TIdAuthentication *Authentication,
          bool &Handled);
	void __fastcall TEMPClick(TObject *Sender);
	void __fastcall PCPClick(TObject *Sender);
	void __fastcall bbtnGetClick(TObject *Sender);
	void __fastcall Show1Click(TObject *Sender);
	void __fastcall Hide1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall tyIconClick(TObject *Sender);
	void __fastcall tyIconDblClick(TObject *Sender);
	void __fastcall tRefreshImagesTimer(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);
	void __fastcall FormClick(TObject *Sender);
private:	// User declarations
	wchar_t temp_path[MAX_PATH];
	wchar_t temperature_img[MAX_PATH];
	wchar_t pcp_img[MAX_PATH];
	wchar_t clc_img[MAX_PATH];
	std::string ConfigFileName;
	AnsiString temperature_url, pcp_url, cloudlevel_url;
	AnsiString proxy_url, proxy_user, proxy_p;
	int proxy_port;
    int opacity;
	bool hidden;

	Log *log;

	void __fastcall GetConfiguration(void);
	void __fastcall SetConfiguration(const char *tmp, const char *pcp,
	const char *clc, const char *proxyurl, const char *proxyport,
	const char *proxyuname, const char *opacity);
	void __fastcall GetPictures(void);
    void __fastcall setProxy(void);

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
