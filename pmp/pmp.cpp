// pmp.cpp : Defines the exported functions for the DLL application.
//

#include "ProTk.h"
#include "pmp.h"
#include "Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}

		// Initializes OLE support for the application. 
		// If AfxOleInit is called from an MFC DLL, the call will fail. 
		// The failure occurs because the function assumes that, if it is called from a DLL, 
		// the OLE system was previously initialized by the calling application. 
		// MFC applications must be initialized as single threaded apartment (STA)
		if (!AfxOleInit())
		{
			AfxMessageBox(L"ERROR in AfxOleInit(): Cannot initialize COM dll...");
			nRetCode = 2;
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}



/*====================================================================*\
FUNCTION :	TestAccessDefault()
PURPOSE  :   enable access to the -Main button
\*====================================================================*/
uiCmdAccessState TestAccessDefault(uiCmdAccessMode access_mode)
{
	return(ACCESS_AVAILABLE);
}


/*====================================================================*\
FUNCTION : user_initialize()
PURPOSE  : Pro/DEVELOP standard initialize - define menu button
\*====================================================================*/
extern "C" int user_initialize(
	int argc,
	char *argv[],
	char *version,
	char *build,
	wchar_t errbuf[80])
{
	ProError status;

	ProUITranslationFilesEnable();

	/*---------------------------------------------------------------------*\
	Loging file open.
	\*---------------------------------------------------------------------*/
	TLog::Open();

	/*---------------------------------------------------------------------*\
	Add new button to the menu bar
	\*---------------------------------------------------------------------*/
	uiCmdCmdId	cmd_id1;

	/*---------------------------------------------------------------------*\
	Add "Simplet" after Utilities button to the menu bar
	\*---------------------------------------------------------------------*/
	status = ProMenubarMenuAdd("PMP_DIALOG", "PMP_DIALOG_LABEL", "Utilities", PRO_B_TRUE, MSGFIL);

	/*---------------------------------------------------------------------*\
	Add Submenu button to the menu bar
	\*---------------------------------------------------------------------*/
	status = ProCmdActionAdd("BT_SHOW_DIALOG", (uiCmdCmdActFn)Gui::Dialog::Show, uiCmdPrioDefault, TestAccessDefault, PRO_B_TRUE, PRO_B_TRUE, &cmd_id1);
	status = ProMenubarmenuPushbuttonAdd("PMP_DIALOG", "BT_SHOW_DIALOG", "BT_SHOW_DIALOG_LABEL", "USER New Button help.", NULL, PRO_B_TRUE, cmd_id1, MSGFIL);

	TLog::Print2(L"%s", L":-> PMP by Mirim System Started Successfully");

	/* Upon success */
	return(0);

#if 0
	/* If unsuccessful, return non-zero.
	* You may store an error message in errbuf.
	* The return value and error message will be displayed to the user.
	* Pro/ENGINEER will call user_terminate() and shut down your application
	*/
	ProStringToWstring(errbuf, "Sample error message");
	return(-1);
#endif
}


/*====================================================================*\
FUNCTION : user_terminate()
PURPOSE  : To handle any termination actions
\*====================================================================*/
extern "C" void user_terminate()
{
	cout << "user_terminate" << endl;
}


