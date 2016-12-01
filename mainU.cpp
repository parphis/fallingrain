/**
 * Application to download images from the www.fallingrain.com.
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainU.h"
#include "OptionsU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

void __fastcall TfrmMain::GetConfiguration(void) {
	std::fstream in(this->ConfigFileName.c_str());
	char *line = new char[1024];
	std::string opt_str = "", opt_name = "", opt_value = "";

	line[0] = '\0';

	if(!in) {
		in.open(this->ConfigFileName.c_str(),
			std::ios::in | std::ios::out | std::ios::trunc);
    }

	while (in) {
		in >> line;
		opt_str = line;

		opt_name = opt_value = "";

		size_t i = opt_str.find_first_of('=');
		opt_name.append(opt_str, 0, i);
		opt_value.append(opt_str, i+1, opt_str.size());

		// decide here what options to load
		if(opt_name.compare("temp_url")==0)
			this->temperature_url = opt_value.c_str();

		if(opt_name.compare("precip_url")==0)
			this->pcp_url = opt_value.c_str();

		if(opt_name.compare("clc_url")==0)
			this->cloudlevel_url = opt_value.c_str();

		if(opt_name.compare("proxy_url")==0)
			this->proxy_url = opt_value.c_str();

		if(opt_name.compare("proxy_port")==0) {
			if(opt_value.empty()==false)
				this->proxy_port = StrToInt(opt_value.c_str());
		}

		if(opt_name.compare("proxy_uname")==0)
			this->proxy_user = opt_value.c_str();

		if(opt_name.compare("opacity")==0) {
			if(opt_value.empty()==false)
				this->opacity = StrToInt(opt_value.c_str());
		}

        setProxy();
	}

	in.close();

	delete [] line;
}

void __fastcall TfrmMain::SetConfiguration(const char *tmp, const char *pcp,
	const char *clc, const char *proxyurl, const char *proxyport,
	const char *proxyuname, const char *opacity) {

	std::fstream config(this->ConfigFileName.c_str(),
		std::ios::in | std::ios::out | std::ios::trunc);

	if(!config) {
		config.open(this->ConfigFileName.c_str(),
			std::ios::in | std::ios::out | std::ios::trunc);
	}

	config << "temp_url=" << tmp << std::endl;
	config << "precip_url=" << pcp << std::endl;
	config << "clc_url=" << clc << std::endl;
	config << "proxy_url=" << proxyurl << std::endl;
	config << "proxy_port=" << proxyport << std::endl;
	config << "proxy_uname=" << proxyuname << std::endl;
	config << "opacity=" << opacity << std::endl;

	config.close();
}

void __fastcall TfrmMain::GetPictures(void) {
    TMemoryStream *ms = new TMemoryStream();

	ms->Clear();

	try {
		FR_HTTP->Get(temperature_url, ms);
		ms->Position = 0;
		if ( (ms->Size > 0) && (FR_HTTP->ResponseCode==200) )
			ms->SaveToFile(temperature_img);
		log->Write("%s\t%d: %s", "Information", FR_HTTP->ResponseCode,
			AnsiString(FR_HTTP->ResponseText).c_str());
		ms->Clear();

		FR_HTTP->Get(pcp_url, ms);
		ms->Position = 0;
		log->Write("%s\t%d: %s", "Information", FR_HTTP->ResponseCode,
			AnsiString(FR_HTTP->ResponseText).c_str());
		if ( (ms->Size > 0) && (FR_HTTP->ResponseCode==200) )
			ms->SaveToFile(pcp_img);
		ms->Clear();

		FR_HTTP->Get(cloudlevel_url, ms);
		ms->Position = 0;
		log->Write("%s\t%d: %s", "Information", FR_HTTP->ResponseCode,
			AnsiString(FR_HTTP->ResponseText).c_str());
		if ( (ms->Size > 0) && (FR_HTTP->ResponseCode==200) )
			ms->SaveToFile(clc_img);
        ms->Clear();
	}
	catch (EIdHTTPProtocolException &e) {
		log->Write("HTTP protocol exception: %s", AnsiString(e.Message).c_str());
	}
	ms->Free();

	FR_HTTP->Disconnect(true);

	TEMP->Picture = NULL;
	PCP->Picture = NULL;
	CLC->Picture = NULL;

	if (FileExists(temperature_img)) {
		TEMP->Picture->LoadFromFile(temperature_img);
	}

	if (FileExists(pcp_img)) {
    	PCP->Picture->LoadFromFile(pcp_img);
	}

	if (FileExists(clc_img)) {
    	CLC->Picture->LoadFromFile(clc_img);
	}
}

void __fastcall TfrmMain::setProxy(void)
{
	FR_HTTP->ProxyParams->ProxyServer = UnicodeString(this->proxy_url.c_str());
	FR_HTTP->ProxyParams->ProxyPort = this->proxy_port;
	FR_HTTP->ProxyParams->ProxyUsername = UnicodeString(this->proxy_user.c_str());
}

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner),
	temperature_url(""),
	pcp_url(""),
	ConfigFileName(".\\.fr.cfg"),
	hidden(false)
{
	GetConfiguration();
	GetTempPath(MAX_PATH, temp_path);
	wcscpy(temperature_img, temp_path);
	wcscpy(pcp_img, temp_path);
	wcscpy(clc_img, temp_path);
	wcsncat(temperature_img, L"tmp.png\0", 8);
	wcsncat(pcp_img, L"pcp.png\0", 8);
	wcsncat(clc_img, L"clc.png\0", 8);

	RECT r;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
	frmMain->Left = r.right-frmMain->Width;
	frmMain->Top = r.bottom-frmMain->Height;

	try {
    	TEMP->Picture->LoadFromFile(temperature_img);
		PCP->Picture->LoadFromFile(pcp_img);
		CLC->Picture->LoadFromFile(clc_img);
	} catch (...) {
		;
	}

    frmMain->AlphaBlendValue = opacity;

	log = new Log(".\\fr.log");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FR_HTTPProxyAuthorization(TObject *Sender, TIdAuthentication *Authentication,
          bool &Handled)
{
	log->Write("Proxy authentication needed", "Warning");
	Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TEMPClick(TObject *Sender)
{
	this->GetPictures();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PCPClick(TObject *Sender)
{
	this->GetPictures();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtnGetClick(TObject *Sender)
{
	this->GetPictures();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Show1Click(TObject *Sender)
{
	int i;

	for (i = Screen->FormCount; i > 0; i--) {
		Screen->Forms[i-1]->Show();
	}

	ShowWindow(frmMain->Handle, SW_RESTORE);
	SetForegroundWindow(frmMain->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Hide1Click(TObject *Sender)
{
	int i;

	ShowWindow(frmMain->Handle, SW_HIDE);

	for (i = 0; i < Screen->FormCount; i++) {
		Screen->Forms[i]->Hide();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Exit1Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tyIconClick(TObject *Sender)
{
	if (hidden) {
		int i;

		for (i = Screen->FormCount; i > 0; i--) {
			Screen->Forms[i-1]->Show();
		}

		SetForegroundWindow(frmMain->Handle);
		ShowWindowAsync(frmMain->Handle, SW_RESTORE);

		hidden = false;
	}
	else {
    	int i;

		ShowWindow(frmMain->Handle, SW_HIDE);

		for (i = 0; i < Screen->FormCount; i++) {
			Screen->Forms[i]->Hide();
		}

		hidden = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tyIconDblClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tRefreshImagesTimer(TObject *Sender)
{
	this->GetPictures();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Options1Click(TObject *Sender)
{
	TfrmOptions *opt = new TfrmOptions(Application);

	opt->edtTMPURL->Text = AnsiString(this->temperature_url).c_str();
	opt->edtPCPURL->Text = AnsiString(this->pcp_url).c_str();
	opt->edtCLCURL->Text = AnsiString(this->cloudlevel_url).c_str();

	opt->edtProxyURL->Text = AnsiString(this->proxy_url);
	opt->edtUserName->Text = AnsiString(this->proxy_user);
	opt->edtp->Text = AnsiString(this->proxy_p);
	opt->edtProxyPort->Text = IntToStr(this->proxy_port);

    opt->trbOpacity->Position = this->opacity;

	if(opt->ShowModal()==IDOK) {

		std::string _tmp = (AnsiString(opt->edtTMPURL->Text)).c_str();
		std::string _pcp = (AnsiString(opt->edtPCPURL->Text)).c_str();
		std::string _clc = (AnsiString(opt->edtCLCURL->Text)).c_str();

		std::string _proxy_url = (AnsiString(opt->edtProxyURL->Text)).c_str();
		std::string _proxy_port = (AnsiString(opt->edtProxyPort->Text)).c_str();
		std::string _uname = (AnsiString(opt->edtUserName->Text)).c_str();
		std::string _p = (AnsiString(opt->edtp->Text)).c_str();
        std::string _opacity = AnsiString(opt->trbOpacity->Position).c_str();

		log->Write("%s\t%s - %s", "Option has changed", _tmp.c_str(), _pcp.c_str());

		this->SetConfiguration(_tmp.c_str(), _pcp.c_str(), _clc.c_str(),
			_proxy_url.c_str(), _proxy_port.c_str(), _uname.c_str(),
			_opacity.c_str());
		this->GetConfiguration();

		setProxy();
		FR_HTTP->ProxyParams->ProxyPassword = UnicodeString(_p.c_str());

        frmMain->AlphaBlendValue = this->opacity;
	}

	delete opt;
	opt = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::FormClick(TObject *Sender)
{
	this->GetPictures();
}
//---------------------------------------------------------------------------

