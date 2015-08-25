// Laser.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Laser.h"
#include "LaserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaserApp

BEGIN_MESSAGE_MAP(CLaserApp, CWinApp)
	//{{AFX_MSG_MAP(CLaserApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaserApp construction

CLaserApp::CLaserApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLaserApp object

CLaserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLaserApp initialization

BOOL CLaserApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization

	CLaserDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
